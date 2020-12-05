ak_vertex_p3* AK_Internal__GetBoxVertices(ak_arena* Storage, ak_v3f CenterP, ak_v3f Dim)
{
    ak_v3f HalfDim = Dim*0.5f;            
    ak_vertex_p3* Result = Storage->PushArray<ak_vertex_p3>(8);
    
    Result[0] = {AK_V3(-HalfDim.x, -HalfDim.y, Dim.z) + CenterP};
    Result[1] = {AK_V3( HalfDim.x, -HalfDim.y, Dim.z) + CenterP};
    Result[2] = {AK_V3( HalfDim.x,  HalfDim.y, Dim.z) + CenterP};
    Result[3] = {AK_V3(-HalfDim.x,  HalfDim.y, Dim.z) + CenterP};
    Result[4] = {AK_V3( HalfDim.x, -HalfDim.y, 0.0f)  + CenterP};
    Result[5] = {AK_V3(-HalfDim.x, -HalfDim.y, 0.0f)  + CenterP};
    Result[6] = {AK_V3(-HalfDim.x,  HalfDim.y, 0.0f)  + CenterP};
    Result[7] = {AK_V3( HalfDim.x,  HalfDim.y, 0.0f)  + CenterP};    
    return Result;
}

ak_u16* AK_Internal__PopulateCircleIndices(ak_u16* Indices, ak_u16 StartSampleIndex, ak_u16 CircleSampleCount)
{
    ak_u16* IndicesAt = Indices;    
    ak_u16 TotalSampleCount = StartSampleIndex+CircleSampleCount;
    for(ak_u16 SampleIndex = StartSampleIndex; SampleIndex < TotalSampleCount; SampleIndex++)
    {
        if(SampleIndex == (TotalSampleCount-1))
        {
            *IndicesAt++ = SampleIndex;
            *IndicesAt++ = SampleIndex - (CircleSampleCount-1);
        }
        else
        {
            *IndicesAt++ = SampleIndex;
            *IndicesAt++ = SampleIndex+1;
        }
    }            
    return IndicesAt;    
}

inline ak_f32 AK_Internal__GetCircleRadOffset(ak_u16 SampleCount)
{
    ak_f32 Result = (2.0f*AK_PI)/(ak_f32)SampleCount;
    return Result;
}

inline ak_u16 
AK_Internal__SubdivideEdge(ak_u16 Index0, ak_u16 Index1, ak_v3f P0, ak_v3f P1, ak_mesh_result<ak_vertex_p3>* MeshOut, ak_hash_map<ak_pair<ak_u32>, ak_u16>* DivisionsMap)
{
    ak_pair<ak_u32> Edge = {Index0, Index1};
    
    ak_u16* MapResult = DivisionsMap->Find(Edge);
    if(MapResult)
        return *MapResult;
    
    ak_v3f P = AK_Normalize((P0+P1)*0.5f);
    ak_u16 Result = AK_SafeU16(MeshOut->VertexCount++);
    MeshOut->Vertices[Result] = {P};
    DivisionsMap->Insert(Edge, Result);
    return Result;
}

template <typename type>
ak_mesh_result<type> AK_AllocateMeshResult(ak_arena* Arena, ak_u32 VertexCount, ak_u32 IndexCount)
{
    ak_mesh_result<type> Result = {};
    Result.VertexCount = VertexCount;
    Result.IndexCount = IndexCount;    
    Result.Vertices = Arena->PushArray<type>(Result.VertexCount);
    Result.Indices = Arena->PushArray<ak_u16>(Result.IndexCount);    
    return Result;
}

void AK_OffsetIndices(ak_u16* Indices, ak_u32 IndexCount, ak_u16 IndexOffset)
{
    for(ak_u32 Index = 0; Index < IndexCount; Index++) Indices[Index] += IndexOffset;
}

void AK_OffsetIndices(ak_mesh_result<ak_vertex_p3>* Mesh, ak_u16 IndexOffset)
{
    AK_OffsetIndices(Mesh->Indices, Mesh->IndexCount, IndexOffset);
}

