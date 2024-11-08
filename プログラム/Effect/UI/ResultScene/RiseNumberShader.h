/*
* @file		ResultManager.h
* @brief	上昇番号シェーダー
* @author	Morita
* @date		2024/07/05
*/

#pragma once

#include <unordered_map>

#include "Library/Shader/UIRenderManager.h"

class RiseNumberShader
{
public:

	//		コンストラクタ
	RiseNumberShader();

	//		デストラクタ
	~RiseNumberShader();

	//		初期化処理
	void Initialize(int dethCount, int clearTime, int score);

	//		描画処理
	void Render(float time);

	//		終了処理
	void Finalize();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 number;
		DirectX::SimpleMath::Vector4 time;
	};

	//		数字の種類
	enum NumberType
	{
		DethCount1,		//		死亡１
		DethCount2,		//		死亡２
		DethCount3,		//		死亡３
		ClearCount1,	//		クリア時間1
		ClearCount2,	//		クリア時間2
		ClearCount3,	//		クリア時間3
		ClearCount4,	//		クリア時間4
		Score1,			//		スコア1
		Score2,			//		スコア2
		Score3,			//		スコア3
		Score4,			//		スコア4
	};

	//		数字の情報
	struct NumberInformation
	{
		DirectX::SimpleMath::Vector2 position;		//		座標
		int number = 0;								//		描画する番号
		int viewNumber = 0;							//		描画順
	};

private:

	//		死亡時の高さ
	const DirectX::SimpleMath::Vector2 DESH_POSITION = { 970.0f, 140.0f };

	//		死亡の間隔
	const float INTERVAL = 60.0f;

	//		スコアとタイムのX座標
	const float SCORE_TIME_X_POSITION = 910.0f;

	//		クリアタイムの高さ
	const float CLEAR_TIME_Y_POSITION = 250.0f;
	
	//		スコアの高さ
	const float SCORE_Y_POSITION = 360.0f;


private:

	//		UI描画マネージャー
	std::unique_ptr<UIRenderManager> m_uiRenderManager;

	//		コンストバッファ
	ConstBuffer buffer;

	//		数字の情報
	std::unordered_map<NumberType, NumberInformation> m_numberinformation;

public:

	/*
	*	数字の作製
	* 
	*	@param	(type)		 数字の種類
	*	@param	(position)	 座標
	*	@param	(viewNumber) 描画順
	*/
	void CreateNumber(NumberType type, DirectX::SimpleMath::Vector2 position,
		  int viewNumber);
};