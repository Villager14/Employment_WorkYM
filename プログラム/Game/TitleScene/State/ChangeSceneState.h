/*
* @file		ChangeSceneState.h
* @brief	�V�[���؂�ւ����������
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleSelectManager.h"

class TitleSelectManager;

class ChangeSceneState : public ITitleSelect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleSelectManager)	�^�C�g���I���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	ChangeSceneState(TitleSelectManager* titleSelectManager);

	//		�f�X�g���N�^
	~ChangeSceneState();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	//		�^�C�g���Z���N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	TitleSelectManager* m_titleSelectManager;

	//		����
	float m_time;
};