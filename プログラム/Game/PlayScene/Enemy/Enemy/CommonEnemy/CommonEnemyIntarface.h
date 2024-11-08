/*
* @file		CommonEnemyIntarface.h
* @brief	���ʂ̓G�̏��
* @author	Morita
* @date		2024/08/26
*/

#pragma once

#include "pch.h"

class CommonEnemyIntarface
{
public:

	//		�R���X�g���N�^
	CommonEnemyIntarface()
		:
		m_rotation(0.0f),
		m_attackJudgement(false),
		m_timeSpeed(0.0f),
		m_viewLength(20.0f)
	{};

	//		�f�X�g���N�^
	~CommonEnemyIntarface() {};

private:

	//		�p�x
	float m_rotation;

	//		�U�����邩�ǂ���
	bool m_attackJudgement;

	//		���Ԃ̑��x
	float m_timeSpeed;

	//		�U���������
	DirectX::SimpleMath::Vector3 m_attakDirection;

	//		���W
	DirectX::SimpleMath::Vector3 m_position;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	float m_viewLength;

	//		��]�ʁi�J�n�j
	DirectX::SimpleMath::Quaternion m_startQuotanion;

	//		��]�ʁi�I���j
	DirectX::SimpleMath::Quaternion m_endQuotanion;

public:


	/*
	*	���W���󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	/*
	*	���W��ݒ肷��
	*
	*/
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	/*
	*	�p�x��ݒ肷��
	*
	*	@param	(rotation)	�p�x
	*/
	void SetRotation(float rotation) { m_rotation = rotation; }

	/*
	*	�p�x���󂯎��
	*
	*	@return �p�x
	*/
	float GetRotation() { return m_rotation; }

	/*
	*	�U�����邩�ǂ������󂯎��
	*
	*	@return true : �U������ false : �U�����Ȃ�
	*/
	bool GetAttackJudgement() { return m_attackJudgement; }

	/*
	*	�U�����邩�ǂ����ݒ肷��
	*
	*	@param	(judgement)	true : �U������ false : �U�����Ȃ�
	*/
	void SetAttackJudgement(bool judgement) { m_attackJudgement = judgement; }

	/*
	*	�U�����������ݒ肷��
	*
	*	@param	(direction)	����
	*/
	void SetAttackDirection(const DirectX::SimpleMath::Vector3& direction) { m_attakDirection = direction; }

	/*
	*	�U������������󂯎��
	*
	*	@return ����
	*/
	const DirectX::SimpleMath::Vector3& GetAttackDirection() { return m_attakDirection; }

	/*
	*	���Ԃ̑��x���󂯎��
	*
	*	@return ���x
	*/
	float GetTimeSpeed() { return m_timeSpeed; }

	/*
	*	���Ԃ̑��x��ݒ肷��
	*
	*	@param	(time)	����
	*/
	void SetTimeSpeed(float time) { m_timeSpeed = time; }

	/*
	*	�v���C���[�̍��W���󂯎��
	*
	*	@return ���W
	*/
	DirectX::SimpleMath::Vector3 GetPlayerPosition() { return m_playerPosition; }

	/*
	*	�v���C���[�̍��W��ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetPlayerPosition(DirectX::SimpleMath::Vector3 position) { m_playerPosition = position; }

	/*
	*	�����̒������󂯎��
	* 
	*	@return ����
	*/
	float GetViewLength() { return m_viewLength; }





};