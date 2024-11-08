/*
* @file		ResultScene.h
* @brief	リザルトシーン
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/ResultScene/ResultManager.h"

class SceneManager;

class ResultScene : public IScene
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(sceneManager)	インスタンスのポインタ	
	*/
	ResultScene(SceneManager* sceneManager);

	//		デストラクタ
	~ResultScene();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	//		プロジェクション行列を作成
	void CreateProj();

	//		ビュー行列の作製
	void CreateView();

private:
	//		シーンマネージャーのインスタンスのポインタ
	SceneManager* m_sceneManager;

	//		リザルトマネージャー
	std::unique_ptr<ResultManager> m_resultManager;

	float m_score;

};