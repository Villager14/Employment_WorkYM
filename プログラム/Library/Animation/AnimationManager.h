/*
* @file		AnimationManager.h
* @brief	アニメーションマネージャー
* @author	Morita
* @date		2024/08/25
*/


#pragma once

#include "../Bones/BonInformation.h"

#include "../Bones/ModelBones.h"

#include "IAnimation.h"

#include "AnimationInformation.h"

#include "AnimationCommonProcess.h"


#include "State/Player/AttackAnimationState.h"
#include "State/Player/CrouchingStayAnimationState.h"
#include "State/Player/CrouchingWalkAnimationState.h"
#include "State/Player/DashAnimationState.h"
#include "State/Player/DropDeadAnimationState.h"
#include "State/Player/FallAnimationState.h"
#include "State/Player/JumpAnimationState.h"
#include "State/Player/SlidingAnimationState.h"
#include "State/Player/StartAnimationState.h"
#include "State/Player/StayAnimationState.h"
#include "State/Player/UprightAnimationState.h"
#include "State/Player/WalkAnimationState.h"
#include "State/Player/WallJumpAnimationState.h"
#include "State/Player/WallWalkAnimationState.h"
#include "State/Player/WireJumpAnimationState.h"

#include "State/Enemy/HandGunStay.h"
#include "State/Enemy/HandGunStyle.h"

class AnimationManager
{
public:

	//		キャラクタータイプ
	enum CharactorType
	{
		Player,			//		プレイヤー
		CommonEnemy,	//		通常エネミー
		Result,
		Title,
	};

	enum AnimationState
	{
		Stay,
		Walk,
		CrouchingStay,
		CrouchingWalk,
		Jump,
		Sliding,
		Dash,
		WallWalk,
		WallJump,
		Wire,
		Start,
		Upright,
		Fall,
		Death,
		Attack,
		HandGunStayA,
		HandGunStyleA,
	};

public:

	//		コンストラクタ
	AnimationManager(CharactorType type);

	//		デストラクタ
	~AnimationManager();

	//		初期化処理
	void Initialize();

	//		描画処理
	void Render();

	//		更新処理
	void Execute(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle,
		float height);

	//		モデルの作製
	void CreateModel(bool createHead);

	/*
	*	モデルの読み込み
	*
	*	@param	(path)		ファイルパス
	*	@param	(effect)	エフェクトファクトリーのポインタ
	*	@param	(modelType)	モデルの種類
	*/
	void LoadModel(const wchar_t* path,
		DirectX::EffectFactory* effect);

	/*
	*	アニメーションの切り替え
	*
	*	@param	(IState)
	*/
	void ChangeState(AnimationState State);

	//		終了処理
	void Finalize();

private:

	//		ボーン
	std::unique_ptr<ModelBones> m_bons;

	//		モデル
	std::vector<std::unique_ptr<DirectX::Model>> m_model;

	//		情報クラス
	std::unique_ptr<AnimationInformation> m_information;

	//		共通処理
	std::unique_ptr<AnimationCommonProcess> m_commonProcess;

	//		キャラクタータイプ
	CharactorType m_charaType;

	//		アニメーションの状態
	IAnimation* m_istate;

	//		アニメーション
	AnimationState m_animationState;

	//		アニメーションの情報
	std::unordered_map<AnimationState, std::unique_ptr<IAnimation>> m_animaInformation;

	//		頭モデルを作成するかどうか
	bool m_createHead;
public:

	/*
	*	アニメーションの共通処理を受け取る
	* 
	*	@return 共通処理
	*/
	AnimationCommonProcess* GetCommonProcess() { return m_commonProcess.get(); }

	/*
	*	情報を受け取る
	* 
	*	@return 情報
	*/
	AnimationInformation* GetInformation() { return m_information.get(); }

	/*
	*	プレイヤーボーンを受け取る
	* 
	*	@return ボーン
	*/
	ModelBones* GetBons() { return m_bons.get(); }
};