/*
* @file		Instancing.cpp
* @brief	�C���X�^���V���O
* @author	Morita
* @date		2024/10/04
*
* �Q�l : http://maverickproj.web.fc2.com/d3d11_18.html
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

		//		���̓A�Z���u���ɒ��_�V�F�[�_�[�p�̍s���ǉ�
	};

	//		�`�悷�鐔�����s���ǉ�����
	for (int i = 0; i < m_count; ++i)
	{
		//		���̓A�Z���u���ɍs����
		D3D11_INPUT_ELEMENT_DESC descf =
		{ "MATRIX", static_cast<UINT>(i), DXGI_FORMAT_R32G32B32A32_FLOAT, 1, static_cast<UINT>(i * 16), D3D11_INPUT_PER_INSTANCE_DATA, 1 };

		INPUT_LAYOUT.push_back(descf);
	}

	//		���_�̓��͏��p�̃o�b�t�@�̏��
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = static_cast<UINT>(m_count * sizeof(DirectX::SimpleMath::Matrix));
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//		�o�b�t�@�̍쐻
	HRESULT hr = device->CreateBuffer(&desc, nullptr, &m_instanceBuffer);
	
	//		�o�b�t�@�����Ă��Ȃ��ꍇ�I������
	if (FAILED(hr))
	{
		exit(0);
	}
	
	ShaderRead(psPath, vsPath);

	//--
	//		���_�C���f�b�N�X�o�b�t�@�̍쐻
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

	//		�쐬���s���͏I������
	if (FAILED(hr))
	{
		exit(0);
	}

	//--
	//		���_�o�b�t�@�̍쐻
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

	//		�쐬���s���͏I������
	if (FAILED(hr))
	{
		exit(0);
	}
}

void Instancing::Render()
{
	//		�R���e�L�X�g
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	D3D11_MAPPED_SUBRESOURCE mappedResouce;

	//		�V�F�[�_�[���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), NULL, 0);
	context->PSSetShader(m_pixelShader.Get(), NULL, 0);

	//		�o�b�t�@�̃��b�N
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
		//		���b�N�ł��ĂȂ�
		exit(0);
	}

	//		�o�b�t�@�̃��b�N����
	context->Unmap(m_instanceBuffer.Get(), 0);

	//		�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());


	//		���b�V���̕`�������ݒ肷��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ID3D11Buffer* buffer[2] = { m_vertexBuffer.Get(), m_instanceBuffer.Get() };
	UINT stride[2] = { sizeof(m_vertex.size()), sizeof(DirectX::SimpleMath::Matrix) };
	UINT offset[2] = { 0, 0 };

	context->IASetVertexBuffers(0, 2, buffer, stride, offset);

	//		�C���f�b�N�X�o�b�t�@�ݒ�
	context->IASetIndexBuffer(m_vertexIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	//		�e�N�X�`���̏��
	context->PSSetShaderResources(0, 1, m_texture[0].GetAddressOf());

	//		�C���X�^���X���g�p�����`��
	context->DrawIndexedInstanced(static_cast<UINT>(m_vertex.size()), m_count, 0, 0, 0);
	//context->DrawIndexedInstanced(m_vertex.size(), m_count, 0, 0, 0);

	//		�V�F�[�_�[���폜����
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

	//		�摜�t�@�C���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, m_resource.ReleaseAndGetAddressOf(),
		m_texture[index].ReleaseAndGetAddressOf());
}

void Instancing::ShaderRead(const wchar_t* psPath, const wchar_t* vsPath)
{
	//		�f�o�C�X
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
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

	//		���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//		�G���[
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
		return;
	}

	//		�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreatePixelShader Failde", NULL, MB_OK);
		return;
	}
}

void Instancing::MeshInformation(const wchar_t* path)
{
	//		�O�p���b�V�������󂯎��
	std::vector<Triangle> triangle = m_learMesh->Lead(path);

	m_vertexIndex = m_learMesh->GetVertexIndex();

	//		���_�̐����󂯎��
	m_vertexCount = m_learMesh->GetVertexCount();

	//		���_�����󂯎��
	m_vertex = m_learMesh->GetVertex();

	m_learMesh->Clear();
}
