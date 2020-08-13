#ifndef AK_PLATFORM_H
#define AK_PLATFORM_H

#ifdef OS_WINDOWS

inline void* 
AllocateMemory(ptr Size)
{
    void* Memory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
    return Memory;
}

inline void 
FreeMemory(void* Memory)
{
    if(Memory)    
        HeapFree(GetProcessHeap(), 0, Memory);    
}

inline string 
GetProgramPathWithName(arena* Arena)
{
    char EXEPathWithName[MAX_PATH+1];
    ptr Size = GetModuleFileName(NULL, EXEPathWithName, MAX_PATH+1);
    string Result = PushLiteralString(EXEPathWithName, Size, Arena);
    return Result;
}

inline b32
FileExists(char* Path)
{
    DWORD Attrib = GetFileAttributes(Path);
    b32 Result = (Attrib != INVALID_FILE_ATTRIBUTES) && !(Attrib & FILE_ATTRIBUTE_DIRECTORY);
    return Result;
}

#endif

inline string 
GetProgramPath(arena* Arena)
{
    string Path = GetProgramPathWithName(Arena);
    return GetFilePath(Path);
}

inline b32
FileRemove(char* Path)
{
    b32 Result = remove(Path) == 0;
    return Result;
}

inline b32
FileRename(char* OldName, char* NewName)
{
    b32 Result = rename(OldName, NewName) == 0;
    return Result;
}

inline b32
FileExists(string Path)
{
    b32 Result = FileExists(Path.Data);
    return Result;
}

inline b32
FileRemove(string Path)
{
    b32 Result = FileRemove(Path.Data);
    return Result;
}

inline b32
FileRename(string OldName, string NewName)
{
    b32 Result = FileRename(OldName.Data, NewName.Data);
    return Result;
}

#endif