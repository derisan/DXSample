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
	CMD_LIST->SetGraphicsRootConstantBufferView(RootParamIndex::ROOT_PARAM_WORLD, GetTransform()->GetWorldCbGpuAddr());

	mMaterial->Render();
	mMesh->Render();
}
