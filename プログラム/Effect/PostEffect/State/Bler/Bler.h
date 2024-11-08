/*
* @file		Bler.h
* @brief	�u���[�̏���
* @author	Morita
* @date		2024/10/02
*/

#pragma once

#include "Common/RenderTexture.h"

#include "../../PostEffectManager.h"

#include "Common/DepthStencil.h"

class Bler
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(postEffectManager)	PostEffectManager�̃C���X�^���X�̃|�C���^
	*/
	Bler(PostEffectManager* postEffectManager);

	~Bler();

	//		����������
	void Initialize();

	/*
	*	�`�揈��
	* 
	*	@param	(texture)	�e�N�X�`��
	*	@return �e�N�X�`��
	*/
	ID3D11ShaderResourceView* Render(ID3D11ShaderResourceView* texture);

	//		�V�F�[�_�[�̍쐻������
	void CreateShader();

	//		�I������
	void Finalize();

	//		�����_�[�e�N�X�`���̍쐬
	void CreateRenderTexture();

public:

	//		�R���X�g�o�b�t�@
	struct SideConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
		DirectX::SimpleMath::Vector4 blerValue;				//		�u���[�̒l
	};

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	PostEffectManager* m_postEffectManager;

	//		�������_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_sideRenderTexture;

	//		�c�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_warpRenderTexture;

	//		�g��e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_expansionRenderTexture;

	//		���u���[
	std::unique_ptr<UIRenderManager> m_sideBler;

	//		�c�u���[
	std::unique_ptr<UIRenderManager> m_warpBler;

	//		�g��u���[
	std::unique_ptr<UIRenderManager> m_expansionBler;

	//		���R���X�g�o�b�t�@
	SideConstBuffer m_sideConstBuffer;

	//		���e�N�X�`��
	ID3D11ShaderResourceView* m_sideTexture;

	//		�c�e�N�X�`��
	ID3D11ShaderResourceView* m_warpTexture;

	//		�g��e�N�X�`��
	ID3D11ShaderResourceView* m_expansionTexture;

	//		���[�x�o�b�t�@
	std::unique_ptr<DepthStencil> m_sideDepthStancil;

	//		�c�[�x�o�b�t�@
	std::unique_ptr<DepthStencil> m_warpDepthStancil;

};