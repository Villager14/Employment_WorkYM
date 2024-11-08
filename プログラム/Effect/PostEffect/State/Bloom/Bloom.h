/*
* @file		Bloom.h
* @brief	�u���[���̏���
* @author	Morita
* @date		2024/10/01
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

#include "../../PostEffectManager.h"

#include "../../IPostEffect.h"

class Bloom : public IPostEffect
{
public:

	//		�R���X�g���N�^
	Bloom(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~Bloom();

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

	//		�[�x�쐬
	void CreateDepth();

	//		�����_�[�^�[�Q�b�g�̍쐻
	void CreateRenderTarget();

public:

	//		�R���X�g�o�b�t�@
	struct LuminanceConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
	};

	struct SyntheticBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;					//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;				//		��]��
		DirectX::XMVECTORF32 backcolor = DirectX::Colors::Black;	//		�w�i�F
	};

private:

	//		�[�x�o�b�t�@
	ID3D11DepthStencilView* m_depthNormalStencil;

	//		�P�x�R���X�g�o�b�t�@
	LuminanceConstBuffer m_luminanceConstBuffer;

	//		�����R���X�g�o�b�t�@
	SyntheticBuffer m_synthticBuffer;

	//		�P�x�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_luminanceShader;

	//		���������V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_syntheticShader;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;
	//		�P�x�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_luminanceRenderTexture;
	//		�ڂ��������_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_gradationRenderTexture;
	//		���������_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_syntheticRenderTexture;
	//		�ŏI�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_rastRenderTexutre;

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	PostEffectManager* m_postEffectManager;

	//		�V�F�[�_�[���\�[�X
	ID3D11ShaderResourceView* m_sceneTexture;

	//		�P�x�e�N�X�`��
	ID3D11ShaderResourceView* m_luminanceTexture;

	//		�ڂ����e�N�X�`��
	ID3D11ShaderResourceView* m_gradationTexture;

	//		�����e�N�X�`��
	ID3D11ShaderResourceView* m_syntheticTexture;

	//		�ŏI�e�N�X�`��
	ID3D11ShaderResourceView* m_rastTexutre;

	//		�u���[���������s��Ȃ��I�u�W�F�N�g�ɑ΂���s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_bloomUnaffectedpixelShader;



	//		�[�x�X�e���V��
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	//		�[�x���\�[�X
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_depthSRV;

	//		�[�x�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthTexture;
};

