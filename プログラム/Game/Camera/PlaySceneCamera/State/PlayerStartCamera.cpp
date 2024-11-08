/*
* @file		PlayerStartCamera.h
* @brief	プレイヤースタートカメラ
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerStartCamera.h"

PlayerStartCamera::PlayerStartCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_time(0.0f),
	m_firstViewJudgement(true)
{
}

PlayerStartCamera::~PlayerStartCamera()
{
}

void PlayerStartCamera::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	//		ゲームスタートフラグをオフにする
	m_playerCameraManager->GetGameManager()->FalseFlag(GameManager::GameStart);

	if (!m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::StartLimitView))
	{
		m_firstViewJudgement = true;
	}
}

void PlayerStartCamera::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	float move = 1.0f - pow(1.0f - m_time, 4.0f);

	//		デグリーからラジアンへ行列にする
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetStartDirection()));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::
		CreateRotationX(DirectX::XMConvertToRadians(Library::Lerp(-40.0f, 0.0f, move)));

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

	if (m_time >= 1.0f)
	{
		//		初期状態の場合
		if (m_firstViewJudgement)
		{
			m_playerCameraManager->GetGameManager()->TrueFlag(GameManager::StartLimitView);

			if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::GameStart))
			{
				m_firstViewJudgement = false;

				//		スタンダードカメラにする
				m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Standard);
			}

			return;
		}

		//		スタンダードカメラにする
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Standard);

		//		ゲームスタートフラグをオンにする
		m_playerCameraManager->GetGameManager()->TrueFlag(GameManager::GameStart);
	}
}

void PlayerStartCamera::Finalize()
{
	m_time = 0.0f;

	m_playerCameraManager->GetInformation()->SetAngle({ m_playerCameraManager->GetStartDirection(), 0.0f});
}
