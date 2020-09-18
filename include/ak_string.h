#ifndef AK_STRING_H
#define AK_STRING_H

struct ak_string
{
    ak_char*  Data;
    ak_u32 Length;        
    
    ak_char operator[](ak_u32 Index);        
};

ak_string AK_CreateEmptyString();
ak_string AK_CreateString(ak_char* Data, ak_u32 StringLength);
ak_string AK_CreateString(ak_char* Data);
ak_string AK_AllocateString(ak_u32 StringLength, ak_arena* Arena);
ak_string AK_PushString(ak_char* Data, ak_u32 StringLength, ak_arena* Arena);
ak_string AK_PushString(ak_char* Data, ak_arena* Arena);
ak_string AK_PushString(const ak_char* Data, ak_arena* Arena); 
ak_bool AK_StringIsNullOrEmpty(ak_string String);
ak_u32 AK_StringLength(ak_char* String);
ak_u32 AK_StringLength(const ak_char* String);
ak_bool AK_StringEquals(ak_char* StringA, ak_u32 StringALength, ak_char* StringB, ak_u32 StringBLength);
ak_bool AK_StringEquals(ak_char* StringA, ak_char* StringB);
ak_bool AK_StringEquals(const ak_char* StringA, const ak_char* StringB);
ak_bool AK_StringEquals(const ak_char* StringA, ak_char* StringB);
ak_bool AK_StringEquals(ak_char* StringA, const ak_char* StringB);
ak_bool AK_StringEquals(ak_char* StringA, ak_char* StringB, ak_u32 StringBLength);
ak_bool AK_StringEquals(ak_string StringA, ak_char* StringB);
ak_bool AK_StringEquals(const ak_char* StringA, ak_string StringB);
ak_bool AK_StringEndsWith(ak_char* String, ak_u32 StringLength, ak_char* MatchString, ak_u32 MatchStringLength);
ak_bool AK_StringEndsWith(ak_char* String, ak_char* MatchString);
ak_bool AK_StringEndsWith(ak_char* String, const ak_char* MatchString);
ak_bool AK_StringEndsWith(const ak_char* String, const ak_char* MatchString);
ak_bool AK_StringEndsWith(ak_char* String, ak_u32 StringLength, ak_char Character);
ak_bool AK_StringEndsWith(ak_string String, ak_char Character);
ak_bool AK_StringBeginsWith(ak_char* String, ak_u32 StringLength, ak_char* MatchString, ak_u32 MatchStringLength);
ak_bool AK_StringBeginsWith(ak_char* String, ak_char* MatchString);
ak_bool AK_StringBeginsWith(ak_char* String, const ak_char* MatchString);
ak_bool AK_StringBeginsWith(const ak_char* String, const ak_char* MatchString);
ak_bool AK_StringBeginsWith(ak_char* String, ak_u32 StringLength, ak_char Character);
ak_bool AK_StringBeginsWith(ak_string String, ak_char Character);
ak_string AK_FindLastChar(ak_string String, ak_char Character);
ak_char*  AK_FindLastChar(ak_char* String, ak_char Character);
ak_string AK_GetFilename(ak_string FilePath);
ak_string AK_GetFilepath(ak_string FilePath);
ak_string AK_GetFileExtension(ak_string FilePath);
ak_string AK_GetFileExtension(ak_char* FilePath);
ak_string AK_GetFilenameWithoutExtension(ak_string FilePath);
ak_string AK_StringConcat(ak_char* StringA, ak_u32 StringALength, ak_char* StringB, ak_u32 StringBLength, ak_arena* Arena);
ak_string AK_StringConcat(ak_char* StringA, ak_char* StringB, ak_arena* Arena);
ak_string AK_StringConcat(const ak_char* StringA, ak_u32 StringALength, const ak_char* StringB, ak_u32 StringBLength, ak_arena* Arena);
ak_string AK_StringConcat(ak_string StringA, ak_char* StringB, ak_u32 StringBLength, ak_arena* Arena);
ak_string AK_StringConcat(ak_string StringA, ak_char* StringB, ak_arena* Arena);
ak_string AK_StringConcat(ak_string StringA, ak_string StringB, ak_arena* Arena);
ak_string AK_StringConcat(ak_char* StringA, ak_string StringB, ak_arena* Arena);
ak_string AK_StringConcat(ak_string String, ak_char Character, ak_arena* Arena);
ak_string AK_StringConcat(ak_char* String, ak_char Character, ak_arena* Arena);
ak_string AK_GetToken(ak_string String);
ak_string AK_FormatString(ak_arena* Arena, const ak_char* Format, va_list List);
ak_string AK_FormatString(ak_arena* Arena, const ak_char* Format, ...);
ak_bool AK_IsInteger(ak_char* String);
ak_bool AK_IsReal(ak_char* String);
ak_bool AK_IsInteger(ak_char* String);
ak_bool AK_IsReal(ak_char* String);
ak_bool AK_IsDigit(ak_char Character);
ak_bool AK_IsNewline(ak_char Character);
ak_bool AK_IsNullChar(ak_char Character);
ak_bool AK_IsWhitespace(ak_char Character);
ak_i32 AK_ToNumeric(ak_char Character);
ak_i32 AK_ToInt(ak_char* String);
ak_f64 AK_ToF64(ak_char* String);
ak_f32 AK_ToF32(ak_char* String);
char AK_ToLower(ak_char Value);
char AK_ToUpper(ak_char Value);
ak_string AK_ToLower(ak_string String, ak_arena* Arena);
ak_string AK_ToUpper(ak_string String, ak_arena* Arena);
ak_char* AK_ToLower(ak_char* String, ak_arena* Arena);
ak_char* AK_ToUpper(ak_char* String, ak_arena* Arena);
ak_char* AK_GetEnd(ak_char* String, ak_u32 StringLength);
ak_char* AK_TrimStart(ak_char* String);
ak_string AK_ReadToken(ak_char* String);
ak_string AK_OffsetString(ak_string String, ak_i32 Offset);
#endif