#ifndef AK_PNG_H
#define AK_PNG_H

#define PNG_SIGNATURE 0x0A1A0A0D474E5089

struct png_result
{
    void* Texels;
    u32   Width;
    u32   Height;
    u32   ComponentCount;    
    
    inline b32 IsValid()
    {
        b32 Result = ((Texels != NULL) && (Width > 0) && (Height > 0) && (ComponentCount > 0));
        return Result;
    }
};

enum 
{    
    PNG_CHUNK_TYPE_IHDR = RIFF_CODE('I', 'H', 'D', 'R'),
    PNG_CHUNK_TYPE_IDAT = RIFF_CODE('I', 'D', 'A', 'T'),    
    PNG_CHUNK_TYPE_IEND = RIFF_CODE('I', 'E', 'N', 'D')    
};

enum png_filter_type
{
    PNG_FILTER_NONE,
    PNG_FILTER_SUB,
    PNG_FILTER_UP,
    PNG_FILTER_AVG,
    PNG_FILTER_PAETH
};

#pragma pack(push, 1)
struct ihdr
{
    u32 Width;
    u32 Height;
    u8 BitDepth;
    u8 ColorType;
    u8 CompressionMethod;
    u8 FilterMethod;    
    u8 InterlaceMethod;
};
#pragma pack(pop)

global const char* __Global__PNG_Internal_ErrorMessage;

inline b32 
PNG_Error(const char* ErrorMessage)
{
    __Global__PNG_Internal_ErrorMessage = ErrorMessage;
    return false;
}

inline const char* 
PNG_GetErrorMessage()
{
    return __Global__PNG_Internal_ErrorMessage;
}

struct png_data_chunk
{
    u8* Data;
    ptr Length;
    
    png_data_chunk* Next;
};

struct png_context
{
    ptr StreamLength;
    ptr StreamAt;
    u8* Stream;
    
    ptr CompressedStreamLength;
    u8* CompressedStream;
        
    u32 ComponentCount;
    u32 BytesPerComponent;
    u32 Width;
    u32 Height;        
};

struct png_chunk
{
    u32 Length;
    u32 Type;
};

inline u8* 
PNG_Read(png_context* Context, ptr Length)
{
    u8* Result = Context->Stream + Context->StreamAt;
    Context->StreamAt += Length;    
    
    if(Context->StreamAt > Context->StreamLength)
        return NULL;
    
    return Result;
}

inline png_chunk* 
PNG_GetChunk(png_context* Context)
{
    png_chunk* Result = (png_chunk*)PNG_Read(Context, sizeof(png_chunk));
    if(Result) Result->Length = EndianSwap32(Result->Length);                        
    return Result;
}

inline b32 
PNG_ValidateSignature(buffer* Buffer)
{
    u64 Signature = *(u64*)Buffer->Data;
    b32 Result = Signature == PNG_SIGNATURE;
    return Result;    
}

inline b32 
PNG_ValidateIHDR(ihdr* IHDR, u32* ComponentCount)
{
    if(IHDR->BitDepth == 8 || IHDR->BitDepth == 16)
    {
        b32 ValidIHDR = true;             
        if(IHDR->ColorType == 0) *ComponentCount = 1;
        else if(IHDR->ColorType == 2) *ComponentCount = 3;
        else if(IHDR->ColorType == 6) *ComponentCount = 4;
        else ValidIHDR = false;            
        
        if(!ValidIHDR)    
            return PNG_Error("PNG file is not supported. Must have 1, 3, or 4 channels.");            
        
        return true;
        
    }
    else
        return PNG_Error("PNG file is not supported. Must have 8 or 16 bits per pixel.");                        
}        

