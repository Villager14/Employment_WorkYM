/*
* @file		TitleScene.h
* @brief	タイトルシーン
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/TitleScene/TitleSelectManager.h"

class SceneManager;

class TitleScene : public IScene
{
public:

	//		コンストラクタ
	TitleScene(SceneManager* sceneManager);

	//		デストラクタ
	~TitleScene();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	void CreateView();

	void CreateProj();

private:
	//		シーンマネージャーのインスタンスのポインタ
	SceneManager* m_sceneManager;

	//		タイトル選択マネージャー
	std::unique_ptr<TitleSelectManager> m_titleSelectManager;
};
