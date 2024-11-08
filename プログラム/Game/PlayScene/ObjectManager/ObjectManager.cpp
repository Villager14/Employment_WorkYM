/*
* @file		ObjectManager.cpp
* @brief	オブジェクトマネージャー
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
	//		メッシュの描画を生成する
	m_drawMesh = std::make_unique<DrawMesh>();

	//		背景オブジェクトの生成
	m_backGroundObject = std::make_unique<BackGroundObject>(this);

	//		ファクトリー
	m_factory = std::make_unique<Factory>(this);

	//		オブジェクトの読み込みクラスの生成
	m_loadObjectInformation = std::make_unique<LoadingObjectInformation>();
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	//		ステージの読み込み
	m_loadObjectInformation->Load(0);

	int wireNumber = 0;

	for (int i = 0, max = static_cast<int>
		(m_loadObjectInformation->GetObjectInformation().size());
		i < max; ++i)
	{
		//		ワイヤー情報オブジェクトの作製
		CreateWireInformation(i, &wireNumber);

		m_factoryObject.push_back(m_factory->CreateObject(
			Factory::Object(m_loadObjectInformation->GetObjectInformation()[i].objectType),
			m_loadObjectInformation->GetObjectInformation()[i]));

	}

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		グライダーのメッシュ
		if (m_factoryObject[i]->GetObjectType() == Factory::Grider)
		{
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(0));
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(1));
		}

		//		壁のメッシュ 床メッシュ　ゴールオブジェクト
		if (m_factoryObject[i]->GetObjectType() == Factory::Wall ||
			m_factoryObject[i]->GetObjectType() == Factory::Goal ||
			m_factoryObject[i]->GetObjectType() == Factory::Floor)
		{
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(0));
		}
	}

	//		背景オブジェクトの初期化
	m_backGroundObject->Initialize(m_objectMesh, m_wireObjectPosition);
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_playerPosition = playerPosition;

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		更新処理
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
		//		描画処理
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
	//		Y軸を気にせず距離がlength以上の場合消す
	if ((DirectX::SimpleMath::Vector3(position.x, 0.0f, position.z) -
		DirectX::SimpleMath::Vector3(m_cameraPosition.x, 0.0f, m_cameraPosition.z)).Length() > length)
	{
		return false;
	}

	//		カメラからのオブジェクトの方向
	DirectX::SimpleMath::Vector3 objectVelocityUnder =
		position - m_cameraPosition;

	//		Y軸は気にしないようにする
	objectVelocityUnder.y = 0.0f;

	DirectX::SimpleMath::Vector3 cameraDirection = m_cameraInformation->GetViewVelocity();

	cameraDirection.y = 0.0f;

	//		正規化処理
	objectVelocityUnder.Normalize();

	//		内積の値が-0.2より小さい場合消す
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

		//		番号
		information.number = *wireNumber;
		*wireNumber += 1;

		//		座標
		information.position =
			m_loadObjectInformation->GetObjectInformation()[index].position;

		m_wireObjectPosition.push_back(m_loadObjectInformation->GetObjectInformation()[index].position);

		m_wireInformation.push_back(information);
	}
}