inline b32
PNG_ReadFileChunks(png_context* Context, buffer* Buffer)
{
    if(!PNG_ValidateSignature(Buffer))    
        return PNG_Error("PNG signature is invalid. Is this a PNG file?");            
    
    *Context = {};
    Context->Stream = Buffer->Data;
    Context->StreamLength = Buffer->Size;
    Context->StreamAt = 8;
    
    ihdr* IHDR = NULL;
    
    png_data_chunk* DataChunkList = NULL;    
    png_data_chunk* LastAddedChunk = NULL;
    
    while(png_chunk* Chunk = PNG_GetChunk(Context))
    {
        switch(Chunk->Type)
        {            
            case PNG_CHUNK_TYPE_IHDR:
            {
                IHDR = (ihdr*)PNG_Read(Context, Chunk->Length);
                if(!PNG_ValidateIHDR(IHDR, &Context->ComponentCount))                
                    return false;                
                
                Context->Width = EndianSwap32(IHDR->Width);
                Context->Height = EndianSwap32(IHDR->Height);
                Context->BytesPerComponent = IHDR->BitDepth/8;
            } break;
            
            case PNG_CHUNK_TYPE_IDAT:
            {
                png_data_chunk* DataChunk = PushStruct(png_data_chunk, Clear, 0);
                DataChunk->Length = Chunk->Length;
                DataChunk->Data = PNG_Read(Context, Chunk->Length);
                
                if(!DataChunkList)
                {
                    DataChunkList = DataChunk;
                    LastAddedChunk = DataChunkList;
                }
                else
                {                    
                    LastAddedChunk->Next = DataChunk;
                    LastAddedChunk = DataChunk;                    
                }                
            } break;
            
            case PNG_CHUNK_TYPE_IEND:
            {                
                if(!DataChunkList)                
                    return PNG_Error("Invalid png file. Did not read any data chunks. Is the file corrupted?");                                                        
                
                png_data_chunk* At = DataChunkList;
                while(At)
                {
                    Context->CompressedStreamLength += At->Length;
                    At = At->Next;
                }
                
                Context->CompressedStream = (u8*)PushSize(Context->CompressedStreamLength, Clear, 0);
                
                At = DataChunkList;    
                u8* Dst = Context->CompressedStream;
                while(At)
                {
                    CopyMemory(Dst, At->Data, At->Length);
                    Dst += At->Length;
                    At = At->Next;
                }
                
                return true;                
            } break;
            
            default:
            {
                PNG_Read(Context, Chunk->Length);
            } break;
        }           
        
        //NOTE(EVERYONE): We skip the cyclic redundacy check.
        //TODO(JJ): Maybe perform the CRC algorithm test to make sure everything has validated correcly?
        PNG_Read(Context, 4);
    }    
    
    return PNG_Error("Could not find the last IEND chunk for the PNG file. Is the file corrupted?");    
}

inline u8 
PaethFilter8(u8 A, u8 B, u8 C)
{
    i32 a = (i32)A;
    i32 b = (i32)B;
    i32 c = (i32)C;
    
    i32 p = a + b - c;
    
    i32 pa = p - a;
    i32 pb = p - b;
    i32 pc = p - c;
    if(pa < 0) pa = -pa;
    if(pb < 0) pb = -pb;
    if(pc < 0) pc = -pc;
    
    if((pa <= pb) && (pa <= pc))
        return A;
    else if(pb <= pc)
        return B;
    else
        return C;
}

inline u16
PaethFilter16(u16 A, u16 B, u16 C)
{
    i32 a = (i32)A;
    i32 b = (i32)B;
    i32 c = (i32)C;
    
    i32 p = a + b - c;
    
    i32 pa = p - a;
    i32 pb = p - b;
    i32 pc = p - c;
    if(pa < 0) pa = -pa;
    if(pb < 0) pb = -pb;
    if(pc < 0) pc = -pc;
    
    if((pa <= pb) && (pa <= pc))
        return A;
    else if(pb <= pc)
        return B;
    else
        return C;
}

