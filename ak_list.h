#ifndef LIST_H
#define LIST_H

template <typename type>
struct list_entry
{
    type Entry;
    list_entry<type>* Next;
    list_entry<type>* Prev;
};

template <typename type>
struct list
{
    list_entry<type>* First;
    list_entry<type>* Last;
    u32 Count;
    
    inline void Add(list_entry<type>* Entry)
    {
        if(Count == 0)
        {
            Last = First = Entry;
        }
        else if(Count == 1)
        {
            Last = Entry;
            Last->Prev = First;
            First->Next = Last;
        }
        else
        {
            Entry->Prev = Last;
            Last = Entry;
            Entry->Prev->Next = Last;
        }
        Count++;
    }
    
    inline type* Allocate(arena* Storage)
    {
        list_entry<type>* Result = PushStruct(Storage, list_entry<type>, Clear, 0);
        Add(Result);
        return &Result->Entry;
    }    
    
    inline list_entry<type>* Pop()
    {
        ASSERT(Last && (Count > 0)); 
        
        list_entry<type>* Result = NULL;
        if(Count == 1)
        {
            Result = Last;
            Last = First = NULL;                
        }
        else
        {        
            list_entry<type>* Prev = Last->Prev;
            Result = Last;
            ASSERT(!Result->Next);
            Last = Prev;
            Result->Prev = NULL;            
            Last->Next = NULL;
        }
        
        Count--;
        return Result;
    }
    
    inline void Remove(list_entry<type>* Entry)
    {
        ASSERT(Count > 0);
        if(Count == 1)
        {
            ASSERT(!Entry->Prev && !Entry->Next);
            First = Last = NULL;        
        }
        else
        {
            list_entry<type>* Prev = Entry->Prev;
            list_entry<type>* Next = Entry->Next;
            
            if(!Prev)
            {
                ASSERT(First == Entry);
                First = Next;
                First->Prev = NULL;
            }        
            else if(!Next)
            {
                ASSERT(Last == Entry);
                Last = Prev;
                Last->Next = NULL;
            }
            else
            {
                Prev->Next = Next;
                Next->Prev = Prev;
            }
            
            Entry->Prev = Entry->Next = NULL;
        }
        
        Count--;
    }
};

template <typename type>
struct list_iterator
{
    list<type>* List;
    list_entry<type>* CurrentEntry;
};

template <typename type>
struct free_list
{
    list<type> List;
    list<type> FreeList;    
    
    inline type* Allocate(arena* Storage)
    {
        if(FreeList.Count > 0)
        {
            list_entry<type>* Entry = RemoveEndOfList(&FreeList);        
            AddToList(&List, Entry);    
            return &Entry->Entry;
        }
        else
        {        
            type* Result = AllocateListEntry(&List, Storage);
            return Result;
        }        
    }
    
    inline void Free(list_entry<type>* Entry)
    {
        RemoveFromList(&List, Entry);        
        ClearStruct(&Entry->Entry, type);
        AddToList(&FreeList, Entry);
    }
    
    inline void Free(type* Entry)
    {
        list_entry<type>* ListEntry = (list_entry<type>*)Entry;
        FreeListEntry(ListEntry);    
    }
    
    inline void FreeAll()
    {
        list_entry<type>* Entry = List.First; 
        for(u32 Index = 0; Index < List.Count; Index++)
        {
            list_entry<type>* ToFree = Entry;
            Entry = Entry->Next;
            FreeListEntry(ToFree);
        }    
        ASSERT(List.Count == 0);
    }
};

template <typename type>
list_iterator<type> BeginIter(list<type>* List)
{
    list_iterator<type> Result = {};
    Result.List = List;
    return Result;
}

template <typename type>
type* GetFirst(list_iterator<type>* Iter)
{
    ASSERT(!Iter->CurrentEntry);    
    Iter->CurrentEntry = Iter->List->First;
    return &Iter->CurrentEntry->Entry;
}

template <typename type>
type* GetNext(list_iterator<type>* Iter)
{
    ASSERT(Iter->CurrentEntry);
    list_entry<type>* Next = Iter->CurrentEntry->Next;
    if(Next)
    {
        Iter->CurrentEntry = Next;
        return &Next->Entry;
    }    
    return NULL;
}

#endif