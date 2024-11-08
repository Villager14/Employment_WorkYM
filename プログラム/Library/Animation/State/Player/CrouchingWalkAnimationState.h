/*
* @file		CrouchingWalkAnimationState.h
* @brief	しゃがみ歩きのアニメーション
* @author	Morita
* @date		2024/06/25
*/

#pragma once

#include "../../IAnimation.h"

#include "../../../Bones/BonInformation.h"

class AnimationManager;

class CrouchingWalkAnimationState : public IAnimation
{
public:

	//		コンストラクタ
	/*
	*	コンストラクタ
	* 
	*	@param	(playerBons) プレイヤーアニメーションのインスタンスのポインタ
	*/
	CrouchingWalkAnimationState(AnimationManager* PlayerAnimation);
	
	//		デストラクタ
	~CrouchingWalkAnimationState();

	//		初期化処理
	void Initialize() override;

	/*
	*	更新処理
	*
	*	@param	(speed)		速度
	*	@param	(position)	座標
	*	@param	(angle)		角度
	*	@param	(height)	頭の高さ
	*/
	void Update(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height,
		std::vector<PlayerBonsInformation>* bonesInformation) override;

	//		終了処理
	void Finalize() override;

private:

	//		プレイヤーのアニメーション
	AnimationManager* m_playerAnimation;

	//		経過時間
	float m_elapsedTime;

	//		アニメーション遷移
	float m_animationTransration;
};