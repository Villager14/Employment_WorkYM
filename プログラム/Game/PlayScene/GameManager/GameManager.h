/*
* @file		GameManager.h
* @brief	ゲームマネージャー
* @author	Morita
* @date		2024/05/22
*/

#pragma once

class GameManager
{
public:

	GameManager();

	~GameManager();

	void Initialize();

	void Update();

	void Finalize();
public:

	enum Flag
	{
		None = 0b00000000,
		GameStart			= 1 << 0,		//		ゲームを開始するか
		DeathJudgement		= 1 << 1,		//		死亡しているか判断する
		RevivalJudgement	= 1 << 2,		//		復活しているか判断する
		GoalJudgement		= 1 << 3,		//		ゴールしているか判断する
		EndJudgement		= 1 << 4,		//		終了しているか判断する
		NextScene			= 1 << 5,		//		次のシーンに行くか判断する
		DamageObjectHit		= 1 << 6,		//		ダメージオブジェクトに当たっているかどうか
		FallDead			= 1 << 7,		//		落下死しているかどうか
		DashJudgement		= 1 << 8,		//		ダッシュをしているかどうか
		StartLimitView		= 1 << 9,		//		開始時のリミット描画
		TimeLimitJudgement  = 1 << 10,		//		タイムリミットかどうか
	};

public:

	//		背景色
	const DirectX::XMVECTORF32 BACK_GROUND_COLOR = DirectX::Colors::Black;

private:

	//		時間
	float m_time;

	//		死亡回数
	int m_deathCount;

	//		ゲームの速度
	float m_gameSpeed;

	//		フラグ
	int m_flag;

	//		リミット時間
	float m_limitTime;

public:

	/*
	*	フラグが立っているか
	* 
	*	@param	(flag)	確認したいフラグ
	*	@return true : yes false : no
	*/
	bool FlagJudgement(Flag flag);

	/*
	*	フラグをOnにする
	* 
	*	@param	(flag)	オンにしたいフラグ
	*/
	 void TrueFlag(Flag flag);

	/*	
	*	フラグをofにする
	* 
	*	@param	(flag)	オフにしたいフラグ
	*/
	 void FalseFlag(Flag flag);

	/*
	*	時間を設定する
	* 
	*	@param	(time)	時間
	*/
	inline void SetTime(float time) { m_time = time; }

	/*
	*	時間を受け取る
	* 
	*	@return 時間
	*/
	float GetTime() { return m_time; }
	
	/*
	*	死亡回数を設定する
	* 
	*	@param	(count)	回数
	*/
	void SetDeathCount(int count) { m_deathCount = count; }

	/*
	*	死亡回数を受け取る
	* 
	*	@return 回数
	*/
	int GetDeathCount() { return m_deathCount; }

	/*
	*	ゲームの速度を設定する
	* 
	*	@return 速度
	*/
	float GetGameSpeed() { return m_gameSpeed; }

	/*
	*	ゲームの速度を設定する
	* 
	*	@param	(speed) 速度
	*/
	void SetGameSpeed(float speed) { m_gameSpeed = speed; }

	/*
	*	リミットタイムを設定する
	* 
	*	@param	(time)	時間
	*/
	void SetLimitTime(float time) { m_limitTime = time; }

	/*
	*	リミットタイムを受け取る
	* 
	*	@return 時間
	*/
	float GetLimitTime() { return m_limitTime; }
};