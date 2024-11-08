/*
* @file		AnimationCommonProcess.h
* @brief	アニメーションの共通処理
* @author	Morita
* @date		2024/08/25
*/

#pragma once

#include "../Bones/ModelBones.h"

#include "../Bones/BonInformation.h"

class AnimationManager;

class AnimationCommonProcess
{
public:

	//		コンストラクタ
	AnimationCommonProcess(AnimationManager* animationManager);

	//		デストラクタ
	~AnimationCommonProcess();

	/*
	*	アニメーションの動き
	* 
	*	@param	(type)				移動させるボーン
	*	@param	(bonesInformation)	ボーンの情報
	*	@param	(firstVal)			初期の値
	*	@param	(endVal)			最終の値
	*	@param	(transrationSPeed)	遷移の速度
	*/
	void AnimationMovement(BonsType type,
		std::vector<PlayerBonsInformation>* bonesInformation,
		DirectX::SimpleMath::Quaternion firstVal,
		DirectX::SimpleMath::Quaternion endVal,
		float transrationSpeed);

	/*
	*	下半身の値を遷移後の値にする
	* 
	*	@param	(bonesInformation)	ボーンの情報
	*	@param	(transrationSpeed)	遷移速度
	*/
	void AnimationLegInitialValue(
		std::vector<PlayerBonsInformation>* bonesInformation,
		float transrationSpeed);

	//		着地処理
	void Landing(float height);

private:

	//		アニメーションマネージャー
	AnimationManager* m_animationManager;
};
