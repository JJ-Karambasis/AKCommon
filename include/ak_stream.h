#ifndef AK_STREAM_H
#define AK_STREAM_H

struct ak_stream
{
    ak_u8* Data;
    ak_u32 Length;
    ak_u32 At;
    
    template <typename type> type* Peek();
    void Consume(ak_u32 Size);
    template <typename type> type* PeekConsume();
    template <typename type> type* PeekConsume(ak_u32 Count);
    void* PeekConsume(ak_u32 Size);
    template <typename type> type Copy();
    template <typename type> type CopyConsume();
    
    void SetOffsetFromEnd(ak_u32 Count);
    void SetOffset(ak_u32 Count);
};

ak_stream AK_BeginStream(ak_u8* Data, ak_u32 Length);
ak_stream AK_BeginStream(ak_buffer Buffer);

#endif
