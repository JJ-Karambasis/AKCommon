#ifndef AK_ERROR_H
#define AK_ERROR_H

typedef ak_string_builder ak_error_stream;

void AK__Internal_LogInfo(ak_error_stream* Stream, 
void AK__Internal_LogError(ak_error_stream* Stream, ak_char* Filename, ak_u32 LineNumber, ak_char* Function, ak_char* Format, ...); 
void AK__Internal_Assert(ak_char* Filename, ak_u32 LineNumber, ak_char* Function, ak_char* Format, ...); 

#endif