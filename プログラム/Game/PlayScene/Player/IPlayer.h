/*
* @file		IPlayer
* @brief	�v���C���[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "pch.h"

class IPlayer
{
public:

	//		����������
	virtual void Initialize() = 0;

	//		�X�V����
	virtual void Update() = 0;

	//		�ړ�����
	virtual void Move() = 0;

	//		�A�j���[�V�����̍X�V
	virtual void Animation() = 0;

	//		�`�揈��
	virtual void Render() = 0;

	//		�I������
	virtual void Finalize() = 0;

	//		�f�X�g���N�^
	virtual ~IPlayer() = default;
};

