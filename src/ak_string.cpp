
ak_char ak_string::operator[](ak_u32 Index) 
{
    AK_Assert(Index < Length, "Index out of bounds");
    return Data[Index]; 
}    

ak_string AK_CreateEmptyString()
{
    return {};
}

ak_string AK_CreateString(ak_char* Data, ak_u32 StringLength)
{
    ak_string Result = {Data, StringLength};
    return Result;
}

ak_string AK_CreateString(ak_char* Data)
{
    ak_string Result = AK_CreateString(Data, AK_StringLength(Data));
    return Result;
}

ak_string AK_CreateString(const ak_char* Data)
{
    ak_string Result = AK_CreateString((ak_char*)Data);
    return Result;
}

ak_string AK_CreateString(ak_buffer Buffer)
{
    ak_string Result = AK_CreateString((ak_char*)Buffer.Data, AK_SafeU32(Buffer.Size));
    return Result;
}

ak_string AK_AllocateString(ak_u32 StringLength, ak_arena* Arena)
{
    ak_string Result;
    Result.Data = Arena->PushArray<ak_char>(StringLength+1);
    Result.Length = StringLength;
    Result.Data[StringLength] = 0;
    return Result;
}

ak_string AK_AllocateString(ak_u32 StringLength)
{
    ak_string Result = {};
    Result.Data = (ak_char*)AK_Allocate(StringLength+1);
    Result.Length = StringLength;
    Result.Data[StringLength] = 0;
    return Result;
}

ak_string AK_PushString(ak_char* Data, ak_u32 StringLength, ak_arena* Arena)
{
    ak_string Result = AK_AllocateString(StringLength, Arena);
    AK_MemoryCopy(Result.Data, Data, StringLength);
    return Result;
}

ak_string AK_PushString(ak_char* Data, ak_arena* Arena)
{
    ak_string Result = AK_PushString(Data, AK_StringLength(Data), Arena);
    return Result;
}

ak_string AK_PushString(const ak_char* Data, ak_arena* Arena)
{
    ak_string Result = AK_PushString((ak_char*)Data, Arena);
    return Result;
}

ak_string AK_PushString(ak_string Data, ak_arena* Arena)
{
    ak_string Result = AK_PushString(Data.Data, Data.Length, Arena);
    return Result;
}

ak_string AK_PushString(ak_char* Data, ak_u32 StringLength)
{
    ak_string Result = AK_AllocateString(StringLength);
    AK_MemoryCopy(Result.Data, Data, StringLength);
    return Result;
}

ak_string AK_PushString(ak_char* Data)
{
    return AK_PushString(Data, AK_StringLength(Data));
}

ak_string AK_PushString(ak_string String)
{
    return AK_PushString(String.Data, String.Length);
}

void AK_FreeString(ak_string String)
{
    if(String.Length && String.Data)
        AK_Free(String.Data);
}

ak_bool AK_StringIsNullOrEmpty(ak_string String)
{
    ak_bool Result = !String.Data || !String.Length;
    return Result;
}

ak_bool AK_StringIsNullOrEmpty(ak_char* String)
{
    ak_bool Result = !String || !AK_StringLength(String);
    return Result;
}

ak_u32 AK_StringLength(ak_char* String)
{
    ak_u32 Result = 0;
    while(*String++)    
        Result++;   
    return Result;
}

ak_u32 AK_StringLength(const ak_char* String)
{
    ak_u32 Result = AK_StringLength((ak_char*)String);
    return Result;
}

ak_bool AK_StringEquals(ak_char* StringA, ak_u32 StringALength, ak_char* StringB, ak_u32 StringBLength)
{
    if(StringALength != StringBLength)
        return false;
    
    for(ak_u32 Index = 0; Index < StringALength; Index++)
    {
        if(StringA[Index] != StringB[Index])
            return false;
    }    
    return true;
}

ak_bool AK_StringEquals(ak_char* StringA, ak_u32 StringALength, const ak_char* StringB, ak_u32 StringBLength)
{
    return AK_StringEquals(StringA, StringALength, (ak_char*)StringB, StringBLength);
}

