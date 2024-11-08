/*
* @file		MenuStart.h
* @brief	メニュースタート時の処理
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class MenuStart : public IMenu
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	()
	*/
	MenuStart(MenuManager* menuManager);

	//		デストラクタ
	~MenuStart();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	//		スライダーの描画
	void SliderView(float transitionTime);

private:

	//		メニューマネージャーのインスタンスのポインタ
	MenuManager* m_menuManager;

	//		スケール
	float m_scale;

	//		移動
	float m_move;


	//		タイトルの遷移時間
	float m_transitionTitleTime;

	//		大まかなメニューの遷移時間
	float m_transitionRoughTime;

	//		設定する部分のUIの遷移時間
	float m_transitionSettingUITime;

	//		初期遷移を行うかどうか判断する
	bool m_startJudgement;
};