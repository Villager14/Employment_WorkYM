/*
* @file		IMenu.cpp
* @brief	���j���[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/07/03
*/

#pragma once

class IMenu
{
public:
	//		����������
	virtual void Initialize() = 0;

	//		�X�V����
	virtual void Update() = 0;

	//		�`�揈��
	virtual void Render() = 0;

	//		�I������
	virtual void Finalize() = 0;

	//		�f�X�g���N�^
	virtual ~IMenu() = default;
};
