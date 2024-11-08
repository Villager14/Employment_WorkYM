/*
* @file		GameStart.h
* @brief	�Q�[���X�^�[�g�}�l�[�W���[
* @author	Morita
* @date		2024/10/20
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "../UIManager.h"

#include "Library/Shader/UIRenderManager.h"

class GameStart
{
public:
	//		�R���X�g���N�^
	GameStart(GameManager* gameManager, UIManager* uiManager);

	//		�f�X�g���N�^
	~GameStart();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();
	
	//		�����̕`��
	void NumberView();

	/*
	*	�X���[�J�E���g�`��
	* 
	*	@return true : �J�E���g�� false : �J�E���g���Ă��Ȃ�
	*/
	bool ThreeCountView();

	//		�^�C�����~�b�g�̈ړ�����
	bool TimeLimitMove();

	//		�^�C�����~�b�g�ԍ��̃����_������
	bool TimeLimitNumberRandom();

	//		�X���[�J�E���g�̏���
	void ThreeCountProcess();

	//		�ԍ��T�C�Y����
	bool NumberSizeTime();
public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�A�X�y�N�g��
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		DirectX::SimpleMath::Vector4 number;			//		����
	};

private:


	//		�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	GameManager* m_gameManager;

	//		UI�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	UIManager* m_uiManager;

	//		�����̕`��
	std::unique_ptr<UIRenderManager> m_numberRender;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�o�ߎ���
	float m_elapsedTime;

	//		�ҋ@����
	float m_stayTime;

	//		�ԍ�
	int m_number;

	//		�����̍X�V�p�x
	float m_numberUpdateFrequency;

	//		�ԍ��o�ߎ���
	float m_numberElapsedTime;

	//		�ԍ�����
	float m_numberTime;

	//		��������
	float m_limitTime;

	//		���~�b�g�������s�����ǂ���
	bool m_limitJudgement;

	//		�ԍ��ҋ@����
	float m_numberStayTime;

	//		�X���[�J�E���g�o�ߎ���
	float m_threeCountElapsedTime;

	//		�ԍ��T�C�Y����
	float m_numberSizeTime;

	//		�X���[�J�E���g�ԍ�
	int m_threeCountNumber;

	//		�I�����邩�ǂ���
	bool m_endJudgement;
};