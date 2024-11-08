/*
* @file		EndSetting.h
* @brief	�I���ݒ�̐ݒ�
* @author	Morita
* @date		2024/07/10
*/
#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class EndSetting : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	()
	*/
	EndSetting(MenuManager* menuManager);

	//		�f�X�g���N�^
	~EndSetting();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	//		�{�^���̏���
	void ButtonProcess();

private:

	//		���j���[�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	MenuManager* m_menuManager;

	//		�^�C�g���̑J�ڎ���
	float m_transitionTitleTime;

	//		��܂��ȃ��j���[�̑J�ڎ���
	float m_transitionRoughTime;

	//		�ݒ肷�镔����UI�̑J�ڎ���
	float m_transitionSettingUITime;

	//		�����J�ڂ��s�����ǂ������f����
	bool m_startJudgement;

	//		�I���J�ڂ��s�����ǂ������f����
	bool m_endJudgement;

	//		�߂邩�ǂ���
	bool m_menuCloseJudgement;

};