#ifndef AK_LOGGER_H
#define AK_LOGGER_H

typedef ak_string_builder ak_logger;

#ifdef AK_DEVELOPER_BUILD
#define AK_Assert(x, format, ...) do { if(!(x)) {AK__Internal_Assert(AK_CURRENT_FILENAME, AK_CURRENT_LINE, AK_CURRENT_FUNCTION, format, __VA_ARGS__); AK_DEBUG_BREAK; } } while(0)
#else
#define AK_Assert(x, format, ...)
#endif

#define AK_InvalidCode() AK_Assert(false, "Invalid code path");
#define AK_NotImplemented() AK_Assert(false, "Code path not implemented");
#define AK_InvalidCase(x) case x: { AK_InvalidCode(); } break
#define AK_INVALID_ELSE else AK_InvalidCode()
#define AK_INVALID_DEFAULT_CASE default:  { AK_InvalidCode(); } break

#define AK_LogInfo(logger, format, ...) AK__Internal_LogInfo(logger, format, __VA_ARGS__)
#define AK_LogWarning(logger, format, ...) AK__Internal_LogWarning(logger, format, __VA_ARGS__)
#define AK_LogError(logger, format, ...) AK__Internal_LogError(logger, AK_CURRENT_FILENAME, AK_CURRENT_LINE, AK_CURRENT_FUNCTION, format, __VA_ARGS__)

void AK__Internal_LogInfo(ak_logger* Logger, ak_char* Format, ...);
void AK__Internal_LogWarning(ak_logger* Logger, ak_char* Format, ...);
void AK__Internal_LogError(ak_logger* Logger, ak_char* Format, ...);
void AK__Internal_Assert(ak_char* Filename, ak_u32 LineNumber, ak_char* Function, ak_char* Format, ...);

ak_bool AK_OutputToFile(ak_logger* Logger, ak_char* Path);
ak_bool AK_OutputToFile(ak_logger* Logger, ak_string Path);

#endif