ak_mesh_result<ak_vertex_p3> AK_GenerateLineBox(ak_arena* Arena, ak_v3f Dimensions, ak_v3f CenterP)
{
    ak_mesh_result<ak_vertex_p3> Result;    
    Result.Vertices = AK_Internal__GetBoxVertices(Arena, CenterP, Dimensions);
    Result.VertexCount = 8;
    
    Result.IndexCount = 24;
    Result.Indices = Arena->PushArray<ak_u16>(Result.IndexCount);
    
    Result.Indices[0]  = 0; Result.Indices[1]  = 1;
    Result.Indices[2]  = 1; Result.Indices[3]  = 2;
    Result.Indices[4]  = 2; Result.Indices[5]  = 3;
    Result.Indices[6]  = 3; Result.Indices[7]  = 0;
    
    Result.Indices[8]  = 4; Result.Indices[9]  = 5;
    Result.Indices[10] = 5; Result.Indices[11] = 6;
    Result.Indices[12] = 6; Result.Indices[13] = 7;
    Result.Indices[14] = 7; Result.Indices[15] = 4;
    
    Result.Indices[16] = 0; Result.Indices[17] = 5;
    Result.Indices[18] = 3; Result.Indices[19] = 6;
    Result.Indices[20] = 1; Result.Indices[21] = 4;
    Result.Indices[22] = 2; Result.Indices[23] = 7;
    
    return Result;
}

ak_mesh_result<ak_vertex_p3> AK_GenerateTriangleBox(ak_arena* Arena, ak_v3f Dimensions, ak_v3f CenterP)
{
    ak_mesh_result<ak_vertex_p3> Result;
    Result.Vertices = AK_Internal__GetBoxVertices(Arena, CenterP, Dimensions);
    Result.VertexCount = 8;
    
    Result.IndexCount = 36;
    Result.Indices = Arena->PushArray<ak_u16>(Result.IndexCount);
    //top
    Result.Indices[0]  = 0; Result.Indices[1]  = 1; Result.Indices[2]  = 2;
    Result.Indices[3]  = 0; Result.Indices[4]  = 2; Result.Indices[5]  = 3;
    //right
    Result.Indices[6]  = 1; Result.Indices[7]  = 4; Result.Indices[8]  = 7;
    Result.Indices[9]  = 1; Result.Indices[10] = 7; Result.Indices[11] = 2;
    //Bottom
    Result.Indices[12] = 4; Result.Indices[13] = 5; Result.Indices[14] = 6;
    Result.Indices[15] = 4; Result.Indices[16] = 6; Result.Indices[17] = 7;
    //Left
    Result.Indices[18] = 5; Result.Indices[19] = 0; Result.Indices[20] = 3;
    Result.Indices[21] = 5; Result.Indices[22] = 3; Result.Indices[23] = 6;
    //Back
    Result.Indices[24] = 7; Result.Indices[25] = 6; Result.Indices[26] = 3;
    Result.Indices[27] = 7; Result.Indices[28] = 3; Result.Indices[29] = 2;
    //Front
    Result.Indices[30] = 5; Result.Indices[31] = 4; Result.Indices[32] = 1;
    Result.Indices[33] = 5; Result.Indices[34] = 1; Result.Indices[35] = 0;
    
    return Result;
}