ak_bool AK_StringEquals(ak_char* StringA, ak_char* StringB)
{
    return AK_StringEquals(StringA, AK_StringLength(StringA), StringB, AK_StringLength(StringB));
}

ak_bool AK_StringEquals(const ak_char* StringA, const ak_char* StringB)
{
    return AK_StringEquals((ak_char*)StringA, (ak_char*)StringB);
}

ak_bool AK_StringEquals(const ak_char* StringA, ak_char* StringB)
{
    return AK_StringEquals((ak_char*)StringA, StringB);
}

ak_bool AK_StringEquals(ak_char* StringA, const ak_char* StringB)
{
    return AK_StringEquals(StringA, (ak_char*)StringB);
}

ak_bool AK_StringEquals(ak_char* StringA, ak_char* StringB, ak_u32 StringBLength)
{
    return AK_StringEquals(StringA, AK_StringLength(StringA), StringB, StringBLength);
}

ak_bool AK_StringEquals(ak_string StringA, ak_char* StringB)
{
    return AK_StringEndsWith(StringA.Data, StringA.Length, StringB, AK_StringLength(StringB));
}

ak_bool AK_StringEquals(const ak_char* StringA, ak_string StringB)
{
    return AK_StringEquals((ak_char*)StringA, StringB.Data, StringB.Length);
}

ak_bool AK_StringEquals(ak_string StringA, ak_string StringB)
{
    return AK_StringEquals(StringA.Data, StringA.Length, StringB.Data, StringB.Length);
}

ak_bool AK_StringEndsWith(ak_char* String, ak_u32 StringLength, ak_char* MatchString, ak_u32 MatchStringLength)
{        
    ak_i32 Difference = StringLength-MatchStringLength;    
    if(Difference < 0)
        return false;
    
    for(ak_u32 AIndex = (ak_u32)Difference, BIndex = 0; AIndex < StringLength; AIndex++, BIndex++)
    {
        if(!MatchString[BIndex])
            break;
        
        if(String[AIndex] != MatchString[BIndex])
            return false;                
    }
    
    return true;
}

ak_bool AK_StringEndsWith(ak_char* String, ak_char* MatchString)
{
    return AK_StringEndsWith(String, AK_StringLength(String), MatchString, AK_StringLength(MatchString));
}

ak_bool AK_StringEndsWith(ak_char* String, const ak_char* MatchString)
{
    return AK_StringEndsWith(String, AK_StringLength(String), (ak_char*)MatchString, AK_StringLength(MatchString));
}

ak_bool AK_StringEndsWith(const ak_char* String, const ak_char* MatchString)
{
    return AK_StringEndsWith((ak_char*)String, AK_StringLength(String), (ak_char*)MatchString, AK_StringLength(MatchString));
}

ak_bool AK_StringEndsWith(ak_char* String, ak_u32 StringLength, ak_char Character)
{
    ak_bool Result = String[StringLength-1] == Character;    
    return Result;
}

ak_bool AK_StringEndsWith(ak_string String, ak_char Character)
{
    return AK_StringEndsWith(String.Data, String.Length, Character);
}

ak_bool AK_StringBeginsWith(ak_char* String, ak_u32 StringLength, ak_char* MatchString, ak_u32 MatchStringLength)
{
    if(StringLength < MatchStringLength)
        return false;
    
    for(ak_u32 StringIndex = 0; StringIndex < StringLength; StringIndex++)
    {           
        if(StringIndex >= MatchStringLength)
            break;
        
        if(String[StringIndex] != MatchString[StringIndex])
        {
            return false;
        }
    }    
    return true;
}

ak_bool AK_StringBeginsWith(ak_char* String, ak_char* MatchString)
{
    return AK_StringBeginsWith(String, AK_StringLength(String), MatchString, AK_StringLength(MatchString));
}

ak_bool AK_StringBeginsWith(ak_char* String, const ak_char* MatchString)
{
    return AK_StringBeginsWith(String, AK_StringLength(String), (ak_char*)MatchString, AK_StringLength(MatchString));
}

