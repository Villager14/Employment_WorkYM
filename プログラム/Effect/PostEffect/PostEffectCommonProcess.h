/*
* @file		PostEffectCommonProcess.h
* @brief	�|�X�g�G�t�F�N�g���ʏ���
* @author	Morita
* @date		2024/10/07
*/

#pragma once

#include "Common/RenderTexture.h"

class PostEffectManager;

class PostEffectCommonProcess
{
public:

	//		�R���X�g���N�^
	PostEffectCommonProcess(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~PostEffectCommonProcess();

	//		�����_�[�e�N�X�`���̍쐻
	/*
	*	�����_�[�e�N�X�`���̍쐻
	* 
	*	@param	(size)	��ʂ̃T�C�Y
	*	@return �����_�[�e�N�X�`���̃C���X�^���X
	*/
	std::unique_ptr<DX::RenderTexture> CreateRenderTexture(DirectX::SimpleMath::Vector2 size =
		LibrarySingleton::GetInstance()->GetScreenSize());

	/*
	*	�e�N�X�`���̍쐻
	* 
	*	@param	(index)	�v�f��
	*/
	void CreateTexture(int index);

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	PostEffectManager* m_postEffectManager;
};