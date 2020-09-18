#undef AK_INVALID_FREE_HEAD
#define AK_INVALID_FREE_HEAD ((ak_u32)-1)

inline ak_bool AK_Internal__PoolIsAllocatedID(ak_u64 ID)
{
    ak_bool Result = (ID & 0xFFFFFFFF00000000) != 0;
    return Result;
}    

template <typename type>
ak_bool ak_pool<type>::IsInitialized()
{
    return Entries && IDs && Capacity;
}

template <typename type>
ak_u64 ak_pool<type>::Allocate()
{
    AK_Assert(IsInitialized(), "Pool is not initialized");
    
    ak_u32 Index;
    if(FreeHead != AK_INVALID_FREE_HEAD)
    {
        Index = FreeHead;
    }
    else
    {
        //CONFIRM(JJ): Should we handle a dynamically grow pool? 
        if(MaxUsed == Capacity)
        {
            Capacity *= 2;            
            void* Temp = AK_Allocate(Capacity*(sizeof(type)+sizeof(ak_u64)));
            AK_MemoryCopy(Temp, Entries, MaxUsed*sizeof(type));
            AK_MemoryCopy((ak_u8*)Temp+Capacity*sizeof(type), IDs, MaxUsed*sizeof(ak_u64));            
            AK_Free(Entries);
            Entries = (type*)Temp;
            IDs = (ak_u64*)(Entries+Capacity);            
        }        
        Index = MaxUsed++;
    }
    
    type* Entry = Entries + Index;    
    ak_u64* ID = IDs + Index;
    AK_MemoryClear(Entry, sizeof(type));
    
    if(FreeHead != AK_INVALID_FREE_HEAD)    
        FreeHead = *ID & 0xFFFFFFFF;
    
    *ID = (NextKey++ << 32) | Index;
    return *ID;
}

template <typename type> 
void ak_pool<type>::Free(ak_u64 ID)
{
    if(ID)
    {
        AK_Assert(AK_Internal__PoolIsAllocatedID(ID), "Cannot free an already freed entry from the pool.");
        ak_u32 Index = AK_PoolIndex(ID);
        AK_Assert(Index < MaxUsed, "Index out of bounds.");
        IDs[Index] = (0 | FreeHead);
        FreeHead = Index;
    }
}

template <typename type>
type* ak_pool<type>::Get(ak_u64 ID)
{
    if(!AK_Internal__PoolIsAllocatedID(ID))
        return NULL;
    
    ak_u32 Index = AK_PoolIndex(ID);
    AK_Assert(Index < MaxUsed, "Index out of bounds.");
    if(IDs[Index] != ID)
        return NULL;
    
    type* Result = &Entries[Index];
    return Result;
}

template <typename type>
void ak_pool<type>::FreeAll()
{
    for(ak_u32 Index = 0; Index < MaxUsed; Index++)
    {
        if(AK_Internal__PoolIsAllocatedID(IDs[Index]))
            Free(IDs[Index]);
    }
}

template <typename type>
ak_pool<type> AK_CreatePool(ak_u32 InitialCapacity)
{
    ak_pool<type> Result = {};
    Result.NextKey = 1;
    Result.FreeHead = AK_INVALID_FREE_HEAD;
    Result.Capacity = InitialCapacity;
    
    void* Data = AK_Allocate(InitialCapacity*(sizeof(type)+sizeof(ak_u64)));
    Result.Entries = (type*)Data;
    Result.IDs = (ak_u64*)(Result.Entries+InitialCapacity);
    return Result;
}

template <typename type>
void AK_DeletePool(ak_pool<type>* Pool)
{
    if(Pool->Entries)
    {
        AK_Free(Pool->Entries);
        *Pool = {};
    }    
}

template <typename type>
ak_pool_iter<type> AK_BeginIter(ak_pool<type>* Pool)
{    
    AK_Assert(Pool->IsInitialized(), "Pool is not initialized");        
    ak_pool_iter<type> Result = {};
    Result.Pool = Pool;
    return Result;
}

template <typename type>
type* ak_pool_iter<type>::First()
{
    AK_Assert(CurrentID == 0, "Iterator has already begun");    
    for(ak_u32 Index = 0; Index < Pool->MaxUsed; Index++)
    {
        if(AK_Internal__PoolIsAllocatedID(Pool->IDs[Index]))
        {
            CurrentID = Pool->IDs[Index];
            return &Pool->Entries[Index];
        }
    }
    
    return NULL;
}

template <typename type>
type* ak_pool_iter<type>::Next()
{
    AK_Assert(CurrentID != 0, "Iterator should call First() before calling Next()");        
    for(ak_u32 Index = AK_PoolIndex(CurrentID)+1; Index < Pool->MaxUsed; Index++)
    {
        if(AK_Internal__PoolIsAllocatedID(Pool->IDs[Index]))
        {
            CurrentID = Pool->IDs[Index];
            return &Pool->Entries[Index];
        }
    }
    
    return NULL;    
}