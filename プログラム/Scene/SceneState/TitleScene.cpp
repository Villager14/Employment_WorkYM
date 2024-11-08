/*
* @file		TitleScene.cpp
* @brief	タイトルシーン
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
	//		タイトル選択マネージャーの生成
	m_titleSelectManager = std::make_unique<TitleSelectManager>();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//		タイトル選択マネージャーの初期化
	m_titleSelectManager->Initialize();

	//		タイトルのBGMの再生
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		メニューの情報を設定する
	m_titleSelectManager->SetMenuInformation(m_sceneManager->GetMenuManager()->GetInformation());

	CreateView();

	CreateProj();
}

void TitleScene::Update()
{
	//		メニューを使える状態にするかどうか？
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_titleSelectManager->
														GetInformation()->GetMenuUseJudgement());

	//		タイトル選択マネージャーの更新処理
	m_titleSelectManager->Update();

	//		シーンを終了するかどうか
	if (m_titleSelectManager->GetInformation()->GetChangeScnenJudgemnet())
	{
		//		プレイシーンに切り替える
		m_sceneManager->ChangeScene(SceneManager::SceneType::Play);
	}
}

void TitleScene::Render()
{
	//		タイトル選択マネージャーの描画処理
	m_titleSelectManager->Render();
}

void TitleScene::Finalize()
{
	m_titleSelectManager->Finalize();
}

void TitleScene::CreateView()
{
	DirectX::SimpleMath::Matrix rotation;

	//		視点方向
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);

	//		アップベクトル
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		ビュー行列を設定する
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	({ 0.0f, 0.0f, 0.0f }, target, up));
}

void TitleScene::CreateProj()
{
	//		ビュー行列を作成する
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(60.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 360.0f);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);
}