ak_mesh_result<ak_vertex_p3> AK_GenerateLineSphere(ak_arena* Arena, ak_f32 Radius, ak_u16 CircleSampleCount, ak_v3f CenterP)
{
    ak_mesh_result<ak_vertex_p3> Result = AK_AllocateMeshResult<ak_vertex_p3>(Arena, CircleSampleCount*3, CircleSampleCount*3*2);
    ak_f32 CircleRadOffset = AK_Internal__GetCircleRadOffset(CircleSampleCount);
    ak_vertex_p3* VertexAt = Result.Vertices;
    
    ak_f32 Radians = 0.0f;        
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius, 0.0f) + CenterP};
    
    Radians = 0.0;
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)                
        *VertexAt++ = {AK_V3(0.0f, AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius) + CenterP};
    
    Radians = 0.0f;
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, 0.0f, AK_Sin(Radians)*Radius) + CenterP};            
    
    ak_u16* Indices = AK_Internal__PopulateCircleIndices(Result.Indices, 0, CircleSampleCount);
    Indices = AK_Internal__PopulateCircleIndices(Indices, CircleSampleCount, CircleSampleCount);
    Indices = AK_Internal__PopulateCircleIndices(Indices, CircleSampleCount*2, CircleSampleCount);
    
    return Result;
}

ak_mesh_result<ak_vertex_p3> AK_GenerateTriangleSphere(ak_arena* Arena, ak_f32 Radius, ak_u32 Subdivisions, ak_v3f CenterP)
{
    ak_f32 t = (1.0f + AK_Sqrt(5.0f)) * 0.5f;
    ak_vertex_p3 Vertices[] = 
    {
        AK_Normalize(AK_V3(-1.0f,  t,     0.0f)),
        AK_Normalize(AK_V3( 1.0f,  t,     0.0f)),
        AK_Normalize(AK_V3(-1.0f, -t,     0.0f)),
        AK_Normalize(AK_V3( 1.0f, -t,     0.0f)),        
        AK_Normalize(AK_V3( 0.0f, -1.0f,  t)),
        AK_Normalize(AK_V3( 0.0f,  1.0f,  t)),
        AK_Normalize(AK_V3( 0.0f, -1.0f, -t)),
        AK_Normalize(AK_V3( 0.0f,  1.0f, -t)),        
        AK_Normalize(AK_V3( t,     0.0f, -1.0f)),
        AK_Normalize(AK_V3( t,     0.0f,  1.0f)),
        AK_Normalize(AK_V3(-t,     0.0f, -1.0f)),
        AK_Normalize(AK_V3(-t,     0.0f,  1.0f))
    };
    
    ak_u16 Indices[] = 
    {
        0, 11, 5,
        0, 5, 1,
        0, 1, 7, 
        0, 7, 10,
        0, 10, 11,
        1, 5, 9,
        5, 11, 4,
        11, 10, 2,
        10, 7, 6,
        7, 1, 8,
        3, 9, 4,
        3, 4, 2,
        3, 2, 6,
        3, 6, 8,
        3, 8, 9,
        4, 9, 5,
        2, 4, 11,
        6, 2, 10,
        8, 6, 7,
        9, 8, 1
    };
    
    ak_arena* GlobalArena = AK_GetGlobalArena();
    ak_temp_arena TempArena = GlobalArena->BeginTemp();
    
    ak_mesh_result<ak_vertex_p3> MeshIn = AK_AllocateMeshResult<ak_vertex_p3>(GlobalArena, AK_Count(Vertices), AK_Count(Indices));
    AK_MemoryCopy(MeshIn.Vertices, Vertices, sizeof(Vertices));
    AK_MemoryCopy(MeshIn.Indices,  Indices, sizeof(Indices));
    
    ak_hash_map<ak_pair<ak_u32>, ak_u16> DivisionsMap = {};
    
    for(ak_u32 SubdivisionIndex = 0; SubdivisionIndex < Subdivisions; SubdivisionIndex++)
    {           
        AK_Assert((MeshIn.IndexCount % 3) == 0, "Sphere mesh is not a valid triangle mesh. There is a programming error here.");
        ak_u32 TriangleCount = MeshIn.IndexCount/3;
        ak_u32 NewVertexCount = MeshIn.VertexCount+(TriangleCount*3);
        ak_u32 NewIndexCount = (TriangleCount*3)*4;
        
        ak_mesh_result<ak_vertex_p3> MeshOut = AK_AllocateMeshResult<ak_vertex_p3>(GlobalArena, NewVertexCount, NewIndexCount);
        MeshOut.VertexCount = MeshIn.VertexCount;
        MeshOut.IndexCount = 0;
        
        AK_MemoryCopy(MeshOut.Vertices, MeshIn.Vertices, sizeof(ak_vertex_p3)*MeshIn.VertexCount);
        
        DivisionsMap.Reset();
        
        for(ak_u32 TriangleIndex = 0; TriangleIndex < TriangleCount; TriangleIndex++)
        {
            ak_u16 Index0 = MeshIn.Indices[TriangleIndex*3 + 0];
            ak_u16 Index1 = MeshIn.Indices[TriangleIndex*3 + 1];
            ak_u16 Index2 = MeshIn.Indices[TriangleIndex*3 + 2];
            
            ak_v3f P0 = MeshIn.Vertices[Index0].P;
            ak_v3f P1 = MeshIn.Vertices[Index1].P;
            ak_v3f P2 = MeshIn.Vertices[Index2].P;
            
            ak_u16 Index3 = AK_Internal__SubdivideEdge(Index0, Index1, P0, P1, &MeshOut, &DivisionsMap);
            ak_u16 Index4 = AK_Internal__SubdivideEdge(Index1, Index2, P1, P2, &MeshOut, &DivisionsMap);
            ak_u16 Index5 = AK_Internal__SubdivideEdge(Index2, Index0, P2, P0, &MeshOut, &DivisionsMap);
            
            MeshOut.Indices[MeshOut.IndexCount++] = Index0;
            MeshOut.Indices[MeshOut.IndexCount++] = Index3;
            MeshOut.Indices[MeshOut.IndexCount++] = Index5;
            
            MeshOut.Indices[MeshOut.IndexCount++] = Index3;
            MeshOut.Indices[MeshOut.IndexCount++] = Index1;
            MeshOut.Indices[MeshOut.IndexCount++] = Index4;
            
            MeshOut.Indices[MeshOut.IndexCount++] = Index4;
            MeshOut.Indices[MeshOut.IndexCount++] = Index2;
            MeshOut.Indices[MeshOut.IndexCount++] = Index5;
            
            MeshOut.Indices[MeshOut.IndexCount++] = Index3;
            MeshOut.Indices[MeshOut.IndexCount++] = Index4;
            MeshOut.Indices[MeshOut.IndexCount++] = Index5;            
        }    
        
        AK_Assert(MeshOut.VertexCount <= NewVertexCount, "Sphere mesh ran out of vertices. There is a programming error here.");
        AK_Assert(MeshOut.IndexCount == NewIndexCount, "Sphere mesh index counts do not match up during subdivision. There is a programming error here.");
        
        MeshIn = MeshOut;
    }
    
    ak_mesh_result<ak_vertex_p3> Result = AK_AllocateMeshResult<ak_vertex_p3>(Arena, MeshIn.VertexCount, MeshIn.IndexCount);    
    AK_MemoryCopy(Result.Indices, MeshIn.Indices, sizeof(ak_u16)*MeshIn.IndexCount);
    for(ak_u32 VertexIndex = 0; VertexIndex < MeshIn.VertexCount; VertexIndex++)     
        Result.Vertices[VertexIndex].P = (MeshIn.Vertices[VertexIndex].P*Radius) + CenterP;                
    
    GlobalArena->EndTemp(&TempArena);
    
    return Result;
}

