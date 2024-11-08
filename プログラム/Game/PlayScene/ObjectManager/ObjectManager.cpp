/*
* @file		ObjectManager.cpp
* @brief	�I�u�W�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "ObjectManager.h"

#include "BackGroundObject/BackGroundObject.h"

ObjectManager::ObjectManager(GameManager* gameManager)
	:
	m_gameManager(gameManager)
{
	//		���b�V���̕`��𐶐�����
	m_drawMesh = std::make_unique<DrawMesh>();

	//		�w�i�I�u�W�F�N�g�̐���
	m_backGroundObject = std::make_unique<BackGroundObject>(this);

	//		�t�@�N�g���[
	m_factory = std::make_unique<Factory>(this);

	//		�I�u�W�F�N�g�̓ǂݍ��݃N���X�̐���
	m_loadObjectInformation = std::make_unique<LoadingObjectInformation>();
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	//		�X�e�[�W�̓ǂݍ���
	m_loadObjectInformation->Load(0);

	int wireNumber = 0;

	for (int i = 0, max = static_cast<int>
		(m_loadObjectInformation->GetObjectInformation().size());
		i < max; ++i)
	{
		//		���C���[���I�u�W�F�N�g�̍쐻
		CreateWireInformation(i, &wireNumber);

		m_factoryObject.push_back(m_factory->CreateObject(
			Factory::Object(m_loadObjectInformation->GetObjectInformation()[i].objectType),
			m_loadObjectInformation->GetObjectInformation()[i]));

	}

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		�O���C�_�[�̃��b�V��
		if (m_factoryObject[i]->GetObjectType() == Factory::Grider)
		{
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(0));
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(1));
		}

		//		�ǂ̃��b�V�� �����b�V���@�S�[���I�u�W�F�N�g
		if (m_factoryObject[i]->GetObjectType() == Factory::Wall ||
			m_factoryObject[i]->GetObjectType() == Factory::Goal ||
			m_factoryObject[i]->GetObjectType() == Factory::Floor)
		{
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(0));
		}
	}

	//		�w�i�I�u�W�F�N�g�̏�����
	m_backGroundObject->Initialize(m_objectMesh, m_wireObjectPosition);
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_playerPosition = playerPosition;

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		�X�V����
		m_factoryObject[i]->Update();
	}
}

void ObjectManager::Render(PlayerCameraInformation* cameraInformation,
	DirectX::SimpleMath::Vector3 cameraPosition,
	PostEffectFlag::Flag flag, PostEffectObjectShader* objectShader)
{
	m_cameraInformation = cameraInformation;
	m_cameraPosition = cameraPosition;

	m_backGroundObject->Render(flag, objectShader);

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		�`�揈��
		m_factoryObject[i]->Render(flag, objectShader);
	}
}

void ObjectManager::Finalize()
{
	m_backGroundObject->Finalize();

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		m_factoryObject[i]->Finalize();
	}

	m_objectMesh.clear();
	m_objectMesh.shrink_to_fit();

	m_factoryObject.clear();
	m_factoryObject.shrink_to_fit();

	m_loadObjectInformation->Finalize();
}

bool ObjectManager::Culling(DirectX::SimpleMath::Vector3 position, float length)
{
	//		Y�����C�ɂ���������length�ȏ�̏ꍇ����
	if ((DirectX::SimpleMath::Vector3(position.x, 0.0f, position.z) -
		DirectX::SimpleMath::Vector3(m_cameraPosition.x, 0.0f, m_cameraPosition.z)).Length() > length)
	{
		return false;
	}

	//		�J��������̃I�u�W�F�N�g�̕���
	DirectX::SimpleMath::Vector3 objectVelocityUnder =
		position - m_cameraPosition;

	//		Y���͋C�ɂ��Ȃ��悤�ɂ���
	objectVelocityUnder.y = 0.0f;

	DirectX::SimpleMath::Vector3 cameraDirection = m_cameraInformation->GetViewVelocity();

	cameraDirection.y = 0.0f;

	//		���K������
	objectVelocityUnder.Normalize();

	//		���ς̒l��-0.2��菬�����ꍇ����
	if (cameraDirection.Dot(objectVelocityUnder) < -0.2f)
	{
		return false;
	}

	return true;
}

void ObjectManager::CreateWireInformation(int index, int *wireNumber)
{
	if (Factory::Object(m_loadObjectInformation->GetObjectInformation()[index].objectType)
		== Factory::Object::Wire)
	{
		WireObjectInformation information;

		//		�ԍ�
		information.number = *wireNumber;
		*wireNumber += 1;

		//		���W
		information.position =
			m_loadObjectInformation->GetObjectInformation()[index].position;

		m_wireObjectPosition.push_back(m_loadObjectInformation->GetObjectInformation()[index].position);

		m_wireInformation.push_back(information);
	}
}
