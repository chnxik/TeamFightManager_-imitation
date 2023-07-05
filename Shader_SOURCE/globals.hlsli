cbuffer Transform : register(b0)
{
    row_major matrix mWorld;
    row_major matrix mView;
    row_major matrix mProjection;
}

Texture2D albedoTexture : register(t0);

SamplerState PointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);