/*
* @file		PlayerCameraManager.cpp
* @brief	プレイヤーのカメラのマネージャー
* @author	Morita
* @date		2024/05/08
*/

#include "pch.h"

#include "PlayerCameraManager.h"

PlayerCameraManager::PlayerCameraManager(GameManager* gameManager)
	:
	m_state{},
	m_playerInformation{},
	m_gameManager(gameManager),
	m_cameraType{},
	m_startDirection(0.0f),
	m_nowViewAngle(70.0f)
{
	//		カメラの情報を
	m_information = std::make_unique<PlayerCameraInformation>();

	//		カメラの派生クラスの生成
	m_stateInformation.insert({ CameraType::Standard, std::make_unique<PlayerCamera>(this) });
	m_stateInformation.insert({ CameraType::Debug, std::make_unique<DebugCamera>(this) });
	m_stateInformation.insert({ CameraType::WallWalk, std::make_unique<PlayerWallWalkCamera>(this) });
	m_stateInformation.insert({ CameraType::Start, std::make_unique<PlayerStartCamera>(this) });
	m_stateInformation.insert({ CameraType::Stop, std::make_unique<PlayerCameraStop>(this) });
	m_stateInformation.insert({ CameraType::Death, std::make_unique<PlayerDeathCamera>(this) });
	m_stateInformation.insert({ CameraType::Goal, std::make_unique<PlayerGoalCamera>(this) });
}

PlayerCameraManager::~PlayerCameraManager()
{
}

void PlayerCameraManager::Initialize(PlayerInformation* playerInformation)
{
	m_playerInformation = playerInformation;

	/*
	*	視野角70度
	*/
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(m_information->GetViewAngle()), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);

	//		情報の初期化
	m_information->Initialize();

	//		初期状態
	m_cameraType = CameraType::Start;

	//		初期状態を設定する
	m_state = m_stateInformation[m_cameraType].get();

	//		初期化処理
	m_state->Initialize();

	//		一度更新をしておく(Effectの為)
	m_state->Update();
}

void PlayerCameraManager::Update()
{
	//		カメラの更新処理
	m_state->Update();

	ViewingAngle();
}

void PlayerCameraManager::Finalize()
{
	m_startDirection = 0.0f;
	m_information->Finalize();
}

void PlayerCameraManager::CameraMove()
{
	//		マウスの相対位置から移動量を出す
	float x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	float y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	DirectX::SimpleMath::Vector2 angle = m_information->GetAngle();

	//		移動量
	DirectX::SimpleMath::Vector2 move = DirectX::SimpleMath::Vector2::Zero;

	//		カメラの移動量を足す
	move.x += x * m_information->GetCameraSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();
	move.y += -y * (m_information->GetCameraSpeed() / 2.0f) * LibrarySingleton::GetInstance()->GetElpsedTime();

	angle += move;

	//		視点移動の制限
	angle.y = Library::Clamp(angle.y, m_information->GetCameraAngleMin(), m_information->ANGLE_Y_MAX);
	
	m_information->SetAngle(angle);
	m_information->SetCameraMove(move);

}

void PlayerCameraManager::ChangeState(CameraType type)
{
	//		現在の同じ状態なら行わない
	if (type == m_cameraType) return;

	//		現在の状態の終了処理を行う
	m_state->Finalize();

	//		新しい状態に上書きする
	m_cameraType = type;

	//		新しい状態にする
	m_state = m_stateInformation[m_cameraType].get();

	//		新しい状態の初期化をする
	m_state->Initialize();

}

void PlayerCameraManager::ViewingAngle()
{
	float time = Library::Clamp(((m_playerInformation->GetAcceleration().Length() - 30.0f) / 60.0f), 0.0f, 1.0f);

	float angle = Library::Lerp(0.0f, 30.0f, time);

	m_nowViewAngle = Library::Lerp(m_nowViewAngle, angle, 0.7f);

	float viewAnge = m_nowViewAngle + m_information->GetViewAngle();

	//		ビュー行列を作成する
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);



	/*
	float time = Library::Clamp(((m_playerInformation->GetAcceleration().Length() - 30.0f) / 60.0f), 0.0f, 1.0f);

	float angle = Library::Lerp(0.0f, 30.0f, time);

	m_nowViewAngle = Library::Lerp(m_nowViewAngle, angle, 0.7f);

	float viewAnge = m_nowViewAngle + m_information->GetViewAngle();

	//		ビュー行列を作成する
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);
	*/

}

void PlayerCameraManager::ViewAngleUpdate(PlayerInformation* playerInformation)
{
	m_playerInformation = playerInformation;

	float time = Library::Clamp(((m_playerInformation->GetAcceleration().Length() - 30.0f) / 60.0f), 0.0f, 1.0f);

	float move = time;

	float viewAnge = Library::Lerp(m_information->GetViewAngle(), m_information->GetViewAngle() + 20.0f, move);

	//		proj行列を作成する
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);
}
