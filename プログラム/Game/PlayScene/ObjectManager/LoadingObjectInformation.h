/*
* LoadingObjectInformation.h
* @brief	オブジェクトの情報の読み込み
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include <string>

#include "ObjectInformation.h"

class LoadingObjectInformation
{
public:

	//		コンストラクタ
	LoadingObjectInformation();

	//		デストラクタ
	~LoadingObjectInformation();

	void Load(int stageNumber);

	//		情報の整理
	void OrganizingInformation(int count, std::string val, ObjectInformation* objectInformation);

	void Finalize();
private:

	//		オブジェクトの情報
	std::vector<ObjectInformation> m_objectInformation;

public:

	/*
	*	オブジェクトの情報
	* 
	*	@return 情報
	*/
	std::vector<ObjectInformation> GetObjectInformation() { return m_objectInformation; };
};