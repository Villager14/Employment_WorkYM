/*
* 
* @file		FloorObject.cpp
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "WireObject.h"

#include "Library/Factory/IFactory.h"

#include <Effects.h>

WireObject::WireObject(ObjectManager* objectManager)
	:
	m_wireModel{},
	m_rotation(0.0f),
	m_objectManager(objectManager),
	m_number(0)
{
	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

WireObject::~WireObject()
{

}

void WireObject::Initialize(ObjectInformation information)
{
	int size = static_cast<int>((*m_objectManager->GetUseWireInformation()).size());

	if (size == 0) m_number = 0;
	else m_number = size - 1;

	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_wireModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Drone.cmo", *m_effect);

	m_wireModel->UpdateEffects([&](DirectX::IEffect* effect)
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

	m_wireRangeModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/WireRange.cmo", *m_effect);

	m_wingModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Wing.cmo", *m_effect);

	m_wingModel->UpdateEffects([](DirectX::IEffect* effect)
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

	//		羽の座標
	m_wingPosition.push_back(WING_POSITION_0);
	m_wingPosition.push_back(WING_POSITION_1);
	m_wingPosition.push_back(WING_POSITION_2);
	m_wingPosition.push_back(WING_POSITION_3);

	//		座標を設定する
	m_world = DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

	m_position = information.position;

	//		デバックワールドの半径の大きさ
	m_debugWorld = DirectX::SimpleMath::Matrix::CreateScale(WIRE_RANGE);

	//		座標を設定する
	m_debugWorld *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

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

void WireObject::Update()
{
	//		プレイヤーとの距離が一定いないの場合
	if ((m_objectManager->GetPlayerPosition()
		- (*m_objectManager->GetUseWireInformation()
		)[m_number].position).Length() < WIRE_RANGE + 7.0f)
	{
		//		使用可能
		(*m_objectManager->GetUseWireInformation())
			[m_number].m_usedJudgement = true;
	}
	//		使用不可能
	else (*m_objectManager->GetUseWireInformation())
			[m_number].m_usedJudgement = false;

	//		羽の回転量
	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * WING_ROTATION_SPEED;
}

void WireObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	//		デバックの描画
	DebugRender();

	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	//		カリング処理
	if (!m_objectManager->Culling(m_position, 500.0f))
	{
		return;
	}

	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//		モデルの描画
	m_wireModel->Draw(context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&]
		{
			//		ポストエフェクト時
			if (flag & PostEffectFlag::Flag::Bloom || flag & PostEffectFlag::Flag::Alpha)
			{
				// ポストエフェクト時のシェーダー設定
				context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
			}
		});

	//		羽の描画
	WingRender(flag, postEffectObjectShader);
}

void WireObject::Finalize()
{
	m_wingPosition.clear();
	m_wingPosition.shrink_to_fit();
	m_wireRangeModel.reset();
	m_wingModel.reset();
	m_wireModel.reset();
}

void WireObject::DebugRender()
{
	//		デバック表示かどうか
	if (LibrarySingleton::GetInstance()->GetDebugJudgement())
	{
		//		ワイヤーが届く範囲(半透明処理)
		for (const auto& it : m_wireRangeModel->meshes)
		{
			auto mesh = it.get();

			mesh->PrepareForRendering(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
				*LibrarySingleton::GetInstance()->GetCommonState(), true);

			mesh->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
				m_debugWorld, LibrarySingleton::GetInstance()->GetView(),
				LibrarySingleton::GetInstance()->GetProj());
		}
	}
}

void WireObject::WingRender(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	for (int i = 0; i < 4; ++i)
	{
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateRotationY(m_rotation);

		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_wingPosition[i]);
		world *= DirectX::SimpleMath::Matrix::CreateTranslation({ m_world._41, m_world._42, m_world._43 });

		//		羽モデルの描画
		m_wingModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(),
			world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), false, [&]
			{
				//		ポストエフェクト時
				if (flag & PostEffectFlag::Flag::Bloom)
				{
					// ポストエフェクト時のシェーダー設定
					context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
				}
			});
	}
}
