/*
* @file		PlayerDeathCamera.cpp
* @brief	プレイヤーの死亡カメラ
* @author	Morita
* @date		2024/05/22
*/

#include "pch.h"

#include "PlayerDeathCamera.h"

PlayerDeathCamera::PlayerDeathCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager)
{
}

PlayerDeathCamera::~PlayerDeathCamera()
{
}

void PlayerDeathCamera::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void PlayerDeathCamera::Update()
{
	//		デグリーからラジアンへ行列にする
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

	//		向いている角度にする
	DirectX::SimpleMath::Matrix rotation = matrixY * matrixX;

	//		カメラ座標
	DirectX::SimpleMath::Vector3 position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		視点方向
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), rotation.Invert());

	//		ターゲットにプレイヤーの座標を足す
	target += m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		アップベクトル
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		ビュー行列を設定する
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	(position, target, up));

	m_playerCameraManager->GetInformation()->SetEye(position);
	m_playerCameraManager->GetInformation()->SetTarget(target);
	m_playerCameraManager->GetInformation()->SetUp(up);

	//		視線ベクトルを設定する
	m_playerCameraManager->GetInformation()->SetViewVelocity(target - position);

	//		もし死亡状態が解除されたら
	if (!m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		スタートカメラ
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::Start);
	}
}

void PlayerDeathCamera::Finalize()
{
	//		カメラの角度をリセットする
	m_playerCameraManager->GetInformation()->SetAngle(DirectX::SimpleMath::Vector2::Zero);
}
