#ifndef AK_STRING_STREAM
#define AK_STRING_STREAM

struct string_stream
{
    arena Storage;
    ptr Capacity;
    ptr Size;
    char* Data;       
    
    inline void CheckStringStreamSize()
    {
        b32 ShouldResize = !Capacity || (Size >= Capacity-1024);
        
        if(ShouldResize)
        {
            ptr NewCapacity = Capacity*2;
            if(!NewCapacity) 
                NewCapacity = 2048;
            
            char* Temp = PushArray(&Storage, NewCapacity, char, Clear, 0);
            CopyMemory(Temp, Data, Capacity);
            Data = Temp;
            Capacity = NewCapacity;
        }
    }
    
    inline void __Internal__Write__(char* Format, va_list Args)
    {
        CheckStringStreamSize();
        Size += vsprintf(Data+Size, Format, Args);
    }
    
    inline void Write(char* Format, ...)
    {
        va_list Args;
        va_start(Args, Format);
        __Internal__Write__(Format, Args);
        va_end(Args);
    }
    
    inline void WriteChar(char Value)
    {
        CheckStringStreamSize();
        Data[Size++] = Value;
    }
    
    inline void NewLine()
    {
        WriteChar('\n');
    }
    
    inline void WriteLine(char* Format, ...)
    {
        va_list Args;
        va_start(Args, Format);
        __Internal__Write__(Format, Args);
        va_end(Args);
        NewLine();
    }
    
    inline string GetString()
    {
        string Result = LiteralString(Data, Size);
        return Result;
    }    
};

inline void CreateStringStream(string_stream* Stream, ptr BlockSize)
{    
    Stream->Storage = CreateArena(BlockSize);    
}

inline string_stream CreateStringStream(ptr BlockSize)
{
    string_stream Result = {};
    CreateStringStream(&Result, BlockSize);
    return Result;
}

inline void DeleteStringStream(string_stream* Stream)
{
    DeleteArena(&Stream->Storage);
    *Stream = {};
}

#endif