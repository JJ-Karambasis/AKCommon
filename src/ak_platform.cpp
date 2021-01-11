#ifdef AK_WINDOWS

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Shell32.lib")

struct ak_file_handle
{
    HANDLE Handle;
    ak_file_attributes Attributes;
};

LRESULT CALLBACK 
AK_Internal__PlatformWindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;
    
    switch(Message)
    {        
        case WM_CLOSE:
        {
            PostQuitMessage(0);
        } break;
        
        default:
        {
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;                
    }
    
    return Result;
}

void* AK_Allocate(ak_uaddr Size)
{
    void* Result = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
    return Result;
}

void  AK_Free(void* Memory)
{
    if(Memory) 
        HeapFree(GetProcessHeap(), 0, Memory);
}

void* AK_AllocateVirtualMemory(ak_uaddr Size)
{
    void* Result = VirtualAlloc(NULL, Size, MEM_RESERVE, PAGE_NOACCESS);
    return Result;
}

void* AK_CommitVirtualMemory(void* Address, ak_uaddr Size)
{
    void* Result = VirtualAlloc(Address, Size, MEM_COMMIT, PAGE_READWRITE);
    return Result;
}

void  AK_DecommitVirtualMemory(void* Address, ak_uaddr Size)
{
    if(Address && Size)
        VirtualFree(Address, Size, MEM_DECOMMIT);
}

void  AK_FreeVirtualMemory(void* Address, ak_uaddr Size)
{
    if(Address && Size)
        VirtualFree(Address, 0, MEM_RELEASE);
}

ak_memory_info AK_GetMemoryInfo()
{
    SYSTEM_INFO SysInfo;
    GetSystemInfo(&SysInfo);
    
    ak_uaddr MemoryInKilo;
    GetPhysicallyInstalledSystemMemory(&MemoryInKilo);
    
    ak_memory_info MemoryInfo = {};
    MemoryInfo.TotalMemory = MemoryInKilo*1024;
    MemoryInfo.PageSize = SysInfo.dwPageSize;
    return MemoryInfo;
}

ak_bool AK_CreateDirectory(ak_char* Path)
{
    return CreateDirectory(Path, NULL);
}

