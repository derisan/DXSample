#include "CorePch.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "GameObject.h"
#include "Engine.h"
#include "Camera.h"

MeshRenderer::MeshRenderer()
	: Component(COMPONENT_TYPE::MESH_RENDERER)
{

}

MeshRenderer::~MeshRenderer()
{
	
}

void MeshRenderer::Render()
{
	CMD_LIST->SetGraphicsRoot32BitConstants(ROOT_PARAMS_WORLD, 16, &GetTransform()->GetLocalToWorldMatrix(), 0);

	auto viewProj = Camera::sViewMatrix * Camera::sProjectionMatrix;
	CMD_LIST->SetGraphicsRoot32BitConstants(ROOT_PARAMS_VIEWPROJ, 32, &viewProj, 0);
	
	mMaterial->Render();
	mMesh->Render();
}
