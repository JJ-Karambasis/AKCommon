#ifndef AK_MESH_GENERATION_H
#define AK_MESH_GENERATION_H

struct ak_mesh_result
{
    ak_u32 VertexCount;
    ak_vertex_p3* Vertices;
    
    ak_u32 IndexCount;
    ak_u16* Indices;
};

ak_mesh_result AK_AllocateMeshResult(ak_arena* Arena, ak_u32 VertexCount, ak_u32 IndexCount);
void           AK_OffsetIndices(ak_u16* Indices, ak_u32 IndexCount, ak_u16 IndexOffset);
void           AK_OffsetIndices(ak_mesh_result* Mesh, ak_u16 IndexOffset);
ak_mesh_result AK_GenerateLineBox(ak_arena* Arena, ak_v3f Dimensions, ak_v3f CenterP=AK_V3<ak_f32>());
ak_mesh_result AK_GenerateTriangleBox(ak_arena* Arena, ak_v3f Dimensions, ak_v3f CenterP=AK_V3<ak_f32>());
ak_mesh_result AK_GenerateLineSphere(ak_arena* Arena, ak_f32 Radius, ak_u16 CircleSampleCount, ak_v3f CenterP=AK_V3<ak_f32>());
ak_mesh_result AK_GenerateTriangleSphere(ak_arena* Arena, ak_f32 Radius, ak_u32 Subdivisions, ak_v3f CenterP=AK_V3<ak_f32>());
ak_mesh_result AK_GenerateLineHemisphere(ak_arena* Arena, ak_f32 Radius, ak_u16 CircleSampleCount, ak_v3f CenterP=AK_V3<ak_f32>());
ak_mesh_result AK_GenerateTriangleCylinder(ak_arena* Arena, ak_f32 Radius, ak_f32 Height, ak_u16 CircleSampleCount, ak_v3f CenterP=AK_V3<ak_f32>());
ak_mesh_result AK_GenerateTriangleCircle(ak_arena* Arena, ak_f32 Radius, ak_f32 Height, ak_u16 CircleSampleCount, ak_v3f CenterP = AK_V3<ak_f32>());
ak_mesh_result AK_GenerateTriangleCone(ak_arena* Arena, ak_f32 Radius, ak_f32 Height, ak_u16 CircleSampleCount, ak_v3f CenterP=AK_V3<ak_f32>());
ak_mesh_result AK_GenerateTriangleTorus(ak_arena* Arena, ak_f32 Radius, ak_f32 InnerRadius, ak_u16 CircleSampleCount, ak_v3f CenterP = AK_V3<ak_f32>());

#endif