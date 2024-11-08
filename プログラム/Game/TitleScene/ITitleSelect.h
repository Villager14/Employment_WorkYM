/*
* @file		ITitleSelect.h
* @brief	�^�C�g���I���̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/05/25
*/

#pragma once

class ITitleSelect
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
	virtual ~ITitleSelect() = default;
};
