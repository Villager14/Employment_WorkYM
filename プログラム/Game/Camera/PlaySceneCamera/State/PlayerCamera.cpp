/*
* @file		PlayerCamera.cpp
* @brief	プレイヤーのカメラ
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayerCamera.h"

PlayerCamera::PlayerCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_shakingTime(0.0f),
	m_shakingRatio(0.0f),
	m_shakingSpeed(0.0f)
{
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_playerCameraManager->GetInformation()->SetCameraAngleMin(m_playerCameraManager->GetInformation()->ANGLE_Y_MIN);
}

void PlayerCamera::Update()
{
	m_playerCameraManager->CameraMove();

	//		現在の座標
	m_position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//m_shakingTime = 0.0f;


	//		デグリーからラジアンへ行列にする
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

	//		向いている角度にする
	DirectX::SimpleMath::Matrix rotation = matrixY * matrixX;

	//		視点方向
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), rotation.Invert());

	//		ターゲットにプレイヤーの座標を足す
	target += m_position;

	//		アップベクトル
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		ビュー行列を設定する
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	(m_position, target, up));

	m_playerCameraManager->GetInformation()->SetEye(m_position);
	m_playerCameraManager->GetInformation()->SetTarget(target);
	m_playerCameraManager->GetInformation()->SetUp(up);

	//		視線ベクトルを設定する
	m_playerCameraManager->GetInformation()->SetViewVelocity(target - m_position);

	//		カメラ停止フラグがtrueの時
	if (m_playerCameraManager->GetPlayerInformationCamera()->GetCameraStop())
	{
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Stop);
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

void PlayerCamera::Finalize()
{
}

void PlayerCamera::ShakingView()
{
	//		現在の座標
	m_position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		プレイヤーの速度を受け取る
	float playerSpeed = m_playerCameraManager->GetPlayerInformationCamera()->GetAcceleration().Length();

	//		頭を動かす割合を設定する
	m_shakingRatio = playerSpeed / m_playerCameraManager->GetPlayerInformationCamera()->GetMaxSpeed();

	//		頭を動かす速さ
	m_shakingSpeed = Library::Lerp(2.0f, 10.0f, m_shakingRatio);

	//		頭を動かす速さ
	m_shakingTime += LibrarySingleton::GetInstance()->GetElpsedTime() * m_shakingSpeed;

	//		縦揺れ
	VerticalShaking();

	//		横揺れ
	HorizontalShaking();
	
}

void PlayerCamera::HorizontalShaking()
{
	DirectX::SimpleMath::Vector2 velocity = { m_playerCameraManager->GetInformation()->GetViewVelocity().x,
										m_playerCameraManager->GetInformation()->GetViewVelocity().z };

	velocity.Normalize();

	velocity = DirectX::SimpleMath::Vector2(velocity.y, -velocity.x);


	float move = (sinf(m_shakingTime) + 1.0f) / 2.0f;

	//		頭の動きの幅
	float moveLength = Library::Lerp(0.0f, 0.2f, m_shakingRatio);


	velocity = DirectX::SimpleMath::Vector2::Lerp( DirectX::SimpleMath::Vector2(velocity.x, velocity.y) * moveLength,
										DirectX::SimpleMath::Vector2(velocity.x, velocity.y) * -moveLength,
										move);

	m_position.x += velocity.x;
	m_position.z += velocity.y;
}

void PlayerCamera::VerticalShaking()
{
	float move = (sinf(m_shakingTime * 2.0f) + 1.0f) / 2.0f;

	//		頭の動きの幅
	float moveLength = Library::Lerp(0.0f, 0.4f, m_shakingRatio);

	m_position.y += Library::Lerp(-moveLength, moveLength, move);
}
