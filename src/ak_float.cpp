ak_f32 AK__Internal_RoundPrecision(ak_f32 Value, ak_u32 X)
{        
    ak_f32 Result = (ak_f32)AK_Round(X*Value)/(ak_f32)X;
    return Result;
}

inline ak_u32 AK__Internal_GetPrecision(ak_u32 Precision)
{
    ak_u32 X = 1;
    Precision--;
    while(Precision > 0) { X *= 10; Precision--; }    
    return X;
}

ak_f32 AK_RoundPrecision(ak_f32 Value, ak_u32 Precision)
{
    ak_u32 X = AK__Internal_GetPrecision(Precision);
    ak_f32 Result = AK__Internal_RoundPrecision(Value, X);
    return Result;
}
ak_bool AK_EqualApprox(ak_f32 A, ak_f32 Eps)
{
    ak_bool Result = AK_Abs(A) < Eps;
    return Result;
}

ak_bool AK_EqualApprox(ak_f64 A, ak_f64 Eps)
{
    ak_bool Result = AK_Abs(A) < Eps;
    return Result;
}

ak_bool AK_EqualZeroEps(ak_f32 V)
{
    return AK_EqualApprox(V, AK_EPSILON32);    
}

ak_bool AK_EqualZeroEps(ak_f64 V)
{
    return AK_EqualApprox(V, AK_EPSILON64);    
}

ak_bool AK_EqualEps(ak_f32 A, ak_f32 B)
{
    ak_f32 ab = AK_Abs(A-B);
    if(ab < AK_EPSILON32)
        return true;
    
    ak_f32 aAbs = AK_Abs(A);
    ak_f32 bAbs = AK_Abs(B);
    if(bAbs > aAbs)
    {
        return ab < AK_EPSILON32*bAbs;
    }
    else
    {
        return ab < AK_EPSILON32*aAbs;
    }
}

ak_bool AK_EqualEps(ak_f64 A, ak_f64 B)
{
    ak_f64 ab = AK_Abs(A-B);
    if(ab < AK_EPSILON64)
        return true;
    
    ak_f64 aAbs = AK_Abs(A);
    ak_f64 bAbs = AK_Abs(B);
    if(bAbs > aAbs)
    {
        return ab < AK_EPSILON64*bAbs;
    }
    else
    {
        return ab < AK_EPSILON64*aAbs;
    }
}

ak_bool AK_IsNan(ak_f32 V)
{
    return isnan(V);
}