/*
* @file		FadeIn.h
* @brief	�t�F�[�h�̏���
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/UIRenderManager.h"

class FadeIn
{
public:

	FadeIn();

	~FadeIn();

	void Initialize();

	void Update(GameManager* gameManager);

	void Render();

	void Finalize();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		����
	float m_time;

	//		�ҋ@����
	float m_stayTime;

	//		�t�F�[�h�C�������邩�ǂ������f����
	bool m_fadeinResetJudgement;

	//		�t�F�[�h�A�E�g�����邩�ǂ������f����
	bool m_fadeoutResetJudgement;

	//		���߂̃t�F�[�h�C�����ǂ���
	bool m_firstJudgement;

	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;

	//		�t�F�[�h�̕`��
	std::unique_ptr<UIRenderManager> m_fadeRender;
};
