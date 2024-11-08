/*
* @file		FogProcess.h
* @brief	�t�H�O�̏���
* @author	Morita
* @date		2024/10/10
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"


class FogProcess : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(manager)	�|�C���^�̃C���X�^���X
	*/
	FogProcess(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~FogProcess();

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

	//		�[�x�쐬
	void CreateDepth();

	//		�����_�[�^�[�Q�b�g���쐬����
	void CreateRenderTarget();
public:
	struct FogShaderConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
		DirectX::SimpleMath::Vector4 backColor;				//		�w�i�F
		DirectX::SimpleMath::Vector4 drawingDistance;		//		�I�u�W�F�N�g�̋���
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

	//		�����_�[�e�N�X�`��(�[�x)
	std::unique_ptr<DX::RenderTexture> m_depthRenderTarget;

	//		�t�H�O�e�N�X�`��
	ID3D11ShaderResourceView* m_fogTexture;

	//		�[�x�̕`��
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	//		�t�H�O�V�F�[�_�[�萔�o�b�t�@
	FogShaderConstBuffer m_fogShaderConstBuffer;

	//		�[�x�X�e���V��
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	//		�[�x���\�[�X
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_depthSRV;

	//		�[�x�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthTexture;
};