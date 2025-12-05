#pragma once
#include "SDL3/SDL_gpu.h"
#include <SDL3/SDL.h>

namespace Fig
{
    enum VertexElementFormat
    {
        VertexElementFormat_Invalid = SDL_GPU_VERTEXELEMENTFORMAT_INVALID,
        
        VertexElementFormat_Int = SDL_GPU_VERTEXELEMENTFORMAT_INT,
        VertexElementFormat_Int2 = SDL_GPU_VERTEXELEMENTFORMAT_INT2,
        VertexElementFormat_Int3 = SDL_GPU_VERTEXELEMENTFORMAT_INT3,
        VertexElementFormat_Int4 = SDL_GPU_VERTEXELEMENTFORMAT_INT4,

        
        VertexElementFormat_UInt = SDL_GPU_VERTEXELEMENTFORMAT_UINT,
        VertexElementFormat_UInt2 = SDL_GPU_VERTEXELEMENTFORMAT_UINT2,
        VertexElementFormat_UInt3 = SDL_GPU_VERTEXELEMENTFORMAT_UINT3,
        VertexElementFormat_UInt4 = SDL_GPU_VERTEXELEMENTFORMAT_UINT4,

        VertexElementFormat_Float = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT,
        VertexElementFormat_Float2 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
        VertexElementFormat_Float3 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
        VertexElementFormat_Float4 = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
        
        
        VertexElementFormat_Byte2 = SDL_GPU_VERTEXELEMENTFORMAT_BYTE2,
        VertexElementFormat_Byte4 = SDL_GPU_VERTEXELEMENTFORMAT_BYTE4,
        
        VertexElementFormat_UByte2 = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2,
        VertexElementFormat_UByte4 = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4,

        VertexElementFormat_Byte2_N = SDL_GPU_VERTEXELEMENTFORMAT_BYTE2_NORM,
        VertexElementFormat_Byte4_N = SDL_GPU_VERTEXELEMENTFORMAT_BYTE4_NORM,
        
        VertexElementFormat_UByte2_N = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2_NORM,
        VertexElementFormat_UByte4_N = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4_NORM,


        VertexElementFormat_Short2 = SDL_GPU_VERTEXELEMENTFORMAT_SHORT2,
        VertexElementFormat_Short4 = SDL_GPU_VERTEXELEMENTFORMAT_SHORT4,
        
        VertexElementFormat_UShort2 = SDL_GPU_VERTEXELEMENTFORMAT_USHORT2,
        VertexElementFormat_UShort4 = SDL_GPU_VERTEXELEMENTFORMAT_USHORT4,

        VertexElementFormat_Short2_N = SDL_GPU_VERTEXELEMENTFORMAT_SHORT2_NORM,
        VertexElementFormat_Short4_N = SDL_GPU_VERTEXELEMENTFORMAT_SHORT4_NORM,
        
        VertexElementFormat_UShort2_N = SDL_GPU_VERTEXELEMENTFORMAT_USHORT2_NORM,
        VertexElementFormat_UShort4_N = SDL_GPU_VERTEXELEMENTFORMAT_USHORT4_NORM,

        

        VertexElementFormat_Half2 = SDL_GPU_VERTEXELEMENTFORMAT_HALF2,
        VertexElementFormat_Half4 = SDL_GPU_VERTEXELEMENTFORMAT_HALF4,

    };
}
