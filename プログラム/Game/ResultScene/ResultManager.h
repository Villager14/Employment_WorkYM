/*
* @file		ResultManager.h
* @brief	���U���g�}�l�[�W���[
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include <unordered_map>

#include "IResultManager.h"

#include "Effect/UI/TitleScene/BackGroundMove.h"

#include "Library/Shader/UIRenderManager.h"

#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"

#include "Library/Animation/AnimationManager.h"

#include "Library/Shader/StandardShader.h"

#include "Effect/UI/ResultScene/RiseNumberShader.h"

#include "ResultInformation.h"

class ResultManager
{
public:

	//		���U���g�}�l�[�W���[
	ResultManager();

	//		���U���g�}�l�[�W���[
	~ResultManager();

	//		����������
	/*
	*	����������
	* 
	*	@param	(score)			�X�R�A
	*	@param	(time)			�^�C��
	*	@param	(deathCount)	���S�J�E���g
	*/
	void Initialize(int score, int time, int deathCount);

	//		����
	void Generation();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		��Ԃ��쐬����
	void CreateState();

	//		�A�j���[�V�����X�L�b�v
	void AnimationSkip();

	//		�V�F�[�_�[�̍쐻
	void CreateStandardShader();

	//		�w�i�̍X�V
	void BackGroundUpdate();

public:


	//		���
	enum State
	{
		Start,			//		�X�^�[�g
		NumberMove,		//		�ԍ�
		Evaluation,		//		�]��
		Stay,			//		�ҋ@
		End,			//		�I��
	};

private:
	
	//		�X�R�A
	int m_score;

	//		����
	int m_time;

	//		���S�J�E���g
	int m_deathCount;

	//		��]��
	float m_rotation;

	//		���j���[���g���邩�ǂ���
	bool m_menuUseJudgement;

	//		���
	std::unique_ptr<ResultInformation> m_information;

	//		���
	IResultManager* m_iState;

	//		��Ԃ̏��
	std::unordered_map<State, std::unique_ptr<IResultManager>> m_stateInformation;

	//		���
	State m_state;

	//		�����̏㏸�V�F�[�_�[
	std::unique_ptr<RiseNumberShader> m_riseNumber;

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<ResultInformation::ResultUIType>> m_shader;

	//		�t�F�[�h�`��
	std::unique_ptr<UIRenderManager> m_fade;

	//		�w�i�ړ��̕`��
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<ScreenEffectManager> m_screenEffectManager;

	//		�v���C���[�A�j���[�V����
	std::unique_ptr<AnimationManager> m_playerAnimation;

public:

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(State state);

	/*
	*	���j���[���g���邩�ǂ����󂯎��
	* 
	*	@return true : �g���� false : �g���Ȃ�
	*/
	bool GetMenuUseJugement() { return m_menuUseJudgement; }

	/*
	*	���j���[���g���邩�ǂ����ݒ肷��
	*
	*	@param	(judgement) true : �g���� false : �g���Ȃ�
	*/
	void SetMenuUseJugement(bool judgement) { m_menuUseJudgement = judgement; }

	/*
	*	�����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ResultInformation* GetInformation() { return m_information.get(); }

	
};