ak_bool AK_StringBeginsWith(const ak_char* String, const ak_char* MatchString)
{
    return AK_StringBeginsWith((ak_char*)String, AK_StringLength(String), (ak_char*)MatchString, AK_StringLength(MatchString));
}

ak_bool AK_StringBeginsWith(ak_char* String, ak_u32 StringLength, ak_char Character)
{
    if(StringLength == 0)
        return false;
    
    return String[0] == Character;
}

ak_bool AK_StringBeginsWith(ak_string String, ak_char Character)
{
    return AK_StringBeginsWith(String.Data, String.Length, Character);
}

ak_string AK_StringFind(ak_string String, ak_string Pattern)
{
    if(Pattern.Length > String.Length)
        return AK_CreateEmptyString();
    
    for(ak_u32 CharIndex = 0; CharIndex < String.Length; CharIndex++)
    {
        if(String[CharIndex] == Pattern[0])
        {
            ak_u32 Remainder = Pattern.Length-1;
            if((CharIndex+Remainder) < String.Length)
            {
                ak_u32 StartIndex = CharIndex;
                ak_bool Valid = true;
                for(ak_u32 PatternIndex = 0; PatternIndex < Pattern.Length; PatternIndex++)
                {
                    if(String[CharIndex] != Pattern[PatternIndex])
                    {
                        Valid = false;
                        break;
                    }
                    CharIndex++;
                }
                if(Valid)
                {
                    return AK_OffsetString(String, StartIndex);
                }
            }
            else
            {
                return AK_CreateEmptyString();
            }
        }
    }
    
    return AK_CreateEmptyString();
}

ak_string AK_StringFind(ak_string String, const ak_char* Pattern)
{
    return AK_StringFind(String, AK_CreateString(Pattern));
}

ak_string AK_FindLastChar(ak_string String, ak_char Character)
{
    ak_char* At = AK_GetEnd(String.Data, String.Length);
    ak_char* End = At;
    while(*End)
    {
        if(*End == Character)
        {
            ak_string Result = AK_CreateString(End, AK_SafeU32((At-End)+1));
            return Result;
        }        
        End--;
    }
    
    return AK_CreateEmptyString();
}

ak_char*  AK_FindLastChar(ak_char* String, ak_char Character)
{
    ak_string Result = AK_FindLastChar(AK_CreateString(String), Character);
    return Result.Data;
}

ak_string AK_GetFilename(ak_string FilePath)
{
    ak_string Result = AK_FindLastChar(FilePath, AK_OS_PATH_DELIMITER);
    if(Result.Data == NULL)
        return FilePath;
    
    return AK_OffsetString(Result, 1);
}

ak_string AK_GetFilepath(ak_string FilePath)
{
    ak_string Filename = AK_GetFilename(FilePath);
    if(AK_StringIsNullOrEmpty(Filename))
        return Filename;
    
    ak_string Result = AK_CreateString(FilePath.Data, FilePath.Length-Filename.Length);
    return Result;
}

ak_string AK_GetFileExtension(ak_string FilePath)
{
    ak_string Result = AK_FindLastChar(FilePath, '.');
    if(Result.Data == NULL)
        return AK_CreateEmptyString();
    return AK_OffsetString(Result, 1);
}

ak_string AK_GetFileExtension(ak_char* FilePath)
{
    ak_string Result = AK_GetFileExtension(AK_CreateString(FilePath));
    return Result;
}

ak_string AK_GetFilenameWithoutExtension(ak_string FilePath)
{
    ak_string Result = AK_GetFilename(FilePath);
    if(AK_StringIsNullOrEmpty(Result))
        return Result;
    
    Result.Length -= (AK_GetFileExtension(FilePath).Length+1);
    return Result;
}

