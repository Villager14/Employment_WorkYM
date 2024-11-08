/*
* @file		ResultStay.cpp
* @brief	���U���g�ҋ@����
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "../ResultManager.h"

#include "../IResultManager.h"

class ResultManager;

class ResultStay : public IResultManager
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(resultManager)	���U���g�}�l�[�W���[�̃C���X�^���X
	*/
	ResultStay(ResultManager* resultManager);
	
	//		�f�X�g���N�^
	~ResultStay();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	//		���U���g�}�l�[�W���[
	ResultManager* m_resultManager;
};