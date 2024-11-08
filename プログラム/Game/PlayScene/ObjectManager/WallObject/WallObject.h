/*
* @file		FloorObject.h
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Library/Factory/IFactory.h"

#include "Library/Factory/Factory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Shader/ObjectShaderManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class WallObject : public IFactory
{
public:

	//		�R���X�g���N�^
	WallObject(ObjectManager* objectManager);

	//		�f�X�g���N�^
	~WallObject();

	/*
	*	����������
	*
	*	@param	(position)	���W
	*/
	void Initialize(ObjectInformation information) override;

	//		�X�V����
	void Update() override;

	//	�`�揈��
	void Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)override ;

	//		�I������
	void Finalize() override;

	/*
	*	�I�u�W�F�N�g�^�C�v���󂯎��
	*
	*	@return�@�I�u�W�F�N�g�^�C�v
	*/
	Factory::Object GetObjectType() override { return Factory::Wall; }


	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return ���b�V���̏��
	*/
	ObjectMesh* GetObjectMesh(int index) override {
		UNREFERENCED_PARAMETER(index);
		return m_objectMesh.get(); }


	//		���f���̕`��
	void LoadModel(ObjectInformation information);

	/*
	*	�|�X�g�G�t�F�N�g�t���O
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectFlag* GetPostEffectFlag() override
	{
		return m_postEffectFlag.get();
	}
public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 Time;				//		����
	};

private:

	//		�����f��
	std::unique_ptr<DirectX::Model> m_wallModel;

	//		�I�u�W�F�N�g�̃��b�V��
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		�I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	ObjectManager* m_objectManager;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�I�u�W�F�N�g�V�F�[�_�[
	std::unique_ptr<ObjectShaderManager> m_objectShader;

	//		����
	float m_time;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	//		���W
	DirectX::SimpleMath::Vector3 m_position;

public:

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return �C���X�^���X
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
