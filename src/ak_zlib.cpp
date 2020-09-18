global ak_string AK_Internal__ZLibErrorMessage;

void AK_Internal__ZLibSetErrorMessage(ak_char* Format, ...)
{    
    ak_arena* Arena = AK_GetGlobalArena();    
    
    va_list List;
    va_start(List, Format);
    AK_Internal__ZLibErrorMessage = AK_FormatString(Arena, Format, List);
    va_end(List);            
}


ak_string AK_ZLib_GetErrorMessage()
{
    return AK_Internal__ZLibErrorMessage;
}

ak_bool AK_Internal__ZLibError(ak_char* Message)
{
    AK_Internal__ZLibSetErrorMessage(Message);
    return false;
}

global ak_u8 AK_Internal__FixedLitLenCodeLen[288] = 
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

global ak_u8 AK_Internal__FixedDistCodeLen[32] = 
{
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

global ak_u8 AK_Internal__CodeLenCodeLenOrder[19] = 
{
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
};

global ak_u16 AK_Internal__ZLibBaseLength[31] = 
{
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 
    51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0
};

global ak_u16 AK_Internal__ZLibLengthExtraBits[31] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 
    4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0
};

global ak_u16 AK_Internal__ZLibBaseDist[32] = 
{
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 
    385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577,
    0, 0
};

global ak_u16 AK_Internal__ZLibDistExtraBits[32] = 
{
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13
};

enum ak_zlib_compression_type
{
    AK_ZLIB_COMPRESSION_NONE,
    AK_ZLIB_COMPRESSION_FIXED,
    AK_ZLIB_COMPRESSION_DYNAMIC    
};

struct ak_internal__zlib_stream
{    
    ak_u8* Stream;
    ak_uaddr At;
    ak_uaddr Size;
    
    ak_u32 NumBits;
    ak_u32 CodeBuffer; 
    
    ak_u8* OutputStream;
    ak_uaddr OutputAt;
    
    ak_bool IsValid()
    {
        ak_bool Result = At < Size;
        return Result;
    }
    
    ak_u8 GetU8()
    {
        if(!IsValid()) return 0;
        ak_u8 Result = Stream[At++];
        return Result;
    }
    
    ak_u16 GetU16()
    {
        ak_u8 A = GetU8();
        ak_u8 B = GetU8();
        
        ak_u16 Result = (B << 8) | A;
        return Result;
    }
    
    inline void FillBits()
    {
        do
        {
            AK_Assert(CodeBuffer < (1U << NumBits), "Code buffer overflow");
            CodeBuffer |= (ak_u32)GetU8() << NumBits;
            NumBits += 8;            
        } while(NumBits <= 24);
    }
    
    inline ak_u32 GetBits(ak_u32 Bits)
    {        
        if(NumBits < Bits) FillBits();
        ak_u32 Result = CodeBuffer & ((1 << Bits) - 1);
        CodeBuffer >>= Bits;
        NumBits -= Bits;
        return Result;
    }        
};

struct ak_internal__zlib_huffman
{
    ak_u16 FirstCode[16];
    ak_u16 FirstSymbol[16];
    ak_i32 MaxCode[16];
    ak_u16 Symbols[288];
};

ak_i32 AK_Internal__ZLibReverse16Bits(ak_i32 CodeBuffer)
{
    CodeBuffer = ((CodeBuffer & 0xAAAA) >>  1) | ((CodeBuffer & 0x5555) << 1);
    CodeBuffer = ((CodeBuffer & 0xCCCC) >>  2) | ((CodeBuffer & 0x3333) << 2);
    CodeBuffer = ((CodeBuffer & 0xF0F0) >>  4) | ((CodeBuffer & 0x0F0F) << 4);
    CodeBuffer = ((CodeBuffer & 0xFF00) >>  8) | ((CodeBuffer & 0x00FF) << 8);
    return CodeBuffer;
}

ak_i32 AK_Internal__ZLibReverseBits(ak_i32 CodeBuffer, ak_i32 Bits)
{
    AK_Assert(Bits <= 16, "Bit count not supported");
    return AK_Internal__ZLibReverse16Bits(CodeBuffer) >> (16-Bits);
}

