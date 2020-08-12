#ifndef MATH_H
#define MATH_H

#define PI 3.14159265359f
#define INV_PI 0.31830988618f
#define SQRT2_2 0.70710678118f

#define TO_DEGREE(rad) (rad * 180.0f * INV_PI)
#define TO_RAD(degree) (degree * PI / 180.0f)

inline f32 Sin(f32 Rads)
{
    f32 Result = sinf(Rads);
    return Result;
}

inline f32 Cos(f32 Rads)
{
    f32 Result = cosf(Rads);
    return Result;
} 

inline f32 Tan(f32 Rads)
{
    f32 Result = tanf(Rads);
    return Result;
}

inline f32 ACos(f32 Rads)
{
    f32 Result = acosf(Rads);
    return Result;
}

inline f32 Exp(f32 Value)
{
    f32 Result = expf(Value);
    return Result;
}

inline f32 Pow(f32 Value, f32 Exp)
{
    f32 Result = powf(Value, Exp);
    return Result;
}

inline f32 Sqrt(f32 Value)
{
    f32 Result;
#if MSVC_COMPILER
    Result = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(Value)));    
#else
    Result = sqrtf(Value);    
#endif
    
    return Result;
}

inline f32 RSqrt(f32 Value)
{
    //IMPORTANT(JJ): Probably don't want the intrinsic to handle the divide by 0 but I want to determine where these happen first and what the intrinsic will return (NAN or infinity?)    
    f32 Result;
#if MSVC_COMPILER        
    Result = _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(Value)));
#else    
    Result = 1.0f/Sqrt(Value);    
#endif
    
    ASSERT(Result != INFINITY);
    return Result;
}

inline f32 Lerp(f32 A, f32 t, f32 B)
{
    f32 Result = (1-t)*A + t*B;
    return Result;
}

struct v2i
{
    union
    {        
        struct
        {
            i32 x;
            i32 y;
        };
        
        struct
        {
            i32 width;
            i32 height;
        };
    };
};

inline v2i V2i(i32 x, i32 y)
{
    v2i Result = {x, y};
    return Result;
}

inline v2i V2i(f32 x, f32 y)
{
    v2i Result = {(i32)x, (i32)y};
    return Result;
}

inline v2i operator+(v2i Left, i32 Right)
{
    v2i Result = {Left.x+Right, Left.y+Right};
    return Result;
}

inline v2i operator+(v2i Left, v2i Right)
{
    v2i Result = {Left.x+Right.x, Left.y+Right.y};
    return Result;
}

inline v2i& 
operator+=(v2i& Left, i32 Right)
{
    Left = Left + Right;
    return Left;
}

inline v2i 
operator-(v2i Left, i32 Right)
{
    v2i Result = {Left.x-Right, Left.y-Right};
    return Result;
}

inline v2i& 
operator-=(v2i& Left, i32 Right)
{
    Left = Left - Right;
    return Left;
}

inline v2i 
operator-(v2i Left, v2i Right)
{
    v2i Result = {Left.x-Right.x, Left.y-Right.y};
    return Result;
}

inline v2i 
operator/(v2i Left, i32 Right)
{
    v2i Result = {Left.x/Right, Left.y/Right};
    return Result;
}

inline b32 operator!=(v2i Left, v2i Right)
{
    b32 Result = (Left.x != Right.x) || (Left.y != Right.y);
    return Result;
}

inline b32 operator!=(v2i Left, i32 Right)
{
    b32 Result = (Left.x != Right) || (Left.y != Right);
    return Result;
}

inline b32 operator==(v2i Left, v2i Right)
{
    b32 Result = (Left.x == Right.x) && (Left.y == Right.y);
    return Result;
}

inline b32 operator<(v2i Left, v2i Right)
{
    b32 Result = (Left.x < Right.x) && (Left.y < Right.y);
    return Result;
}

inline b32 operator>=(v2i Left, i32 Right)
{
    b32 Result = (Left.x >= Right) && (Left.y >= Right);
    return Result;
}

inline v2i MinimumV2(v2i Left, v2i Right)
{
    v2i Result;
    Result.x = MinimumI32(Left.x, Right.x);
    Result.y = MinimumI32(Left.y, Right.y);
    return Result;
}

inline v2i MaximumV2(v2i Left, v2i Right)
{
    v2i Result;
    Result.x = MaximumI32(Left.x, Right.x);
    Result.y = MaximumI32(Left.y, Right.y);
    return Result;
}

struct v2f
{
    union
    {
        struct
        {
            f32 x;
            f32 y;           
        };
        
        struct
        {
            f32 width;
            f32 height;
        };
    };
};

inline v2i Round2i(v2f V)
{
    v2i Result = {RoundI32(V.x), RoundI32(V.y)};
    return Result;
}

inline v2f RoundPrecisionMag2f(v2f V, u32 X)
{
    v2f Result = {RoundPrecisionMag(V.x, X), RoundPrecisionMag(V.y, X)};
    return Result;
}

inline v2f RoundPrecision(v2f V, u32 Precision)
{
    u32 X = GetPrecision(Precision);
    v2f Result = RoundPrecisionMag2f(V, X);
    return Result;
}

inline v2f
InvalidV2()
{
    v2f Result = {INFINITY, INFINITY};
    return Result;
}

inline v2f 
V2()
{
    v2f Result = {};
    return Result;
}

inline v2f 
V2(i32 x, i32 y)
{
    v2f Result = {(f32)x, (f32)y};
    return Result;
}

inline v2f 
V2(v2i V)
{
    v2f Result = V2(V.x, V.y);
    return Result;
}

inline v2f 
V2(f32 x, f32 y)
{
    v2f Result = {x, y};
    return Result;
}

inline v2f
V2(f32* V)
{
    v2f Result = V2(V[0], V[1]);
    return Result;
}

inline v2f
V2(f64* V)
{
    v2f Result = V2((f32)V[0], (f32)V[1]);
    return Result;
}

inline v2f
operator+(v2f Left, f32 Right)
{
    v2f Result = {Left.x+Right, Left.y+Right};
    return Result;
}

inline v2f
operator+(v2f Left, v2f Right)
{
    v2f Result = {Left.x+Right.x, Left.y+Right.y};
    return Result;
}

inline v2f& 
operator+=(v2f& Left, f32 Right)
{
    Left = Left + Right;
    return Left;
}

inline v2f&
operator+=(v2f& Left, v2f Right)
{
    Left = Left + Right;
    return Left;
}

inline v2f
operator-(f32 Left, v2f Right)
{
    v2f Result = {Left-Right.x, Left-Right.y};
    return Result;
}

inline v2f
operator-(v2f Left, f32 Right)
{
    v2f Result = {Left.x-Right, Left.y-Right};
    return Result;
}

inline v2f
operator-(v2f Left, v2f Right)
{
    v2f Result = {Left.x-Right.x, Left.y-Right.y};
    return Result;
}

inline v2f& 
operator-=(v2f& Left, f32 Right)
{
    Left = Left - Right;
    return Left;
}

inline v2f&
operator-=(v2f& Left, v2f Right)
{
    Left = Left - Right;
    return Left;
}

inline v2f 
operator*(v2f Left, f32 Right)
{
    v2f Result = {Left.x*Right, Left.y*Right};
    return Result;
}

inline v2f 
operator*(f32 Left, v2f Right)
{
    v2f Result = Right*Left;
    return Result;
}

inline v2f
operator*(v2i Left, f32 Right)
{
    v2f Result = {Left.x*Right, Left.y*Right};
    return Result;
}

inline v2f&
operator*=(v2f& Left, f32 Right)
{
    Left = Left * Right;
    return Left;
}

inline v2f 
operator*(v2f Left, v2f Right)
{
    v2f Result = {Left.x*Right.x, Left.y*Right.y};
    return Result;
}

inline v2f&
operator*=(v2f& Left, v2f Right)
{
    Left = Left * Right;
    return Left;
}

