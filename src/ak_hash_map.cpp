ak_u32 AK_HashMap__Internal_Pow2Ceil(ak_u32 V)
{
    --V;
    V |= V >> 1;
    V |= V >> 2;
    V |= V >> 4;
    V |= V >> 8;
    V |= V >> 16;
    ++V;
    V += ( V == 0 );    
    return V;
}

template <typename key, typename value>
ak_i32 AK_HashMap__Internal_FindSlot(ak_hash_map<key, value>* Map, key& Key)
{
    ak_u32 SlotMask = Map->SlotCapacity - 1;
    ak_u32 Hash = AK_HashFunction(Key);
    
    ak_u32 BaseSlot = Hash & SlotMask;
    ak_u32 BaseCount = Map->Slots[BaseSlot].BaseCount;
    ak_u32 Slot = BaseSlot;
    
    while(BaseCount > 0)
    {
        ak_u32 SlotHash = Map->Slots[Slot].KeyHash;
        if(SlotHash)
        {
            ak_u32 SlotBase = SlotHash & SlotMask;
            if(SlotBase == BaseSlot)
            {
                AK_Assert(BaseCount > 0, "No active slots");
                BaseCount--;
                if(SlotHash == Hash && AK_HashCompare(Map->ItemKeys[Map->Slots[Slot].ItemIndex], Key))
                    return (ak_i32)Slot;
            }
        }        
        
        Slot = (Slot+1) & SlotMask;
    }
    
    return -1;
}

template <typename key, typename value>
void AK_HashMap__Internal_ExpandSlots(ak_hash_map<key, value>* Map)
{
    ak_u32 OldCapacity = Map->SlotCapacity;
    ak_hash_map_slot* OldSlots = Map->Slots;
    
    Map->SlotCapacity *= 2;
    ak_u32 SlotMask = Map->SlotCapacity-1;
    
    Map->Slots = (ak_hash_map_slot*)AK_Allocate(Map->SlotCapacity*sizeof(ak_hash_map_slot));
    for(ak_u32 OldSlotIndex = 0; OldSlotIndex < OldCapacity; OldSlotIndex++)
    {
        ak_u32 Hash = OldSlots[OldSlotIndex].KeyHash;
        if(Hash)
        {
            ak_u32 BaseSlot = Hash & SlotMask;
            ak_u32 Slot = BaseSlot;
            while(Map->Slots[Slot].KeyHash)
                Slot = (Slot+1) & SlotMask;
            Map->Slots[Slot].KeyHash = Hash;
            ak_u32 ItemIndex = OldSlots[OldSlotIndex].ItemIndex;
            Map->Slots[Slot].ItemIndex = ItemIndex;
            Map->ItemSlots[ItemIndex] = Slot;            
            Map->Slots[BaseSlot].BaseCount++;
        }
    }
    
    AK_Free(OldSlots);
}

template <typename key, typename value>
void AK_HashMap__Internal_ExpandItems(ak_hash_map<key, value>* Map)
{
    Map->ItemCapacity *= 2;
    void* MapData = AK_Allocate(Map->ItemCapacity * (sizeof(key) + sizeof(value) + sizeof(ak_u32)));        
    
    key* NewItemKeys = (key*)MapData;
    ak_u32* NewItemSlots = (ak_u32*)(NewItemKeys + Map->ItemCapacity);
    value* NewItemEntries = (value*)(NewItemSlots + Map->ItemCapacity);        
    
    AK_MemoryCopy(NewItemKeys, Map->ItemKeys, Map->Size*sizeof(key));
    AK_MemoryCopy(NewItemSlots, Map->ItemSlots, Map->Size*sizeof(ak_u32));
    AK_MemoryCopy(NewItemEntries, Map->ItemEntries, Map->Size*sizeof(value));
    
    AK_Free(Map->ItemKeys);
    
    Map->ItemKeys = NewItemKeys;
    Map->ItemSlots = NewItemSlots;
    Map->ItemEntries = NewItemEntries;        
}

template <typename key, typename value>
ak_bool ak_hash_map<key, value>::IsInitialized()
{
    ak_bool Result = SlotCapacity > 0 && Slots && ItemKeys;
    return Result;
}