ak_internal__zlib_huffman 
AK_Internal__ZLibBuildHuffman(ak_u8* CodeLengths, ak_u32 CodeLengthCount)
{
    ak_internal__zlib_huffman Result = {};
    
    ak_i32 CountOfCodeLengths[17] = {};
    for(ak_u32 CodeLengthIndex = 0; CodeLengthIndex < CodeLengthCount; CodeLengthIndex++)
    {
        CountOfCodeLengths[CodeLengths[CodeLengthIndex]]++;
    }
    
    CountOfCodeLengths[0] = 0;
    
    ak_i32 NextCode[16];
    ak_i32 Code = 0;
    ak_i32 FirstSymbol = 0;
    for(ak_u32 CodeLengthIndex = 1; CodeLengthIndex < 16; CodeLengthIndex++)
    {
        NextCode[CodeLengthIndex] = Code;
        Result.FirstCode[CodeLengthIndex] = (ak_u16)Code;
        Result.FirstSymbol[CodeLengthIndex] = (ak_u16)FirstSymbol;
        
        Code += CountOfCodeLengths[CodeLengthIndex];
        
        Result.MaxCode[CodeLengthIndex] = Code << (16-CodeLengthIndex);
        Code <<= 1;        
        FirstSymbol += CountOfCodeLengths[CodeLengthIndex];
    }
    
    for(ak_u32 CodeLengthIndex = 0; CodeLengthIndex < CodeLengthCount; CodeLengthIndex++)
    {
        ak_i32 CodeLength = CodeLengths[CodeLengthIndex];
        if(CodeLength)
        {
            ak_i32 C = NextCode[CodeLength] - Result.FirstCode[CodeLength] + Result.FirstSymbol[CodeLength];
            Result.Symbols[C] = (ak_u16)CodeLengthIndex;
            NextCode[CodeLength]++;
        }
    }
    
    return Result;
}

ak_i32 AK_Internal__ZLibDecodeHuffman(ak_internal__zlib_huffman* Huffman, ak_internal__zlib_stream* Stream)
{
    if(Stream->NumBits < 16) Stream->FillBits();    
    ak_i32 CodeBuffer = AK_Internal__ZLibReverseBits(Stream->CodeBuffer, 16);
    
    ak_u32 BitCount;
    for(BitCount = 0; ; BitCount++)
    {
        if(CodeBuffer < Huffman->MaxCode[BitCount])
            break;
    }
    
    if(BitCount >= 16) return -1;    
    
    ak_i32 Code = (CodeBuffer >> (16-BitCount)) - Huffman->FirstCode[BitCount] + Huffman->FirstSymbol[BitCount];
    Stream->CodeBuffer >>= BitCount;
    Stream->NumBits -= BitCount;    
    ak_u16 Result = Huffman->Symbols[Code];
    return Result;
}

