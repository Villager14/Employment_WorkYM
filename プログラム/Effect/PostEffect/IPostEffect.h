/*
* @file		IPostEffect.h
* @brief	�|�X�g�G�t�F�N�g�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/10/21
*/

#pragma once

#include "pch.h"

class IPostEffect
{
public:

	//		����������
	virtual void Initialize() = 0;

	//		�X�V����
	virtual void Update() = 0;

	//		�I�u�W�F�N�g�`��
	virtual void ObjectRender() = 0;

	//		�|�X�g�G�t�F�N�g��̕`��
	virtual void PostEffectRender() = 0;

	//		�I������
	virtual void Filanize() = 0;

	//		�e�N�X�`�����󂯎��
	virtual ID3D11ShaderResourceView* GetTexture() = 0;

	//		�f�X�g���N�^
	virtual ~IPostEffect() = default;

};