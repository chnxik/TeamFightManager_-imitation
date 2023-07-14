cbuffer Transform : register(b0)
{
    row_major matrix mWorld;
    row_major matrix mView;
    row_major matrix mProjection;
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

Texture2D albedoTexture : register(t0);

SamplerState PointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);