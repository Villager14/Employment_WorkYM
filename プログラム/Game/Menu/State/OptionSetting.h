/*
* @file		OptionSetting.h
* @brief	オプションの設定
* @author	Morita
* @date		2024/07/10
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class OptionSetting : public IMenu
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	()
	*/
	OptionSetting(MenuManager* menuManager);

	//		デストラクタ
	~OptionSetting();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:

	//		メニューマネージャーのインスタンスのポインタ
	MenuManager* m_menuManager;

	//		タイトルの遷移時間
	float m_transitionTitleTime;

	//		大まかなメニューの遷移時間
	float m_transitionRoughTime;

	//		設定する部分のUIの遷移時間
	float m_transitionSettingUITime;

	//		初期遷移を行うかどうか判断する
	bool m_startJudgement;

	//		終了遷移を行うかどうか判断する
	bool m_endJudgement;

	//		閉めるかどうか
	bool m_menuCloseJudgement;

};