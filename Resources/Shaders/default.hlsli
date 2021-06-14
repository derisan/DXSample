#ifndef _DEFAULT_HLSLI_
#define _DEFAULT_HLSLI_

#include "params.hlsli"
#include "utils.hlsli"

struct VS_INPUT
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct PS_INPUT
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
    float3 viewPos : POSITION;
    float3 viewNormal : NORMAL;
};

PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output;
    
    output.position = mul(float4(input.position, 1.0f), gWorld);
    output.position = mul(output.position, gView);
    
    output.viewPos = output.position;
    
    output.position = mul(output.position, gProj);

    output.viewNormal = mul(input.normal, (float3x3) gWorld);
    output.viewNormal = normalize(mul(output.viewNormal, (float3x3) gView));
    
    output.uv = input.uv;

    return output;
}

float4 PS_Main(PS_INPUT input) : SV_Target
{
    float4 color = texImage.Sample(samplerType, input.uv);
    
    return color;
}

#endif