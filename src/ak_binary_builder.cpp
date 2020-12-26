template <typename type> type* ak_binary_builder::Allocate()
{
    if(!Arena)
        Arena = AK_CreateArena();
    return Arena->Push<type>();
}

template <typename type> 
ak_u32 ak_binary_builder::Write(type Type)
{
    type* Data = Allocate<type>();
    *Data = Type;
    return sizeof(type);
}

void ak_binary_builder::WriteString(ak_char* Format, ...)
{
    if(!Arena)
        Arena = AK_CreateArena();
    
    va_list Args;
    va_start(Args, Format);
    AK_Internal__ArenaBuilderWrite(Arena, Format, Args);
    va_end(Args);
}

void ak_binary_builder::WriteString(const ak_char* Format, ...)
{
    if(!Arena)
        Arena = AK_CreateArena();
    
    va_list Args;
    va_start(Args, Format);
    AK_Internal__ArenaBuilderWrite(Arena, (ak_char*)Format, Args);
    va_end(Args);
}

ak_buffer ak_binary_builder::PushBuffer(ak_arena* DstArena)
{
    ak_buffer Result = {};
    if(Arena)
    {
        Result.Size = Arena->GetTotalUsed();
        Result.Data = (ak_u8*)DstArena->Push(Result.Size);
        
        ak_uaddr At = 0;
        for(ak_memory_block* Block = Arena->FirstBlock; Block; Block = Block->Next)
        {
            ak_uaddr BlockSize = Block->Current-Block->Start;            
            AK_MemoryCopy(Result.Data+At, Block->Start, BlockSize);
            At += BlockSize;
        }
        
        AK_Assert(At == Result.Size, "String builder allocation is invalid. This is a programming error.");        
        return Result;
    }
    return Result;
}

void ak_binary_builder::Clear()
{
    if(Arena)
        Arena->Clear();
}

void ak_binary_builder::ReleaseMemory()
{
    if(Arena)
        AK_DeleteArena(Arena);
    Arena = NULL;
}