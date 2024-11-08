/*
* @file		AnimationManager.h
* @brief	�A�j���[�V�����}�l�[�W���[
* @author	Morita
* @date		2024/08/25
*/


#pragma once

#include "../Bones/BonInformation.h"

#include "../Bones/ModelBones.h"

#include "IAnimation.h"

#include "AnimationInformation.h"

#include "AnimationCommonProcess.h"


#include "State/Player/AttackAnimationState.h"
#include "State/Player/CrouchingStayAnimationState.h"
#include "State/Player/CrouchingWalkAnimationState.h"
#include "State/Player/DashAnimationState.h"
#include "State/Player/DropDeadAnimationState.h"
#include "State/Player/FallAnimationState.h"
#include "State/Player/JumpAnimationState.h"
#include "State/Player/SlidingAnimationState.h"
#include "State/Player/StartAnimationState.h"
#include "State/Player/StayAnimationState.h"
#include "State/Player/UprightAnimationState.h"
#include "State/Player/WalkAnimationState.h"
#include "State/Player/WallJumpAnimationState.h"
#include "State/Player/WallWalkAnimationState.h"
#include "State/Player/WireJumpAnimationState.h"

#include "State/Enemy/HandGunStay.h"
#include "State/Enemy/HandGunStyle.h"

class AnimationManager
{
public:

	//		�L�����N�^�[�^�C�v
	enum CharactorType
	{
		Player,			//		�v���C���[
		CommonEnemy,	//		�ʏ�G�l�~�[
		Result,
		Title,
	};

	enum AnimationState
	{
		Stay,
		Walk,
		CrouchingStay,
		CrouchingWalk,
		Jump,
		Sliding,
		Dash,
		WallWalk,
		WallJump,
		Wire,
		Start,
		Upright,
		Fall,
		Death,
		Attack,
		HandGunStayA,
		HandGunStyleA,
	};

public:

	//		�R���X�g���N�^
	AnimationManager(CharactorType type);

	//		�f�X�g���N�^
	~AnimationManager();

	//		����������
	void Initialize();

	//		�`�揈��
	void Render();

	//		�X�V����
	void Execute(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle,
		float height);

	//		���f���̍쐻
	void CreateModel(bool createHead);

	/*
	*	���f���̓ǂݍ���
	*
	*	@param	(path)		�t�@�C���p�X
	*	@param	(effect)	�G�t�F�N�g�t�@�N�g���[�̃|�C���^
	*	@param	(modelType)	���f���̎��
	*/
	void LoadModel(const wchar_t* path,
		DirectX::EffectFactory* effect);

	/*
	*	�A�j���[�V�����̐؂�ւ�
	*
	*	@param	(IState)
	*/
	void ChangeState(AnimationState State);

	//		�I������
	void Finalize();

private:

	//		�{�[��
	std::unique_ptr<ModelBones> m_bons;

	//		���f��
	std::vector<std::unique_ptr<DirectX::Model>> m_model;

	//		���N���X
	std::unique_ptr<AnimationInformation> m_information;

	//		���ʏ���
	std::unique_ptr<AnimationCommonProcess> m_commonProcess;

	//		�L�����N�^�[�^�C�v
	CharactorType m_charaType;

	//		�A�j���[�V�����̏��
	IAnimation* m_istate;

	//		�A�j���[�V����
	AnimationState m_animationState;

	//		�A�j���[�V�����̏��
	std::unordered_map<AnimationState, std::unique_ptr<IAnimation>> m_animaInformation;

	//		�����f�����쐬���邩�ǂ���
	bool m_createHead;
public:

	/*
	*	�A�j���[�V�����̋��ʏ������󂯎��
	* 
	*	@return ���ʏ���
	*/
	AnimationCommonProcess* GetCommonProcess() { return m_commonProcess.get(); }

	/*
	*	�����󂯎��
	* 
	*	@return ���
	*/
	AnimationInformation* GetInformation() { return m_information.get(); }

	/*
	*	�v���C���[�{�[�����󂯎��
	* 
	*	@return �{�[��
	*/
	ModelBones* GetBons() { return m_bons.get(); }
};