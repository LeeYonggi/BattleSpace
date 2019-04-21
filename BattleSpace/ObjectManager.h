#pragma once
#include "Singleton.h"

enum OBJ_KINDS
{
	OBJ_CAMERA,
	OBJ_BACKGROUND,
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_PBULLET,
	OBJ_EBULLET,
	OBJ_SAVEPOINT,
	OBJ_ITEM,
	OBJ_EFFECT,
	OBJ_BACKUI,
	OBJ_UI,
	OBJ_FRONTUI,
	OBJ_CREATOR,
	OBJ_LAST
};
class ObjectManager :
	public Singleton<ObjectManager>
{
public:
	ObjectManager();
	virtual ~ObjectManager();

private:
	map<OBJ_KINDS, list<Object*>*> m_ObjectList;
public:
	void Init();
	void Update();
	void Render();
	void Release();

public:
	template<class T>
	T *AddObject(OBJ_KINDS kind, T *obj)
	{
		auto iter = m_ObjectList.find(kind);
		if (iter == m_ObjectList.end()) return nullptr;

		obj->Init();

		iter->second->push_back(obj);

		return obj;
	}
	list<Object*> *GetObjectList(OBJ_KINDS kind);
};

#define OBJECTMANAGER ObjectManager::GetInstance()
