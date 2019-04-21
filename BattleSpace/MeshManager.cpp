#include "DXUT.h"
#include "MeshManager.h"


MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
	Release();
}

CMeshLoader * MeshManager::AddMesh(string str, wstring fileName)
{
	auto iter = m_Meshs.find(str);
	if (iter != m_Meshs.end()) return iter->second;

	CMeshLoader *temp = new CMeshLoader;

	temp->Create(DEVICE, fileName.c_str());

	m_Meshs.insert(make_pair(str, temp));

	return temp;
}

vector<CMeshLoader*> MeshManager::AddAnimeMesh(string str, wstring fileName, int low, int high)
{
	vector<CMeshLoader*> temp;

	for (int i = low; i <= high; i++)
	{
		WCHAR wstr[128];
		wsprintf(wstr, fileName.c_str(), i);
		temp.push_back(AddMesh(str + to_string(i), wstr));
	}
	return temp;
}

vector<Material*>* MeshManager::GetMaterials(wstring fileName, vector<Material*>* materials)
{
	auto iter = m_Material.find(fileName);
	if (iter != m_Material.end()) return iter->second;

	m_Material.insert(make_pair(fileName, materials));

	return nullptr;
}

void MeshManager::DrawMesh(CMeshLoader * mesh, Vector3 pos, Matrix matR, float scale, D3DXCOLOR color)
{
	Matrix matW, matT, matS;
	
	D3DXMatrixScaling(&matS, scale, scale, scale);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);
	
	matW = matS * matR * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	Vector3 dir = {1.0f, -1.0f, 1.0f};

	D3DLIGHT9 light = d3d::GetDirectionalLight(&dir, &color);

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->LightEnable(0, true);
	DEVICE->SetLight(0, &light);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	for (int i = 0; i < mesh->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl = mesh->GetMaterial(i)->mtl;
		mtl.Ambient.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Diffuse.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Specular.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Emissive = D3DXCOLOR(mesh->GetMaterial(i)->mtl.Diffuse) * 0.4f;
		mtl.Emissive.a = mesh->GetMaterial(i)->fAlpha;

		mtl.Power = 1.0f;

		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, mesh->GetMaterial(i)->pTexture);
		mesh->GetMesh()->DrawSubset(i);
	}
}

void MeshManager::DrawEffect(CMeshLoader * mesh, Texture *texture, Vector3 pos, Matrix matR, float scale, D3DXCOLOR color)
{
	Matrix matW, matT, matS;

	D3DXMatrixScaling(&matS, scale, scale, scale);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matW = matS * matR * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	Vector3 dir = { 1.0f, -1.0f, 1.0f };

	D3DLIGHT9 light = d3d::GetDirectionalLight(&dir, &color);

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->LightEnable(0, true);
	DEVICE->SetLight(0, &light);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	for (int i = 0; i < mesh->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl = mesh->GetMaterial(i)->mtl;
		mtl.Ambient.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Diffuse.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Specular.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Emissive = D3DXCOLOR(mesh->GetMaterial(i)->mtl.Diffuse) * 1.0f;
		mtl.Emissive.a = mesh->GetMaterial(i)->fAlpha;

		mtl.Power = 1.0f;

		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, texture->tex);
		mesh->GetMesh()->DrawSubset(i);
	}
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHSRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHSRCALPHA);
}

void MeshManager::DrawAlphaMesh(CMeshLoader * mesh, Vector3 pos, Matrix matR, float scale, D3DXCOLOR color, bool isCullMode)
{
	Matrix matW, matT, matS;

	D3DXMatrixScaling(&matS, scale, scale, scale);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matW = matS * matR * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	Vector3 dir = { 1.0f, -1.0f, 1.0f };

	D3DLIGHT9 light = d3d::GetDirectionalLight(&dir, &color);

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->LightEnable(0, true);
	DEVICE->SetLight(0, &light);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	if(isCullMode)
		DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	for (int i = 0; i < mesh->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl = mesh->GetMaterial(i)->mtl;
		mtl.Ambient.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Diffuse.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Specular.a = mesh->GetMaterial(i)->fAlpha;
		mtl.Emissive = D3DXCOLOR(mesh->GetMaterial(i)->mtl.Diffuse) * 1.0f;
		mtl.Emissive.a = mesh->GetMaterial(i)->fAlpha;

		mtl.Power = 1.0f;

		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, mesh->GetMaterial(i)->pTexture);
		mesh->GetMesh()->DrawSubset(i);
	}
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHSRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHSRCALPHA);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void MeshManager::Release()
{
	for (auto iter : m_Material)
	{
		for (auto _iter : *iter.second)
		{
			SAFE_DELETE(_iter);
		}
		iter.second->clear();
		SAFE_DELETE(iter.second);
	}
	m_Material.clear();

	for (auto iter : m_Meshs)
	{
		SAFE_DELETE(iter.second);
	}
	m_Meshs.clear();
}
