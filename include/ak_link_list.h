#ifndef AK_LINK_LIST
#define AK_LINK_LIST

template <typename type>
struct ak_link_entry
{    
    type Entry;
    ak_link_entry<type>* Next;
    ak_link_entry<type>* Prev;
};

template <typename type>
struct ak_link_list
{    
    ak_link_entry<type>* First;
    ak_link_entry<type>* Last;
    ak_u32 Size;
    
    void Push(ak_link_entry<type>* Entry);
    void Push(ak_arena* Arena, type Entry);
    ak_link_entry<type>* Pop();
    void Remove(ak_link_entry<type>* Entry);
};

template <typename type>
struct ak_link_list_iter
{
    ak_link_list<type>* List;
    
    ak_link_entry<type>* Current;
    
    AK_ITER_FUNCTIONS(type);
};

template <typename type> ak_link_list_iter<type> AK_BeginIter(ak_link_list<type>* Iter);

#endif