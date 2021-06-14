#include "CorePch.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "GameObject.h"
#include "Engine.h"

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
	CMD_LIST->SetGraphicsRoot32BitConstants(ROOT_PARAMS_VIEWPROJ, 16, &matrix::Identity, 0);
	CMD_LIST->SetGraphicsRoot32BitConstants(ROOT_PARAMS_VIEWPROJ, 16, &matrix::Identity, 16);

	mMaterial->Render();
	mMesh->Render();
}
