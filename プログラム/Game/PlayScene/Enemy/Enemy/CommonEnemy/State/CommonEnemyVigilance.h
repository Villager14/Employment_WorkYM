/*
* @file		CommonEnemyVigilance.h
* @brief	一般的な敵警戒状態
* @author	Morita
* @date		2024/05/01
*/

#pragma once

#include "../ICommonEnemy.h"

class CommonEnemy;

class CommonEnemyVigilance : public ICommonEnemy
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(commonEnemy)	状態管理クラスのポインタ
	*/
	CommonEnemyVigilance(CommonEnemy* commonEnemy);

	//		デストラクタ
	~CommonEnemyVigilance();

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

	//		クールタイム
	float m_coolTime;
};