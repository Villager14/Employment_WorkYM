/*
* @file		ClockBackGround.h
* @brief	UI���v�̔w�i
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../UIManager.h"

class ClockBackGround
{
public:
	//		�R���X�g���N�^
	ClockBackGround(UIManager* uiManager);

	//		�f�X�g���N�^
	~ClockBackGround();

	//		��������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(elapsedTime)	�o�ߎ���
	*/
	void Update(float elapsedTime);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	//		��]��
	const float ROTATION_RADIAN = 60.0f;

private:

	//		UI�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	UIManager* m_uiManager;

	//		�ŏ�����
	float m_rotationMin;

	//		�ő厞��
	float m_rotationMax;

	//		�ߋ��̎���
	float m_pastTime;

	//		��]��
	float m_rotation;
};
