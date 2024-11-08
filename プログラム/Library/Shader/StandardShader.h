/*
* @file		StandardShader.h
* @brief	リザルトUIのマネージャー
* @author	Morita
* @date		2024/07/04
*/

#pragma once

#include "pch.h"

#include <unordered_map>

#include "Library/Shader/UIRenderManager.h"


template<typename UIType>
class StandardShader
{
public:

	/*
	*	コンストラクタ
	*
	*	@param	(titleSceneManager)	タイトルシーンマネージャーのインスタンスのポインタ
	*/
	StandardShader() {};

	//		デストラクタ
	~StandardShader() {};

	//		初期化処理
	void Initialize();

	/*
	*	UIの情報を作成する
	*
	*	@param	(path)		テクスチャのパス
	*	@param	(position)	座標
	*	@param	(size)		サイズ
	*	@param	(type)		UIの種類
	*/
	void CreateUIInformation(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size,
		UIType type);

	/*
	*	描画処理
	*
	*	@param	(type)	描画するUIの種類
	*/
	void Render(UIType type);

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;						//		座標
		DirectX::SimpleMath::Vector2 scale;							//		サイズ
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;	//		テクスチャ
		DirectX::SimpleMath::Vector2 textureSize;					//		テクスチャサイズ
	};

private:

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	//		シェーダーの情報
	std::unordered_map<UIType, UIInformation> m_shaderInformation;

public:

	/*
	*	コンストバッファを受け取る
	*
	*	@return	コンストバッファのポインタ
	*/
	ConstBuffer* GetConsutBuffer() { return &m_constBuffer; }

	/*
	*	UIの情報を受け取る
	* 
	*	@return key UIの種類 val　UIの情報
	*/
	std::unordered_map<UIType, UIInformation>* GetUIInformation() { return &m_shaderInformation; };

	/*
	*	テクスチャの情報を更新する
	* 
	*	@param	(type)		変更するUIの種類
	*	@param	(texture)	テクスチャ
	*	@param	(size)		サイズ
	*/
	void ChangeTexture(UIType type, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
					   DirectX::SimpleMath::Vector2 size);
};

template<typename UIType>
void StandardShader<UIType>::Initialize()
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(L"Resources/Texture/TitleScene/TitleRogo.png",
		L"Resources/Shader/UI/UIShader/UIShaderVS.cso",
		L"Resources/Shader/UI/UIShader/UIShaderGS.cso",
		L"Resources/Shader/UI/UIShader/UIShaderPS.cso",
		m_constBuffer,
		{ 0.0f, 0.0f , }, { 1.0f,
		1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		回転行列を送る
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ウィンドウサイズを送る
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

template<typename UIType>
void StandardShader<UIType>::CreateUIInformation(const wchar_t* path, DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 size, UIType type)
{
	UIInformation uiInformation;

	uiInformation.position = position;
	uiInformation.scale = size;
	m_shader->LoadTexture(path);
	uiInformation.texture = m_shader->GetTexture();
	uiInformation.textureSize = m_shader->GetTextureSize();

	m_shaderInformation.insert({ type, uiInformation });
}

template<typename UIType>
void StandardShader<UIType>::Render(UIType type)
{
	m_shader->SetPosition(m_shaderInformation[type].position);
	m_shader->SetSize(m_shaderInformation[type].scale);
	m_shader->SetTexture(m_shaderInformation[type].texture);
	m_shader->SetTextureSize(static_cast<int>(m_shaderInformation[type].textureSize.x),
		static_cast<int>(m_shaderInformation[type].textureSize.y));

	m_shader->Render(m_constBuffer);
}

template<typename UIType>
inline void StandardShader<UIType>::ChangeTexture(UIType type,
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
	DirectX::SimpleMath::Vector2 size)
{
	m_shaderInformation[type].texture = texture;
	m_shaderInformation[type].textureSize = size;
}
