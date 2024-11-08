/*
* @file		ScreenColor.h
* @brief	�X�N���[���̐F
* @author	Morita
* @date		2024/10/21
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"


class FadePostEffect : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(manager)	�|�C���^�̃C���X�^���X
	*/
	FadePostEffect(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~FadePostEffect();

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

	//		�t�F�[�h�̏���
	void Fade();

	//		�����_�[�^�[�Q�b�g�̍쐻
	void CreateRenderTarget();

public:
	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�̃C���X�^���X
	PostEffectManager* m_postEffectManager;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�t�H�O�e�N�X�`��
	ID3D11ShaderResourceView* m_colorTexture;

	//		�[�x�̕`��
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	//		�t�H�O�V�F�[�_�[�萔�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�t�F�[�h�ҋ@����
	float m_fadeStayTime;

	//		�t�F�[�h����
	float m_fadeTime;

	//		�t�F�[�h�C�������邩�ǂ������f����
	bool m_fadeinResetJudgement;

	//		�t�F�[�h�A�E�g�����邩�ǂ������f����
	bool m_fadeoutResetJudgement;

	//		���߂̃t�F�[�h�C�����ǂ���
	bool m_firstJudgement;

};