

#pragma once

#include "../UIManager.h"

#include "Library/Shader/UIRenderManager.h"

class SpeedLine
{
public:

	SpeedLine(UIManager* uiManager);

	~SpeedLine();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�A�X�y�N�g��
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		DirectX::SimpleMath::Vector4 time;				//		����
		float backTime = 0.0f;
		DirectX::SimpleMath::Vector3 pad;
		float alphaPower = 0.0f;
		DirectX::SimpleMath::Vector3 pad2;
	};

private:

	const float LINE_LENGTH = 0.1f;

	//		�Œᑬ�x
	const float MINIMUM_SPEED = 40.0f;

	//		�ō����x
	const float MAXIMUM_SPEED = 110.0f;

	//		�Œ�A���t�@�p���[
	const float MIN_ALPHA_POWER = 0.5f;

	//		�ō��A���t�@�p���[
	const float MAX_ALPHA_POWER = 0.7f;

	//		���C�Œᑬ�x
	const float RAY_SPEED_MIN = 1.5f;

	//		���C�ō����x
	const float RAY_SPEED_MAX = 3.0f;


private:

	//		UI�}�l�[�W���̃C���X�^���X�̃|�C���^
	UIManager* m_uiManager;

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;
	
	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;

	//		����
	float m_time;

	//		�O����
	float m_frontTime;

	//		��뎞��
	bool frontFlag;

	//		���x
	float m_speed;

	//		�w�i�̑��x
	float m_backTime;
};