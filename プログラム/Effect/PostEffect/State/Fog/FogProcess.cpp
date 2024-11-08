/*
* @file		FogProcess.cpp
* @brief	�t�H�O�̏���
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

	//		�V�F�[�_�[�̓ǂݍ���
	LoadShader(L"Resources/Shader/PostEffect/Bloom/Depth/ShadowDepthVS.cso",
		L"Resources/Shader/PostEffect/Bloom/Depth/ShadowDepthPS.cso");

	//		�[�x�쐬
	CreateDepth();

	//		�[�x�V�F�[�_�[�`��
	m_depthShaderView = std::make_unique<UIRenderManager>();

	//		�����p
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Fog/Depth/FogDepthVS.cso",
		L"Resources/Shader/PostEffect/Fog/Depth/FogDepthGS.cso",
		L"Resources/Shader/PostEffect/Fog/Depth/FogDepthPS.cso",
		m_fogShaderConstBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�萔�o�b�t�@�̒l
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
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|���Ȃ��悤�ɂ���
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		�����_�[�^�[�Q�b�g�̕ύX(�I�u�W�F�N�g�̕`��)
	m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(), m_depthStencilView.Get());
}

void FogProcess::PostEffectRender()
{
	//		�����_�[�^�[�Q�b�g�̕ύX
	m_fogTexture = m_postEffectManager->ChangeRenderTarget(m_depthRenderTarget.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	//		�e�N�X�`���T�C�Y�̕ύX
	m_depthShaderView->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
									  static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		�e�N�X�`�����Z�b�g����
	m_depthShaderView->SetTexture(m_depthSRV);
	m_depthShaderView->SetTexture(m_postEffectManager->GetShaderTexture(), 1);

	//		�t�H�O�����̕`��
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

	// �s�N�Z���V�F�[�_�[�̍쐬�i�[�x�p�j
	std::vector<uint8_t> ps =
		DX::ReadData(psPath);
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps.data(), ps.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	// ���_�V�F�[�_�[�̍쐬�i�[�x�p�j
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
	//		�T�C�Y
	RECT rect = { 0,0, static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	UINT width = size_t(std::max<LONG>(rect.right - rect.left, 1));
	UINT height = size_t(std::max<LONG>(rect.bottom - rect.top, 1));

	// �[�x�e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = width; // �e�N�X�`���̕�
	depthTextureDesc.Height = height; // �e�N�X�`���̍���
	depthTextureDesc.MipLevels = size_t(1);
	depthTextureDesc.ArraySize = size_t(1);
	depthTextureDesc.Format = DXGI_FORMAT_R32_TYPELESS; // �[�x�t�H�[�}�b�g
	depthTextureDesc.SampleDesc.Count = 1; // �}���`�T���v�����O�̃J�E���g
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	// �e�N�X�`�����쐬
	HRESULT hr = device->CreateTexture2D(&depthTextureDesc, nullptr, &m_depthTexture);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		MessageBox(0, L"CreateTexture2D Failed", NULL, MB_OK);
	}

	// �[�x�X�e���V���r���[�̍쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = device->CreateDepthStencilView(m_depthTexture.Get(), &dsvDesc, &m_depthStencilView);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		MessageBox(0, L"CreateDepthStencilView Failed", NULL, MB_OK);
	}

	// �V�F�[�_�[���\�[�X�r���[�̍쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(m_depthTexture.Get(), &srvDesc, &m_depthSRV);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		MessageBox(0, L"CreateShaderResourceView Failed", NULL, MB_OK);
	}
}

void FogProcess::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_depthRenderTarget = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
