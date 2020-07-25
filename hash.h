#ifndef HASH_H
#define HASH_H

inline u64 Hash(i32 Value, u64 TableSize)
{
    u64 Result = (Value * 2654435761) % TableSize;
    return Result;
}

inline u64 Hash(f32 Value)
{
    union
    {
        f32 Float;
        u32 Int;
    } U;
    
    U.Float = Value;    
    return (u64)U.Int;
}

inline u64 Hash(v2f V)
{
    u64 Result = ((Hash(V.x) ^ (Hash(V.y) << 1)) >> 1);
    return Result;
}

inline u64 Hash(v3f V)
{
    u64 Result = Hash(V.xy) ^ (Hash(V.z) << 1);    
    return Result;
}

inline u64 Hash(vertex_p3_n3 Vertex)
{
    u64 Result = ((Hash(Vertex.P) ^ (Hash(Vertex.N) << 1)) >> 1);
    return Result;
}

inline u64 Hash(vertex_p3_n3_uv Vertex)
{
    u64 Result = ((Hash(Vertex.P) ^ (Hash(Vertex.N) << 1)) >> 1) ^ (Hash(Vertex.UV) << 1);
    return Result;
}

inline u64 Hash(v2f V, u64 TableSize)
{
    u64 Result = Hash(V) % TableSize;
    return Result;
}

inline u64 Hash(v3f V, u64 TableSize)
{
    u64 Result = Hash(V) % TableSize;    
    return Result;
}

inline u64 Hash(vertex_p3_n3 Vertex, u64 TableSize)
{
    u64 Result = Hash(Vertex) % TableSize;    
    return Result;
}

inline u64 Hash(vertex_p3_n3_uv Vertex, u64 TableSize)
{
    u64 Result = Hash(Vertex) % TableSize;    
    return Result;
}

struct uint_pair
{
    u32 Pair01;
    u32 Pair02;
};

inline u64 Hash(uint_pair Pair, u64 TableSize)
{
    u64 Result = BijectiveMap(Pair.Pair01, Pair.Pair02) % TableSize;
    return Result;
}

inline b32 operator!=(uint_pair Left, uint_pair Right)
{
    b32 Result = (Left.Pair01 != Right.Pair01) || (Left.Pair02 != Right.Pair02);
    return Result;
}

struct int_pair
{
    i32 Pair01;
    i32 Pair02;
};

inline u64 Hash(int_pair Pair, u64 TableSize)
{
    u64 Result = BijectiveMap(Pair.Pair01, Pair.Pair02) % TableSize;
    return Result;
}

inline b32 operator!=(int_pair Left, int_pair Right)
{
    b32 Result = (Left.Pair01 != Right.Pair01) || (Left.Pair02 != Right.Pair02);
    return Result;
}

#endif