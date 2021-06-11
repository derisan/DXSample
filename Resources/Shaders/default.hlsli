cbuffer cbOffset : register(b0)
{
    float4 offset : packoffset(c0);
}

struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output;
    
    output.position = float4(input.position, 1.0f) + offset;
    output.color = input.color;
    
    return output;
}

float4 PS_Main(PS_INPUT input) : SV_Target
{
    return input.color;
}