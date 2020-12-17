#ifndef AK_MEMORY_H
#define AK_MEMORY_H

struct ak_buffer
{
    ak_u8* Data;
    ak_u64 Size;
    
    ak_bool IsValid();
};

struct ak_stream
{
    ak_u8* Start;
    ak_u8* Current;
    ak_u8* End;
    
    ak_u8* Read(ak_uaddr Size);
    template <typename type> type* Read();            
    template <typename type> type* ReadArray(ak_u32 Count);
};

enum ak_arena_clear_flags
{
    AK_ARENA_CLEAR_FLAGS_CLEAR,
    AK_ARENA_CLEAR_FLAGS_NOCLEAR
};

struct ak_temp_arena
{
    struct ak_arena* Arena;
    struct ak_memory_block* MemoryBlock;
    ak_u8* BlockMarker;
};

struct ak_memory_block
{
    ak_u8* Start;
    ak_u8* Current;
    ak_u8* End;
    
    ak_memory_block* Prev;
    ak_memory_block* Next;
};

struct ak_arena
{
    ak_uaddr InitialBlockSize;
    ak_memory_block* FirstBlock;
    ak_memory_block* LastBlock;
    ak_memory_block* CurrentBlock;
    ak_u32 TemporaryArenas;
    
    void Clear();
    void* Push(ak_uaddr Size, ak_arena_clear_flags ClearFlags, ak_i32 Alignment);
    void* Push(ak_uaddr Size, ak_i32 Alignment);
    void* Push(ak_uaddr Size, ak_arena_clear_flags ClearFlags);    
    void* Push(ak_uaddr Size);
    
    template <typename type> type* Push(ak_arena_clear_flags ClearFlags, ak_i32 Alignment);
    template <typename type> type* Push(ak_i32 Alignment);
    template <typename type> type* Push(ak_arena_clear_flags ClearFlags);
    template <typename type> type* Push();
    
    template <typename type> type* PushArray(ak_u32 Count, ak_arena_clear_flags ClearFlags, ak_i32 Alignment);
    template <typename type> type* PushArray(ak_u32 Count, ak_i32 Alignment);
    template <typename type> type* PushArray(ak_u32 Count, ak_arena_clear_flags ClearFlags);
    template <typename type> type* PushArray(ak_u32 Count);
    
    ak_temp_arena BeginTemp();
    void EndTemp(ak_temp_arena* TempArena);
    ak_bool TempCheck();
    
    ak_uaddr GetTotalUsed();
};

void* AK_MemoryCopy(void* Dst, void* Src, ak_uaddr Size);
void* AK_MemoryCopy(void* Dst, const void* Src, ak_uaddr Size);
void AK_MemoryClear(void* Memory, ak_uaddr Size);
template <typename type> type* AK_MemorySet(type* Memory, type Data, ak_uaddr Count);
template <typename type> type* AK_CopyArray(type* Dst, type* Src, ak_u32 Count);
template <typename type> type* AK_CopyArray(type* Dst, const type* Src, ak_u32 Count);
template <typename type> void AK_ClearArray(type* Dst, ak_u32 Count);
ak_arena* AK_CreateArena(ak_uaddr InitialBlockSIze = AK_Megabyte(1));
void AK_DeleteArena(ak_arena* Arena);
ak_arena* AK_GetGlobalArena();
void AK_SetGlobalArena(ak_arena* Arena);
ak_stream AK_CreateStream(ak_u8* Stream, ak_uaddr Size);

#endif