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
    
    inline b32 IsInitialized()
    {
        b32 Result = Entries != NULL;    
        return Result;
    }
        
    inline u32 GetIndex(u64 ID)
    {
        i32 Result = (u32)(ID & 0xFFFFFFFF);
        return Result;
    }
        
    inline b32 IsAllocatedID(u64 ID)
    {
        b32 Result = (ID & 0xFFFFFFFF00000000) != 0;
        return Result;
    }    
    
    inline u64 Allocate()
    {
        u32 Index;
        if(FreeHead != INVALID_FREE_HEAD)
        {
            Index = FreeHead;
        }
        else
        {
            //CONFIRM(JJ): Should we handle a dynamically grow pool? 
            ASSERT(MaxUsed < Capacity);
            Index = MaxUsed++;
        }
        
        pool_entry<type>* Entry = Entries + Index;    
        if(FreeHead != -1)    
            FreeHead = Entry->ID & 0xFFFFFFFF;
        
        Entry->ID = (NextKey++ << 32) | Index;
        return Entry->ID;
    }
        
    inline void Free(u64 ID)
    {
        ASSERT(IsAllocatedID(ID));
        u32 Index = GetIndex(ID);
        
        pool_entry<type>* Entry = &Entries[Index];
        ClearStruct(&Entry->Entry, type);
        
        Entry->ID = (0 | FreeHead);    
        ASSERT(!IsAllocatedID(Entry->ID));
        FreeHead = Index;
    }
    
    inline void Free(type* Entry)
    {
        u64 ID = ((u64*)Entry)[-1];
        Free(ID);
    }
    
    inline type* Get(u64 ID)
    {
        if(!IsAllocatedID(ID))
            return NULL;
        
        i32 Index = GetIndex(ID);
        pool_entry<type>* Entry = &Entries[Index];
        if(Entry->ID != ID)
            return NULL;
        
        type* Result = &Entry->Entry;
        return Result;
    }
    
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
    
    if(Pool->IsInitialized())
    {
        for(u32 Index = 0; Index < Pool->Capacity; Index++)
        {
            pool_entry<type>* Entry = Pool->Entries + Index;
            if(Pool->IsAllocatedID(Entry->ID))
            {
                Iter->CurrentID = Entry->ID;
                return &Entry->Entry;
            }
        }
    }
    
    return NULL;
}

template <typename type>
type* GetNext(pool_iter<type>* Iter)
{
    ASSERT(Iter->CurrentID != 0);    
    
    pool<type>* Pool = Iter->Pool;
    if(Pool->IsInitialized())
    {
        for(u32 Index = Pool->GetIndex(Iter->CurrentID)+1; Index < Pool->Capacity; Index++)
        {
            pool_entry<type>* Entry = Pool->Entries + Index;
            if(Pool->IsAllocatedID(Entry->ID))
            {
                Iter->CurrentID = Entry->ID;
                return &Entry->Entry;
            }
        }
    }
    
    return NULL;
}
                                  

#endif