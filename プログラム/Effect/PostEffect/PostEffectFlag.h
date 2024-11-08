/*
* @file		PostEffectFlag.h
* @brief	�|�X�g�G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/10/01
*/

#pragma once

#include "pch.h"

class PostEffectFlag
{
public:

	enum Flag
	{
		None		= 0b00000000000,
		Normal		= 0b00000000001,		//		�ʏ�`��
		BloomDepth  = 0b00000000010,		//		�u���[���[�x
		Bloom		= 0b00000000100,		//		�u���[��
		Fog			= 0b00000001000,		//		�t�H�O�̏���
		AlphaDepth  = 0b00000010000,		//		�A���t�@�[�x����
		Alpha		= 0b00000100000,		//		�A���t�@�̏���
		UI			= 0b00001000000,		//		UI�̕`��
		Color		= 0b00010000000,		//		��ʂ̐F�ύX
		UIBack		= 0b00100000000,		//		UI�̌�`��
		Glitch		= 0b01000000000,		//		�O���b�`�m�C�Y
		Fade		= 0b10000000000,		//		�t�F�[�h
	};

public:

	//		�R���X�g���N�^
	PostEffectFlag()
	:
	m_flag(Flag::None)
	{};

	//		�f�X�g���N�^
	~PostEffectFlag() {};

private:

	//		�t���O
	int m_flag;

public:

	/*
	*	�t���O���󂯎��
	* 
	*	@return �t���O
	*/
	int GetFlag() { return m_flag; }

	/*
	*	�t���O�������Ă��邩
	*
	*	@param	(flag)	�m�F�������t���O
	*	@return true : yes false : no
	*/
	bool FlagJudgement(Flag flag)
	{
		//		�����̃r�b�g���P�̏ꍇ
		if (m_flag & flag) return true;

		return false;
	}

	/*
	*	�t���O��On�ɂ���
	*
	*	@param	(flag)	�I���ɂ������t���O
	*/
	void TrueFlag(Flag flag)
	{
		m_flag |= flag;
	}

	/*
	*	�t���O��of�ɂ���
	*
	*	@param	(flag)	�I�t�ɂ������t���O
	*/
	void FalseFlag(Flag flag)
	{
		//		�t���O���I���̎��̓I�t�ɂ���
		m_flag &= ~flag;
	}
};