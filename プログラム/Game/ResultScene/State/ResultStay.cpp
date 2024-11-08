/*
* @file		ResultStay.cpp
* @brief	���U���g�ҋ@����
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultStay.h"

ResultStay::ResultStay(ResultManager* resultManager)
	:
	m_resultManager(resultManager)
{
}

ResultStay::~ResultStay()
{
}

void ResultStay::Initialize()
{
}

void ResultStay::Update()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Space�܂��͍��N���b�N���������ꍇ��������
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

		//		��Ԃ�؂�ւ���(�����ړ����)
		m_resultManager->ChangeState(ResultManager::State::End);
	}
}

void ResultStay::Render()
{
	//		�]��
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::EvaluationUI);

	//		�J�ڗU���摜
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::
		Button);

	//		�����̕`��
	m_resultManager->GetInformation()->GetRiseNumber()->Render(4.0f);
}

void ResultStay::Finalize()
{
}
