/*
* @file		TransparencyDepth.h
* @brief	透明処理の深度処理
* @author	Morita
* @date		2024/10/18
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../IPostEffect.h"

class EffectDepthRender : public IPostEffect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(posteffectManager)	ポストエフェクトマネージャーのインスタンスのポインタ
	*/
	EffectDepthRender(PostEffectManager* postEffectManager);

	//		デストラクタ
	~EffectDepthRender();

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
	ID3D11ShaderResourceView* GetTexture() override { return m_texture; };

	//		深度作成
	void CreateDepth();

	//		レンダーターゲットの作製
	void CreateRenderTarget();

public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
		DirectX::SimpleMath::Vector4 backColor;				//		背景色
		DirectX::SimpleMath::Vector4 drawingDistance;		//		オブジェクトの距離
	};

private:
	//		コンストバッファ
	ConstBuffer m_constBuffer;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_depthRenderTexture;

	//		深度の描画
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	//		テクスチャ
	ID3D11ShaderResourceView* m_texture;

	//		ポストエフェクトマネージャー
	PostEffectManager* m_postEffectManager;

	//		深度ステンシル
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	//		深度リソース
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_depthSRV;

	//		深度テクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthTexture;
};
