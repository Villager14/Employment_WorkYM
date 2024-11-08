/*
* @file		ScreenEffectManager.cpp
* @brief	�X�N���[���G�t�F�N�g�̃}�l�[�W���[
* @author	Morita
* @date		2024/05/22
*/

#include "pch.h"

#include "ScreenEffectManager.h"

ScreenEffectManager::ScreenEffectManager(Scene scene, GameManager* gameManager)
	:
	m_gameManager(gameManager),
	m_shaderResouceView(),
	m_scene(),
	m_backColor()
{
	

	m_scene = scene;

	m_playerModelTexture = std::make_unique<PlayerModelTexture>();

	m_playerModelTexture->Create({ 1280.0f, 0.0f }, { 1.0f, 1.0f });

	//		�w�i�̐F
	m_backColor = DirectX::Colors::Black;
}

ScreenEffectManager::~ScreenEffectManager()
{
}

void ScreenEffectManager::Initialize()
{
	CreateRenderTexture();
}

void ScreenEffectManager::Update()
{
	
	m_playerModelTexture->Update();
}

void ScreenEffectManager::Render()
{
	m_playerModelTexture->Render(m_shaderResouceView);
}

void ScreenEffectManager::Finalize()
{
	m_renderTexture.reset();
}

void ScreenEffectManager::CreateRenderTexture()
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice();

	//		�����_�[�e�N�X�`���̍쐻
	m_renderTexture = std::make_unique<DX::RenderTexture>(
		LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetBackBufferFormat());

	//		�f�o�C�X�̐ݒ�
	m_renderTexture->SetDevice(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice());

	//		�T�C�Y�̐ݒ�
	RECT rect = { 0,0, static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	m_renderTexture->SetWindow(rect);

	//		�T���v���[�̍쐻
	D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
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
	device->CreateSamplerState(&sampler_desc,
		m_sampler.ReleaseAndGetAddressOf());
}

void ScreenEffectManager::ChangeRenderTarget()
{
	auto context = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDeviceContext();

	//		�����_�[�^�[�Q�b�g
	auto rtv = m_renderTexture->GetRenderTargetView();

	//		���\�[�X
	m_shaderResouceView = m_renderTexture->GetShaderResourceView();

	//		�[�x�o�b�t�@
	auto depthStencil = LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetDepthStencilView();

	m_backColor = DirectX::Colors::White;

	//		�����_�[�^�[�Q�b�g��ύX
	context->ClearRenderTargetView(rtv, m_backColor);

	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0);

	context->OMSetRenderTargets(1, &rtv, depthStencil);
}

void ScreenEffectManager::FirstRenderTarget()
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