template <typename key, typename value>
void ak_hash_map<key, value>::Insert(key Key, value Value)
{
    if(!IsInitialized())
        *this = AK_CreateHashMap<key, value>();
    
    AK_Assert(AK_HashMap__Internal_FindSlot(this, Key) < 0, "Cannot insert duplicate keys into hash map");
    
    if(Size >= (SlotCapacity - SlotCapacity/3))
        AK_HashMap__Internal_ExpandSlots(this);
    
    ak_u32 SlotMask = SlotCapacity-1;
    ak_u32 Hash = AK_HashFunction(Key);
    
    ak_u32 BaseSlot = Hash & SlotMask;
    ak_u32 BaseCount = Slots[BaseSlot].BaseCount;
    ak_u32 Slot = BaseSlot;
    ak_u32 FirstFree = Slot;
    
    while(BaseCount)
    {
        ak_u32 SlotHash = Slots[Slot].KeyHash;
        if(SlotHash == 0 && (Slots[FirstFree].KeyHash != 0)) FirstFree = Slot;
        ak_u32 SlotBase = SlotHash & SlotMask;
        if(SlotBase == BaseSlot)
            BaseCount--;
        Slot = (Slot+1) & SlotMask;
    }
    
    Slot = FirstFree;
    while(Slots[Slot].KeyHash)
        Slot = (Slot+1) & SlotMask;
    
    if(Size >= ItemCapacity)
        AK_HashMap__Internal_ExpandItems(this);
    
    AK_Assert(!Slots[Slot].KeyHash && (Hash & SlotMask) == BaseSlot, "");
    AK_Assert(Hash, "Invalid hash");
    
    Slots[Slot].KeyHash = Hash;
    Slots[Slot].ItemIndex = Size;
    Slots[BaseSlot].BaseCount++;
    
    ItemEntries[Size] = Value;
    ItemKeys[Size] = Key;
    ItemSlots[Size] = Slot;
    
    Size++;
}

template <typename key, typename value>
void ak_hash_map<key, value>::Remove(key Key)
{   
    if(!IsInitialized())
        *this = AK_CreateHashMap<key, value>();
    
    ak_i32 Slot = AK_HashMap__Internal_FindSlot(this, Key);
    AK_Assert(Slot >= 0, "Cannot find entry with key in hash map");
    
    ak_u32 SlotMask = SlotCapacity-1;
    ak_u32 Hash = Slots[Slot].KeyHash;
    ak_u32 BaseSlot = Hash & SlotMask;
    AK_Assert(Hash, "Hash is invalid");
    Slots[BaseSlot].BaseCount--;
    Slots[Slot].KeyHash = 0;
    
    ak_u32 Index = Slots[Slot].ItemIndex;
    ak_u32 LastIndex = Size-1;
    
    if(Index != LastIndex)
    {
        ItemKeys[Index] = ItemKeys[LastIndex];
        ItemSlots[Index] = ItemSlots[LastIndex];
        ItemEntries[Index] = ItemEntries[LastIndex];
        Slots[ItemSlots[LastIndex]].ItemIndex = Index;
    }
    
    Size--;
    
}

template <typename key, typename value>
value* ak_hash_map<key, value>::Find(key Key)
{   
    if(!IsInitialized())
        *this = AK_CreateHashMap<key, value>();
    
    ak_i32 Slot = AK_HashMap__Internal_FindSlot(this, Key);
    if(Slot < 0) return NULL;
    
    ak_u32 Index = Slots[Slot].ItemIndex;
    return &ItemEntries[Index];
}

template <typename key, typename value>
void ak_hash_map<key, value>::Reset()
{
    if(!IsInitialized())
        *this = AK_CreateHashMap<key, value>();
    
    Size = 0;
    AK_MemoryClear(Slots, SlotCapacity*sizeof(ak_hash_map_slot));
}

