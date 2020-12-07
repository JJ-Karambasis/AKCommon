ak_u32 AK_SafeAddrToU32(ak_uaddr Value)
{
    if(sizeof(ak_uaddr) == 8)
        return AK_SafeU32((ak_u64)Value);
    else if(sizeof(ak_uaddr) == 4)
        return (ak_u32)Value;
    AK_INVALID_ELSE;
}

ak_u16 AK_SafeU16(ak_u32 Value)
{
    AK_Assert(Value <= 0xFFFF, "32 bit unsigned integer value is out of range to convert to 16 bit unsigned integer");
    return (ak_u16)Value;
}

ak_u32 AK_SafeU32(ak_u64 Value)
{
    AK_Assert(Value <= 0xFFFFFFFF, "64 bit unsigned integer value is out of range to convert to 32 bit unsigned integer");
    return (ak_u32)Value;
}

ak_i32 AK_SafeI32(ak_i64 Value)
{
    AK_Assert((Value >= AK_INT_MIN) && (Value <= AK_INT_MAX), "64 bit signed integer value is out of range to convert to 32 signed bit integer");
    return (ak_i32)Value;
}

ak_f32 AK_SafeRatio(ak_i32 Numerator, ak_i32 Denominator)
{
    AK_Assert(Denominator != 0, "Denomiator cannot be zero. Value will become infinity");
    ak_f32 Result = (ak_f32)Numerator/(ak_f32)Denominator;
    return Result;
}

ak_f32 AK_SafeRatio(ak_v2i Fraction)
{
    return AK_SafeRatio(Fraction.w, Fraction.h);
}

ak_f32 AK_SafeInverse(ak_f32 A)
{
    AK_Assert(!AK_EqualZeroEps(A), "Cannot take the inverse of a value that is zero (or extremely close too).");    
    return 1.0f/A;
}

ak_u64 AK_BijectiveMap(ak_u32 A, ak_u32 B)
{
    ak_u64 Result = (A >= B) ? A*A + A + B : A + B*B;
    return Result;
}

ak_i64 AK_BijectiveMap(ak_i32 A, ak_i32 B)
{
    ak_i64 Result = (A >= B) ? A*A + A + B : A + B*B;
    return Result;
}

ak_bool AK_EqualSign(ak_f32 a, ak_f32 b)
{
    ak_bool Result = (a >= 0) ^ (b < 0);
    return Result;
}

global ak_u64 AK_Internal__Seed64 = (ak_u64)-1;
global ak_u32 AK_Internal__Seed32 = (ak_u32)-1;

void AK_SetRandomSeed64(ak_u64 Seed)
{
    AK_Internal__Seed64 = Seed;
}

void AK_SetRandomSeed32(ak_u32 Seed)
{
    AK_Internal__Seed32 = Seed;
}

void AK_SetRandomSeed64()
{
#ifdef AK_WINDOWS
    LARGE_INTEGER Seed;
    QueryPerformanceCounter(&Seed);
    AK_SetRandomSeed64(Seed.QuadPart);
#else
    AK_NotImplemented();
#endif
}

void AK_SetRandomSeed32()
{
#ifdef AK_WINDOWS
    LARGE_INTEGER Seed;
    QueryPerformanceCounter(&Seed);
    AK_SetRandomSeed32(Seed.LowPart);
#else
    AK_NotImplemented();
#endif
}

//NOTE(EVERYONE): Random number generator based on Xorshift
//https://en.wikipedia.org/wiki/Xorshift
ak_u64 AK_Random64()
{
    if(AK_Internal__Seed64 == (ak_u64)-1)
        AK_SetRandomSeed64();
    
    ak_u64 Result = AK_Internal__Seed64;
    Result ^= Result << 13;
    Result ^= Result >> 7;
    Result ^= Result << 17;
    AK_Internal__Seed64 = Result;
    return Result;
}

ak_u32 AK_Random32()
{
    if(AK_Internal__Seed32 == (ak_u32)-1)
        AK_SetRandomSeed32();
    ak_u32 Result = AK_Internal__Seed32;
    Result ^= Result << 13;
    Result ^= Result >> 17;
    Result ^= Result << 5;
    AK_Internal__Seed32 = Result;
    return Result;
}

ak_f32 AK_RandomF32()
{
    return ((ak_f32)AK_Random32()) * (1.0f/4294967296.f);
}

ak_iaddr AK_AlignTo(ak_uaddr V, ak_uaddr Alignment)
{
    Alignment = Alignment ? Alignment : 1;
    ak_uaddr Mod = V & (Alignment-1);
    return Mod ? V + (Alignment-Mod) : V;
}