inline ak_bool
AK_Internal__ZLibInflate(ak_internal__zlib_stream* Stream)
{    
    ak_u8 BFINAL;
    ak_u8 BTYPE;
    
    do
    {
        BFINAL = (ak_u8)Stream->GetBits(1);
        BTYPE = (ak_u8)Stream->GetBits(2);
        
        switch(BTYPE)
        {
            case AK_ZLIB_COMPRESSION_NONE:
            {
                if(Stream->NumBits & 0x7)
                    Stream->GetBits(Stream->NumBits & 0x07);
                
                //Drain remaining bits
                ak_u8 Bytes[4];           
                ak_u32 ByteIndex = 0;
                while(Stream->NumBits > 0)
                {
                    Bytes[ByteIndex++] = (ak_u8)(Stream->CodeBuffer & 0xFF);
                    Stream->CodeBuffer >>= 8;
                    Stream->NumBits -= 8;
                }                
                AK_Assert(Stream->NumBits == 0, "Bit count in byte stream is not 0. This is a programming error.");
                
                while(ByteIndex < 4)
                    Bytes[ByteIndex++] = Stream->GetU8();
                
                ak_u16 Len  = (Bytes[1] << 8) | Bytes[0];
                ak_u16 NLen = (Bytes[3] << 8) | Bytes[2];
                
                if(NLen != (Len ^ 0xFFFF)) return AK_Internal__ZLibError("ZLib data uncompressed is corrupted. Len and NLen are undefined");                
                if(!Stream->IsValid()) return AK_Internal__ZLibError("ZLib data uncompressed is corrupted. Read past the ZLib buffer");
                
                AK_MemoryCopy(Stream->OutputStream+Stream->OutputAt, Stream->Stream+Stream->At, Len);
                Stream->OutputAt += Len;
                Stream->At += Len;
                
            } break;
            
            case AK_ZLIB_COMPRESSION_FIXED:
            case AK_ZLIB_COMPRESSION_DYNAMIC:
            {          
                ak_internal__zlib_huffman LitLenHuffman;
                ak_internal__zlib_huffman DistHuffman;
                
                if(BTYPE == AK_ZLIB_COMPRESSION_FIXED)
                {      
                    LitLenHuffman = AK_Internal__ZLibBuildHuffman(AK_Internal__FixedLitLenCodeLen, AK_Count(AK_Internal__FixedLitLenCodeLen));
                    DistHuffman = AK_Internal__ZLibBuildHuffman(AK_Internal__FixedDistCodeLen, AK_Count(AK_Internal__FixedDistCodeLen));
                }
                else
                {
                    ak_u8 HuffmanCodeLenCodeLen[19] = {};
                    
                    ak_u32 HLIT = Stream->GetBits(5) + 257;
                    ak_u32 HDIST = Stream->GetBits(5) + 1;
                    ak_u32 HCLEN = Stream->GetBits(4) + 4;
                    
                    for(ak_u32 CodeLenIndex = 0; CodeLenIndex < HCLEN; CodeLenIndex++)                    
                        HuffmanCodeLenCodeLen[AK_Internal__CodeLenCodeLenOrder[CodeLenIndex]] = (ak_u8)Stream->GetBits(3);
                    
                    ak_internal__zlib_huffman CodeLenHuffman = AK_Internal__ZLibBuildHuffman(HuffmanCodeLenCodeLen, AK_Count(HuffmanCodeLenCodeLen));
                    
                    ak_u8 LitLenDistCodeLen[286+33] = {};
                    
                    ak_u32 Counter = 0;
                    while(Counter < (HLIT+HDIST))
                    {
                        ak_i32 DecodedValue = AK_Internal__ZLibDecodeHuffman(&CodeLenHuffman, Stream);
                        if(DecodedValue == -1)
                            return AK_Internal__ZLibError("Error decoding code len huffman");
                        
                        if(DecodedValue < 16)
                        {
                            LitLenDistCodeLen[Counter++] = (ak_u8)DecodedValue;
                        }
                        else
                        {
                            ak_u8 CopyValue = 0;
                            ak_u32 RepeatValue = 0;
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
                                return AK_Internal__ZLibError("ZLib data compressed is corrupted. The dynamic values are invalid");                                                            
                            
                            while(RepeatValue--)
                                LitLenDistCodeLen[Counter++] = CopyValue;
                        }
                    }
                    
                    LitLenHuffman = AK_Internal__ZLibBuildHuffman(LitLenDistCodeLen, HLIT);
                    DistHuffman = AK_Internal__ZLibBuildHuffman(LitLenDistCodeLen+HLIT, HDIST);
                }
                
                for(;;)
                {
                    ak_i32 DecodedValue = AK_Internal__ZLibDecodeHuffman(&LitLenHuffman, Stream);
                    if(DecodedValue == -1)
                        AK_Internal__ZLibError("Error decoded lit len huffman");
                    
                    if(DecodedValue < 256)
                    {
                        Stream->OutputStream[Stream->OutputAt++] = (ak_u8)DecodedValue;                        
                    }
                    else if(DecodedValue == 256)
                    {
                        break;
                    }
                    else
                    {
                        DecodedValue -= 257;
                        ak_u32 Length = AK_Internal__ZLibBaseLength[DecodedValue];
                        if(AK_Internal__ZLibLengthExtraBits[DecodedValue])
                            Length += Stream->GetBits(AK_Internal__ZLibLengthExtraBits[DecodedValue]);
                        
                        DecodedValue = AK_Internal__ZLibDecodeHuffman(&DistHuffman, Stream);
                        ak_u32 Distance = AK_Internal__ZLibBaseDist[DecodedValue];
                        if(AK_Internal__ZLibDistExtraBits[DecodedValue])
                            Distance += Stream->GetBits(AK_Internal__ZLibDistExtraBits[DecodedValue]);
                        
                        if(Distance > Stream->OutputAt)
                            return AK_Internal__ZLibError("ZLib data compressed is corrupted. The distance to read is larger than our current ZLib buffer");
                        
                        ak_u8* P = Stream->OutputStream + (Stream->OutputAt - Distance);
                        
                        while(Length--)                        
                            Stream->OutputStream[Stream->OutputAt++] = *P++;                        
                    }                                        
                }
            } break;
            
            default:
            {
                AK_Internal__ZLibError("ZLib data is corrupted. Could not find a valid compression type");
            } break;
        }
        
    } while(!BFINAL);
    
    return true;
}

ak_bool AK_ZLibDecompress(void* DecompressedData, void* CompressedData, ak_u32 CompressedDataLength)
{
    ak_internal__zlib_stream Stream = {};
    Stream.Stream = (ak_u8*)CompressedData;
    Stream.Size = CompressedDataLength;
    Stream.OutputStream = (ak_u8*)DecompressedData;
    
    ak_u32 CM = (ak_u8)Stream.GetBits(4);
    ak_u32 CINFO = (ak_u8)Stream.GetBits(4);
    
    if(CM != 8) return AK_Internal__ZLibError("ZLib compression method is not supported. Only supported method is deflate");    
    if(CINFO > 7) return AK_Internal__ZLibError("ZLib compression info not supported");
    
    ak_u8 CMF = ((CINFO << 4) & 0xF0) | (CM & 0x0F);
    ak_u8 FLAG = (ak_u8)Stream.GetBits(8);
    
    ak_u8 FCHECK = (FLAG & 0x1F);
    ak_u8 FDICT  = (FLAG & 0x20);
    ak_u8 FLEVEL = (FLAG & 0xC0);
    
    if((CMF*256 + FLAG) % 31 != 0) return AK_Internal__ZLibError("ZLib header is corrupted");    
    if(FDICT) return AK_Internal__ZLibError("ZLib preset dictionary is not supported");
    
    return AK_Internal__ZLibInflate(&Stream);            
}