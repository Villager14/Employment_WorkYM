/*
* @file		UIRender.h
* @brief	UIシェーダーの描画
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "UIRenderManager.h"

#include <WICTextureLoader.h>
#include "Common/BinaryFile.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> UIRenderManager::INPUT_LAYOUT =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	0,										D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),	D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	   0,	sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0},
};

UIRenderManager::UIRenderManager()
	:
	m_textureWidth(0),
	m_textureHeight(0),
	m_centerPoint(CENTER_POINT::MIDDLE_CENTER)
{
	m_sample = LibrarySingleton::GetInstance()->GetCommonState()->LinearWrap();
}

UIRenderManager::~UIRenderManager()
{
}

void UIRenderManager::LoadTexture(const wchar_t* path, int index)
{
	if (m_texture.size() <= index)
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> tex;

		m_texture.push_back(tex);
	}

	//		画像ファイルの読み込み
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, m_resource.ReleaseAndGetAddressOf(),
		m_texture[index].ReleaseAndGetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

	//		テクスチャ化
	DX::ThrowIfFailed(m_resource.As(&texture));

	D3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);

	//		テクスチャのサイズを取得
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

void UIRenderManager::LoadShader(
	const wchar_t* vsPath,
	const wchar_t* gsPath,
	const wchar_t* psPath)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	m_pixelShader = LibrarySingleton::GetInstance()->CreatePSShader(psPath);
	m_geometryShader = LibrarySingleton::GetInstance()->CreateGSShader(gsPath);
	BinaryFile VSData = LibrarySingleton::GetInstance()->CreateVSShader(vsPath, &m_vertexShader);


	//		インプットレイアウトの作製
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());
}

void UIRenderManager::Finalize()
{
	m_textureWidth = 0;
	m_textureHeight = 0;

	m_texture.clear();
	m_texture.shrink_to_fit();

	m_constBufferManager.reset();
}
