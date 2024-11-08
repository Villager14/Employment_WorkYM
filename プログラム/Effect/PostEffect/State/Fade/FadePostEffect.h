/*
* @file		ScreenColor.h
* @brief	スクリーンの色
* @author	Morita
* @date		2024/10/21
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"


class FadePostEffect : public IPostEffect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(manager)	ポインタのインスタンス
	*/
	FadePostEffect(PostEffectManager* postEffectManager);

	//		デストラクタ
	~FadePostEffect();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		オブジェクト描画
	void ObjectRender() override;

	//		ポストエフェクト後の描画
	void PostEffectRender() override;

	//		終了処理
	void Filanize() override;

	//		テクスチャを受け取る
	ID3D11ShaderResourceView* GetTexture() override { return nullptr; };

	//		フェードの処理
	void Fade();

	//		レンダーターゲットの作製
	void CreateRenderTarget();

public:
	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		ポストエフェクトマネージャーのポインタのインスタンス
	PostEffectManager* m_postEffectManager;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		フォグテクスチャ
	ID3D11ShaderResourceView* m_colorTexture;

	//		深度の描画
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	//		フォグシェーダー定数バッファ
	ConstBuffer m_constBuffer;

	//		フェード待機時間
	float m_fadeStayTime;

	//		フェード時間
	float m_fadeTime;

	//		フェードインをするかどうか判断する
	bool m_fadeinResetJudgement;

	//		フェードアウトをするかどうか判断する
	bool m_fadeoutResetJudgement;

	//		初めのフェードインかどうか
	bool m_firstJudgement;

};