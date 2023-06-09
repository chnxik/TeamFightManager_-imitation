struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

cbuffer Color : register(b1)
{
    float4 Color;
}

float4 main(VSOut In) : SV_TARGET
{
    In.Color = Color;
    
     return In.Color;
}