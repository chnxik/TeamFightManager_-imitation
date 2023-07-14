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
    float4 color = float4(0.f, 1.f, 0.f, 1.f);
    
    if (0 < overlapcnt)
        color = float4(1.f, 0.f, 0.f, 1.f);
  
    return color;
}