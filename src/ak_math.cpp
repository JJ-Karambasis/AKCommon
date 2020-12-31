template <typename type>
type AK_Lerp(type A, type t, type B)
{
    return (1-t)*A + t*B;    
}

template <typename type>
type& ak_v2<type>::operator[](ak_u32 Index)
{
    AK_Assert(Index < 2, "Index out of bounds");
    return Data[Index];
}

template <typename type>
ak_u32 ak_v2<type>::LargestComp()
{
    return AK_Abs(x) >= AK_Abs(y) ? 0 : 1;
}

template <typename type>
type& ak_v3<type>::operator[](ak_u32 Index)
{
    AK_Assert(Index < 3, "Index out of bounds");
    return Data[Index];
}

template <typename type>
ak_u32 ak_v3<type>::LargestComp()
{
    ak_u32 Result = xy.LargestComp();
    return AK_Abs(z) >= AK_Abs(Data[Result]) ? 2 : Result;
}

template <typename type>
type& ak_v4<type>::operator[](ak_u32 Index)
{
    AK_Assert(Index < 4, "Index out of bounds");
    return Data[Index];
}

template <typename type>
ak_u32 ak_v4<type>::LargestComp()
{
    u32 Result = xyz.LargestComp();
    return AK_Abs(w) >= AK_Abs(Data[Result]) ? 3 : Result;
}

template <typename type>
type& ak_quat<type>::operator[](ak_u32 Index)
{
    ASSERT(Index < 4);
    return Data[Index];
}

template <typename type>
type& ak_m3<type>::operator[](ak_u32 Index)
{
    AK_Assert(Index < 9, "Index out of bounds");
    return Data[Index];
}

template <typename type>
type& ak_m4<type>::operator[](ak_u32 Index)
{
    AK_Assert(Index < 16, "Index out of bounds");
    return Data[Index];
}

template <typename type> ak_v2<type> AK_V2() 
{ 
    return {}; 
}

template <typename type> ak_v2<type> AK_V2(type x, type y) 
{ 
    return {x, y}; 
}

template <typename type> ak_v2<type> AK_V2(type* Data) 
{ 
    return {Data[0], Data[1]}; 
}

template <typename type> ak_v2<type> operator+(type Left, ak_v2<type> Right) 
{ 
    return {Left+Right.x, Left+Right.y}; 
}

template <typename type> ak_v2<type> operator+(ak_v2<type> Left, type Right) 
{ 
    return {Left.x+Right, Left.y+Right}; 
}

template <typename type> 
ak_v2<type> operator+(ak_v2<type> Left, ak_v2<type> Right) 
{ 
    return {Left.x+Right.x, Left.y+Right.y}; 
}

