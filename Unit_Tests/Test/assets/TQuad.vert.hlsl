#include "./TQuad.hlsli"

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.Position = float4(input.Position, 1);
    output.UV = input.UV;
    return output;
}

Texture2D<float4> Texture : register(t0, space2);
SamplerState Sampler : register(s0, space2);
float4 PSMain(VSOutput input) : SV_Target0
{
    return Texture.Sample(Sampler, input.UV);
}

