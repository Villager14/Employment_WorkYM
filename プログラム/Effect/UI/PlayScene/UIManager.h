/*
* @file		UIManager.h
* @brief	UI�}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/StandardShader.h"

class ClockManager;
class CoolTime;
class GameOverManager;
class GameClearManager;
class SpeedLine;
class GameStart;
class CountDown;

class UIManager
{
public:
	//		�R���X�g���N�^
	UIManager(PlayerInformation* playerInformation, GameManager* gameManager);

	//		�f�X�g���N�^
	~UIManager();

	//		��������
	void Initialize();

	//		����
	void Generation();

	//		�X�V����
	void Update();

	//		�I������
	void Finalize();

	void FrontRender();

	void BackRender();

	//		UI�e�N�X�`���̍쐻
	void CreateStandardUITexture();

public:

	enum UIType
	{
		ClockBackGround,		//		���v�̔w�i
		ClockColon,				//		���v�̃R����
		CloolTimeBackGround,	//		�N�[���^�C���̔w�i
		GameOver,				//		�Q�[���I�[�o�[
		GameOverContinue,		//		�Q�[���I�[�o�[�̃R���e�B�j���[
		NextInduction,			//		���̏�Ԃ̗U��
		ScreenRay,				//		�X�N���[���̃��C
		GameClearBarUnder,		//		�Q�[���N���A�̃o�[
		GameClearBarUp,			//		�Q�[���N���A�̃o�[		
		GameClearBackGround,	//		�Q�[���N���A�̔w�i
		GameStartTimeLimit,		//		�Q�[���X�^�[�g�^�C�����~�b�g
		GameStartTimeTen		//		�Q�[���X�^�[�g�^�C�����~�b�g�̓_
	}; 

public:

	//		���v�w�i���W
	const DirectX::SimpleMath::Vector2 CLOCK_BACK_GROUND_POSITION = { 480.0f, 200.0f };

	//		���v���Ԕw�i���W
	const DirectX::SimpleMath::Vector2 CLOCK_BACK_TIME_GROUND_POSITION = { 539.0f, 0.0f };

	//		���̏�ԗU�����W
	const DirectX::SimpleMath::Vector2 NEXT_INDCCTION = { 0.0f, 200.0f };

	//		���b�Z�[�W�o�[��̍��W
	const DirectX::SimpleMath::Vector2 MESSAGE_BER_UP = { 0.0f, 13.0f };

	//		���b�Z�[�W�o�[���̍��W
	const DirectX::SimpleMath::Vector2 MESSAGE_BER_DOWN = { 0.0f, -13.0f };

private:
	//		���v�̔w�i
	std::unique_ptr<ClockManager> m_clockManager;

	//		�N�[���^�C��
	std::unique_ptr<CoolTime> m_coolTime;

	//		�J�E���g�_�E��
	std::unique_ptr<CountDown> m_countDonw;
		
	//		�Q�[���I�[�o�[
	std::unique_ptr<GameOverManager> m_gameOver;

	//		�X�s�[�h���C��
	std::unique_ptr<SpeedLine> m_speedLine;

	//		�Q�[���X�^�[�g
	std::unique_ptr<GameStart> m_gameStart;

	//		�v���C���[�̏����󂯎��
	PlayerInformation* m_playerInformation;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	//		�Q�[���N���A�}�l�[�W���[
	std::unique_ptr<GameClearManager> m_clearManager;

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

public:

	/*
	*	�X�^���_�[�h�V�F�[�_�[���󂯎��
	* 
	*	@return �X�^���_�[�h�V�F�[�_�[���󂯎��
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

	/*
	*	�Q�[���}�l�[�W���[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	�v���C���[�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformation* GetPlayerInformation() { return  m_playerInformation; }
};