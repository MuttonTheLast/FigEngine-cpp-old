




struct VSInput
{
    float3 Position : TEXCOORD0;
    float2 UV : TEXCOORD1;
};

struct VSOutput
{
    float2 UV : TEXCOORD0;
    float4 Position : SV_Position;
};



