/*
* LoadingObjectInformation.h
* @brief	�I�u�W�F�N�g�̏��̓ǂݍ���
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include <string>

#include "ObjectInformation.h"

class LoadingObjectInformation
{
public:

	//		�R���X�g���N�^
	LoadingObjectInformation();

	//		�f�X�g���N�^
	~LoadingObjectInformation();

	void Load(int stageNumber);

	//		���̐���
	void OrganizingInformation(int count, std::string val, ObjectInformation* objectInformation);

	void Finalize();
private:

	//		�I�u�W�F�N�g�̏��
	std::vector<ObjectInformation> m_objectInformation;

public:

	/*
	*	�I�u�W�F�N�g�̏��
	* 
	*	@return ���
	*/
	std::vector<ObjectInformation> GetObjectInformation() { return m_objectInformation; };
};