/*
* @file		ObjectShaderManager.cpp
* @brief	�I�u�W�F�N�g�̃V�F�[�_�[�}�l�[�W��
* @author	Morita
* @date		2024/09/24
*/

#include "pch.h"

#include "ObjectShaderManager.h"

#include <WICTextureLoader.h>

#include "Common/BinaryFile.h"

ObjectShaderManager::ObjectShaderManager()
{
	//		�V�F�[�_�[���g�p���Ă��Ȃ���Ԃɂ���
	m_useShader = ShaderType::None;
}

ObjectShaderManager::~ObjectShaderManager()
{
}

void ObjectShaderManager::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture.push_back(texture);
}

void ObjectShaderManager::SetShader(ID3D11DeviceContext1* context)
{
	if (m_constantBuffer != nullptr)
	{
		//		�萔�o�b�t�@�̐ݒ�
		ID3D11Buffer* cbuff[] = { m_constantBuffer.Get() };

		//		�W�I���g���V�F�[�_�[
		if ((m_useShader & ShaderType::GeometryShader) != 0)
		{
			context->GSSetConstantBuffers(1, 1, cbuff);
		}

		//		���_�V�F�[�_�[
		if ((m_useShader & ShaderType::VertexShader) != 0)
		{
			context->VSSetConstantBuffers(1, 1, cbuff);
		}

		//		�s�N�Z���V�F�[�_�[
		if ((m_useShader & ShaderType::PixelShader) != 0)
		{
			context->PSSetConstantBuffers(1, 1, cbuff);
		}
	}
	
	//		�e�N�X�`���̐ݒ�
	for (int i = 0, max = static_cast<int>(m_texture.size());
		i < max; ++i)
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());

	//		�W�I���g���V�F�[�_�[
	if ((m_useShader & ShaderType::GeometryShader) != 0)
	{
		context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	}

	//		���_�V�F�[�_�[
	if ((m_useShader & ShaderType::VertexShader) != 0)
	{
		context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	}

	//		�s�N�Z���V�F�[�_�[
	if ((m_useShader & ShaderType::PixelShader) != 0)
	{
		context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	}
}

void ObjectShaderManager::LoadShader(ShaderType type, const wchar_t* filePath)
{
	m_useShader |= type;

	//		�s�N�Z���V�F�[�_�[�̏ꍇ
	if ((type & ShaderType::PixelShader) != 0)
	{

		m_pixelShader = LibrarySingleton::GetInstance()->CreatePSShader(filePath);
	}

	//		���_�V�F�[�_�[�̏ꍇ
	if ((type & ShaderType::VertexShader) != 0)
	{
		BinaryFile VSData = LibrarySingleton::GetInstance()->CreateVSShader(filePath, &m_vertexShader);
	}

	//		�W�I���g���V�F�[�_�[�̏ꍇ
	if ((type & ShaderType::GeometryShader) != 0)
	{
		m_geometryShader = LibrarySingleton::GetInstance()->CreateGSShader(filePath);
	}
}