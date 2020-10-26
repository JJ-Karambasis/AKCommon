ak_i32 AK_Min(ak_i32 A, ak_i32 B)
{
    ak_i32 Result;
#ifdef AK_MSVC_COMPILER    
    Result = _mm_cvtsi128_si32(_mm_min_epi32(_mm_set1_epi32(A), _mm_set1_epi32(B)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_u32 AK_Min(ak_u32 A, ak_u32 B)
{
    ak_u32 Result;
#ifdef AK_MSVC_COMPILER
    Result = (ak_u32)_mm_cvtsi128_si32(_mm_min_epu32(_mm_set1_epi32(A), _mm_set1_epi32(B)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_u64 AK_Min(ak_u64 A, ak_u64 B)
{
    ak_u64 Result = (A < B) ? A : B;
    return Result;
}

ak_f32 AK_Min(ak_f32 A, ak_f32 B)
{
    ak_f32 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(A), _mm_set_ss(B)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_f32 AK_Min(ak_f32 A, ak_f32 B, ak_f32 C)
{
    ak_f32 Result = AK_Min(A, AK_Min(B, C));
    return Result;
}

ak_f64 AK_Min(ak_f64 A, ak_f64 B)
{
    ak_f64 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtsd_f64(_mm_min_sd(_mm_set_sd(A), _mm_set_sd(B)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_i32 AK_Max(ak_i32 A, ak_i32 B)
{
    ak_i32 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtsi128_si32(_mm_max_epi32(_mm_set1_epi32(A), _mm_set1_epi32(B)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_u32 AK_Max(ak_u32 A, ak_u32 B)
{
    ak_u32 Result;
#ifdef AK_MSVC_COMPILER
    Result = (ak_u32)_mm_cvtsi128_si32(_mm_max_epu32(_mm_set1_epi32(A), _mm_set1_epi32(B)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_u64 AK_Max(ak_u64 A, ak_u64 B)
{
    ak_u64 Result = (A > B) ? A : B;
    return Result;
}

ak_f32 AK_Max(ak_f32 A, ak_f32 B)
{
    ak_f32 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(A), _mm_set_ss(B)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_f32 AK_Max(ak_f32 A, ak_f32 B, ak_f32 C)
{
    ak_f32 Result = AK_Max(A, AK_Max(B, C));
    return Result;
}

ak_f64 AK_Max(ak_f64 A, ak_f64 B)
{
    ak_f64 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(A), _mm_set_sd(B)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_u32 AK_Clamp(ak_u32 Value, ak_u32 Min, ak_u32 Max)
{
    ak_u32 Result = AK_Min(AK_Max(Value, Min), Max);
    return Result;
}

ak_i32 AK_Clamp(ak_i32 Value, ak_i32 Min, ak_i32 Max)
{
    ak_i32 Result = AK_Min(AK_Max(Value, Min), Max);
    return Result;
}

ak_f32 AK_Clamp(ak_f32 Value, ak_f32 Min, ak_f32 Max)
{
    ak_f32 Result = AK_Min(AK_Max(Value, Min), Max);
    return Result;
}

ak_f64 AK_Clamp(ak_f64 Value, ak_f64 Min, ak_f64 Max)
{
    ak_f64 Result = AK_Min(AK_Max(Value, Min), Max);
    return Result;
}

ak_f32 AK_Saturate(ak_f32 Value)
{
    ak_f32 Result = AK_Clamp(Value, 0.0f, 1.0f);
    return Result;
}

ak_f64 AK_Saturate(ak_f64 Value)
{
    ak_f64 Result = AK_Clamp(Value, 0.0, 1.0);
    return Result;
}

ak_u64 AK_Cycles()
{
    ak_u64 Result;
#ifdef AK_MSVC_COMPILER
    Result = __rdtsc();
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_i32 AK_Ceil(ak_f32 Value)
{
    ak_i32 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtss_si32(_mm_ceil_ss(_mm_setzero_ps(), _mm_set_ss(Value)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_i32 AK_Round(ak_f32 Value)
{
    ak_i32 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtss_si32(_mm_round_ss(_mm_setzero_ps(), _mm_set_ss(Value), _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC));
#else
    AK_NotImplemented();    
#endif    
    return Result;
}

ak_i32 AK_Floor(ak_f32 Value)
{
    ak_i32 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtss_si32(_mm_floor_ps(_mm_set_ss(Value)));
#else
    AK_NotImplemented();
#endif 
    return Result;
}

ak_u16 AK_EndianSwap16(ak_u16 Value)
{
    ak_u16 Result = ((Value << 8) | (Value >> 8));
    return Result;
}

ak_u32 AK_EndianSwap32(ak_u32 Value)
{
    ak_u32 Result = ((Value << 24) | 
                     ((Value & 0xFF00) << 8) |
                     ((Value >> 8) & 0xFF00) | 
                     (Value >> 24));
    return Result;    
}

ak_f32 AK_Sin(ak_f32 Rads)
{
    ak_f32 Result = sinf(Rads);
    return Result;
}

ak_f64 AK_Sin(ak_f64 Rads)
{
    ak_f64 Result = sin(Rads);
    return Result;
}

ak_f32 AK_Cos(ak_f32 Rads)
{
    ak_f32 Result = cosf(Rads);
    return Result;
}

ak_f64 AK_Cos(ak_f64 Rads)
{
    ak_f64 Result = cos(Rads);
    return Result;
}

ak_f32 AK_Tan(ak_f32 Rads)
{
    ak_f32 Result = tanf(Rads);
    return Result;
}

ak_f64 AK_Tan(ak_f64 Rads)
{
    ak_f64 Result = tan(Rads);
    return Result;
}

ak_f32 AK_ATan2(ak_f32 A, ak_f32 B)
{
    ak_f32 Result = atan2f(A, B);
    return Result;
}

ak_f32 AK_ASin(ak_f32 Rads)
{
    ak_f32 Result = asinf(Rads);
    return Result;
}

ak_f32 AK_Sqrt(ak_f32 Value)
{
    ak_f32 Result;
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(Value)));    
#else
    AK_NotImplemented();    
#endif    
    return Result;
}

ak_f64 AK_Sqrt(ak_f64 Value)
{
    ak_f64 Result;        
#ifdef AK_MSVC_COMPILER
    Result = _mm_cvtsd_f64(_mm_sqrt_pd(_mm_set_sd(Value)));
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_f32 AK_Pow(ak_f32 Value, ak_f32 Exp)
{
    ak_f32 Result = powf(Value, Exp);
    return Result;
}

ak_i32 AK_AtomicAdd32(ak_i32 volatile* Value, ak_i32 Addend)
{
    ak_i32 Result;
#ifdef AK_MSVC_COMPILER
    Result = _InterlockedExchangeAdd((long volatile*)Value, Addend);
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_i64 AK_AtomicAdd64(ak_i64 volatile* Value, ak_i64 Addend)
{
    ak_i64 Result;
#ifdef AK_MSVC_COMPILER
    Result = _InterlockedExchangeAdd64((ak_i64 volatile*)Value, Addend);
#else
    AK_NotImplemented();
#endif
    return Result;
}

ak_f32 AK_Frac(ak_f32 Value)
{
    ak_f32 IntPart;
    return modff(Value, &IntPart);
}