/*
* @file		ResultScene.h
* @brief	リザルトシーン
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultScene.h"

ResultScene::ResultScene(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager),
	m_score(0.0f)
{
	//		リザルトマネージャーの生成
	m_resultManager = std::make_unique<ResultManager>();
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	float time = static_cast<float>(m_sceneManager->GetClearTime());

	float deth = static_cast<float>(m_sceneManager->GetDeathCount());

	float maxTime = static_cast<float>(m_sceneManager->GetMaxTime());
	
	float score = 0.0f;

	if (deth == 0)
	{
		score = 1000.0f;
	}
	else if (deth < 3)
	{
		score = 700.0f;
	}
	else
	{
		score = 200.0f;
	}

	score *= Library::Lerp(3.0f, 1.0f, time / maxTime);

	m_score = score;

	//		リザルトマネージャーの初期化
	m_resultManager->Initialize(static_cast<int>(m_score), m_sceneManager->GetClearTime(),
								m_sceneManager->GetDeathCount());

	//		プロジェクション行列の作製
	CreateProj();
	//		ビュー行列の作製
	CreateView();

	//		BGMを再生する
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::ResultScene);
}

void ResultScene::Update()
{
	//		背景の更新
	m_resultManager->BackGroundUpdate();

	//		メニューを開いている場合処理をしない
	if (m_sceneManager->GetMenuManager()->GetInformation()->GetMenuJudgement()) return;

	//		メニューを使えるかどうか
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_resultManager->GetMenuUseJugement());

	//		リザルトマネージャーの更新処理
	m_resultManager->Update();

	if (m_resultManager->GetInformation()->GetChangeSceneJudgement())
	{
		m_sceneManager->ChangeScene(SceneManager::SceneType::Title);
	}
}

void ResultScene::Render()
{
	//		リザルトマネージャーの描画処理
	m_resultManager->Render();
}

void ResultScene::Finalize()
{
	m_resultManager->Finalize();

	m_score = 0.0f;
}

void ResultScene::CreateProj()
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

void ResultScene::CreateView()
{
	DirectX::SimpleMath::Matrix rotation;

	//		視点方向
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);

	//		アップベクトル
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		ビュー行列を設定する
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	({0.0f, 0.0f, 0.0f}, target, up));
}
