/*
* @file		BackGroundMove.h
* @brief	�w�i�̈ړ�
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class BackGroundMove
{
public:

	//		�R���X�g���N�^
	BackGroundMove();

	//		�f�X�g���N�^
	~BackGroundMove();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�E�B���h�E�T�C�Y
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		DirectX::SimpleMath::Vector4 time;				//		����
	};

private:

	//		�w�i�̑��x
	const float BACK_GROUND_SPEED = 0.1f;

private:

	//		UI�`��}�l�[�W���[
	std::unique_ptr<UIRenderManager> m_uiRenderManager;

	//		����
	float m_time;

	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;
};
