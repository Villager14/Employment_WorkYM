/*
* @file		MenuInformationRead.h
* @brief	メニューの情報の読み込み
* @author	Morita
* @date		2024/07/18
*/

#include <fstream>

class MenuInformationRead
{
public:

	//		コンストラクタ
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