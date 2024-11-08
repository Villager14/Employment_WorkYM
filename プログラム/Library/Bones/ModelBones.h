/*
* @file		ModelBones.h
* @brief	���f���̃{�[��
* @author	Morita
* @date		2024/08/26
*/

#pragma once

#include "BonInformation.h"

class ModelBones
{
public:

	//		�R���X�g���N�^
	ModelBones(bool createHead = false, bool createGun = false);

	//		�f�X�g���N�^
	~ModelBones();

	//		������
	void Initialize();

	/*
	*	�{�[���̍쐬
	*
	*	@param	(position)	���W
	*	@param	(length)	�{�[���̒���
	*	@paarm	(type)		���g�̃I�u�W�F�N�g�^�C�v
	*	@param	(parent)	�e�I�u�W�F�N�g�^�C�v
	*/
	void CrateBons(DirectX::SimpleMath::Vector3 position,
		float length, BonsType type,
		BonsType parent = BonsType::Empty);

	/*
*	���[���h���v�Z����(�ċA����)
*
*	@param	(world)		���[���h�s��̃|�C���^
*	@param	(modelType)	���f���̎��
*/
	BonsType ParentProcess(DirectX::SimpleMath::Matrix* world, BonsType modelType);

	enum AnimationType
	{
		Start,			//		�X�^�[�g
		Walk,			//		����
		Stay,			//		�ҋ@
		Jump,			//		�W�����v
		Dash,			//		�_�b�V��
		CrouchingStop,	//		���Ⴊ�ݒ�~
		CrouchingWalk,	//		���Ⴊ�݈ړ�
		Sliding,		//		�X���C�f�B���O
		WallWalk,		//		�Ǖ���
		WallJump,		//		�ǃW�����v
		WireJump,		//		���C���[�W�����v
		Empty
	};

	std::vector<PlayerBonsInformation>* GetBonesInformation() { return &m_bonesInformation; }

private:

	std::vector<std::unique_ptr<DirectX::Model>> m_playerModel;

	//		�p�x
	float rotation;

	//		�o�ߎ���
	float m_elapsedTime;

	std::vector<PlayerBonsInformation> m_bonesInformation;

	//		�A�j���[�V�����̎��
	AnimationType m_animationType;
};