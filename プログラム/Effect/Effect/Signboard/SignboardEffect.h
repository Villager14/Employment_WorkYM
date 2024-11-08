/*
* @file		SignboardEffect.h
* @brief	看板エフェクト
* @author	Morita
* @date		2024/10/30
*/

#pragma once

#include "Library/Shader/EffectShaderManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class EffectManager;

class SignboardEffect
{
public:

	//		コンストラクタ
	SignboardEffect(EffectManager* effectManager);

	//		デストラクタ
	~SignboardEffect();

	//		初期化処理
	void Initialzie();

	//		更新処理
	void Update();

	//		描画処理
	void Render(PostEffectFlag::Flag flag);

	//		終了処理
	void Finalize();

private:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
	};

	struct SignboardInformation
	{
		DirectX::SimpleMath::Vector3 position;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	};

	enum SignboardType
	{
		Move,
	};

	void CreateParameta(SignboardType type,
		DirectX::SimpleMath::Vector3 position,
		const wchar_t* path);

private:

	//		エフェクトシェーダーマネージャー
	std::unique_ptr<EffectShaderManager<ConstBuffer>> m_effectShaderManager;

	ConstBuffer m_constBuffer;

	//		エフェクトマネージャー
	EffectManager* m_effectManager;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	std::unordered_map<SignboardType, SignboardInformation> m_parameta;
};