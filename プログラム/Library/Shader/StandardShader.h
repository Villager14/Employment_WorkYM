/*
* @file		StandardShader.h
* @brief	���U���gUI�̃}�l�[�W���[
* @author	Morita
* @date		2024/07/04
*/

#pragma once

#include "pch.h"

#include <unordered_map>

#include "Library/Shader/UIRenderManager.h"


template<typename UIType>
class StandardShader
{
public:

	/*
	*	�R���X�g���N�^
	*
	*	@param	(titleSceneManager)	�^�C�g���V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	StandardShader() {};

	//		�f�X�g���N�^
	~StandardShader() {};

	//		����������
	void Initialize();

	/*
	*	UI�̏����쐬����
	*
	*	@param	(path)		�e�N�X�`���̃p�X
	*	@param	(position)	���W
	*	@param	(size)		�T�C�Y
	*	@param	(type)		UI�̎��
	*/
	void CreateUIInformation(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size,
		UIType type);

	/*
	*	�`�揈��
	*
	*	@param	(type)	�`�悷��UI�̎��
	*/
	void Render(UIType type);

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;						//		���W
		DirectX::SimpleMath::Vector2 scale;							//		�T�C�Y
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;	//		�e�N�X�`��
		DirectX::SimpleMath::Vector2 textureSize;					//		�e�N�X�`���T�C�Y
	};

private:

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�V�F�[�_�[�̏��
	std::unordered_map<UIType, UIInformation> m_shaderInformation;

public:

	/*
	*	�R���X�g�o�b�t�@���󂯎��
	*
	*	@return	�R���X�g�o�b�t�@�̃|�C���^
	*/
	ConstBuffer* GetConsutBuffer() { return &m_constBuffer; }

	/*
	*	UI�̏����󂯎��
	* 
	*	@return key UI�̎�� val�@UI�̏��
	*/
	std::unordered_map<UIType, UIInformation>* GetUIInformation() { return &m_shaderInformation; };

	/*
	*	�e�N�X�`���̏����X�V����
	* 
	*	@param	(type)		�ύX����UI�̎��
	*	@param	(texture)	�e�N�X�`��
	*	@param	(size)		�T�C�Y
	*/
	void ChangeTexture(UIType type, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
					   DirectX::SimpleMath::Vector2 size);
};

template<typename UIType>
void StandardShader<UIType>::Initialize()
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(L"Resources/Texture/TitleScene/TitleRogo.png",
		L"Resources/Shader/UI/UIShader/UIShaderVS.cso",
		L"Resources/Shader/UI/UIShader/UIShaderGS.cso",
		L"Resources/Shader/UI/UIShader/UIShaderPS.cso",
		m_constBuffer,
		{ 0.0f, 0.0f , }, { 1.0f,
		1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		��]�s��𑗂�
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		�E�B���h�E�T�C�Y�𑗂�
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

template<typename UIType>
void StandardShader<UIType>::CreateUIInformation(const wchar_t* path, DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 size, UIType type)
{
	UIInformation uiInformation;

	uiInformation.position = position;
	uiInformation.scale = size;
	m_shader->LoadTexture(path);
	uiInformation.texture = m_shader->GetTexture();
	uiInformation.textureSize = m_shader->GetTextureSize();

	m_shaderInformation.insert({ type, uiInformation });
}

template<typename UIType>
void StandardShader<UIType>::Render(UIType type)
{
	m_shader->SetPosition(m_shaderInformation[type].position);
	m_shader->SetSize(m_shaderInformation[type].scale);
	m_shader->SetTexture(m_shaderInformation[type].texture);
	m_shader->SetTextureSize(static_cast<int>(m_shaderInformation[type].textureSize.x),
		static_cast<int>(m_shaderInformation[type].textureSize.y));

	m_shader->Render(m_constBuffer);
}

template<typename UIType>
inline void StandardShader<UIType>::ChangeTexture(UIType type,
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
	DirectX::SimpleMath::Vector2 size)
{
	m_shaderInformation[type].texture = texture;
	m_shaderInformation[type].textureSize = size;
}
