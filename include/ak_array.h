#ifndef AK_ARRAY_H
#define AK_ARRAY_H

template <typename type>
struct ak_array
{    
    ak_u32 Size;
    ak_u32 Capacity;
    type* Entries;
    
    type& operator[](ak_u32 Index);    
    type* Get(ak_u32 Index);    
    type* operator+(ak_u32 Index);    
    void Add(type Value);
    void Reserve(ak_u32 NewCapacity);
    void Resize(ak_u32 NewSize);
    void Clear();                
};

template <typename type>
struct ak_array_iter
{
    ak_u32 Index;
    ak_array<type>* Array;    
    
    AK_ITER_FUNCTIONS(type);    
};

template <typename type>
struct ak_fixed_array
{
    type*  Data;
    ak_u32 Size;    
    
    type& operator[](ak_u32 Index);
    type* Get(ak_u32 Index);
    type* operator+(ak_u32 Index);
};

template <typename type> ak_array<type> AK_CreateArray(ak_u32 InitialCapacity=32);
template <typename type> ak_fixed_array<type> AK_CreateArray(type* Data, ak_u32 Size);
template <typename type> void AK_DeleteArray(ak_array<type>* Array);
template <typename type> ak_array_iter<type> AK_BeginIter(ak_array<type>* Array);

#endif