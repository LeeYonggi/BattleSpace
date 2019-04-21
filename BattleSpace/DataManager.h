#pragma once
#include "Singleton.h"


class SavePoint;

class DataManager :
	public Singleton<DataManager>
{
public:
	DataManager();
	virtual ~DataManager();

public:
	Vector3 savePoint;
	int point = 0;

};

#define DATAMANAGER DataManager::GetInstance()