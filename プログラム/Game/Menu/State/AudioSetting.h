/*
* @file		AudioSetting.h
* @brief	���̐ݒ�
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class AudioSetting : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	()
	*/
	AudioSetting(MenuManager* menuManager);

	//		�f�X�g���N�^
	~AudioSetting();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	//		�X���C�_�[�̕`��
	void SliderView(float transitionTime);

	//		�X���C�_�[�̍X�V����
	void SliderUpdate();
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