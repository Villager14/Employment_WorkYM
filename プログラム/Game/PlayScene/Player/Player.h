/*
* @file		Player.h
* @brief	プレイヤーの処理
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "Game/PlayScene/CollitionManager/CollitionInformation.h"

#include "Game/PlayScene/Player/PlayerInformationCollition.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "PlayerInformation.h"

#include "Library/Animation/AnimationManager.h"

#include "State/PlayerStay.h"
#include "State/PlayerWalk.h"
#include "State/PlayerCrouching.h"
#include "State/PlayerJump.h"
#include "State/PlayerSliding.h"
#include "State/PlayerDash.h"
#include "State/PlayerSlowTime.h"
#include "State/PlayerWallWalk.h"
#include "State/PlayerWire.h"
#include "State/PlayerWallJump.h"
#include "State/PlayerDeath.h"
#include "State/PlayerStart.h"
#include "State/PlayerGoal.h"
#include "State/PlayerFall.h"

#include "State/PlayerAttack.h"

#include "../ObjectManager/WireObject/WireObjectInformation.h"

#include <unordered_map>

#include "PlayerCommonProcessing.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class Player
{
public:

	//		コンストラクタ
	Player(GameManager* gameManager);

	//		デストラクタ
	~Player();

	//		初期化処理
	void Initialize();

	//		生成処理
	void Generation();

	//		更新処理
	void Update(PlayerCameraInformation* cameraInformation);

	//		メッシュの更新
	void MeshUpdate();

	//		アニメーションの更新
	void AnimationUpdate();

	//		モデルの描画
	void ModelRender(PostEffectFlag::Flag flag);

	//		デバック描画
	void DebugRender();

	//		終了処理
	void Finalize();

	//		死亡したか判断する
	void DeathJudgement();

public:

	//		プレイヤーの状態
	enum PlayerState
	{
		Stay,
		Walk,
		Crouching,
		Jump,
		Sliding,
		Dash,
		WallWalk,
		WallJump,
		Wire,
		Death,
		Start,
		Goal,
		Fall,
	};

public:

	/*
	*	状態を変更する
	*
	*	@param	(state)	状態
	*/
	void ChangeState(PlayerState state);

	//		ワイヤーの状態遷移
	void ChangeWireState(int index);

private:

	//		プレイヤーの状態の情報
	std::unordered_map<PlayerState, std::unique_ptr<IPlayer>> m_stateInformation;

	//		現在の状態
	PlayerState m_playerState;

	//		現在の状態
	IPlayer* m_state;

	//		プレイヤーのアニメーションの処理
	std::unique_ptr<AnimationManager> m_playerAnimation;

	//		当たり判定の情報
	CollitionInformation* m_collitionInformation;

	//		当たり判定用プレイヤーの情報
	std::unique_ptr<PlayerInformationCollition> m_playerInformationCollition;

	//		プレイヤーの攻撃
	std::unique_ptr<PlayerAttack> m_playerAttack;

	//		プレイヤーの情報
	std::unique_ptr<PlayerInformation> m_information;

	//		プレイヤーの共通処理
	std::unique_ptr<PlayerCommonProcessing> m_commonProcessing;

	//		カメラの情報
	PlayerCameraInformation* m_cameraInformation;

	//		ゲームマネージャー
	GameManager* m_gameManager;

	//		ワイヤーの情報
	std::vector<WireObjectInformation> *m_wireInformation;

	//		メニューを使えるかどうか
	bool m_menuUseJudgement;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

public:

	/*
	*	ゲームマネージャーを受け取る
	* 
	*	@return ゲームマネージャーのインスタンスのポインタ
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	プレイヤーカメラの情報
	* 
	*	@return カメラの情報
	*/
	PlayerCameraInformation* GetCameraInformation() { return m_cameraInformation; }

	/*
	*	プレイヤーカメラの情報
	*
	*	@return カメラの情報
	*/
	void SetCameraInformation(PlayerCameraInformation* information) { m_cameraInformation = information; }


	/*
	*	当たり判定の情報を受け取る
	* 
	*	@param	(collitionInformation)	インスタンスのポインタ
	*/
	void SetCollitionInformation(CollitionInformation* collitionInformation)
							{ m_collitionInformation = collitionInformation; }

	/*
	*	当たり判定の情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	CollitionInformation* GetCollitionInformation() { return m_collitionInformation; }

	/*
	*	プレイヤーの共通処理
	* 
	*	@return インスタ巣のポンタ
	*/
	PlayerCommonProcessing* GetCommonProcessing() { return m_commonProcessing.get(); }

	/*
	*	当たり判定用情報を設定する
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerInformationCollition* GetPlayerInformationCollition() { return m_playerInformationCollition.get(); }

	/*
	*	プレイヤーの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerInformation* GetInformation() { return m_information.get(); }

	/*
	*	プレイヤーアニメーションのインスタンスのポインタ
	* 
	*	@return ポインタのインスタンス
	*/
	AnimationManager* GetAnimation() { return m_playerAnimation.get(); }

	/*
	*	ワイヤーの情報を設定する
	* 
	*	@param	(wireInformation)	ワイヤーの情報
	*/
	void SetWireInformation(std::vector<WireObjectInformation>* wireInformation) { m_wireInformation = wireInformation; }

	/*
	*	ワイヤー情報を受け取る
	* 
	*	@return ワイヤーの情報
	*/
	std::vector<WireObjectInformation>* GetWireObjectInformation() { return m_wireInformation; }

	/*
	*	メニューを使うことができるかどうか受け取る
	*	
	*	return true : 使うことができる　false : 使うことができない
	*/
	bool GetMenuUseJugement() { return m_menuUseJudgement; }

	/*
	*	メニューを使うことができるかどうか設定する
	*
	*	@param	(judgement) true : 使うことができる　false : 使うことができない
	*/
	void SetMenuUiseJudgement(bool judgement) { m_menuUseJudgement = judgement; }
 }; 
