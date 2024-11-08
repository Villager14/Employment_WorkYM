/*
* @file		Bloom.cpp
* @brief	ブルームの処理
* @author	Morita
* @date		2024/10/01
*/

#include "pch.h"

#include "Bloom.h"

#include "..\Bler\Bler.h"

#include "Library/Library.h"

#include "../BloomDepth/BloomDepth.h"

Bloom::Bloom(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
	CreateDepth();
}

Bloom::~Bloom()
{
}

void Bloom::Initialize()
{
	//		輝度シェーダーを生成する
	m_luminanceShader = std::make_unique<UIRenderManager>();
	m_syntheticShader = std::make_unique<UIRenderManager>();

	CreateRenderTarget();

	//		ウィンドウサイズを設定する
	m_luminanceConstBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	m_luminanceConstBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	m_synthticBuffer.windowSize = m_luminanceConstBuffer.windowSize;
	m_synthticBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		背景色の取得
	m_synthticBuffer.backcolor = m_postEffectManager->GetBackColor();

	//		輝度シェーダーを作成する
	m_luminanceShader->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Bloom/Luminance/LuminanceVS.cso",
		L"Resources/Shader/PostEffect/Bloom/Luminance/LuminanceGS.cso",
		L"Resources/Shader/PostEffect/Bloom/Luminance/LuminancePS.cso",
		m_luminanceConstBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		合成用
	m_syntheticShader->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Bloom/Synthetic/SyntheticVS.cso",
		L"Resources/Shader/PostEffect/Bloom/Synthetic/SyntheticGS.cso",
		L"Resources/Shader/PostEffect/Bloom/Synthetic/SyntheticPS.cso",
		m_synthticBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		ピクセルシェーダーの作製
	m_bloomUnaffectedpixelShader = LibrarySingleton::GetInstance()->CreatePSShader
	(L"Resources/Shader/PostEffect/Bloom/BloomUnaffectedObject/BloomunaffectedObject.cso");
}

void Bloom::Update()
{
}

void Bloom::ObjectRender()
{
	//		背景色
	m_postEffectManager->SetBackRenderColor(DirectX::Colors::Black);

	//		オブジェクトに対してシェーダーを掛ける
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(true);

	//		ポストエフェクトを行わないオブジェクトに対してエフェクトを掛ける
	m_postEffectManager->GetPostObjectShader()->SetPixselShader(m_bloomUnaffectedpixelShader.Get());

	//		深度バッファの取得
	m_depthNormalStencil = LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetDepthStencilView();

	//		レンダーターゲットの変更(輝度取得用)
	m_luminanceTexture = m_postEffectManager->ChangeRenderTarget(m_luminanceRenderTexture.get(), m_depthStencilView.Get());
}

void Bloom::PostEffectRender()
{
	//		レンダーターゲットの変更(ぼかし処理)
	m_gradationTexture = m_postEffectManager->ChangeRenderTarget(m_gradationRenderTexture.get(), m_depthNormalStencil);

	//		テクスチャの設定
	m_luminanceShader->SetTexture(m_luminanceTexture);

	//		テクスチャサイズの設定
	m_luminanceShader->SetTextureSize(
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		輝度テクスチャの描画
	m_luminanceShader->Render(m_luminanceConstBuffer);

	//		ブラーの処理
	m_syntheticTexture = m_postEffectManager->GetBler()->Render(m_gradationTexture);


	//		最終レンダーテクスチャ
	m_rastTexutre = m_postEffectManager->ChangeRenderTarget(m_rastRenderTexutre.get(), m_depthNormalStencil);

	//		テクスチャの設定
	m_syntheticShader->SetTexture(m_syntheticTexture);
	m_syntheticShader->SetTexture(m_postEffectManager->GetShaderTexture(), 1);
	m_syntheticShader->SetTexture((*m_postEffectManager->GetPostEffectProcess())
			[PostEffectFlag::Flag::BloomDepth]->GetTexture(), 2);
	m_syntheticShader->SetTexture(m_depthSRV.Get(), 3);

	//		テクスチャサイズの設定
	m_syntheticShader->SetTextureSize(
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		テクスチャの描画
	m_syntheticShader->Render(m_synthticBuffer);

	m_postEffectManager->SetShaderTexture(m_rastTexutre);
}

void Bloom::Filanize()
{
	m_luminanceShader.reset();
	m_syntheticShader.reset();

	//		レンダーテクスチャの作製
	m_renderTexture.reset();
	m_luminanceRenderTexture.reset();
	m_gradationRenderTexture.reset();
	m_syntheticRenderTexture.reset();
	m_rastRenderTexutre.reset();
}

void Bloom::CreateDepth()
{
	//		サイズ
	RECT rect = { 0,0, static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	const auto width = size_t(std::max<LONG>(rect.right - rect.left, 1));
	const auto height = size_t(std::max<LONG>(rect.bottom - rect.top, 1));

	// 深度テクスチャの設定
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = static_cast<UINT>(width); // テクスチャの幅
	depthTextureDesc.Height = static_cast<UINT>(height); // テクスチャの高さ
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.Format = DXGI_FORMAT_R32_TYPELESS; // 深度フォーマット
	depthTextureDesc.SampleDesc.Count = 1; // マルチサンプリングのカウント
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	// テクスチャを作成
	HRESULT hr = device->CreateTexture2D(&depthTextureDesc, nullptr, &m_depthTexture);
	if (FAILED(hr))
	{
		// エラーハンドリング
		MessageBox(0, L"CreateTexture2D Failed", NULL, MB_OK);
	}

	// 深度ステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = device->CreateDepthStencilView(m_depthTexture.Get(), &dsvDesc, &m_depthStencilView);
	if (FAILED(hr))
	{
		// エラーハンドリング
		MessageBox(0, L"CreateDepthStencilView Failed", NULL, MB_OK);
	}

	// シェーダーリソースビューの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(m_depthTexture.Get(), &srvDesc, &m_depthSRV);
	if (FAILED(hr))
	{
		// エラーハンドリング
		MessageBox(0, L"CreateShaderResourceView Failed", NULL, MB_OK);
	}
}

void Bloom::CreateRenderTarget()
{
	//		レンダーテクスチャの作製
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_luminanceRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_gradationRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_syntheticRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_rastRenderTexutre = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