inline v2f
operator/(v2f V, f32 Right)
{
    v2f Result = {V.x/Right, V.y/Right};
    return Result;
}

inline v2f&
operator/=(v2f& V, f32 Right)
{
    V = V / Right;
    return V;
}

inline v2f
operator/(f32 Left, v2f Right)
{
    v2f Result = {Left/Right.x, Left/Right.y};
    return Result;
}

inline v2f 
operator/(v2f Left, v2f Right)
{
    v2f Result = {Left.x/Right.x, Left.y/Right.y};
    return Result;
}

inline v2f
Negate(v2f V)
{
    v2f Result = {-V.x, -V.y};
    return Result;
}

inline v2f
operator-(v2f V)
{
    v2f Result = Negate(V);
    return Result;
}

inline b32 operator!=(v2f Left, f32 Right)
{
    b32 Result = (Left.x != Right) || (Left.y != Right);
    return Result;
}

inline b32 operator!=(v2f Left, v2f Right)
{
    b32 Result = (Left.x != Right.x) || (Left.y != Right.y);
    return Result;
}

inline b32 operator==(v2f Left, v2f Right)
{
    b32 Result = (Left.x == Right.x) && (Left.y == Right.y);
    return Result;
}

inline b32 operator<(v2f Left, v2f Right)
{
    b32 Result = (Left.x < Right.x) && (Left.y < Right.y);
    return Result;
}

inline b32 operator<=(v2f Left, v2f Right)
{
    b32 Result = (Left.x <= Right.x) && (Left.y <= Right.y);
    return Result;
}

inline b32 operator>=(v2f Left, f32 Right)
{
    b32 Result = (Left.x >= Right) && (Left.y >= Right);
    return Result;
}

inline b32 operator>=(v2f Left, v2f Right)
{
    b32 Result = (Left.x >= Right.x) && (Left.y >= Right.y);
    return Result;
}

inline v2f Abs2f(v2f V)
{
    v2f Result = {Abs(V.x), Abs(V.y)};
    return Result;
}

inline f32
Dot(v2f Left, v2f Right)
{
    f32 Result = Left.x*Right.x + Left.y*Right.y;
    return Result;
}

inline f32
DotEpsilon(v2f Left, v2f Right)
{
    f32 Result = 2.0f * FLT_EPSILON * Dot(Abs2f(Left), Abs2f(Right));
    return Result;
}

inline f32 
SquareMagnitude(v2f V)
{
    f32 Result = Dot(V, V);
    return Result;
}

inline f32
Magnitude(v2f V)
{
    f32 Result = Sqrt(SquareMagnitude(V));
    return Result;
}

inline f32
InverseMagnitude(v2f V)
{
    f32 Result = RSqrt(SquareMagnitude(V));
    return Result;
}

inline v2f
Normalize(v2f V)
{
    f32 InvMag = 1.0f/Magnitude(V);
    v2f Result = InvMag*V;
    return Result;
}

inline v2f
Perp(v2f V)
{
    v2f Result = {V.y, -V.x};
    return Result;
}

inline v2f
PerpCCW(v2f V)
{
    v2f Result = {-V.y, V.x};
    return Result;
}

inline f32
Cross2D(v2f Left, v2f Right)
{
    f32 Result = Left.y*Right.x - Left.x*Right.y;
    return Result;
}

inline v2i 
FloorV2(v2f Value)
{
    v2i Result;
    Result.x = FloorI32(Value.x);
    Result.y = FloorI32(Value.y);
    return Result;
}

inline b32
AreEqual(v2f P0, v2f P1, f32 Epsilon)
{
    b32 Result = SquareMagnitude(P0-P1) < Epsilon;
    return Result;
}

struct v3f
{
    union
    {        
        struct 
        {
            f32 x;
            f32 y;
            f32 z;            
        };
        
        struct 
        {
            f32 r;
            f32 g;
            f32 b;            
        };
        
        struct
        {
            f32 pitch;
            f32 yaw;
            f32 roll;
        };
        
        struct
        {
            v2f xy;
            f32 __unused_0__;
        };
        
        struct
        {
            f32 __unused_1__;
            v2f yz;
        };        
    };
};

const global v3f Global_WorldXAxis = {1.0f, 0.0f, 0.0f};
const global v3f Global_WorldYAxis = {0.0f, 1.0f, 0.0f};
const global v3f Global_WorldZAxis = {0.0f, 0.0f, 1.0f};

inline v3f
V3()
{
    v3f Result = {};
    return Result;
}

inline v3f
V3(f32 Value)
{
    v3f Result = {Value, Value, Value};
    return Result;
}

inline v3f 
V3(v2f v)
{
    v3f Result = {v.x, v.y};
    return Result;
}

inline v3f 
V3(v2f xy, f32 z)
{
    v3f Result = {xy.x, xy.y, z};
    return Result;
}

inline v3f 
V3(f32 x, v2f yz)
{
    v3f Result = {x, yz.x, yz.y};
    return Result;
}

inline v3f 
V3(f32 x, f32 y, f32 z)
{
    v3f Result;
    Result.x = x;
    Result.y = y;
    Result.z = z;
    return Result;
}

inline v3f
V3(f32* V)
{
    v3f Result = V3(V[0], V[1], V[2]);
    return Result;
}

inline v3f
V3(f64* V)
{
    v3f Result = V3((f32)V[0], (f32)V[1], (f32)V[2]);
    return Result;
}

inline v3f
V3(const f64* V)
{
    v3f Result = V3((f32)V[0], (f32)V[1], (f32)V[2]);
    return Result;
}

inline v3f
InvalidV3()
{
    v3f Result = {INFINITY, INFINITY, INFINITY};
    return Result;
}

inline b32 
IsInvalidV3(v3f V)
{
    b32 Result = ((V.x == INFINITY) || (V.y == INFINITY) || (V.z == INFINITY));
    return Result;
}

inline v3f
operator+(v3f Left, v3f Right)
{
    v3f Result;
    Result.x = Left.x + Right.x;
    Result.y = Left.y + Right.y;
    Result.z = Left.z + Right.z;
    return Result;
}

inline v3f
operator+(v3f Left, f32 Right)
{
    v3f Result;
    Result.x = Left.x + Right;
    Result.y = Left.y + Right;
    Result.z = Left.z + Right;
    return Result;
}

inline v3f&
operator+=(v3f& Left, v3f Right)
{
    Left = Left + Right;    
    return Left;
}

inline v3f
operator-(v3f Left, v3f Right)
{
    v3f Result;
    Result.x = Left.x - Right.x;
    Result.y = Left.y - Right.y;
    Result.z = Left.z - Right.z;
    return Result;
}

inline v3f
operator-(v3f Left, f32 Right)
{
    v3f Result;
    Result.x = Left.x - Right;
    Result.y = Left.y - Right;
    Result.z = Left.z - Right;
    return Result;
}

inline v3f&
operator-=(v3f& Left, v3f Right)
{
    Left = Left - Right;
    return Left;
}

inline v3f 
operator*(v3f Left, f32 Right)
{
    v3f Result;
    Result.x = Left.x * Right;
    Result.y = Left.y * Right;
    Result.z = Left.z * Right;
    return Result;
}

inline v3f 
operator*(f32 Left, v3f Right)
{
    v3f Result = Right*Left;    
    return Result;
}

inline v3f&
operator*=(v3f& Left, f32 Right)
{
    Left = Left * Right;
    return Left;
}

inline v3f 
operator*(v3f Left, v3f Right)
{
    v3f Result;
    Result.x = Left.x * Right.x;
    Result.y = Left.y * Right.y;
    Result.z = Left.z * Right.z;
    return Result;
}

inline v3f&
operator*=(v3f& Left, v3f Right)
{
    Left = Left * Right;
    return Left;
}

