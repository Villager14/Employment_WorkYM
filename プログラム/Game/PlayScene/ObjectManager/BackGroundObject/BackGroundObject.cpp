/*
* @file		BackGroundObject.cpp
* @brief	背景オブジェクト
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "BackGroundObject.h"

#include "PostProcess.h"

#include "Common/ReaData.h"

BackGroundObject::BackGroundObject(ObjectManager* objectManager)
	:
	m_objectManager(objectManager)
{
	//		背景の情報を生成する
	m_information = std::make_unique<BackGroundObjectInformation>();

	//		ポストエフェクトフラグ
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

BackGroundObject::~BackGroundObject()
{
}

void BackGroundObject::Initialize(std::vector<ObjectMesh*> mesh,
	const std::vector<DirectX::SimpleMath::Vector3>& wirePosition)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_backGroundModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Background.cmo", *m_effect);

	
	m_backGroundModel->UpdateEffects([&](DirectX::IEffect* effect)
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

	m_information->Create(mesh, wirePosition);

	// ピクセルシェーダーの作成
	std::vector<uint8_t> ps_torus =
		DX::ReadData(L"Resources/Shader/Model/BillShader/BillShaderPS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps_torus.data(), ps_torus.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	//		ブルームを掛けるようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);

	//		通常描画時にも描画するようにするを
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		ブルームの深度描画は描画しない
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::BloomDepth);

	//		フォグの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);
}

void BackGroundObject::Update()
{
}

void BackGroundObject::Render(PostEffectFlag::Flag flag,
	PostEffectObjectShader* objectShader)
{
	UNREFERENCED_PARAMETER(objectShader);

	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	for (int i = 0, max = static_cast<int>(m_information->GetObjectPosition().size()); i < max; ++i)
	{
		//		カリングの処理
		if (!m_objectManager->Culling(m_information->GetObjectPosition()[i], 500.0f))
		{
			continue;
		}

		//		回転処理
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::
			CreateFromQuaternion(m_information->GetObjectQuaternion()[i]);

		//		座標
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_information->GetObjectPosition()[i]);

		//		モデルの描画
		m_backGroundModel->Draw(context,
			*LibrarySingleton::GetInstance()->GetCommonState(),
			world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), false, [&]() {

				context->PSSetShader(m_pixselShader.Get(), nullptr, 0);
			});
	}
}

void BackGroundObject::Finalize()
{
	m_information->Finalize();

	m_backGroundModel.reset();
}