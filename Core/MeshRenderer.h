#pragma once
#include "Component.h"

class Mesh;
class Material;

class MeshRenderer :
    public Component
{
public:
    MeshRenderer();
    ~MeshRenderer();

    void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = std::move(mesh); }
    void SetMaterial(std::shared_ptr<Material> material) { mMaterial = std::move(material); }

    virtual void Update() override { render(); }

private:
    void render();

private:
    std::shared_ptr<Mesh> mMesh = nullptr;
    std::shared_ptr<Material> mMaterial = nullptr;
};

