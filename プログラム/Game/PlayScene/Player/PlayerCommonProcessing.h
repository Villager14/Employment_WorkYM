/*
* @file		PlayerCommonProcessing.h
* @brief	�v���C���[�̋��ʏ����N���X
* @author	Morita
* @date		2024/07/18
*/

#pragma once

class Player;

class PlayerCommonProcessing
{
public:

	PlayerCommonProcessing(Player* player);

	~PlayerCommonProcessing();

	/*
	*	�d�͏���
	*
	*	@param	(weekJudgement)	�ア�d�͂ɂ��邩�ǂ���
	*/
	void Gravity(bool weekJudgement = false);

	//		�����b�V���ɓ������Ă��邩���f����
	bool FloorMeshHitJudgement();

	//		�ǃ��b�V���ɓ������Ă��邩���f����
	bool WallMeshHitJudgement();

	/*
	*	����Ԃɂ���
	*
	*	@param	(firstHeight)	�ŏ��̍���
	*	@param	(endHeight)		�ŏI�I�ȍ���
	*	@param	(speed)			���x
	*/
	void PlayerHeightTransition(const float& firstHeight, const float& endHeight, const float& speed);

	//		���x���
	void SpeedUpperLimit();

	/*
	*	�ړ�����
	*
	*	@param	(keyPressJudgement)	�L�[�����������ǂ���
	*	@return �ړ�����
	*/
	DirectX::SimpleMath::Vector3 Direction(bool* keyPressjudgement);

	/*
	*	�ړ��������
	*
	*	@param (direction) �ړ�����������
	*	@return ����
	*/
	DirectX::SimpleMath::Vector3 MoveDirection
	(const DirectX::SimpleMath::Vector3 direction);

	/*
	*	���C���[�A�N�V���������邩�ǂ���
	*
	*	@returnr ���邩�ǂ��� true : �s�� fales : �s��Ȃ�
	*/
	bool WireActionJudgement();

	//		�Ǒ����ԂɂȂ邩�ǂ���
	void WallWalkJudgement();

	//		�_�b�V���̃N�[���^�C��
	void DashCoolTime();

private:

	Player* m_player;
};