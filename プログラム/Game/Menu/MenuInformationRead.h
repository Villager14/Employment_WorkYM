/*
* @file		MenuInformationRead.h
* @brief	���j���[�̏��̓ǂݍ���
* @author	Morita
* @date		2024/07/18
*/

#include <fstream>

class MenuInformationRead
{
public:

	//		�R���X�g���N�^
	MenuInformationRead() {};

	~MenuInformationRead() {};

	void Read()
	{
		std::string fileName = "test.json";

		std::ifstream ifs(fileName.c_str());

		if (ifs.good())
		{
			




		}

	}

private:



};