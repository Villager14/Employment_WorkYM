/*
* @file		DebugCamera.cpp
* @brief	デバックカメラ
* @author	Morita
* @date		2024/04/23
*/

#include "pch.h"

#include "DebugCamera.h"

#include "Library/Library.h"

DebugCamera::DebugCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager)
{
	//		マウスを相対位置にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	//		マウスのフォールチをリセットする
	DirectX::Mouse::Get().ResetScrollWheelValue();
}

DebugCamera::~DebugCamera()
{
}

void DebugCamera::Initialize()
{
}

void DebugCamera::Update()
{
	m_playerCameraManager->CameraMove();

	//		行列にする
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::
		CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

	DirectX::SimpleMath::Matrix rt = rotY * rotX;

	//		カメラの座標
	DirectX::SimpleMath::Vector3 eye = {0.0f, 1.0f, 1.0f};

	DirectX::SimpleMath::Vector3 up = { 0.0f, 1.0f, 0.0f };

	//		注視している場所を中心に回転するようにする
	eye = DirectX::SimpleMath::Vector3::Transform(eye, rt.Invert());

	//		注視点からの距離
	eye *= (5.0f - 0.0f / 100.0f);

	up = DirectX::SimpleMath::Vector3::Transform(up, rt.Invert());

	//		ターゲットの座標を足す
	eye += m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		ターゲットの座標を設定する
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3
				(m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight().x,
				 m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight().y + 1.5f,
				 m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight().z);

	//		ビュー行列を設定する
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::
		CreateLookAt(eye, target, up));
}

void DebugCamera::Finalize()
{
}