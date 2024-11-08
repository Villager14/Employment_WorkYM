/*
* @file		Bloom.h
* @brief	ブルームの処理
* @author	Morita
* @date		2024/10/01
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

#include "../../PostEffectManager.h"

#include "../../IPostEffect.h"

class Bloom : public IPostEffect
{
public:

	//		コンストラクタ
	Bloom(PostEffectManager* postEffectManager);

	//		デストラクタ
	~Bloom();

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

	//		深度作成
	void CreateDepth();

	//		レンダーターゲットの作製
	void CreateRenderTarget();

public:

	//		コンストバッファ
	struct LuminanceConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
	};

	struct SyntheticBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;					//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;				//		回転量
		DirectX::XMVECTORF32 backcolor = DirectX::Colors::Black;	//		背景色
	};

private:

	//		深度バッファ
	ID3D11DepthStencilView* m_depthNormalStencil;

	//		輝度コンストバッファ
	LuminanceConstBuffer m_luminanceConstBuffer;

	//		合成コンストバッファ
	SyntheticBuffer m_synthticBuffer;

	//		輝度シェーダー
	std::unique_ptr<UIRenderManager> m_luminanceShader;

	//		合成処理シェーダー
	std::unique_ptr<UIRenderManager> m_syntheticShader;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;
	//		輝度レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_luminanceRenderTexture;
	//		ぼかしレンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_gradationRenderTexture;
	//		合成レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_syntheticRenderTexture;
	//		最終レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_rastRenderTexutre;

	//		ポストエフェクトマネージャー
	PostEffectManager* m_postEffectManager;

	//		シェーダーリソース
	ID3D11ShaderResourceView* m_sceneTexture;

	//		輝度テクスチャ
	ID3D11ShaderResourceView* m_luminanceTexture;

	//		ぼかしテクスチャ
	ID3D11ShaderResourceView* m_gradationTexture;

	//		合成テクスチャ
	ID3D11ShaderResourceView* m_syntheticTexture;

	//		最終テクスチャ
	ID3D11ShaderResourceView* m_rastTexutre;

	//		ブルーム処理を行わないオブジェクトに対するピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_bloomUnaffectedpixelShader;



	//		深度ステンシル
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	//		深度リソース
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_depthSRV;

	//		深度テクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthTexture;
};

