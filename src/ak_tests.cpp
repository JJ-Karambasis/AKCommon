void MathV2Tests()
{
    
    {
        ak_v2f A = {1, 2};
        ASSERT(A[1] == 2);
        A[0] = 5;
        ASSERT(A[0] == 5);
        ASSERT(A.LargestComp() == 0);
        
        ak_v4f C = {10, -4, -1010101, 4};
        C[3] = 100;
        ASSERT(C[3] == 100);
        ASSERT(C.LargestComp() == 2);
        
        ak_quatf D = {1, 1, 1, 100};
        ASSERT(D[3] == 100);                
        
        ak_m3f E = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        E[7] = 10;
        ASSERT(E[7] == 10);
        
        ak_m4f F = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        F[15] = 100;
        ASSERT(F[15] == 100);
    }    
    
    
    {
        ak_v2f A = AK_V2<ak_f32>();
        ASSERT(A.x == 0 && A.y == 0);
        
        ak_v2f B = AK_V2(2.0f, 5.0f);
        ASSERT(B.x == 2 && B.y == 5);
        
        ak_f32 Data[2] = {10, 13};
        ak_v2f C = AK_V2(Data);
        ASSERT(C.x == 10 && C.y == 13);
    }
    
    {
        ak_v2f A = AK_V2(10.0f, 15.0f);
        ak_v2f B = AK_V2(19.0f, 10.0f);
        ak_v2f C = AK_V2(-100.0f, -12.0f);
        
        ak_v2f D = 10.0f + A;
        ak_v2f E = B + -1.0f;
        ak_v2f F = A+B;
        C += 1.0f;
        C += A;
        
        ASSERT(D.x == 20 && D.y == 25);
        ASSERT(E.x == 18 && E.y == 9);
        ASSERT(F.x == 29 && F.y == 25);
        ASSERT(C.x == -89 && C.y == 4);
    }
    
    {
        ak_v2f A = AK_V2(10.0f, 15.0f);
        ak_v2f B = AK_V2(19.0f, 10.0f);
        ak_v2f C = AK_V2(-100.0f, -12.0f);
        
        ak_v2f D = 10.0f - A;
        ak_v2f E = B - -1.0f;
        ak_v2f F = A-B;
        C -= 1.0f;
        C -= A;
        
        ASSERT(D.x == 0 && D.y == -5);
        ASSERT(E.x == 20 && E.y == 11);
        ASSERT(F.x == -9 && F.y == 5);
        ASSERT(C.x == -111 && C.y == -28);
    }
    
    {
        ak_v2f A = AK_V2(10.0f, 15.0f);
        ak_v2f B = AK_V2(19.0f, 10.0f);
        ak_v2f C = AK_V2(-100.0f, -12.0f);
        
        ak_v2f D = 10.0f * A;
        ak_v2f E = B * -1.0f;
        ak_v2f F = A*B;
        C *= 2.0f;
        C *= A;
        
        ASSERT(D.x == 100 && D.y == 150);
        ASSERT(E.x == -19 && E.y == -10);
        ASSERT(F.x == 190 && F.y == 150);
        ASSERT(C.x == -2000 && C.y == -360);
    }
    
    
    {
        ak_v2f A = AK_V2(100.0f, 50.0f);
        ak_v2f B = AK_V2(25.0f, 10.0f);
        ak_v2f C = AK_V2(-100.0f, -40.0f);
        
        ak_v2f D = 10.0f / A;
        ak_v2f E = B / -5.0f;
        ak_v2f F = A/B;
        C /= 2.0f;
        C /= A;
        
        ASSERT(D.x == 0.1f && D.y == 0.2f);
        ASSERT(E.x == -5 && E.y == -2);
        ASSERT(F.x == 4 && F.y == 5);
        ASSERT(C.x == -0.5f && C.y == -0.4f);
        
        A = -A;
        ASSERT(A.x == -100.0f && A.y == -50.0f);
    }
    
    {
        ak_v2f A = AK_V2(100.0f, 50.0f);
        ak_v2f B = AK_V2(90.0f, 40.0f);
        ak_v2f C = AK_V2(-23.0f, 100.0f);
        ak_v2f D = AK_V2(25.0f, 25.0f);
        ak_v2f E = AK_V2(100.0f, 50.0f);
        
        ASSERT(D != C);
        ASSERT(!(D != 25.0f));
        ASSERT(!(25.0f != D));
        
        ASSERT(D == 25.0f);
        ASSERT(!(D == B));
        ASSERT(25.0f == D);
        
        ASSERT(A > B);
        ASSERT(A > 30.0f);
        ASSERT(!(A > 60.0f));
        
        ASSERT(D < B);
        ASSERT(5.0f < B);
        ASSERT(B < 100.0f);
        
        ASSERT(A >= E);
        ASSERT(!(A > E));
        ASSERT(D >= 25.0f);
        ASSERT(25.0f >= D);
        
        ASSERT(A <= E);
        ASSERT(!(A < E));
        ASSERT(D <= 25.0f);
        ASSERT(25.0f <= D);            
    }
    
    {
        ak_v2f A = AK_V2(-5.0f, -2.0f);
        ak_v2f AbsA = AK_AbsV2(A);
        ASSERT(AbsA.x == 5 && AbsA.y == 2);
        
        ak_v2f B = AK_V2(2.0f, -3.0f);
        ASSERT(AK_Dot(A, B) == -4);
        
        ASSERT(AK_SqrMagnitude(A) == 29);
        ASSERT(AK_Magnitude(AK_V2(3, 4)) == 5);
        
        ak_v2f N = AK_Normalize(AK_V2(5.0f, 0.0f));
        ASSERT(AK_Magnitude(N) == 1 && N.x == 1);
        
        ak_v2f V = AK_Lerp(AK_V2(0.0f, 0.0f), 0.5f, AK_V2(-1.0f, 1.0f));
        ASSERT(V.x == -0.5f && V.y == 0.5f);
    }    
}

