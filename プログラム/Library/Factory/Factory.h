/*
* @file		Factory.h
* @brief	�t�@�N�g���[
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
		Floor,		//		���I�u�W�F�N�g
		Wall,		//		�ǃI�u�W�F�N�g
		Goal,		//		�S�[���I�u�W�F�N�g
		Grider,		//		�j��I�u�W�F�N�g
		Wire,		//		���C���[�I�u�W�F�N�g
		Signboard,	//		�ŔI�u�W�F�N�g
		None,
	};

public:

	std::unique_ptr<IFactory> CreateObject(Object type,
		ObjectInformation objectInformation);

private:

	//		�I�u�W�F�N�g�}�l�[�W���[
	//ObjectManager* m_objectManager;

	//		�I�u�W�F�N�g�̏��
	std::unordered_map<Object, std::function<std::unique_ptr<IFactory>()>> m_objectInformation;
};
