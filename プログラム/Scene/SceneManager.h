/*
* @file		SceneManager.h
* @brief	�V�[���}�l�[�W���[
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include <unordered_map>

#include "Scene/IScene.h"

#include "SceneState/TutorialScene.h"
#include "SceneState/PlayScene.h"
#include "SceneState/TitleScene.h"
#include "SceneState/ResultScene.h"

class PlayScene;
class TitleScene;
class ResultScene;
class TutorialScene;

#include "Game/Menu/MenuManager.h"

class SceneManager
{
public:
	//		�R���X�g���N�^
	SceneManager();

	//		�f�X�g���N�^
	~SceneManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

public:

	enum SceneType
	{
		Title,
		Play,
		Result,
		Tutorial,
	};

private:

	//		�V�[��
	IScene* m_scene;

	//		���j���[�}�l�[�W���[
	std::unique_ptr<MenuManager> m_menuManager;

	//        �N���A�^�C��
	int m_clearTime;

	//        ���S�J�E���g
	int m_deathCount;

	//		�ő�^�C��
	int m_maxTime;

	//		�V�[���̏��
	std::unordered_map<SceneType, std::unique_ptr<IScene>> m_sceneInformation;

	//		�V�[���^�C�v
	SceneType m_sceneType;

	//		�Q�[�����I�����邩
	bool m_endJudgement;

public:

	void ChangeScene(SceneType type);

	/*
	*    �N���A�^�C����ݒ肷��
	*
	*    @param    (time)    ����
	*/
	void SetClearTime(int time) { m_clearTime = time; }

	/*
	*    �N���A�^�C�����󂯎��
	*
	*    @return ����
	*/
	int GetClearTime() { return m_clearTime; }

	/*
	*    ���S�񐔂�ݒ肷��
	*
	*    @param    (count)    ��
	*/
	void SetDeathCount(int count) { m_deathCount = count; }

	/*
	*    ���S�񐔂��󂯎��
	*
	*    @return ��
	*/
	int GetDeathCount() { return m_deathCount; }
	
	void SetMaxTime(int time) { m_maxTime = time; }

	int GetMaxTime() { return m_maxTime; }

	/*
	*	���j���[�}�l�[�W���[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuManager* GetMenuManager() { return m_menuManager.get(); }

	void SetEndJudgement(bool judgement) { m_endJudgement = judgement; }

	bool GetEndJudgement() { return m_endJudgement; }
};
