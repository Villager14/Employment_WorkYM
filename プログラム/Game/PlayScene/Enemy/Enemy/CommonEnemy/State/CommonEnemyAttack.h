/*
* @file		CommonEnemyAttack.h
* @brief	一般的な敵の攻撃
* @author	Morita
* @date		2024/05/06
*/

#pragma once

#include "../ICommonEnemy.h"

class CommonEnemy;

class CommonEnemyAttack : public ICommonEnemy
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(commonEnemy)	状態管理クラスのポインタ
	*/
	CommonEnemyAttack(CommonEnemy* commonEnemy);

	//		デストラクタ
	~CommonEnemyAttack();

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

	//		攻撃時間
	float m_attackTime;
};