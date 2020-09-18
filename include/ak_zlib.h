#ifndef AK_ZLIB_H
#define AK_ZLIB_H

ak_string AK_ZLib_GetErrorMessage();
ak_bool AK_ZLibDecompress(void* DecompressedData, void* CompressedData, ak_u32 CompressedDataLength);

#endif