ak_mesh_result<ak_vertex_p3> AK_GenerateLineHemisphere(ak_arena* Arena, ak_f32 Radius, ak_u16 CircleSampleCount, ak_v3f CenterP)
{
    ak_u16 HalfCircleSampleCountPlusOne = (CircleSampleCount/2)+1;
    ak_f32 CircleRadOffset = AK_Internal__GetCircleRadOffset(CircleSampleCount);
    
    ak_u32 VertexCount = CircleSampleCount+(HalfCircleSampleCountPlusOne*2);
    ak_mesh_result<ak_vertex_p3> Result = AK_AllocateMeshResult<ak_vertex_p3>(Arena, VertexCount, VertexCount*2);
    
    ak_vertex_p3* VertexAt = Result.Vertices;
    
    ak_f32 Radians = 0.0f;        
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius, 0.0f) + CenterP};
    
    Radians = 0.0;
    for(ak_u32 SampleIndex = 0; SampleIndex < HalfCircleSampleCountPlusOne; SampleIndex++, Radians += CircleRadOffset)                
        *VertexAt++ = {AK_V3(0.0f, AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius) + CenterP};
    
    Radians = 0.0f;
    for(ak_u32 SampleIndex = 0; SampleIndex < HalfCircleSampleCountPlusOne; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, 0.0f, AK_Sin(Radians)*Radius) + CenterP};            
    
    
    ak_u16* Indices = AK_Internal__PopulateCircleIndices(Result.Indices, 0, CircleSampleCount);
    Indices = AK_Internal__PopulateCircleIndices(Indices, CircleSampleCount, HalfCircleSampleCountPlusOne);
    Indices = AK_Internal__PopulateCircleIndices(Indices, CircleSampleCount+HalfCircleSampleCountPlusOne, HalfCircleSampleCountPlusOne);    
    
    return Result;
}

