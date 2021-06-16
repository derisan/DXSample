#ifndef _SKYBOX_FX_
#define _SKYBOX_FX_

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
    output.uv = input.uv;
    
    float4 viewPos = mul(float4(input.position, 0.0f), gView);
    float4 clipPos = mul(viewPos, gProj);
    
    output.position = clipPos.xyww;
    
    return output;
}

float4 PS_Main(PS_INPUT input) : SV_Target
{
    float4 color = diffuseMap.Sample(samplerType, input.uv);
        
    return color;
}

#endif