inline b32 
ReconstructPNG(void* DstTexels, void* SrcTexels, png_context* Context)
{
    u8* Src = (u8*)SrcTexels;
    u8* Dst = (u8*)DstTexels;
    
    u8* LastRow = NULL;
    for(u32 YIndex = 0; YIndex < Context->Height; YIndex++)
    {
        u8 FilterType = *Src++;
        
        u8* CurrentRow = Dst;
        switch(FilterType)
        {
            case PNG_FILTER_NONE:
            {
                for(u32 XIndex = 0; XIndex < Context->Width; XIndex++)
                {
                    u8* DstAt = Dst;
                    u8* SrcAt = Src;
                    for(u32 ComponentIndex = 0; ComponentIndex < Context->ComponentCount; ComponentIndex++)       
                    {
                        for(u32 ByteIndex = 0; ByteIndex < Context->BytesPerComponent; ByteIndex++)
                            *DstAt++ = *SrcAt++;                        
                    }                    
                }
            } break;
            
            case PNG_FILTER_SUB:
            {
                u8* PrevPixel = NULL;                
                for(u32 XIndex = 0; XIndex < Context->Width; XIndex++)
                {                    
                    u8* Start = Dst;
                    for(u32 ComponentIndex = 0; ComponentIndex < Context->ComponentCount; ComponentIndex++)
                    {
                        for(u32 ByteIndex = 0; ByteIndex < Context->BytesPerComponent; ByteIndex++)
                        {
                            u8 PrevPixelValue = PrevPixel ? PrevPixel[ComponentIndex*Context->BytesPerComponent + ByteIndex] : 0;
                            *Dst++ = (*Src++ + PrevPixelValue);                                                                        
                        }
                    }
                    PrevPixel = Start;                                                                                
                }
                
            } break;
            
            case PNG_FILTER_UP:
            {
                if(!LastRow)                
                    return PNG_Error("Failed to reconstruct the png file. Unfiltered data is corrupted. Skipping PNG");                                                        
                
                for(u32 XIndex = 0; XIndex < Context->Width; XIndex++)
                {
                    for(u32 ComponentIndex = 0; ComponentIndex < Context->ComponentCount; ComponentIndex++)                    
                    {
                        for(u32 ByteIndex = 0; ByteIndex < Context->BytesPerComponent; ByteIndex++)                        
                            *Dst++ = *Src++ + *LastRow++;                                            
                    }
                }
                
            } break;
            
            case PNG_FILTER_AVG:
            {
                if(!LastRow)                
                    return PNG_Error("Failed to reconstruct the png file. Unfiltered data is corrupted.");                                        
                
                u8* PrevPixel = NULL;
                for(u32 XIndex = 0; XIndex < Context->Width; XIndex++)
                {
                    u8* Start = Dst;
                    for(u32 ComponentIndex = 0; ComponentIndex < Context->ComponentCount; ComponentIndex++)
                    {
                        for(u32 ByteIndex = 0; ByteIndex < Context->BytesPerComponent; ByteIndex++)
                        {
                            u8 PrevPixelValue = PrevPixel ? PrevPixel[ComponentIndex*Context->BytesPerComponent + ByteIndex] : 0;
                            u8 LastRowValue = *LastRow++;
                            
                            u32 Avg = ((u32)PrevPixelValue + (u32)LastRowValue) / 2;                                                
                            *Dst++ = *Src++ + (u8)Avg;
                        }
                    }
                    PrevPixel = Start;                    
                }
            } break;
            
            case PNG_FILTER_PAETH:
            {
                if(!LastRow)                
                    return PNG_Error("Failed to reconstruct the png file. Unfiltered data is corrupted.");                                        
                
                u8* LastRowPrevPixel = NULL;
                u8* PrevPixel = NULL;
                
                for(u32 XIndex = 0; XIndex < Context->Width; XIndex++)
                {
                    u8* Start = Dst;
                    u8* StartLastRow = LastRow;
                    
                    for(u32 ComponentIndex = 0; ComponentIndex < Context->ComponentCount; ComponentIndex++)
                    {
                        for(u32 ByteIndex = 0; ByteIndex < Context->BytesPerComponent; ByteIndex++)
                        {
                            u8 PrevPixelValue = PrevPixel ? PrevPixel[ComponentIndex*Context->BytesPerComponent + ByteIndex] : 0;
                            u8 LastRowValue = *LastRow++;
                            u8 PrevPixelLastRowValue = LastRowPrevPixel ? LastRowPrevPixel[ComponentIndex*Context->BytesPerComponent + ByteIndex] : 0;                        
                            
                            u8 Paeth = PaethFilter8(PrevPixelValue, LastRowValue, PrevPixelLastRowValue);                        
                            *Dst++ = *Src++ + Paeth;                        
                        }
                    }
                    
                    LastRowPrevPixel = StartLastRow;
                    PrevPixel = Start;
                }
            } break;
            
            default:
            {
                return PNG_Error("Failed to reconstruct the png file. Unfiltered data is corrupted. Could not find a valid filter type.");                
            } break;
        }
        
        LastRow = CurrentRow;
    }    
    
    if(Context->BytesPerComponent == 2)
    {
        u32 TotalPixels = Context->Width*Context->Height*Context->ComponentCount;
        u16* Dst16 = (u16*)DstTexels;
        
        for(u32 PixelIndex = 0; PixelIndex < TotalPixels; PixelIndex++)
            Dst16[PixelIndex] = EndianSwap16(Dst16[PixelIndex]);
    }
    
    return true;    
}