template <typename type> 
ak_v2<type>& operator+=(ak_v2<type>& Left, type Right) 
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_v2<type>& operator+=(ak_v2<type>& Left, ak_v2<type> Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> ak_v2<type> operator-(type Left, ak_v2<type> Right) 
{ 
    return {Left-Right.x, Left-Right.y}; 
}

template <typename type> ak_v2<type> operator-(ak_v2<type> Left, type Right) 
{ 
    return {Left.x-Right, Left.y-Right}; 
}

template <typename type> 
ak_v2<type> operator-(ak_v2<type> Left, ak_v2<type> Right) 
{ 
    return {Left.x-Right.x, Left.y-Right.y}; 
}

template <typename type> 
ak_v2<type>& operator-=(ak_v2<type>& Left, type Right) 
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_v2<type>& operator-=(ak_v2<type>& Left, ak_v2<type> Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> ak_v2<type> operator*(type Left, ak_v2<type> Right) 
{ 
    return {Left*Right.x, Left*Right.y}; 
}

template <typename type> ak_v2<type> operator*(ak_v2<type> Left, type Right) 
{ 
    return {Left.x*Right, Left.y*Right}; 
}

template <typename type> 
ak_v2<type> operator*(ak_v2<type> Left, ak_v2<type> Right) 
{ 
    return {Left.x*Right.x, Left.y*Right.y}; 
}

template <typename type> 
ak_v2<type>& operator*=(ak_v2<type>& Left, type Right) 
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_v2<type>& operator*=(ak_v2<type>& Left, ak_v2<type> Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> ak_v2<type> operator/(type Left, ak_v2<type> Right) 
{ 
    return {Left/Right.x, Left/Right.y}; 
}

template <typename type> ak_v2<type> operator/(ak_v2<type> Left, type Right) 
{ 
    return {Left.x/Right, Left.y/Right}; 
}

template <typename type> 
ak_v2<type> operator/(ak_v2<type> Left, ak_v2<type> Right) 
{ 
    return {Left.x/Right.x, Left.y/Right.y}; 
}

template <typename type> 
ak_v2<type>& operator/=(ak_v2<type>& Left, type Right) 
{
    Left = Left/Right;
    return Left;
}

template <typename type> 
ak_v2<type>& operator/=(ak_v2<type>& Left, ak_v2<type> Right)
{
    Left = Left/Right;
    return Left;
}

template <typename type> 
ak_v2<type> operator-(ak_v2<type> V)
{
    return {-V.x, -V.y};
}

template <typename type> 
ak_bool operator!=(type Left, ak_v2<type> Right)
{
    return Left != Right.x || Left != Right.y;
}

template <typename type> 
ak_bool operator!=(ak_v2<type> Left, type Right)
{
    return Left.x != Right || Left.y != Right;
}

template <typename type> 
ak_bool operator!=(ak_v2<type> Left, ak_v2<type> Right)
{
    return Left.x != Right.x || Left.y != Right.y;
}

template <typename type> 
ak_bool operator==(type Left, ak_v2<type> Right)
{
    return Left == Right.x && Left == Right.y;
}

template <typename type> 
ak_bool operator==(ak_v2<type> Left, type Right)
{
    return Left.x == Right && Left.y == Right;
}

template <typename type> 
ak_bool operator==(ak_v2<type> Left, ak_v2<type> Right)
{
    return Left.x == Right.x && Left.y == Right.y;
}

template <typename type> 
ak_bool operator<(type Left, ak_v2<type> Right)
{
    return Left < Right.x && Left < Right.y;
}

template <typename type> 
ak_bool operator<(ak_v2<type> Left, type Right)
{
    return Left.x < Right && Left.y < Right;
}

template <typename type> 
ak_bool operator<(ak_v2<type> Left, ak_v2<type> Right)
{
    return Left.x < Right.x && Left.y < Right.y;
}

template <typename type> 
ak_bool operator>(type Left, ak_v2<type> Right)
{
    return Left > Right.x && Left > Right.y;
}

template <typename type> 
ak_bool operator>(ak_v2<type> Left, type Right)
{
    return Left.x > Right && Left.y > Right;
}

template <typename type> 
ak_bool operator>(ak_v2<type> Left, ak_v2<type> Right)
{
    return Left.x > Right.x && Left.y > Right.y;
}

template <typename type> 
ak_bool operator>=(type Left, ak_v2<type> Right)
{
    return Left >= Right.x && Left >= Right.y;
}

template <typename type> 
ak_bool operator>=(ak_v2<type> Left, type Right)
{
    return Left.x >= Right && Left.y >= Right;
}

template <typename type> 
ak_bool operator>=(ak_v2<type> Left, ak_v2<type> Right)
{
    return Left.x >= Right.x && Left.y >= Right.y;
}

template <typename type> 
ak_bool operator<=(type Left, ak_v2<type> Right)
{
    return Left <= Right.x && Left <= Right.y;
}

template <typename type> 
ak_bool operator<=(ak_v2<type> Left, type Right)
{
    return Left.x <= Right && Left.y <= Right;
}

template <typename type> 
ak_bool operator<=(ak_v2<type> Left, ak_v2<type> Right)
{
    return Left.x <= Right.x && Left.y <= Right.y;
}

template <typename type> 
ak_v2<type> AK_AbsV2(ak_v2<type> V)
{
    return {AK_Abs(V.x), AK_Abs(V.y) };
}

template <typename type> 
type AK_Dot(ak_v2<type> Left, ak_v2<type> Right)
{
    return Left.x*Right.x + Left.y*Right.y;
}

template <typename type> 
type AK_SqrMagnitude(ak_v2<type> V)
{
    return AK_Dot(V, V);
}

template <typename type> 
type AK_Magnitude(ak_v2<type> V)
{
    return AK_Sqrt(AK_SqrMagnitude(V));    
}

template <typename type> 
ak_v2<type> AK_Normalize(ak_v2<type> V)
{
    type InvLength = AK_Magnitude(V);
    if(InvLength == (type)0)
        return {};
    InvLength = (type)1/InvLength;    
    return V*InvLength;
}

template <typename type>
ak_v2<type> AK_Lerp(ak_v2<type> A, type t, ak_v2<type> B)
{
    return (1-t)*A + t*B;
}

ak_v2f AK_InvalidV2f()
{
    return {INFINITY, INFINITY};
}

ak_v2f AK_V2f(ak_i32 x, ak_i32 y)
{
    return {(ak_f32)x, (ak_f32)y};
}

ak_v2f AK_V2f(ak_v2i V)
{
    return AK_V2f(V.x, V.y);
}

ak_v2f AK_V2f(ak_f64 x, ak_f64 y)
{
    return {(ak_f32)x, (ak_f32)y};
}

ak_v2f AK_V2f(ak_f64* Data)
{
    return AK_V2f(Data[0], Data[1]);
}

ak_bool AK_EqualApprox(ak_v2f A, ak_v2f B, ak_f32 Epsilon)
{
    return AK_SqrMagnitude(A-B) <= AK_Square(Epsilon);
}

template <typename type> 
ak_v3<type> AK_V3()
{
    return {};
}

template <typename type> ak_v3<type> AK_V3(type x, type y, type z)
{
    return {x, y, z};
}

template <typename type> ak_v3<type> AK_V3(ak_v2<type> xy)
{
    return {xy.x, xy.y};
}

template <typename type> ak_v3<type> AK_V3(ak_v2<type> xy, type z)
{
    return {xy.x, xy.y, z};
}

template <typename type> ak_v3<type> AK_V3(type x, ak_v2<type> yz)
{
    return {x, yz.x, yz.y};
}

template <typename type> ak_v3<type> AK_V3(type* V)
{
    return {V[0], V[1], V[2]};
}

template <typename type> 
ak_v3<type> operator+(type Left, ak_v3<type> Right)
{
    return {Left + Right.x, Left+Right.y, Left+Right.z};
}

template <typename type> 
ak_v3<type> operator+(ak_v3<type> Left, type Right)
{
    return {Left.x + Right, Left.y + Right, Left.z + Right};
}

template <typename type> 
ak_v3<type> operator+(ak_v3<type> Left, ak_v3<type> Right)
{
    return {Left.x + Right.x, Left.y + Right.y, Left.z + Right.z};
}

template <typename type> 
ak_v3<type>& operator+=(ak_v3<type>& Left, type Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_v3<type>& operator+=(ak_v3<type>& Left, ak_v3<type> Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_v3<type> operator-(type Left, ak_v3<type> Right)
{
    return {Left-Right.x, Left-Right.y, Left-Right.z};
}

template <typename type> 
ak_v3<type> operator-(ak_v3<type> Left, type Right)
{
    return {Left.x-Right, Left.y-Right, Left.z-Right};
}

template <typename type> 
ak_v3<type> operator-(ak_v3<type> Left, ak_v3<type> Right)
{
    return {Left.x-Right.x, Left.y-Right.y, Left.z-Right.z};
}

template <typename type> 
ak_v3<type>& operator-=(ak_v3<type>& Left, type Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_v3<type>& operator-=(ak_v3<type>& Left, ak_v3<type> Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_v3<type> operator*(type Left, ak_v3<type> Right)
{
    return {Left*Right.x, Left*Right.y, Left*Right.z};
}

template <typename type> 
ak_v3<type> operator*(ak_v3<type> Left, type Right)
{
    return {Left.x*Right, Left.y*Right, Left.z*Right};
}

template <typename type> 
ak_v3<type> operator*(ak_v3<type> Left, ak_v3<type> Right)
{
    return {Left.x*Right.x, Left.y*Right.y, Left.z*Right.z};
}

template <typename type> 
ak_v3<type>& operator*=(ak_v3<type>& Left, type Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_v3<type>& operator*=(ak_v3<type>& Left, ak_v3<type> Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_v3<type> operator/(type Left, ak_v3<type> Right)
{
    return {Left/Right.x, Left/Right.y, Left/Right.z};
}

template <typename type> 
ak_v3<type> operator/(ak_v3<type> Left, type Right)
{
    return {Left.x/Right, Left.y/Right, Left.z/Right};
}

template <typename type> 
ak_v3<type> operator/(ak_v3<type> Left, ak_v3<type> Right)
{
    return {Left.x/Right.x, Left.y/Right.y, Left.z/Right.z};
}

template <typename type> 
ak_v3<type>& operator/=(ak_v3<type>& Left, type Right)
{
    Left = Left/Right;
    return Left;
}

template <typename type> 
ak_v3<type>& operator/=(ak_v3<type>& Left, ak_v3<type> Right)
{
    Left = Left/Right;
    return Left;
}

template <typename type> 
ak_v3<type> operator-(ak_v3<type> V)
{
    return {-V.x, -V.y, -V.z};
}

template <typename type> 
ak_bool operator!=(type Left, ak_v3<type> Right)
{
    return Left != Right.x || Left != Right.y || Left != Right.z;
}

template <typename type> 
ak_bool operator!=(ak_v3<type> Left, type Right)
{
    return Left.x != Right || Left.y != Right || Left.z != Right;
}

template <typename type> 
ak_bool operator!=(ak_v3<type> Left, ak_v3<type> Right)
{
    return Left.x != Right.x || Left.y != Right.y || Left.z != Right.z;
}

template <typename type> 
ak_bool operator==(type Left, ak_v3<type> Right)
{
    return Left == Right.x && Left == Right.y && Left == Right.z;
}

template <typename type> 
ak_bool operator==(ak_v3<type> Left, type Right)
{
    return Left.x == Right && Left.y == Right && Left.z == Right;
}

template <typename type> 
ak_bool operator==(ak_v3<type> Left, ak_v3<type> Right)
{
    return Left.x == Right.x && Left.y == Right.y && Left.z == Right.z;
}

template <typename type> 
ak_bool operator<(type Left, ak_v3<type> Right)
{
    return Left < Right.x && Left < Right.y && Left < Right.z;
}

template <typename type> 
ak_bool operator<(ak_v3<type> Left, type Right)
{
    return Left.x < Right && Left.y < Right && Left.z < Right;
}

template <typename type> 
ak_bool operator<(ak_v3<type> Left, ak_v3<type> Right)
{
    return Left.x < Right.x && Left.y < Right.y && Left.z < Right.z;
}

template <typename type> 
ak_bool operator>(type Left, ak_v3<type> Right)
{
    return Left > Right.x && Left > Right.y && Left > Right.z;
}

template <typename type> 
ak_bool operator>(ak_v3<type> Left, type Right)
{
    return Left.x > Right && Left.y > Right && Left.z > Right;
}

template <typename type> 
ak_bool operator>(ak_v3<type> Left, ak_v3<type> Right)
{
    return Left.x > Right.x && Left.y > Right.y && Left.z > Right.z;
}

template <typename type> 
ak_bool operator>=(type Left, ak_v3<type> Right)
{
    return Left >= Right.x && Left >= Right.y && Left >= Right.z;
}

template <typename type> 
ak_bool operator>=(ak_v3<type> Left, type Right)
{
    return Left.x >= Right && Left.y >= Right && Left.z >= Right;
}

template <typename type> 
ak_bool operator>=(ak_v3<type> Left, ak_v3<type> Right)
{
    return Left.x >= Right.x && Left.y >= Right.y && Left.z >= Right.z;
}

template <typename type> 
ak_bool operator<=(type Left, ak_v3<type> Right)
{
    return Left <= Right.x && Left <= Right.y && Left <= Right.z;
}

template <typename type> 
ak_bool operator<=(ak_v3<type> Left, type Right)
{
    return Left.x <= Right && Left.y <= Right && Left.z <= Right;
}

template <typename type> 
ak_bool operator<=(ak_v3<type> Left, ak_v3<type> Right)
{
    return Left.x <= Right.x && Left.y <= Right.y && Left.z <= Right.z;
}

template <typename type> 
ak_v3<type> AK_AbsV3(ak_v3<type> V)
{
    return {AK_Abs(V.x), AK_Abs(V.y), AK_Abs(V.z)};
}

template <typename type> 
type AK_Dot(ak_v3<type> Left, ak_v3<type> Right)
{
    return Left.x*Right.x + Left.y*Right.y + Left.z*Right.z;
}

template <typename type> 
type AK_SqrMagnitude(ak_v3<type> V)
{
    return AK_Dot(V, V);
}

template <typename type> 
type AK_Magnitude(ak_v3<type> V)
{
    return (type)AK_Sqrt((ak_f32)AK_SqrMagnitude(V));    
}

template <typename type> 
ak_v3<type> AK_Normalize(ak_v3<type> V)
{
    type InvLength = AK_Magnitude(V);
    if(InvLength == (type)0)
        return {};
    InvLength = 1.0f/InvLength;    
    return V*InvLength;
}

template <typename type> 
ak_v3<type> AK_Lerp(ak_v3<type> A, type t, ak_v3<type> B)
{
    return (1-t)*A + t*B;
}

template <typename type> 
ak_v3<type> AK_Cross(ak_v3<type> Left, ak_v3<type> Right)
{
    return {Left.y*Right.z - Left.z*Right.y, Left.z*Right.x - Left.x*Right.z, Left.x*Right.y - Left.y*Right.x};
}

template <typename type> 
type AK_Determinant(ak_v3<type> U, ak_v3<type> V, ak_v3<type> W)
{
    return AK_Dot(U, AK_Cross(V, W));
}

template <typename type> 
ak_v3<type> AK_SphericalToCartesian(ak_v3<type> SphericalCoordinates)
{
    ak_v3<type> Result;
    type s = SphericalCoordinates.radius*AK_Sin(SphericalCoordinates.inclination);
    type c = SphericalCoordinates.radius*AK_Cos(SphericalCoordinates.inclination);
    
    Result.x = s*AK_Cos(SphericalCoordinates.azimuth);
    Result.y = s*AK_Sin(SphericalCoordinates.azimuth);
    Result.z = c;
    return Result;    
}

template <typename type> 
ak_v3<type> AK_ToNormalizedDeviceCoordinates(ak_v2<type> XY, ak_v2<type> Resolution)
{
    ak_v3<type> Result;
    Result.x = ((type)2 * XY.x) / Resolution.w - (type)1;
    Result.y = (type)1 - ((type)2 * XY.y) / Resolution.h;
    Result.z = (type)1;
    return Result;
}

ak_v3f AK_InvalidV3f()
{
    return {INFINITY, INFINITY, INFINITY};
}

ak_v3f AK_V3f(ak_i32 x, ak_i32 y, ak_i32 z)
{
    return {(ak_f32)x, (ak_f32)y, (ak_f32)z};
}

ak_v3f AK_V3f(ak_f64 x, ak_f64 y, ak_f64 z)
{
    return {(ak_f32)x, (ak_f32)y, (ak_f32)z};
}

ak_v3f AK_V3f(ak_f64* Data)
{
    return AK_V3f(Data[0], Data[1], Data[2]);
}

ak_v3f AK_V3f(const ak_f64* Data)
{
    return AK_V3f(Data[0], Data[1], Data[2]);
}

ak_bool AK_EqualApprox(ak_v3f A, ak_v3f B, ak_f32 Epsilon)
{
    return AK_SqrMagnitude(A-B) <= AK_Square(Epsilon);
}

ak_bool AK_EqualEps(ak_v3f A, ak_v3f B)
{
    ak_bool Result = AK_EqualEps(A.x, B.x) && AK_EqualEps(A.y, B.y) && AK_EqualEps(A.z, B.z);
    return Result;
}

ak_color3f AK_RGB(ak_f32 r, ak_f32 g, ak_f32 b)
{
    return {r, g, b};
}

ak_color3f AK_White3()
{
    return AK_RGB(1.0f, 1.0f, 1.0f);
}

ak_color3f AK_Red3()
{
    return AK_RGB(1.0f, 0.0f, 0.0f);
}

ak_color3f AK_Green3()
{
    return AK_RGB(0.0f, 1.0f, 0.0f);
}

ak_color3f AK_Blue3()
{
    return AK_RGB(0.0f, 0.0f, 1.0f);
}

ak_color3f AK_Yellow3()
{
    return AK_RGB(1.0f, 1.0f, 0.0f);
}

ak_color3f AK_Black3()
{
    return AK_RGB(0.0f, 0.0f, 0.0f);
}

ak_color3f AK_Cyan3()
{
    return AK_RGB(0.0f, 1.0f, 1.0f);
}

ak_color3f AK_Magenta3()
{
    return AK_RGB(1.0f, 0.0f, 1.0f);
}

template <typename type> 
ak_v4<type> AK_V4()
{
    return {};
}

template <typename type> 
ak_v4<type> AK_V4(type x, type y, type z, type w)
{
    return {x, y, z, w};
}

template <typename type> 
ak_v4<type> AK_V4(ak_v2<type> xy)
{
    return {xy.x, xy.y};
}

template <typename type> 
ak_v4<type> AK_V4(ak_v3<type> xyz)
{
    return {xyz.x, xyz.y, xyz.z};
}

template <typename type> 
ak_v4<type> AK_V4(ak_v2<type> xy, ak_v2<type> yz)
{
    return {xy.x, xy.y, yz.x, yz.y};
}

template <typename type> 
ak_v4<type> AK_V4(ak_v2<type> xy, type z, type w)
{
    return {xy.x, xy.y, z, w};
}

template <typename type> 
ak_v4<type> AK_V4(ak_v3<type> xyz, type w)
{
    return {xyz.x, xyz.y, xyz.z, w};
}

template <typename type> ak_v4<type> AK_V4(type* V)
{
    return {V[0], V[1], V[2], V[3]};
}

template <typename type> 
ak_v4<type> operator+(type Left, ak_v4<type> Right)
{
    return {Left+Right.x, Left+Right.y, Left+Right.z, Left+Right.w};
}

template <typename type> 
ak_v4<type> operator+(ak_v4<type> Left, type Right)
{
    return {Left.x+Right, Left.y+Right, Left.z+Right, Left.w+Right};
}

template <typename type> 
ak_v4<type> operator+(ak_v4<type> Left, ak_v4<type> Right)
{
    return {Left.x+Right.x, Left.y+Right.y, Left.z+Right.z, Left.w+Right.w};
}

template <typename type> 
ak_v4<type>& operator+=(ak_v4<type>& Left, type Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_v4<type>& operator+=(ak_v4<type>& Left, ak_v4<type> Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_v4<type> operator-(type Left, ak_v4<type> Right)
{
    return {Left-Right.x, Left-Right.y, Left-Right.z, Left-Right.w};
}

template <typename type> 
ak_v4<type> operator-(ak_v4<type> Left, type Right)
{
    return {Left.x-Right, Left.y-Right, Left.z-Right, Left.w-Right};
}

template <typename type> 
ak_v4<type> operator-(ak_v4<type> Left, ak_v4<type> Right)
{
    return {Left.x-Right.x, Left.y-Right.y, Left.z-Right.z, Left.w-Right.w};
}

template <typename type> 
ak_v4<type>& operator-=(ak_v4<type>& Left, type Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_v4<type>& operator-=(ak_v4<type>& Left, ak_v4<type> Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_v4<type> operator*(type Left, ak_v4<type> Right)
{
    return {Left*Right.x, Left*Right.y, Left*Right.z, Left*Right.w};
}

template <typename type> 
ak_v4<type> operator*(ak_v4<type> Left, type Right)
{
    return {Left.x*Right, Left.y*Right, Left.z*Right, Left.w*Right};
}

template <typename type> 
ak_v4<type> operator*(ak_v4<type> Left, ak_v4<type> Right)
{
    return {Left.x*Right.x, Left.y*Right.y, Left.z*Right.z, Left.w*Right.w};
}

template <typename type> 
ak_v4<type>& operator*=(ak_v4<type>& Left, type Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_v4<type>& operator*=(ak_v4<type>& Left, ak_v4<type> Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_v4<type> operator/(type Left, ak_v4<type> Right)
{
    return {Left/Right.x, Left/Right.y, Left/Right.z, Left/Right.w};
}

template <typename type> 
ak_v4<type> operator/(ak_v4<type> Left, type Right)
{
    return {Left.x/Right, Left.y/Right, Left.z/Right, Left.w/Right};
}

template <typename type> 
ak_v4<type> operator/(ak_v4<type> Left, ak_v4<type> Right)
{
    return {Left.x/Right.x, Left.y/Right.y, Left.z/Right.z, Left.w/Right.w};
}

template <typename type> 
ak_v4<type>& operator/=(ak_v4<type>& Left, type Right)
{
    Left = Left/Right;
    return Left;
}

template <typename type> 
ak_v4<type>& operator/=(ak_v4<type>& Left, ak_v4<type> Right)
{
    Left = Left/Right;
    return Left;
}

template <typename type> 
ak_v4<type> operator-(ak_v4<type> V)
{
    ak_v4<type> Result = {-V.x, -V.y, -V.z, -V.w};
    return Result;
}

#if 0
template <typename type> ak_bool operator!=(type Left, ak_v4<type> Right);
template <typename type> ak_bool operator!=(ak_v4<type> Left, type Right);
template <typename type> ak_bool operator!=(ak_v4<type> Left, ak_v4<type> Right);
template <typename type> ak_bool operator==(type Left, ak_v4<type> Right);
template <typename type> ak_bool operator==(ak_v4<type> Left, type Right);
#endif

template <typename type> 
ak_bool operator==(ak_v4<type> Left, ak_v4<type> Right)
{
    return (Left.x == Right.x) && (Left.y == Right.y) && (Left.z == Right.z) && (Left.w == Right.w);
}

#if 0 
template <typename type> ak_bool operator<(type Left, ak_v4<type> Right);
template <typename type> ak_bool operator<(ak_v4<type> Left, type Right);
template <typename type> ak_bool operator<(ak_v4<type> Left, ak_v4<type> Right);
template <typename type> ak_bool operator>(type Left, ak_v4<type> Right);
template <typename type> ak_bool operator>(ak_v4<type> Left, type Right);
template <typename type> ak_bool operator>(ak_v4<type> Left, ak_v4<type> Right);
template <typename type> ak_bool operator>=(type Left, ak_v4<type> Right);
template <typename type> ak_bool operator>=(ak_v4<type> Left, type Right);
template <typename type> ak_bool operator>=(ak_v4<type> Left, ak_v4<type> Right);
template <typename type> ak_bool operator<=(type Left, ak_v4<type> Right);
template <typename type> ak_bool operator<=(ak_v4<type> Left, type Right);
template <typename type> ak_bool operator<=(ak_v4<type> Left, ak_v4<type> Right);
#endif

template <typename type> 
ak_v4<type> AK_AbsV4(ak_v4<type> V)
{
    ak_v4<type> Result = {AK_Abs(V.x), AK_Abs(V.y), AK_Abs(V.z), AK_Abs(V.w)};
    return Result;
}

template <typename type> 
type AK_Dot(ak_v4<type> Left, ak_v4<type> Right)
{
    type Result = Left.x*Right.x + Left.y*Right.y + Left.z*Right.z + Left.w*Right.w;
    return Result;
}

template <typename type> 
type AK_SqrMagnitude(ak_v4<type> V)
{
    return AK_Dot(V, V);
}

template <typename type> type AK_Magnitude(ak_v4<type> V)
{
    return AK_Sqrt(AK_SqrMagnitude(V));
}

template <typename type> 
ak_v4<type> AK_Normalize(ak_v4<type> V)
{
    type InvLength = AK_Magnitude(V);
    if(InvLength == (type)0)
        return {};
    InvLength = (type)1/InvLength;
    return V*InvLength;
}

ak_v4f AK_InvalidV4f()
{
    ak_v4f Result = {INFINITY, INFINITY, INFINITY, INFINITY};
    return Result;
}

ak_v4f AK_V4f(ak_i32 x, ak_i32 y, ak_i32 z, ak_i32 w)
{
    ak_v4f Result = {(ak_f32)x, (ak_f32)y, (ak_f32)z, (ak_f32)w};
    return Result;
}

ak_v4f AK_V4f(ak_f64 x, ak_f64 y, ak_f64 z, ak_f64 w)
{
    ak_v4f Result = {(ak_f32)x, (ak_f32)y, (ak_f32)z, (ak_f32)w};
    return Result;    
}

ak_v4f AK_V4f(ak_f64* Data)
{
    ak_v4f Result = {(ak_f32)Data[0], (ak_f32)Data[1], (ak_f32)Data[2], (ak_f32)Data[3]};
    return Result;    
}

ak_bool AK_EqualApprox(ak_v4f A, ak_v4f B, ak_f32 Epsilon)
{
    return AK_SqrMagnitude(A-B) <= AK_Square(Epsilon);    
}

ak_v4f AK_Lerp(ak_v4f A, ak_f32 t, ak_v4f B)
{
    ak_v4f Result = (1-t)*A + t*B;
    return Result;
}

ak_color4f AK_RGBA(ak_f32 r, ak_f32 g, ak_f32 b, ak_f32 a)
{
    return {r, g, b, a};
}

ak_color4f AK_White4(ak_f32 a)
{
    return {1.0f, 1.0f, 1.0f, a};
}

ak_color4f AK_Red4(ak_f32 a)
{
    return {1.0f, 0.0f, 0.0f, a};
}

ak_color4f AK_Green4(ak_f32 a)
{
    return {0.0f, 1.0f, 0.0f, a};
}

ak_color4f AK_Blue4(ak_f32 a)
{
    return {0.0f, 0.0f, 1.0f, a};
}

ak_color4f AK_Yellow4(ak_f32 a)
{
    return {1.0f, 1.0f, 0.0f, a};
}

ak_color4f AK_Black4(ak_f32 a)
{
    return {0.0f, 0.0f, 0.0f, a};
}

ak_color4f AK_Cyan4(ak_f32 a)
{
    return {0.0f, 1.0f, 1.0f, a};
}

ak_color4f AK_Magenta4(ak_f32 a)
{
    return {1.0f, 0.0f, 1.0f, a};
}

ak_color4f AK_Orange4(ak_f32 a)
{
    return {1.0f, 0.0f, 1.0f, a};
}

ak_u32 AK_BGRA_U32(ak_color4f Color)
{
    ak_u8 B = (ak_u8)AK_Floor(Color.b >= 1.0f ? 255 : Color.b * 256.0f);
    ak_u8 G = (ak_u8)AK_Floor(Color.g >= 1.0f ? 255 : Color.g * 256.0f);
    ak_u8 R = (ak_u8)AK_Floor(Color.r >= 1.0f ? 255 : Color.r * 256.0f);
    ak_u8 A = (ak_u8)AK_Floor(Color.a >= 1.0f ? 255 : Color.a * 256.0f);
    
    return B | (G << 8) | (R << 16) | (A << 24);
}

ak_u32 AK_RGBA_U32(ak_color4f Color)
{
    ak_u8 B = (ak_u8)AK_Floor(Color.b >= 1.0f ? 255 : Color.b * 256.0f);
    ak_u8 G = (ak_u8)AK_Floor(Color.g >= 1.0f ? 255 : Color.g * 256.0f);
    ak_u8 R = (ak_u8)AK_Floor(Color.r >= 1.0f ? 255 : Color.r * 256.0f);
    ak_u8 A = (ak_u8)AK_Floor(Color.a >= 1.0f ? 255 : Color.a * 256.0f);
    
    return R | (G << 8) | (B << 16) | (A << 24);
}

template <typename type> 
ak_quat<type> AK_Quat(type x, type y, type z, type w)
{
    ak_quat<type> Result = {x, y, z, w};
    return Result;
}

template <typename type> 
ak_quat<type> AK_Quat(ak_v3<type> v, type s)
{
    ak_quat<type> Result;
    Result.v = v;
    Result.s = s;
    return Result;
}

template <typename type> 
ak_quat<type> AK_Quat(ak_v4<type> q)
{
    ak_quat<type> Result;
    Result.q = q;
    return Result;
}

template <typename type> 
ak_quat<type> AK_Quat(type* Data)
{
    ak_quat<type> Result = {Data[0], Data[1], Data[2], Data[3]};
    return Result;
}

template <typename type> 
ak_quat<type> operator+(type Left, ak_quat<type> Right)
{
    ak_quat<type> Result;
    Result.q = Left+Right.q;
    return Result;
}

template <typename type> 
ak_quat<type> operator+(ak_quat<type> Left, type Right)
{
    ak_quat<type> Result;
    Result.q = Left.q+Right;
    return Result;
}

template <typename type> 
ak_quat<type> operator+(ak_quat<type> Left, ak_quat<type> Right)
{
    ak_quat<type> Result;
    Result.q = Left.q+Right.q;
    return Result;
}

template <typename type> 
ak_quat<type>& operator+=(ak_quat<type>& Left, type Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_quat<type>& operator+=(ak_quat<type>& Left, ak_quat<type> Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_quat<type> operator-(type Left, ak_quat<type> Right)
{
    ak_quat<type> Result;
    Result.q = Left-Right.q;
    return Result;
}

template <typename type> 
ak_quat<type> operator-(ak_quat<type> Left, type Right)
{
    ak_quat<type> Result;
    Result.q = Left.q-Right;
    return Result;
}

template <typename type> 
ak_quat<type> operator-(ak_quat<type> Left, ak_quat<type> Right)
{
    ak_quat<type> Result;
    Result.q = Left.q-Right.q;
    return Result;
}

template <typename type> 
ak_quat<type>& operator-=(ak_quat<type>& Left, type Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_quat<type>& operator-=(ak_quat<type>& Left, ak_quat<type> Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_quat<type> operator*(type Left, ak_quat<type> Right)
{
    ak_quat<type> Result;
    Result.q = Left*Right.q;
    return Result;
}

template <typename type> 
ak_quat<type> operator*(ak_quat<type> Left, type Right)
{
    ak_quat<type> Result;
    Result.q = Left.q*Right;
    return Result;
}

template <typename type> 
ak_quat<type> operator*(ak_quat<type> Left, ak_quat<type> Right)
{
    ak_quat<type> Result = AK_Quat(AK_Cross(Left.v, Right.v) + Right.s*Left.v + Right.v*Left.s, 
                                   Left.s*Right.s - AK_Dot(Left.v, Right.v));
    return Result;    
}

template <typename type> 
ak_quat<type>& operator*=(ak_quat<type>& Left, type Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_quat<type>& operator*=(ak_quat<type>& Left, ak_quat<type> Right)
{
    Left = Left*Right;
    return Left;
}

#if 0 
template <typename type> ak_bool operator!=(type Left, ak_quat<type> Right);
template <typename type> ak_bool operator!=(ak_quat<type> Left, type Right);
template <typename type> ak_bool operator!=(ak_quat<type> Left, ak_quat<type> Right);
template <typename type> ak_bool operator==(type Left, ak_quat<type> Right);
template <typename type> ak_bool operator==(ak_quat<type> Left, type Right);
#endif

template <typename type> 
ak_bool operator==(ak_quat<type> Left, ak_quat<type> Right)
{
    return Left.q == Right.q;
}

#if 0
template <typename type> ak_bool operator<(type Left, ak_quat<type> Right);
template <typename type> ak_bool operator<(ak_quat<type> Left, type Right);
template <typename type> ak_bool operator<(ak_quat<type> Left, ak_quat<type> Right);
template <typename type> ak_bool operator>(type Left, ak_quat<type> Right);
template <typename type> ak_bool operator>(ak_quat<type> Left, type Right);
template <typename type> ak_bool operator>(ak_quat<type> Left, ak_quat<type> Right);
template <typename type> ak_bool operator>=(type Left, ak_quat<type> Right);
template <typename type> ak_bool operator>=(ak_quat<type> Left, type Right);
template <typename type> ak_bool operator>=(ak_quat<type> Left, ak_quat<type> Right);
template <typename type> ak_bool operator<=(type Left, ak_quat<type> Right);
template <typename type> ak_bool operator<=(ak_quat<type> Left, type Right);
template <typename type> ak_bool operator<=(ak_quat<type> Left, ak_quat<type> Right);
#endif

template <typename type> 
ak_quat<type> AK_EulerToQuat(type Roll, type Pitch, type Yaw)
{
    type cy = AK_Cos(Yaw/2);
    type sy = AK_Sin(Yaw/2);
    type cr = AK_Cos(Roll/2);
    type sr = AK_Sin(Roll/2);  
    type cp = AK_Cos(Pitch/2);
    type sp = AK_Sin(Pitch/2);
    
    ak_quat<type> Result;
    //q.x = sr * cp * cy - cr * sp * sy;
    Result.x = (cy*cp*sr) - (sy*sp*cr);
    //q.y = cr * sp * cy + sr * cp * sy;
    Result.y = (sy*cp*sr) + (cy*sp*cr);
    //q.z = cr * cp * sy - sr * sp * cy;
    Result.z = (sy*cp*cr) - (cy*sp*sr);
    //q.w = cr * cp * cy + sr * sp * sy;
    Result.w = (cy*cp*cr) + (sy*sp*sr);
    return AK_Normalize(Result);
}

template <typename type> 
ak_quat<type> AK_EulerToQuat(ak_v3<type> Euler)
{
    return AK_EulerToQuat(Euler.roll, Euler.pitch, Euler.yaw);
}

template <typename type> 
ak_quat<type> AK_MatrixToQuat(ak_m3<type> Matrix)
{
    ak_quat<type> Result;
    
    type Trace = Matrix.m00 + Matrix.m11 + Matrix.m22;
    if(Trace > (type)0)
    {
        type s = (type)0.5 / AK_Sqrt(Trace + 1);        
        Result.w = (type)0.25 / s;
        Result.x = (Matrix.m12 - Matrix.m21)*s;
        Result.y = (Matrix.m20 - Matrix.m02)*s;
        Result.z = (Matrix.m01 - Matrix.m10)*s;
        return Result;
    }    
    
    if((Matrix.m00 > Matrix.m11) && (Matrix.m00 > Matrix.m22))
    {
        type s = 2 * AK_Sqrt(1 + Matrix.m00 - Matrix.m11 - Matrix.m22);
        Result.w = (Matrix.m12 - Matrix.m21) / s;
        Result.x = (type)0.25 * s;
        Result.y = (Matrix.m10 + Matrix.m01) / s;
        Result.z = (Matrix.m20 + Matrix.m02) / s;
    }
    else if(Matrix.m11 > Matrix.m22)
    {
        type s = 2 * AK_Sqrt(1 + Matrix.m11 - Matrix.m00 - Matrix.m22);
        Result.w = (Matrix.m20 - Matrix.m02) / s;
        Result.x = (Matrix.m10 + Matrix.m01) / s;
        Result.y = (type)0.25 * s;
        Result.z = (Matrix.m21 + Matrix.m12) / s;
    }
    else
    {
        type s = 2 * AK_Sqrt(1 + Matrix.m22 - Matrix.m00 - Matrix.m11);
        Result.w = (Matrix.m01 - Matrix.m10) / s;
        Result.x = (Matrix.m20 + Matrix.m02) / s;
        Result.y = (Matrix.m21 + Matrix.m12) / s;
        Result.z = (type)0.25*s;
    }
    
    return Result;
}

template <typename type> 
ak_v3<type> AK_QuatToEuler(ak_quat<type> Quat)
{
    ak_v3<type> Result;
    
    type sinr_cosp = 2 * (Quat.w * Quat.x + Quat.y * Quat.z);
    type cosr_cosp = 1 - 2 * (Quat.x * Quat.x + Quat.y * Quat.y);
    Result.roll = AK_ATan2(sinr_cosp, cosr_cosp);
    
    type sinp = 2 * (Quat.w * Quat.y - Quat.z * Quat.x);
    if (AK_Abs(sinp) >= 1)
    {
        Result.pitch = copysignf(AK_PI/2, sinp);
    }
    else
    {
        Result.pitch = AK_ASin(sinp);
    }
    
    type siny_cosp = 2 * (Quat.w * Quat.z + Quat.x * Quat.y);
    type cosy_cosp = 1 - 2 * (Quat.y * Quat.y + Quat.z * Quat.z);
    Result.yaw = AK_ATan2(siny_cosp, cosy_cosp);
    
    return Result;
}

template <typename type> 
ak_m3<type>   AK_QuatToMatrix(ak_quat<type> Quat)
{
    type qxqy = Quat.x*Quat.y;
    type qwqz = Quat.w*Quat.z;
    type qxqz = Quat.x*Quat.z;
    type qwqy = Quat.w*Quat.y;
    type qyqz = Quat.y*Quat.z;
    type qwqx = Quat.w*Quat.x;
    
    type qxqx = AK_Square(Quat.x);
    type qyqy = AK_Square(Quat.y);
    type qzqz = AK_Square(Quat.z);
    
    ak_m3<type> Result = 
    {
        1 - 2*(qyqy+qzqz), 2*(qxqy+qwqz),     2*(qxqz-qwqy),   
        2*(qxqy-qwqz),     1 - 2*(qxqx+qzqz), 2*(qyqz+qwqx),   
        2*(qxqz+qwqy),     2*(qyqz-qwqx),     1 - 2*(qxqx+qyqy)
    };
    
    return Result;
}

template <typename type>
ak_v3<type> AK_QuatToXAxis(ak_quat<type> Quat)
{
    type qwqy = Quat.w*Quat.y;
    type qxqz = Quat.x*Quat.z;
    type qxqy = Quat.x*Quat.y;
    type qwqz = Quat.w*Quat.z;
    type qyqy = AK_Square(Quat.y);
    type qzqz = AK_Square(Quat.z);
    
    ak_v3<type> Result = {1 - 2*(qyqy+qzqz), 2*(qxqy+qwqz), 2*(qxqz-qwqy)};
    return Result;
}

template <typename type>
ak_v3<type> AK_QuatToYAxis(ak_quat<type> Quat)
{
    type qwqx = Quat.w*Quat.x;
    type qyqz = Quat.y*Quat.z;
    type qxqy = Quat.x*Quat.y;
    type qwqz = Quat.w*Quat.z;
    type qxqx = AK_Square(Quat.x);
    type qzqz = AK_Square(Quat.z);
    
    ak_v3<type> Result = {2*(qxqy-qwqz),     1 - 2*(qxqx+qzqz), 2*(qyqz+qwqx)};
    return Result;
}

template <typename type>
ak_v3<type> AK_QuatToZAxis(ak_quat<type> Quat)
{
    type qxqz = Quat.x*Quat.z;
    type qwqy = Quat.w*Quat.y;
    type qyqz = Quat.y*Quat.z;
    type qwqx = Quat.w*Quat.x;
    type qxqx = AK_Square(Quat.x);
    type qyqy = AK_Square(Quat.y);
    
    ak_v3<type> Result = {2*(qxqz+qwqy), 2*(qyqz-qwqx), 1 - 2*(qxqx+qyqy)};
    return Result;
}

template <typename type> 
ak_quat<type> AK_IdentityQuat()
{
    ak_quat<type> Result = {0.0f, 0.0f, 0.0f, 1.0f};
    return Result;
}

template <typename type> 
ak_quat<type> AK_Conjugate(ak_quat<type> Quat)
{
    ak_quat<type> Result;
    Result.v = -Quat.v;
    Result.s = Quat.s;    
    return Result;
}

template <typename type>          
type AK_SqrMagnitude(ak_quat<type> Quat)
{
    return AK_SqrMagnitude(Quat.q);
}

template <typename type> 
type AK_Magnitude(ak_quat<type> Quat)
{
    return AK_Magnitude(Quat.q);
}

template <typename type>          
ak_quat<type> AK_Normalize(ak_quat<type> Quat)
{
    return AK_Quat(AK_Normalize(Quat.q));
}

template <typename type>
ak_quat<type> AK_RotQuat(ak_v3<type> Axis, type Angle)
{
    ak_quat<type> Result;
    Result.v = Axis*AK_Sin(Angle/2);
    Result.s = AK_Cos(Angle/2);    
    return AK_Normalize(Result);
}

template <typename type>
ak_v3<type> AK_Rotate(ak_v3<type> V, ak_quat<type> Quat)
{
    ak_v3<type> Result = ((2 * AK_Dot(Quat.v, V) * Quat.v)   + 
                          ((AK_Square(Quat.s) - AK_SqrMagnitude(Quat.v))*V) + 
                          (2 * Quat.s * AK_Cross(Quat.v, V)));
    return Result;
}

template <typename type> 
ak_quat<type> AK_Inverse(ak_quat<type> Quat)
{
    type Denom = 1.0f/AK_SqrMagnitude(Quat);
    return AK_Conjugate(Quat)*Denom;
}

template <typename type> 
ak_quat<type> AK_QuatDiff(ak_quat<type> Q1, ak_quat<type> Q2)
{
    return AK_Inverse(Q1)*Q2;
}

ak_quatf AK_Lerp(ak_quatf A, ak_f32 t, ak_quatf B)
{
    ak_quatf Result = AK_Quat(AK_Normalize(AK_Lerp(A.q, t, B.q)));
    return Result;
}

ak_quatf AK_SLerp(ak_quatf A, ak_f32 t, ak_quatf B);

template <typename type> 
ak_m3<type> AK_M3()
{
    return {};
}

template <typename type> 
ak_m3<type> AK_M3(type Diagonal)
{
    ak_m3<type> Result = 
    {
        Diagonal, (type)0, (type)0, 
        (type)0, Diagonal, (type)0, 
        (type)0, (type)0, Diagonal
    };
    return Result;
}

template <typename type> 
ak_m3<type> AK_M3(ak_v3<type> Row0, ak_v3<type> Row1, ak_v3<type> Row2)
{
    ak_m3<type> Result;
    Result.Row0 = Row0;
    Result.Row1 = Row1;
    Result.Row2 = Row2;
    return Result;
}

template <typename type> 
ak_m3<type> AK_M3(type* Data)
{
    ak_m3<type> Result = 
    {
        Data[0], Data[1], Data[2], 
        Data[3], Data[4], Data[5],
        Data[6], Data[7], Data[8]
    };
    
    return Result;
}

template <typename type> 
ak_m3<type> AK_M3(ak_v3<type>* Rows)
{
    return AK_M3(Rows[0], Rows[1], Rows[2]);
}

template <typename type> 
ak_m3<type> AK_M3(ak_m4<type> M)
{
    ak_m3<type> Result;
    Result.Row0 = M.Row0.xyz;
    Result.Row1 = M.Row1.xyz;
    Result.Row2 = M.Row2.xyz;
    return Result;
}

template <typename type> 
ak_m3<type> AK_IdentityM3()
{
    ak_m3<type> Result = AK_M3((type)1);
    return Result;
}

template <typename type> 
void AK_Basis(ak_v3<type> Z, ak_v3<type>* X, ak_v3<type>* Y)
{
    Z = AK_Normalize(Z);
    ak_v3<type> Up = AK_V3((type)0, (type)1, (type)0);
    if(AK_EqualEps(Z, Up))
        Up = AK_V3((type)0, (type)0, (type)1);
    
    *X = -AK_Normalize(AK_Cross(Z, Up));
    *Y = AK_Cross(Z, *X);
}

template <typename type> 
ak_m3<type> AK_Basis(ak_v3<type> Z)
{
    Z = AK_Normalize(Z);
    ak_v3<type> X, Y;   
    AK_Basis(Z, &X, &Y);        
    return AK_M3(X, Y, Z);        
}

#if 0
template <typename type> type        AK_Determinant(ak_m3<type> M);
#endif

template <typename type> 
ak_m3<type> AK_Transpose(ak_m3<type> M)
{
    ak_m3<type> Result = 
    {
        M[0], M[3], M[6],
        M[1], M[4], M[7],
        M[2], M[5], M[8]
    };
    return Result;
}

#if 0 
template <typename type> ak_m3<type> AK_Inverse(ak_m3<type> M);
template <typename type> ak_m3<type> AK_TransformM3(ak_m3<type> Orient, ak_v3<type> Scale);
template <typename type> ak_m3<type> AK_TransformM3(ak_quat<type> Orient, ak_v3<type> Scale);
template <typename type> ak_m3<type> AK_InvTransformM3(ak_m3<type> Orient, ak_v3<type> Scale);
template <typename type> ak_m3<type> AK_InvTransformM3(ak_quat<type> Orient, ak_v3<type> Scale);
#endif

template <typename type> 
ak_m3<type> AK_InvTransformM3(ak_m3<type> M)
{
    type sx = (type)1/AK_SqrMagnitude(M.XAxis);
    type sy = (type)1/AK_SqrMagnitude(M.YAxis);
    type sz = (type)1/AK_SqrMagnitude(M.ZAxis);
    
    ak_v3<type> x = sx*M.XAxis;
    ak_v3<type> y = sy*M.YAxis;
    ak_v3<type> z = sz*M.ZAxis;
    
    ak_m3<type> Result = 
    {
        x.x, y.x, z.x,
        x.y, y.y, z.y,
        x.z, y.z, z.z,        
    };
    
    return Result;
}

template <typename type> 
ak_m3<type> AK_NormalizeM3(ak_m3<type> M)
{
    ak_m3<type> Result;
    Result.XAxis = AK_Normalize(M.XAxis);
    Result.YAxis = AK_Normalize(M.YAxis);
    Result.ZAxis = AK_Normalize(M.ZAxis);
    return Result;
}

template <typename type> 
ak_m3<type> operator+(type Left, ak_m3<type> Right)
{
    ak_m3<type> Result;
    Result.Row0 = Left+Right.Row0;
    Result.Row1 = Left+Right.Row1;
    Result.Row2 = Left+Right.Row2;
    return Result;
}

template <typename type> 
ak_m3<type> operator+(ak_m3<type> Left, type Right)
{
    ak_m3<type> Result;
    Result.Row0 = Left.Row0+Right;
    Result.Row1 = Left.Row1+Right;
    Result.Row2 = Left.Row2+Right;
    return Result;
}

template <typename type> 
ak_m3<type>& operator+=(ak_m3<type>& Left, type Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_m3<type> operator+(ak_m3<type> Left, ak_m3<type> Right)
{
    ak_m3<type> Result;
    Result.Row0 = Left.Row0 + Right.Row0;
    Result.Row1 = Left.Row1 + Right.Row1;
    Result.Row2 = Left.Row2 + Right.Row2;
    return Result;
}

template <typename type> 
ak_m3<type>& operator+=(ak_m3<type>& Left, ak_m3<type> Right)
{
    Left = Left+Right;
    return Left;
}

template <typename type> 
ak_m3<type> operator-(type Left, ak_m3<type> Right)
{
    ak_m3<type> Result;
    Result.Row0 = Left-Right.Row0;
    Result.Row1 = Left-Right.Row1;
    Result.Row2 = Left-Right.Row2;
    return Result;
}

template <typename type> 
ak_m3<type> operator-(ak_m3<type> Left, type Right)
{
    ak_m3<type> Result;
    Result.Row0 = Left.Row0-Right;
    Result.Row1 = Left.Row1-Right;
    Result.Row2 = Left.Row2-Right;
    return Result;
}

template <typename type> 
ak_m3<type>& operator-=(ak_m3<type>& Left, type Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_m3<type> operator-(ak_m3<type> Left, ak_m3<type> Right)
{
    ak_m3<type> Result;
    Result.Row0 = Left.Row0 - Right.Row0;
    Result.Row1 = Left.Row1 - Right.Row1;
    Result.Row2 = Left.Row2 - Right.Row2;
    return Result;
}

template <typename type> 
ak_m3<type>& operator-=(ak_m3<type>& Left, ak_m3<type> Right)
{
    Left = Left-Right;
    return Left;
}

template <typename type> 
ak_m3<type> operator*(type Left, ak_m3<type> Right)
{
    ak_m3<type> Result;
    Result.Row0 = Left*Right.Row0;
    Result.Row1 = Left*Right.Row1;
    Result.Row2 = Left*Right.Row2;
    return Result;
}

template <typename type> 
ak_m3<type> operator*(ak_m3<type> Left, type Right)
{
    ak_m3<type> Result;
    Result.Row0 = Left.Row0*Right;
    Result.Row1 = Left.Row1*Right;
    Result.Row2 = Left.Row2*Right;
    return Result;
}

template <typename type> 
ak_m3<type>& operator*=(ak_m3<type>& Left, type Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_m3<type> operator*(ak_m3<type> Left, ak_m3<type> Right)
{
    Right = AK_Transpose(Right);
    ak_m3<type> Result;
    
    Result.m00 = AK_Dot(Left.Rows[0], Right.Rows[0]);
    Result.m01 = AK_Dot(Left.Rows[0], Right.Rows[1]);
    Result.m02 = AK_Dot(Left.Rows[0], Right.Rows[2]);
    Result.m10 = AK_Dot(Left.Rows[1], Right.Rows[0]);
    Result.m11 = AK_Dot(Left.Rows[1], Right.Rows[1]);
    Result.m12 = AK_Dot(Left.Rows[1], Right.Rows[2]);
    Result.m20 = AK_Dot(Left.Rows[2], Right.Rows[0]);
    Result.m21 = AK_Dot(Left.Rows[2], Right.Rows[1]);
    Result.m22 = AK_Dot(Left.Rows[2], Right.Rows[2]);
    return Result;
}

template <typename type> 
ak_m3<type>& operator*=(ak_m3<type>& Left, ak_m3<type> Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_v3<type> operator*(ak_v3<type> Left, ak_m3<type> Right)
{
    Right = AK_Transpose(Right);
    
    ak_v3<type> Result;
    Result.x = AK_Dot(Left, Right.XAxis);
    Result.y = AK_Dot(Left, Right.YAxis);
    Result.z = AK_Dot(Left, Right.ZAxis);
    return Result;
}

template <typename type> 
ak_v3<type>& operator*=(ak_v3<type>& Left, ak_m3<type> Right)
{
    Left = Left*Right;
    return Left;
}

ak_m3f AK_OrientAt(ak_v3f Position, ak_v3f Target, ak_v3f Up)
{
    ak_v3f Z = AK_Normalize(Position-Target);
    if(AK_EqualEps(Z, Up))
        Up = AK_YAxis();
    
    ak_v3f X = -AK_Normalize(AK_Cross(Z, Up));
    ak_v3f Y = AK_Cross(Z, X);
    
    ak_m3f Result = AK_M3(X, Y, Z);
    return Result;
}

ak_m3f AK_M3f(ak_f64* Data)
{
    ak_m3f Result = 
    {
        (ak_f32)Data[0], (ak_f32)Data[1], (ak_f32)Data[2],
        (ak_f32)Data[3], (ak_f32)Data[4], (ak_f32)Data[5],
        (ak_f32)Data[6], (ak_f32)Data[7], (ak_f32)Data[8]
    };
    
    return Result;
}

template <typename type> 
ak_m4<type> AK_M4()
{
    return {};
}

template <typename type> 
ak_m4<type> AK_M4(type Diagonal)
{
    ak_m4<type> Result = 
    {
        Diagonal, (type)0,  (type)0,  (type)0,
        (type)0,  Diagonal, (type)0,  (type)0, 
        (type)0,  (type)0,  Diagonal, (type)0, 
        (type)0,  (type)0,  (type)0,  Diagonal
    };
    
    return Result;
}

template <typename type> ak_m4<type> AK_M4(ak_v4<type> Row0, ak_v4<type> Row1, ak_v4<type> Row2, ak_v4<type> Row3);
template <typename type> ak_m4<type> AK_M4(ak_v4<type>* Rows);
template <typename type> ak_m4<type> AK_M4(ak_v3<type> Row0, ak_v3<type> Row1, ak_v3<type> Row2, ak_v3<type> Row3);
template <typename type> ak_m4<type> AK_M4(ak_v3<type>* Rows);
template <typename type> ak_m4<type> AK_M4(type* Data);

template <typename type> 
ak_m4<type> AK_IdentityM4()
{
    return AK_M4((type)1);
}

template <typename type> 
type AK_Determinant(ak_m4<type> M)
{
    type Result = (M.m00 * AK_Determinant(M.Rows[1].yzw, M.Rows[2].yzw, M.Rows[3].yzw) - 
                   M.m10 * AK_Determinant(M.Rows[0].yzw, M.Rows[2].yzw, M.Rows[3].yzw) + 
                   M.m20 * AK_Determinant(M.Rows[0].yzw, M.Rows[1].yzw, M.Rows[3].yzw) - 
                   M.m30 * AK_Determinant(M.Rows[0].yzw, M.Rows[1].yzw, M.Rows[2].yzw));    
    return Result;
}

template <typename type> 
ak_m4<type> AK_Transpose(ak_m4<type> M)
{
    ak_m4<type> Result = 
    {
        M[0], M[4], M[8],  M[12],
        M[1], M[5], M[9],  M[13], 
        M[2], M[6], M[10], M[14],
        M[3], M[7], M[11], M[15]
    };
    
    return Result;
}

template <typename type> 
ak_m4<type> AK_Inverse(ak_m4<type> M)
{
    type Det = AK_Determinant(M);
    AK_Assert(!AK_EqualZeroEps(Det), "Matrix is not invertable");
    
    ak_m4<type> Adjoint = 
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
    
    ak_m4<type> Result = ((type)1/Det) * Adjoint;    
    return Result;
}

template <typename type> 
ak_m4<type> AK_TransformM4(ak_v3<type> Translation)
{
    ak_m4<type> Result = AK_IdentityM4<type>();
    Result.Translation.xyz = Translation;
    return Result;
}

template <typename type> 
ak_m4<type> AK_TransformM4(ak_v3<type> Translation, ak_v3<type> XAxis, ak_v3<type> YAxis, ak_v3<type> ZAxis)
{
    ak_m4<type> Result = {};
    Result.XAxis.xyz = XAxis;
    Result.YAxis.xyz = YAxis;
    Result.ZAxis.xyz = ZAxis;
    Result.Translation = AK_V4(Translation, 1.0f);
    return Result;
}

template <typename type> 
ak_m4<type> AK_TransformM4(ak_v3<type> Translation, ak_m3<type>  Orientation)
{
    return AK_TransformM4(Translation, Orientation.XAxis, Orientation.YAxis, Orientation.ZAxis);    
}

template <typename type> 
ak_m4<type> AK_TransformM4(ak_v3<type> Translation, ak_quat<type> Orientation)
{
    return AK_TransformM4(Translation, AK_QuatToMatrix(Orientation));
}

template <typename type> 
ak_m4<type> AK_TransformM4(ak_v3<type> Translation, ak_v3<type> Scale)
{
    return AK_TransformM4(Translation, AK_V3(Scale.x, (type)0, (type)0), 
                          AK_V3((type)0, Scale.y, (type)0), AK_V3((type)0, (type)0, Scale.z));
}

template <typename type> 
ak_m4<type> AK_TransformM4(ak_v3<type> Translation, ak_m3<type> Orientation, ak_v3<type> Scale)
{
    return AK_TransformM4(Translation, Orientation.XAxis*Scale.x, Orientation.YAxis*Scale.y, Orientation.ZAxis*Scale.z);
}

template <typename type> 
ak_m4<type> AK_TransformM4(ak_v3<type> Translation, ak_quat<type> Orientation, ak_v3<type> Scale)
{
    return AK_TransformM4(Translation, AK_QuatToMatrix(Orientation), Scale);
}

template <typename type> 
ak_m4<type> AK_TransformM4(ak_sqt<type> Transform)
{
    return AK_TransformM4(Transform.Translation, Transform.Orientation, Transform.Scale);
}

template <typename type> 
ak_m4<type> AK_ScaleM4(ak_v3<type> Scale)
{
    return 
    {
        Scale.x, (type)0, (type)0, (type)0, 
        (type)0, Scale.y, (type)0, (type)0, 
        (type)0, (type)0, Scale.z, (type)0, 
        (type)0, (type)0, (type)0, (type)1
    };
}

template <typename type> ak_m4<type> AK_InvScale(ak_v3<type> Scale)
{
    Scale = (type)1/Scale;    
    return AK_ScaleM4(Scale);    
};

template <typename type> 
ak_m4<type> AK_XRotM4(type Radians)
{
    type c = AK_Cos(Radians);
    type s = AK_Sin(Radians);
    
    return 
    {
        (type)1, (type)0, (type)0, (type)0, 
        (type)0,       c,       s, (type)0, 
        (type)0,      -s,       c, (type)0, 
        (type)0, (type)0, (type)0, (type)1
    };
}

template <typename type> 
ak_m4<type> AK_YRotM4(type Radians)
{
    type c = AK_Cos(Radians);
    type s = AK_Sin(Radians);
    
    return 
    {
        c,       (type)0,       -s, (type)0, 
        (type)0, (type)1,  (type)0, (type)0, 
        s,       (type)0,        c, (type)0, 
        (type)0, (type)0,  (type)0, (type)1                                    
    };        
}

template <typename type> 
ak_m4<type> AK_ZRotM4(type Radians)
{
    type c = AK_Cos(Radians);
    type s = AK_Sin(Radians);
    
    return
    {
        c,             s, (type)0, (type)0, 
        -s,            c, (type)0, (type)0, 
        (type)0, (type)0, (type)1, (type)0, 
        (type)0, (type)0, (type)0, (type)1
    };
}

template <typename type> 
ak_m4<type> AK_XYZRotM4(ak_v3<type> Radians)
{
    return AK_ZRotM4(Radians.z) * (AK_YRotM4(Radians.y) * AK_XRotM4(Radians.x));
}

template <typename type> 
ak_m4<type> AK_InvTransformM4(ak_v3<type> Translation, ak_v3<type> XAxis, ak_v3<type> YAxis, ak_v3<type> ZAxis)
{
    type tx = -AK_Dot(Translation, XAxis);
    type ty = -AK_Dot(Translation, YAxis);
    type tz = -AK_Dot(Translation, ZAxis);
    
    ak_m4<type> Result = 
    {
        XAxis.x, YAxis.x, ZAxis.x, (type)0,
        XAxis.y, YAxis.y, ZAxis.y, (type)0,
        XAxis.z, YAxis.z, ZAxis.z, (type)0,
        tx,      ty,      tz,      (type)1 
    };
    
    return Result;
}

template <typename type> 
ak_m4<type> AK_InvTransformM4(ak_v3<type> Translation, ak_m3<type>  Orientation)
{
    return AK_InvTransformM4(Translation, Orientation.XAxis, Orientation.YAxis, Orientation.ZAxis);
}

template <typename type> 
ak_m4<type> AK_InvTransformM4(ak_v3<type> Translation, ak_quat<type> Orientation)
{
    reutrn AK_InvTransformM4(Translation, AK_QuatToMatrix(Orientation));
}

template <typename type> 
ak_m4<type> AK_InvTransformM4(ak_m4<type> M)
{
    type sx = (type)1/AK_SqrMagnitude(M.XAxis.xyz);
    type sy = (type)1/AK_SqrMagnitude(M.YAxis.xyz);
    type sz = (type)1/AK_SqrMagnitude(M.ZAxis.xyz);
    
    ak_v3<type> x = sx*M.XAxis.xyz;
    ak_v3<type> y = sy*M.YAxis.xyz;
    ak_v3<type> z = sz*M.ZAxis.xyz;
    
    ak_f32 tx = -AK_Dot(M.Translation.xyz, x);
    ak_f32 ty = -AK_Dot(M.Translation.xyz, y);
    ak_f32 tz = -AK_Dot(M.Translation.xyz, z);
    
    ak_m4<type> Result = 
    {
        x.x, y.x, z.x, (type)0,
        x.y, y.y, z.y, (type)0,
        x.z, y.z, z.z, (type)0,
        tx,  ty,  tz,  (type)1
    };
    
    return Result;
}

#if 0 
template <typename type> ak_m4<type> operator+(type Left, ak_m4<type> Right);
template <typename type> ak_m4<type> operator+(ak_m4<type> Left, type Right);
template <typename type> ak_m4<type> operator+(ak_m4<type> Left, ak_m4<type> Right);
template <typename type> ak_m4<type>& operator+=(ak_m4<type>& Left, type Right);
template <typename type> ak_m4<type>& operator+=(ak_m4<type>& Left, ak_m4<type>& Right);
template <typename type> ak_m4<type> operator-(type Left, ak_m4<type> Right);
template <typename type> ak_m4<type> operator-(ak_m4<type> Left, type Right);
template <typename type> ak_m4<type> operator-(ak_m4<type> Left, ak_m4<type> Right);
template <typename type> ak_m4<type>& operator-=(ak_m4<type>& Left, type Right);
template <typename type> ak_m4<type>& operator-=(ak_m4<type>& Left, ak_m4<type> Right);
#endif

template <typename type> 
ak_m4<type> operator*(type Left, ak_m4<type> Right)
{
    ak_m4<type> Result;
    Result.Row0 = Left*Right.Row0;
    Result.Row1 = Left*Right.Row1;
    Result.Row2 = Left*Right.Row2;
    Result.Row3 = Left*Right.Row3;
    return Result;
}

template <typename type> 
ak_m4<type> operator*(ak_m4<type> Left, type Right)
{
    ak_m4<type> Result;
    Result.Row0 = Left.Row0*Right;
    Result.Row1 = Left.Row1*Right;
    Result.Row2 = Left.Row2*Right;
    Result.Row3 = Left.Row3*Right;
    return Result;
}

template <typename type> 
ak_m4<type>& operator*=(ak_m4<type>& Left, type Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_m4<type> operator*(ak_m4<type> Left, ak_m4<type> Right)
{
    Right = AK_Transpose(Right);
    ak_m4<type> Result;
    
    Result.m00 = AK_Dot(Left.Rows[0], Right.Rows[0]);
    Result.m01 = AK_Dot(Left.Rows[0], Right.Rows[1]);
    Result.m02 = AK_Dot(Left.Rows[0], Right.Rows[2]);
    Result.m03 = AK_Dot(Left.Rows[0], Right.Rows[3]);
    
    Result.m10 = AK_Dot(Left.Rows[1], Right.Rows[0]);
    Result.m11 = AK_Dot(Left.Rows[1], Right.Rows[1]);
    Result.m12 = AK_Dot(Left.Rows[1], Right.Rows[2]);
    Result.m13 = AK_Dot(Left.Rows[1], Right.Rows[3]);
    
    Result.m20 = AK_Dot(Left.Rows[2], Right.Rows[0]);
    Result.m21 = AK_Dot(Left.Rows[2], Right.Rows[1]);
    Result.m22 = AK_Dot(Left.Rows[2], Right.Rows[2]);
    Result.m23 = AK_Dot(Left.Rows[2], Right.Rows[3]);
    
    Result.m30 = AK_Dot(Left.Rows[3], Right.Rows[0]);
    Result.m31 = AK_Dot(Left.Rows[3], Right.Rows[1]);
    Result.m32 = AK_Dot(Left.Rows[3], Right.Rows[2]);
    Result.m33 = AK_Dot(Left.Rows[3], Right.Rows[3]);
    return Result;
}

template <typename type> 
ak_m4<type>& operator*=(ak_m4<type>& Left, ak_m4<type> Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_v4<type> operator*(ak_v4<type> Left, ak_m4<type> Right)
{
    Right = AK_Transpose(Right);
    ak_v4<type> Result;
    Result.x = AK_Dot(Left, Right.Rows[0]);
    Result.y = AK_Dot(Left, Right.Rows[1]);
    Result.z = AK_Dot(Left, Right.Rows[2]);
    Result.w = AK_Dot(Left, Right.Rows[3]);
    return Result;
}

template <typename type> 
ak_v4<type>& operator*=(ak_v4<type>& Left, ak_m4<type> Right)
{
    Left = Left*Right;
    return Left;
}

template <typename type> 
ak_m4<type> AK_Perspective(type FOV, type AspectRatio, type Near, type Far)
{
    type c = (type)1/AK_Tan(FOV*0.5f);
    type a = AspectRatio;
    
    ak_m4<type> Result = 
    {
        c/a,     (type)0,  (type)0,                       (type)0,
        (type)0, c,        (type)0,                       (type)0,
        (type)0, (type)0, -(Far+Near)/(Far-Near),         (type)-1,
        (type)0, (type)0, -((type)2*Far*Near)/(Far-Near), (type)0
    };
    
    return Result;
}

template <typename type> 
ak_m4<type> AK_Orthographic(type Left, type Right, type Top, type Bottom, type Near, type Far)
{
    ak_m4<type> Result = 
    {
        (type)2/(Right-Left),        (type)0,                    (type)0,               (type)0,
        (type)0,                     (type)2/(Top-Bottom),       (type)0,               (type)0, 
        (type)0,                     (type)0,                    (type)2/(Far-Near),    (type)0, 
        -(Right+Left)/(Right-Left), -(Top+Bottom)/(Top-Bottom), -(Far+Near)/(Far-Near), (type)1
    };
    
    return Result;
}

template <typename type> 
ak_v3<type> AK_TransformPoint(ak_v3<type> Point, ak_m4<type> Transform)
{
    return (AK_V4(Point, (type)1) * Transform).xyz;    
}

template <typename type> 
void AK_TransformPoints(ak_v3<type>* Points, ak_u32 PointCount, ak_m4<type> Transform)
{
    for(ak_u32 PointIndex = 0; PointIndex < PointCount; PointIndex++)
        Points[PointIndex] = AK_TransformPoint(Points[PointIndex], Transform);
}

ak_m4f AK_LookAt(ak_v3f Position, ak_v3f Target, ak_v3f Up)
{
    ak_v3f Z = AK_Normalize(Position-Target);
    if(AK_EqualEps(Z, Up))
        Up = AK_YAxis();
    
    ak_v3f X = -AK_Normalize(AK_Cross(Z, Up));
    ak_v3f Y = AK_Cross(Z, X);
    return AK_InvTransformM4(Position, X, Y, Z);
}

ak_m4f AK_M4f(ak_f64* Data)
{
    ak_m4f Result = 
    {
        (ak_f32)Data[0],  (ak_f32)Data[1],  (ak_f32)Data[2],  (ak_f32)Data[3],
        (ak_f32)Data[4],  (ak_f32)Data[5],  (ak_f32)Data[6],  (ak_f32)Data[7],
        (ak_f32)Data[8],  (ak_f32)Data[9],  (ak_f32)Data[10], (ak_f32)Data[11],
        (ak_f32)Data[12], (ak_f32)Data[13], (ak_f32)Data[14], (ak_f32)Data[15]
    };
    
    return Result;
}

template <typename type> 
ak_sqt<type> AK_SQT()
{
    ak_sqt<type> Result = {};
    Result.Translation = AK_V3<type>();
    Result.Orientation = AK_IdentityQuat<type>();
    Result.Scale = AK_V3((type)1, (type)1, (type)1);
    return Result;
}

template <typename type> 
ak_sqt<type> AK_SQT(ak_v3<type> Translation)
{
    ak_sqt<type> Result = AK_SQT<type>();
    Result.Translation = Translation;
    return Result;
}

template <typename type> 
ak_sqt<type> AK_SQT(ak_v3<type> Translation, ak_quat<type> Orientation)
{
    ak_sqt<type> Result = {};
    Result.Translation = Translation;
    Result.Orientation = Orientation;
    Result.Scale = AK_V3((type)1, (type)1, (type)1);
    return Result;
}

template <typename type> 
ak_sqt<type> AK_SQT(ak_v3<type> Translation, ak_v3<type> Scale)
{
    ak_sqt<type> Result = {};
    Result.Translation = Translation;
    Result.Orientation = AK_IdentityQuat<type>();
    Result.Scale = Scale;
    return Result;
}

template <typename type> 
ak_sqt<type> AK_SQT(ak_v3<type> Translation, type Scale)
{
    return AK_SQT(Translation, AK_V3(Scale, Scale, Scale));    
}

template <typename type> 
ak_sqt<type> AK_SQT(ak_v3<type> Translation, ak_quat<type> Orientation, ak_v3<type> Scale)
{
    ak_sqt<type> Result = {};
    Result.Translation = Translation;
    Result.Orientation = Orientation;
    Result.Scale = Scale;
    return Result;
}

template <typename type> 
ak_sqt<type> AK_SQT(ak_v3<type> Translation, ak_quat<type> Orientation, type Scale)
{
    return AK_SQT(Translation, Orientation, AK_V3(Scale, Scale, Scale));
}

template <typename type> 
ak_sqt<type> AK_SQT(ak_v3<type> Translation, ak_m3<type> Orientation)
{
    return AK_SQT(Translation, AK_MatrixToQuat(Orientation));
}

template <typename type> 
ak_sqt<type> AK_SQT(ak_m4<type> M)
{
    ak_sqt<type> Result = {};
    Result.Translation = M.Translation.xyz;
    Result.Scale = AK_V3(AK_Magnitude(M.XAxis.xyz), AK_Magnitude(M.YAxis.xyz), AK_Magnitude(M.ZAxis.xyz));    
    ak_m3<type> Rotation = AK_M3(M.XAxis.xyz/Result.Scale.x, M.YAxis.xyz/Result.Scale.y, M.ZAxis.xyz/Result.Scale.z);
    Result.Orientation = AK_MatrixToQuat(Rotation);
    return Result;
}

template <typename type> 
ak_sqt<type> operator*(ak_sqt<type> A, ak_sqt<type> B)
{
    ak_sqt<type> Result = {};
    Result.Orientation = A.Orientation*B.Orientation;
    Result.Scale = A.Scale*B.Scale;
    Result.Translation = AK_Rotate(A.Translation*B.Scale, Result.Orientation) + B.Translation;
    return Result;
}

template <typename type> 
ak_sqt<type>& operator*=(ak_sqt<type>& A, ak_sqt<type> B)
{
    A = A*B;
    return A;
}

template <typename type> 
ak_bool operator==(ak_sqt<type> A, ak_sqt<type> B)
{
    return ((A.Translation == B.Translation) &&
            (A.Orientation == B.Orientation) &&
            (A.Scale == B.Scale));
}

template <typename type> 
ak_v3<type> AK_Transform(ak_v3<type> Point, ak_v3<type> Translation, ak_quat<type> Orientation, ak_v3<type> Scale)
{
    ak_v3<type> Result = AK_Rotate(Point*Scale, Orientation)+Translation;
    return Result;
}

template <typename type> 
ak_v3<type> AK_Transform(ak_v3<type> Point, ak_sqt<type> Transform)
{
    return AK_Transform(Point, Transform.Translation, Transform.Orientation, Transform.Scale);
}

#if 0
template <typename type> ak_v3<type> AK_InverseTransform(ak_v3<type> Point, ak_v3<type> Translation, ak_quat<type> Orientation, ak_v3<type> Scale);
template <typename type> ak_v3<type> AK_InverseTransform(ak_v3<type> Point, ak_sqt<type> Transform);
#endif

template <typename type> 
ak_plane<type> AK_Plane(ak_v3<type> Origin, ak_v3<type> Normal)
{
    ak_plane<type> Result = {};
    Result.Normal = Normal;
    Result.Origin = Origin;
    Result.Equation[0] = Normal.x;
    Result.Equation[1] = Normal.y;
    Result.Equation[2] = Normal.z;
    Result.Equation[3] = -(Normal.x*Origin.x + Normal.y*Origin.y + Normal.z*Origin.z);
    return Result;
}

template <typename type> 
type AK_SignDistance(ak_plane<type> Plane, ak_v3<type> Point)
{
    return AK_Dot(Point, Plane.Normal) + Plane.Equation[3];
}

ak_quadratic_equation_result AK_SolveQuadraticEquation(ak_f32 a, ak_f32 b, ak_f32 c)
{
    ak_quadratic_equation_result Result = {};
    
    ak_f32 Determinant = b*b - 4*a*c;
    if(Determinant < 0)
        return Result;
    
    ak_f32 Discriminant = AK_Sqrt(Determinant);    
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

template <typename type> 
ak_frustum<type> AK_CreateFrustum(ak_m4<type> Matrix)
{
    ak_frustum<type> Result = {};
    ak_v3<type> Col1 = AK_V3(Matrix.m00, Matrix.m10, Matrix.m20);
    ak_v3<type> Col2 = AK_V3(Matrix.m01, Matrix.m11, Matrix.m21);
    ak_v3<type> Col3 = AK_V3(Matrix.m02, Matrix.m12, Matrix.m22);
    ak_v3<type> Col4 = AK_V3(Matrix.m03, Matrix.m13, Matrix.m23);
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
    for(ak_i32 PlaneIndex = 0; PlaneIndex < 6; PlaneIndex++)
    {
        type Mag = (type)1/AK_Magnitude(Result.Normals[PlaneIndex]);
        Result.Normals[PlaneIndex] *= Mag;
        Result.Distances[PlaneIndex] *= Mag;
    }
    return Result;
}

template <typename type> 
void AK_GetFrustumCorners(ak_v3<type>* Corners, ak_m4<type> Perspective)
{
    ak_m4<type> InversePerspective = AK_Inverse(Perspective);
    ak_v4<type> Intermediate[8];
    Intermediate[0] = AK_V4((type)-1, (type)-1, (type)-1, (type)1) * InversePerspective;
    Intermediate[1] = AK_V4((type) 1, (type)-1, (type)-1, (type)1) * InversePerspective;
    Intermediate[2] = AK_V4((type) 1, (type) 1, (type)-1, (type)1) * InversePerspective;
    Intermediate[3] = AK_V4((type)-1, (type) 1, (type)-1, (type)1) * InversePerspective;
    Intermediate[4] = AK_V4((type) 1, (type)-1, (type) 1, (type)1) * InversePerspective;
    Intermediate[5] = AK_V4((type)-1, (type)-1, (type) 1, (type)1) * InversePerspective;
    Intermediate[6] = AK_V4((type)-1, (type) 1, (type) 1, (type)1) * InversePerspective;
    Intermediate[7] = AK_V4((type) 1, (type) 1, (type) 1, (type)1) * InversePerspective;
    
    Corners[0] = Intermediate[0].xyz / Intermediate[0].w;
    Corners[1] = Intermediate[1].xyz / Intermediate[1].w;
    Corners[2] = Intermediate[2].xyz / Intermediate[2].w;
    Corners[3] = Intermediate[3].xyz / Intermediate[3].w;
    Corners[4] = Intermediate[4].xyz / Intermediate[4].w;
    Corners[5] = Intermediate[5].xyz / Intermediate[5].w;
    Corners[6] = Intermediate[6].xyz / Intermediate[6].w;
    Corners[7] = Intermediate[7].xyz / Intermediate[7].w;
}