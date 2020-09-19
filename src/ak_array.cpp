template <typename type>
void AK_Array__Internal_Expand(ak_array<type>* Array)
{    
    if(!Array->Data)
    {
        Array->Data = (type*)AllocateMemory(sizeof(type)*Array->Capacity);
        return;
    }
    
    type* Temp = (type*)AllocateMemory(sizeof(type)*Array->Capacity);
    CopyMemory(Temp, Array->Data, Array->Size*sizeof(type));
    FreeMemory(Array->Data);
    Array->Data = Temp;        
}

template <typename type>
type& ak_array<type>::operator[](ak_u32 Index)
{
    AK_Assert(Index < Size, "Index out of bounds");
    return Entries[Index];
} 

template <typename type>
type* ak_array<type>::Get(ak_u32 Index)
{
    AK_Assert(Index < Size, "Index out of bounds");
    return &Entries[Index];
}

template <typename type>
type* ak_array<type>::operator+(ak_u32 Index)
{        
    return Get(Index);
}

template <typename type>
void ak_array<type>::Add(type Value)
{   
    if(Capacity == 0)
        *this = AK_CreateArray<type>();
    
    if(Size == Capacity)     
        Reserve(Capacity*2);            
    
    Entries[Size++] = Value;
}

template <typename type>
void ak_array<type>::Reserve(ak_u32 NewCapacity)
{
    if(NewCapacity > Capacity)
    {
        Capacity = NewCapacity;
        type* Temp = (type*)AK_Allocate(Capacity*sizeof(type));
        AK_MemoryCopy(Temp, Entries, sizeof(type)*Size);
        AK_Free(Entries);
        Entries = Temp;
    }
}

template <typename type>
void ak_array<type>::Resize(ak_u32 NewSize)
{    
    Reserve(NewSize);
    if(NewSize > Size)
        AK_MemoryClear(Entries+Size, (NewSize-Size)*sizeof(type));
    else if(NewSize < Size)
        AK_MemoryClear(Entries+NewSize, (Size-NewSize)*sizeof(type));
    Size = NewSize;
}

template <typename type>
void ak_array<type>::Clear()
{
    AK_MemoryClear(Entries, sizeof(type)*Size);
    Size = 0;    
}

template <typename type>
ak_array<type> AK_CreateArray(ak_u32 InitialCapacity)
{
    ak_array<type> Result = {};    
    Result.Capacity = InitialCapacity;    
    Result.Entries = (type*)AK_Allocate(sizeof(type)*InitialCapacity);    
    Result.Size = 0;    
    return Result;
}

template <typename type> 
void AK_DeleteArray(ak_array<type>* Array)
{
    if(Array->Entries) AK_Free(Array->Entries);
    Array->Size = 0;
    Array->Capacity = 0;
    Array->Entries = NULL;
}

template <typename type>
ak_array_iter<type> AK_BeginIter(ak_array<type>* Array)
{
    ak_array_iter<type> Result = {};
    Result.Array = Array;
    return Result;
}

template <typename type>
type* ak_array_iter<type>::First()
{
    AK_Assert(Index == 0, "Iterator has already begun");    
    if(Index < Array->Size) return Array->Get(Index++);        
    return NULL;    
}

template <typename type>
type* ak_array_iter<type>::Next()
{
    AK_Assert(Index != 0, "Iterator should call First() before calling Next()");
    if(Index < Array->Size) return Array->Get(Index++);        
    return NULL;
}

template <typename type>
ak_fixed_array<type> AK_CreateArray(type* Data, ak_u32 Size)
{
    ak_fixed_array<type> Result = {Data, Size};
    return Result;
}

template <typename type>
type& ak_fixed_array<type>::operator[](ak_u32 Index)
{
    AK_Assert(Index < Size, "Index out of bounds");
    return Data[Index];
}