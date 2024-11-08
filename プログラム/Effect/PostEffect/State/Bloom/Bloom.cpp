/*
* @file		Bloom.cpp
* @brief	�u���[���̏���
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
	//		�P�x�V�F�[�_�[�𐶐�����
	m_luminanceShader = std::make_unique<UIRenderManager>();
	m_syntheticShader = std::make_unique<UIRenderManager>();

	CreateRenderTarget();

	//		�E�B���h�E�T�C�Y��ݒ肷��
	m_luminanceConstBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	m_luminanceConstBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	m_synthticBuffer.windowSize = m_luminanceConstBuffer.windowSize;
	m_synthticBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		�w�i�F�̎擾
	m_synthticBuffer.backcolor = m_postEffectManager->GetBackColor();

	//		�P�x�V�F�[�_�[���쐬����
	m_luminanceShader->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Bloom/Luminance/LuminanceVS.cso",
		L"Resources/Shader/PostEffect/Bloom/Luminance/LuminanceGS.cso",
		L"Resources/Shader/PostEffect/Bloom/Luminance/LuminancePS.cso",
		m_luminanceConstBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�����p
	m_syntheticShader->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Bloom/Synthetic/SyntheticVS.cso",
		L"Resources/Shader/PostEffect/Bloom/Synthetic/SyntheticGS.cso",
		L"Resources/Shader/PostEffect/Bloom/Synthetic/SyntheticPS.cso",
		m_synthticBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�s�N�Z���V�F�[�_�[�̍쐻
	m_bloomUnaffectedpixelShader = LibrarySingleton::GetInstance()->CreatePSShader
	(L"Resources/Shader/PostEffect/Bloom/BloomUnaffectedObject/BloomunaffectedObject.cso");
}

void Bloom::Update()
{
}

void Bloom::ObjectRender()
{
	//		�w�i�F
	m_postEffectManager->SetBackRenderColor(DirectX::Colors::Black);

	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|����
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(true);

	//		�|�X�g�G�t�F�N�g���s��Ȃ��I�u�W�F�N�g�ɑ΂��ăG�t�F�N�g���|����
	m_postEffectManager->GetPostObjectShader()->SetPixselShader(m_bloomUnaffectedpixelShader.Get());

	//		�[�x�o�b�t�@�̎擾
	m_depthNormalStencil = LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetDepthStencilView();

	//		�����_�[�^�[�Q�b�g�̕ύX(�P�x�擾�p)
	m_luminanceTexture = m_postEffectManager->ChangeRenderTarget(m_luminanceRenderTexture.get(), m_depthStencilView.Get());
}

void Bloom::PostEffectRender()
{
	//		�����_�[�^�[�Q�b�g�̕ύX(�ڂ�������)
	m_gradationTexture = m_postEffectManager->ChangeRenderTarget(m_gradationRenderTexture.get(), m_depthNormalStencil);

	//		�e�N�X�`���̐ݒ�
	m_luminanceShader->SetTexture(m_luminanceTexture);

	//		�e�N�X�`���T�C�Y�̐ݒ�
	m_luminanceShader->SetTextureSize(
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		�P�x�e�N�X�`���̕`��
	m_luminanceShader->Render(m_luminanceConstBuffer);

	//		�u���[�̏���
	m_syntheticTexture = m_postEffectManager->GetBler()->Render(m_gradationTexture);


	//		�ŏI�����_�[�e�N�X�`��
	m_rastTexutre = m_postEffectManager->ChangeRenderTarget(m_rastRenderTexutre.get(), m_depthNormalStencil);

	//		�e�N�X�`���̐ݒ�
	m_syntheticShader->SetTexture(m_syntheticTexture);
	m_syntheticShader->SetTexture(m_postEffectManager->GetShaderTexture(), 1);
	m_syntheticShader->SetTexture((*m_postEffectManager->GetPostEffectProcess())
			[PostEffectFlag::Flag::BloomDepth]->GetTexture(), 2);
	m_syntheticShader->SetTexture(m_depthSRV.Get(), 3);

	//		�e�N�X�`���T�C�Y�̐ݒ�
	m_syntheticShader->SetTextureSize(
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		�e�N�X�`���̕`��
	m_syntheticShader->Render(m_synthticBuffer);

	m_postEffectManager->SetShaderTexture(m_rastTexutre);
}

void Bloom::Filanize()
{
	m_luminanceShader.reset();
	m_syntheticShader.reset();

	//		�����_�[�e�N�X�`���̍쐻
	m_renderTexture.reset();
	m_luminanceRenderTexture.reset();
	m_gradationRenderTexture.reset();
	m_syntheticRenderTexture.reset();
	m_rastRenderTexutre.reset();
}

void Bloom::CreateDepth()
{
	//		�T�C�Y
	RECT rect = { 0,0, static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	const auto width = size_t(std::max<LONG>(rect.right - rect.left, 1));
	const auto height = size_t(std::max<LONG>(rect.bottom - rect.top, 1));

	// �[�x�e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = static_cast<UINT>(width); // �e�N�X�`���̕�
	depthTextureDesc.Height = static_cast<UINT>(height); // �e�N�X�`���̍���
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
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

void Bloom::CreateRenderTarget()
{
	//		�����_�[�e�N�X�`���̍쐻
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_luminanceRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_gradationRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_syntheticRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_rastRenderTexutre = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
