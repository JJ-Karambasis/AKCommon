#ifndef AK_PLATFORM_H
#define AK_PLATFORM_H

enum platform_file_attributes
{
    PLATFORM_FILE_ATTRIBUTES_READ,
    PLATFORM_FILE_ATTRIBUTES_WRITE
};

global const char* __Global__Platform_Internal_ErrorMessage;

inline b32 Platform_Error(const char* ErrorMessage)
{
    __Global__Platform_Internal_ErrorMessage = ErrorMessage;
    return false;
}

inline const char* Platform_GetErrorMessage()
{
    return __Global__Platform_Internal_ErrorMessage;
}

#ifdef INVALID_FILE_SIZE
#undef INVALID_FILE_SIZE
#endif

#define INVALID_FILE_SIZE ((u64)-1)
#define NO_OFFSET ((u64)-1)

#ifdef OS_WINDOWS

typedef u64 platform_time;

struct platform_file_handle
{
    HANDLE Handle;
    platform_file_attributes Attributes;
    
    b32 IsValid()
    {
        return (Handle != NULL) && (Handle != INVALID_HANDLE_VALUE);
    }
};

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

inline platform_file_handle
FileOpen(char* Path, platform_file_attributes Attributes)
{
    DWORD DesiredAttributes = 0;
    DWORD CreationDisposition = 0;
    if(Attributes == PLATFORM_FILE_ATTRIBUTES_READ)
    {
        DesiredAttributes = GENERIC_READ;
        CreationDisposition = OPEN_EXISTING;
    }
    else if(Attributes == PLATFORM_FILE_ATTRIBUTES_WRITE)
    {
        DesiredAttributes = GENERIC_WRITE;
        CreationDisposition = CREATE_ALWAYS;
    }
    else
    {
        Platform_Error("Invalid platform file attribute");                
        return {};
    }    
    
    HANDLE Handle = CreateFile(Path, DesiredAttributes, 0, NULL, CreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
    if(Handle == INVALID_HANDLE_VALUE)
    {
        Platform_Error("Failed to open the file.");
        return {};
    }
    
    platform_file_handle Result = {};
    Result.Handle = Handle;
    Result.Attributes = Attributes;
    return Result;
}

inline void
FileClose(platform_file_handle* Handle)
{
    ASSERT(Handle->IsValid());
    CloseHandle(Handle->Handle);
    *Handle = {};
}

inline u64 
FileGetSize(platform_file_handle* Handle)
{
    ASSERT(Handle->IsValid() && (Handle->Attributes == PLATFORM_FILE_ATTRIBUTES_READ));
    
    LARGE_INTEGER Result;
    if(!GetFileSizeEx(Handle->Handle, &Result))
    {
        Platform_Error("Failed to get file size.");
        return INVALID_FILE_SIZE;    
    }
    return Result.QuadPart;
}

inline b32
FileRead(platform_file_handle* Handle, void* Data, u32 ReadSize, u64 Offset)
{
    ASSERT(Handle->IsValid() && (Handle->Attributes == PLATFORM_FILE_ATTRIBUTES_READ));
    
    OVERLAPPED* OffsetPointer = NULL;
    OVERLAPPED Offsets = {};
    if(Offset != NO_OFFSET)
    {
        Offsets.Offset = (DWORD)(Offset & 0xFFFFFFFF);
        Offsets.OffsetHigh = (DWORD)((Offset >> 32) & 0xFFFFFFFF);
        OffsetPointer = &Offsets;
    }
    
    DWORD BytesRead;
    if(ReadFile(Handle->Handle, Data, ReadSize, &BytesRead, OffsetPointer) && (BytesRead == ReadSize))
        return true;
    
    Platform_Error("Failed to read the file.");    
    return false;
}

inline b32
FileWrite(platform_file_handle* Handle, void* Data, u32 WriteSize, u64 Offset)
{
    ASSERT(Handle->IsValid() && (Handle->Attributes == PLATFORM_FILE_ATTRIBUTES_WRITE));
    
    OVERLAPPED* OffsetPointer = NULL;
    OVERLAPPED Offsets = {};
    if(Offset != NO_OFFSET)
    {
        Offsets.Offset = (DWORD)(Offset & 0xFFFFFFFF);
        Offsets.OffsetHigh = (DWORD)((Offset >> 32) & 0xFFFFFFFF);
        OffsetPointer = &Offsets;
    }
    
    DWORD BytesWritten;
    if(WriteFile(Handle->Handle, Data, WriteSize, &BytesWritten, OffsetPointer) && (BytesWritten == WriteSize))
        return true;
    
    Platform_Error("Failed to write the file.");
    return false;
}

global b32 _Internal_Global_InitFrequency_;
global LARGE_INTEGER _Internal_Global_Frequency_;

inline platform_time WallClock()
{
    LARGE_INTEGER Result;
    QueryPerformanceCounter(&Result);
    return Result.QuadPart;
}

inline f64 GetElapsedTime(platform_time End, platform_time Start)
{
    if(!_Internal_Global_InitFrequency_) { QueryPerformanceFrequency(&_Internal_Global_Frequency_); _Internal_Global_InitFrequency_ = true; }    
    f64 Result = ((f64)(End-Start))/((f64)_Internal_Global_Frequency_.QuadPart);
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

inline buffer 
ReadEntireFile(char* Path)
{
    platform_file_handle File = FileOpen(Path, PLATFORM_FILE_ATTRIBUTES_READ);
    if(!File.IsValid())
        return {};
    
    u32 FileSize = SafeU32(FileGetSize(&File));
    void* Data = AllocateMemory(FileSize);    
    FileRead(&File, Data, FileSize, NO_OFFSET);
    
    buffer Result;
    Result.Data = (u8*)Data;
    Result.Size = (ptr)FileSize;
    
    FileClose(&File);
    return Result;    
}

inline buffer 
ReadEntireFile(string Path)
{
    return ReadEntireFile(Path.Data);
}

inline b32
WriteEntireFile(char* Path, void* Data, u32 DataSize)
{
    platform_file_handle File = FileOpen(Path, PLATFORM_FILE_ATTRIBUTES_WRITE);
    if(!File.IsValid())
        return false;
    
    FileWrite(&File, Data, DataSize, NO_OFFSET);
    FileClose(&File);
    return true;
}

inline b32
WriteEntireFile(string Path, void* Data, u32 DataSize)
{
    return WriteEntireFile(Path.Data, Data, DataSize);
}

inline void FreeFileMemory(buffer* Buffer)
{
    if(Buffer->Data)
        FreeMemory(Buffer->Data);
}

inline platform_file_handle
FileOpen(string Path, platform_file_attributes Attributes)
{
    return FileOpen(Path.Data, Attributes);
}

#endif