inline v3f 
operator/(v3f Left, v3f Right)
{
    v3f Result;
    Result.x = Left.x / Right.x;
    Result.y = Left.y / Right.y;
    Result.z = Left.z / Right.z;
    return Result;
}

inline v3f
operator/(v3f V, f32 Right)
{
    v3f Result = {V.x/Right, V.y/Right, V.z/Right};
    return Result;
}

inline v3f
operator/(f32 Left, v3f Right)
{
    v3f Result = {Left/Right.x, Left/Right.y, Left/Right.z};
    return Result;
}

inline v3f&
operator/=(v3f& Left, f32 Right)
{
    Left = Left/Right;
    return Left;
}

inline v3f&
operator/=(v3f& Left, v3f Right)
{
    Left = Left/Right;
    return Left;
}

inline v3f 
operator-(v3f V)
{
    v3f Result = {-V.x, -V.y, -V.z};
    return Result;
}

inline b32 operator==(v3f Left, v3f Right)
{
    b32 Result = (Left.x == Right.x) && (Left.y == Right.y) && (Left.z == Right.z);
    return Result;
}

inline b32 operator!=(v3f Left, v3f Right)
{
    b32 Result = (Left.x != Right.x) || (Left.y != Right.y) || (Left.z != Right.z);
    return Result;
}

inline b32 operator<=(v3f Left, v3f Right)
{
    b32 Result = (Left.x <= Right.x) && (Left.y <= Right.y) && (Left.z <= Right.z);
    return Result;
}

inline b32 operator>=(v3f Left, v3f Right)
{
    b32 Result = (Left.x >= Right.x) && (Left.y >= Right.y) && (Left.z >= Right.z);
    return Result;
}

inline f32
Dot(v3f Left, v3f Right)
{
    f32 Result = Left.x*Right.x + Left.y*Right.y + Left.z*Right.z;
    return Result;
}

inline v3f 
Cross(v3f Left, v3f Right)
{
    v3f Result = {Left.y*Right.z - Left.z*Right.y, Left.z*Right.x - Left.x*Right.z, Left.x*Right.y - Left.y*Right.x};
    return Result;
}

inline f32 
SquareMagnitude(v3f V)
{
    f32 Result = Dot(V, V);
    return Result;
}

inline f32
Magnitude(v3f V)
{
    f32 SqrLength = SquareMagnitude(V);
    if(SqrLength == 0)
        return 0;
    
    f32 Result = Sqrt(SqrLength);
    return Result;
}

inline f32
InverseMagnitude(v3f V)
{   
    f32 Length = Magnitude(V);
    if(Length == 0)
        return 0;
    
    f32 Result = 1.0f/Length;
    return Result;
}

inline v3f
Normalize(v3f V)
{
    f32 InvMag = InverseMagnitude(V);
    v3f Result = InvMag*V;
    return Result;
}

inline f32
Determinant(v3f U, v3f V, v3f W)
{
    f32 Result = Dot(U, Cross(V, W));
    return Result;
}

inline v3f
Lerp(v3f A, f32 t, v3f B)
{
    v3f Result = V3(Lerp(A.x, t, B.x),
                    Lerp(A.y, t, B.y),
                    Lerp(A.z, t, B.z));
    return Result;
}

inline b32
AreEqual(v3f P0, v3f P1, f32 Epsilon)
{
    b32 Result = SquareMagnitude(P0-P1) < Epsilon;
    return Result;
}

#ifdef RGB
#undef RGB
#endif

inline v3f
RGB(f32 r, f32 g, f32 b)
{
    v3f Result = V3(r, g, b);
    return Result;
}

inline v3f White3()
{
    v3f Result = RGB(1.0f, 1.0f, 1.0f);
    return Result;
}

inline v3f Red3()
{
    return RGB(1.0f, 0.0f, 0.0f);
}

inline v3f Green3()
{
    v3f Result = RGB(0.0f, 1.0f, 0.0f);
    return Result;
}

inline v3f Blue3()
{    
    return RGB(0.0f, 0.0f, 1.0f);
}

inline v3f Yellow3()
{
    v3f Result = RGB(1.0f, 1.0f, 0.0f);
    return Result;
}

inline v3f Black3()
{
    v3f Result = RGB(0.0f, 0.0f, 0.0f);
    return Result;
}

inline v3f Cyan3()
{
    v3f Result = RGB(0.0f, 1.0f, 1.0f);
    return Result;
}

inline v3f Magenta3()
{
    v3f Result = RGB(1.0f, 0.0f, 1.0f);
    return Result;
}

typedef v3f c3;

struct v4f
{
    union
    {        
        struct
        {
            f32 x;
            f32 y;
            f32 z;
            f32 w;
        };        
        
        struct
        {
            v2f xy;
            v2f zw;
        };
        
        struct
        {
            v3f xyz;
            f32 __unused_0__;
        };
        struct
        {
            f32 __unused_1__;
            v3f yzw;
        };
        
        struct
        {
            f32 r;
            f32 g;
            f32 b;
            f32 a;
        };
    };
};

inline v3f
V3(v4f V)
{
    v3f Result = V.xyz;
    return Result;
}

inline v4f 
V4(f32 x, f32 y, f32 z, f32 w)
{
    v4f Result;
    Result.x = x;
    Result.y = y;
    Result.z = z;
    Result.w = w;
    return Result;
}

inline v4f 
V4(v2f xy, f32 z, f32 w)
{
    v4f Result;
    Result.xy = xy;    
    Result.z = z;
    Result.w = w;
    return Result;
}

inline v4f 
V4(f32* xyz, f32 w)
{
    v4f Result = V4(xyz[0], xyz[1], xyz[2], w);    
    return Result;
}

inline v4f 
V4(f64* xyz, f32 w)
{
    v4f Result = V4((f32)xyz[0], (f32)xyz[1], (f32)xyz[2], w);    
    return Result;
}

inline v4f 
V4(v3f xyz, f32 w)
{
    v4f Result;
    Result.xyz = xyz;    
    Result.w = w;
    return Result;
}

inline v4f 
operator*(f32 Left, v4f Right)
{
    v4f Result = {Left*Right.x, Left*Right.y, Left*Right.z, Left*Right.w};
    return Result;
}

inline f32
Dot(v4f Left, v4f Right)
{
    f32 Result = Left.x*Right.x + Left.y*Right.y + Left.z*Right.z + Left.w*Right.w;
    return Result;
}

inline f32 
SquareMagnitude(v4f V)
{
    f32 Result = Dot(V, V);
    return Result;
}

inline f32
Magnitude(v4f V)
{
    f32 Result = Sqrt(SquareMagnitude(V));
    return Result;
}

inline f32
InverseMagnitude(v4f V)
{    
    f32 Result = 1.0f/Magnitude(V);
    return Result;
}

inline v4f
Normalize(v4f V)
{
    f32 InvMag = InverseMagnitude(V);
    v4f Result = InvMag*V;
    return Result;
}

inline v4f 
RGBA(f32 r, f32 g, f32 b, f32 a)
{
    v4f Result = V4(r, g, b, a);
    return Result;
}

inline v4f White4()
{
    v4f Result = RGBA(1.0f, 1.0f, 1.0f, 1.0f);
    return Result;
}

global v4f Global_Red = RGBA(1.0f, 0.0f, 0.0f, 1.0f);
inline v4f Red4()
{
    return Global_Red;
}

inline v4f Green4()
{
    v4f Result = RGBA(0.0f, 1.0f, 0.0f, 1.0f);
    return Result;
}

global v4f Global_Blue = RGBA(0.0f, 0.0f, 1.0f, 0.0f);
inline v4f Blue4()
{    
    return Global_Blue;
}

inline v4f Yellow4()
{
    v4f Result = RGBA(1.0f, 1.0f, 0.0f, 1.0f);
    return Result;
}

inline v4f Black4()
{
    v4f Result = RGBA(0.0f, 0.0f, 0.0f, 1.0f);
    return Result;
}