ak_mesh_result<ak_vertex_p3> AK_GenerateTriangleCylinder(ak_arena* Arena, ak_f32 Radius, ak_f32 Height, ak_u16 CircleSampleCount, ak_v3f CenterP)
{
    ak_mesh_result<ak_vertex_p3> Result = AK_AllocateMeshResult<ak_vertex_p3>(Arena, CircleSampleCount*2 + 2, 
                                                                              CircleSampleCount*3*2 + CircleSampleCount*6);    
    ak_f32 CircleRadOffset = AK_Internal__GetCircleRadOffset(CircleSampleCount);
    ak_u16 CenterVertexOffset = CircleSampleCount*2;
    
    ak_vertex_p3* VertexAt = Result.Vertices; 
    
    ak_f32 Radians = 0.0f;    
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)    
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius, 0.0f) + CenterP};            
    
    Radians = 0.0f;
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius, Height) + CenterP};
    
    *VertexAt++ = {AK_V3(0.0f, 0.0f, 0.0f) + CenterP};
    *VertexAt++ = {AK_V3(0.0f, 0.0f, Height) + CenterP};
    
    ak_u16* IndicesAt = Result.Indices;
    for(ak_u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        ak_u16 SampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        
        *IndicesAt++ = SampleIndex;
        *IndicesAt++ = CenterVertexOffset;
        *IndicesAt++ = SampleIndexPlusOne;
    }    
    
    CenterVertexOffset++;
    
    for(ak_u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        ak_u16 ActualSampleIndex = SampleIndex + CircleSampleCount;
        ak_u16 ActualSampleIndexPlusOne = (ActualSampleIndex+1);
        if(ActualSampleIndexPlusOne == (CircleSampleCount*2))
            ActualSampleIndexPlusOne = CircleSampleCount;
        
        *IndicesAt++ = ActualSampleIndexPlusOne;
        *IndicesAt++ = CenterVertexOffset;
        *IndicesAt++ = ActualSampleIndex; 
    }
    
    for(ak_u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        ak_u16 BottomSampleIndex = SampleIndex;
        ak_u16 TopSampleIndex = SampleIndex + CircleSampleCount;
        ak_u16 BottomSampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        ak_u16 TopSampleIndexPlusOne = TopSampleIndex+1;
        if(TopSampleIndexPlusOne == (CircleSampleCount*2))
            TopSampleIndexPlusOne = CircleSampleCount;
        
        *IndicesAt++ = BottomSampleIndex;
        *IndicesAt++ = TopSampleIndexPlusOne;
        *IndicesAt++ = TopSampleIndex;
        
        *IndicesAt++ = BottomSampleIndex;
        *IndicesAt++ = BottomSampleIndexPlusOne;
        *IndicesAt++ = TopSampleIndexPlusOne;
    }
    
    return Result;
}

