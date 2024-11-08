/*
* @file		SignboardObject.cpp
* @brief	看板オブジェクトの描画
* @author	Morita
* @date		2024/10/31
*/

#include "pch.h"

#include "SignboardObject.h"

#include <Effects.h>

SignboardObject::SignboardObject(ObjectManager* objectManager)
	:
	m_signboardModel{},
	m_objectManager(objectManager)
{
	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

SignboardObject::~SignboardObject()
{

}

void SignboardObject::Initialize(ObjectInformation information)
{
	LoadModel(information);

	//		Y軸の回転
	m_world = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(information.rotation.y));

	m_position = information.position;

	//		座標
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

	//		通常描画をするようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		ブルームを掛けるようにする
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);

	//		ブルームの深度描画は描画しない
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);

	//		フォグの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	//		アルファの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
}

void SignboardObject::Update()
{
}

void SignboardObject::Render(PostEffectFlag::Flag flag,
		PostEffectObjectShader* postEffectObjectShader)
{
	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	auto common = LibrarySingleton::GetInstance()->GetCommonState();
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//		モデルの描画
	m_signboardModel->Draw(context, *common,
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			//		ポストエフェクト時
			if (flag & PostEffectFlag::Flag::Alpha)
			{
				// ポストエフェクト時のシェーダー設定
				context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
			}
			else
			{
				m_objectShader->SetShader(context);
			}
		});
}

void SignboardObject::Finalize()
{
	m_signboardModel.reset();
}

void SignboardObject::LoadModel(ObjectInformation information)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	std::wostringstream oss;

	oss << Library::StringToWString(information.modelPath);

	//		モデルの読み込み
	m_signboardModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		oss.str().c_str(), *m_effect);

	m_signboardModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(false);
			}
		});

	//		オブジェクトシェーダーマネージャーの生成
	m_objectShader = std::make_unique<ObjectShaderManager>();

	std::wostringstream oss2;

	oss2 << Library::StringToWString(information.collitionPath);

	//		テクスチャの読み込み
	m_objectShader->LoadTexture(oss2.str().c_str());

	//		シェーダーの読み込み（ピクセルシェーダー）
	m_objectShader->LoadShader(ObjectShaderManager::PixelShader,
		L"Resources/Shader/Model/BillShader/BillShaderPS.cso");
}
