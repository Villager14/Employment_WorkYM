/*
* @file		CommonEnemy.h
* @brief	��ʓI�ȓG
* @author	Morita
* @date		2024/05/01
*/

#pragma once

#include "State/CommonEnemyStay.h"
#include "State/CommonEnemyVigilance.h"
#include "State/CommonEnemyCharge.h"
#include "State/CommonEnemyAttack.h"

#include "Library/Animation/AnimationManager.h"

#include "../EnemyInformation.h"

#include "CommonEnemyIntarface.h"

class CommonEnemy
{
public:

	//		�R���X�g���N�^
	CommonEnemy(EnemyInformation enemyInformation);

	//		�f�X�g���N�^
	~CommonEnemy();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	*
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@param	(timeSpeed)			���Ԃ̑��x
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition,
		float timeSpeed);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();


public:

	enum State
	{
		Stay,		//		�ҋ@
		Vigilance,	//		�x��
		Charge,		//		�`���[�W
		Attack,		//		�U��
	};

private:

	//		���
	ICommonEnemy* m_istate;

	//		��Ԃ̏��
	std::unordered_map<State, std::unique_ptr<ICommonEnemy>> m_stateintarface;

	State m_state;

	//		�v���C���[�A�j���[�V����
	std::unique_ptr<AnimationManager> m_playerAnimation;

	//		���
	std::unique_ptr<CommonEnemyIntarface> m_intarface;

	//		���E�ɓ����Ă��邩�ǂ���
	bool m_viewJudgement;

	//		�G�l�~�[�̏��
	EnemyInformation m_enemyInformation;
public:

	/*
	*	��Ԃ�؂�ւ���
	*
	*	@param	(nextState)	���̏��
	*/
	void ChangeState(State nextState)
	{
		//		������Ԃ̏ꍇ���������Ȃ�
		if (m_state == nextState) return;

		//���݂̏�Ԃ̏I������
		m_istate->Finalize();

		//���̏�Ԃ�؂�ւ���
		m_state = nextState;

		//���̏�Ԃ�؂�ւ���
		m_istate = m_stateintarface[m_state].get();

		//���̏�Ԃ̏���������
		m_istate->Initialize();
	}

	/*
	*	�v���C���[�A�j���[�V����
	*
	*	@return �v���C���[�A�j���[�V����
	*/
	AnimationManager* GetPlayerAnimation() { return m_playerAnimation.get(); }

	/*
	*	�U�����W���󂯎��
	*
	*	@return ���W
	*/
	DirectX::SimpleMath::Vector3 GetAttackPosition()
	{
		DirectX::SimpleMath::Vector3 attackPosition = m_intarface->GetPosition();

		attackPosition.y += 5.0f;

		return attackPosition;
	}

	/*
	*	�����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	CommonEnemyIntarface* GetInformation() { return m_intarface.get(); }


	bool FieldOfVision();
};