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
	auto offset = GetTransform()->GetOffset();
	
	CMD_LIST->SetGraphicsRoot32BitConstants(0, 4, &offset, 0);

	mMaterial->Render();
	mMesh->Render();
}
