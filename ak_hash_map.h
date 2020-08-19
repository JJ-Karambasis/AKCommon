#ifndef HASH_MAP_H
#define HASH_MAP_H

template <typename key, typename value>
struct key_value
{
    b32 Found;
    key Key;
    value Value;
};

template <typename key, typename value>
struct hash_map
{
    u32 TableSize;
    key_value<key, value>* Table;
    b32 (*Compare)(key A, key B);
    
    inline b32 Find(key Key, value* Value = NULL)
    {
        u64 HashIndex = Hash(Key, TableSize);         
        
        while(Table[HashIndex].Found && !Compare(Table[HashIndex].Key, Key))
        {
            HashIndex++;
            ASSERT(HashIndex < TableSize);
        }

        if(Value)
        {
            if(Table[HashIndex].Found)
                *Value = Table[HashIndex].Value;
        }
        
        return Table[HashIndex].Found;        
    }
    
    inline void Insert(key Key, value Value)
    {
        u64 HashIndex = Hash(Key, TableSize);
        while(Table[HashIndex].Found && !Compare(Table[HashIndex].Key, Key))
        {
            HashIndex++;
            ASSERT(HashIndex < TableSize);
        }
                
        Table[HashIndex].Key = Key;
        Table[HashIndex].Value = Value;
        Table[HashIndex].Found = true;
    }
};

template <typename key, typename value>
inline hash_map<key, value> CreateHashMap(u32 TableSize, b32 (*Compare)(key A, key B), arena* Arena = GetDefaultArena())
{
    hash_map<key, value> Result;
    Result.Compare = Compare;
    Result.TableSize = TableSize;
    Result.Table = (key_value<key, value>*)PushSize(Arena, sizeof(key_value<key, value>)*TableSize, Clear, 0);
    
    return Result;
}

#endif