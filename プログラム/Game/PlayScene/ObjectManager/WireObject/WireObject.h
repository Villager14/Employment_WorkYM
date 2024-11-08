/*
* @file		FloorObject.h
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Factory/IFactory.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class WireObject : public IFactory
{
public:

	//		�R���X�g���N�^
	WireObject(ObjectManager* objectManager);

	//		�f�X�g���N�^
	~WireObject();

	/*
	*	����������
	*
	*	@param	(position)	���W
	*/
	void Initialize(ObjectInformation information) override;

	//		�X�V����
	void Update() override;

	/*
	*	�`�揈��
	*
	*	@param	(drawMesh)	���b�V���`��̃C���X�^���X�̃|�C���^
	*/
	void Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader) override;

	//		�I������
	void Finalize() override;

	/*
*	�I�u�W�F�N�g�^�C�v���󂯎��
*
*	@return�@�I�u�W�F�N�g�^�C�v
*/
	Factory::Object GetObjectType() override { return Factory::Wire; }


	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return ���b�V���̏��
	*/
	ObjectMesh* GetObjectMesh(int index) override {
		UNREFERENCED_PARAMETER(index);
		return m_objectMesh.get();
	}

	/*
	*	�|�X�g�G�t�F�N�g�t���O
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectFlag* GetPostEffectFlag() override
	{
		return m_postEffectFlag.get();
	}

	//		�f�o�b�N�̕`��
	void DebugRender();

	//		�H�̕`��
	void WingRender(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader);

private:
	//		�H���W1
	DirectX::SimpleMath::Vector3 WING_POSITION_0 = { 4.0f, 5.0f, 3.6f };
	//		�H���W2
	DirectX::SimpleMath::Vector3 WING_POSITION_1 = { 4.2f, 5.0f, -3.0f };
	//		�H���W3
	DirectX::SimpleMath::Vector3 WING_POSITION_2 = { -4.0f, 5.0f, 3.6f };
	//		�H���W4
	DirectX::SimpleMath::Vector3 WING_POSITION_3 = { -4.2f, 5.0f, -3.0f };

	//		���C���[�͈̔�
	float WIRE_RANGE = 120.0f;

	//		�H�̉�]���x
	float WING_ROTATION_SPEED = 10.0f;

private:

	//		���C���[���f��
	std::unique_ptr<DirectX::Model> m_wireModel;

	//		���C���[�͈̔̓��f��
	std::unique_ptr<DirectX::Model> m_wireRangeModel;

	//		�H�I�u�W�F�N�g
	std::unique_ptr<DirectX::Model> m_wingModel;

	//		�I�u�W�F�N�g�̃��b�V��
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		�f�o�b�N�p�̃��[���h���W
	DirectX::SimpleMath::Matrix m_debugWorld;
	
	//		��]
	float m_rotation;

	//		�H�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wingPosition;

	//		�I�u�W�F�N�g�}�l�[�W���[
	ObjectManager* m_objectManager;

	//		�ԍ�
	int m_number;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	//		���W
	DirectX::SimpleMath::Vector3 m_position;
};
