/*
* 
* @file		CommonEnemyBullet.h
* @brief	一般的な敵の弾
* @author	Morita
* @date		2024/05/06
*/

#pragma once



class CommonEnemyBullet
{
public:

	//		コンストラクタ
	CommonEnemyBullet();

	//		デストラクタ
	~CommonEnemyBullet();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update(float timeSpeed);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	//		発射しているかどうか
	bool m_firingJudgement;

	//		発射座標
	DirectX::SimpleMath::Vector3 m_position;

	//		移動方向
	DirectX::SimpleMath::Vector3 m_velocity;

	//		経過時間
	float m_elapsedTime;

	//		モデル
	std::unique_ptr<DirectX::Model> m_model;

public:

	/*
	*	発射しているかどうか受け取る
	* 
	*	@return true : 発射している false : 発射していない
	*/
	bool GetFiringJudgement() { return m_firingJudgement; }

	/*
	*	発射しているかどうかを設定する
	* 
	*	@param	(judgement)	true : 発射している false : 発射していない
	*/
	void SetFiringJudgement(bool judgement) { m_firingJudgement = judgement; }

	/*
	*	弾の情報を設定する
	*	
	*	@param	(position)	発射座標
	*	@param	(velocity)	発射方向
	*/
	void SetBulletInformation(const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& velicity)
	{
		m_position = position;
		m_velocity = velicity;
		m_velocity.Normalize();
	}

	/*
	*	座標を受け取る
	* 
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
};