/*
* @file		SignboardEffect.h
* @brief	�ŔG�t�F�N�g
* @author	Morita
* @date		2024/10/30
*/

#pragma once

#include "Library/Shader/EffectShaderManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class EffectManager;

class SignboardEffect
{
public:

	//		�R���X�g���N�^
	SignboardEffect(EffectManager* effectManager);

	//		�f�X�g���N�^
	~SignboardEffect();

	//		����������
	void Initialzie();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render(PostEffectFlag::Flag flag);

	//		�I������
	void Finalize();

private:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
	};

	struct SignboardInformation
	{
		DirectX::SimpleMath::Vector3 position;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	};

	enum SignboardType
	{
		Move,
	};

	void CreateParameta(SignboardType type,
		DirectX::SimpleMath::Vector3 position,
		const wchar_t* path);

private:

	//		�G�t�F�N�g�V�F�[�_�[�}�l�[�W���[
	std::unique_ptr<EffectShaderManager<ConstBuffer>> m_effectShaderManager;

	ConstBuffer m_constBuffer;

	//		�G�t�F�N�g�}�l�[�W���[
	EffectManager* m_effectManager;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	std::unordered_map<SignboardType, SignboardInformation> m_parameta;
};