#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) (1.0f, 0.f, 1.0f, 1.0f);
    color = albedoTexture.Sample(PointSampler, In.UV);
    
    if (Left >= In.Pos.x || Right <= In.Pos.x)
        discard;
    
    if (Top >= In.Pos.y || Bottom <= In.Pos.y)
        discard;
    

    return color;
}