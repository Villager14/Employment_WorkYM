/*
* @file		TitleInformation.h
* @brief	�^�C�g���̏��
* @author	Morita
* @date		2024/08/01
*/

#pragma once

#include "pch.h"

#include "Library/Shader/UIRenderManager.h"

#include "Library/Shader/StandardShader.h"

#include "Library/Shader/UIRenderManager.h"

#include "Effect/UI/TitleScene/BackGroundMove.h"

#include "ITitleSelect.h"

class TitleInformation
{
public:

	//		�R���X�g���N�^
	TitleInformation()
	:
		m_inputKey(false),
		m_backGroundMove(nullptr),
		m_fade(nullptr),
		m_standardShader(nullptr),
		m_changeSceneJudgement(false),
		m_scrollWheel(0),
		m_direction(false),
		m_menuUseJudgement(false)
	{};

	//		�f�X�g���N�^
	~TitleInformation() {};

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

	//		UI�̎��
	enum TitleUIType
	{
		Play,		//		�v���C
		End,		//		�I��
		Setting,	//		�ݒ�
		TitleRogo,	//		�^�C�g�����S
		Space,		//		�X�y�[�X
		W,			//		W
		A,			//		A
	};

	//		���
	enum State
	{
		PlayState,		//		�v���C���
		EndState,		//		�I�����
		SettingState,	//		�ݒ���
		ChangState,		//		�ύX���
		StartState		//		�X�^�[�g���
	};

	enum MoveDirection
	{
		UP,
		Down,
		Back,
	};

public:

	void Initilaize(BackGroundMove* backGroundMove,
		StandardShader<TitleUIType>* standardShader,
		UIRenderManager* fade)
	{
		m_backGroundMove = backGroundMove;
		m_standardShader = standardShader;
		m_fade = fade;
	}

	void Finalize()
	{
		m_inputKey = false;
		m_changeSceneJudgement = false;
		m_scrollWheel = 0;
	}

public:

	//		�^�C�g�����S�̍��W
	const DirectX::SimpleMath::Vector2 TITLE_POINT = { 0.0f, -170.0f };

	//		���S�n�_
	const DirectX::SimpleMath::Vector2 CENTER_POINT = { 0.0f,120.0f };

	//		���n�_
	const DirectX::SimpleMath::Vector2 UNDER_POINT = { 0.0f, 200.0f };

	//		��n�_
	const DirectX::SimpleMath::Vector2 UP_POINT = { 0.0f, 40.0f };

	//		�X�y�[�X�̃v���C�����W
	const DirectX::SimpleMath::Vector2 SPACE_PLAY = { 300.0f, 120.0f };

	//		�X�y�[�X�̃G���h�����W
	const DirectX::SimpleMath::Vector2 SPACE_END = { 270.0f, 120.0f };

	//		�X�y�[�X�̐ݒ莞���W
	const DirectX::SimpleMath::Vector2 SPACE_SETTING = { 410.0f, 120.0f };

	//		W�̃v���C�����W
	const DirectX::SimpleMath::Vector2 W_PLAY = { 120.0f, 40.0f };

	//		W�̃G���h�����W
	const DirectX::SimpleMath::Vector2 W_END = { 110.0f, 40.0f };

	//		W�̐ݒ莞���W
	const DirectX::SimpleMath::Vector2 W_SETTING = { 180.0f, 40.0f };

	//		A�̃v���C�����W
	const DirectX::SimpleMath::Vector2 A_PLAY = { 120.0f, 200.0f };

	//		A�̃G���h�����W
	const DirectX::SimpleMath::Vector2 A_END = { 110.0f, 200.0f };

	//		A�̐ݒ莞���W
	const DirectX::SimpleMath::Vector2 A_SETTING = { 180.0f, 200.0f };


	//		�ړ����x
	const float MOVE_SPEED = 7.0f;

	//		�ő�X�P�[��
	const float MAX_SCALE = 1.0f;

	//		�ŏ��X�P�[��
	const float MIN_SCALE = 0.5f;

private:

	//		�w�i�ړ�
	BackGroundMove* m_backGroundMove;

	//		�X�^���_�[�h�V�F�[�_�[
	StandardShader<TitleUIType>* m_standardShader;

	//		�t�F�[�h�̏���
	UIRenderManager* m_fade;

	//		�萔�o�b�t�@
	ConstBuffer m_buffer;

