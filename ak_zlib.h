#ifndef AK_ZLIB
#define AK_ZLIB

global u8 Global_FixedLitLenCodeLen[288] = 
{
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8
};

global u8 Global_FixedDistCodeLen[32] = 
{
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

global u8 Global_CodeLenCodeLenOrder[19] = 
{
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
};

global u16 Global_ZLibBaseLength[31] = 
{
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 
    51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0
};

global u16 Global_ZLibLengthExtraBits[31] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 
    4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0
};

global u16 Global_ZLibBaseDist[32] = 
{
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 
    385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577,
    0, 0
};

global u16 Global_ZLibDistExtraBits[32] = 
{
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13
};

global const char* __Global__Zlib_Internal_ErrorMessage;

inline 
b32 ZLib_Error(const char* ErrorMessage)
{    
    __Global__Zlib_Internal_ErrorMessage = ErrorMessage;
    return false;
}

inline const char* 
ZLib_GetErrorMessage()
{
    return __Global__Zlib_Internal_ErrorMessage;
}

enum zlib_compression_type
{
    ZLIB_COMPRESSION_NONE,
    ZLIB_COMPRESSION_FIXED,
    ZLIB_COMPRESSION_DYNAMIC    
};

struct zlib_stream
{    
    u8* Stream;
    ptr At;
    ptr Size;
    
    u32 NumBits;
    u32 CodeBuffer; 
    
    u8* OutputStream;
    ptr OutputAt;
    
    b32 IsValid()
    {
        b32 Result = At < Size;
        return Result;
    }
    inline u8 GetU8()
    {
        if(!IsValid()) return 0;
        u8 Result = Stream[At++];
        return Result;
    }
    
    inline u16 GetU16()
    {
        u8 A = GetU8();
        u8 B = GetU8();
        
        u16 Result = (B << 8) | A;
        return Result;
    }
    
    inline void FillBits()
    {
        do
        {
            ASSERT(CodeBuffer < (1U << NumBits));
            CodeBuffer |= (u32)GetU8() << NumBits;
            NumBits += 8;            
        } while(NumBits <= 24);
    }
    
    inline u32 GetBits(u32 Bits)
    {        
        if(NumBits < Bits) FillBits();
        u32 Result = CodeBuffer & ((1 << Bits) - 1);
        CodeBuffer >>= Bits;
        NumBits -= Bits;
        return Result;
    }        
};

i32 Reverse16Bits(i32 CodeBuffer)
{
    CodeBuffer = ((CodeBuffer & 0xAAAA) >>  1) | ((CodeBuffer & 0x5555) << 1);
    CodeBuffer = ((CodeBuffer & 0xCCCC) >>  2) | ((CodeBuffer & 0x3333) << 2);
    CodeBuffer = ((CodeBuffer & 0xF0F0) >>  4) | ((CodeBuffer & 0x0F0F) << 4);
    CodeBuffer = ((CodeBuffer & 0xFF00) >>  8) | ((CodeBuffer & 0x00FF) << 8);
    return CodeBuffer;
}

inline i32 ReverseBits(i32 CodeBuffer, i32 Bits)
{
    ASSERT(Bits <= 16);
    return Reverse16Bits(CodeBuffer) >> (16-Bits);
}

struct zlib_huffman
{
    u16 FirstCode[16];
    u16 FirstSymbol[16];
    i32 MaxCode[16];
    u16 Symbols[288];
};

inline zlib_huffman 
ZLib_BuildHuffman(u8* CodeLengths, u32 CodeLengthCount)
{
    zlib_huffman Result = {};
    
    i32 CountOfCodeLengths[17] = {};
    for(u32 CodeLengthIndex = 0; CodeLengthIndex < CodeLengthCount; CodeLengthIndex++)
    {
        CountOfCodeLengths[CodeLengths[CodeLengthIndex]]++;
    }
    
    CountOfCodeLengths[0] = 0;
    
    i32 NextCode[16];
    i32 Code = 0;
    i32 FirstSymbol = 0;
    for(u32 CodeLengthIndex = 1; CodeLengthIndex < 16; CodeLengthIndex++)
    {
        NextCode[CodeLengthIndex] = Code;
        Result.FirstCode[CodeLengthIndex] = (u16)Code;
        Result.FirstSymbol[CodeLengthIndex] = (u16)FirstSymbol;
        
        Code += CountOfCodeLengths[CodeLengthIndex];
        
        Result.MaxCode[CodeLengthIndex] = Code << (16-CodeLengthIndex);
        Code <<= 1;        
        FirstSymbol += CountOfCodeLengths[CodeLengthIndex];
    }
    
    for(u32 CodeLengthIndex = 0; CodeLengthIndex < CodeLengthCount; CodeLengthIndex++)
    {
        i32 CodeLength = CodeLengths[CodeLengthIndex];
        if(CodeLength)
        {
            i32 C = NextCode[CodeLength] - Result.FirstCode[CodeLength] + Result.FirstSymbol[CodeLength];
            Result.Symbols[C] = (u16)CodeLengthIndex;
            NextCode[CodeLength]++;
        }
    }
    
    return Result;
}

