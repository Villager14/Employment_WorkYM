/*
* @file		PlayerGoalCamera.cpp
* @brief	プレイヤーのゴールカメラ
* @author	Morita
* @date		2024/06/27
*/

#include "pch.h"

#include "PlayerGoalCamera.h"

PlayerGoalCamera::PlayerGoalCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_elapsedTime(0.0f),
	m_downElapsedTime(0.0f)
{
}

PlayerGoalCamera::~PlayerGoalCamera()
{
}

void PlayerGoalCamera::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_angle = m_playerCameraManager->GetInformation()->GetAngle();

	m_elapsedTime = 0.0f;

	m_downElapsedTime = 0.0f;
}

void PlayerGoalCamera::Update()
{
	CameraMove();

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
}

void PlayerGoalCamera::Finalize()
{
	//		カメラの角度をリセットする
	m_playerCameraManager->GetInformation()->SetAngle(DirectX::SimpleMath::Vector2::Zero);

}

void PlayerGoalCamera::CameraMove()
{
	if (m_elapsedTime < 2.0f)
	{

		//		経過時間
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;


		if (m_elapsedTime <= 1.0f)
		{
			//		カメラを平行にする
			m_playerCameraManager->GetInformation()->SetAngle({ m_angle.x ,Library::Lerp(m_angle.y, 0.0f, m_elapsedTime) });
		}
	}
	else
	{
		m_downElapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_downElapsedTime = Library::Clamp(m_downElapsedTime, 0.0f, 1.0f);

		//		下を向く
		m_playerCameraManager->GetInformation()->SetAngle({ m_angle.x ,Library::Lerp(0.0f, -50.0f, m_downElapsedTime) });
	}
}
