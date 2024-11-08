/*
* @file		PlayerCameraStop.cpp
* @brief	プレイヤー動かないのカメラ
* @author	Morita
* @date		2024/06/10
*/

#include "pch.h"

#include "PlayerCameraStop.h"

PlayerCameraStop::PlayerCameraStop(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager)
{
}

PlayerCameraStop::~PlayerCameraStop()
{
}

void PlayerCameraStop::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void PlayerCameraStop::Update()
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

	//		プレイヤーの停止が終了したとき
	if (!m_playerCameraManager->GetPlayerInformationCamera()->GetCameraStop())
	{
		//		プレイヤーカメラに切り替える
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::Standard);
	}

	//		もしカメラ移動量が０より大きかったら
	if (m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() > 0.0f)
	{
		//		壁走りカメラに切り替える
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::WallWalk);
	}

	//		死亡している場合
	if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		死亡カメラにする
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Death);
	}

	//		次のシーンを選んだ際
	if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::EndJudgement))
	{
		//		ゴールカメラにする
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Goal);
	}
}

void PlayerCameraStop::Finalize()
{
}
