/*
* @file		TutorialScene.cpp
* @brief	タイトルシーン
* @author	Morita
* @date		2024/09/17
*/

#include "pch.h"

#include "TutorialScene.h"

TutorialScene::TutorialScene(SceneManager* sceneManager)
{
	//		チュートリアルマネージャの生成
	m_tutorialManager = std::make_unique<TutorialManager>(sceneManager);
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Initialize()
{
	//		チュートリアルマネージャの初期化処理
	m_tutorialManager->Initialize();
}

void TutorialScene::Update()
{
	//		チュートリアルマネージャーの更新処理
	m_tutorialManager->Update();
}

void TutorialScene::Render()
{
	//		チュートリアルマネージャーの描画処理
	m_tutorialManager->Render();
}

void TutorialScene::Finalize()
{
	//		終了処理
	m_tutorialManager->Finalize();
}
