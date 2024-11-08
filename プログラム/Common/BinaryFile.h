/*
* @file		ShaderRead.cpp
* @brief	シェーダー読み込み
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include <memory>

class BinaryFile
{
protected:

	//		データ
	std::unique_ptr<char[]> m_data;

	//		サイズ
	unsigned int m_size;

public:

	/*
	*	ファイル名を指定してロード
	* 
	*	@param	(fileName)	ファイルパス
	*/
	static BinaryFile LoadFile(const wchar_t* fileName);

	//		コンストラクタ
	BinaryFile();

	//		ムーブコンストラクタ
	BinaryFile(BinaryFile&& i);

	//		アクセサ
	char* GetData() { return m_data.get(); }

	//		サイズ
	unsigned int GetSize() { return m_size; }
};