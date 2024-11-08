/*
* @file		TitleCommonProcess.h
* @brief	�^�C�g�����ʏ���
* @author	Morita
* @date		2024/08/05
*/

#pragma once

#include "TitleInformation.h"

class TitleCommonProcess
{
public:

	//		�R���X�g���N�^
	TitleCommonProcess(TitleInformation* m_information);

	//		�f�X�g���N�^
	~TitleCommonProcess();

	/*
	*	�ړ�����
	* 
	*	@param	(moveDirection)	�ړ�����ꏊ
	*	@param	(direction)		�ړ��������
	*	@param	(time)			����
	*	@param	(type)			�ړ�����^�C�v
	*/
	void MoveProcess(TitleInformation::MoveDirection moveDirection,
		bool direction, float time, TitleInformation::TitleUIType type);

private:

	/*
	*	���S�����ւ̏���
	*
	*	@bool (direction)	true : ��ֈړ����� false : ���S�ֈړ�����
	*/
	void CentreUP(bool direction, float time, TitleInformation::TitleUIType type);

	/*
	*	���S���牺�ւ̏���
	*
	*	@bool (direction)	true : ���ֈړ����� false : ���S�ֈړ�����
	*/
	void CenterUnder(bool direction, float time, TitleInformation::TitleUIType type);

	/*
	*	���S���牺�ւ̏���
	*
	*	@bool (direction)	true : ���ֈړ����� false : ���S�ֈړ�����
	*/
	void UPUnder(bool direction, float time, TitleInformation::TitleUIType type);

	/*
	*	�V�F�[�_�[�̕`��
	* 
	*	@param	(type)	�`�悷����
	*/
	inline void DrawShader(TitleInformation::TitleUIType type);

	/*
	*	��������
	*	
	*	@param	(time)	����
	*/
	inline void DecreaseValue(float time);

	/*
	*	�㏸����
	*
	*	@param	(time)	����
	*/
	inline void ElevatedValue(float time);

private:

	//		���
	TitleInformation* m_information;

	//		�J�ڗ�(�ړ�)
	float m_move;

	//		�J�ڗ�(�T�C�Y)
	float m_size;

	//		�������W
	DirectX::SimpleMath::Vector2 m_firstPosition;

	//		�ŏI���W
	DirectX::SimpleMath::Vector2 m_endPosition;

	//		�����T�C�Y
	float m_firstSize;

	//		�ŏI�T�C�Y
	float m_endSize;

};
