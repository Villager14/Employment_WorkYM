/*
* @file		FadeIn.h
* @brief	フェードの処理
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/UIRenderManager.h"

class FadeIn
{
public:

	FadeIn();

	~FadeIn();

	void Initialize();

	void Update(GameManager* gameManager);

	void Render();

	void Finalize();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		時間
	float m_time;

	//		待機時間
	float m_stayTime;

	//		フェードインをするかどうか判断する
	bool m_fadeinResetJudgement;

	//		フェードアウトをするかどうか判断する
	bool m_fadeoutResetJudgement;

	//		初めのフェードインかどうか
	bool m_firstJudgement;

	//		コンストバッファ
	ConstBuffer buffer;

	//		フェードの描画
	std::unique_ptr<UIRenderManager> m_fadeRender;
};
