#ifndef AK_HASH_MAP_H
#define AK_HASH_MAP_H

#ifndef AK_DEFAULT_HASH_MAP_SIZE 
#define AK_DEFAULT_HASH_MAP_SIZE 8191
#endif

struct ak_hash_map_slot
{
    ak_u32 KeyHash;
    ak_u32 ItemIndex;
    ak_u32 BaseCount;
};

template <typename key, typename value>
struct ak_hash_map
{   
    ak_u32 Size;
    ak_u32 SlotCapacity;
    ak_u32 ItemCapacity;
    
    ak_hash_map_slot* Slots;
    key*    ItemKeys;
    ak_u32* ItemSlots;
    value*  ItemEntries;
    
    ak_bool IsInitialized();
    void   Insert(key Key, value Value);    
    value* Find(key Key);
    void   Remove(key Key);
    void   Reset();    
};

template <typename key, typename value>
ak_hash_map<key, value> AK_CreateHashMap(ak_u32 InitialCapacity=AK_DEFAULT_HASH_MAP_SIZE);

template <typename key, typename value>
void AK_DeleteHashMap(ak_hash_map<key, value>* HashMap);

////////////////////////////////////////////////////
//NOTE(EVERYONE): Common hash functions
////////////////////////////////////////////////////
ak_u32 AK_HashFunction(ak_u64 Key);
ak_u32 AK_HashFunction(ak_u32 Key);
ak_u32 AK_HashFunction(ak_f32 Value);
ak_u32 AK_HashFunction(ak_char* Value);
ak_u32 AK_HashFunction(const ak_char* Value);
ak_u32 AK_HashFunction(ak_pair<ak_u32> Pair);
ak_u32 AK_HashFunction(ak_pair<ak_i32> Pair);


////////////////////////////////////////////////////
//NOTE(EVERYONE): Common compare functions
////////////////////////////////////////////////////
ak_bool AK_HashCompare(ak_u64 A, ak_u64 B);
ak_bool AK_HashCompare(ak_u32 A, ak_u32 B);
ak_bool AK_HashCompare(ak_f32 A, ak_f32 B);
ak_bool AK_HashCompare(char* A, char* B);
ak_bool AK_HashCompare(ak_pair<ak_u32> PairA, ak_pair<ak_u32> PairB);
ak_u32 AK_HashFunction(ak_pair<ak_i32> PairA, ak_pair<ak_i32> PairB);

#endif