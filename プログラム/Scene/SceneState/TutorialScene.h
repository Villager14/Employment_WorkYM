/*
* @file		TutorialScene.h
* @brief	タイトルシーン
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include "Scene/IScene.h"

#include "Game/TutorialScene/TutorialManager.h"

class SceneManager;

class TutorialScene : public IScene
{
public:

	//		コンストラクタ
	TutorialScene(SceneManager* sceneManager);

	//		デストラクタ
	~TutorialScene();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:

	//		チュートリアルマネージャ
	std::unique_ptr<TutorialManager> m_tutorialManager;

};