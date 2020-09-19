#ifndef AK_UTIL_H
#define AK_UTIL_H

template <typename type>
struct ak_pair
{
    type A;
    type B;
};

ak_u32 AK_SafeAddrToU32(ak_uaddr Value);
ak_u16 AK_SafeU16(ak_u32 Value);
ak_u32 AK_SafeU32(ak_u64 Value);
ak_i32 AK_SafeI32(ak_i64 Value);
ak_f32 AK_SafeRatio(ak_i32 Numerator, ak_i32 Denominator);
ak_f32 AK_SafeInverse(ak_f32 A);
ak_u64 AK_BijectiveMap(ak_u32 A, ak_u32 B);
ak_i64 AK_BijectiveMap(ak_i32 A, ak_i32 B);
ak_bool AK_EqualSign(ak_f32 a, ak_f32 b);
void AK_SetRandomSeed64(ak_u64 Seed);
void AK_SetRandomSeed32(ak_u32 Seed);
ak_u64 AK_Random64();
ak_u32 AK_Random32();

#endif