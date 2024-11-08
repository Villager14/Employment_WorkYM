/*
* @file		Factory.cpp
* @brief	ファクトリー
* @author	Morita
* @date		2024/08/21
*/

#include "pch.h"

#include "Factory.h"

#include "IFactory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Game/PlayScene/ObjectManager/GrinderObject/GriderObject.h"

#include "Game/PlayScene/ObjectManager/WallObject/WallObject.h"

#include "Game/PlayScene/ObjectManager/GoalObject/GoalObject.h"

#include "Game/PlayScene/ObjectManager/FloorObject/FloorObject.h"

#include "Game/PlayScene/ObjectManager/WireObject/WireObject.h"

#include "Game/PlayScene/ObjectManager/SignboardObject/SignboardObject.h"

Factory::Factory(ObjectManager* objectManager)
{
	m_objectInformation[Object::Grider] = [objectManager] {return std::make_unique<GriderObject>(objectManager); };
	m_objectInformation[Object::Wall] = [objectManager] {return std::make_unique<WallObject>(objectManager); };
	m_objectInformation[Object::Goal] = [objectManager] {return std::make_unique<GoalObject>(objectManager); };
	m_objectInformation[Object::Floor] = [objectManager] {return std::make_unique<FloorObject>(objectManager); };
	m_objectInformation[Object::Wire] = [objectManager] {return std::make_unique<WireObject>(objectManager); };
	m_objectInformation[Object::Signboard] = [objectManager] {return std::make_unique<SignboardObject>(objectManager); };
}

Factory::~Factory()
{
}

std::unique_ptr<IFactory> Factory::CreateObject
(Object type, ObjectInformation objectInformation)
{
	//		オブジェクトタイプがあるかどうか
	auto it = m_objectInformation.find(type);

	if (it != m_objectInformation.end())
	{
		std::unique_ptr<IFactory> factory = it->second();

		//		初期化処理
		factory->Initialize(objectInformation);

		return factory;
	}

	return nullptr;
}
 