i32 ZLib_DecodeHuffman(zlib_huffman* Huffman, zlib_stream* Stream)
{
    if(Stream->NumBits < 16) Stream->FillBits();
    
    i32 CodeBuffer = ReverseBits(Stream->CodeBuffer, 16);
    
    u32 BitCount;
    for(BitCount = 0; ; BitCount++)
    {
        if(CodeBuffer < Huffman->MaxCode[BitCount])
            break;
    }
    
    if(BitCount >= 16) return -1;    
    
    i32 Code = (CodeBuffer >> (16-BitCount)) - Huffman->FirstCode[BitCount] + Huffman->FirstSymbol[BitCount];
    Stream->CodeBuffer >>= BitCount;
    Stream->NumBits -= BitCount;    
    u16 Result = Huffman->Symbols[Code];
    return Result;
}

inline b32 
ZLib_Inflate(zlib_stream* Stream)
{    
    u8 BFINAL;
    u8 BTYPE;
    
    do
    {
        BFINAL = (u8)Stream->GetBits(1);
        BTYPE = (u8)Stream->GetBits(2);
        
        switch(BTYPE)
        {
            case ZLIB_COMPRESSION_NONE:
            {
                if(Stream->NumBits & 0x7)
                    Stream->GetBits(Stream->NumBits & 0x07);
                
                //Drain remaining bits
                u8 Bytes[4];           
                u32 ByteIndex = 0;
                while(Stream->NumBits > 0)
                {
                    Bytes[ByteIndex++] = (u8)(Stream->CodeBuffer & 0xFF);
                    Stream->CodeBuffer >>= 8;
                    Stream->NumBits -= 8;
                }                
                ASSERT(Stream->NumBits == 0);
                
                while(ByteIndex < 4)
                    Bytes[ByteIndex++] = Stream->GetU8();
                
                u16 Len  = (Bytes[1] << 8) | Bytes[0];
                u16 NLen = (Bytes[3] << 8) | Bytes[2];
                
                if(NLen != (Len ^ 0xFFFF)) return ZLib_Error("ZLib data uncompressed is corrupted. Len and NLen are undefined.");                
                if(!Stream->IsValid()) return ZLib_Error("ZLib data uncompressed is corrupted. Read past the ZLib buffer.");
                
                CopyMemory(Stream->OutputStream+Stream->OutputAt, Stream->Stream+Stream->At, Len);
                Stream->OutputAt += Len;
                Stream->At += Len;
                
            } break;
            
            case ZLIB_COMPRESSION_FIXED:
            case ZLIB_COMPRESSION_DYNAMIC:
            {          
                zlib_huffman LitLenHuffman;
                zlib_huffman DistHuffman;
                
                if(BTYPE == ZLIB_COMPRESSION_FIXED)
                {      
                    LitLenHuffman = ZLib_BuildHuffman(Global_FixedLitLenCodeLen, ARRAYCOUNT(Global_FixedLitLenCodeLen));
                    DistHuffman = ZLib_BuildHuffman(Global_FixedDistCodeLen, ARRAYCOUNT(Global_FixedDistCodeLen));
                }
                else
                {
                    u8 HuffmanCodeLenCodeLen[19] = {};
                    
                    u32 HLIT = Stream->GetBits(5) + 257;
                    u32 HDIST = Stream->GetBits(5) + 1;
                    u32 HCLEN = Stream->GetBits(4) + 4;
                    
                    for(u32 CodeLenIndex = 0; CodeLenIndex < HCLEN; CodeLenIndex++)                    
                        HuffmanCodeLenCodeLen[Global_CodeLenCodeLenOrder[CodeLenIndex]] = (u8)Stream->GetBits(3);
                    
                    zlib_huffman CodeLenHuffman = ZLib_BuildHuffman(HuffmanCodeLenCodeLen, ARRAYCOUNT(HuffmanCodeLenCodeLen));
                    
                    u8 LitLenDistCodeLen[286+33] = {};
                    
                    u32 Counter = 0;
                    while(Counter < (HLIT+HDIST))
                    {
                        i32 DecodedValue = ZLib_DecodeHuffman(&CodeLenHuffman, Stream);
                        if(DecodedValue == -1)
                            return ZLib_Error("Error decoding code len huffman");
                        
                        if(DecodedValue < 16)
                        {
                            LitLenDistCodeLen[Counter++] = (u8)DecodedValue;
                        }
                        else
                        {
                            u8 CopyValue = 0;
                            u32 RepeatValue = 0;
                            if(DecodedValue == 16)
                            {
                                CopyValue = LitLenDistCodeLen[Counter-1];
                                RepeatValue = Stream->GetBits(2)+3;                                                                                                
                            }
                            else if(DecodedValue == 17)
                            {
                                RepeatValue = Stream->GetBits(3)+3;  
                            }
                            else if(DecodedValue == 18)
                            {
                                RepeatValue = Stream->GetBits(7)+11;
                            }
                            else                            
                                return ZLib_Error("ZLib data compressed is corrupted. The dynamic values are invalid.");                                                            
                            
                            while(RepeatValue--)
                                LitLenDistCodeLen[Counter++] = CopyValue;
                        }
                    }
                    
                    LitLenHuffman = ZLib_BuildHuffman(LitLenDistCodeLen, HLIT);
                    DistHuffman = ZLib_BuildHuffman(LitLenDistCodeLen+HLIT, HDIST);
                }
                
                for(;;)
                {
                    i32 DecodedValue = ZLib_DecodeHuffman(&LitLenHuffman, Stream);
                    if(DecodedValue == -1)
                        ZLib_Error("Error decoded lit len huffman");
                    
                    if(DecodedValue < 256)
                    {
                        Stream->OutputStream[Stream->OutputAt++] = (u8)DecodedValue;                        
                    }
                    else if(DecodedValue == 256)
                    {
                        break;
                    }
                    else
                    {
                        DecodedValue -= 257;
                        u32 Length = Global_ZLibBaseLength[DecodedValue];
                        if(Global_ZLibLengthExtraBits[DecodedValue])
                            Length += Stream->GetBits(Global_ZLibLengthExtraBits[DecodedValue]);
                        
                        DecodedValue = ZLib_DecodeHuffman(&DistHuffman, Stream);
                        u32 Distance = Global_ZLibBaseDist[DecodedValue];
                        if(Global_ZLibDistExtraBits[DecodedValue])
                            Distance += Stream->GetBits(Global_ZLibDistExtraBits[DecodedValue]);
                        
                        if(Distance > Stream->OutputAt)
                            return ZLib_Error("ZLib data compressed is corrupted. The distance to read is larger than our current ZLib buffer.");
                        
                        u8* P = Stream->OutputStream + (Stream->OutputAt - Distance);
                        
                        while(Length--)                        
                            Stream->OutputStream[Stream->OutputAt++] = *P++;                        
                    }
                        
                        
                }
            } break;
                        
            default:
            {
                ZLib_Error("ZLib data is corrupted. Could not find a valid compression type.");
            } break;
        }
                                
    } while(!BFINAL);
    
    return true;
}

inline b32 
ZLib_Decompress(void* DecompressedData, void* CompressedData, ptr CompressedDataLength)
{
    zlib_stream Stream = {};
    Stream.Stream = (u8*)CompressedData;
    Stream.Size = CompressedDataLength;
    Stream.OutputStream = (u8*)DecompressedData;
    
    u32 CM = (u8)Stream.GetBits(4);
    u32 CINFO = (u8)Stream.GetBits(4);
    
    if(CM != 8) return ZLib_Error("ZLib compression method is not supported. Only supported method is deflate.");    
    if(CINFO > 7) return ZLib_Error("ZLib compression info not supported.");
    
    u8 CMF = ((CINFO << 4) & 0xF0) | (CM & 0x0F);
    u8 FLAG = (u8)Stream.GetBits(8);
    
    u8 FCHECK = (FLAG & 0x1F);
    u8 FDICT  = (FLAG & 0x20);
    u8 FLEVEL = (FLAG & 0xC0);
    
    if((CMF*256 + FLAG) % 31 != 0) return ZLib_Error("ZLib header is corrupted.");    
    if(FDICT) return ZLib_Error("ZLib preset dictionary is not supported.");
    
    b32 Result = ZLib_Inflate(&Stream);        
    return Result;
}

#endif