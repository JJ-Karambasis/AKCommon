#ifndef MESH_GENERATION_H
#define MESH_GENERATION_H

struct mesh_generation_result
{
    u32 VertexCount;
    vertex_p3* Vertices;
    
    u32 IndexCount;
    u16* Indices;
};

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
    mesh_generation_result Result;
    Result.VertexCount = CircleSampleCount*3;
    Result.IndexCount = Result.VertexCount*2;
    
    f32 CircleRadOffset = (2.0f*PI)/(f32)CircleSampleCount;
    
    Result.Vertices = PushArray(Storage, Result.VertexCount, vertex_p3, Clear, 0);
    Result.Indices = PushArray(Storage, Result.IndexCount, u16, Clear, 0);
    
    vertex_p3* VertexAt = Result.Vertices;
    
    f32 Radians = 0.0f;        
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {V3(Cos(Radians), Sin(Radians), 0.0f) + CenterP};
    
    Radians = 0.0;
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)                
        *VertexAt++ = {V3(0.0f, Cos(Radians), Sin(Radians)) + CenterP};
    
    Radians = 0.0f;
    for(u32 SampleIndex = 0; SampleIndex < CircleSampleCount; SampleIndex++, Radians += CircleRadOffset)
        *VertexAt++ = {V3(Cos(Radians), 0.0f, Sin(Radians)) + CenterP};            
    
    u16* IndicesAt = Result.Indices;
    PopulateCircleIndices(&IndicesAt, 0, CircleSampleCount);
    PopulateCircleIndices(&IndicesAt, CircleSampleCount, CircleSampleCount);
    PopulateCircleIndices(&IndicesAt, CircleSampleCount*2, CircleSampleCount);
    
    return Result;
}

#endif