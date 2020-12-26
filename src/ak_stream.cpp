ak_stream AK_BeginStream(ak_u8* Data, ak_u32 Length)
{
    ak_stream Result = {};
    Result.Data = Data;
    Result.Length = Length;
    return Result;
}

ak_stream AK_BeginStream(ak_buffer Buffer)
{
    return AK_BeginStream(Buffer.Data, AK_SafeU32(Buffer.Size));
}

template <typename type>
type* ak_stream::Peek()
{
    return (type*)(Data+At);
}

void ak_stream::Consume(ak_u32 Size)
{
    AK_Assert((At + Size) <= Length, "Stream overflowed");
    At += Size;
}

template <typename type>
type* ak_stream::PeekConsume()
{
    type* Result = Peek<type>();
    Consume(sizeof(type));
    return Result;
}

template <typename type>
type* ak_stream::PeekConsume(ak_u32 Count)
{
    type* Result = Peek<type>();
    Consume(Count*sizeof(type));
    return Result;
}

void* ak_stream::PeekConsume(ak_u32 Size)
{
    void* Result = Peek<void>();
    Consume(Size);
    return Result;
}

template <typename type>
type ak_stream::Copy()
{
    return *(type*)(Data+At);
}

template <typename type>
type ak_stream::CopyConsume()
{
    type Result = Copy<type>();
    Consume(sizeof(type));
    return Result;
}

void ak_stream::SetOffsetFromEnd(ak_u32 Offset)
{
    At = Length-1;
    AK_Assert(At-Offset > 0, "Stream underflow");
    At -= Offset;
}

void ak_stream::SetOffset(ak_u32 Offset)
{
    AK_Assert(Offset < Length, "Stream overflow");
    At = Offset;
}