#ifndef AK_STRING_BUILDER_H
#define AK_STRING_BUILDER_H

struct ak_string_builder
{
    ak_arena* Arena;    
    
    void Write(ak_char* Format, ...);
    void WriteChar(ak_char Character);
    void WriteLine(ak_char* Format, ...);
    void NewLine();
        
    ak_string PushString(ak_arena* DstArena);
    void Clear();
    void ReleaseMemory();
};

#endif