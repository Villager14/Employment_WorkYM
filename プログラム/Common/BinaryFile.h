/*
* @file		ShaderRead.cpp
* @brief	�V�F�[�_�[�ǂݍ���
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include <memory>

class BinaryFile
{
protected:

	//		�f�[�^
	std::unique_ptr<char[]> m_data;

	//		�T�C�Y
	unsigned int m_size;

public:

	/*
	*	�t�@�C�������w�肵�ă��[�h
	* 
	*	@param	(fileName)	�t�@�C���p�X
	*/
	static BinaryFile LoadFile(const wchar_t* fileName);

	//		�R���X�g���N�^
	BinaryFile();

	//		���[�u�R���X�g���N�^
	BinaryFile(BinaryFile&& i);

	//		�A�N�Z�T
	char* GetData() { return m_data.get(); }

	//		�T�C�Y
	unsigned int GetSize() { return m_size; }
};