/*
* @file		PlayerInformationCollition
* @brief	�����蔻��p�v���C���[�̏��
* @author	Morita
* @date		2024/05/16
*/

#pragma once

#include "pch.h"

class PlayerInformationCollition
{
public:
	//		�R���X�g���N�^
	PlayerInformationCollition()
	:
		m_slidingJudgement(false)
	{};

	//		�f�X�g���N�^
	~PlayerInformationCollition() {};


private:

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		�v���C���[�̍���
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		�X���C�f�B���O�����Ă��邩�ǂ���
	bool m_slidingJudgement;

	//		�ǈړ����̖@��
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;
	
public:

	/*
	*	�v���C���[�̍��W���󂯎��
	* 
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerPosition() { return m_playerPosition; }

	/*
	*	�v���C���[�̍��W��ݒ肷��
	* 
	*	@param	(position)	���W
	*/
	void SetPlayerPosition(const DirectX::SimpleMath::Vector3& position) { m_playerPosition = position; }

	/*
	*	�v���C���[�̍������󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerHeight() { return m_playerHeight; }

	/*
	*	�v���C���[�̍�����ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetPlayerHeight(const DirectX::SimpleMath::Vector3& position) { m_playerHeight = position; }

	/*
	*	�ǈړ����̖@�����󂯎��
	*
	*	@return �@��
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	�ǈړ����̖@����ݒ肷��
	*
	*	@param	(normalize)	�@��
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	�X���C�f�B���O�����Ă��邩�󂯎��
	*	
	*	@return true : �X���C�f�B���O���Ă��� false : �X���C�f�B���O���Ă��Ȃ�
	*/
	bool GetSlidingJudgement() { return m_slidingJudgement; }

	/*
	*	�X���C�f�B���O���Ă��邩�ǂ����ݒ肷��
	* 
	*	@parma	(judgement)	true : �X���C�f�B���O���Ă��� false : �X���C�f�B���O���Ă��Ȃ�
	*/
	void SetSlidingJudgement(bool judgement) { m_slidingJudgement = judgement; }

};