ak_string AK_StringConcat(ak_char* StringA, ak_u32 StringALength, ak_char* StringB, ak_u32 StringBLength, ak_arena* Arena)
{
    ak_u32 StringLength = StringALength + StringBLength;
    ak_string Result = AK_AllocateString(StringLength+1, Arena);        
    CopyMemory(Result.Data, StringA, StringALength);
    CopyMemory(Result.Data+StringALength, StringB, StringBLength);    
    Result.Data[StringLength] = 0;                   
    Result.Length = StringLength;
    return Result;
}

ak_string AK_StringConcat(ak_char* StringA, ak_char* StringB, ak_arena* Arena)
{
    return AK_StringConcat(StringA, AK_StringLength(StringA), StringB, AK_StringLength(StringB), Arena);
}

ak_string AK_StringConcat(const ak_char* StringA, ak_u32 StringALength, const ak_char* StringB, ak_u32 StringBLength, ak_arena* Arena)
{
    return AK_StringConcat((ak_char*)StringA, StringALength, (ak_char*)StringB, StringBLength, Arena);
}

ak_string AK_StringConcat(ak_string StringA, ak_char* StringB, ak_u32 StringBLength, ak_arena* Arena)
{
    return AK_StringConcat(StringA.Data, StringA.Length, StringB, StringBLength, Arena);
}

ak_string AK_StringConcat(ak_string StringA, ak_char* StringB, ak_arena* Arena)
{
    return AK_StringConcat(StringA.Data, StringA.Length, StringB, AK_StringLength(StringB), Arena);
}

ak_string AK_StringConcat(ak_string StringA, ak_string StringB, ak_arena* Arena)
{
    return AK_StringConcat(StringA.Data, StringA.Length, StringB.Data, StringB.Length, Arena);
}

ak_string AK_StringConcat(ak_char* StringA, ak_string StringB, ak_arena* Arena)
{
    return AK_StringConcat(StringA, AK_StringLength(StringA), StringB.Data, StringB.Length, Arena);    
}

ak_string AK_StringConcat(ak_string String, ak_char Character, ak_arena* Arena)
{
    return AK_StringConcat(String.Data, String.Length, &Character, 1, Arena);
}

ak_string AK_StringConcat(ak_char* String, ak_char Character, ak_arena* Arena)
{
    return AK_StringConcat(String, AK_StringLength(String), &Character, 1, Arena);
}

ak_string AK_StringConcat(ak_string String, const ak_char* StringB, ak_arena* Arena)
{
    return AK_StringConcat(String.Data, String.Length, (ak_char*)StringB, AK_StringLength(StringB), Arena);
}

ak_string AK_FormatString(ak_arena* Arena, const ak_char* Format, va_list List)
{
#undef FORMAT_STRING_PADDING
#define FORMAT_STRING_PADDING 128
    ak_i32 InitialStringLength = (ak_i32)AK_StringLength(Format)+1;
    ak_char* String = Arena->PushArray<ak_char>(InitialStringLength);
    
    ak_u32 Iterations = 4;
    
    ak_i32 Result = 0;
    do
    {        
        Result = vsnprintf(String, InitialStringLength, Format, List);        
        if((Result >= 0) && Result < InitialStringLength)
        {
            Arena->PushArray<ak_char>(1);
            return AK_CreateString(String, Result);
        }        
        AK_MemoryClear(String, InitialStringLength);
        Arena->PushArray<ak_char>(InitialStringLength);
        InitialStringLength *= 2;
    } while(Iterations--);    
    
#undef FORMAT_STRING_PADDING
    return AK_CreateEmptyString();
}

ak_string AK_FormatString(ak_arena* Arena, const ak_char* Format, ...)
{
    va_list List;
    va_start(List, Format);
    ak_string Result = AK_FormatString(Arena, Format, List);
    va_end(List);
    return Result;
}

ak_bool AK_IsInteger(ak_char* String)
{
    String = AK_TrimStart(String);
    while(*String)
    {
        if(!AK_IsDigit(*String))
            return false;
        String++;
    }    
    return true;
}

