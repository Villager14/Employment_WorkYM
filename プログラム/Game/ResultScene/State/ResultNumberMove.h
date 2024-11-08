/*
* @file		ResultNumberMove.h
* @brief	���U���g�����ړ�����
* @author	Morita
* @date		2024/05/29
*/

#pragma once

#include "../ResultManager.h"

#include "../IResultManager.h"

class ResultManager;

class ResultNumberMove : public IResultManager
{
public:
	
	/*
	*	�R���X�g���N�^
	* 
	*	@param	(resultManager)	���U���g�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	ResultNumberMove(ResultManager* resultManager);

	//		�f�X�g���N�^
	~ResultNumberMove();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	//		�J�ڑ��x
	const float MOVE_SPEED = 2.0f;

	//		�ő厞��
	const float MAX_TIME = 4.0f;

private:

	//		���U���g�}�l�[�W���[
	ResultManager* m_resultManager;

	float m_time;
};