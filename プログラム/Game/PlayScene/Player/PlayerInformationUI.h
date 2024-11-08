/*
* @file		PlayerInformationUI.h
* @brief	UI用判定用プレイヤーの情報
* @author	Morita
* @date		2024/05/16
*/

#pragma once

#include "pch.h"

class PlayerInformationUI
{
public:
	//		コンストラクタ
	PlayerInformationUI()
	:
		m_dashJudgement(false),
		m_dashCoolTime(0.0f),
		m_dashMaxTime(0.0f)
	{};

	//		デストラクタ
	~PlayerInformationUI() {};

private:

	//		ダッシュしているかどうか
	bool m_dashJudgement;

	//		ダッシュのクールタイム時間を受け取る
	float m_dashCoolTime;

	//		ダッシュのクールタイム最大時間
	float m_dashMaxTime;

public:
};


