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
    float4 color = float4(1.0f, 0.f, 1.0f, 1.0f);
    
    color = albedoTexture.Sample(PointSampler, In.UV);
    
    if (color.w == 0.f)
        discard;
    
    if (0 < UseMasking)
    {
        if (Left >= In.Pos.x || Right <= In.Pos.x)
            discard;
    
        if (Top >= In.Pos.y || Bottom <= In.Pos.y)
            discard;
    }
    
    if (0.f < useGray)
    {
        float gray = ((color.x + color.y + color.z) / 3.f) * GrayRatio;
        color.x = gray;
        color.y = gray;
        color.z = gray;
    }
    
    if (0.f < useAlpha)
    {
        color.w = AlphaRatio;
    }
    
    return color;
    }