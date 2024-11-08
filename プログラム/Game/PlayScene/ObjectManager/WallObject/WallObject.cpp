/*
* @file		FloorObject.cpp
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "WallObject.h"

#include <Effects.h>

WallObject::WallObject(ObjectManager* objectManager)
	:
	m_wallModel{},
	m_objectManager(objectManager),
	m_time(0.0f)
{
	//		オブジェクトメッシュの生成
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

WallObject::~WallObject()
{

}

void WallObject::Initialize(ObjectInformation information)
{
	LoadModel(information);

	std::wostringstream oss2;

	oss2 << Library::StringToWString(information.collitionPath);

	//		初期化処理
	m_objectMesh->Initialize(oss2.str().c_str());

	//		Y軸の回転
	m_world = DirectX::SimpleMath::Matrix::CreateRotationY
				(DirectX::XMConvertToRadians(information.rotation.y));

	//		静的オブジェクトにする
	m_objectMesh->StaticProcess(m_world, information.position);

	m_position = information.position;

	//		座標
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

	//		オブジェクトタイプの設定（壁）
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Wall);

	if (information.effectFlag)
	{
		//		通常描画をするようにする
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

		//		ブルームを掛けるようにする
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);

		//		ブルームの深度描画は描画しない
		m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::BloomDepth);

		//		フォグの処理の場合描画する
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

		//		アルファの処理の場合描画する
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	}
	else
	{
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
}

void WallObject::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_time > 5.0f)
	{
		m_time = 0.0f;
	}

	m_constBuffer.Time = { m_time, 0.0f, 0.0f, 0.0f };

	m_objectShader->UpdateBuffer(m_constBuffer);
}

void WallObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	auto common = LibrarySingleton::GetInstance()->GetCommonState();
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//		モデルの描画
	m_wallModel->Draw(context, *common,
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

	//		メッシュの描画
	//drawMesh->StaticRender(m_objectMesh.get());
}

void WallObject::Finalize()
{
	m_wallModel.reset();
	m_objectMesh->Finalize();
}

void WallObject::LoadModel(ObjectInformation information)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	std::wostringstream oss;

	oss << Library::StringToWString(information.modelPath);

	//		モデルの読み込み
	m_wallModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		oss.str().c_str(), *m_effect);

	m_wallModel->UpdateEffects([&](DirectX::IEffect* effect)
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

	//		テクスチャの読み込み
	m_objectShader->LoadTexture(L"Resources/Texture/Object/Wall/WallTexture.png");
	m_objectShader->LoadTexture(L"Resources/Texture/Object/Wall/wallFantom.png");
	m_objectShader->LoadTexture(L"Resources/Texture/Object/Wall/wallSpray.png");
	m_objectShader->LoadTexture(L"Resources/Texture/Object/Wall/NormalMap.png");

	//		シェーダーの読み込み（ピクセルシェーダー）
	m_objectShader->LoadShader(ObjectShaderManager::PixelShader,
					L"Resources/Shader/Model/Wall/WallPS.cso");
	m_objectShader->LoadShader(ObjectShaderManager::VertexShader,
					L"Resources/Shader/Model/Wall/WallVS.cso");

	//		コンストバッファの作製
	m_objectShader->CreateConstBuffer(m_constBuffer);

}
