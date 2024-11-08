/*
* @file		PlayScene.cpp
* @brief	プレイシーン
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayScene.h"

#include "Common/DebugDraw.h"

PlayScene::PlayScene(SceneManager* sceneManager)
	:
	m_sceneManager{sceneManager},
	m_menuCloseJugement(false)
{
	Generation();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//		ゲームマネージャーの初期化処理
	m_gameManager->Initialize();

	//		リミットタイムを設定する
	m_gameManager->SetLimitTime(90.0f);

	//		プレイヤーカメラマネージャーの初期化処理
	m_playerCameraManager->Initialize(m_player->GetInformation());

	//		カメラの情報を受け取る
	m_player->SetCameraInformation(m_playerCameraManager->GetInformation());

	//		プレイヤーの初期化処理
	m_player->Initialize();

	//		オブジェクトマネージャーの初期化処理
	m_objectManager->Initialize();

	//		UIマネージャーの初期化
	m_uiManager->Initialize();

	//		ポストエフェクトマネージャーの初期化
	m_postEffectManager->Initialize(m_gameManager->BACK_GROUND_COLOR);

	//		ワイヤーの情報を受け取る
	m_effectManager->SetWireInformation(m_objectManager->GetUseWireInformation());

	//		エフェクトマネージャーの初期化
	m_effectManager->Initialize();

	//		リスポーンマネージャーの初期化
	m_respawnManager->Initialize();

	//		プレイシーン時のBGMを再生
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::PlayScene);

	//		視野角の情報を受け取る
	m_playerCameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

	//		視野角の更新
	m_playerCameraManager->ViewAngleUpdate(m_player->GetInformation());

	//		カメラの速度の更新
	m_playerCameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());
}

void PlayScene::Generation()
{
	//		ゲームマネージャーを生成する
	m_gameManager = std::make_unique<GameManager>();

	//		プレイヤーカメラマネージャーの生成
	m_playerCameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		プレイヤーの生成
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		ポストエフェクトマネージャー
	m_postEffectManager = std::make_unique<PostEffectManager>(m_gameManager.get(),
															  m_sceneManager->GetMenuManager()->GetInformation());

	//		エフェクトマネージャーの作製
	m_effectManager = std::make_unique<EffectManager>(m_player->GetInformation(), m_playerCameraManager->GetInformation());

	//		UIマネージャーの生成
	m_uiManager = std::make_unique<UIManager>(m_player->GetInformation(), m_gameManager.get());

	//		当たり判定マネージャーの生成
	m_collitionManager = std::make_unique<CollitionManager>(m_gameManager.get());

	//		オブジェクトマネージャーの生成
	m_objectManager = std::make_unique<ObjectManager>(m_gameManager.get());

	//		リスポーンマネージャー
	m_respawnManager = std::make_unique<RespawnManager>(m_gameManager.get());
}

bool PlayScene::MenuInformation()
{
	//		メニューを開いている場合の処理
	if (m_sceneManager->GetMenuManager()->GetInformation()->GetMenuJudgement())
	{
		//		メニューを開いている
		m_menuCloseJugement = true;

		//		視野角の情報を受け取る
		m_playerCameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

		//		視野角の更新
		m_playerCameraManager->ViewAngleUpdate(m_player->GetInformation());

		//		カメラの速度の更新
		m_playerCameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());

		//		グレイ
		m_postEffectManager->Update(PostEffectFlag::Flag::Color);

		return true;
	}

	return false;
}

void PlayScene::Update()
{
	//		Pを押すとリザルトになる
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState().IsKeyDown(DirectX::Keyboard::P))
	{
		m_sceneManager->ChangeScene(SceneManager::Result);

		return;
	}

	//		メニューを開いているかどうか
	if (MenuInformation()) return;

	//		メニューが使えるかどうか？
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_player->GetMenuUseJugement());

	//		オブジェクトマネージャーの更新処理
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		ワイヤーの情報を受け取る
	m_player->SetWireInformation(m_objectManager->GetUseWireInformation());

	//		視線ベクトルを設定する
	m_player->GetInformation()->SetViewVelocity(m_playerCameraManager->GetInformation()->GetViewVelocity());

	//		プレイヤーの更新処理
	m_player->Update(m_playerCameraManager->GetInformation());

	//		メッシュを受け取る
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		当たり判定の更新処理
	m_collitionManager->Update(m_player->GetPlayerInformationCollition());

	//		当たり判定の情報
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		メッシュアップデート
	m_player->MeshUpdate();

	//		マウス絶対モードから相対モードに切り替わる時一フレーム必要なので
	if (m_menuCloseJugement)
	{
		m_menuCloseJugement = false;
	}
	else
	{
		//		カメラマネージャーの更新処理
		m_playerCameraManager->Update();
	}

	//		プレイヤーにカメラの角度を送る
	m_player->GetInformation()->SetCameraAngle(m_playerCameraManager->GetInformation()->GetAngle());

	//		アニメーションのアップデート
	m_player->AnimationUpdate();

	//		UIマネージャーの更新
	m_uiManager->Update();

	//		ポストエフェクトの更新処理
	for (int i = 1; i <= PostEffectFlag::Flag::Fade;)
	{
		m_postEffectManager->Update(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		ゲームマネージャーの更新処理
	m_gameManager->Update();

	//		エフェクトマネージャーの描画
	m_effectManager->Update();

	//		リスポーンポイントの更新処理
	m_respawnManager->Update(m_player->GetInformation()->GetPosition());

	//		リスポーン座標を設定する
	m_player->GetInformation()->SetRespawnPosition(m_respawnManager->GetRespownPosition());

	//		リスポーン時の回転量を受け取る
	m_playerCameraManager->SetStartDirection(m_respawnManager->GetRespownDirection());

	//		次のシーンに切り替えるかどうか
	if (m_gameManager->FlagJudgement(GameManager::NextScene))
	{
		//		次のシーンに切り替える（リザルトシーン）
		m_sceneManager->ChangeScene(SceneManager::SceneType::Result);
	}
}

void PlayScene::Render()
{
	for (int i = 1; i <= PostEffectFlag::Flag::Fade;)
	{
		//		ポストエフェクトマネージャーの変更
		m_postEffectManager->Render(PostEffectFlag::Flag(i));

				//オブジェクトマネージャーの描画処理
		m_objectManager->Render(m_player->GetCameraInformation(),
			m_player->GetInformation()->GetPlayerHeight(),
			PostEffectFlag::Flag(i), m_postEffectManager->GetPostObjectShader());

		//		プレイヤーのモデル描画
		m_player->ModelRender(PostEffectFlag::Flag(i));

		//		エフェクトマネージャーの描画
		m_effectManager->Render(PostEffectFlag::Flag(i));

		if (PostEffectFlag::Flag(i) == PostEffectFlag::Flag::UI)
		{
			//		UIマネージャーの描画
			m_uiManager->FrontRender();
		}

		if (PostEffectFlag::Flag(i) == PostEffectFlag::Flag::UIBack)
		{
			//		UIマネージャーの後描画
			m_uiManager->BackRender();
		}

		//		ポストエフェクトマネージャーのラスト描画
		m_postEffectManager->RastRender(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		デバック描画
	m_player->DebugRender();

	//		レンダーテクスチャをリセットする
	m_postEffectManager->ResetRenderTarget();

	//		レンダーテクスチャの描画
	m_postEffectManager->RenderTextureView();
}

void PlayScene::Finalize()
{
	//		クリアタイムを受け取る
	m_sceneManager->SetClearTime(static_cast<int>(m_gameManager->GetTime()));

	//		死亡回数を受け取る
	m_sceneManager->SetDeathCount(static_cast<int>(m_gameManager->GetDeathCount()));


	m_sceneManager->SetMaxTime(static_cast<int>(m_gameManager->GetLimitTime()));

	//		ゲームマネージャーの終了処理
	m_gameManager->Finalize();

	m_collitionManager->Finalize();

	//		カメラの終了処理
	m_playerCameraManager->Finalize();

	//		プレイヤの終了処理
	m_player->Finalize();

	//		ポストエフェクトマネージャー
	m_postEffectManager->Finalize();

	//		リスポーンポイントの終了処理
	m_respawnManager->Finalize();

	//		エフェクトマネージャー
	m_effectManager->Finalize();
	
	//		UIマネージャーの終了処理
	m_uiManager->Finalize();

	m_objectManager->Finalize();
}