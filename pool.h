#ifndef POOL_H
#define POOL_H

#define INVALID_FREE_HEAD (u32)-1

template <typename type>
struct pool_entry
{
    u64 ID;
    type Entry;
};

template <typename type>
struct pool
{
    pool_entry<type>* Entries;
    u32 MaxUsed;
    u64 NextKey;
    u32 FreeHead;
    u32 Capacity;
};

template <typename type>
pool<type> CreatePool(arena* Arena, u32 Capacity)
{
    pool<type> Result = {};
    Result.NextKey = 1;
    Result.FreeHead = INVALID_FREE_HEAD;
    Result.Capacity = Capacity;
    Result.Entries = PushArray(Arena, Capacity, pool_entry<type>, Clear, 0);
    return Result;
}

inline u32 GetPoolIndex(u64 ID)
{
    i32 Result = (u32)(ID & 0xFFFFFFFF);
    return Result;
}

inline b32 IsAllocatedID(u64 ID)
{
    b32 Result = (ID & 0xFFFFFFFF00000000) != 0;
    return Result;
}

template <typename type>
u64 AllocateFromPool(pool<type>* Pool)
{
    u32 Index;
    if(Pool->FreeHead != INVALID_FREE_HEAD)
    {
        Index = Pool->FreeHead;
    }
    else
    {
        //CONFIRM(JJ): Should we handle a dynamically grow pool? 
        ASSERT(Pool->MaxUsed < Pool->Capacity);
        Index = Pool->MaxUsed++;
    }
    
    pool_entry<type>* Entry = Pool->Entries + Index;    
    if(Pool->FreeHead != -1)    
        Pool->FreeHead = Entry->ID & 0xFFFFFFFF;
    
    Entry->ID = (Pool->NextKey++ << 32) | Index;
    return Entry->ID;
}

template <typename type>
void FreeFromPool(pool<type>* Pool, u64 ID)
{
    ASSERT(IsAllocatedID(ID));
    u32 Index = GetPoolIndex(ID);
    
    pool_entry<type>* Entry = &Pool->Entries[Index];
    ClearStruct(&Entry->Entry, type);
    
    Entry->ID = (0 | Pool->FreeHead);    
    ASSERT(!IsAllocatedID(Entry->ID));
    Pool->FreeHead = Index;
}

template <typename type>
type* GetByID(pool<type>* Pool, u64 ID)
{
    ASSERT(IsAllocatedID(ID));
    i32 Index = GetPoolIndex(ID);    
    type* Result = &Pool->Entries[Index].Entry;
    return Result;
}

template <typename type>
struct pool_iter
{
    pool<type>* Pool;
    u64 CurrentID;
};

template <typename type>
pool_iter<type> BeginIter(pool<type>* Pool)
{
    pool_iter<type> Result = {};
    Result.Pool = Pool;    
    return Result;
}

template <typename type>
type* GetFirst(pool_iter<type>* Iter)
{
    ASSERT(Iter->CurrentID == 0);
    
    pool<type>* Pool = Iter->Pool;
    for(u32 Index = 0; Index < Pool->Capacity; Index++)
    {
        pool_entry<type>* Entry = Pool->Entries + Index;
        if(IsAllocatedID(Entry->ID))
        {
            Iter->CurrentID = Entry->ID;
            return &Entry->Entry;
        }
    }
    
    return NULL;
}

template <typename type>
type* GetNext(pool_iter<type>* Iter)
{
    ASSERT(Iter->CurrentID != 0);    
    
    pool<type>* Pool = Iter->Pool;
    for(u32 Index = GetPoolIndex(Iter->CurrentID)+1; Index < Pool->Capacity; Index++)
    {
        pool_entry<type>* Entry = Pool->Entries + Index;
        if(IsAllocatedID(Entry->ID))
        {
            Iter->CurrentID = Entry->ID;
            return &Entry->Entry;
        }
    }
    
    return NULL;
}
                                  

#endif