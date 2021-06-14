#pragma once
#include "Component.h"

enum class LIGHT_TYPE : uint8
{
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT
};

enum
{
    MAX_LIGHT_COUNTS = 50
};

struct LightColor
{
    vec4 Diffuse;
    vec4 Ambient;
    vec4 Specular;
};

struct LightInfo
{
    LightColor Color;
    vec4 Position;
    vec4 Direction;
    int32 LightType;
    float Range;
    float Angle;
    float Padding;
};

struct LightParams
{
    uint32 LightCount;
    vec3 Padding;
    LightInfo Lights[MAX_LIGHT_COUNTS];
};

class Light :
    public Component
{
public:
    Light();
    virtual ~Light();

    virtual void FinalUpdate() override;

	const LightInfo& GetLightInfo() { return mLightInfo; }

	void SetDiffuse(const vec3& diffuse) { mLightInfo.Color.Diffuse = diffuse; }
	void SetAmbient(const vec3& ambient) { mLightInfo.Color.Ambient = ambient; }
	void SetSpecular(const vec3& specular) { mLightInfo.Color.Specular = specular; }
	void SetLightDirection(const vec3& direction) { mLightInfo.Direction = direction; }
	void SetLightType(LIGHT_TYPE type) { mLightInfo.LightType = static_cast<int32>(type); }
	void SetLightRange(float range) { mLightInfo.Range = range; }
	void SetLightAngle(float angle) { mLightInfo.Angle = angle; }

private:
    LightInfo mLightInfo = {};
};