inline v4f Cyan4()
{
    v4f Result = RGBA(0.0f, 1.0f, 1.0f, 1.0f);
    return Result;
}

inline v4f Magenta4()
{
    v4f Result = RGBA(1.0f, 0.0f, 1.0f, 1.0f);
    return Result;
}

typedef v4f c4;

struct m3
{
    union
    {
        f32 M[9];
        v3f Rows[3];
        struct
        {
            f32 m00, m01, m02;
            f32 m10, m11, m12;
            f32 m20, m21, m22;            
        };
        
        struct
        {
            v3f Row0;
            v3f Row1;
            v3f Row2;            
        };
        
        struct
        {
            v3f XAxis;
            v3f YAxis;
            v3f ZAxis;            
        };
    };
};

inline m3
M3(f32 Diagonal)
{
    m3 Result = {};
    Result.m00 = Diagonal;
    Result.m11 = Diagonal;
    Result.m22 = Diagonal;
    return Result;
}

inline m3
M3(v3f XAxis, v3f YAxis, v3f ZAxis)
{
    m3 Result;
    Result.XAxis = XAxis;
    Result.YAxis = YAxis;
    Result.ZAxis = ZAxis;    
    return Result;
}

void CreateBasis(v3f Z, v3f* X, v3f* Y)
{
    Z = Normalize(Z);
    *X = -Cross(Z, Global_WorldYAxis);
    if((Abs(X->x) < 1e-6f) && (Abs(X->y) < 1e-6f) && (Abs(X->z) < 1e-6f))    
        *X = -Cross(Z, Global_WorldZAxis);   
    
    *X = Normalize(*X);
    *Y = Cross(Z, *X);        
}

m3 CreateBasis(v3f Z)
{
    v3f X, Y;
    CreateBasis(Z, &X, &Y);    
    return M3(X, Y, Z);
}

inline m3
IdentityM3()
{
    m3 Result = M3(1.0f);
    return Result;
}

inline f32
Determinant(m3 M)
{
    f32 Result = Determinant(M.XAxis, M.YAxis, M.ZAxis);
    return Result;
}

inline m3
Transpose(m3 M)
{
    m3 Result;
    Result.m00 = M.m00;
    Result.m01 = M.m10;
    Result.m02 = M.m20;
    Result.m10 = M.m01;
    Result.m11 = M.m11;
    Result.m12 = M.m21;
    Result.m20 = M.m02;
    Result.m21 = M.m12;
    Result.m22 = M.m22;
    return Result;
}

inline m3
InverseTransformM3(m3 M)
{
    f32 sx = 1.0f/SquareMagnitude(M.XAxis);
    f32 sy = 1.0f/SquareMagnitude(M.YAxis);
    f32 sz = 1.0f/SquareMagnitude(M.ZAxis);
    
    v3f x = sx*M.XAxis;
    v3f y = sy*M.YAxis;
    v3f z = sz*M.ZAxis;
    
    m3 Result = 
    {
        x.x, y.x, z.x,
        x.y, y.y, z.y,
        x.z, y.z, z.z,        
    };
    
    return Result;
}

inline v3f
operator*(v3f Left, m3 Right)
{
    Right = Transpose(Right);
    
    v3f Result;
    Result.x = Dot(Left, Right.Rows[0]);
    Result.y = Dot(Left, Right.Rows[1]);
    Result.z = Dot(Left, Right.Rows[2]);
    
    return Result;
}

inline v3f&
operator*=(v3f& Left, m3 Right)
{
    Left = Left*Right;    
    return Left;
}

inline m3
operator*(m3 Left, m3 Right)
{
    Right = Transpose(Right);
    m3 Result;
    
    Result.m00 = Dot(Left.Rows[0], Right.Rows[0]);
    Result.m01 = Dot(Left.Rows[0], Right.Rows[1]);
    Result.m02 = Dot(Left.Rows[0], Right.Rows[2]);
    Result.m10 = Dot(Left.Rows[1], Right.Rows[0]);
    Result.m11 = Dot(Left.Rows[1], Right.Rows[1]);
    Result.m12 = Dot(Left.Rows[1], Right.Rows[2]);
    Result.m20 = Dot(Left.Rows[2], Right.Rows[0]);
    Result.m21 = Dot(Left.Rows[2], Right.Rows[1]);
    Result.m22 = Dot(Left.Rows[2], Right.Rows[2]);
    return Result;
}

inline m3
XRot(f32 Angle)
{
    m3 Result = IdentityM3();
    f32 c = Cos(Angle);
    f32 s = Sin(Angle);
    
    Result.m11 =  c;
    Result.m12 =  s;
    Result.m21 = -s;
    Result.m22 =  c;
    return Result;
}

inline m3 
YRot(f32 Angle)
{
    m3 Result = IdentityM3();
    
    f32 c = Cos(Angle);
    f32 s = Sin(Angle);
    
    Result.m00 =  c;
    Result.m02 = -s;
    Result.m20 =  s;
    Result.m22 =  c;
    return Result;
}

inline m3 
ZRot(f32 Angle)
{
    m3 Result = IdentityM3();
    
    f32 c = Cos(Angle);
    f32 s = Sin(Angle);
    
    Result.m00 =  c;
    Result.m01 =  s;
    Result.m10 = -s;
    Result.m11 =  c;    
    return Result;
}

inline m3& 
operator*=(m3& Left, m3 Right)
{
    Left = Left*Right;
    return Left;
}

struct m4
{
    union
    {
        f32 M[16];
        v4f Rows[4];
        struct
        {
            f32 m00, m01, m02, m03;
            f32 m10, m11, m12, m13;
            f32 m20, m21, m22, m23;
            f32 m30, m31, m32, m33;
        };
        
        struct
        {
            v4f Row0;
            v4f Row1;
            v4f Row2;
            v4f Row3;
        };
        
        struct
        {
            v4f XAxis;
            v4f YAxis;
            v4f ZAxis;
            v4f Translation;
        };
    };
};

inline m3
M3(m4 M)
{
    m3 Result;
    Result.XAxis = M.XAxis.xyz;
    Result.YAxis = M.YAxis.xyz;
    Result.ZAxis = M.ZAxis.xyz;
    return Result;
}

inline m4
M4(f32* Data)
{
    m4 Result = 
    {
        Data[0],  Data[1],  Data[2],  Data[3],
        Data[4],  Data[5],  Data[6],  Data[7],
        Data[8],  Data[9],  Data[10], Data[11],
        Data[12], Data[13], Data[14], Data[15]
    };    
    
    return Result;
}

inline m4
M4(f64* Data)
{
    m4 Result = 
    {
        (f32)Data[0],  (f32)Data[1],  (f32)Data[2],  (f32)Data[3],
        (f32)Data[4],  (f32)Data[5],  (f32)Data[6],  (f32)Data[7],
        (f32)Data[8],  (f32)Data[9],  (f32)Data[10], (f32)Data[11],
        (f32)Data[12], (f32)Data[13], (f32)Data[14], (f32)Data[15]
    };    
    
    return Result;
}

inline m4
M4(f32 Diagonal)
{
    m4 Result = {};
    Result.m00 = Diagonal;
    Result.m11 = Diagonal;
    Result.m22 = Diagonal;
    Result.m33 = Diagonal;
    return Result;
}

inline m4
IdentityM4()
{
    m4 Result = M4(1.0f);
    return Result;
}

inline m4
Transpose(m4 M)
{
    m4 Result;
    Result.m00 = M.m00;
    Result.m01 = M.m10;
    Result.m02 = M.m20;
    Result.m03 = M.m30;
    Result.m10 = M.m01;
    Result.m11 = M.m11;
    Result.m12 = M.m21;
    Result.m13 = M.m31;
    Result.m20 = M.m02;
    Result.m21 = M.m12;
    Result.m22 = M.m22;
    Result.m23 = M.m32;
    Result.m30 = M.m03;
    Result.m31 = M.m13;
    Result.m32 = M.m23;
    Result.m33 = M.m33;
    return Result;
}

