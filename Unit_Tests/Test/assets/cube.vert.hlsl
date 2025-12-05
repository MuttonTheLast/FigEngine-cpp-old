#include "./cube.hlsli"

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.Position = float4(input.Position, 1);
    output.Color = float4(input.Color, 1);
    return output;
}


float4 PSMain(VSOutput input) : SV_Target0
{
    return input.Color;
}

