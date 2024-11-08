/*
* @file		Transparency.h
* @brief	アルファエフェクトの処理
* @author	Morita
* @date		2024/10/16
*/


#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"

class EffectRender : public IPostEffect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(manager)	ポインタのインスタンス
	*/
	EffectRender(PostEffectManager* postEffectManager);

	//		デストラクタ
	~EffectRender();

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

	//		シェーダーの読み込み
	void LoadShader(
		const wchar_t* vsPath,
		const wchar_t* psPath
	);

	void SetObjectShader(PostEffectObjectShader* shader);

	//		レンダーターゲットの作製
	void CreateRenderTarget();

public:
	struct FogShaderConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
	};

private:

	//		ポストエフェクトマネージャーのポインタのインスタンス
	PostEffectManager* m_postEffectManager;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		レンダーテクスチャ(透明)
	std::unique_ptr<DX::RenderTexture> m_transparencyRenderTexture;

	//		テクスチャ
	ID3D11ShaderResourceView* m_texture;

	//		透明テクスチャ
	ID3D11ShaderResourceView* m_alphaEffectTexture;

	//		透明レンダーマネージャー
	std::unique_ptr<UIRenderManager> m_transparencyRenderManager;

	//		フォグシェーダー定数バッファ
	FogShaderConstBuffer m_fogShaderConstBuffer;

	//		オブジェクトに対するシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_objectShader;
};