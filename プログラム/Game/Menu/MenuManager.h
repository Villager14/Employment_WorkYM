/*
* @file		MenuManager.h
* @brief	���j���[�̃}�l�[�W���[
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include <unordered_map>

#include "IMenu.h"

#include "State/AudioSetting.h"
#include "State/MenuStart.h"
#include "State/OptionSetting.h"
#include "State/EndSetting.h"
#include "State/MenuClose.h"

#include "MenuInformation.h"

#include "MenuCommonProcess.h"

#include "Scene/SceneManager.h"

class AboveUI;
class Slider;
class MenuSelect;
class FrameWalkUI;

class MenuManager
{
public:
	//		�R���X�g���N�^
	MenuManager(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~MenuManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();
	
	//		���j���[�̔w�i�̕`��
	void MenuBackRneder();

	//		UI�̍쐻
	void CreateUI();

private:

	//		���݂̃^�C�v
	MenuInformation::MenuType m_type;

	//		���݂̏��
	IMenu* m_state;

	//		���j���[�̏�Ԃ̏��
	std::unordered_map<MenuInformation::MenuType, std::unique_ptr<IMenu>> m_menuStateInformation;

	//		���߂ĉ��y���j���[���J���Ă��邩�ǂ���
	bool m_firstAudioMenuJudgement;

	//		���j���[�̏��
	std::unique_ptr<MenuInformation> m_information;

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<MenuInformation::UIType>> m_standardShader;

	//		�㏸UI
	std::unique_ptr<AboveUI> m_aboveUI;

	//		�X���C�_�[UI
	std::unique_ptr<Slider> m_slider;

	//		���j���[�̑I��
	std::unique_ptr<MenuSelect> m_menuSelect;

	//		�t���[�����[�NUI
	std::unique_ptr<FrameWalkUI> m_frameWalkUI;

	//		���ʏ���
	std::unique_ptr<MenuCommonProcess> m_commonProcess;

	//		�V�[���}�l�[�W��
	SceneManager* m_sceneManager;
public:

	/*
	*	���j���[�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuInformation* GetInformation() { return m_information.get(); }

	/*
	*	��܂��ȃ��j���[�̕`��
	* 
	*	@param	(transitionTime)	�J�ڎ���
	*/
	void RoughMenuViwe(float transitionTime);

	//		�I���������j���[�̕`��
	void MenuSelectView();

	/*
	*	��Ԃ̐؂�ւ�
	* 
	*	@param	(type)	���
	*/
	void ChangState(MenuInformation::MenuType type);

	/*
	*	UI�̑J�ڏ���
	* 
	*	@param	(transitionTime1)	�J�ڎ��ԂP
	*	@param	(transitionTime2)	�J�ڎ��ԂQ
	*	@param	(transitionTime3)	�J�ڎ��ԂR
	*	@param	(startJudgement)	�X�^�[�g���Ă��邩�ǂ������f����
	*	@param	(endJudgement)		�I��点�邩�ǂ������f����
	*	@param	(moveJudgement)		�J�ڎ��ԂR�𓮂��������f����
	*/
	bool Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool *startJudgement, bool endJudgement, bool moveJudgement);

	/*
	*	�C�[�W���O�֐��ʏ�UI�p
	* 
	*	@param	(time)	����
	*/
	float EasingIcon(float time) { return 1.0f - pow(1.0f - time, 3.0f); }

	/*
	*	�C�[�W���O�֐��w�i�p
	* 
	*	@param	(time) ����
	*/
	float EasingBackUI(float time) {
		if (time == 1.0f)
		{
			return 1.0f;
		}
		else
		{
			return 1.0f - pow(2.0f, -10.0f * time);
		}
	}

	/*
	*	Audio���j���[�����j���[���J��������x�����s���������󂯎��
	* 
	*	@retun	true : �s�� false : �s��Ȃ�
	*/
	bool GetFirstAudioMenuJudgement() { return m_firstAudioMenuJudgement; }

	/*
	*	Audio���j���[�����j���[���J��������x�����s��������ݒ肷��
	*
	*	@param	(judgement)	true : �s�� false : �s��Ȃ�
	*/
	void SetFirstAudioMenuJudgement(bool judgement) { m_firstAudioMenuJudgement = judgement; }

	/*
	*	���j���[�̋��ʏ���
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuCommonProcess* GetCommonProcess() { return m_commonProcess.get(); }

	/*
	*	�V�[���}�l�[�W���[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	SceneManager* GetSceneManager() { return m_sceneManager; }

};