ak_file_handle* AK_OpenFile(ak_char* Path, ak_file_attributes FileAttributes)
{    
    DWORD DesiredAttributes = 0;
    DWORD CreationDisposition = 0;
    if(FileAttributes == AK_FILE_ATTRIBUTES_READ)
    {
        DesiredAttributes = GENERIC_READ;
        CreationDisposition = OPEN_EXISTING;
    }
    else if(FileAttributes == AK_FILE_ATTRIBUTES_WRITE)
    {
        DesiredAttributes = GENERIC_WRITE;
        CreationDisposition = CREATE_ALWAYS;
    }
    AK_INVALID_ELSE;
    
    HANDLE Handle = CreateFile(Path, DesiredAttributes, 0, NULL, CreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
    if(Handle == INVALID_HANDLE_VALUE)
        return 0;
    
    ak_file_handle* File = (ak_file_handle*)AK_Allocate(sizeof(ak_file_handle));
    File->Handle = Handle;
    File->Attributes = FileAttributes;    
    return File;
}

ak_file_handle* AK_OpenFile(ak_string Path, ak_file_attributes FileAttributes)
{
    return AK_OpenFile(Path.Data, FileAttributes);
}

void AK_CloseFile(ak_file_handle* File)
{        
    if(File)
    {
        CloseHandle(File->Handle);
        AK_Free(File);        
        File->Handle = NULL;
    }        
}

ak_u64 AK_GetFileSize(ak_file_handle* File)
{    
    if(!File)
        return (ak_u64)-1;
    
    if(File->Attributes != AK_FILE_ATTRIBUTES_READ)
        return (ak_u64)-1;
    
    LARGE_INTEGER Result;
    if(!GetFileSizeEx(File->Handle, &Result))
        return (ak_u64)-1;
    
    return Result.QuadPart;        
}

ak_u64 AK_GetFilePointer(ak_file_handle* File)
{    
    if(!File)
        return (ak_u64)-1;
    
    LONG High = 0;
    DWORD Low = SetFilePointer(File->Handle, 0, &High, FILE_CURRENT);
    if(Low == INVALID_SET_FILE_POINTER)
        return (ak_u64)-1;
    
    return ((ak_u64)High << 32) | Low;
}

ak_bool AK_ReadFile(ak_file_handle* File, void* Data, ak_u32 ReadSize, ak_u64 Offset)
{    
    if(!File)
        return false;
    
    if(File->Attributes != AK_FILE_ATTRIBUTES_READ)
        return false;
    
    OVERLAPPED* OffsetPointer = NULL;
    OVERLAPPED Offsets = {};
    if(Offset != AK_NO_OFFSET)
    {
        Offsets.Offset = (DWORD)(Offset & 0xFFFFFFFF);
        Offsets.OffsetHigh = (DWORD)((Offset >> 32) & 0xFFFFFFFF);
        OffsetPointer = &Offsets;
    }
    
    DWORD BytesRead;
    if(!ReadFile(File->Handle, Data, ReadSize, &BytesRead, OffsetPointer))
        return false;
    
    if(BytesRead != ReadSize)
        return false;
    
    return true;
}

ak_bool AK_WriteFile(ak_file_handle* File, void* Data, ak_u32 WriteSize, ak_u64 Offset)
{    
    if(!File)
        return false;
    
    if(File->Attributes != AK_FILE_ATTRIBUTES_WRITE)
        return false;
    
    OVERLAPPED* OffsetPointer = NULL;
    OVERLAPPED Offsets = {};
    if(Offset != AK_NO_OFFSET)
    {
        Offsets.Offset = (DWORD)(Offset & 0xFFFFFFFF);
        Offsets.OffsetHigh = (DWORD)((Offset >> 32) & 0xFFFFFFFF);
        OffsetPointer = &Offsets;
    }
    
    DWORD BytesWritten;
    if(!WriteFile(File->Handle, Data, WriteSize, &BytesWritten, OffsetPointer))
        return false;
    
    if(BytesWritten != WriteSize)
        return false;
    
    return true;
}

void AK_MessageBoxOk(ak_char* Title, ak_char* Message)
{
    MessageBox(NULL, Message, Title, MB_OK);
}

ak_bool AK_MessageBoxYesNo(ak_char* Title, ak_char* Message)
{
    int Code = MessageBox(NULL, Message, Title, MB_YESNO);
    return Code == IDYES;
}

ak_bool AK_FileExists(ak_char* Path)
{
    DWORD Attrib = GetFileAttributes(Path);
    ak_bool Result = (Attrib != INVALID_FILE_ATTRIBUTES) && !(Attrib & FILE_ATTRIBUTE_DIRECTORY);
    return Result;
}

ak_bool AK_DirectoryExists(ak_char* Path)
{
    DWORD Attrib = GetFileAttributes(Path);
    ak_bool Result = (Attrib != INVALID_FILE_ATTRIBUTES) && (Attrib & FILE_ATTRIBUTE_DIRECTORY);
    return Result;
}

ak_bool AK_FileRemove(ak_char* Path)
{
    ak_bool Result = DeleteFile(Path);
    return Result;
}

ak_bool AK_DirectoryRemove(ak_char* Path)
{
    ak_bool Result = RemoveDirectory(Path);
    return Result;
}


ak_bool AK_DirectoryRemoveRecursively(ak_char* Path)
{
    SHFILEOPSTRUCT FileOp = 
    {
        NULL, 
        FO_DELETE, 
        Path, 
        "", 
        FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT, 
        false, 
        0, 
        ""
    };
    return SHFileOperation(&FileOp) == 0;
}


ak_bool AK_FileRename(ak_char* OldName, ak_char* NewName)
{
    ak_bool Result = MoveFile(OldName, NewName);
    return Result;
}

ak_bool AK_FileCopy(ak_char* OldFile, ak_char* NewFile)
{
    ak_bool Result = CopyFile(OldFile, NewFile, FALSE);
    return Result;
}

ak_string AK_GetExecutablePathWithName(ak_arena* Arena)
{
    ak_arena* GlobalArena = AK_GetGlobalArena();
    ak_temp_arena TempArena = GlobalArena->BeginTemp();
    
    ak_u32 Iterations = 4;
    
    DWORD ErrorCode = 0;
    DWORD InitialSize = MAX_PATH+1;
    
    ak_char* String = GlobalArena->PushArray<ak_char>(InitialSize);
    ak_u32 Size = 0;
    do
    {
        Size = GetModuleFileName(NULL, String, InitialSize);
        ErrorCode = GetLastError();
        if(ErrorCode == ERROR_INSUFFICIENT_BUFFER)
        {
            AK_MemoryClear(String, InitialSize);
            GlobalArena->PushArray<ak_char>(InitialSize);
            InitialSize *= 2;
        }        
    } while((ErrorCode == ERROR_INSUFFICIENT_BUFFER) && Iterations--);
    
    ak_string Result = AK_CreateEmptyString();
    if(ErrorCode != ERROR_INSUFFICIENT_BUFFER)
    {
        Result = AK_PushString(String, Size, Arena);
    }
    
    GlobalArena->EndTemp(&TempArena);
    return Result;
}

ak_array<ak_string> AK_GetAllFilesInDirectory(ak_string Directory, ak_arena* Arena)
{   
    ak_arena* GlobalArena = AK_GetGlobalArena();
    ak_temp_arena TempArena = GlobalArena->BeginTemp();
    
    ak_array<ak_string> Result = {};
    if(!AK_StringEndsWith(Directory, '\\') && !AK_StringEndsWith(Directory, '/'))        
        Directory = AK_StringConcat(Directory, "\\", GlobalArena);
    
    ak_string Wildcard = AK_StringConcat(Directory, '*', GlobalArena);
    
    WIN32_FIND_DATAA FindData;
    HANDLE Handle = FindFirstFile(Wildcard.Data, &FindData);
    if(Handle != INVALID_HANDLE_VALUE)
    {
        ak_bool Loop = true;
        while(Loop)
        {   
            ak_string File = AK_StringConcat(Directory, FindData.cFileName, Arena);
            Result.Add(File);            
            Loop = FindNextFile(Handle, &FindData);
        }   
        
        FindClose(Handle);
    }
    
    GlobalArena->EndTemp(&TempArena);    
    return Result;
}

inline wchar_t* 
AK_Internal__Win32ConvertToWide(ak_char* String, ak_arena* Arena)
{
    ak_i32 StringSize = (ak_i32)AK_StringLength(String)+1;
    wchar_t* Result = Arena->PushArray<wchar_t>(StringSize);
    MultiByteToWideChar(CP_ACP, 0, String, -1, Result, StringSize);
    return Result;
}

inline ak_char* 
AK_Internal__Win32ConvertToStandard(wchar_t* String, ak_arena* Arena)
{
    //CONFIRM(JJ): Do we want to actually support wide strings in string.h? If so can we remove these wide string functions 
    //from the c runtime libary?
    int StringSize = (int)wcslen(String)+1;
    ak_char* Result = Arena->PushArray<ak_char>(StringSize);
    WideCharToMultiByte(CP_ACP, 0, String, -1, Result, StringSize, NULL, NULL);
    return Result;
}

global ak_bool AK_Internal__InitFrequency;
global LARGE_INTEGER AK_Internal__Frequency;

ak_high_res_clock AK_WallClock()
{
    LARGE_INTEGER Result;
    QueryPerformanceCounter(&Result);
    return Result.QuadPart;
}

ak_f64 AK_GetElapsedTime(ak_high_res_clock End, ak_high_res_clock Start)
{
    if(!AK_Internal__InitFrequency) { QueryPerformanceFrequency(&AK_Internal__Frequency); AK_Internal__InitFrequency = true; }
    ak_f64 Result = ((ak_f64)(End-Start))/((ak_f64)AK_Internal__Frequency.QuadPart);
    return Result;
}

void AK_ConsoleLog(ak_char* Format, ...)
{
    char String[1024];
    
    va_list Args;
    va_start(Args, Format);
    vsprintf(String, Format, Args);
    va_end(Args);
    
    OutputDebugStringA(String);    
}

#define GLOBAL_INTERNAL__WINDOW_CLASS_NAME "Global_WindowClass"
global WNDCLASSEX Global_Internal__WindowClass;

ak_window* AK_CreateWindow(ak_u16 Width, ak_u16 Height, ak_char* Title)
{
    if(Global_Internal__WindowClass.cbSize == 0)
    {                
        Global_Internal__WindowClass.cbSize = sizeof(WNDCLASSEX);
        Global_Internal__WindowClass.style = CS_VREDRAW|CS_HREDRAW|CS_OWNDC;
        Global_Internal__WindowClass.lpfnWndProc = AK_Internal__PlatformWindowProc;
        Global_Internal__WindowClass.hInstance = GetModuleHandle(0);
        Global_Internal__WindowClass.lpszClassName = GLOBAL_INTERNAL__WINDOW_CLASS_NAME;    
        if(!RegisterClassEx(&Global_Internal__WindowClass))    
            return NULL;
    }
    
    DWORD ExStyle = 0;
    DWORD Style = WS_OVERLAPPEDWINDOW|WS_VISIBLE;
    
    RECT WindowRect = {0, 0, (LONG)Width, (LONG)Height};
    AdjustWindowRectEx(&WindowRect, Style, FALSE, ExStyle);    
    
    HWND Window = CreateWindowEx(ExStyle, GLOBAL_INTERNAL__WINDOW_CLASS_NAME, Title, Style, 
                                 CW_USEDEFAULT, CW_USEDEFAULT, 
                                 WindowRect.right-WindowRect.left,
                                 WindowRect.bottom-WindowRect.top,
                                 0, 0, GetModuleHandle(0), NULL);
    if(!Window)            
        return NULL;        
    
    return (ak_window*)Window;
}

void AK_GetWindowResolution(ak_window* PlatformWindow, ak_u16* OutWidth, ak_u16* OutHeight)
{
    HWND Window = (HWND)PlatformWindow;
    
    RECT Rect;
    if(GetClientRect(Window, &Rect))    
    {
        if(OutWidth) *OutWidth = (ak_u16)(Rect.right-Rect.left);
        if(OutHeight) *OutHeight = (ak_u16)(Rect.bottom-Rect.top);
    }    
}

HWND AK_GetPlatformWindow(ak_window* Window)
{
    if(Window)
        return (HWND)Window;
    return NULL;
}

#endif

ak_buffer AK_ReadEntireFile(ak_char* Path, ak_arena* Arena)
{
    ak_file_handle* FileHandle = AK_OpenFile(Path, AK_FILE_ATTRIBUTES_READ);
    if(!FileHandle)
        return {};
    
    ak_u64 FileSize64 = AK_GetFileSize(FileHandle);
    if(FileSize64 == (ak_u64)-1)
    {
        AK_CloseFile(FileHandle);
        return {};
    }
    
    ak_u32 FileSize = AK_SafeU32(FileSize64);
    ak_buffer Result;
    Result.Size = FileSize;
    Result.Data = (ak_u8*)Arena->Push(FileSize);
    ak_bool ReadResult = AK_ReadFile(FileHandle, Result.Data, FileSize);
    
    AK_CloseFile(FileHandle);
    if(!ReadResult)
        return {};    
    return Result;
}

ak_buffer AK_ReadEntireFile(ak_string Path, ak_arena* Arena)
{
    return AK_ReadEntireFile(Path.Data, Arena);
}

ak_bool AK_WriteEntireFile(ak_char* Path, void* Data, ak_u32 Size)
{
    ak_file_handle* FileHandle = AK_OpenFile(Path, AK_FILE_ATTRIBUTES_WRITE);
    if(!FileHandle)
        return false;
    
    ak_bool Result = AK_WriteFile(FileHandle, Data, Size, AK_NO_OFFSET);
    AK_CloseFile(FileHandle);
    return Result;    
}

ak_bool AK_WriteEntireFile(ak_string Path, void* Data, ak_u32 Size)
{
    return AK_WriteEntireFile(Path.Data, Data, Size);
}

ak_bool AK_FileExists(ak_string Path)
{
    return AK_FileExists(Path.Data);
}

ak_bool AK_DirectoryExists(ak_string Path)
{
    return AK_DirectoryExists(Path.Data);
}

ak_bool AK_FileRemove(ak_string Path)
{
    return AK_FileRemove(Path.Data);
}

ak_bool AK_FileRename(ak_string OldName, ak_string NewName)
{        
    return AK_FileRename(OldName.Data, NewName.Data);
}

ak_bool AK_FileRename(ak_string OldName, const ak_char* NewName)
{
    return AK_FileRename(OldName.Data, (ak_char*)NewName);
}

ak_string AK_GetExecutablePath(ak_arena* Arena)
{
    return AK_GetFilepath(AK_GetExecutablePathWithName(Arena));
}

ak_array<ak_string> AK_GetAllFilesInDirectory(ak_char* Directory, ak_arena* Arena)
{
    return AK_GetAllFilesInDirectory(AK_CreateString(Directory), Arena);
}

void AK_MessageBoxOk(ak_char* Title, ak_string Message)
{
    AK_MessageBoxOk(Title, Message.Data);
}

ak_bool AK_MessageBoxYesNo(ak_char* Title, ak_string Message)
{
    return AK_MessageBoxYesNo(Title, Message.Data);
}

ak_bool AK_CreateDirectory(ak_string Path)
{
    return AK_CreateDirectory(Path.Data);
}

ak_bool AK_DirectoryRemove(ak_string Path)
{
    ak_bool Result = AK_DirectoryRemove(Path.Data);
    return Result;
}

ak_bool AK_WriteFile(ak_file_handle* File, const void* Data, ak_u32 Size, ak_u64 Offset)
{
    return AK_WriteFile(File, (void*)Data, Size, Offset);
}

ak_bool AK_DirectoryRemoveRecursively(ak_string Path)
{
    return AK_DirectoryRemoveRecursively(Path.Data);
}

ak_bool AK_FileCopy(ak_string OldFile, ak_string NewFile)
{
    return AK_FileCopy(OldFile.Data, NewFile.Data);
}