inline m4 
TransformM4(v3f Position, v3f Scale)
{
    m4 Result;
    Result.XAxis = V4(Scale.x, 0.0f,    0.0f,    0.0f);
    Result.YAxis = V4(0.0f,    Scale.y, 0.0f,    0.0f);
    Result.ZAxis = V4(0.0f,    0.0f,    Scale.z, 0.0f);
    Result.Translation = V4(Position, 1.0f);
    return Result;
}

inline m4 
TransformM4(v3f Position)
{
    m4 Result = TransformM4(Position, V3(1.0f, 1.0f, 1.0f));            
    return Result;
}

inline m4
TransformM4(v3f Position, v3f XAxis, v3f YAxis, v3f ZAxis)
{
    m4 Result;
    Result.XAxis       = V4(XAxis, 0.0f);
    Result.YAxis       = V4(YAxis, 0.0f);
    Result.ZAxis       = V4(ZAxis, 0.0f);
    Result.Translation = V4(Position, 1.0f);
    return Result;
}

inline m4
TransformM4(v3f Position, m3 Orientation)
{
    m4 Result = TransformM4(Position, Orientation.XAxis, Orientation.YAxis, Orientation.ZAxis);    
    return Result;
}

inline m4 
InverseTransformM4(v3f Position, v3f XAxis, v3f YAxis, v3f ZAxis)
{
    f32 tx = -Dot(Position, XAxis);
    f32 ty = -Dot(Position, YAxis);
    f32 tz = -Dot(Position, ZAxis);
    
    m4 Result = 
    {
        XAxis.x, YAxis.x, ZAxis.x, 0.0f,
        XAxis.y, YAxis.y, ZAxis.y, 0.0f,
        XAxis.z, YAxis.z, ZAxis.z, 0.0f,
        tx,      ty,      tz,      1.0f 
    };
    
    return Result;
}

inline m4 
InverseTransformM4(v3f Position, m3 Orientation)
{
    m4 Result = InverseTransformM4(Position, Orientation.XAxis, Orientation.YAxis, Orientation.ZAxis);    
    return Result;
}

inline m4
InverseTransformM4(m4 M)
{
    f32 sx = 1.0f/SquareMagnitude(M.XAxis.xyz);
    f32 sy = 1.0f/SquareMagnitude(M.YAxis.xyz);
    f32 sz = 1.0f/SquareMagnitude(M.ZAxis.xyz);
    
    v3f x = sx*M.XAxis.xyz;
    v3f y = sy*M.YAxis.xyz;
    v3f z = sz*M.ZAxis.xyz;
    
    f32 tx = -Dot(M.Translation.xyz, x);
    f32 ty = -Dot(M.Translation.xyz, y);
    f32 tz = -Dot(M.Translation.xyz, z);
    
    m4 Result = 
    {
        x.x, y.x, z.x, 0,
        x.y, y.y, z.y, 0,
        x.z, y.z, z.z, 0,
        tx,  ty,  tz,  1
    };
    
    return Result;
}

inline m4
operator*(m4 Left, m4 Right)
{
    Right = Transpose(Right);
    m4 Result;
    
    Result.m00 = Dot(Left.Rows[0], Right.Rows[0]);
    Result.m01 = Dot(Left.Rows[0], Right.Rows[1]);
    Result.m02 = Dot(Left.Rows[0], Right.Rows[2]);
    Result.m03 = Dot(Left.Rows[0], Right.Rows[3]);
    
    Result.m10 = Dot(Left.Rows[1], Right.Rows[0]);
    Result.m11 = Dot(Left.Rows[1], Right.Rows[1]);
    Result.m12 = Dot(Left.Rows[1], Right.Rows[2]);
    Result.m13 = Dot(Left.Rows[1], Right.Rows[3]);
    
    Result.m20 = Dot(Left.Rows[2], Right.Rows[0]);
    Result.m21 = Dot(Left.Rows[2], Right.Rows[1]);
    Result.m22 = Dot(Left.Rows[2], Right.Rows[2]);
    Result.m23 = Dot(Left.Rows[2], Right.Rows[3]);
    
    Result.m30 = Dot(Left.Rows[3], Right.Rows[0]);
    Result.m31 = Dot(Left.Rows[3], Right.Rows[1]);
    Result.m32 = Dot(Left.Rows[3], Right.Rows[2]);
    Result.m33 = Dot(Left.Rows[3], Right.Rows[3]);
    return Result;
}

inline m4& 
operator*=(m4& Left, m4 Right)
{
    Left = Left*Right;
    return Left;
}

inline v4f
operator*(v4f Left, m4 Right)
{
    Right = Transpose(Right);
    v4f Result;
    Result.x = Dot(Left, Right.Rows[0]);
    Result.y = Dot(Left, Right.Rows[1]);
    Result.z = Dot(Left, Right.Rows[2]);
    Result.w = Dot(Left, Right.Rows[3]);
    return Result;
}

inline v4f&
operator*=(v4f& Left, m4 Right)
{    
    Left = Left*Right;
    return Left;
}

inline m4
operator*(f32 Left, m4 Right)
{
    m4 Result;
    Result.Row0 = V4(Left * Right.Row0.x, Left * Right.Row0.y, Left * Right.Row0.z, Left * Right.Row0.w);
    Result.Row1 = V4(Left * Right.Row1.x, Left * Right.Row1.y, Left * Right.Row1.z, Left * Right.Row1.w);
    Result.Row2 = V4(Left * Right.Row2.x, Left * Right.Row2.y, Left * Right.Row2.z, Left * Right.Row2.w);
    Result.Row3 = V4(Left * Right.Row3.x, Left * Right.Row3.y, Left * Right.Row3.z, Left * Right.Row3.w);
    return Result;
}

inline m4
PerspectiveM4(f32 FieldOfView, f32 AspectRatio, f32 Near, f32 Far)
{
    f32 c = 1.0f/Tan(FieldOfView*0.5f);
    f32 a = AspectRatio;
    
    m4 Result = 
    {
        c/a,  0.0f,   0.0f,                       0.0f,
        0.0f, c,      0.0f,                       0.0f,
        0.0f, 0.0f, -(Far+Near)/(Far-Near),      -1.0f,
        0.0f, 0.0f, -(2.0f*Far*Near)/(Far-Near),   0.0f
    };
    
    return Result;
}

inline m4
OrthographicM4(f32 Left, f32 Right, f32 Top, f32 Bottom, f32 Near, f32 Far)
{
    m4 Result = 
    {
        2.0f/(Right-Left),           0.0f,                       0.0f,                  0.0f,
        0.0f,                        2.0f/(Top-Bottom),          0.0f,                  0.0f, 
        0.0f,                        0.0f,                      -2.0f/(Far-Near),       0.0f, 
        -(Right+Left)/(Right-Left), -(Top+Bottom)/(Top-Bottom), -(Far+Near)/(Far-Near), 1.0f
    };
    
    return Result;
}

struct quaternion
{
    union
    {        
        struct
        {
            f32 x;
            f32 y;
            f32 z;
            f32 w;
        };
        
        struct
        {
            v3f v;
            f32 s;
        };
    };
};

quaternion Quaternion(f32 x, f32 y, f32 z, f32 w)
{
    quaternion Result;
    Result.x = x;
    Result.y = y;
    Result.z = z;
    Result.w = w;
    return Result;
}

quaternion Quaternion(v3f v, f32 s)
{
    quaternion Result = Quaternion(v.x, v.y, v.z, s);
    return Result;
}

inline quaternion 
Conjugate(quaternion Q)
{
    quaternion Result = Quaternion(-Q.v, Q.s);
    return Result;
}

inline quaternion 
IdentityQuaternion()
{
    quaternion Result;
    Result.v = {};
    Result.s = 1.0f;
    return Result;
}

