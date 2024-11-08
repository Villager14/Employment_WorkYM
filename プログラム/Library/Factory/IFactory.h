/*
* @file		IFactory
* @brief	�t�@�N�g���[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/08/21
*/

#pragma once

#include "pch.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Game/PlayScene/ObjectManager/ObjectInformation.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Factory.h"

#include "Effect/PostEffect/PostEffectObjectShader.h"

class IFactory
{
public:
	//		����������
	virtual void Initialize(ObjectInformation information) = 0;

	//		�X�V����
	virtual void Update() = 0;

	//		�`�揈��
	virtual void Render(PostEffectFlag::Flag flag,
		PostEffectObjectShader* postEffectObjectShader) = 0;

	//		�I������
	virtual void Finalize() = 0;

	//		�I�u�W�F�N�g�^�C�v
	virtual Factory::Object GetObjectType() = 0;

	//		�I�u�W�F�N�g���b�V�����󂯎��
	virtual ObjectMesh* GetObjectMesh(int index) = 0;

	/*
	*	�|�X�g�G�t�F�N�g�t���O
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	virtual PostEffectFlag* GetPostEffectFlag() = 0;

	//		�f�X�g���N�^
	virtual ~IFactory() = default;
};
