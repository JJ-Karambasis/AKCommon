#ifndef AK_INTRINSIC_H
#define AK_INTRINSIC_H

#ifdef AK_MSVC_COMPILER
#include <intrin.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include <smmintrin.h>
#endif

ak_i32 AK_Min(ak_i32 A, ak_i32 B);
ak_u32 AK_Min(ak_u32 A, ak_u32 B);
ak_u64 AK_Min(ak_u64 A, ak_u64 B);
ak_f32 AK_Min(ak_f32 A, ak_f32 B);
ak_f32 AK_Min(ak_f32 A, ak_f32 B, ak_f32 C);
ak_f64 AK_Min(ak_f64 A, ak_f64 B);
ak_i32 AK_Max(ak_i32 A, ak_i32 B);
ak_u32 AK_Max(ak_u32 A, ak_u32 B);
ak_u64 AK_Max(ak_u64 A, ak_u64 B);
ak_f32 AK_Max(ak_f32 A, ak_f32 B);
ak_f32 AK_Max(ak_f32 A, ak_f32 B, ak_f32 C);
ak_f64 AK_Max(ak_f64 A, ak_f64 B);
ak_u32 AK_Clamp(ak_u32 Value, ak_u32 Min, ak_u32 Max);
ak_i32 AK_Clamp(ak_i32 Value, ak_i32 Min, ak_i32 Max);
ak_f32 AK_Clamp(ak_f32 Value, ak_f32 Min, ak_f32 Max);
ak_f64 AK_Clamp(ak_f64 Value, ak_f64 Min, ak_f64 Max);
ak_f32 AK_Saturate(ak_f32 Value);
ak_f64 AK_Saturate(ak_f64 Value);
ak_u64 AK_Cycles();
ak_i32 AK_Ceil(ak_f32 Value);
ak_i32 AK_Round(ak_f32 Value);
ak_i32 AK_Floor(ak_f32 Value);
ak_u16 AK_EndianSwap16(ak_u16 Value);
ak_u32 AK_EndianSwap32(ak_u32 Value);
ak_f32 AK_Sin(ak_f32 Rads);
ak_f32 AK_Cos(ak_f32 Rads);
ak_f32 AK_Tan(ak_f32 Rads);
ak_f32 AK_ACos(ak_f32 Rads);
ak_f32 AK_ATan2(ak_f32 A, ak_f32 B);
ak_f32 AK_ASin(ak_f32 Rads);
ak_f32 AK_Sqrt(ak_f32 Value);
ak_f32 AK_Pow(ak_f32 Value, ak_f32 Exp);
ak_i32 AK_AtomicAdd32(ak_i32 volatile* Value, ak_i32 Addend);
ak_i64 AK_AtomicAdd64(ak_i64 volatile* Value, ak_i64 Addend);
ak_f32 AK_Frac(ak_f32 Value);

#endif