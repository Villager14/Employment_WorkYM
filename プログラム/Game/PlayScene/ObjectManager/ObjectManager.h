/*
* @file		ObjectManager.h
* @brief	�I�u�W�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "WireObject/WireObjectInformation.h"

#include "../GameManager/GameManager.h"

#include "Library/Factory/Factory.h"

#include "Library/Factory/IFactory.h"

#include "LoadingObjectInformation.h"

#include "ObjectInformation.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/PostEffect/PostEffectObjectShader.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

class BackGroundObject;

class ObjectManager
{
public:

	//		�R���X�g���N�^
	ObjectManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~ObjectManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	�`�揈��
	* 
	*	@param	(cameraVelocity)	�����x�N�g��
	*/
	void Render(PlayerCameraInformation* cameraInformation,
				DirectX::SimpleMath::Vector3 cameraPosition,
				PostEffectFlag::Flag flag, PostEffectObjectShader* objectShader);

	//		�I������
	void Finalize();

	/*
	*	�I�u�W�F�N�g�̍��W
	* 
	*	@param	(position)	�I�u�W�F�N�g�̍��W
	*	@return true �J�����O���� false : �J�����O���Ȃ�
	*/
	bool Culling(DirectX::SimpleMath::Vector3 position, float length);

	/*
	*	���C���[�̏��I�u�W�F�N�g���쐬����
	* 
	*	@param	(index)			�v�f
	*	@param	(wireNumber)	���C���[�̔ԍ�
	*/
	void CreateWireInformation(int index, int *wireNumber);

private:
	//		�w�i�I�u�W�F�N�g
	std::unique_ptr<BackGroundObject> m_backGroundObject;

	//		�I�u�W�F�N�g�̃��b�V��
	std::vector<ObjectMesh*> m_objectMesh;

	//		���b�V����`�悷��
	std::unique_ptr<DrawMesh> m_drawMesh;
	 
	//		�J���������x�N�g��
	PlayerCameraInformation* m_cameraInformation;

	//		�J�����̍��W
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	//		���C���[�I�u�W�F�N�g�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wireObjectPosition;

	//		���C���[�̏��
	std::vector<WireObjectInformation> m_wireInformation;

	//		�t�@�N�g���[
	std::unique_ptr<Factory> m_factory;

	//		�t�@�N�g���[�I�u�W�F�N�g
	std::vector<std::unique_ptr<IFactory>> m_factoryObject;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	//		�I�u�W�F�N�g�̏��̓ǂݍ���
	std::unique_ptr<LoadingObjectInformation> m_loadObjectInformation;

	//		�I�u�W�F�N�g�̏��
	std::vector<ObjectInformation> m_objectInformation;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

public:


	/*
	*	�v���C���[�̍��W���󂯎��
	* 
	*	@return ���W
	*/
	DirectX::SimpleMath::Vector3 GetPlayerPosition() { return m_playerPosition; }

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	* 
	*	@return �I�u�W�F�N�g���b�V���̃C���X�^���X�̃|�C���^
	*/
	std::vector<ObjectMesh*> GetMesh() { return m_objectMesh; }

	/*
	*	���C���[�I�u�W�F�N�g�̏����󂯎��
	* 
	*	@return	���C���[���
	*/
	std::vector<WireObjectInformation>* GetUseWireInformation() { return &m_wireInformation; }

	/*
	*	�Q�[���}�l�[�W���[���󂯎��
	* 
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	PlayerCameraInformation* GetCameraInformation() { return m_cameraInformation; }
};