inline void PNG_Free(void* Texels)
{
    if(Texels)    
        FreeMemory(Texels);    
}

inline void 
PNG_Free(png_result* Result)
{
    PNG_Free(Result->Texels);
}

inline png_result
PNG_Load(string Path)
{
    temp_arena TempArena = BeginTemporaryMemory();
    
    png_result Result = {};
    
    buffer FileBuffer = ReadEntireFile(Path.Data);
    if(FileBuffer.IsValid())
    {
        png_context Context;        
        if(PNG_ReadFileChunks(&Context, &FileBuffer))
        {
            ptr DecompressedLength = (Context.Width*Context.ComponentCount*Context.BytesPerComponent+1)*Context.Height;
            u8* DecompressedData = (u8*)PushSize(DecompressedLength, Clear, 0);
            
            if(ZLib_Decompress(DecompressedData, Context.CompressedStream, Context.CompressedStreamLength))
            {                
                Result.Width = Context.Width;
                Result.Height = Context.Height;
                Result.ComponentCount = Context.ComponentCount;
                
                if(Context.BytesPerComponent == 1)
                {
                    void* Texels = AllocateMemory(Context.Width*Context.Height*Context.ComponentCount);                
                    if(ReconstructPNG(Texels, DecompressedData, &Context))
                    {
                        Result.Width = Context.Width;
                        Result.Height = Context.Height;
                        Result.ComponentCount = Context.ComponentCount;
                        Result.Texels = Texels;
                    }
                    else
                    {
                        PNG_Free(Texels);
                    }
                }
                else
                {
                    void* TempTexels = PushSize(Context.Width*Context.Height*Context.ComponentCount*Context.BytesPerComponent, Clear, 0);
                    if(ReconstructPNG(TempTexels, DecompressedData, &Context))
                    {
                        ptr ImageSize = Context.Width*Context.Height*Context.ComponentCount;
                        void* Texels = AllocateMemory(Context.Width*Context.Height*Context.ComponentCount);
                        
                        u8* DstTexels = (u8*)Texels;
                        u16* SrcTexels = (u16*)TempTexels;
                        
                        for(u32 TexelIndex = 0; TexelIndex < ImageSize; TexelIndex++)
                            DstTexels[TexelIndex] = (u8)((SrcTexels[TexelIndex] >> 8) & 0xFF);
                        
                        Result.Width = Context.Width;
                        Result.Height = Context.Height;
                        Result.ComponentCount = Context.ComponentCount;
                        Result.Texels = Texels;                        
                    }
                    
                }
            }
            else
            {                
                PNG_Error(ZLib_GetErrorMessage());
            }
        }        
    }
    else
    {
        PNG_Error("Failed to open the PNG file.");
    }
    
    EndTemporaryMemory(&TempArena);    
    return Result;
}

#endif