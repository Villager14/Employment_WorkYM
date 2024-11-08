/*
* @file		TitleSelectManager.h
* @brief	タイトルの選択マネージャー
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include <unordered_map>

#include "ITitleSelect.h"

#include "Effect/UI/TitleScene/BackGroundMove.h"

#include "Library/Shader/StandardShader.h"

#include "Library/Shader/UIRenderManager.h"

#include "Game/Menu/MenuInformation.h"

#include "TitleInformation.h"

#include "TitleCommonProcess.h"

#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"

#include "Library/Animation/AnimationManager.h"

class TitleUIManager;

class TitleSelectManager
{
public:

	//		コンストラクタ
	TitleSelectManager();

	//		デストラクタ
	~TitleSelectManager();

	//		初期化処理
	void Initialize();

	//		生成
	void Generation();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		キー入力
	void InputKey();

	//		スタンダードシェーダーの作製
	void CreateStandardShader();

	/*
	*	状態を変更する
	*
	*	@param	(state)	状態
	*/
	void ChangeState(TitleInformation::State state);

private:

	//		選択
	ITitleSelect* m_iState;

	//		現在の状態
	TitleInformation::State m_state;

	//		メニューの情報
	MenuInformation* m_menuInformation;

	//		情報
	std::unique_ptr<TitleInformation> m_information;

	//		背景移動処理
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		タイトルUIマネージャー
	std::unique_ptr<StandardShader<TitleInformation::TitleUIType>> m_standardShader;

	//		フェード描画
	std::unique_ptr<UIRenderManager> m_fade;

	//		共通処理
	std::unique_ptr<TitleCommonProcess> m_commonProcess;

	//		スクリーンエフェクトマネージャー
	std::unique_ptr<ScreenEffectManager> m_screenEffectManager;

	//		プレイヤーアニメーション
	std::unique_ptr<AnimationManager> m_playerAnimation;

public:

	/*
	*	タイトルの情報を受け取る
	* 
	*	@return	インスタンスのポインタ
	*/
	TitleInformation* GetInformation() { return m_information.get(); }

	/*
	*	メニューの情報を設定する
	* 
	*	@param	(information)	カメラのインスタンスのポインタ
	*/
	void SetMenuInformation(MenuInformation* information) { m_menuInformation = information; }

	/*
	*	メニューの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	MenuInformation* GetMenuInformation() { return m_menuInformation; }

	/*
	*	タイトル共通処理を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	TitleCommonProcess* GetCommonProcess() { return m_commonProcess.get(); }

	AnimationManager* GetAnimation() { return m_playerAnimation.get(); }

};