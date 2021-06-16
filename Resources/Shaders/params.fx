#ifndef _PARAMS_FX_
#define _PARAMS_FX_

struct LightColor
{
    float4 diffuse;
    float4 ambient;
    float4 specular;
};

struct LightInfo
{
    LightColor color;
    float4 position;
    float4 direction;
    int lightType;
    float range;
    float angle;
    float padding;
};

cbuffer cbWorld : register(b0)
{
    row_major matrix gWorld;
}

cbuffer cbViewProj : register(b1)
{
    row_major matrix gView;
    row_major matrix gProj;
}

cbuffer cbLight : register(b2)
{
    int gLightCount;
    float3 lightPadding;
    LightInfo gLights[50];
}

cbuffer cbMaterial : register(b3)
{
    int bUseNormalMap;
}

Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);

SamplerState samplerType : register(s0);

#endif