inline quaternion 
EulerQuaternion(f32 Pitch, f32 Yaw, f32 Roll)
{
    f32 cp = Cos(Yaw*0.5f);
    f32 sp = Sin(Yaw*0.5f);
    f32 cy = Cos(Roll*0.5f);
    f32 sy = Sin(Roll*0.5f);  
    f32 cr = Cos(Pitch*0.5f);
    f32 sr = Sin(Pitch*0.5f);
    
    quaternion Result;
    Result.x = (cy*cp*sr) - (sy*sp*cr);
    Result.y = (sy*cp*sr) + (cy*sp*cr);
    Result.z = (sy*cp*cr) - (cy*sp*sr);
    Result.w = (cy*cp*cr) + (sy*sp*sr);
    return Result;
}

inline quaternion
RollQuaternion(quaternion Q)
{
    f32 Mag = Sqrt(Q.w*Q.w + Q.z*Q.z);    
    ASSERT(Abs(Mag) > 1e-6f); 
    Mag = 1.0f/Mag;
    
    quaternion Result = {};    
    Result.z = Q.z*Mag;
    Result.w = Q.w*Mag;
    return Result;
}

inline quaternion 
EulerQuaternion(v3f Euler)
{
    quaternion Result = EulerQuaternion(Euler.pitch, Euler.yaw, Euler.roll);
    return Result;
}

inline quaternion MatrixQuaternion(m3 Matrix)
{
    quaternion Result;
    
    f32 Trace = Matrix.m00 + Matrix.m11 + Matrix.m22;
    if(Trace > 0)
    {
        f32 s = 0.5f / Sqrt(Trace + 1.0f);        
        Result.w = 0.25f / s;
        Result.x = (Matrix.m12 - Matrix.m21)*s;
        Result.y = (Matrix.m20 - Matrix.m02)*s;
        Result.z = (Matrix.m01 - Matrix.m10)*s;
        return Result;
    }    
    
    if((Matrix.m00 > Matrix.m11) && (Matrix.m00 > Matrix.m22))
    {
        f32 s = 2.0f * Sqrt(1.0f + Matrix.m00 - Matrix.m11 - Matrix.m22);
        Result.w = (Matrix.m12 - Matrix.m21) / s;
        Result.x = 0.25f * s;
        Result.y = (Matrix.m10 + Matrix.m01) / s;
        Result.z = (Matrix.m20 + Matrix.m02) / s;
    }
    else if(Matrix.m11 > Matrix.m22)
    {
        f32 s = 2.0f * Sqrt(1.0f + Matrix.m11 - Matrix.m00 - Matrix.m22);
        Result.w = (Matrix.m20 - Matrix.m02) / s;
        Result.x = (Matrix.m10 + Matrix.m01) / s;
        Result.y = 0.25f * s;
        Result.z = (Matrix.m21 + Matrix.m12) / s;
    }
    else
    {
        f32 s = 2.0f * Sqrt(1.0f + Matrix.m22 - Matrix.m00 - Matrix.m11);
        Result.w = (Matrix.m01 - Matrix.m10) / s;
        Result.x = (Matrix.m20 + Matrix.m02) / s;
        Result.y = (Matrix.m21 + Matrix.m12) / s;
        Result.z = 0.25f*s;
    }
    
    return Result;
}

inline f32 
SquareMagnitude(quaternion Q)
{
    f32 Result = SquareMagnitude(Q.v) + Square(Q.s);
    return Result;
}

inline f32
Magnitude(quaternion Q)
{
    f32 Result = Sqrt(SquareMagnitude(Q));
    return Result;
}

inline f32
InverseMagnitude(quaternion Q)
{
    f32 Result = 1.0f/Magnitude(Q);
    return Result;
}

inline quaternion 
operator*(quaternion Left, f32 Right)
{
    quaternion Result = Quaternion(Left.v*Right, Left.s*Right);    
    return Result;
}

inline quaternion 
operator*(f32 Left, quaternion Right)
{
    quaternion Result = Quaternion(Left*Right.v, Left*Right.s);
    return Result;
}

inline quaternion
Normalize(quaternion Q)
{
    f32 InvMag = InverseMagnitude(Q);
    quaternion Result = InvMag*Q;
    return Result;
}

inline quaternion 
operator*(quaternion Left, quaternion Right)
{
    quaternion Result = Quaternion(Cross(Left.v, Right.v) + Right.s*Left.v + Right.v*Left.s, 
                                   Left.s*Right.s - Dot(Left.v, Right.v));
    return Result;
}

inline quaternion& 
operator*=(quaternion& Left, quaternion Right)
{
    Left = Left*Right;
    return Left;        
}

quaternion RotQuat(v3f Axis, f32 Angle)
{
    quaternion Result;
    Result.v = Axis*Sin(Angle*0.5f);
    Result.s = Cos(Angle*0.5f);
    Result = Normalize(Result);
    return Result;
}

inline v3f 
Rotate(v3f V, quaternion Q)
{
    v3f Result = ((2.0f * Dot(Q.v, V) * Q.v)   + 
                  ((Square(Q.s) - SquareMagnitude(Q.v))*V) + 
                  (2.0f * Q.s * Cross(Q.v, V)));
    return Result;
}

struct sqt
{
    quaternion Orientation;
    v3f Translation;
    v3f Scale;
};

inline sqt
CreateSQT(v3f Translation, v3f Scale, quaternion Orientation)
{
    sqt Result;
    Result.Translation = Translation;
    Result.Scale = Scale;
    Result.Orientation = Orientation;
    return Result;
}

inline sqt
CreateSQT(v3f Translation, f32 Scale, quaternion Orientation)
{
    sqt Result = CreateSQT(Translation, V3(Scale, Scale, Scale), Orientation);    
    return Result;
}

inline sqt 
CreateSQT(v3f Translation, v3f Scale, v3f Euler)
{
    sqt Result = CreateSQT(Translation, Scale, EulerQuaternion(Euler));    
    return Result;
}

inline sqt 
CreateSQT(m4 M)
{
    sqt Result;
    Result.Translation = M.Translation.xyz;
    Result.Scale = V3(Magnitude(M.XAxis.xyz), Magnitude(M.YAxis.xyz), Magnitude(M.ZAxis.xyz));    
    m3 Rotation = M3(Normalize(M.XAxis.xyz), Normalize(M.YAxis.xyz), Normalize(M.ZAxis.xyz));
    Result.Orientation = Normalize(MatrixQuaternion(Rotation));
    return Result;
}

inline m3 
ToMatrix3(quaternion Q)
{
    f32 qxqy = Q.x*Q.y;
    f32 qwqz = Q.w*Q.z;
    f32 qxqz = Q.x*Q.z;
    f32 qwqy = Q.w*Q.y;
    f32 qyqz = Q.y*Q.z;
    f32 qwqx = Q.w*Q.x;
    
    f32 qxqx = Square(Q.x);
    f32 qyqy = Square(Q.y);
    f32 qzqz = Square(Q.z);
    
    m3 Result = 
    {
        1 - 2*(qyqy+qzqz), 2*(qxqy+qwqz),     2*(qxqz-qwqy),   
        2*(qxqy-qwqz),     1 - 2*(qxqx+qzqz), 2*(qyqz+qwqx),   
        2*(qxqz+qwqy),     2*(qyqz-qwqx),     1 - 2*(qxqx+qyqy)
    };
    return Result;
}

inline quaternion
Lerp(quaternion A, f32 t, quaternion B)
{
    quaternion Result = Normalize(Quaternion(Lerp(A.v, t, B.v), Lerp(A.s, t, B.s)));
    return Result;
}

inline m4
TransformM4(v3f Translation, quaternion Orientation)
{
    m4 Result = TransformM4(Translation, ToMatrix3(Orientation));    
    return Result;
}

