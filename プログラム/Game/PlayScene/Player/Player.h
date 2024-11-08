/*
* @file		Player.h
* @brief	�v���C���[�̏���
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "Game/PlayScene/CollitionManager/CollitionInformation.h"

#include "Game/PlayScene/Player/PlayerInformationCollition.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "PlayerInformation.h"

#include "Library/Animation/AnimationManager.h"

#include "State/PlayerStay.h"
#include "State/PlayerWalk.h"
#include "State/PlayerCrouching.h"
#include "State/PlayerJump.h"
#include "State/PlayerSliding.h"
#include "State/PlayerDash.h"
#include "State/PlayerSlowTime.h"
#include "State/PlayerWallWalk.h"
#include "State/PlayerWire.h"
#include "State/PlayerWallJump.h"
#include "State/PlayerDeath.h"
#include "State/PlayerStart.h"
#include "State/PlayerGoal.h"
#include "State/PlayerFall.h"

#include "State/PlayerAttack.h"

#include "../ObjectManager/WireObject/WireObjectInformation.h"

#include <unordered_map>

#include "PlayerCommonProcessing.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class Player
{
public:

	//		�R���X�g���N�^
	Player(GameManager* gameManager);

	//		�f�X�g���N�^
	~Player();

	//		����������
	void Initialize();

	//		��������
	void Generation();

	//		�X�V����
	void Update(PlayerCameraInformation* cameraInformation);

	//		���b�V���̍X�V
	void MeshUpdate();

	//		�A�j���[�V�����̍X�V
	void AnimationUpdate();

	//		���f���̕`��
	void ModelRender(PostEffectFlag::Flag flag);

	//		�f�o�b�N�`��
	void DebugRender();

	//		�I������
	void Finalize();

	//		���S���������f����
	void DeathJudgement();

public:

	//		�v���C���[�̏��
	enum PlayerState
	{
		Stay,
		Walk,
		Crouching,
		Jump,
		Sliding,
		Dash,
		WallWalk,
		WallJump,
		Wire,
		Death,
		Start,
		Goal,
		Fall,
	};

public:

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(PlayerState state);

	//		���C���[�̏�ԑJ��
	void ChangeWireState(int index);

private:

	//		�v���C���[�̏�Ԃ̏��
	std::unordered_map<PlayerState, std::unique_ptr<IPlayer>> m_stateInformation;

	//		���݂̏��
	PlayerState m_playerState;

	//		���݂̏��
	IPlayer* m_state;

	//		�v���C���[�̃A�j���[�V�����̏���
	std::unique_ptr<AnimationManager> m_playerAnimation;

	//		�����蔻��̏��
	CollitionInformation* m_collitionInformation;

	//		�����蔻��p�v���C���[�̏��
	std::unique_ptr<PlayerInformationCollition> m_playerInformationCollition;

	//		�v���C���[�̍U��
	std::unique_ptr<PlayerAttack> m_playerAttack;

	//		�v���C���[�̏��
	std::unique_ptr<PlayerInformation> m_information;

	//		�v���C���[�̋��ʏ���
	std::unique_ptr<PlayerCommonProcessing> m_commonProcessing;

	//		�J�����̏��
	PlayerCameraInformation* m_cameraInformation;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	//		���C���[�̏��
	std::vector<WireObjectInformation> *m_wireInformation;

	//		���j���[���g���邩�ǂ���
	bool m_menuUseJudgement;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

public:

	/*
	*	�Q�[���}�l�[�W���[���󂯎��
	* 
	*	@return �Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	�v���C���[�J�����̏��
	* 
	*	@return �J�����̏��
	*/
	PlayerCameraInformation* GetCameraInformation() { return m_cameraInformation; }

	/*
	*	�v���C���[�J�����̏��
	*
	*	@return �J�����̏��
	*/
	void SetCameraInformation(PlayerCameraInformation* information) { m_cameraInformation = information; }


	/*
	*	�����蔻��̏����󂯎��
	* 
	*	@param	(collitionInformation)	�C���X�^���X�̃|�C���^
	*/
	void SetCollitionInformation(CollitionInformation* collitionInformation)
							{ m_collitionInformation = collitionInformation; }

	/*
	*	�����蔻��̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	CollitionInformation* GetCollitionInformation() { return m_collitionInformation; }

	/*
	*	�v���C���[�̋��ʏ���
	* 
	*	@return �C���X�^���̃|���^
	*/
	PlayerCommonProcessing* GetCommonProcessing() { return m_commonProcessing.get(); }

	/*
	*	�����蔻��p����ݒ肷��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformationCollition* GetPlayerInformationCollition() { return m_playerInformationCollition.get(); }

	/*
	*	�v���C���[�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformation* GetInformation() { return m_information.get(); }

	/*
	*	�v���C���[�A�j���[�V�����̃C���X�^���X�̃|�C���^
	* 
	*	@return �|�C���^�̃C���X�^���X
	*/
	AnimationManager* GetAnimation() { return m_playerAnimation.get(); }

	/*
	*	���C���[�̏���ݒ肷��
	* 
	*	@param	(wireInformation)	���C���[�̏��
	*/
	void SetWireInformation(std::vector<WireObjectInformation>* wireInformation) { m_wireInformation = wireInformation; }

	/*
	*	���C���[�����󂯎��
	* 
	*	@return ���C���[�̏��
	*/
	std::vector<WireObjectInformation>* GetWireObjectInformation() { return m_wireInformation; }

	/*
	*	���j���[���g�����Ƃ��ł��邩�ǂ����󂯎��
	*	
	*	return true : �g�����Ƃ��ł���@false : �g�����Ƃ��ł��Ȃ�
	*/
	bool GetMenuUseJugement() { return m_menuUseJudgement; }

	/*
	*	���j���[���g�����Ƃ��ł��邩�ǂ����ݒ肷��
	*
	*	@param	(judgement) true : �g�����Ƃ��ł���@false : �g�����Ƃ��ł��Ȃ�
	*/
	void SetMenuUiseJudgement(bool judgement) { m_menuUseJudgement = judgement; }
 }; 
