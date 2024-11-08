/*
* @file		AboveUI.h
* @brief	UI�̏㏸����
* @author	Morita
* @date		2024/07/09
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class MenuSelect
{
public:

	//		�R���X�g���N�^
	MenuSelect();

	//		�f�X�g���N�^
	~MenuSelect();

	//		����������
	void Initialize();
public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
		DirectX::SimpleMath::Vector4 time;					//		����
	};

private:

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	float m_time;

public:

	/*
	*	�`�揈��
	*
	*	@param	(type)	�`�悷��UI�̎��
	*/
	void Render(DirectX::SimpleMath::Vector2 position);

	//		���Ԃ̃��Z�b�g
	void TimeReset() { m_time = 0.0f; };
};