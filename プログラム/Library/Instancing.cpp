/*
* @file		Instancing.cpp
* @brief	インスタンシング
* @author	Morita
* @date		2024/10/04
*
* 参考 : http://maverickproj.web.fc2.com/d3d11_18.html
*/

#include "pch.h"

#include "Instancing.h"

#include "Common/BinaryFile.h"

#include <WICTextureLoader.h>

Instancing::Instancing()
	:
	time(0.0f)
{
	m_learMesh = std::make_unique<LeadMesh>();
}

Instancing::~Instancing()
{
}


void Instancing::Initilaize(int count, const wchar_t* psPath, const wchar_t* vsPath)
{
	m_count = count;

	auto device = LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice();

	INPUT_LAYOUT =
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	0,										D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),	D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	   0,	sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0},

		//		入力アセンブラに頂点シェーダー用の行列を追加
	};

	//		描画する数だけ行列を追加する
	for (int i = 0; i < m_count; ++i)
	{
		//		入力アセンブラに行列情報
		D3D11_INPUT_ELEMENT_DESC descf =
		{ "MATRIX", static_cast<UINT>(i), DXGI_FORMAT_R32G32B32A32_FLOAT, 1, static_cast<UINT>(i * 16), D3D11_INPUT_PER_INSTANCE_DATA, 1 };

		INPUT_LAYOUT.push_back(descf);
	}

	//		頂点の入力情報用のバッファの情報
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = static_cast<UINT>(m_count * sizeof(DirectX::SimpleMath::Matrix));
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//		バッファの作製
	HRESULT hr = device->CreateBuffer(&desc, nullptr, &m_instanceBuffer);
	
	//		バッファが作れていない場合終了する
	if (FAILED(hr))
	{
		exit(0);
	}
	
	ShaderRead(psPath, vsPath);

	//--
	//		頂点インデックスバッファの作製
	//--
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(UINT) * static_cast<UINT>(m_vertexIndex.size());
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA indexInitData;
	ZeroMemory(&indexInitData, sizeof(indexInitData));
	indexInitData.pSysMem = m_vertexIndex.data();
	
	hr = device->CreateBuffer(&indexBufferDesc, &indexInitData, &m_vertexIndexBuffer);

	//		作成失敗時は終了する
	if (FAILED(hr))
	{
		exit(0);
	}

	//--
	//		頂点バッファの作製
	//--
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = static_cast<UINT>((m_vertex.size() - 1.0) * sizeof(DirectX::SimpleMath::Vector3));
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexInitada;
	ZeroMemory(&vertexInitada, sizeof(vertexInitada));
	vertexInitada.pSysMem = m_vertex.data();

	hr = device->CreateBuffer(&vertexBufferDesc, &vertexInitada, &m_vertexBuffer);

	//		作成失敗時は終了する
	if (FAILED(hr))
	{
		exit(0);
	}
}

void Instancing::Render()
{
	//		コンテキスト
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	D3D11_MAPPED_SUBRESOURCE mappedResouce;

	//		シェーダーをセットする
	context->VSSetShader(m_vertexShader.Get(), NULL, 0);
	context->PSSetShader(m_pixelShader.Get(), NULL, 0);

	//		バッファのロック
	HRESULT hr = context->Map(m_instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResouce);

	time += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (SUCCEEDED(hr))
	{
		DirectX::SimpleMath::Matrix* matrix =
			(DirectX::SimpleMath::Matrix*)(mappedResouce.pData);

		for (int i = 0; i < m_count; ++i)
		{
			DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

			world *= DirectX::SimpleMath::Matrix::CreateRotationY(time);

			world *= DirectX::SimpleMath::Matrix::CreateTranslation
			(DirectX::SimpleMath::Vector3(-10.0f, 0.0f, i * 30.0f));

			world = world * 
				LibrarySingleton::GetInstance()->GetView() * 
				LibrarySingleton::GetInstance()->GetProj();

			matrix[i] = XMMatrixTranspose(world);
		}
	}
	else
	{
		//		ロックできてない
		exit(0);
	}

	//		バッファのロック解除
	context->Unmap(m_instanceBuffer.Get(), 0);

	//		インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());


	//		メッシュの描画方式を設定する
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ID3D11Buffer* buffer[2] = { m_vertexBuffer.Get(), m_instanceBuffer.Get() };
	UINT stride[2] = { sizeof(m_vertex.size()), sizeof(DirectX::SimpleMath::Matrix) };
	UINT offset[2] = { 0, 0 };

	context->IASetVertexBuffers(0, 2, buffer, stride, offset);

	//		インデックスバッファ設定
	context->IASetIndexBuffer(m_vertexIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	//		テクスチャの情報
	context->PSSetShaderResources(0, 1, m_texture[0].GetAddressOf());

	//		インスタンスを使用した描画
	context->DrawIndexedInstanced(static_cast<UINT>(m_vertex.size()), m_count, 0, 0, 0);
	//context->DrawIndexedInstanced(m_vertex.size(), m_count, 0, 0, 0);

	//		シェーダーを削除する
	context->VSSetShader(NULL, NULL, 0);
	context->PSSetShader(NULL, NULL, 0);
}

void Instancing::LoadTexture(const wchar_t* path, int index)
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
}

void Instancing::ShaderRead(const wchar_t* psPath, const wchar_t* vsPath)
{
	//		デバイス
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(vsPath);
	BinaryFile PSData = BinaryFile::LoadFile(psPath);

	HRESULT hr = device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	if (FAILED(hr))
	{
		exit(0);
	}

	//		頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//		エラー
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
		return;
	}

	//		ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreatePixelShader Failde", NULL, MB_OK);
		return;
	}
}

void Instancing::MeshInformation(const wchar_t* path)
{
	//		三角メッシュ情報を受け取る
	std::vector<Triangle> triangle = m_learMesh->Lead(path);

	m_vertexIndex = m_learMesh->GetVertexIndex();

	//		頂点の数を受け取る
	m_vertexCount = m_learMesh->GetVertexCount();

	//		頂点情報を受け取る
	m_vertex = m_learMesh->GetVertex();

	m_learMesh->Clear();
}
