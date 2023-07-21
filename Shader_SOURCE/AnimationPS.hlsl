#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITIONT;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float4 color = (float4) 0.0f;
    
    float2 diff = (AtlasSize - SpriteSize) / 2.0f;
    float2 UV = (SpriteLeftTop - diff - SpriteOffset) + (AtlasSize * In.UV);
    
    if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
        || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
        discard;
    
    color = atlasTexture.Sample(PointSampler, UV);
    
    return color;
}