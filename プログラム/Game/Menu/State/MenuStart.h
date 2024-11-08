/*
* @file		MenuStart.h
* @brief	���j���[�X�^�[�g���̏���
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class MenuStart : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	()
	*/
	MenuStart(MenuManager* menuManager);

	//		�f�X�g���N�^
	~MenuStart();

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

private:

	//		���j���[�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	MenuManager* m_menuManager;

	//		�X�P�[��
	float m_scale;

	//		�ړ�
	float m_move;


	//		�^�C�g���̑J�ڎ���
	float m_transitionTitleTime;

	//		��܂��ȃ��j���[�̑J�ڎ���
	float m_transitionRoughTime;

	//		�ݒ肷�镔����UI�̑J�ڎ���
	float m_transitionSettingUITime;

	//		�����J�ڂ��s�����ǂ������f����
	bool m_startJudgement;
};