void MathV3Tests()
{
    {        
        ak_v3f B = {3, 1, 2};
        B[2] = 5;
        ASSERT(B[2] == 5);
        ASSERT(B.LargestComp() == 2);        
    }
    
    {        
        ak_v3f A = AK_V3<ak_f32>();
        ak_v3f B = AK_V3(2.0f, 1.0f, 3.0f);
        ak_v3f C = AK_V3(AK_V2(1.0f, 2.0f));
        ak_v3f D = AK_V3(AK_V2(5.0f, 1.0f), -1.0f);
        ak_v3f E = AK_V3(10.0f, AK_V2(1.0f, 1.0f));        
        ak_f32 Data[3] = {1.0f, 2.0f, 3.0f};
        ak_v3f F = AK_V3(Data);
        
        ASSERT(A.x == 0 && A.y == 0 && A.z == 0);
        ASSERT(B.x == 2 && B.y == 1 && B.z == 3);
        ASSERT(C.x == 1 && C.y == 2 && C.z == 0);
        ASSERT(D.x == 5 && D.y == 1 && D.z == -1);
        ASSERT(E.x == 10 && E.y == 1 && E.z == 1);
        ASSERT(F.x == 1 && F.y == 2 && F.z == 3);
    }
    
    {
        ak_v3f A = AK_V3(1.0f, 0.0f, 1.0f);
        ak_v3f B = AK_V3(-1.0f, 5.0f, 2.0f);
        
        ak_v3f C = A+B;                
        ak_v3f D = A+3.0f;
        ak_v3f E = -2.0f+B;
        
        ASSERT(C.x == 0 && C.y == 5 && C.z == 3);        
        ASSERT(D.x == 4 && D.y == 3 && D.z == 4);
        ASSERT(E.x == -3 && E.y == 3 && E.z == 0);
        
        C += 1.0f;
        C += A;
        
        ASSERT(C.x == 2 && C.y == 6 && C.z == 5);
    }
    
    {
        ak_v3f A = AK_V3(1.0f, 0.0f, 1.0f);
        ak_v3f B = AK_V3(-1.0f, 5.0f, 2.0f);
        
        ak_v3f C = A-B;                
        ak_v3f D = A-3.0f;
        ak_v3f E = -2.0f-B;
        
        ASSERT(C.x == 2 && C.y == -5 && C.z == -1);        
        ASSERT(D.x == -2 && D.y == -3 && D.z == -2);
        ASSERT(E.x == -1 && E.y == -7 && E.z == -4);
        
        C -= 1.0f;
        C -= A;
        
        ASSERT(C.x == 0 && C.y == -6 && C.z == -3);
    }
    
    {
        ak_v3f A = AK_V3(2.0f, 3.0f, 1.0f);
        ak_v3f B = AK_V3(2.0f, 2.0f, 3.0f);
        
        ak_v3f C = A*B;
        ak_v3f D = -1.0f*A;
        ak_v3f E = B*3.0f;
        
        ASSERT(C.x == 4 && C.y == 6 && C.z == 3);
        ASSERT(D.x == -2 && D.y == -3 && D.z == -1);
        ASSERT(E.x == 6 && E.y == 6 && E.z == 9);
        
        C *= -2.0f;
        C *= A;
        
        ASSERT(C.x == -16 && C.y == -36 && C.z == -6);
    }
    
    {
        ak_v3f A = AK_V3(4.0f, 8.0f, 12.0f);
        ak_v3f B = AK_V3(2.0f, 2.0f, 3.0f);
        
        ak_v3f C = A/B;
        ak_v3f D = A/2.0f;
        ak_v3f E = 6.0f/B;
        
        ASSERT(C.x == 2 && C.y == 4 && C.z == 4);;
        ASSERT(D.x == 2 && D.y == 4 && D.z == 6);
        ASSERT(E.x == 3 && E.y == 3 && E.z == 2);
        
        C /= 0.5f;
        C /= A;
        
        ASSERT(C.x == 1 && C.y == 1 && C.z == 0.6666666666f);
        
        A = -A;
        ASSERT(A.x == -4 && A.y == -8 && A.z == -12);
    }
    
    {
        ak_v3f A = AK_V3(100.0f, 50.0f, 60.0f);
        ak_v3f B = AK_V3(90.0f, 40.0f, 50.0f);
        ak_v3f C = AK_V3(AK_V2(-23.0f, 100.0f));
        ak_v3f D = AK_V3(25.0f, 25.0f, 25.0f);
        ak_v3f E = AK_V3(100.0f, 50.0f, 60.0f);
        
        ASSERT(D != C);
        ASSERT(!(D != 25.0f));
        ASSERT(!(25.0f != D));
        
        ASSERT(D == 25.0f);
        ASSERT(!(D == B));
        ASSERT(25.0f == D);
        
        ASSERT(A > B);
        ASSERT(A > 30.0f);
        ASSERT(!(A > 60.0f));
        
        ASSERT(D < B);
        ASSERT(5.0f < B);
        ASSERT(B < 100.0f);
        
        ASSERT(A >= E);
        ASSERT(!(A > E));
        ASSERT(D >= 25.0f);
        ASSERT(25.0f >= D);
        
        ASSERT(A <= E);
        ASSERT(!(A < E));
        ASSERT(D <= 25.0f);
        ASSERT(25.0f <= D);  
    }
    
    {
        ak_v3f A = AK_AbsV3(AK_V3(-3.0f, -2.0f, -4.0f));
        ASSERT(A.x == 3 && A.y == 2 && A.z == 4);
        
        ak_v3f B = AK_V3(2.0f, 1.0f, 3.0f);
        ASSERT(AK_Dot(A, B) == 20);
        ASSERT(AK_SqrMagnitude(B) == 14);
        
        ak_v3f C = AK_V3(4.0f, 2.0f, 4.0f);
        ASSERT(AK_Magnitude(C) == 6);
        
        ak_v3f D = AK_Normalize(AK_V3(0.0f, 0.0f, -9.0f));
        ASSERT(AK_SqrMagnitude(D) == 1 && D.z == -1);
        
        ak_v3f E = AK_Lerp(AK_V3(-1.0f, -1.0f, 1.0f), 0.25f, AK_V3(1.0f, 1.0f, -1.0f));
        ASSERT(E.x == -0.5f && E.y == -0.5f && E.z == 0.5f);
        
        ak_v3f F = AK_Cross(AK_V3(1.0f, 0.0f, 0.0f), AK_V3(0.0f, 1.0f, 0.0f));
        ASSERT(F.x == 0.0f && F.y == 0.0f && F.z == 1.0f);
        
        ASSERT(AK_Determinant(AK_V3(6.0f, 1.0f, 1.0f), AK_V3(4.0f, -2.0f, 5.0f), AK_V3(2.0f, 8.0f, 7.0f)) == -306);                
    }
}

