/*
* @file		GlitchNoise.h
* @brief	グリッチノイズ
* @author	Morita
* @date		2024/10/22
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"


class GlitchNoise : public IPostEffect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(manager)	ポインタのインスタンス
	*/
	GlitchNoise(PostEffectManager* postEffectManager);

	//		デストラクタ
	~GlitchNoise();

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

	//		レンダーターゲットを作成する
	void CreateRenderTarget();

public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
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

	ConstBuffer m_constBuffer;

};