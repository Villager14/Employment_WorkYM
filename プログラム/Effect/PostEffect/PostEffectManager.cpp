/*
* @file		PostEffectManager.cpp
* @brief	�|�X�g�G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/10/01
*/

#include "pch.h"

#include "PostEffectManager.h"

#include "State/Bler/Bler.h"

#include "State/Bloom/Bloom.h"
#include "State/Bler/Bler.h"
#include "State/Fog/FogProcess.h"
#include "State/BloomDepth/BloomDepth.h"
#include "State/Effect/EffectRender.h"
#include "State/EffectDepth/EffectDepthRender.h"
#include "State/UIRender/UIRender.h"
#include "State/Normal/NormalRender.h"
#include "State/ScreenColor/ScreenColor.h"
#include "State/Fade/FadePostEffect.h"
#include "State/GlitchNoise/GlitchNoise.h"

PostEffectManager::PostEffectManager(GameManager* gameManager, MenuInformation* menuInformation)
	:
	m_gameManager(gameManager),
	m_menuInformation(menuInformation)
{
	//		�|�X�g�G�t�F�N�g���ʏ���
	m_commonProcess = std::make_unique<PostEffectCommonProcess>(this);

	m_backRenderColor = DirectX::Colors::Black;
	m_backColor = DirectX::Colors::Black;
}

PostEffectManager::~PostEffectManager()
{
}

void PostEffectManager::Initialize(DirectX::XMVECTORF32 color)
{
	//		�|�X�g�G�t�F�N�g�I�u�W�F�N�g�V�F�[�_�[�̐���
	m_objectShader = std::make_unique<PostEffectObjectShader>();

	//		�T���v���[�̍쐻
	CreateSampler();

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		�X�^���_�[�h�V�F�[�_�[�̏�����
	m_standardShader->Initialize();

	//		�e�N�X�`���̍쐻
	for (int i = 0; i < UIType::UITexture + 1; ++i)
		m_commonProcess->CreateTexture(i);

	//		�w�i�F���󂯎��
	m_backColor = color;

	//		�u���[�̐���
	m_bler = std::make_unique<Bler>(this);

	m_bler->Initialize();

	m_postEffectProcess.insert({ PostEffectFlag::Flag::Normal,		std::make_unique<NormalRender>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::Bloom,		std::make_unique<Bloom>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::BloomDepth,	std::make_unique<BloomDepth>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::Fog,			std::make_unique<FogProcess>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::Alpha,		std::make_unique<EffectRender>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::AlphaDepth,	std::make_unique<EffectDepthRender>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::UI,			std::make_unique<UIRender>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::UIBack,		std::make_unique<UIRender>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::Color,		std::make_unique<ScreenColor>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::Glitch,		std::make_unique<GlitchNoise>(this) });
	m_postEffectProcess.insert({ PostEffectFlag::Flag::Fade,		std::make_unique<FadePostEffect>(this) });

	//		�|�X�g�G�t�F�N�g�����̏�����
	for (auto& e : m_postEffectProcess)
	{
		e.second->Initialize();
	}
}

void PostEffectManager::Update(PostEffectFlag::Flag flag)
{
	m_postEffectProcess[flag]->Update();
}

void PostEffectManager::Render(PostEffectFlag::Flag flag)
{
	m_postEffectProcess[flag]->ObjectRender();
}

void PostEffectManager::RastRender(PostEffectFlag::Flag flag)
{
	m_postEffectProcess[flag]->PostEffectRender();
}

void PostEffectManager::Finalize()
{
	//		�u���[�̏I������
	m_bler.reset();

	m_standardShader.reset();

	m_objectShader.reset();

	for (auto& e : m_postEffectProcess)
	{
		e.second->Filanize();
	}

	m_postEffectProcess.clear();
}

void PostEffectManager::CreateSampler()
{
	//		�T���v���[�̍쐻
	D3D11_SAMPLER_DESC sampler_desc = {};// CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	//		�t�B���^�[�������@
	sampler_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	//		u�e�N�X�`���������@
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	//		v�e�N�X�`���������@
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	//		w�e�N�X�`���������@
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	//		�����̃T���v�����O�f�[�^�Ƃ̔�r
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_LESS;

	//		�T���v�����O�̍쐻
	LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreateSamplerState(&sampler_desc,
		m_sampler.ReleaseAndGetAddressOf());

	m_objectShader->SetSampler(m_sampler.Get());
}

ID3D11ShaderResourceView* PostEffectManager::ChangeRenderTarget(DX::RenderTexture* renderTarget,
																ID3D11DepthStencilView* depthStencil)
{
	auto context = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDeviceContext();

	//		�����_�[�^�[�Q�b�g
	auto rtv = renderTarget->GetRenderTargetView();

	//		���\�[�X
	ID3D11ShaderResourceView* shaderResource = renderTarget->GetShaderResourceView();

	//		�����_�[�^�[�Q�b�g��ύX
	context->ClearRenderTargetView(rtv, m_backRenderColor);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, depthStencil);

	return shaderResource;
}

void PostEffectManager::ResetRenderTarget()
{
	auto context = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDeviceContext();

	//		�����_�[�^�[�Q�b�g
	auto renderTarget = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetRenderTargetView();

	//		�[�x
	auto depthStencil = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	auto viewPoart = LibrarySingleton::GetInstance()->GetDeviceResources()->GetScreenViewport();

	context->RSSetViewports(1, &viewPoart);
}

void PostEffectManager::RenderTextureView()
{
	m_standardShader->ChangeTexture(UIType::RastTexture,
								m_shaderResourceView,
								LibrarySingleton::GetInstance()->GetScreenSize());

	m_standardShader->Render(UIType::RastTexture);
}
