/*
* @file		ResultStart.h
* @brief	���U���g�J�n����
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "../ResultManager.h"

#include "../IResultManager.h"

class ResultManager;

class ResultStart : public IResultManager
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(resultManager)	���U���g�}�l�[�W���[�̃C���X�^���X
	*/
	ResultStart(ResultManager* resultManager);
	
	//		�f�X�g���N�^
	~ResultStart();

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