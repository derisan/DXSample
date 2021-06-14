#pragma once
#include "Component.h"

class Transform :
    public Component
{
public:
    Transform();
    ~Transform();

    void SetOffset(const vec4& offset) { mOffset = offset; }
    vec4 GetOffset() const { return mOffset; }

private:
    vec4 mOffset = {};
};