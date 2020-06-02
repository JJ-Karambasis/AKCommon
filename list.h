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
};

template <typename type>
inline void AddToList(list<type>* List, list_entry<type>* Entry)
{
    if(List->Count == 0)
    {
        List->Last = List->First = Entry;
    }
    else if(List->Count == 1)
    {
        List->Last = Entry;
        List->Last->Prev = List->First;
        List->First->Next = List->Last;
    }
    else
    {
        Entry->Prev = List->Last;
        List->Last = Entry;
        Entry->Prev->Next = List->Last;
    }
    List->Count++;
}

template <typename type>
list_entry<type>* RemoveEndOfList(list<type>* List)
{
    ASSERT(List->Last && (List->Count > 0)); 
    
    result* Result = NULL;
    if(List->Count == 1)
    {
        Result = List->Last;
        List->Last = List->First = NULL;                
    }
    else
    {        
        result* Prev = List->Last->Prev;
        Result = List->Last;
        ASSERT(!Result->Next);
        List->Last = Prev;
        Result->Prev = NULL;            
    }
    
    List->Count--;
    return Result;
}

template <typename type>
void RemoveFromList(list<type>* List, list_entry<type>* Entry)
{
    ASSERT(List->Count > 0);
    if(List->Count == 1)
    {
        ASSERT(!Entry->Prev && !Entry->Next);
        List->First = List->Last = NULL;        
    }
    else
    {
        entry* Prev = Entry->Prev;
        entry* Next = Entry->Next;
        
        if(!Prev)
        {
            ASSERT(List->First == Entry);
            List->First = Next;
            List->First->Prev = NULL;
        }        
        else if(!Next)
        {
            ASSERT(List->Last == Entry);
            List->Last = Prev;
            List->Last->Next = NULL;
        }
        else
        {
            Prev->Next = Next;
            Next->Prev = Prev;
        }
        
        Entry->Prev = Entry->Next = NULL;
    }
    
    List->Count--;
}

template <typename type>
type* AllocateListEntry(list<type>* List, arena* Storage)
{
    list_entry<type>* Result = PushStruct(Storage, list_entry<type>, Clear, 0);
    AddToList(List, Result);
    return &Result->Entry;
}

template <typename type>
type* AllocateListEntry(free_list<type>* FreeList, arena* Storage)
{    
    if(List->FreeList.Count > 0)
    {
        list_entry<type>* Entry = RemoveEndOfList(FreeList->FreeList);        
        AddToList(&FreeList->List, Entry);    
        return &Entry->Entry;
    }
    else
    {
        type* Result = AllocateListEntry(FreeList->List, Storage);
        return Result;
    }        
}

template <typename type>
type* FreeListEntry(free_list<type>* FreeList, list_entry<type>* Entry)
{    
    RemoveFromList(&FreeList->List, Entry);        
    AddToList(&FreeList->FreeList, Entry);
}

template <typename type>
void FreeAllEntries(free_list<type>* FreeList)
{
    list_entry<type>* Entry = FreeList->List.First; 
    for(u32 Index = 0; Index < FreeList->List.Count; Index++)
    {
        list_entry<type>* ToFree = Entry;
        Entry = Entry->Next;
        FreeListEntry(FreeList, ToFree);
    }    
    ASSERT(FreeList->List.Count == 0);
}

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