#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <typename type>
struct dynamic_array
{
    u32 Capacity;
    u32 Size;
    type* Data;
    
    inline type& operator[](u32 Index)
    {
        ASSERT(Index < Size);
        return Data[Index];
    } 
    
    inline type* Get(u32 Index)
    {
        ASSERT(Index < Size);
        return &Data[Index];
    }
    
    inline type* operator+(u32 Index)
    {        
        return Get(Index);
    }
    
    inline b32 IsInitialized()
    {
        b32 Result = Capacity > 0;
        return Result;
    }
    
    
    inline void Add(type Value)
    {
        ASSERT(IsInitialized());
        if(!Data)        
            Data = (type*)AllocateMemory(sizeof(type)*Capacity);            
        
        if(Size == Capacity)
        {
            Capacity *= 2;
            type* Temp = (type*)AllocateMemory(sizeof(type)*Capacity);
            CopyMemory(Temp, Data, Size*sizeof(type));
            FreeMemory(Data);
            Data = Temp;
        }
        
        Data[Size++] = Value;
    }
};

template <typename type>
inline dynamic_array<type> CreateDynamicArray(u32 InitialCapacity=1)
{
    dynamic_array<type> Result;
    Result.Capacity = InitialCapacity;
    Result.Size = 0;
    Result.Data = NULL;
    return Result;
}

template <typename type>
inline void DeleteDynamicArray(dynamic_array<type>* Array)
{
    if(Array->Data)
        FreeMemory(Array->Data);    
    Array->Data = NULL;
    Array->Capacity = Array->Size = 0;
}

template <typename type>
struct dynamic_array_iter
{
    dynamic_array<type>* Array;    
    u32 Index;
};

template <typename type>
dynamic_array_iter<type> BeginIter(dynamic_array<type>* Array)
{
    dynamic_array_iter<type> Result = {};
    Result.Array = Array;
    return Result;
}

template <typename type>
type* GetFirst(dynamic_array_iter<type>* Iter)
{
    ASSERT(Iter->Index == 0);
    if(Iter->Index >= Iter->Array->Size)
        return NULL;
    
    Iter->Index++;
    return Iter->Array->Get(0);
}

template <typename type>
type* GetNext(dynamic_array_iter<type>* Iter)
{
    ASSERT(Iter->Index != 0);
    if(Iter->Index >= Iter->Array->Size)
        return NULL;    
    return Iter->Array->Get(Iter->Index++);
}

#endif