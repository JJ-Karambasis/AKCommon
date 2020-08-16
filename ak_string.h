#ifndef STRING_H
#define STRING_H

struct string
{
    char* Data;
    ptr Length;
    
    inline char operator[](ptr Index)
    {
        return Data[Index];
    }        
};

struct string_storage
{
    ptr Capacity;
    string String;    
};

string_storage AllocateStringStorage(arena* Arena, ptr Capacity)
{
    string_storage Result = {};
    Result.String.Data = PushArray(Arena, Capacity, char, Clear, 0);
    Result.Capacity = Capacity;
    return Result;
}

void CopyToStorage(string_storage* Storage, string String)
{
    ASSERT(Storage->Capacity > String.Length);
    CopyMemory(Storage->String.Data, String.Data, String.Length);
    Storage->String.Length = String.Length;    
}

inline string InvalidString()
{
    string Result = {};
    return Result;
}

inline b32 IsInvalidString(string String)
{
    b32 Result = !String.Data || !String.Length;
    return Result;
}

ptr LiteralStringLength(char* Data)
{
    ptr Result = 0;
    while(*Data++)
        Result++;
    return Result;
}

ptr LiteralStringLength(const char* Data)
{
    ptr Result = LiteralStringLength((char*)Data);
    return Result;
}

inline b32 StringEquals(char* A, ptr ALength, char* B, ptr BLength)
{
    if(ALength != BLength)
        return false;
    
    for(u32 Index = 0; Index < ALength; Index++)
    {
        if(A[Index] != B[Index])
            return false;
    }    
    return true;
}

inline b32 StringEquals(char* A, char* B)
{
    b32 Result = StringEquals(A, LiteralStringLength(A), B, LiteralStringLength(B));
    return Result;
}

inline b32 StringEquals(char* A, const char* B)
{
    b32 Result = StringEquals(A, LiteralStringLength(A), (char*)B, LiteralStringLength(B));
    return Result;
}

inline b32 StringEquals(char* A, char* B, ptr BLength)
{
    b32 Result = StringEquals(A, LiteralStringLength(A), B, BLength);
    return Result;
}

inline b32 StringEquals(const char* A, const char* B)
{
    b32 Result = StringEquals((char*)A, LiteralStringLength(A), (char*)B, LiteralStringLength(B));
    return Result;
}

inline b32 StringEquals(string A, char* B)
{
    b32 Result = StringEquals(A.Data, A.Length, B, LiteralStringLength(B));
    return Result;
}

inline b32 EndsWith(char* String, ptr StringLength, char* EndString)
{
    ptr EndStringLength = LiteralStringLength(EndString);
    ptr Difference = StringLength-EndStringLength;
        
    for(ptr AIndex = Difference, BIndex = 0; AIndex < StringLength; AIndex++, BIndex++)
    {
        if(!EndString[BIndex])
            break;
        
        if(String[AIndex] != EndString[BIndex])
            return false;                
    }
    
    return true;
}

inline b32 EndsWith(char* String, const char* EndString)
{
    return EndsWith(String, LiteralStringLength(String), (char*)EndString);
}

inline b32 EndsWith(const char* String, const char* EndString)
{
    return EndsWith((char*)String, LiteralStringLength(String), (char*)EndString);
}

inline b32 BeginsWith(char* String, ptr StringLength, char* BeginString)
{
    for(u32 StringIndex = 0; StringIndex < StringLength; StringIndex++)
    {   
        if(!BeginString[StringIndex])
            break;
        
        if(String[StringIndex] != BeginString[StringIndex])
        {
            return false;
        }
    }    
    return true;
}

inline b32 BeginsWith(char* String, char* BeginString)
{
    b32 Result = BeginsWith(String, LiteralStringLength(String), BeginString);
    return Result;
}

inline b32 BeginsWith(char* String, const char* BeginString)
{
    b32 Result = BeginsWith(String, (char*)BeginString);
    return Result;
}

inline b32 BeginsWith(const char* String, const char* BeginString)
{
    b32 Result = BeginsWith((char*)String, (char*)BeginString);
    return Result;
}

string LiteralString(char* Data, ptr StringLength);
inline string operator+(string Left, int Right)
{
    string Result = LiteralString(Left.Data+Right, Left.Length-Right);
    return Result;
}

inline ptr operator-(string Left, char* Right)
{
    ptr Result = Left.Data - Right;
    return Result;
}

inline string operator-(string Left, i32 Right)
{
    string Result = Left;
    Result.Length -= Right;
    return Result;
}

inline ptr operator-(string Left, string Right)
{
    ptr Result = Left.Data - Right.Data;
    return Result;
}

inline string LiteralString(char* Data, ptr StringLength)
{
    string Result;
    Result.Data = Data;
    Result.Length = StringLength;
    return Result;
}

inline string LiteralString(char* Data)
{
    string Result = LiteralString(Data, LiteralStringLength(Data));
    return Result;
}

inline string AllocateLiteralString(ptr StringLength, arena* Arena = GetDefaultArena())
{
    string Result;
    Result.Data = (char*)PushSize(Arena, StringLength+1, Clear, 0);
    Result.Data[StringLength] = 0;
    Result.Length = StringLength;
    return Result;
}

inline string PushLiteralString(char* String, ptr StringLength, arena* Arena = GetDefaultArena())
{
    string Result = AllocateLiteralString(StringLength, Arena);
    CopyMemory(Result.Data, String, StringLength);
    return Result;
}

