/*
* @file		UIRender.h
* @brief	UI�V�F�[�_�[�̕`��
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "ConstBufferManager.h"

enum class CENTER_POINT
{
	ABOVE_LEFT,
	ABOVE_CENTER,
	ABOVE_RIGHT,

	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,

	UNDER_LEFT,
	UNDER_CENTER,
	UNDER_RIGHT,
};

class UIRenderManager
{
public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
	};

	//		�R���X�g���N�^
	UIRenderManager();
	
	//		�f�X�g���N�^
	~UIRenderManager();

	//		���_
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	/*
	*	�e�N�X�`���̓ǂݍ���
	* 
	*	@param	(path)	�t�@�C���p�X
	*/
	void LoadTexture(const wchar_t* path, int index = 0);

	/*
	*	�V�F�[�_�[���쐬����
	* 
	*	@param	(path)			�e�N�X�`���̃p�X
	*	@param	(position)		���W
	*	@param	(scale)			�X�P�[��
	*	@param	(centerPoint)	���S�_
	*/
	template<typename UIType>
	void Create(
		const wchar_t* texpath,
		const wchar_t* vsPath,
		const wchar_t* gsPath,
		const wchar_t* psPath,
		const UIType& obj,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale,
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER);

	//		�V�F�[�_�[�̓ǂݍ���
	void LoadShader(
		const wchar_t* vsPath,
		const wchar_t* gsPath,
		const wchar_t* psPath
		);

	template<typename UIType>
	void Render(const UIType& obj);

	//		�I������
	void Finalize();

private:

	//		�o�b�t�@�[
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;

	//		���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		�e�N�X�`���n���h��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	//		�W�I���g���b�N�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//		�e�N�X�`�����T�C�Y
	int m_textureWidth;

	//		�e�N�X�`���c�T�C�Y
	int m_textureHeight;

	//		�X�P�[��
	DirectX::SimpleMath::Vector2 m_scale;

	//		���W
	DirectX::SimpleMath::Vector2 m_position;

	//		��]
	DirectX::SimpleMath::Matrix m_rotationMatrix;

	//		���S�_
	CENTER_POINT m_centerPoint;

	//		�R���X�g�o�b�t�@�}�l�[�W���[
	std::unique_ptr<ConstBufferManager> m_constBufferManager;

	//		�T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sample;
public:

	/*
	*	��]��ݒ肷��
	*
	*	@param	(rotatonMatrix)	��]
	*/
	void SetRotationMatrix(DirectX::SimpleMath::Matrix rotatonMatrix)
	{
		m_rotationMatrix = rotatonMatrix;
	}

	DirectX::SimpleMath::Matrix GetRotationMatrix() { return m_rotationMatrix; }

	/*
	*	���W��ݒ肷��
	* 
	*	@param	(position)	���W
	*/
	void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

	/*
	*	�T�C�Y��ݒ肷��
	* 
	*	@param	(size)	�T�C�Y
	*/
	void SetSize(DirectX::SimpleMath::Vector2 size) { m_scale = size; }

	/*
	*	�Z���^�[�|�C���g��ݒ肷��
	* 
	*	@param	(centerPoint)	���S�ʒu
	*/
	void SetCenterPoint(CENTER_POINT centerPoint) { m_centerPoint = centerPoint; }

	void SetSampler(ID3D11SamplerState* sampler) { m_sample = sampler; }

	ConstBufferManager* GetConstBufferManager() { return m_constBufferManager.get(); }

	void SetTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, int index = 0) 
	{ 
		if (m_texture.size() <= index)
		{
			m_texture.push_back(texture);
		}
		else
		{
			m_texture[index] = texture;
		}
	};

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(int index = 0) { return m_texture[index]; }

	DirectX::SimpleMath::Vector2 GetTextureSize() 
	{ return { static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight) }; }

	void SetTextureSize(int width, int height) {m_textureWidth = width; m_textureHeight = height; }
};

template<typename UIType>
inline void UIRenderManager::Create(const wchar_t* texpath,
	const wchar_t* vsPath, const wchar_t* gsPath, const wchar_t* psPath,
	const UIType& obj, DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 scale, CENTER_POINT centerPoint)
{
	m_position = position;
	m_scale = scale;
	m_centerPoint = centerPoint;

	m_constBufferManager = std::make_unique<ConstBufferManager>();

	//		�V�F�[�_�[�̓ǂݍ���
	LoadShader(vsPath, gsPath, psPath);

	m_constBufferManager->CreateConstBuffer(obj);

	//		�摜�̓ǂݍ���
	LoadTexture(texpath);
}

template<typename UIType>
inline void UIRenderManager::Render(const UIType& obj)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto commonState = LibrarySingleton::GetInstance()->GetCommonState();

	//		�摜�̒��S
	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(m_centerPoint)),
		DirectX::SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)),
		DirectX::SimpleMath::Vector2(1.0f,0.0f))
	};

	m_constBufferManager->UpdateBuffer(obj);

	//		�R���X�g�o�b�t�@�̃o�C���h
	m_constBufferManager->BindBuffer();

	//		�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { commonState->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//ID3D11SamplerState* sampler[1] = { m_sample.Get()};
	//context->PSSetSamplers(0, 1, sampler);

	//		�������`��w��
	ID3D11BlendState* blendestate = commonState->NonPremultiplied();

	//		�������菈��
	context->OMSetBlendState(blendestate, nullptr, 0xFFFFFFFF);

	//		�[�x�o�b�t�@�ɏ������ݎQ��
	context->OMSetDepthStencilState(commonState->DepthDefault(), 0);

	//		�J�����O�͍����
	context->RSSetState(commonState->CullNone());

	//		�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	for (int i = 0, max = static_cast<int>(m_texture.size());
		 i < max; ++i)
	{
		//		�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//		�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//		�|���S����`��
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->Begin();
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->
		Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->End();

	//		�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}
