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
    float2 frameUV = (SpriteLeftTop - diff - SpriteOffset);
    float2 UV = (SpriteLeftTop - diff - SpriteOffset) + (AtlasSize * In.UV);
    
    if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
        || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
        discard;
    
    if (0 < UseMasking)
    {
        if (Left >= In.Pos.x || Right <= In.Pos.x)
            discard;
    
        if (Top >= In.Pos.y || Bottom <= In.Pos.y)
            discard;
    }
    
    color = atlasTexture.Sample(PointSampler, UV);
    
    if (DamagedTime == 0)
    {
        return color;
    };
    
    // Champ Damaged effect
    float4 DamageColor = 1.f - color;
    
    color.x += DamageColor * DamagedTime;
    color.y += DamageColor * DamagedTime;
    color.z += DamageColor * DamagedTime;
    
    return color;
}