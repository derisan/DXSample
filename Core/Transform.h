#pragma once
#include "Component.h"

class Transform :
    public Component
{
public:
    Transform();
    ~Transform();

    virtual void FinalUpdate() override;
	
	const vec3&		GetLocalPosition() const { return mLocalPosition; }
	const vec3&		GetLocalRotation() const { return mLocalRotation; }
	const vec3&		GetLocalScale() const { return mLocalScale; }
	const matrix&	GetLocalToWorldMatrix() const { return mWorldMatrix; }
	const vec3&		GetWorldPosition() const { return mWorldMatrix.Translation(); }
	vec3			GetRight() const { return mWorldMatrix.Right(); }
	vec3			GetUp() const { return mWorldMatrix.Up(); }
	vec3			GetForward() const { return mWorldMatrix.Backward(); }	
	std::weak_ptr<Transform> GetParent() const { return mParent; }
	
	void SetLocalPosition(const vec3& position) { mLocalPosition = position; }
	void SetLocalRotation(const vec3& rotation) { mLocalRotation = rotation; }
	void SetLocalScale(const vec3& scale) { mLocalScale = scale; }
	void SetParent(std::shared_ptr<Transform> parent) { mParent = parent; }

private:
    vec3 mLocalPosition = {};
    vec3 mLocalRotation = {};
    vec3 mLocalScale = {1.0f, 1.0f, 1.0f};

    matrix mLocalMatrix = {};
    matrix mWorldMatrix = {};

    std::weak_ptr<Transform> mParent;
};