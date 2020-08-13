#ifndef HASH_TABLE_H
#define HASH_TABLE_H

template <typename type>
struct hash_entry
{
    b32 Found;
    type Key;
};

template <typename type>
struct hash_table
{
    u32 TableSize;
    hash_entry<type>* Table;
    
    inline u64 GetHashIndex(type Key)
    {
        u64 HashIndex = Hash(Key, TableSize);
        
        //TODO(JJ): This is so bad :(
        b32 Reverse = false;
        while(Table[HashIndex].Found && (Table[HashIndex].Key != Key))
        {
            if((HashIndex+1) == TableSize)
                Reverse = true;
            
            if(Reverse)
            {
                HashIndex--;
                ASSERT(HashIndex > 0);
            }
            else
            {                
                HashIndex++;                                            
            }
        }
        return HashIndex;
    }
    
    inline b32 operator[](type Key)
    {
        u64 HashIndex = GetHashIndex(Key);
        
        b32 Result = Table[HashIndex].Found;
        if(!Result)
        {
            Table[HashIndex].Key = Key;
            Table[HashIndex].Found = true;
        }
        
        return Result;
    }
};

template <typename type>
inline hash_table<type> CreateHashTable(u32 TableSize)
{
    hash_table<type> Result;
    Result.TableSize = TableSize;
    Result.Table = PushArray(TableSize, hash_entry<type>, Clear, 0);
    return Result;
}

#endif