/*
* @file		UIRender.h
* @brief	UI�̕`�揈��
* @author	Morita
* @date		2024/10/20
*/


#pragma once

#include "../../PostEffectManager.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"

class UIRender : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(manager)	�|�C���^�̃C���X�^���X
	*/
	UIRender(PostEffectManager* manager);

	//		�f�X�g���N�^
	~UIRender();

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

	//		�����_�[�^�[�Q�b�g���쐬����
	void CreateRenderTarget();

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�̃C���X�^���X
	PostEffectManager* m_postEffectManager;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;


	//		�����e�N�X�`��
	ID3D11ShaderResourceView* m_alphaEffectTexture;
};