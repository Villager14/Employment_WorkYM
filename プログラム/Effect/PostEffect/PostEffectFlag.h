/*
* @file		PostEffectFlag.h
* @brief	ポストエフェクトマネージャー
* @author	Morita
* @date		2024/10/01
*/

#pragma once

#include "pch.h"

class PostEffectFlag
{
public:

	enum Flag
	{
		None		= 0b00000000000,
		Normal		= 0b00000000001,		//		通常描画
		BloomDepth  = 0b00000000010,		//		ブルーム深度
		Bloom		= 0b00000000100,		//		ブルーム
		Fog			= 0b00000001000,		//		フォグの処理
		AlphaDepth  = 0b00000010000,		//		アルファ深度処理
		Alpha		= 0b00000100000,		//		アルファの処理
		UI			= 0b00001000000,		//		UIの描画
		Color		= 0b00010000000,		//		画面の色変更
		UIBack		= 0b00100000000,		//		UIの後描画
		Glitch		= 0b01000000000,		//		グリッチノイズ
		Fade		= 0b10000000000,		//		フェード
	};

public:

	//		コンストラクタ
	PostEffectFlag()
	:
	m_flag(Flag::None)
	{};

	//		デストラクタ
	~PostEffectFlag() {};

private:

	//		フラグ
	int m_flag;

public:

	/*
	*	フラグを受け取る
	* 
	*	@return フラグ
	*/
	int GetFlag() { return m_flag; }

	/*
	*	フラグが立っているか
	*
	*	@param	(flag)	確認したいフラグ
	*	@return true : yes false : no
	*/
	bool FlagJudgement(Flag flag)
	{
		//		両方のビットが１の場合
		if (m_flag & flag) return true;

		return false;
	}

	/*
	*	フラグをOnにする
	*
	*	@param	(flag)	オンにしたいフラグ
	*/
	void TrueFlag(Flag flag)
	{
		m_flag |= flag;
	}

	/*
	*	フラグをofにする
	*
	*	@param	(flag)	オフにしたいフラグ
	*/
	void FalseFlag(Flag flag)
	{
		//		フラグがオンの時はオフにする
		m_flag &= ~flag;
	}
};