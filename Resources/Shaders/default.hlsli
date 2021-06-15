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
    float3 viewTanget : TANGENT;
    float3 viewBinormal : BINORMAL;
};

PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    
    matrix worldView = mul(gWorld, gView);
    
    output.position = mul(float4(input.position, 1.0f), worldView);
    output.viewPos = output.position;
    output.position = mul(output.position, gProj);
    
    output.viewNormal = normalize(mul(float4(input.normal, 0.0f), worldView).xyz);
    output.viewTanget = normalize(mul(float4(input.tangent, 0.0f), worldView).xyz);
    output.viewBinormal = normalize(cross(output.viewTanget, output.viewNormal));
  
    output.uv = input.uv;

    return output;
}

float4 PS_Main(PS_INPUT input) : SV_Target
{
    float4 color = diffuseMap.Sample(samplerType, input.uv);
    
    float3 viewNormal = input.viewNormal;
    if (bUseNormalMap)
    {
        float3 tangentSpaceNormal = normalMap.Sample(samplerType, input.uv).xyz;
        tangentSpaceNormal = (tangentSpaceNormal - 0.5f) * 2.0f;
        float3x3 TBN = { input.viewTanget, input.viewBinormal, input.viewNormal };
        viewNormal = normalize(mul(tangentSpaceNormal, TBN));
    }
    
    LightColor totalColor = (LightColor) 0;
    
    for (int i = 0; i < gLightCount; i++)
    {
        LightColor color = CalculateLightColor(i, viewNormal, input.viewPos);
        totalColor.diffuse += color.diffuse;
        totalColor.ambient += color.ambient;
        totalColor.specular += color.specular;
    }
    
    color.xyz = (totalColor.diffuse.xyz * color.xyz)
        + totalColor.ambient.xyz * color.xyz
        + totalColor.specular.xyz;
    
    return color;
}

#endif