void MathTests()
{
    {        
        f32 a = 1.1f;
        ASSERT(AK_Ceil(a) == 2);
        
        f32 b = 2.9f;
        ASSERT(AK_Ceil(b) == 3);
        
        ASSERT(AK_Floor(a) == 1);
        ASSERT(AK_Floor(b) == 2);
        
        ASSERT(AK_Sin(AK_PI*0.5f) == 1.0f);
        ASSERT(AK_Cos(AK_PI*0.0f) == 1.0f);
        ASSERT(AK_Tan(AK_ToRadians(45)) == 1.0f);
        
        ASSERT(AK_Lerp(0.0f, 0.5f, 0.5f) == 0.25f);
    }
    
    MathV2Tests();
    MathV3Tests();
}

void MemoryTests()
{
    ak_arena* Arena = AK_CreateArena();
    
    void* MemTest = Arena->Push(AK_Megabyte(4));
    AK_MemorySet(MemTest, 4, AK_Megabyte(4));
    
    ak_temp_arena TempArena = Arena->BeginTemp();
    MemTest = Arena->Push(AK_Megabyte(12));
    ak_temp_arena TempArena2 = Arena->BeginTemp();
    MemTest = Arena->Push(AK_Megabyte(32));
    Arena->EndTemp(&TempArena2);
    MemTest = Arena->Push(AK_Megabyte(4));
    Arena->EndTemp(&TempArena);
    
    ak_u64* Tests = Arena->Push<ak_u64>();
    
    AK_DeleteArena(Arena);    
    
    ak_pool<ak_u64>* Pool = AK_CreatePool<ak_u64>();
    
    ak_u64* Result1 = Pool->Allocate();
    ak_u64* Result2 = Pool->Allocate();
    ak_u64* Result3 = Pool->Allocate();
    
    Pool->Free(Result2);
    
    ak_u64* Result4 = Pool->Allocate();
    ASSERT(Result4 == Result2); 
    
    Pool->Free(Result4);
    Pool->Free(Result3);
    
    ak_u64* Result5 = Pool->Allocate();
    ak_u64* Result6 = Pool->Allocate();
    
    ASSERT(Result5 == Result3);
    ASSERT(Result6 == Result4);        
}

void LoggerTests()
{
    ak_logger Logger = {};
    AK_LogInfo(&Logger, "Hello %s", "World");
    AK_LogWarning(&Logger, "This is a warning");
    AK_LogError(&Logger, "This is an error");    
    AK_OutputToFile(&Logger, "Logger.txt");
}

void ArrayTests()
{
    ak_array<ak_u32> Test = {};
    Test.Add(4);
    
    ak_u32 Capacity = Test.Capacity*2;
    for(u32 Index = 0; Index <= Capacity; Index++)
        Test.Add(Index);    
    
    ASSERT(Test[Test.Size-1] == Capacity);
}