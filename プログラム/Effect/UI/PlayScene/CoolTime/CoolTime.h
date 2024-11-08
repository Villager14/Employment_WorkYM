/*
* @file		CoolTime.h
* @brief	�N�[���^�C��
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Library/Shader/UIRenderManager.h"

#include "../UIManager.h"

class CoolTime
{
public:

	//		�R���X�g���N�^
	CoolTime(UIManager* uiManager);

	//		�f�X�g���N�^
	~CoolTime();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	*	
	*	�v���C���[�̏����󂯂Ƃ�
	*/
	void Update(PlayerInformation* playerInformation);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		�����̕`��
	void NumberView();

private:

	enum State
	{
		None,		//		�����Ȃ����
		Reduce,		//		���炷���
		Increase	//		���₷���
	};

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�A�X�y�N�g��
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		DirectX::SimpleMath::Vector4 number;			//		����
	};

	//		�R���X�g�o�b�t�@��]
	struct ConstBufferCircle
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 rotation;
	};


private:

	//		�����̒��S�̍��W
	const float NUMBER_CENTER_POSITION = 1179.0f;

	//		�����̊Ԋu
	const float NUMBER_INTERVAL = 30.0f;

	//		�N�[���^�C���̍��W
	const DirectX::SimpleMath::Vector2 COOL_TIME_POSITION = { 270.0f, 0.0f };

private:

	//		UI�}�l�[�W���̃C���X�^���X�̃|�C���^
	UIManager* m_uiManager;

	//		�p�x
	float m_angle;

	//		����
	float m_time;

	//		�p�[�Z���g
	float m_ratio;

	//		�N�[���^�C���ɓ��������ǂ������f����
	bool m_coolTimeJudgement;

	//		���
	State m_state;

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_coolTimeNumberShader;

	//		��]�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_coolTImeShader;

	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;

	//		��]�R���X�g�o�b�t�@
	ConstBufferCircle circleBuffer;
};
