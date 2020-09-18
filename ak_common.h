#ifndef AK_COMMON_H
#define AK_COMMON_H

#ifndef AK_WINDOWS
#ifdef _WIN32
#define AK_WINDOWS
#endif
#endif //AK_WINDOWS

#ifndef AK_MSVC_COMPILER
#ifdef _MSC_VER
#define AK_MSVC_COMPILER
#endif //_MSC_VER
#endif //AK_MSVC_COMPILER

#ifdef AK_WINDOWS
#define AK_OS_PATH_DELIMITER  '\\'
#include <Windows.h>
#include <shobjidl_core.h>
#define AK_DEBUG_BREAK __debugbreak();
#endif //AK_WINDOWS

#ifdef AK_MSVC_COMPILER
#define AK_EXPORT __declspec(dllexport)
#endif //AK_MSVC_COMPILER

#undef AK_INT_MIN
#define AK_INT_MIN (-2147483647 - 1)

#undef AK_INT_MAX
#define AK_INT_MAX 2147483647

#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef float  ak_f32;
typedef double ak_f64;

typedef char ak_char;

typedef uint8_t  ak_u8;
typedef uint16_t ak_u16;
typedef uint32_t ak_u32;
typedef uint64_t ak_u64;

typedef int8_t  ak_i8;
typedef int16_t ak_i16;
typedef int32_t ak_i32;
typedef int64_t ak_i64;

typedef ak_i32 ak_bool;

typedef size_t ak_uaddr;
typedef ptrdiff_t ak_iaddr;

#define AK_CURRENT_FILENAME (AK_FindLastChar(__FILE__, AK_OS_PATH_DELIMITER) ? AK_FindLastChar(__FILE__, AK_OS_PATH_DELIMITER)+1 : __FILE__)
#define AK_CURRENT_LINE __LINE__
#define AK_CURRENT_FUNCTION __FUNCSIG__

#define AK_Count(x) (sizeof((x)) / sizeof((x)[0]))
#define AK_Byte(x) (x)
#define AK_Kilobyte(x) (x*1024LL)
#define AK_Megabyte(x) (AK_Kilobyte(x)*1024LL)
#define AK_Gigabyte(x) (AK_Megabyte(x)*1024LL)
#define AK_Terabyte(x) (AK_Terabyte(x)*1024LL)
#define AK_Square(x) ((x)*(x))
#define AK_Bitset(x) (1 << (x))
#define AK_Sign(x) (((x) < 0) ? -1 : 1)
#define AK_Swap(x, y) do { auto temp = x; x = y; y = temp; } while(0)
#define AK_RiffCode(x, y, z, w) (((ak_u32)(x) << 0) | ((ak_u32)(y) << 8) | ((ak_u32)(z) << 16) | ((ak_u32)(w) << 24))
#define AK_Abs(v) (((v) < 0) ? -(v) : (v))

#define AK_Expand( x ) x
#define AK_Cat(A, B) A ## B
#define AK_Cat2(A, B) AK_Cat(A, B)
#define AK_Select(NAME, NUM) AK_Cat(NAME ## _, NUM)
#define AK_GetCount( _1, _2, _3, _4, _5, _6, COUNT, ... ) COUNT
#define AK_VaSize( ... ) AK_Expand(AK_GetCount( __VA_ARGS__, 6, 5, 4, 3, 2, 1 ))
#define AK_VaSelect( NAME, ... ) AK_Select( NAME, AK_VaSize(__VA_ARGS__) )(__VA_ARGS__)
#define AK_StringifyX(macro) #macro
#define AK_Stringify(macro) AK_StringifyX(macro)
#define AK_FieldOffset(type, member) ((ak_uaddr)&(((type*)0)->member))

#define AK_ForEach(Value, Structure) auto AK_Cat2(iter_, __LINE__) = AK_BeginIter(Structure); \
for(auto* Value = AK_Cat2(iter_, __LINE__).First(); Value; Value = AK_Cat2(iter_, __LINE__).Next())

#define AK_ITER_FUNCTIONS(type) \
type* First(); \
type* Next(); \

#define internal static
#define global static
#define local static

#include "include/ak_float.h"
#include "include/ak_intrinsic.h"
#include "include/ak_util.h"
#include "include/ak_atomic.h"
#include "include/ak_memory.h"
#include "include/ak_string.h"
#include "include/ak_string_builder.h"
#include "include/ak_logger.h"
#include "include/ak_math.h"
#include "include/ak_array.h"
#include "include/ak_pool.h"
#include "include/ak_hash_map.h"
#include "include/ak_link_list.h"
#include "include/ak_platform.h"
#include "include/ak_mesh_generation.h"
#include "include/ak_zlib.h"
#include "include/ak_png.h"
#include "include/ak_tests.h"
#endif

#ifdef AK_COMMON_IMPLEMENTATION
#include "src/ak_float.cpp"
#include "src/ak_intrinsic.cpp"
#include "src/ak_util.cpp"
#include "src/ak_atomic.cpp"
#include "src/ak_memory.cpp"
#include "src/ak_string.cpp"
#include "src/ak_string_builder.cpp"
#include "src/ak_logger.cpp"
#include "src/ak_math.cpp"
#include "src/ak_array.cpp"
#include "src/ak_pool.cpp"
#include "src/ak_hash_map.cpp"
#include "src/ak_link_list.cpp"
#include "src/ak_platform.cpp"
#include "src/ak_mesh_generation.cpp"
#include "src/ak_zlib.cpp"
#include "src/ak_png.cpp"
#endif

#ifdef AK_COMMON_INCLUDE_UNIT_TESTS
#include "src/ak_tests.cpp"
#endif