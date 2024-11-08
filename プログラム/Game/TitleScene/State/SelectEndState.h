/*
* @file		SelectEndState.h
* @brief	�I����I���������
* @author	Morita
* @date		2024/05/26
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleSelectManager.h"

class TitleSelectManager;

class SelectEndState : public ITitleSelect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleSelectManager)	�^�C�g���I���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	SelectEndState(TitleSelectManager* titleSelectManager);

	//		�f�X�g���N�^
	~SelectEndState();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	//		UI�̈ړ�
	void UIMove();

	//		�V�[����؂�ւ��鏈��
	void ChangeSceneProcess();

private:

	//		�^�C�g���Z���N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	TitleSelectManager* m_titleSelectManager;

	//		����
	float m_time;

};