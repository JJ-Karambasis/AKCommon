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
    
    inline type* operator+(u32 Index)
    {
        ASSERT(Index < Size);
        return &Data[Index];
    }
};

template <typename type>
inline dynamic_array<type> CreateDynamicArray(u32 InitialCapacity)
{
    dynamic_array<type> Result;
    Result.Capacity = InitialCapacity;
    Result.Size = 0;
    Result.Data = NULL;
    return Result;
}

template <typename type>
inline b32 IsInitialized(dynamic_array<type>* Array)
{
    b32 Result = Array->Capacity > 0;
    return Result;
}

template <typename type>
inline void DeleteDynamicArray(dynamic_array<type>* Array)
{
    if(Array->Data)
        __Internal_Free__(Array->Data);    
    Array->Data = NULL;
    Array->Capacity = Array->Size = 0;
}

template <typename type>
inline void Append(dynamic_array<type>* Array, type Value)
{
    ASSERT(IsInitialized(Array));
    if(!Array->Data)        
        Array->Data = (type*)__Internal_Allocate__(sizeof(type)*Array->Capacity);            
    
    if(Array->Size == Array->Capacity)
    {
        Array->Capacity *= 2;
        type* Temp = (type*)__Internal_Allocate__(sizeof(type)*Array->Capacity);
        CopyMemory(Temp, Array->Data, Array->Size*sizeof(type));
        __Internal_Free__(Array->Data);
        Array->Data = Temp;
    }
    
    Array->Data[Array->Size++] = Value;
}

#endif