template <typename key, typename value>
ak_hash_map<key, value> AK_CreateHashMap(ak_u32 InitialCapacity)
{
    ak_hash_map<key, value> Result = {};
    InitialCapacity = AK_HashMap__Internal_Pow2Ceil(InitialCapacity);        
    Result.SlotCapacity = AK_HashMap__Internal_Pow2Ceil(InitialCapacity + InitialCapacity/2);
    Result.Slots = (ak_hash_map_slot*)AK_Allocate(sizeof(ak_hash_map_slot)*Result.SlotCapacity);
    
    Result.ItemCapacity = InitialCapacity;
    void* MapData = AK_Allocate(Result.ItemCapacity * (sizeof(key) + sizeof(value) + sizeof(ak_u32)));   
    
    Result.ItemKeys = (key*)MapData;
    Result.ItemSlots = (ak_u32*)(Result.ItemKeys + Result.ItemCapacity);
    Result.ItemEntries = (value*)(Result.ItemSlots + Result.ItemCapacity);
    
    return Result;
}

template <typename key, typename value>
void AK_DeleteHashMap(ak_hash_map<key, value>* HashMap)
{
    if(HashMap->Slots) AK_Free(HashMap->Slots);
    if(HashMap->ItemKeys) AK_Free(HashMap->ItemKeys);
    *HashMap = {};    
}

ak_u32 AK_HashFunction(ak_u64 Key)
{
    Key = ( ~Key ) + ( Key << 18 );
    Key = Key ^ ( Key >> 31 );
    Key = Key * 21;
    Key = Key ^ ( Key >> 11 );
    Key = Key + ( Key << 6 );
    Key = Key ^ ( Key >> 22 );      
    return (ak_u32)Key;
}

ak_u32 AK_HashFunction(ak_u32 Key)
{    
    return AK_HashFunction((ak_u64)Key);
}

ak_u32 AK_HashFunction(ak_f32 Value)
{
    union
    {
        ak_f32 Float;
        ak_u32 Int;
    } U;
    
    U.Float = Value;
    return AK_HashFunction(U.Int);
}

ak_u32 AK_HashFunction(ak_char* Value)
{
    ak_u64 Result = 0;
    ak_u64 Rand1 = 31414;
    ak_u64 Rand2 = 27183;
    
    char* At = Value;
    while(*At)
    {
        Result *= Rand1;
        Result += *At;
        Rand1 *= Rand2;At++;
    }
    
    return AK_HashFunction(Result);
}

ak_u32 AK_HashFunction(const ak_char* Value)
{
    return AK_HashFunction((ak_char*)Value);
}

ak_u32 AK_HashFunction(ak_string Value)
{
    ak_u64 Result = 0;
    ak_u64 Rand1 = 31414;
    ak_u64 Rand2 = 27183;
    
    for(ak_u32 Index = 0; Index < Value.Length; Index++)
    {
        Result *= Rand1;
        Result += Value[Index];
        Rand1 *= Rand2;
    }
    
    return AK_HashFunction(Result);
}

ak_u32 AK_HashFunction(ak_pair<ak_u32> Pair)
{
    return AK_HashFunction(AK_BijectiveMap(Pair.A, Pair.B));
}

ak_u32 AK_HashFunction(ak_pair<ak_i32> Pair)
{
    return AK_HashFunction((ak_u64)AK_BijectiveMap(Pair.A, Pair.B));
}

ak_bool AK_HashCompare(ak_u64 A, ak_u64 B)
{
    return A == B;
}

ak_bool AK_HashCompare(ak_u32 A, ak_u32 B)
{
    return A == B;
}

ak_bool AK_HashCompare(ak_f32 A, ak_f32 B)
{
    return A == B;
}

ak_bool AK_HashCompare(char* A, char* B)
{
    return AK_StringEquals(A, B);
}

ak_bool AK_HashCompare(ak_string A, ak_string B)
{
    return AK_StringEquals(A, B);
}

ak_bool AK_HashCompare(ak_pair<ak_u32> PairA, ak_pair<ak_u32> PairB)
{
    return (PairA.A == PairB.A) && (PairA.B == PairB.B);    
}

ak_bool AK_HashCompare(ak_pair<ak_i32> PairA, ak_pair<ak_i32> PairB)
{
    return (PairA.A == PairB.A) && (PairA.B == PairB.B);    
}