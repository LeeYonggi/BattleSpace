#include "DXUT.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
	Init();
}


ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::Init()
{
	for (int i = 0; i < OBJ_LAST; i++)
		m_ObjectList.insert(make_pair(OBJ_KINDS(i), new list<Object*>()));
}

void ObjectManager::Update()
{
	for (auto iter : m_ObjectList)
	{
		for (auto obj = iter.second->begin(); obj != iter.second->end(); )
		{
			if ((*obj)->isDestroy)
			{
				SAFE_RELEASE((*obj));
				SAFE_DELETE((*obj));
				obj = iter.second->erase(obj);
			}
			else
			{
				if ((*obj)->isActive)
					(*obj)->Update();
				obj++;
			}
		}
	}
}

void ObjectManager::Render()
{
	for (auto iter : m_ObjectList)
	{
		for (auto obj = iter.second->begin(); obj != iter.second->end(); obj++)
		{
			if ((*obj)->isActive)
				(*obj)->Render();
		}
	}
}

void ObjectManager::Release()
{
	for (auto iter : m_ObjectList)
	{
		for (auto _iter : *iter.second)
		{
			SAFE_RELEASE(_iter);
			SAFE_DELETE(_iter);
		}
		iter.second->clear();
		SAFE_DELETE(iter.second);
	}
	m_ObjectList.clear();
}

list<Object*> *ObjectManager::GetObjectList(OBJ_KINDS kind)
{
	auto iter = m_ObjectList.find(kind);
	if (iter == m_ObjectList.end()) return nullptr;

	return iter->second;
}
