/*
* @file		SelectPlayerState.h
* @brief	�v���C��I���������
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleSelectManager.h"

class TitleSelectManager;

class SelectPlayState : public ITitleSelect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleSelectManager)	�^�C�g���I���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	SelectPlayState(TitleSelectManager* titleSelectManager);

	//		�f�X�g���N�^
	~SelectPlayState();

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

	//		�^�C�g���I���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	TitleSelectManager* m_titleSelectManager;

	//		����
	float m_time;
};