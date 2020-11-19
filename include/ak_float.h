#ifndef AK_FLOAT_H
#define AK_FLOAT_H

#undef AK_EPSILON32
#undef AK_MIN32
#undef AK_MAX32

#undef AK_EPSILON64
#undef AK_MIN64
#undef AK_MAX64

#define AK_EPSILON32 1.192092896e-07F
#define AK_MIN32 1.175494351e-38F
#define AK_MAX32 3.402823466e+38F

#define AK_EPSILON64 2.2204460492503131e-016
#define AK_MIN64 2.2250738585072014e-308
#define AK_MAX64 1.7976931348623158e+30

ak_f32  AK_RoundPrecision(ak_f32 Value, ak_u32 X);
ak_bool AK_EqualApprox(ak_f32 A, ak_f32 Eps);
ak_bool AK_EqualApprox(ak_f64 A, ak_f64 Eps);
ak_bool AK_EqualZeroEps(ak_f32 V);
ak_bool AK_EqualZeroEps(ak_f64 V);
ak_bool AK_EqualEps(ak_f32 A, ak_f32 B);
ak_bool AK_EqualEps(ak_f64 A, ak_f64 B);
ak_bool AK_IsNan(ak_f32 V);

#endif