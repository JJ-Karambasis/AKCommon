#ifndef MESH_GENERATION_H
#define MESH_GENERATION_H

struct mesh_generation_result
{
    u32 VertexCount;
    vertex_p3* Vertices;
    
    u32 IndexCount;
    u16* Indices;
};

inline f32 GetCircleRadOffset(u16 SampleCount)
{
    f32 Result = (2.0f*PI)/(f32)SampleCount;
    return Result;
}

inline mesh_generation_result 
AllocateMeshGenerationResult(arena* Storage, u32 VertexCount, u32 IndexCount)
{    
    mesh_generation_result MeshGenerationResult = {};
    MeshGenerationResult.VertexCount = VertexCount;
    MeshGenerationResult.IndexCount = IndexCount;
        
    MeshGenerationResult.Vertices = PushArray(Storage, MeshGenerationResult.VertexCount, vertex_p3, Clear, 0);
    MeshGenerationResult.Indices = PushArray(Storage, MeshGenerationResult.IndexCount, u16, Clear, 0);
    
    return MeshGenerationResult;
}

inline void
OffsetIndices(u16* Indices, u16 IndexCount, u16 IndexOffset)
{
    for(u32 Index = 0; Index < IndexCount; Index++)
    {
        Indices[Index] += IndexOffset;
    }
}

inline void 
PopulateBoxVertices(arena* Storage, mesh_generation_result* MeshResult, v3f CenterP, v3f Dim)
{
    v3f HalfDim = Dim*0.5f;    
    
    MeshResult->VertexCount = 8;
    MeshResult->Vertices = PushArray(Storage, MeshResult->VertexCount, vertex_p3, Clear, 0);
    
    MeshResult->Vertices[0] = {V3(-HalfDim.x, -HalfDim.y, Dim.z) + CenterP};
    MeshResult->Vertices[1] = {V3( HalfDim.x, -HalfDim.y, Dim.z) + CenterP};
    MeshResult->Vertices[2] = {V3( HalfDim.x,  HalfDim.y, Dim.z) + CenterP};
    MeshResult->Vertices[3] = {V3(-HalfDim.x,  HalfDim.y, Dim.z) + CenterP};
    MeshResult->Vertices[4] = {V3( HalfDim.x, -HalfDim.y, 0.0f)  + CenterP};
    MeshResult->Vertices[5] = {V3(-HalfDim.x, -HalfDim.y, 0.0f)  + CenterP};
    MeshResult->Vertices[6] = {V3(-HalfDim.x,  HalfDim.y, 0.0f)  + CenterP};
    MeshResult->Vertices[7] = {V3( HalfDim.x,  HalfDim.y, 0.0f)  + CenterP};    
}

inline void 
PopulateCircleIndices(u16** Indices, u16 StartSampleIndex, u16 CircleSampleCount)
{
    u16* IndicesAt = *Indices;    
    u16 TotalSampleCount = StartSampleIndex+CircleSampleCount;
    for(u16 SampleIndex = StartSampleIndex; SampleIndex < TotalSampleCount; SampleIndex++)
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
    *Indices = IndicesAt;
} 

inline mesh_generation_result
GenerateLineBox(arena* Storage, v3f Dim, v3f CenterP = V3())
{    
    mesh_generation_result Result;    
    PopulateBoxVertices(Storage, &Result, CenterP, Dim);
    
    Result.IndexCount = 24;
    Result.Indices = PushArray(Storage, Result.IndexCount, u16, Clear, 0);
    
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

inline mesh_generation_result
GenerateTriangleBox(arena* Storage, v3f Dim, v3f CenterP = V3())
{
    mesh_generation_result Result;
    PopulateBoxVertices(Storage, &Result, CenterP, Dim);
    
    Result.IndexCount = 36;
    Result.Indices = PushArray(Storage, Result.IndexCount, u16, Clear, 0);
    
    Result.Indices[0]  = 0; Result.Indices[1]  = 1; Result.Indices[2]  = 2;
    Result.Indices[3]  = 0; Result.Indices[4]  = 2; Result.Indices[5]  = 3;
    
    Result.Indices[6]  = 1; Result.Indices[7]  = 4; Result.Indices[8]  = 7;
    Result.Indices[9]  = 1; Result.Indices[10] = 7; Result.Indices[11] = 2;
    
    Result.Indices[12] = 4; Result.Indices[13] = 5; Result.Indices[14] = 6;
    Result.Indices[15] = 4; Result.Indices[16] = 6; Result.Indices[17] = 7;
    
    Result.Indices[18] = 5; Result.Indices[19] = 0; Result.Indices[20] = 3;
    Result.Indices[21] = 5; Result.Indices[22] = 3; Result.Indices[23] = 6;
    
    Result.Indices[24] = 3; Result.Indices[25] = 2; Result.Indices[26] = 7;
    Result.Indices[27] = 3; Result.Indices[28] = 7; Result.Indices[29] = 6;
    
    Result.Indices[30] = 5; Result.Indices[31] = 4; Result.Indices[32] = 1;
    Result.Indices[33] = 5; Result.Indices[34] = 1; Result.Indices[35] = 0;
    
    return Result;
}

inline mesh_generation_result
GenerateLineSphere(arena* Storage, f32 Radius, u16 CircleSampleCount, v3f CenterP = V3())
{
    mesh_generation_result Result = AllocateMeshGenerationResult(Storage, CircleSampleCount*3, CircleSampleCount*3*2);
    
    f32 CircleRadOffset = GetCircleRadOffset(CircleSampleCount);    
    vertex_p3* VertexAt = Result.Vertices;
    
    f32 Radians = 0.0f;        
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {V3(Cos(Radians), Sin(Radians), 0.0f)*Radius + CenterP};
    
    Radians = 0.0;
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)                
        *VertexAt++ = {V3(0.0f, Cos(Radians), Sin(Radians))*Radius + CenterP};
    
    Radians = 0.0f;
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {V3(Cos(Radians), 0.0f, Sin(Radians))*Radius + CenterP};            
    
    u16* IndicesAt = Result.Indices;
    PopulateCircleIndices(&IndicesAt, 0, CircleSampleCount);
    PopulateCircleIndices(&IndicesAt, CircleSampleCount, CircleSampleCount);
    PopulateCircleIndices(&IndicesAt, CircleSampleCount*2, CircleSampleCount);
    
    return Result;
}