ak_bool AK_IsReal(ak_char* String)
{
    String = AK_TrimStart(String);
    ak_bool FoundDecimal = false;
    ak_bool FoundFloat = false;
    while(*String)
    {
        if(!AK_IsDigit(*String))
        {
            if(*String == '.')
            {
                if(FoundDecimal) return false;
                FoundDecimal = true;
            }            
            else if(*String == 'f')
            {
                if(!FoundDecimal) return false;
                if(FoundFloat) return false;
                FoundFloat = true;
            }
            else
                return false;
        }
        
        String++;
    }    
    return true;
}

ak_bool AK_IsDigit(ak_char Character)
{
    ak_bool Result = isdigit(Character);
    return Result;
}

ak_bool AK_IsNewline(ak_char Character)
{
    ak_bool Result = (Character == '\n' || Character == '\r');
    return Result;
}

ak_bool AK_IsNullChar(ak_char Character)
{
    ak_bool Result = (Character == '\0');
    return Result;
}

ak_bool AK_IsWhitespace(ak_char Character)
{
    ak_bool Result = AK_IsNewline(Character) || (Character == ' ') || (Character == '\t') ||  (Character == '\0');
    return Result;
}

ak_i32 AK_ToNumeric(ak_char Character)
{
    AK_Assert(AK_IsDigit(Character), "Numeric is not a digit, cannot convert to integer");
    ak_i32 Result = (ak_i32)(Character - '0');
    return Result;
}

ak_i32 AK_ToInt(ak_char* String)
{
    //AK_Assert(AK_IsInteger(String), "String is not an integer number, cannot convert");
    ak_i32 Result = atoi(String);
    return Result;
}

ak_f64 AK_ToF64(ak_char* String)
{
    //AK_Assert(AK_IsReal(String), "String is not a real number, cannot convert");
    ak_f64 Result = atof(String);
    return Result;
}

ak_f32 AK_ToF32(ak_char* String)
{    
    ak_f32 Result = (ak_f32)AK_ToF64(String);
    return Result;
}

ak_char AK_ToLower(ak_char Value)
{
    return (ak_char)tolower(Value);
}

ak_char AK_ToUpper(ak_char Value)
{
    return (ak_char)toupper(Value);
}

ak_string AK_ToLower(ak_string String, ak_arena* Arena)
{
    ak_string Result = AK_AllocateString(String.Length, Arena);
    for(ak_u32 StringIndex = 0; StringIndex < String.Length; StringIndex++)
        Result.Data[StringIndex] = AK_ToLower(String.Data[StringIndex]);
    return Result;
}

ak_string AK_ToUpper(ak_string String, ak_arena* Arena)
{
    ak_string Result = AK_AllocateString(String.Length, Arena);
    for(ak_u32 StringIndex = 0; StringIndex < String.Length; StringIndex++)
        Result.Data[StringIndex] = AK_ToUpper(String.Data[StringIndex]);
    return Result;
}

ak_char* AK_ToLower(ak_char* String, ak_arena* Arena)
{
    return AK_ToLower(AK_CreateString(String), Arena).Data;
}

ak_char* AK_ToUpper(ak_char* String, ak_arena* Arena)
{
    return AK_ToUpper(AK_CreateString(String), Arena).Data;
}

ak_char* AK_GetEnd(ak_char* String, ak_u32 StringLength)
{
    ak_char* Result = String + StringLength-1;
    return Result;
}

ak_char* AK_TrimStart(ak_char* String)
{
    ak_char* Result = String;
    while(AK_IsWhitespace(*Result)) Result++;
    return Result;
}

ak_string AK_OffsetLength(ak_string String, ak_i32 Offset)
{
    ak_string Result = AK_CreateString(String.Data, String.Length+Offset);
    return Result;
}

ak_string AK_OffsetString(ak_string String, ak_i32 Offset)
{
    ak_string Result = {String.Data+Offset, String.Length-Offset};
    return Result;
}

ak_string AK_ReadToken(ak_char* String)
{
    String = AK_TrimStart(String);
    ak_char* At = String;
    ak_u32 Length = 0;
    while(!AK_IsWhitespace(*At)) { At++; Length++; }
    return AK_CreateString(String, Length);    
}

