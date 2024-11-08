/*
* @file		FogProcess.h
* @brief	フォグの処理
* @author	Morita
* @date		2024/10/10
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"


class FogProcess : public IPostEffect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(manager)	ポインタのインスタンス
	*/
	FogProcess(PostEffectManager* postEffectManager);

	//		デストラクタ
	~FogProcess();

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

	//		深度作成
	void CreateDepth();

	//		レンダーターゲットを作成する
	void CreateRenderTarget();
public:
	struct FogShaderConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
		DirectX::SimpleMath::Vector4 backColor;				//		背景色
		DirectX::SimpleMath::Vector4 drawingDistance;		//		オブジェクトの距離
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

	//		レンダーテクスチャ(深度)
	std::unique_ptr<DX::RenderTexture> m_depthRenderTarget;

	//		フォグテクスチャ
	ID3D11ShaderResourceView* m_fogTexture;

	//		深度の描画
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	//		フォグシェーダー定数バッファ
	FogShaderConstBuffer m_fogShaderConstBuffer;

	//		深度ステンシル
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	//		深度リソース
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_depthSRV;

	//		深度テクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthTexture;
};