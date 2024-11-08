/*
* @file		Factory.h
* @brief	ファクトリー
* @author	Morita
* @date		2024/08/21
*/

#pragma once

#include <unordered_map>

#include "Game/PlayScene/ObjectManager/ObjectInformation.h"

class IFactory;

class ObjectManager;

class Factory
{
public:
	Factory(ObjectManager* ObjectManager);

	~Factory();

public:

	enum Object
	{
		Floor,		//		床オブジェクト
		Wall,		//		壁オブジェクト
		Goal,		//		ゴールオブジェクト
		Grider,		//		破壊オブジェクト
		Wire,		//		ワイヤーオブジェクト
		Signboard,	//		看板オブジェクト
		None,
	};

public:

	std::unique_ptr<IFactory> CreateObject(Object type,
		ObjectInformation objectInformation);

private:

	//		オブジェクトマネージャー
	//ObjectManager* m_objectManager;

	//		オブジェクトの情報
	std::unordered_map<Object, std::function<std::unique_ptr<IFactory>()>> m_objectInformation;
};
