/*
* @file		IPlayerCamera.h
* @brief	�v���C���[�̃J�����̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/05/08
*/

#pragma once

class IPlayerCamera
{
public:

	//		����������
	virtual void Initialize() = 0;

	//		�X�V����
	virtual void Update() = 0;

	//		�I������
	virtual void Finalize() = 0;

	//		�f�X�g���N�^
	virtual ~IPlayerCamera() = default;
};