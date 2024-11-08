/*
* @file		CommonEnemyStay.h
* @brief	一般的な敵待機状態
* @author	Morita
* @date		2024/05/01
*/

#pragma once

#include "../ICommonEnemy.h"

class CommonEnemy;

class CommonEnemyStay : public ICommonEnemy
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(commonEnemy)	状態管理クラスのポインタ
	*/
	CommonEnemyStay(CommonEnemy* commonEnemy);

	//		デストラクタ
	~CommonEnemyStay();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:
	//		状態管理クラスのポインタ
	CommonEnemy* m_commonEnemy;

	
};