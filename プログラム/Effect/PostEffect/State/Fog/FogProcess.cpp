/*
* @file		FogProcess.cpp
* @brief	フォグの処理
* @author	Morita
* @date		2024/10/10
*/

#include "pch.h"

#include "FogProcess.h"

#include "Common/ReaData.h"

FogProcess::FogProcess(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{

}

FogProcess::~FogProcess()
{
}

void FogProcess::Initialize()
{
	CreateRenderTarget();

	//		シェーダーの読み込み
	LoadShader(L"Resources/Shader/PostEffect/Bloom/Depth/ShadowDepthVS.cso",
		L"Resources/Shader/PostEffect/Bloom/Depth/ShadowDepthPS.cso");

	//		深度作成
	CreateDepth();

	//		深度シェーダー描画
	m_depthShaderView = std::make_unique<UIRenderManager>();

	//		合成用
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Fog/Depth/FogDepthVS.cso",
		L"Resources/Shader/PostEffect/Fog/Depth/FogDepthGS.cso",
		L"Resources/Shader/PostEffect/Fog/Depth/FogDepthPS.cso",
		m_fogShaderConstBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		定数バッファの値
	m_fogShaderConstBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_fogShaderConstBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_fogShaderConstBuffer.backColor = m_postEffectManager->GetBackColor();
	m_fogShaderConstBuffer.drawingDistance = { LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
											LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX,
											0.0f, 0.0f };
}

void FogProcess::Update()
{
}

void FogProcess::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛けないようにする
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		レンダーターゲットの変更(オブジェクトの描画)
	m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(), m_depthStencilView.Get());
}

void FogProcess::PostEffectRender()
{
	//		レンダーターゲットの変更
	m_fogTexture = m_postEffectManager->ChangeRenderTarget(m_depthRenderTarget.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	//		テクスチャサイズの変更
	m_depthShaderView->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
									  static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		テクスチャをセットする
	m_depthShaderView->SetTexture(m_depthSRV);
	m_depthShaderView->SetTexture(m_postEffectManager->GetShaderTexture(), 1);

	//		フォグ処理の描画
	m_depthShaderView->Render(m_fogShaderConstBuffer);

	m_postEffectManager->SetShaderTexture(m_fogTexture);
}

void FogProcess::Filanize()
{
	m_renderTexture.reset();
	m_depthRenderTarget.reset();
	m_depthShaderView.reset();
}

void FogProcess::LoadShader(const wchar_t* vsPath, const wchar_t* psPath)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// ピクセルシェーダーの作成（深度用）
	std::vector<uint8_t> ps =
		DX::ReadData(psPath);
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps.data(), ps.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	// 頂点シェーダーの作成（深度用）
	std::vector<uint8_t> vs =
		DX::ReadData(vsPath);
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs.data(), vs.size(),
			nullptr, m_vertexShader.ReleaseAndGetAddressOf())
	);
}

void FogProcess::SetObjectShader(PostEffectObjectShader* shader)
{
	shader->SetPixselShader(m_pixselShader.Get());
	shader->SetVertexShader(m_vertexShader.Get());
}

void FogProcess::CreateDepth()
{
	//		サイズ
	RECT rect = { 0,0, static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	UINT width = size_t(std::max<LONG>(rect.right - rect.left, 1));
	UINT height = size_t(std::max<LONG>(rect.bottom - rect.top, 1));

	// 深度テクスチャの設定
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = width; // テクスチャの幅
	depthTextureDesc.Height = height; // テクスチャの高さ
	depthTextureDesc.MipLevels = size_t(1);
	depthTextureDesc.ArraySize = size_t(1);
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

void FogProcess::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_depthRenderTarget = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
