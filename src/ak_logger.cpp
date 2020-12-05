void AK__Internal_LogInfo(ak_logger* Logger, ak_char* Format, ...)
{    
    ak_arena* Arena = AK_GetGlobalArena();
    ak_temp_arena TempArena = Arena->BeginTemp();
    
    va_list List;
    va_start(List, Format);
    ak_string MessageString = AK_FormatString(Arena, Format, List);
    va_end(List);
    
    Logger->WriteLine("INFO - Message: %s", MessageString.Data);
    
    Arena->EndTemp(&TempArena);
}

void AK__Internal_LogWarning(ak_logger* Logger, ak_char* Format, ...)
{    
    ak_arena* Arena = AK_GetGlobalArena();
    ak_temp_arena TempArena = Arena->BeginTemp();
    
    va_list List;
    va_start(List, Format);
    ak_string MessageString = AK_FormatString(Arena, Format, List);
    va_end(List);
    
    Logger->WriteLine("WARNING - Message: %s", MessageString.Data);
    
    Arena->EndTemp(&TempArena);
}

void AK__Internal_LogError(ak_logger* Logger, ak_char* Filename, ak_u32 LineNumber, ak_char* Function, ak_char* Format, ...)
{    
    ak_arena* Arena = AK_GetGlobalArena();
    ak_temp_arena TempArena = Arena->BeginTemp();
    
    va_list List;
    va_start(List, Format);
    ak_string MessageString = AK_FormatString(Arena, Format, List);
    va_end(List);
    
    Logger->WriteLine("ERROR - Message: %s\n\tFile: %s Function: %s Line: %d", MessageString.Data, Filename, Function, LineNumber);
    
    Arena->EndTemp(&TempArena);    
}

global ak_arena* AK_Internal__AssertArena; 
void AK__Internal_Assert(ak_char* Filename, ak_u32 LineNumber, ak_char* Function, ak_char* Format, ...)
{
    ak_char* HeaderFormat = "Assertion failed!\nFile: %s\nFunction: %s\nLine Number: %d\nMessage: %s";
    
    if(!AK_Internal__AssertArena)
        AK_Internal__AssertArena = AK_CreateArena();
    
    ak_temp_arena TempArena = AK_Internal__AssertArena->BeginTemp();
    
    va_list List;
    va_start(List, Format);
    ak_string MessageString = AK_FormatString(AK_Internal__AssertArena, Format, List);
    va_end(List);
    
    ak_string Text = AK_FormatString(AK_Internal__AssertArena, HeaderFormat, Filename, Function, LineNumber, MessageString.Data);    
    AK_MessageBoxOk("Assertion", Text.Data);
    
    AK_Internal__AssertArena->EndTemp(&TempArena);
}

ak_bool AK_OutputToFile(ak_logger* Logger, ak_char* Path)
{
    ak_arena* GlobalArena = AK_GetGlobalArena();
    ak_temp_arena TempArena = GlobalArena->BeginTemp();    
    ak_string String = Logger->PushString(GlobalArena);
    ak_bool Result = AK_WriteEntireFile(Path, String.Data, String.Length);    
    GlobalArena->EndTemp(&TempArena);        
    return Result;
}

ak_bool AK_OutputToFile(ak_logger* Logger, ak_string Path)
{
    return AK_OutputToFile(Logger, Path.Data);
}