/*
* @file		PlayerCameraManager.h
* @brief	�v���C���[�̃J�����̃}�l�[�W���[
* @author	Morita
* @date		2024/05/08
*/

#pragma once

#include "IPlayerCamera.h"

#include "State/DebugCamera.h"
#include "State/PlayerCamera.h"
#include "State/PlayerWallWalkCamera.h"
#include "State/PlayerStartCamera.h"
#include "State/PlayerDeathCamera.h"
#include "State/PlayerCameraStop.h"
#include "State/PlayerGoalCamera.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "PlayerCameraInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include <unordered_map>

class DebugCamera;
class PlayerCamera;
class PlayerWallWalkCamera;
class PlayerStartCamera;
class PlayerDeathCamera;
class PlayerCameraStop;
class PlayerGoalCamera;


class PlayerCameraManager
{
public:
	//		�R���X�g���N�^
	PlayerCameraManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~PlayerCameraManager();

	//		����������
	void Initialize(PlayerInformation* playerInformation);

	/*
	*	�X�V����
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update();

	//		�I������
	void Finalize();

	//		�J�����̈ړ�����
	void CameraMove();

	//		����p
	void ViewingAngle();

	//		����p�̍X�V
	void ViewAngleUpdate(PlayerInformation* playerInformation);

public:

	//		�J�����̃^�C�v
	enum CameraType
	{
		Debug,
		Standard,
		WallWalk,
		Start,
		Stop,
		Goal,
		Death,
	};

private:

	//		���
	IPlayerCamera* m_state;

	//		�J�����̏��
	std::unique_ptr<PlayerCameraInformation> m_information;

	//		�J�����p�v���C���[�̏��
	PlayerInformation* m_playerInformation;
	
	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	//		�h���N���X�̊i�[
	std::unordered_map<CameraType, std::unique_ptr<IPlayerCamera>> m_stateInformation;

	//		���݂̃J�����^�C�v
	CameraType m_cameraType;

	//		���݂̎���p
	float m_nowViewAngle;

	//		�J�n���̕��@
	float m_startDirection;

public:
	/*
	*	�J�����̏�Ԃ̐؂�ւ�
	* 
	*	@param	(type)	�J�����̎��
	*/
	void ChangeState(CameraType type);


	/*
	*	�Q�[���}�l�[�W���[���󂯎��
	* 
	*	@return �Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	�J�����̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerCameraInformation* GetInformation() { return m_information.get(); }
	
	/*
	*	�v���C���[�̏����󂯎��
	* 
	*	@return �v���C���[�̏��
	*/
	PlayerInformation* GetPlayerInformationCamera() { return m_playerInformation; }

	/*
	*	�J�n���̕��@��ݒ肷��
	* 
	*	@param	(direction)	�p�x
	*/
	void SetStartDirection(float direction) { m_startDirection = direction; }

	/*
	*	�J�n���̕������󂯎��
	* 
	*	@return �p�x
	*/
	float GetStartDirection() { return m_startDirection; }
};