ak_mesh_result<ak_vertex_p3> AK_GenerateTriangleTorus(ak_arena* Arena, ak_f32 Radius, ak_f32 InnerRadius, ak_u16 CircleSampleCount, ak_v3f CenterP)
{
    ak_mesh_result<ak_vertex_p3> Result = AK_AllocateMeshResult<ak_vertex_p3>(Arena, CircleSampleCount*CircleSampleCount, CircleSampleCount*CircleSampleCount*2*3);    
    ak_f32 CircleRadOffset = AK_Internal__GetCircleRadOffset(CircleSampleCount);    
    
    ak_vertex_p3* VertexAt = Result.Vertices; 
    
    ak_f32 Radians = 0.0f;    
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
    {
        ak_f32 InnerRadians = 0.0f;
        ak_v3f InnerCenter = AK_V3(AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius, 0.0f) + CenterP;
        for(ak_u32 InnerSample = 0; InnerSample < CircleSampleCount; InnerSample++, InnerRadians += CircleRadOffset)
        {
            ak_v3f W = AK_Normalize(InnerCenter - CenterP);
            *VertexAt++ = {CenterP + InnerCenter + (InnerRadius*AK_Cos(InnerRadians)*InnerCenter) + AK_V3f(0.0f, 0.0f, InnerRadius*AK_Sin(InnerRadians))};
        }         
    }
    
    ak_u16* IndicesAt = Result.Indices;
    ak_i32 VertexMax = CircleSampleCount*CircleSampleCount;
    for(ak_u16 SampleIndex = 0; SampleIndex < VertexMax; SampleIndex++)
    {
        ak_u16 SampleIndexPlusOne = (SampleIndex+1) % VertexMax;
        
        *IndicesAt++ = SampleIndex;
        *IndicesAt++ = SampleIndexPlusOne;
        *IndicesAt++ = (SampleIndex + CircleSampleCount) % VertexMax;
        if(SampleIndex != 0)
        {
            *IndicesAt++ = SampleIndex;
            *IndicesAt++ = (SampleIndex + CircleSampleCount) % VertexMax;
            *IndicesAt++ = (SampleIndex + CircleSampleCount - 1) % VertexMax;
        }                
    }        
    
    return Result;
}

inline ak_mesh_result<ak_vertex_p3>
AK_GenerateTriangleCircle(ak_arena* Arena, ak_f32 Radius, ak_f32 Height, ak_u16 CircleSampleCount, ak_v3f CenterP)
{   
    ak_mesh_result<ak_vertex_p3> Result = AK_AllocateMeshResult<ak_vertex_p3>(Arena, CircleSampleCount*2, CircleSampleCount*3*2);    
    ak_f32 CircleRadOffset = AK_Internal__GetCircleRadOffset(CircleSampleCount);    
    
    ak_vertex_p3* VertexAt = Result.Vertices; 
    
    ak_f32 Radians = 0.0f;    
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)    
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius, 0.0f) + CenterP};            
    
    Radians = 0.0f;
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius, Height) + CenterP};
    
    ak_u16* IndicesAt = Result.Indices;
    for(ak_u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        ak_u16 SampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        
        *IndicesAt++ = SampleIndex;
        *IndicesAt++ = SampleIndexPlusOne;
        *IndicesAt++ = SampleIndex + CircleSampleCount;
        if(SampleIndex != 0)
        {
            *IndicesAt++ = SampleIndex;
            *IndicesAt++ = SampleIndex + CircleSampleCount;
            *IndicesAt++ = SampleIndex + CircleSampleCount - 1;
        }                
    }        
    
    return Result;
}

