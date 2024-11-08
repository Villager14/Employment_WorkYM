/*
* @file		MenuInformation.h
* @brief	メニューの情報
* @author	Morita
* @date		2024/07/12
*/

#pragma once

#include "pch.h"

#include "Library/Shader/StandardShader.h"
#include "Effect/UI/Menu/AboveUI/AboveUI.h"
#include "Effect/UI/Menu/Slider/Slider.h"
#include "Effect/UI/Menu/MenuSelect/MenuSelect.h"
#include "Effect/UI/Menu/FrameWalkUI/FrameWalkUI.h"

class MenuInformation
{
public:
	//		コンストラクタ
	MenuInformation()
		:
		m_aboveUI{ nullptr },
		m_standardShader{ nullptr },
		m_menuSelect{ nullptr },
		m_slider{ nullptr },
		m_frameWalkUI{ nullptr },
		m_viewAngle(70.0f),
		m_cameraSpeed(5.0f),
		m_menuUseJudgement(false),
		m_menuJudgement(false),
		m_menuTransitionJudgement(false),
		m_rangeUI(AboveUI::UIType::Empty),
		m_slideUIType(AboveUI::UIType::Empty),
		m_selectUI(MenuInformation::MenuType::Empty),
		m_initializeProcessJudgement(true)
	{}

	//		デストラクタ
	~MenuInformation() {}


public:

	enum UIType
	{
		Bar1,
		Bar2,
		BackGround,
		AudioSelect,
		OptionSelect,
		GamePlaySelect,
		Slide,
		AudioTitle,
		MousePointa,
	};

	enum MenuType
	{
		Start,
		Audio,
		Option,
		GamePlay,
		Close,

		Empty,
	};

public:

	/*
	*	初期化
	* 
	*	@param	(standardShader)	スタンダードシェーダーのインスタンスのポインタ
	*	@param	(aboveUI)			上昇シェーダーのインスタンスのポインタ
	*	@param	(slider)			スライダーシェーダーのインスタンスのポインタ
	*	@param	(menuSelect)		メニュー選択シェーダーのインスタンスのポインタ
	*	@param	(frameWalkUI)		フレームワークシェーダーのインスタンスのポインタ
	*/
	void Initialzie(StandardShader<MenuInformation::UIType>* standardShader,
		AboveUI* aboveUI,
		Slider* slider,
		MenuSelect* menuSelect, FrameWalkUI* frameWalk)
	{
		m_standardShader = standardShader;
		m_aboveUI = aboveUI;
		m_slider = slider;
		m_menuSelect = menuSelect;
		m_frameWalkUI = frameWalk;
	}
	


public:
	//		音楽タイトルの座標
	const DirectX::SimpleMath::Vector2 AUDIO_TITLE_POSITION_MIN = { 119.0f, 106.0f };
	const DirectX::SimpleMath::Vector2 AUDIO_TITLE_POSITION_MAX = { 400.0f, 210.0f };

	//		オプションタイトルの座標
	const DirectX::SimpleMath::Vector2 OPTION_TITLE_POSITION_MIN = { 119.0f, 227.0f };
	const DirectX::SimpleMath::Vector2 OPTION_TITLE_POSITION_MAX = { 400.0f, 329.0f };

	//		終了タイトルの座標
	const DirectX::SimpleMath::Vector2 GAMEPLAY_TITLE_POSITION_MIN = { 119.0f, 347.0f };
	const DirectX::SimpleMath::Vector2 GAMEPLAY_TITLE_POSITION_MAX = { 400.0f, 452.0f };

	//		遷移速度
	const float TRANSITION_SPEED = 3.0f;

	//		メニューの速度
	const float MENU_SPEED = 2.0f;

	//		つまみの大きさ
	const DirectX::SimpleMath::Vector2 KNOB_LENGTH = { 15.0f, 33.0f };
private:

	//		スタンダードシェーダー
	StandardShader<UIType>* m_standardShader;

	//		上昇UI
	AboveUI* m_aboveUI;

	//		スライダーUI
	Slider* m_slider;

	//		メニューの選択
	MenuSelect* m_menuSelect;

	//		フレームワーク
	FrameWalkUI* m_frameWalkUI;

	//		選択UI
	AboveUI::UIType m_rangeUI;

	//		次の状態を設定する
	MenuInformation::MenuType m_selectUI;

	//		スライダーを使っているUIの種類
	AboveUI::UIType m_slideUIType;

