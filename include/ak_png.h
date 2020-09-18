#ifndef AK_PNG_H
#define AK_PNG_H

struct ak_png
{
    void* Texels;
    ak_u32   Width;
    ak_u32   Height;
    ak_u32   ComponentCount;        
    ak_bool IsValid();    
};

ak_string AK_PNG_GetErrorMessage();
ak_png AK_LoadPNG(ak_arena* Arena, ak_char* File);
ak_png AK_LoadPNG(ak_arena* Arena, ak_string File);

#endif