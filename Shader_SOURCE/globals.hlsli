cbuffer Transform : register(b0)
{
    row_major matrix    mWorld;
    row_major matrix    mView;
    row_major matrix    mProjection;
    float               mDir;
}

cbuffer Masking : register(b1)
{
    float Left;
    float Top;
    float Right;
    float Bottom;
}

cbuffer Collider : register(b2)
{
    int overlapcnt;
}

cbuffer Animator : register(b3)
{
    float2 SpriteLeftTop;
    float2 SpriteSize;
    float2 SpriteOffset;
    float2 AtlasSize;
}

cbuffer Champ : register(b4)
{
    float DamagedTime;
}

Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);

struct LightAttribute
{
    float4  color;
    float4  position;
    float4  direction;
    
    uint    type;
    float   radius;
    float   angle;
    int     pad;
};

StructuredBuffer<LightAttribute> lightsAttribute : register(t13);

SamplerState PointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);