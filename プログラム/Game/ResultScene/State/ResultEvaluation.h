/*
* @file		ResultEvaluation.h
* @brief	���U���g�]������
* @author	Morita
* @date		2024/06/28
*/

#pragma once

#include "../ResultManager.h"

#include "../IResultManager.h"

class ResultManager;

class ResultEvaluation : public IResultManager
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(resultManager)	���U���g�}�l�[�W���[�̃C���X�^���X
	*/
	ResultEvaluation(ResultManager* resultManager);
	
	//		�f�X�g���N�^
	~ResultEvaluation();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	float Easing(float time);

private:

	//		���U���g�}�l�[�W���[
	ResultManager* m_resultManager;

	//		����
	float m_time;
};