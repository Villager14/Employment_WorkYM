/*
* @file		UIRender.h
* @brief	UIシェーダーの描画
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "ConstBufferManager.h"

enum class CENTER_POINT
{
	ABOVE_LEFT,
	ABOVE_CENTER,
	ABOVE_RIGHT,

	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,

	UNDER_LEFT,
	UNDER_CENTER,
	UNDER_RIGHT,
};

class UIRenderManager
{
public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
	};

	//		コンストラクタ
	UIRenderManager();
	
	//		デストラクタ
	~UIRenderManager();

	//		頂点
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	/*
	*	テクスチャの読み込み
	* 
	*	@param	(path)	ファイルパス
	*/
	void LoadTexture(const wchar_t* path, int index = 0);

	/*
	*	シェーダーを作成する
	* 
	*	@param	(path)			テクスチャのパス
	*	@param	(position)		座標
	*	@param	(scale)			スケール
	*	@param	(centerPoint)	中心点
	*/
	template<typename UIType>
	void Create(
		const wchar_t* texpath,
		const wchar_t* vsPath,
		const wchar_t* gsPath,
		const wchar_t* psPath,
		const UIType& obj,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale,
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER);

	//		シェーダーの読み込み
	void LoadShader(
		const wchar_t* vsPath,
		const wchar_t* gsPath,
		const wchar_t* psPath
		);

	template<typename UIType>
	void Render(const UIType& obj);

	//		終了処理
	void Finalize();

private:

	//		バッファー
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;

	//		入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		テクスチャハンドル
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	//		ジオメトリックシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//		テクスチャ横サイズ
	int m_textureWidth;

	//		テクスチャ縦サイズ
	int m_textureHeight;

	//		スケール
	DirectX::SimpleMath::Vector2 m_scale;

	//		座標
	DirectX::SimpleMath::Vector2 m_position;

	//		回転
	DirectX::SimpleMath::Matrix m_rotationMatrix;

	//		中心点
	CENTER_POINT m_centerPoint;

	//		コンストバッファマネージャー
	std::unique_ptr<ConstBufferManager> m_constBufferManager;

	//		サンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sample;
public:

	/*
	*	回転を設定する
	*
	*	@param	(rotatonMatrix)	回転
	*/
	void SetRotationMatrix(DirectX::SimpleMath::Matrix rotatonMatrix)
	{
		m_rotationMatrix = rotatonMatrix;
	}

	DirectX::SimpleMath::Matrix GetRotationMatrix() { return m_rotationMatrix; }

	/*
	*	座標を設定する
	* 
	*	@param	(position)	座標
	*/
	void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

	/*
	*	サイズを設定する
	* 
	*	@param	(size)	サイズ
	*/
	void SetSize(DirectX::SimpleMath::Vector2 size) { m_scale = size; }

	/*
	*	センターポイントを設定する
	* 
	*	@param	(centerPoint)	中心位置
	*/
	void SetCenterPoint(CENTER_POINT centerPoint) { m_centerPoint = centerPoint; }

	void SetSampler(ID3D11SamplerState* sampler) { m_sample = sampler; }

	ConstBufferManager* GetConstBufferManager() { return m_constBufferManager.get(); }

	void SetTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, int index = 0) 
	{ 
		if (m_texture.size() <= index)
		{
			m_texture.push_back(texture);
		}
		else
		{
			m_texture[index] = texture;
		}
	};

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(int index = 0) { return m_texture[index]; }

	DirectX::SimpleMath::Vector2 GetTextureSize() 
	{ return { static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight) }; }

	void SetTextureSize(int width, int height) {m_textureWidth = width; m_textureHeight = height; }
};

template<typename UIType>
inline void UIRenderManager::Create(const wchar_t* texpath,
	const wchar_t* vsPath, const wchar_t* gsPath, const wchar_t* psPath,
	const UIType& obj, DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 scale, CENTER_POINT centerPoint)
{
	m_position = position;
	m_scale = scale;
	m_centerPoint = centerPoint;

	m_constBufferManager = std::make_unique<ConstBufferManager>();

	//		シェーダーの読み込み
	LoadShader(vsPath, gsPath, psPath);

	m_constBufferManager->CreateConstBuffer(obj);

	//		画像の読み込み
	LoadTexture(texpath);
}

template<typename UIType>
inline void UIRenderManager::Render(const UIType& obj)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto commonState = LibrarySingleton::GetInstance()->GetCommonState();

	//		画像の中心
	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(m_centerPoint)),
		DirectX::SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)),
		DirectX::SimpleMath::Vector2(1.0f,0.0f))
	};

	m_constBufferManager->UpdateBuffer(obj);

	//		コンストバッファのバインド
	m_constBufferManager->BindBuffer();

	//		画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { commonState->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//ID3D11SamplerState* sampler[1] = { m_sample.Get()};
	//context->PSSetSamplers(0, 1, sampler);

	//		半透明描画指定
	ID3D11BlendState* blendestate = commonState->NonPremultiplied();

	//		透明判定処理
	context->OMSetBlendState(blendestate, nullptr, 0xFFFFFFFF);

	//		深度バッファに書き込み参照
	context->OMSetDepthStencilState(commonState->DepthDefault(), 0);

	//		カリングは左回り
	context->RSSetState(commonState->CullNone());

	//		シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	for (int i = 0, max = static_cast<int>(m_texture.size());
		 i < max; ++i)
	{
		//		ピクセルシェーダにテクスチャを登録する
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//		インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//		板ポリゴンを描画
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->Begin();
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->
		Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->End();

	//		シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}
