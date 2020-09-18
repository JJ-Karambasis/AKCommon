#ifndef AK_POOL_H
#define AK_POOL_H

#define AK_PoolIndex(ID) ((ak_u32)(ID & 0xFFFFFFFF))

template <typename type>
struct ak_pool
{    
    ak_u32 Capacity;
    ak_u32 MaxUsed;
    ak_u64 NextKey;
    ak_u32 FreeHead;
    type*   Entries;
    ak_u64* IDs;
    
    
    ak_bool IsInitialized();
    ak_u64 Allocate();
    void Free(ak_u64 ID);
    type* Get(ak_u64 ID);
    void FreeAll();
};

template <typename type>
struct ak_pool_iter
{
    ak_pool<type>* Pool;
    ak_u64 CurrentID;    
    AK_ITER_FUNCTIONS(type);
};

template <typename type> ak_pool<type> AK_CreatePool(ak_u32 InitialCapacity=32);
template <typename type> void AK_DeletePool(ak_pool<type>* Pool);
template <typename type> ak_pool_iter<type> AK_BeginIter(ak_pool<type>* Pool);

#endif