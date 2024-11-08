/*
* @file		ModelBones.h
* @brief	モデルのボーン
* @author	Morita
* @date		2024/08/26
*/

#include "pch.h"

#include "ModelBones.h"


ModelBones::ModelBones(bool createHead, bool createGun)
	:
	rotation(0.0f),
	m_elapsedTime(0.0f),
	m_animationType{}
{
	float scale = 2.6f;

	CrateBons(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f) / 3.0f * scale, 1.0f, BonsType::Body);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f) / 3.0f * scale, 1.0f, BonsType::BodyDown, Body);
	CrateBons(DirectX::SimpleMath::Vector3(-0.7f, 1.1f, 0.0f) / 3.0f * scale, 1.0f, BonsType::LArmUp, Body);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, -0.7f, 0.0f) / 3.0f * scale, 1.0f, BonsType::LArmDown, LArmUp);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, -0.7f, 0.0f) / 3.0f * scale, 1.0f, BonsType::LArmHand, LArmDown);
	CrateBons(DirectX::SimpleMath::Vector3(0.7f, 1.1f, 0.0f) / 3.0f * scale, 1.0f, BonsType::RArmUp, Body);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, -0.7f, 0.0f) / 3.0f * scale, 1.0f, BonsType::RArmDown, RArmUp);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, -0.7f, 0.0f) / 3.0f * scale, 1.0f, BonsType::RArmHand, RArmDown);
	CrateBons(DirectX::SimpleMath::Vector3(-0.3f, -0.2f, 0.0f) / 3.0f * scale, 1.0f, BonsType::LLegUp, BodyDown);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, -1.15f, -0.1f) / 3.0f * scale, 1.0f, BonsType::LLegDown, LLegUp);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, -1.3f, 0.0f) / 3.0f * scale, 1.0f, BonsType::LShoes, LLegDown);
	CrateBons(DirectX::SimpleMath::Vector3(0.3f, -0.2f, 0.0f) / 3.0f * scale, 1.0f, BonsType::RLegUp, BodyDown);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, -1.15f, -0.1f) / 3.0f * scale, 1.0f, BonsType::RLegDown, RLegUp);
	CrateBons(DirectX::SimpleMath::Vector3(0.0f, -1.3f, 0.0f) / 3.0f * scale, 1.0f, BonsType::RShoes, RLegDown);
	if (createHead)CrateBons(DirectX::SimpleMath::Vector3(0.0f, 1.2f, 0.0f) / 3.0f * scale, 1.0f, BonsType::Head, Body);
	if (createGun) CrateBons(DirectX::SimpleMath::Vector3(-0.1f, -0.2f, 0.0f) / 3.0f * scale, 1.0f, BonsType::Gun, RArmHand);
}

ModelBones::~ModelBones()
{
}

void ModelBones::Initialize()
{
	//		初期のアニメーションの種類
	m_animationType = AnimationType::Stay;
}

void ModelBones::CrateBons(DirectX::SimpleMath::Vector3 position, float length, BonsType type, BonsType parent)
{
	PlayerBonsInformation bons;

	//		ボーンの情報を格納する
	bons.position = position;

	position.y;
	bons.firstPosition = position;
	bons.length = length;
	bons.type = type;
	bons.parent = parent;

	m_bonesInformation.push_back(bons);
}

BonsType ModelBones::ParentProcess(DirectX::SimpleMath::Matrix* world, BonsType modelType)
{
	//		回転量を掛ける
	*world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion
	(m_bonesInformation[static_cast<int>(modelType)].rotation);

	if (m_bonesInformation[static_cast<int>(modelType)].parent == BonsType::Empty)
	{
		//		座標を掛ける
		*world *= DirectX::SimpleMath::Matrix::CreateTranslation(
			m_bonesInformation[static_cast<int>(modelType)].position);

		return BonsType::Empty;
	}
	else
	{
		//		親クラスの相対位置を掛ける
		*world *= DirectX::SimpleMath::Matrix::CreateTranslation(
			m_bonesInformation[static_cast<int>(modelType)].firstPosition);

		ParentProcess(world, m_bonesInformation[static_cast<int>(modelType)].parent);
	}

	return BonsType::Empty;
}