inline m4
TransformM4(v3f Translation, m3 Orientation, v3f Scale)
{    
    Orientation.XAxis *= Scale.x;
    Orientation.YAxis *= Scale.y;
    Orientation.ZAxis *= Scale.z;
    m4 Result = TransformM4(Translation, Orientation);
    return Result;
}

inline m4 
TransformM4(v3f Translation, v3f XAxis, v3f YAxis, v3f ZAxis, v3f Scale)
{
    m3 OrientationMatrix = M3(XAxis, YAxis, ZAxis);
    m4 Result = TransformM4(Translation, OrientationMatrix, Scale);
    return Result;
}

inline m4
TransformM4(v3f Translation, quaternion Orientation, v3f Scale)
{
    m3 OrientationMatrix = ToMatrix3(Orientation);
    m4 Result = TransformM4(Translation, OrientationMatrix, Scale);    
    return Result;
}

inline m4
TransformM4(v3f Translation, v3f Scale, v3f Euler)
{
    m4 Result = TransformM4(Translation, EulerQuaternion(Euler), Scale);
    return Result;
}

inline m4
TransformM4(sqt SQT)
{
    m4 Result = TransformM4(SQT.Translation, SQT.Orientation, SQT.Scale);
    return Result;
}

inline v3f TransformV3(v3f Point, sqt Transform)
{
    v3f Result = Rotate(Point*Transform.Scale, Transform.Orientation) + Transform.Translation;
    return Result;
}

inline v3f InverseTransformV3(v3f Point, sqt Transform)
{
    v3f Result = Rotate(Point-Transform.Translation, Conjugate(Transform.Orientation)) / Transform.Scale;
    return Result;
}

inline v3f TransformV3(v3f Point, m4 Transform)
{
    v4f Result = V4(Point, 1.0f)*Transform;
    return Result.xyz;
}

inline sqt TransformSQT(sqt A, sqt B)
{
    sqt Result;
    Result.Translation = A.Translation + B.Translation;
    Result.Scale = A.Scale*B.Scale;
    Result.Orientation = A.Orientation*B.Orientation;
    return Result;
}

struct vertex_p2_uv_c
{
    v2f P;
    v2f UV;
    u32 C;
};

struct vertex_p3
{
    v3f P;
};

struct vertex_p3_n3
{
    v3f P;
    v3f N;
};

struct vertex_p3_n3_weights
{
    v3f P;
    v3f N;
    u8 JointI[4];
    f32 JointW[4];
};

struct vertex_p3_n3_uv
{
    v3f P;
    v3f N;
    v2f UV;
};

struct vertex_p3_n3_uv_weights
{   
    v3f P;
    v3f N;
    v2f UV;    
    u8 JointI[4];
    f32 JointW[4];
};

struct vertex_p3_n3_t4_uv
{
    v3f P;
    v3f N;
    v4f T;
    v2f UV;    
};

struct vertex_p3_n3_t4_uv_weights
{
    v3f P;
    v3f N;
    v4f T;
    v2f UV;    
    u8 JointI[4];
    f32 JointW[4];
};

inline b32 operator!=(vertex_p3_n3 Left, vertex_p3_n3 Right)
{
    b32 Result = (Left.P != Right.P) || (Left.N != Right.N);
    return Result;
}

inline b32 operator!=(vertex_p3_n3_uv Left, vertex_p3_n3_uv Right)
{
    b32 Result = (Left.P != Right.P) || (Left.N != Right.N) || (Left.UV != Right.UV);
    return Result;
}

struct quadratic_equation_result
{
    u32 RootCount;
    f32 Roots[2];
};

inline quadratic_equation_result 
SolveQuadraticEquation(f32 a, f32 b, f32 c)
{    
    quadratic_equation_result Result = {};
    
    f32 Determinant = b*b - 4*a*c;
    if(Determinant < 0)
        return Result;
    
    f32 Discriminant = Sqrt(Determinant);    
    Result.RootCount = 2;
    
    if(b < 0)
    {
        Result.Roots[0] = (-b + Discriminant) / (2*a);
        Result.Roots[1] = (2*c) / (-b + Discriminant);
    }
    else
    {
        Result.Roots[0] = (2*c) / (-b - Discriminant);
        Result.Roots[1] = (-b - Discriminant) / (2*a);
    }
    
    return Result;
}

inline f32 Determinant(m4 M)
{
    f32 Result = (M.m00 * Determinant(M.Rows[1].yzw, M.Rows[2].yzw, M.Rows[3].yzw) - 
                  M.m10 * Determinant(M.Rows[0].yzw, M.Rows[2].yzw, M.Rows[3].yzw) + 
                  M.m20 * Determinant(M.Rows[0].yzw, M.Rows[1].yzw, M.Rows[3].yzw) - 
                  M.m30 * Determinant(M.Rows[0].yzw, M.Rows[1].yzw, M.Rows[2].yzw));    
    return Result;
}
inline m4 Inverse(m4 M)
{
    f32 Det = Determinant(M);
    if(Det == 0)
    {        
        ASSERT(false);
        return {};
    }
    
    m4 Adjoint = 
    {
        M.m11*M.m22*M.m33 + M.m12*M.m23*M.m31 + M.m13*M.m21*M.m32 - M.m13*M.m22*M.m31 - M.m12*M.m21*M.m33 - M.m11*M.m23*M.m32,
        -M.m01*M.m22*M.m33 - M.m02*M.m23*M.m31 - M.m03*M.m21*M.m32 + M.m03*M.m22*M.m31 + M.m02*M.m21*M.m33 + M.m01*M.m23*M.m32,
        M.m01*M.m12*M.m33 + M.m02*M.m13*M.m31 + M.m03*M.m11*M.m32 - M.m03*M.m12*M.m31 - M.m02*M.m11*M.m33 - M.m01*M.m13*M.m32,
        -M.m01*M.m12*M.m23 - M.m02*M.m13*M.m21 - M.m03*M.m11*M.m22 + M.m03*M.m12*M.m21 + M.m02*M.m11*M.m23 + M.m01*M.m13*M.m22,
        -M.m10*M.m22*M.m33 - M.m12*M.m23*M.m30 - M.m13*M.m20*M.m32 + M.m13*M.m22*M.m30 + M.m12*M.m20*M.m33 + M.m10*M.m23*M.m32,
        M.m00*M.m22*M.m33 + M.m02*M.m23*M.m30 + M.m03*M.m20*M.m32 - M.m03*M.m22*M.m30 - M.m02*M.m20*M.m33 - M.m00*M.m23*M.m32,
        -M.m00*M.m12*M.m33 - M.m02*M.m13*M.m30 - M.m03*M.m10*M.m32 + M.m03*M.m12*M.m30 + M.m02*M.m10*M.m33 + M.m00*M.m13*M.m32,
        M.m00*M.m12*M.m23 + M.m02*M.m13*M.m20 + M.m03*M.m10*M.m22 - M.m03*M.m12*M.m20 - M.m02*M.m10*M.m23 - M.m00*M.m13*M.m22,
        M.m10*M.m21*M.m33 + M.m11*M.m23*M.m30 + M.m13*M.m20*M.m31 - M.m13*M.m21*M.m30 - M.m11*M.m20*M.m33 - M.m10*M.m23*M.m31,
        -M.m00*M.m21*M.m33 - M.m01*M.m23*M.m30 - M.m03*M.m20*M.m31 + M.m03*M.m21*M.m30 + M.m01*M.m20*M.m33 + M.m00*M.m23*M.m31,
        M.m00*M.m11*M.m33 + M.m01*M.m13*M.m30 + M.m03*M.m10*M.m31 - M.m03*M.m11*M.m30 - M.m01*M.m10*M.m33 - M.m00*M.m13*M.m31,
        -M.m00*M.m11*M.m23 - M.m01*M.m13*M.m20 - M.m03*M.m10*M.m21 + M.m03*M.m11*M.m20 + M.m01*M.m10*M.m23 + M.m00*M.m13*M.m21,
        -M.m10*M.m21*M.m32 - M.m11*M.m22*M.m30 - M.m12*M.m20*M.m31 + M.m12*M.m21*M.m30 + M.m11*M.m20*M.m32 + M.m10*M.m22*M.m31,
        M.m00*M.m21*M.m32 + M.m01*M.m22*M.m30 + M.m02*M.m20*M.m31 - M.m02*M.m21*M.m30 - M.m01*M.m20*M.m32 - M.m00*M.m22*M.m31,
        -M.m00*M.m11*M.m32 - M.m01*M.m12*M.m30 - M.m02*M.m10*M.m31 + M.m02*M.m11*M.m30 + M.m01*M.m10*M.m32 + M.m00*M.m12*M.m31,
        M.m00*M.m11*M.m22 + M.m01*M.m12*M.m20 + M.m02*M.m10*M.m21 - M.m02*M.m11*M.m20 - M.m01*M.m10*M.m22 - M.m00*M.m12*M.m21
    };

    return 1.0f/Det * Adjoint;
}

