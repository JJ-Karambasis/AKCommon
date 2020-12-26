void AK_Internal__ArenaBuilderWrite(ak_arena* Arena, ak_char* Format, va_list Args)
{
    ak_arena* GlobalArena = AK_GetGlobalArena();
    ak_temp_arena TempArena = GlobalArena->BeginTemp();
    
    ak_string WriteString = AK_FormatString(GlobalArena, Format, Args);        
    ak_char* DstString = Arena->PushArray<ak_char>(WriteString.Length);
    
    AK_MemoryCopy(DstString, WriteString.Data, WriteString.Length);
    
    GlobalArena->EndTemp(&TempArena);
}

void AK_Internal__StringBuilderWrite(ak_string_builder* StringBuilder, ak_char* Format, va_list Args)
{
    if(!StringBuilder->Arena)
        StringBuilder->Arena = AK_CreateArena();
    AK_Internal__ArenaBuilderWrite(StringBuilder->Arena, Format, Args);
}

void ak_string_builder::Write(ak_char* Format, ...)
{
    va_list Args;
    va_start(Args, Format);
    AK_Internal__StringBuilderWrite(this, Format, Args);
    va_end(Args);
}

void ak_string_builder::WriteChar(ak_char Character)
{
    if(!Arena)
        Arena = AK_CreateArena();
    
    ak_char* V = Arena->PushArray<char>(1);
    *V = Character;
}

void ak_string_builder::WriteLine(ak_char* Format, ...)
{
    va_list Args;
    va_start(Args, Format);
    AK_Internal__StringBuilderWrite(this, Format, Args);
    va_end(Args);
    NewLine();
}

void ak_string_builder::NewLine()
{
    WriteChar('\n');
}

ak_string ak_string_builder::PushString(ak_arena* DstArena)
{
    if(Arena)
    {
        ak_u32 Size = AK_SafeAddrToU32(Arena->GetTotalUsed());        
        ak_string Result = AK_AllocateString(Size, DstArena);
        
        ak_uaddr At = 0;
        for(ak_memory_block* Block = Arena->FirstBlock; Block; Block = Block->Next)
        {
            ak_uaddr BlockSize = Block->Current-Block->Start;            
            AK_MemoryCopy(Result.Data+At, Block->Start, BlockSize);
            At += BlockSize;
        }
        
        AK_Assert(At == Size, "String builder allocation is invalid. This is a programming error.");        
        return Result;
    }
    else
        return AK_CreateEmptyString();
}

void ak_string_builder::Clear()
{
    if(Arena)
        Arena->Clear();
}


void ak_string_builder::ReleaseMemory()
{
    if(Arena)
        AK_DeleteArena(Arena);
    Arena = NULL;
}
