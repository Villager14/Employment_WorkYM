/*
* @file		RespawnPointRead.h
* @brief	リスポーンポイントの読み込み処理
* @author	Morita
* @date		2024/10/03
*/

#pragma once

#include <string>

class RespawnPointRead
{
public:

	//		コンストラクタ
	RespawnPointRead();

	//		デストラクタ
	~RespawnPointRead();

	//		初期化処理
	void ReadProcess(int stageNumber);

	/*
	*	パラメーターを設定する
	*
	*	@param	(val)		値
	*	@param	(index)		要素数
	*	@param	(position)	座標
	*	@param	(length)	長さ
	*/
	void SetParameter(std::string val, int index, DirectX::SimpleMath::Vector3* position,
		float* length, float* direction);

	//		終了処理
	void Finalize();

private:

	//		座標
	std::vector<DirectX::SimpleMath::Vector3> m_position;

	//		長さ
	std::vector<float> m_length;

	//		向き
	std::vector<float> m_direction;

public:

	/*
	*	リスポーン座標を受け取る
	*
	*	@return 座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetPosition() { return m_position; }

	/*
	*	距離を受け取る
	*
	*	@return 距離
	*/
	const std::vector<float>& GetLength() { return m_length; }

	/*
	*	方向を受け取る
	* 
	*	@return 角度
	*/
	const std::vector<float>& GetDirection() { return m_direction; }
};