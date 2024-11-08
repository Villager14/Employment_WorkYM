/*
* @file		MenuCommonProcess.h
* @brief	メニューの共通処理
* @author	Morita
* @date		2024/08/05
*/

#pragma once

#include "MenuInformation.h"

class MenuCommonProcess
{
public:

	//		コンストラクタ
	MenuCommonProcess(MenuInformation* menuInformation);

	//		デストラクタ
	~MenuCommonProcess();

	//		メニューのESCボタンで閉じる処理
	bool MenuEscCloseProcess();


	/*
	*	四角の当たり判定
	* 
	*	@param	(min)	最小値
	*	@param	(max)	最大値
	*	@return true : 当たっている false : 当たっていない
	*/
	bool BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);

	/*
	*	選択したかどうか
	*
	*	@param	(type)	選択しないメニューの種類
	*/
	bool ButtonCollider(MenuInformation::MenuType type);

	/*
	*	スライダーの処理
	*
	*	@param	(type)	種類
	*/
	void SlideProcess(AboveUI::UIType type);

	//		マウスポインタの処理
	void MousePointa();

private:

	//		メニューの情報
	MenuInformation* m_information;
};