	//		�L�[���͂����������ǂ���
	bool m_inputKey;

	//		�V�[����ύX���邩�ǂ���
	bool m_changeSceneJudgement;

	//		�X�N���[���̒l
	int m_scrollWheel;

	//		�ړ�����
	bool m_direction;

	//		���j���[���g���邩�ǂ���
	bool m_menuUseJudgement;

	//		��Ԃ̏��
	std::unordered_map<TitleInformation::State, std::unique_ptr<ITitleSelect>> m_stateInformation;

	//		�`�揇��ݒ肷��
	std::vector<TitleInformation::TitleUIType> m_drawOder;

public:

	/*
	*	�t�F�[�h�̕`��
	*
	*	@param	(time)	����
	*/
	void FadeViewProcess(float time) {
		m_buffer.time = { time, 0.0f, 0.0f, 0.0f };
		m_fade->Render(m_buffer);
	}

	/*
	*	�R���X�g�o�b�t�@�̃|�C���^���󂯎��
	* 
	*	@return �R���X�g�o�b�t�@
	*/
	ConstBuffer GetBuffer() { return m_buffer; }

	/*
	*	�R���X�g�o�b�t�@��ݒ肷��
	* 
	*	@param	(buffer)	�R���X�g�o�b�t�@
	*/
	void SetBuffer(ConstBuffer buffer) { m_buffer = buffer;};

	/*
	*	�^�C�g��UI�}�l�[�W���[�̃C���X�^���X�̃|�C���^���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	StandardShader<TitleUIType>* GetStandardShader() { return m_standardShader; }

	/*
	*	�L�[���͂����邩�ǂ����󂯎��
	*
	*	@return true : �L�[���͂����� false : �L�[���͂��Ȃ�
	*/
	bool GetKeyInput() { return m_inputKey; }

	/*
	*	�L�[���͂����邩�ǂ����󂯎��
	*
	*	@param	(judgement) true : �L�[���͂����� false : �L�[���͂��Ȃ�
	*/
	void SetKeyInput(bool judgement) { m_inputKey = judgement; }

	/*
	*	�V�[����؂�ւ��邩�ǂ������f����
	*
	*	@param	(judgement)	true : �؂�ւ��� false : �؂�ւ��Ȃ�
	*/
	void SetChangeSceneJudgement(bool judgement) { m_changeSceneJudgement = judgement; }

	/*
	*	�V�[����؂�ւ��邩�ǂ������f����
	*
	*	@return true : �؂�ւ��� false : �؂�ւ��Ȃ�
	*/
	bool GetChangeScnenJudgemnet() { return m_changeSceneJudgement; }

	/*
	*	�X�N���[���z�C�[����ݒ肷��
	* 
	*	@param	(wheel)	�z�C�[���̒l
	*/
	void SetScrollWheel(int wheel) { m_scrollWheel = wheel; }

	/*
	*	�X�N���[���z�C�[���̒l���󂯎��
	* 
	*	@return �X�N���[���̒l
	*/
	int GetScrollWheel() { return m_scrollWheel; }

	/*
	*	�ړ��������󂯎��
	*
	*	@return true : �� false : ��
	*/
	bool GetDirection() { return m_direction; }

	/*
	*	�ړ������󂯎��
	*
	*	@param	(direction) true : �� false : ��
	*/
	void SetDirection(bool direction) { m_direction = direction; }

	/*
	*	���j���[���J���邩�ǂ����ݒ肷��
	*
	*	@param	(judgement)	true : �g���� false : �g���Ȃ�
	*/
	void SetMenuUseJudgement(bool judgement) { m_menuUseJudgement = judgement; }

	/*
	*	���j���[���J���邩�ǂ����ݒ肷��
	*
	*	@return	true : �g���� false : �g���Ȃ�
	*/
	bool GetMenuUseJudgement() { return m_menuUseJudgement; }

	/*
	*	��Ԃ̏����󂯎��
	*
	*	@return	�|�C���^
	*/
	std::unordered_map<TitleInformation::State, std::unique_ptr<ITitleSelect>>* GetStateInformation() { return &m_stateInformation; }

	/*
	*	�`�揇�̏����󂯎��
	*
	*	@return	�|�C���^
	*/
	std::vector<TitleInformation::TitleUIType>* GetDraowOder() { return &m_drawOder; }

};