inline mesh_generation_result
GenerateTriangleCylinder(arena* Storage, f32 Radius, f32 Height, u16 CircleSampleCount, v3f CenterP = V3())
{   
    mesh_generation_result Result = AllocateMeshGenerationResult(Storage, CircleSampleCount*2 + 2, 
                                                                 CircleSampleCount*3*2 + CircleSampleCount*6);    
    f32 CircleRadOffset = GetCircleRadOffset(CircleSampleCount);
    u16 CenterVertexOffset = CircleSampleCount*2;
    
    vertex_p3* VertexAt = Result.Vertices; 
    
    f32 Radians = 0.0f;    
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)    
        *VertexAt++ = {V3(Cos(Radians)*Radius, Sin(Radians)*Radius, 0.0f) + CenterP};            
    
    Radians = 0.0f;
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {V3(Cos(Radians)*Radius, Sin(Radians)*Radius, Height) + CenterP};
    
    *VertexAt++ = {V3(0.0f, 0.0f, 0.0f) + CenterP};
    *VertexAt++ = {V3(0.0f, 0.0f, Height) + CenterP};
    
    u16* IndicesAt = Result.Indices;
    for(u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        u16 SampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        
        *IndicesAt++ = SampleIndex;
        *IndicesAt++ = CenterVertexOffset;
        *IndicesAt++ = SampleIndexPlusOne;
    }    
    
    CenterVertexOffset++;
    
    for(u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        u16 ActualSampleIndex = SampleIndex + CircleSampleCount;
        u16 ActualSampleIndexPlusOne = (ActualSampleIndex+1);
        if(ActualSampleIndexPlusOne == (CircleSampleCount*2))
            ActualSampleIndexPlusOne = CircleSampleCount;
        
        *IndicesAt++ = ActualSampleIndexPlusOne;
        *IndicesAt++ = CenterVertexOffset;
        *IndicesAt++ = ActualSampleIndex; 
    }
    
    for(u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        u16 BottomSampleIndex = SampleIndex;
        u16 TopSampleIndex = SampleIndex + CircleSampleCount;
        u16 BottomSampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        u16 TopSampleIndexPlusOne = TopSampleIndex+1;
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

inline mesh_generation_result
GenerateTriangleCone(arena* Storage, f32 Radius, f32 Height, u16 CircleSampleCount, v3f CenterP = V3())
{
    mesh_generation_result Result = AllocateMeshGenerationResult(Storage, CircleSampleCount+2, CircleSampleCount*3*2);    
    f32 CircleRadOffset = GetCircleRadOffset(CircleSampleCount);
    
    vertex_p3* VertexAt = Result.Vertices;
    
    f32 Radians = 0.0f;
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {V3(Cos(Radians)*Radius, Sin(Radians)*Radius, 0.0f) + CenterP};
    
    *VertexAt++ = {V3(0.0f, 0.0f, 0.0f) + CenterP};
    *VertexAt++ = {V3(0.0f, 0.0f, Height) + CenterP};
    
    u16 CenterVertexOffset = CircleSampleCount;
    
    u16* IndicesAt = Result.Indices;    
    for(u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        u16 SampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        
        *IndicesAt++ = SampleIndex;
        *IndicesAt++ = CenterVertexOffset;
        *IndicesAt++ = SampleIndexPlusOne;
    }
    
    CenterVertexOffset++;
    for(u16 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++)
    {
        u16 SampleIndexPlusOne = (SampleIndex+1) % CircleSampleCount;
        
        *IndicesAt++ = SampleIndex;
        *IndicesAt++ = SampleIndexPlusOne;
        *IndicesAt++ = CenterVertexOffset;        
    }
    
    return Result;
}

#endif