ak_mesh_result<ak_vertex_p3> AK_GenerateTriangleCone(ak_arena* Arena, ak_f32 Radius, ak_f32 Height, ak_u16 CircleSampleCount, ak_v3f CenterP)
{
    ak_mesh_result<ak_vertex_p3> Result = AK_AllocateMeshResult<ak_vertex_p3>(Arena, CircleSampleCount+2, CircleSampleCount*3*2);    
    ak_f32 CircleRadOffset = AK_Internal__GetCircleRadOffset(CircleSampleCount);
    
    ak_vertex_p3* VertexAt = Result.Vertices;
    
    ak_f32 Radians = 0.0f;
    for(ak_u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {AK_V3(AK_Cos(Radians)*Radius, AK_Sin(Radians)*Radius, 0.0f) + CenterP};
    
    *VertexAt++ = {AK_V3(0.0f, 0.0f, 0.0f) + CenterP};
    *VertexAt++ = {AK_V3(0.0f, 0.0f, Height) + CenterP};
    
    ak_u16 CenterVertexOffset = CircleSampleCount;
    
    ak_u16* IndicesAt = Result.Indices;    
    for(ak_u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        ak_u16 SampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        
        *IndicesAt++ = SampleIndex;
        *IndicesAt++ = CenterVertexOffset;
        *IndicesAt++ = SampleIndexPlusOne;
    }
    
    CenterVertexOffset++;
    for(ak_u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        ak_u16 SampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        
        *IndicesAt++ = SampleIndex;
        *IndicesAt++ = SampleIndexPlusOne;
        *IndicesAt++ = CenterVertexOffset;        
    }
    
    return Result;
}

ak_mesh_result<ak_vertex_p3> AK_GenerateTriangleQuad(ak_arena* Arena, ak_v3f CenterP, ak_v2f Dimensions)
{
    ak_mesh_result<ak_vertex_p3> Result = AK_AllocateMeshResult<ak_vertex_p3>(Arena, 4, 6);
    ak_v2f HalfDimensions = Dimensions*0.5f;
    
    Result.Vertices[0].P = AK_V3(CenterP.xy - HalfDimensions, CenterP.z);
    Result.Vertices[1].P = AK_V3(CenterP.x + HalfDimensions.x, CenterP.y - HalfDimensions.y, CenterP.z);
    Result.Vertices[2].P = AK_V3(CenterP.xy + HalfDimensions, CenterP.z);
    Result.Vertices[3].P = AK_V3(CenterP.x - HalfDimensions.x, CenterP.y + HalfDimensions.y, CenterP.z);
    
    Result.Indices[0] = 0;
    Result.Indices[1] = 1;
    Result.Indices[2] = 2;
    Result.Indices[3] = 2;
    Result.Indices[4] = 3;
    Result.Indices[5] = 0;
    
    return Result;
}

ak_mesh_result<ak_vertex_p3_n3> AK_GenerateTriangleBoxN(ak_arena* Arena, ak_v3f Dimensions, ak_v3f CenterP)
{
    ak_mesh_result<ak_vertex_p3_n3> Result = AK_AllocateMeshResult<ak_vertex_p3_n3>(Arena, 24, 36);
    
    ak_v3f HalfDim = Dimensions*0.5f;
    
    Result.Vertices[0]  = {AK_V3(-HalfDim.x, -HalfDim.y, Dimensions.z) + CenterP, AK_ZAxis()};
    Result.Vertices[1]  = {AK_V3( HalfDim.x, -HalfDim.y, Dimensions.z) + CenterP, AK_ZAxis()};
    Result.Vertices[2]  = {AK_V3( HalfDim.x,  HalfDim.y, Dimensions.z) + CenterP, AK_ZAxis()};
    Result.Vertices[3]  = {AK_V3(-HalfDim.x,  HalfDim.y, Dimensions.z) + CenterP, AK_ZAxis()};
    
    Result.Vertices[4]  = {AK_V3( HalfDim.x, -HalfDim.y, Dimensions.z) + CenterP, AK_XAxis()};
    Result.Vertices[5]  = {AK_V3( HalfDim.x, -HalfDim.y, 0.0f) + CenterP, AK_XAxis()};
    Result.Vertices[6]  = {AK_V3( HalfDim.x,  HalfDim.y, 0.0f) + CenterP, AK_XAxis()};
    Result.Vertices[7]  = {AK_V3( HalfDim.x,  HalfDim.y, Dimensions.z) + CenterP, AK_XAxis()};
    
    Result.Vertices[8]  = {AK_V3( HalfDim.x, -HalfDim.y, 0.0f) + CenterP, -AK_ZAxis()};
    Result.Vertices[9]  = {AK_V3(-HalfDim.x, -HalfDim.y, 0.0f) + CenterP, -AK_ZAxis()};
    Result.Vertices[10] = {AK_V3(-HalfDim.x,  HalfDim.y, 0.0f) + CenterP, -AK_ZAxis()};
    Result.Vertices[11] = {AK_V3( HalfDim.x,  HalfDim.y, 0.0f) + CenterP, -AK_ZAxis()};
    
    Result.Vertices[12] = {AK_V3(-HalfDim.x, -HalfDim.y, 0.0f) + CenterP, -AK_XAxis()};
    Result.Vertices[13] = {AK_V3(-HalfDim.x, -HalfDim.y, Dimensions.z) + CenterP, -AK_XAxis()};
    Result.Vertices[14] = {AK_V3(-HalfDim.x,  HalfDim.y, Dimensions.z) + CenterP, -AK_XAxis()};
    Result.Vertices[15] = {AK_V3(-HalfDim.x,  HalfDim.y, 0.0f) + CenterP, -AK_XAxis()};
    
    Result.Vertices[16] = {AK_V3(-HalfDim.x, -HalfDim.y, 0.0f) + CenterP, -AK_YAxis()};
    Result.Vertices[17] = {AK_V3( HalfDim.x, -HalfDim.y, 0.0f) + CenterP, -AK_YAxis()};
    Result.Vertices[18] = {AK_V3( HalfDim.x, -HalfDim.y, Dimensions.z) + CenterP, -AK_YAxis()};
    Result.Vertices[19] = {AK_V3(-HalfDim.x, -HalfDim.y, Dimensions.z) + CenterP, -AK_YAxis()};
    
    Result.Vertices[20] = {AK_V3(-HalfDim.x,  HalfDim.y, Dimensions.z) + CenterP, AK_YAxis()};
    Result.Vertices[21] = {AK_V3( HalfDim.x,  HalfDim.y, Dimensions.z) + CenterP, AK_YAxis()};
    Result.Vertices[22] = {AK_V3( HalfDim.x,  HalfDim.y, 0.0f) + CenterP, AK_YAxis()};
    Result.Vertices[23] = {AK_V3(-HalfDim.x,  HalfDim.y, 0.0f) + CenterP, AK_YAxis()};
    
    Result.Indices[0]  = 0;  Result.Indices[1]  = 1;  Result.Indices[2]  = 2;
    Result.Indices[3]  = 2;  Result.Indices[4]  = 3;  Result.Indices[5]  = 0;    
        
    Result.Indices[6]  = 4;  Result.Indices[7]  = 5;  Result.Indices[8]  = 6;
    Result.Indices[9]  = 6;  Result.Indices[10] = 7;  Result.Indices[11] = 4;
        
    Result.Indices[12] = 8;  Result.Indices[13] = 9;  Result.Indices[14] = 10;
    Result.Indices[15] = 10; Result.Indices[16] = 11; Result.Indices[17] = 8;
        
    Result.Indices[18] = 12; Result.Indices[19] = 13; Result.Indices[20] = 14;
    Result.Indices[21] = 14; Result.Indices[22] = 15; Result.Indices[23] = 12;
    
    
    Result.Indices[24] = 16; Result.Indices[25] = 17; Result.Indices[26] = 18;
    Result.Indices[27] = 18; Result.Indices[28] = 19; Result.Indices[29] = 16;    
    
    Result.Indices[30] = 20; Result.Indices[31] = 21; Result.Indices[32] = 22;
    Result.Indices[33] = 22; Result.Indices[34] = 23; Result.Indices[35] = 20;
    
    return Result;
}