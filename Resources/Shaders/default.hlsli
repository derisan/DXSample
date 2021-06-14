cbuffer cbWorld : register(b0)
{
    row_major matrix gWorld : packoffset(c0);
}

cbuffer cbViewProj : register(b1)
{
    row_major matrix gViewProj : packoffset(c0);
}

Texture2D texImage : register(t0);
SamplerState samplerType : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct PS_INPUT
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output;
    
    output.position = mul(float4(input.position, 1.0f), gWorld);
    output.position = mul(output.position, gViewProj);
    
    output.uv = input.uv;
   
    return output;
}

float4 PS_Main(PS_INPUT input) : SV_Target
{
    float4 color = texImage.Sample(samplerType, input.uv);
    
    return color;
}