/*
* @file		AnimationInformation.h
* @brief	アニメーションの情報
* @author	Morita
* @date		2024/08/25
*/

#pragma once

#include "pch.h"

class AnimationInformation
{
public:

	//		コンストラクタ
	AnimationInformation() :
		m_wireJudgement(false),
		m_landingTime(0.0f),
		m_fallJudgement(false),
		m_gunModelJudgement(false)
	{};

	//		デストラクタ
	~AnimationInformation() {};

	void Finalize()
	{
		m_wireJudgement = false;
		m_fallJudgement = false;
		m_gunModelJudgement = false;
		m_landingTime = 0.0f;
		m_world.clear();
		m_world.shrink_to_fit();
	}

private:

	//		ワイヤーフレームにするかどうか
	bool m_wireJudgement;

	//		ワールド座標
	std::vector<DirectX::SimpleMath::Matrix> m_world;

	//		落下していたかどうか
	bool m_fallJudgement;

	//		着地時間
	float m_landingTime;

	//		銃モデル
	bool m_gunModelJudgement;
public:

	/*
	*	ワイヤーフレームにするか受け取る
	*
	*	@reutrn true : フレームにする false : フレームにしない
	*/
	bool GetWireJudgement() { return m_wireJudgement; }

	/*
	*	ワイヤーフレームにするかを設定
	*
	*	@param	(judgement)	true : フレームにする false : フレームにしない
	*/
	void SetWireJudgement(bool judgement) { m_wireJudgement = judgement; }

	/*
	*	モデルのワールド行列を設定する
	*
	*	@param	(world)	行列
	*/
	void SetModelWorld(DirectX::SimpleMath::Matrix world) { m_world.push_back(world); }

	/*
	*	モデルのワールド座標を受け取る
	*
	*	@return 行列
	*/
	DirectX::SimpleMath::Matrix* GetWorld(int index) { return &m_world[index]; }

	/*
	*	落下しているか受け取る
	*
		@return true : 落下している　false : 落下していない
	*/
	bool GetFallJudgement() { return m_fallJudgement; }

	/*
	*	落下しているか設定する
	*
	*	@param	(judgement)	true : 落下している　false : 落下していない
	*/
	void SetFallJudgement(bool judgement) { m_fallJudgement = judgement; }

	/*
	*	着地時間を受け取る
	*
	*	@return 時間
	*/
	float GetLandingTime() { return m_landingTime; }

	/*
	*	着地時間を設定する
	*
	*	@param	(time)	時間
	*/
	void SetLandingTime(float time) { m_landingTime = time; }

	/*
	*	銃のモデルを使うかどうか
	* 
	*	@return true : 使う false : 使わない
	*/
	bool GetGunModelJudgement() { return m_gunModelJudgement; }

	/*
	*	銃のモデルを使わないかどうか
	* 
	*	@param	(judgement)	true : 使う false : 使わない
	*/
	void SetGunModelJudgement(bool judgement) { m_gunModelJudgement = judgement; }
};