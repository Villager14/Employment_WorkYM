/*
* @file		GriderObject.h
* @brief	�j�ӃI�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/08/09
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Library/Factory/IFactory.h"

#include "Library/Factory/Factory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class GriderObject : public IFactory
{
public:

	//		�R���X�g���N�^
	GriderObject(ObjectManager* objectManager);

	//		�f�X�g���N�^
	~GriderObject();

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
	*	�I�u�W�F�N�g���b�V���̍쐻
	* 
	*	@param	(position)	���W
	*/
	void CreateObjectMesh();

	/*
	*	�I�u�W�F�N�g�^�C�v���󂯎��
	* 
	*	@return�@�I�u�W�F�N�g�^�C�v
	*/
	Factory::Object GetObjectType() override { return Factory::Grider; }


	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return ���b�V���̏��
	*/
	ObjectMesh* GetObjectMesh(int index) override { return m_objectMesh[index].get(); }

	/*
	*	�|�X�g�G�t�F�N�g�t���O
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectFlag* GetPostEffectFlag() override
	{
		return m_postEffectFlag.get();
	}
private:

	//		�j�ӃI�u�W�F�N�g���f���i��]�j
	std::unique_ptr<DirectX::Model> m_griderRotationObject;

	//		�j�ӃI�u�W�F�N�g���f���i�y��j
	std::unique_ptr<DirectX::Model> m_griderObject;

	//		�I�u�W�F�N�g�̃��b�V��
	std::vector<std::unique_ptr<ObjectMesh>> m_objectMesh;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		��]��
	DirectX::SimpleMath::Quaternion m_rotation;

	float m_rog;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_floorPS;

	// �e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	//		���W
	DirectX::SimpleMath::Vector3 m_position;

	ObjectManager* m_objectManager;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
};
