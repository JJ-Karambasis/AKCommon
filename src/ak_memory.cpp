global ak_memory_info _AK_Internal__MemoryInfo;
global ak_memory_info* AK_Internal__MemoryInfo;

ak_memory_block* AK_Internal__GetArenaBlock(ak_arena* Arena, ak_uaddr Size, ak_i32 Alignment)
{
    ak_memory_block* Block = Arena->CurrentBlock;
    if(!Block)
        return NULL;
    
    ak_u8* CurrentUsed = Block->Current;
    if(Alignment != 0)
    {
        AK_Assert((Alignment & (Alignment-1)) == 0, "Alignment is not a power of two");
        CurrentUsed = (ak_u8*)AK_AlignTo((ak_uaddr)CurrentUsed, Alignment);
    }    
    
    if(CurrentUsed+Size > Block->End)
    {
        Block = Block->Next;
        return Block;
    }
    
    return Block;
}

ak_memory_block* AK_CreateMemoryBlock(ak_uaddr BlockSize)
{
    ak_memory_block* Block = (ak_memory_block*)AK_Allocate(BlockSize + sizeof(ak_memory_block));    
    Block->Start = (ak_u8*)(Block+1);
    Block->Current = Block->Start;
    Block->End = Block->Start + BlockSize;
    Block->Prev = Block->Next = NULL;
    return Block;
}

void AK_Internal__AddBlockToArena(ak_arena* Arena, ak_memory_block* Block)
{
    ak_memory_block* Last = Arena->LastBlock;
    if(!Last)
    {
        AK_Assert(!Arena->FirstBlock, "Arena list is screwed up. This is a programming error.");
        Arena->FirstBlock = Arena->LastBlock = Block;
    }
    else
    {
        Last->Next = Block;
        Block->Prev = Last;
        Arena->LastBlock = Block;
    }
}

void* AK_MemoryCopy(void* Dst, void* Src, ak_uaddr Size)
{
    ak_u8* DstAt = (ak_u8*)Dst;
    ak_u8* SrcAt = (ak_u8*)Src;
    while(Size--)
        *DstAt++ = *SrcAt++;
    return Dst;
}

void* AK_MemoryCopy(void* Dst, const void* Src, ak_uaddr Size)
{
    return AK_MemoryCopy(Dst, (void*)Src, Size);
}

template <typename type>
type* AK_MemorySet(type* Memory, type Data, ak_uaddr Count)
{    
    for(ak_uaddr Index = 0; Index < Count; Index++)
        Memory[Index] = Data;
    return Memory;
}

void AK_MemoryClear(void* Memory, ak_uaddr Size)
{
    AK_MemorySet((ak_u8*)Memory, (ak_u8)0, Size);
}

template <typename type>
type* AK_CopyArray(type* Dst, type* Src, ak_u32 Count)
{
    for(ak_u32 Index = 0; Index < Count; Index++)
        Dst[Index] = Src[Index];
    return Dst;
}

template <typename type>
type* AK_CopyArray(type* Dst, const type* Src, ak_u32 Count)
{
    return AK_CopyArray(Dst, (type*)Src, Count);
}

ak_bool ak_buffer::IsValid()
{
    return Data && Size;
}

ak_u8* ak_stream::Read(ak_uaddr Size)
{
    AK_Assert((Current + Size) <= End, "Stream read overflow");
    ak_u8* Result = Current;
    Current += Size;
    return Result;
}

template <typename type>
type* ak_stream::Read()
{
    return (type*)Read(sizeof(type));
}

template <typename type>
type* ak_stream::ReadArray(ak_u32 Count)
{
    return (type*)Read(sizeof(type)*Count);
}

ak_stream AK_CreateStream(ak_u8* Stream, ak_uaddr Size)
{
    ak_stream Result = {};
    Result.Start = Stream;
    Result.Current = Stream;
    Result.End = Stream + Size;
    return Result;
}

void ak_arena::Clear()
{
    AK_Assert(TempCheck(), "Cannot clear arena. Still have temporary arenas being used.");
    for(ak_memory_block* Block = FirstBlock; Block; Block = Block->Next)
        Block->Current = Block->Start;
    CurrentBlock = FirstBlock;
}

void* ak_arena::Push(ak_uaddr Size, ak_arena_clear_flags ClearFlags, ak_i32 Alignment)
{    
    AK_Assert(Size < InitialBlockSize, "Size of the arena allocation must be smaller than the block size.");
    
    ak_memory_block* Block = AK_Internal__GetArenaBlock(this, Size, Alignment);
    if(!Block)
    {   
        Block = AK_CreateMemoryBlock(InitialBlockSize);        
        AK_Internal__AddBlockToArena(this, Block);
    }
    
    CurrentBlock = Block;
    if(Alignment != 0)
        Block->Current = (ak_u8*)AK_AlignTo((ak_uaddr)Block->Current, Alignment);
    
    void* Result = Block->Current;
    Block->Current += Size;
    
    if(ClearFlags == AK_ARENA_CLEAR_FLAGS_CLEAR)
        AK_MemoryClear(Result, Size);
    
    return Result;
}

