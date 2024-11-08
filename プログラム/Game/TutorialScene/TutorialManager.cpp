/*
* @file		TutorialManager.cpp
* @brief	チュートリアル管理
* @author	Morita
* @date		2024/09/17
*/

#include "pch.h"

#include "TutorialManager.h"

#include "Scene/SceneManager.h"

TutorialManager::TutorialManager(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
	//		生成
	Generation();
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Initialize()
{
	//		チュートリアルをマップに追加
	m_tutorialInformation[TutorialState::Walk] = std::make_unique<TutorialWalkState>(this);

	//		初期の状態(Walk)
	m_tutorialState = TutorialState::Walk;

	//		現在のチュートリアル状態オブジェクトを取得
	m_state = m_tutorialInformation[m_tutorialState].get();

	//		初期化処理
	m_state->Initialize();

	//		オブジェクトマネージャーの初期化処理
	m_objectManager->Initialize();

	//		プレイヤーの初期化処理
	m_player->Initialize();

	//		プレイヤーカメラマネージャーの初期化処理
	m_cameraManager->Initialize(m_player->GetInformation());

	//		カメラの情報を受け取る
	m_player->SetCameraInformation(m_cameraManager->GetInformation());

	//		視野角の情報を受け取る
	m_cameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

	//		視野角の更新
	m_cameraManager->ViewAngleUpdate(m_player->GetInformation());

	//		カメラの速度の更新
	m_cameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());

	//		カメラの状態をスタンダードにする
	m_cameraManager->ChangeState(PlayerCameraManager::Standard);
}

void TutorialManager::Update()
{
	//		視線ベクトルを設定する
	m_player->GetInformation()->SetViewVelocity(m_cameraManager->GetInformation()->GetViewVelocity());

	//		プレイヤーのワールド座標を受け取る
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		オブジェクトマネージャーの更新処理
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		プレイヤーの更新処理
	m_player->Update(m_cameraManager->GetInformation());

	//		カメラの更新処理
	m_cameraManager->Update();

	//		プレイヤーにカメラの角度を送る
	m_player->GetInformation()->SetCameraAngle(m_cameraManager->GetInformation()->GetAngle());

	//		メッシュアップデート
	m_player->MeshUpdate();

	//		メッシュを受け取る
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		当たり判定の更新処理
	m_collitionManager->Update(m_player->GetPlayerInformationCollition());

	//		当たり判定の情報
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		アニメーションのアップデート
	m_player->AnimationUpdate();

}

void TutorialManager::Render()
{
	//		オブジェクトマネージャーの描画処理
	//m_objectManager->Render(m_player->GetCameraInformation()->GetViewVelocity(),
	//	m_player->GetInformation()->GetPlayerHeight(),
	//	);

	//		モデルの描画
	//m_player->ModelRender();

	//		デバック描画
	m_player->DebugRender();
}

void TutorialManager::Finalize()
{
}

void TutorialManager::Generation()
{
	//		ゲームマネージャーを生成する
	m_gameManager = std::make_unique<GameManager>();

	//		プレイヤーを生成する
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		カメラマネージャーを生成する
	m_cameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		オブジェクトマネージャー
	m_objectManager = std::make_unique<ObjectManager>(m_gameManager.get());

	//		当たり判定マネージャーの生成
	m_collitionManager = std::make_unique<CollitionManager>(m_gameManager.get());

	//		チュートリアルの情報を生成する
	m_information = std::make_unique<TutorialInformation>();

	//		チュートリアルの情報の初期化
	m_information->Initialize(m_player.get());
}
