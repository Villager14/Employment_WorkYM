/*
* @file		ResultInformation.h
* @brief	���U���g���
* @author	Morita
* @date		2024/08/04
*/

#pragma once

#include "pch.h"

class ResultInformation
{
public:

	//		�R���X�g���N�^
	ResultInformation()
	:
		m_shader(nullptr),
		m_backGroundMove(nullptr),
		m_fade(nullptr),
		m_playerAnimation(nullptr),
		m_riseNumber(nullptr),
		m_screenEffectManager(nullptr),
		m_changeScene(false)
	{};

	//		�f�X�g���N�^
	~ResultInformation(){};

public:

	//		���U���g��UI�̎��
	enum ResultUIType
	{
		Back,			//		UI�w�i
		Button,			//		�{�^���q���g
		EvaluationUI,	//		�]��
		PlayerBack,		//		�v���C���̔w�i
	};

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

public:

	void Initialize(StandardShader<ResultInformation::ResultUIType>* shader,
		RiseNumberShader* riseNumber, UIRenderManager* fade,
		BackGroundMove* backGroundMove, ScreenEffectManager* screenEffectManager,
		AnimationManager* playerAnimation)
	{
		m_shader = shader;
		m_riseNumber = riseNumber;
		m_fade = fade;
		m_backGroundMove = backGroundMove;
		m_screenEffectManager = screenEffectManager;
		m_playerAnimation = playerAnimation;
	}

	void Finalize()
	{
		m_changeScene = false;
		m_buffer.time = { 0.0f, 0.0f, 0.0f, 0.0f };
	}

public:

	//		�v���C���[�̉�]���x
	const float PLAYER_ROTATION_SPEED = 30.0f;

	//		�v���C���[�̍���
	const float PLAYER_HEIGHT = 2.5f;

	//		�v���C���[�̍��W
	const DirectX::SimpleMath::Vector3 PLAYER_POSITION = { 0.0f, 0.0f, 8.0f };

	//		�X�R�A�̍��W
	const DirectX::SimpleMath::Vector2 SCORE_POSITION = { 350.0f, 150.0f };

	//		���̃V�[���̗U�����W
	const DirectX::SimpleMath::Vector2 NEXT_SCENE = { 0.0f, 280.0f };

	//		�X�R�AA
	const float SCORE_A = 2000.0f;

	//		�X�R�AB
	const float SCORE_B = 1000.0f;

private:

	//		�V�F�[�_�[
	StandardShader<ResultInformation::ResultUIType>* m_shader;

	//		�����̏㏸�V�F�[�_�[
	RiseNumberShader* m_riseNumber;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_buffer;

	//		�t�F�[�h�`��
	UIRenderManager* m_fade;

	//		�w�i�̈ړ�
	BackGroundMove* m_backGroundMove;

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[
	ScreenEffectManager* m_screenEffectManager;

	//		�v���C���[�A�j���[�V����
	AnimationManager* m_playerAnimation;

private:

	//		�V�[����؂�ւ���
	bool m_changeScene;


public:

	/*
	*	�^�C�g��UI�}�l�[�W���[�̃C���X�^���X�̃|�C���^���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	StandardShader<ResultInformation::ResultUIType>* GetStandardShader() { return m_shader; }

	/*
	*	�㏸�ԍ��V�F�[�[�_�[�̃C���X�^���X�̃|�C���^���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	RiseNumberShader* GetRiseNumber() { return m_riseNumber; }

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
	void SetBuffer(ConstBuffer buffer) { m_buffer = buffer; };

	/*
	*	�t�F�[�h���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	UIRenderManager* GetFade() { return m_fade; }

	/*
	*	�w�i���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	BackGroundMove* GetBackGround() { return m_backGroundMove; }

	/*
	*	�X�N���[���G�t�F�N�g���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	ScreenEffectManager* GetScreenEffect() { return m_screenEffectManager; }

	/*
	*	�v���C���[�A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	AnimationManager* GetAnimation() { return m_playerAnimation; }

	/*
	*	�V�[����؂�ւ��邩�ݒ肷��
	*
	*	@param	(judgement)	true : �؂�ւ��� false : �؂�ւ��Ȃ�
	*/
	void SetChangeSceneJudgement(bool judgement) { m_changeScene = judgement; }

	/*
	*	�V�[����؂�ւ��邩�󂯎��
	*
	*	@return true : �؂�ւ��� false : �؂�ւ��Ȃ�
	*/
	bool GetChangeSceneJudgement() { return m_changeScene; }

};
