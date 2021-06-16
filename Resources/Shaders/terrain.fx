#ifndef _TERRAIN_FX_
#define _TERRAIN_FX_

#include "params.fx"

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
    PS_INPUT output = (PS_INPUT)0;
    
    matrix worldView = mul(gWorld, gView);
    
    output.position = mul(float4(input.position, 1.0f), worldView);
    output.position = mul(output.position, gProj);
   
    output.uv = input.uv;

    return output;
}

float4 PS_Main(PS_INPUT input) : SV_Target
{
    float4 color = diffuseMap.Sample(samplerType, input.uv);
    
    //float4 color = float4(1.0f, 0.0f, 1.0f, 1.0f);
    
    return color;
}

#endif