inline m4 LookAt(v3f Position, v3f Target)
{
    v3f Z = Normalize(Position-Target);
    
    v3f X, Y;
    CreateBasis(Z, &X, &Y);
    
    m4 Result = InverseTransformM4(Position, X, Y, Z);
    return Result;
}

struct rigid_transform
{
    
    v3f         Translation;
    quaternion  Orientation;
};

inline rigid_transform
CreateRigidTransform(v3f Translation, v3f Euler)
{
    rigid_transform Result;            
    Result.Translation = Translation;    
    Result.Orientation = EulerQuaternion(Euler);
    return Result;
}

inline rigid_transform
CreateRigidTransform(v3f Translation, quaternion Orientation)
{
    rigid_transform Result;
    Result.Translation = Translation;
    Result.Orientation = Orientation;
    return Result;
}

struct rigid_transform_matrix
{
    v3f Translation;
    m3  Orientation;
};

struct spherical_coordinates
{
    f32 Radius;
    f32 Azimuth;
    f32 Inclination;
};

inline spherical_coordinates
SphericalCoordinates(f32 Radius, f32 Azimuth, f32 Inclination)
{
    spherical_coordinates Result;
    Result.Radius = Radius;
    Result.Azimuth = Azimuth;
    Result.Inclination = Inclination;
    return Result;
}

inline v3f 
ToCartesianCoordinates(spherical_coordinates Coordinates)
{
    v3f Result;    
    f32 s = Coordinates.Radius*Sin(Coordinates.Inclination);
    f32 c = Coordinates.Radius*Cos(Coordinates.Inclination);
    
    Result.x = s*Cos(Coordinates.Azimuth);
    Result.y = s*Sin(Coordinates.Azimuth);
    Result.z = c;
    return Result;    
}

inline v3f TransformV3(v3f Point, rigid_transform Transform)
{
    v3f Result = Rotate(Point, Transform.Orientation) + Transform.Translation;
    return Result;
}

inline v3f InverseTransformV3(v3f Point, rigid_transform Transform)
{
    v3f Result = Rotate(Point-Transform.Translation, Conjugate(Transform.Orientation));    
    return Result;
}

inline m4 TransformM4(rigid_transform Transform)
{
    m4 Result = TransformM4(Transform.Translation, Transform.Orientation);
    return Result;
}

inline rigid_transform 
operator*(rigid_transform TransformA, rigid_transform TransformB)
{
    rigid_transform Result;
    Result.Orientation = TransformA.Orientation*TransformB.Orientation;
    Result.Translation = TransformA.Translation+TransformB.Translation;
    return Result;
}

inline sqt 
CreateSQT(rigid_transform Transform, v3f Scale)
{    
    sqt Result;    
    Result.Translation = Transform.Translation;
    Result.Scale = Scale;
    Result.Orientation = Transform.Orientation;
    return Result;
}

inline sqt
CreateSQT(v3f Translation, quaternion Orientation)
{
    sqt Result = CreateSQT(Translation, 1.0f, Orientation);
    return Result;
}

inline sqt 
CreateSQT(rigid_transform Transform, f32 Scale)
{    
    sqt Result = CreateSQT(Transform, V3(Scale, Scale, Scale));        
    return Result;
}

inline sqt 
CreateSQT(rigid_transform Transform)
{    
    sqt Result = CreateSQT(Transform, 1.0f);
    return Result;
}

struct rect3D
{
    v3f Min;
    v3f Max;
};

inline rect3D
CreateRect3D(v3f Min, v3f Max)
{
    rect3D Rect;
    Rect.Min = Min;
    Rect.Max = Max;
    return Rect;
}

struct frustum
{
    v3f Normals[6];
    f32 Distances[6];
};

inline frustum CreateFrustum(m4 Matrix)
{
    frustum Result = {};
    v3f Col1 = V3(Matrix.m00, Matrix.m10, Matrix.m20);
    v3f Col2 = V3(Matrix.m01, Matrix.m11, Matrix.m21);
    v3f Col3 = V3(Matrix.m02, Matrix.m12, Matrix.m22);
    v3f Col4 = V3(Matrix.m03, Matrix.m13, Matrix.m23);
    Result.Normals[0] = Col4 + Col1;
    Result.Normals[1] = Col4 - Col1;
    Result.Normals[2] = Col4 + Col2;
    Result.Normals[3] = Col4 - Col2;
    Result.Normals[4] = Col3;
    Result.Normals[5] = Col4 - Col3;
    Result.Distances[0] = Matrix.m33 + Matrix.m30;
    Result.Distances[1] = Matrix.m33 - Matrix.m30;
    Result.Distances[2] = Matrix.m33 + Matrix.m31;
    Result.Distances[3] = Matrix.m33 - Matrix.m31;
    Result.Distances[4] = Matrix.m32;
    Result.Distances[5] = Matrix.m33 - Matrix.m32;
    for(i32 PlaneIndex = 0; PlaneIndex < 6; PlaneIndex++)
    {
        f32 Mag = 1.0f/Magnitude(Result.Normals[PlaneIndex]);
        Result.Normals[PlaneIndex] *= Mag;
        Result.Distances[PlaneIndex] *= Mag;
    }
    return Result;
}

inline void GetFrustumCorners(v3f* Corners, m4 Perspective)
{
    m4 InversePerspective = Inverse(Perspective);
    v4f Intermediate[8];
    Intermediate[0] = V4(-1, -1, -1, 1) * InversePerspective;
    Intermediate[1] = V4( 1, -1, -1, 1) * InversePerspective;
    Intermediate[2] = V4( 1,  1, -1, 1) * InversePerspective;
    Intermediate[3] = V4(-1,  1, -1, 1) * InversePerspective;
    Intermediate[4] = V4( 1, -1, 1, 1) * InversePerspective;
    Intermediate[5] = V4(-1, -1,  1, 1) * InversePerspective;
    Intermediate[6] = V4(-1,  1,  1, 1) * InversePerspective;
    Intermediate[7] = V4( 1,  1,  1, 1) * InversePerspective;

    Corners[0] = Intermediate[0].xyz / Intermediate[0].w;
    Corners[1] = Intermediate[1].xyz / Intermediate[1].w;
    Corners[2] = Intermediate[2].xyz / Intermediate[2].w;
    Corners[3] = Intermediate[3].xyz / Intermediate[3].w;
    Corners[4] = Intermediate[4].xyz / Intermediate[4].w;
    Corners[5] = Intermediate[5].xyz / Intermediate[5].w;
    Corners[6] = Intermediate[6].xyz / Intermediate[6].w;
    Corners[7] = Intermediate[7].xyz / Intermediate[7].w;
}

inline void TransformVectors(v3f* Vectors, i32 VectorSize, m4 Transformation)
{
    for(int i = 0; i < VectorSize; i++)
    {
        Vectors[i] = (V4(Vectors[i], 1) * Transformation).xyz;
    }
}

#endif