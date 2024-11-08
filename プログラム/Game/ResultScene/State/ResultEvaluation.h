/*
* @file		ResultEvaluation.h
* @brief	リザルト評価処理
* @author	Morita
* @date		2024/06/28
*/

#pragma once

#include "../ResultManager.h"

#include "../IResultManager.h"

class ResultManager;

class ResultEvaluation : public IResultManager
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(resultManager)	リザルトマネージャーのインスタンス
	*/
	ResultEvaluation(ResultManager* resultManager);
	
	//		デストラクタ
	~ResultEvaluation();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	float Easing(float time);

private:

	//		リザルトマネージャー
	ResultManager* m_resultManager;

	//		時間
	float m_time;
};