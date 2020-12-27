#ifndef AK_PLATFORM_H
#define AK_PLATFORM_H

#undef AK_NO_OFFSET
#define AK_NO_OFFSET ((ak_u64)-1)

#ifdef AK_WINDOWS
typedef ak_u64 ak_high_res_clock;
#endif

enum ak_file_attributes
{
    AK_FILE_ATTRIBUTES_READ,
    AK_FILE_ATTRIBUTES_WRITE
};

#define AK_INVALID_FILE_HANDLE 0
struct ak_file_handle;

struct ak_memory_info
{
    ak_uaddr TotalMemory;    
    ak_uaddr PageSize;
};

struct ak_window;

ak_string AK_PlatformGetErrorMessage();
void* AK_Allocate(ak_uaddr Size);
void  AK_Free(void* Memory);
void* AK_AllocateVirtualMemory(ak_uaddr Size);
void* AK_CommitVirtualMemory(void* Address, ak_uaddr Size);
void  AK_DecommitVirtualMemory(void* Address, ak_uaddr Size);
void  AK_FreeVirtualMemory(void* Address, ak_uaddr Size);
ak_memory_info AK_GetMemoryInfo();
void AK_MessageBoxOk(ak_char* Title, ak_char* Message);
void AK_MessageBoxOk(ak_char* Title, ak_string Message);
ak_bool AK_MessageBoxYesNo(ak_char* Title, ak_char* Message);
ak_bool AK_MessageBoxYesNo(ak_char* Title, ak_string Message);
ak_string AK_GetExecutablePathWithName(ak_arena* Arena);
ak_string AK_GetExecutablePath(ak_arena* Arena);
ak_bool AK_FileExists(ak_string Path);
ak_bool AK_FileExists(ak_char* Path);
ak_bool AK_DirectoryExists(ak_char* Path);
ak_bool AK_DirectoryExists(ak_string Path);
ak_bool AK_FileRemove(ak_string Path);
ak_bool AK_FileRemove(ak_char* Path);
ak_bool AK_DirectoryRemove(ak_string Path);
ak_bool AK_DirectoryRemove(ak_char* Path);
ak_bool AK_DirectoryRemoveRecursively(ak_string Path);
ak_bool AK_DirectoryRemoveRecursively(ak_char* Path);
ak_bool AK_FileRename(ak_string OldName, ak_string NewName);
ak_bool AK_FileRename(ak_string OldName, const ak_char* NewName);
ak_bool AK_FileRename(ak_char* OldName, ak_char* NewName);
ak_bool AK_CreateDirectory(ak_string Path);
ak_bool AK_CreateDirectory(ak_char* Path);
ak_file_handle* AK_OpenFile(ak_string Path, ak_file_attributes FileAttributes);
ak_file_handle* AK_OpenFile(ak_char* Path, ak_file_attributes FileAttributes);
void AK_CloseFile(ak_file_handle* File);
ak_u64 AK_GetFileSize(ak_file_handle File);
ak_bool AK_ReadFile(ak_file_handle* File, void* Data, ak_u32 Size, ak_u64 Offset=AK_NO_OFFSET);
ak_bool AK_WriteFile(ak_file_handle* File, void* Data, ak_u32 Size, ak_u64 Offset=AK_NO_OFFSET);
ak_bool AK_WriteFile(ak_file_handle* File, const void* Data, ak_u32 Size, ak_u64 Offset=AK_NO_OFFSET);
ak_u64 AK_GetFilePointer(ak_file_handle* File);
ak_array<ak_string> AK_GetAllFilesInDirectory(ak_char* Directory, ak_arena* Arena);
ak_array<ak_string> AK_GetAllFilesInDirectory(ak_string Directory, ak_arena* Arena);
ak_string AK_OpenFileDialog(ak_char* Extension);
ak_string AK_OpenFileDialog(ak_string Extension);
ak_string AK_SaveFileDialog(ak_char* Extension);
ak_string AK_SaveFileDialog(ak_string Extension);
ak_buffer AK_ReadEntireFile(ak_string Path, ak_arena* Arena);
ak_buffer AK_ReadEntireFile(ak_char* Path, ak_arena* Arena);
ak_bool AK_WriteEntireFile(ak_string Path, void* Data, ak_u32 DataSize);
ak_bool AK_WriteEntireFile(ak_char* Path, void* Data, ak_u32 DataSize);
ak_high_res_clock AK_WallClock();
ak_f64 AK_GetElapsedTime(ak_high_res_clock End, ak_high_res_clock Start);
void AK_ConsoleLog(ak_char* Format, ...);

ak_window* AK_CreateWindow(ak_u16 Width, ak_u16 Height, ak_char* Title);
void AK_GetWindowResolution(ak_window* PlatformWindow, ak_u16* OutWidth, ak_u16* OutHeight);


#ifdef AK_WINDOWS
HWND AK_GetPlatformWindow(ak_window* Window);
#endif

#endif