	//		視野角
	float m_viewAngle;

	//		カメラの速度
	float m_cameraSpeed;

	//		メニューを使用することができるか
	bool m_menuUseJudgement;

	//		メニューを使っているか
	bool m_menuJudgement;

	//		メニューが遷移中かどうか
	bool m_menuTransitionJudgement;

	//		初期化処理をするかどうか
	bool m_initializeProcessJudgement;

public:

	/*
	*	スタンダードシェーダーを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader; }

	/*
	*	上昇UIを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	AboveUI* GetAboveUI() { return m_aboveUI; }

	/*
	*	スライダーUIを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	Slider* GetSlider() { return m_slider; }

	/*
	*	メニュー選択UIを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	MenuSelect* GetMenuSelect() { return m_menuSelect; }

	/*
	*	フレームワークUIを受け取る
	* 
	*	@return フレームワークのポインタ
	*/
	FrameWalkUI* GetFramWalkUI() { return m_frameWalkUI; }

	/*
	*	視野角を設定する
	* 
	*	@param	(angle)	角度
	*/
	void SetViewAngle(float angle) { m_viewAngle = angle; }

	/*
	*	視野角を受け取る
	* 
	*	@return 角度
	*/
	float GetViewAngle() { return m_viewAngle; }

	/*
	*	カメラの速度を設定する
	* 
	*	@param	(speed)	速度
	*/
	void SetCameraSpeed(float speed) { m_cameraSpeed = speed; }

	/*
	*	カメラ速度を受け取る
	* 
	*	@retuen	速度
	*/
	float GetCameraSpeed() { return m_cameraSpeed; }

	/*
	*	メニューを使えるかどうか判断する
	*
	*	@return true : 使える false : 使えない
	*/
	bool GetMenuUseJudgement() { return m_menuUseJudgement; }

	/*
	*	メニューを使えるかどうか設定する
	*
	*	@param	(judgement)	true : 使える false : 使えない
	*/
	void SetMenuUseJudgement(bool judgement) { m_menuUseJudgement = judgement; }

	/*
	*	メニューを使っているかどうか受け取る
	* 
	*	@returen true : 使っている　false 使っていない
	*/
	bool GetMenuJudgement() { return m_menuJudgement; }

	/*
	*	メニューを使っているかどうか設定する
	* 
	*	@param	(judgement)	true : 使っている　false 使っていない
	*/
	void SetMenuJudgement(bool judgement) { m_menuJudgement = judgement; }

	/*
	*	メニューの遷移状態かどうか受け取る
	*
	*	@returen true : 遷移状態開始　false 遷移状態終了
	*/
	bool GetMenuTransrationJudgement() { return m_menuTransitionJudgement; }

	/*
	*	メニューの遷移状態かどうか設定する
	*
	*	@returen true : 遷移状態開始　false 遷移状態終了
	*/
	void SetMenuTransrationJudgement(bool judgement) { m_menuTransitionJudgement = judgement; }

	/*
	*	初期化処理を行うかどうか受け取る
	*
	*	@return true : 行う false : 行わない
	*/
	bool GetInitializeJudgement() { return m_initializeProcessJudgement; }

	/*
	*	メニューを使えるかどうか設定する
	*
	*	@param	(judgement)	true : 行う false : 行わない
	*/
	void SetInitializeJudgement(bool judgement) { m_initializeProcessJudgement = judgement; }

	/*
	*	選択UIを受け取る
	* 
	*	@return 選択UI
	*/
	AboveUI::UIType GetRangeUI() { return m_rangeUI; }

	/*
	*	選択UIを設定する
	*
	*	@param	(type)	タイプ
	*/
	void SetRangeUI(AboveUI::UIType type) { m_rangeUI = type; };

	/*
	*	次の状態を受け取る
	*
	*	@return 状態
	*/
	MenuInformation::MenuType GetSelectUI() { return m_selectUI; }

	/*
	*	次の状態を設定する
	*
	*	@param	(type)	状態
	*/
	void SetSelectUI(MenuInformation::MenuType type) { m_selectUI = type; };

	/*
	*	スライダー選択UIを受け取る
	*
	*	@return 選択UI
	*/
	AboveUI::UIType GetSliderSelectUI() { return m_slideUIType; }

	/*
	*	スライダー選択UIを設定する
	*
	*	@param	(type)	タイプ
	*/
	void SetSliderSelectUI(AboveUI::UIType type) { m_slideUIType = type; };

};