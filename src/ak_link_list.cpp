template <typename type> 
void ak_link_list<type>::Push(ak_link_entry<type>* Entry)
{
    if(Size == 0)
    {
        Last = First = Entry;
    }
    else if(Size == 1)
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
    Size++;
}

template <typename type> 
void ak_link_list<type>::Push(ak_arena* Arena, type Entry)
{
    ak_link_entry<type>* LinkEntry = Arena->Push<ak_link_entry<type>>();
    LinkEntry->Entry = Entry;
    Push(LinkEntry);
}

template <typename type> 
ak_link_entry<type>* ak_link_list<type>::Pop()
{
    AK_Assert(Last && (Count > 0), "Cannot pop from link list that is empty"); 
    
    list_entry<type>* Result = NULL;
    if(Size == 1)
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
    
    Size--;
    return Result;
}

template <typename type> 
void ak_link_list<type>::Remove(ak_link_entry<type>* Entry)
{
    AK_Assert(Last && (Size > 0), "Cannot remove from lihnk list that is empty");
    if(Size == 1)
    {
        AK_Assert(!Entry->Prev && !Entry->Next, "Invalid link list");
        First = Last = NULL;        
    }
    else
    {
        ak_link_entry<type>* Prev = Entry->Prev;
        ak_link_entry<type>* Next = Entry->Next;
        
        if(!Prev)
        {
            AK_Assert(First == Entry, "Invalid link list");
            First = Next;
            First->Prev = NULL;
        }        
        else if(!Next)
        {
            AK_Assert(Last == Entry, "Invalid link list");
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
    Size--;
}    

template <typename type>
ak_link_list_iter<type> AK_BeginIter(ak_link_list<type>* LinkList)
{
    ak_link_list_iter<type> Result = {};
    Result.List = LinkList;    
    return Result;
}

template <typename type>
type* ak_link_list_iter<type>::First()
{    
    AK_Assert(!Current, "Iterator has already begun");
    Current = List->First;
    if(Current) return &Current->Entry;    
    return NULL;
}

template <typename type>
type* ak_link_list_iter<type>::Next()
{
    AK_Assert(Current, "Iterator should call First() before calling Next()");    
    ak_link_entry<type>* Next = Current->Next;
    if(Next)
    {
        Current = Next;
        return &Next->Entry;
    }    
    return NULL;    
}