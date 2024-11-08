/*
* @file		PlayerCamera.cpp
* @brief	プレイヤーのカメラ
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayerWallWalkCamera.h"

PlayerWallWalkCamera::PlayerWallWalkCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_time(0.0f)
{
}

PlayerWallWalkCamera::~PlayerWallWalkCamera()
{
}

void PlayerWallWalkCamera::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_playerCameraManager->GetInformation()->SetCameraAngleMin(-20.0f);
}

void PlayerWallWalkCamera::Update()
{
	if (m_time < 1.0f)
	{
		//		経過時間 ＊　５
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 5.0f;

		//		一秒以上にならないようにする
		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		float angle = 0;
		float radian = 0;

		//		カメラ角度と移動角度を受け取る
		RadianConversion(&angle, &radian);

		//		カメラの角度を設定する
		m_playerCameraManager->GetInformation()->SetAngle({
			Library::Lerp(angle, radian, m_time),
			m_playerCameraManager->GetInformation()->GetAngle().y });
	}
	else
	{
		//		通常のカメラと同じ動き
		m_playerCameraManager->CameraMove();
	}

	//		デグリーからラジアンへ行列にする
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::
		CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

	//		向いている角度にする
	DirectX::SimpleMath::Matrix rotation = matrixY * matrixX;

	//		カメラ座標
	DirectX::SimpleMath::Vector3 position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		視点方向
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), rotation.Invert());


	//		ターゲットにプレイヤーの座標を足す
	target += m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	DirectX::SimpleMath::Vector3 directin2 = m_playerCameraManager->GetPlayerInformationCamera()->GetWallWalkNormalize();

	float length2 = m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() / 5.0f;

	directin2 = DirectX::SimpleMath::Vector3::Lerp(DirectX::SimpleMath::Vector3::Zero, directin2 * 0.1f, length2);

	directin2.y = Library::Lerp(1.0f, 0.9f, length2);

	//		アップベクトル
	DirectX::SimpleMath::Vector3 up = directin2;

	//		ビュー行列を作成
	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::CreateLookAt
	(position, target, up);

	m_playerCameraManager->GetInformation()->SetEye(position);
	m_playerCameraManager->GetInformation()->SetTarget(target);
	m_playerCameraManager->GetInformation()->SetUp(up);

	//		視線ベクトルを設定する
	m_playerCameraManager->GetInformation()->SetViewVelocity(target - position);

	//		ビュー行列を設定する
	LibrarySingleton::GetInstance()->SetView(view);

	//		もしカメラ移動量が０以下の場合
	if (m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() <= 0.0f)
	{
		//		プレイヤーカメラに切り替える
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::Standard);
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

void PlayerWallWalkCamera::Finalize()
{
	m_time = 0.0f;
}

void PlayerWallWalkCamera::RadianConversion(float* cameraangle, float* velocityRadian)
{
	int radian = static_cast<int>(DirectX::XMConvertToDegrees(
		atan2(m_playerCameraManager->GetPlayerInformationCamera()->GetDirection().z,
			m_playerCameraManager->GetPlayerInformationCamera()->GetDirection().x)));


	//		カメラの角度を受け取る
	int angle = static_cast<int>(m_playerCameraManager->GetInformation()->GetAngle().x);

	//		範囲を0~３６０にする
	radian = (radian - 90) % 360;
	angle %= 360;

	//		０以下の場合360を足し正の数にする
	if (angle < 0.0f) { angle += 360; }
	if (radian < 0.0f) { radian += 360; }

	//		最短距離で移動するため（+ -）(- +)の時(+ -)の方に360を足す
	if (radian < 90 && angle > 270)
	{
		radian += 360;
	}
	else if (angle < 90.0f && radian > 270)
	{
		angle += 360;
	}

	*cameraangle = static_cast<float>(angle);
	*velocityRadian = static_cast<float>(radian);
}
