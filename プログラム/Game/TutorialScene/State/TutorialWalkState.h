/*
* @file		TutorialWalkState.h
* @brief	チュートリアル歩き
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include "../ITutorialManager.h"

class TutorialManager;

class TutorialWalkState : public ITutorialManager
{
public:

	//		コンストラクタ
	TutorialWalkState(TutorialManager* tutorialManager);

	//		デストラクタ
	~TutorialWalkState();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:

	//		チュートリアルマネージャのインスタンスのポインタ
	TutorialManager* m_tutorialManager;


};