inline string PushLiteralString(char* String, arena* Arena = GetDefaultArena())
{
    string Result = PushLiteralString(String, LiteralStringLength(String), Arena);
    return Result;
}

inline string PushLiteralString(const char* String, arena* Arena = GetDefaultArena())
{
    string Result = PushLiteralString((char*)String, LiteralStringLength(String), Arena);
    return Result;
}

inline char* GetEnd(string String)
{
    char* Result = String.Data + String.Length-1;
    return Result;
}

string FindLastChar(string String, char Char)
{
    char* At = GetEnd(String);
    char* End = At;
    while(*End)
    {
        if(*End == Char)
        {
            string Result = LiteralString(End, (At-End)+1); 
            return Result;
        }
        End--;
    }      
    
    return {};    
}

char* FindLastChar(char* String, char Char)
{
    string Result = FindLastChar(LiteralString(String), Char);
    return Result.Data;
}

inline string GetFilename(string Path)
{
    string Result = FindLastChar(Path, OS_PATH_DELIMITER);
    if(Result.Data == NULL)
        return Path;
    return Result+1;
}

inline string GetFilePath(string Path)
{
    string Filename = GetFilename(Path);
    string Result = LiteralString(Path.Data, Filename-Path);
    return Result;
}

inline string GetFileExtension(string Path)
{
    string Result = FindLastChar(Path, '.');
    if(Result.Data == NULL)
        return {};
    return Result+1;
}

inline string GetFileExtension(char* String)
{
    string Result = GetFileExtension(LiteralString(String));
    return Result;
}

inline string GetFilenameWithoutExtension(string Path)
{
    string Result = GetFilename(Path);
    Result.Length -= (GetFileExtension(Path).Length+1);
    return Result;
}

inline string Concat(char* A, ptr ALength, char* B, ptr BLength, arena* Arena = GetDefaultArena())
{
    ptr StringLength = ALength + BLength;
    string Result;
    Result.Data = (char*)PushSize(Arena, StringLength+1, Clear, 0);
    
    CopyMemory(Result.Data, A, ALength);
    CopyMemory(Result.Data+ALength, B, BLength);    
    Result.Data[StringLength] = 0;                   
    Result.Length = StringLength;
    return Result;
}

inline string Concat(char* A, char* B, arena* Arena = GetDefaultArena())
{
    string Result = Concat(A, LiteralStringLength(A), B, LiteralStringLength(B), Arena);
    return Result;
}

inline string Concat(const char* A, ptr ALength, const char* B, ptr BLength, arena* Arena = GetDefaultArena())
{
    string Result = Concat((char*)A, ALength, (char*)B, BLength, Arena);
    return Result;
}

inline string Concat(string A, char* B, ptr BLength, arena* Arena = GetDefaultArena())
{
    string Result = Concat(A.Data, A.Length, B, BLength, Arena);
    return Result;        
}

inline string Concat(string A, char* B, arena* Arena = GetDefaultArena())
{
    string Result = Concat(A.Data, A.Length, B, LiteralStringLength(B), Arena);        
    return Result;
}

inline string Concat(string A, string B, arena* Arena = GetDefaultArena())
{
    string Result = Concat(A.Data, A.Length, B.Data, B.Length, Arena);
    return Result;
}

inline string Concat(char* A, string B, arena* Arena = GetDefaultArena())
{
    string Result = Concat(A, LiteralStringLength(A), B.Data, B.Length, Arena);
    return Result;
}

inline string Concat(string A, char B, arena* Arena = GetDefaultArena())
{
    string Result = Concat(A.Data, A.Length, &B, 1, Arena);
    return Result;
}

inline string Concat(char* A, char B, arena* Arena = GetDefaultArena())
{
    string Result = Concat(A, LiteralStringLength(A), &B, 1, Arena);
    return Result;
}

inline char* ToUpper(char* String, arena* Arena = GetDefaultArena())
{
    ptr StringLength = LiteralStringLength(String);
    char* Result = PushArray(Arena, StringLength+1, char, Clear, 0);
    for(u32 StringIndex = 0; StringIndex < StringLength; StringIndex++)
        Result[StringIndex] = ToUpper(String[StringIndex]);
    Result[StringLength] = 0;
    return Result;
}

inline string ToUpper(string String)
{
    string Result = AllocateLiteralString(String.Length);
    for(u32 StringIndex = 0; StringIndex < String.Length; StringIndex++)
        Result.Data[StringIndex] = ToUpper(String.Data[StringIndex]);
    return Result;
}

//TODO(JJ): Replace this with our own format string that will actually use a stringstream
string FormatString(char* Format, va_list List, arena* StringArena = GetDefaultArena())
{
#define FORMAT_STRING_PADDING 128    
    char* String = PushArray(StringArena, LiteralStringLength(Format)+FORMAT_STRING_PADDING, char, Clear, 0);    
    ptr StringLength = vsprintf(String, Format, List);        
    
    string Result = LiteralString(String, StringLength);    
    return Result;
}

string FormatString(const char* Format, ...)
{    
    va_list List;
    va_start(List, Format);    
    
    string Result = FormatString((char*)Format, List);
    
    va_end(List);
    
    return Result;
}

char* EatWhitespace(char* String)
{
    char* Result = String;
    while(IsWhitespace(*Result)) Result++;
    return Result;
}

char* ProcessToken(char* String)
{
    char* Result = String;
    while(!IsWhitespace(*Result)) Result++;
    return Result;
}

#endif