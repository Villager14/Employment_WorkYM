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

class ResultEnd : public IResultManager
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(resultManager)	���U���g�}�l�[�W���[�̃C���X�^���X
	*/
	ResultEnd(ResultManager* resultManager);
	
	//		�f�X�g���N�^
	~ResultEnd();

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

	//		����
	float m_time;
};