#pragma once
#include "Singleton.h"
class MeshManager :
	public Singleton<MeshManager>
{
public:
	MeshManager();
	virtual ~MeshManager();

private:
	map<string, CMeshLoader*> m_Meshs;
	map<wstring, vector<Material*>*> m_Material;
public:
	CMeshLoader *AddMesh(string str, wstring fileName);
	vector<CMeshLoader*> AddAnimeMesh(string str, wstring fileName, int low, int high);
	vector<Material*> *GetMaterials(wstring fileName, vector<Material*>* materials);

	void DrawMesh(CMeshLoader *mesh, Vector3 pos, Matrix matR, float scale = 1.0f, D3DXCOLOR color = {1, 1, 1, 1});
	void DrawEffect(CMeshLoader *mesh, Texture *texture, Vector3 pos, Matrix matR, float scale = 1.0f, D3DXCOLOR color = {1, 1, 1, 1});
	void DrawAlphaMesh(CMeshLoader *mesh, Vector3 pos, Matrix matR, float scale = 1.0f, D3DXCOLOR color = { 1, 1, 1, 1 }, bool isCullMode = true);

	void Release();

};

#define MESHMANAGER MeshManager::GetInstance()