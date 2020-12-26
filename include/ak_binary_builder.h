#ifndef AK_BINARY_BUILDER_H
#define AK_BINARY_BUILDER_H

struct ak_binary_builder
{
    ak_arena* Arena;
    
    template <typename type> type* Allocate();
    template <typename type> ak_u32 Write(type Type);
    void WriteString(ak_char* Format, ...);
    void WriteString(const ak_char* Format, ...);
    
    ak_buffer PushBuffer(ak_arena* DstArena);
    void Clear();
    void ReleaseMemory();
};

#endif