void* ak_arena::Push(ak_uaddr Size, ak_i32 Alignment)
{
    return Push(Size, AK_ARENA_CLEAR_FLAGS_CLEAR, Alignment);    
}

void* ak_arena::Push(ak_uaddr Size, ak_arena_clear_flags ClearFlags)
{
    return Push(Size, ClearFlags, 0);
}

void* ak_arena::Push(ak_uaddr Size)
{
    return Push(Size, AK_ARENA_CLEAR_FLAGS_CLEAR, 0);
}

template <typename type> 
type* ak_arena::Push(ak_arena_clear_flags ClearFlags, ak_i32 Alignment)
{
    type* Result = (type*)Push(sizeof(type), ClearFlags, Alignment);
    return Result;
}

template <typename type> 
type* ak_arena::Push(ak_i32 Alignment)
{
    type* Result = (type*)Push(sizeof(type), Alignment);
    return Result;
}

template <typename type> 
type* ak_arena::Push(ak_arena_clear_flags ClearFlags)
{
    type* Result = (type*)Push(sizeof(type), ClearFlags);
    return Result;
}

template <typename type> 
type* ak_arena::Push()
{
    type* Result = (type*)Push(sizeof(type));
    return Result;
}

template <typename type> 
type* ak_arena::PushArray(ak_u32 Count, ak_arena_clear_flags ClearFlags, ak_i32 Alignment)
{
    type* Result = (type*)Push(sizeof(type)*Count, ClearFlags, Alignment);
    return Result;
}

template <typename type> 
type* ak_arena::PushArray(ak_u32 Count, ak_i32 Alignment)
{
    type* Result = (type*)Push(sizeof(type)*Count, Alignment);
    return Result;
}

template <typename type> 
type* ak_arena::PushArray(ak_u32 Count, ak_arena_clear_flags ClearFlags)
{
    type* Result = (type*)Push(sizeof(type)*Count, ClearFlags);
    return Result;
}

template <typename type> 
type* ak_arena::PushArray(ak_u32 Count)
{
    type* Result = (type*)Push(sizeof(type)*Count);
    return Result;
}

ak_temp_arena ak_arena::BeginTemp()
{
    ak_temp_arena TempArena = {};        
    TempArena.Arena = this;
    AK_Assert(CurrentBlock, "Arena has not been initialized");
    TempArena.MemoryBlock = CurrentBlock;
    TempArena.BlockMarker = CurrentBlock->Current;    
    TemporaryArenas++;
    return TempArena;
}

void ak_arena::EndTemp(ak_temp_arena* TempArena)
{           
    AK_Assert(TempArena->Arena == this, "You are ending a temporary arena on an arena that did not start it");
    CurrentBlock = TempArena->MemoryBlock;
    CurrentBlock->Current = TempArena->BlockMarker;
    for(ak_memory_block* Block = CurrentBlock->Next; Block; Block = Block->Next)
        Block->Current = Block->Start;    
    TemporaryArenas--;
}

ak_bool ak_arena::TempCheck()
{
    return TemporaryArenas == 0;
}

ak_uaddr ak_arena::GetTotalUsed()
{
    ak_uaddr Result = 0;    
    for(ak_memory_block* Block = FirstBlock; Block; Block = Block->Next)    
        Result += ((ak_uaddr)Block->Current-(ak_uaddr)Block->Start);                
    return Result;
}

ak_arena* AK_CreateArena(ak_uaddr InitialBlockSize)
{
    void* Memory = AK_Allocate(InitialBlockSize + sizeof(ak_arena) + sizeof(ak_memory_block));
    ak_arena* Arena = (ak_arena*)Memory;
    Arena->InitialBlockSize = InitialBlockSize;
    
    ak_memory_block* Block = (ak_memory_block*)(Arena+1);
    Block->Start = (ak_u8*)(Block+1);
    Block->Current = Block->Start;
    Block->End = Block->Start+InitialBlockSize;
    Block->Prev = Block->Next = NULL;
    AK_Internal__AddBlockToArena(Arena, Block);    
    Arena->CurrentBlock = Arena->FirstBlock;
    return Arena;
}

void AK_DeleteArena(ak_arena* Arena)
{
    ak_memory_block* Block = Arena->FirstBlock->Next;
    while(Block)
    {
        ak_memory_block* BlockToDelete = Block;
        Block = Block->Next;
        AK_Free(BlockToDelete);
    }    
    
    AK_Free(Arena);
    Arena = NULL;       
}

global ak_arena* AK_Internal__Global_Arena;
ak_arena* AK_GetGlobalArena()
{
    AK_Assert(AK_Internal__Global_Arena, "Global arena has not be set. Please call AK_SetGlobalArena() first before AK_GetGlobalArena()");
    return AK_Internal__Global_Arena;
}

void AK_SetGlobalArena(ak_arena* Arena)
{
    AK_Internal__Global_Arena = Arena;
}