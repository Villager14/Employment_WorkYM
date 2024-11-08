/*
* @file		Transparency.h
* @brief	�A���t�@�G�t�F�N�g�̏���
* @author	Morita
* @date		2024/10/16
*/


#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"

class EffectRender : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(manager)	�|�C���^�̃C���X�^���X
	*/
	EffectRender(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~EffectRender();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I�u�W�F�N�g�`��
	void ObjectRender() override;

	//		�|�X�g�G�t�F�N�g��̕`��
	void PostEffectRender() override;

	//		�I������
	void Filanize() override;

	//		�e�N�X�`�����󂯎��
	ID3D11ShaderResourceView* GetTexture() override { return nullptr; };

	//		�V�F�[�_�[�̓ǂݍ���
	void LoadShader(
		const wchar_t* vsPath,
		const wchar_t* psPath
	);

	void SetObjectShader(PostEffectObjectShader* shader);

	//		�����_�[�^�[�Q�b�g�̍쐻
	void CreateRenderTarget();

public:
	struct FogShaderConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
	};

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�̃C���X�^���X
	PostEffectManager* m_postEffectManager;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�����_�[�e�N�X�`��(����)
	std::unique_ptr<DX::RenderTexture> m_transparencyRenderTexture;

	//		�e�N�X�`��
	ID3D11ShaderResourceView* m_texture;

	//		�����e�N�X�`��
	ID3D11ShaderResourceView* m_alphaEffectTexture;

	//		���������_�[�}�l�[�W���[
	std::unique_ptr<UIRenderManager> m_transparencyRenderManager;

	//		�t�H�O�V�F�[�_�[�萔�o�b�t�@
	FogShaderConstBuffer m_fogShaderConstBuffer;

	//		�I�u�W�F�N�g�ɑ΂���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_objectShader;
};