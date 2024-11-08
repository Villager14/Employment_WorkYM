/*
* @file		MenuCommonProcess.h
* @brief	���j���[�̋��ʏ���
* @author	Morita
* @date		2024/08/05
*/

#pragma once

#include "MenuInformation.h"

class MenuCommonProcess
{
public:

	//		�R���X�g���N�^
	MenuCommonProcess(MenuInformation* menuInformation);

	//		�f�X�g���N�^
	~MenuCommonProcess();

	//		���j���[��ESC�{�^���ŕ��鏈��
	bool MenuEscCloseProcess();


	/*
	*	�l�p�̓����蔻��
	* 
	*	@param	(min)	�ŏ��l
	*	@param	(max)	�ő�l
	*	@return true : �������Ă��� false : �������Ă��Ȃ�
	*/
	bool BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);

	/*
	*	�I���������ǂ���
	*
	*	@param	(type)	�I�����Ȃ����j���[�̎��
	*/
	bool ButtonCollider(MenuInformation::MenuType type);

	/*
	*	�X���C�_�[�̏���
	*
	*	@param	(type)	���
	*/
	void SlideProcess(AboveUI::UIType type);

	//		�}�E�X�|�C���^�̏���
	void MousePointa();

private:

	//		���j���[�̏��
	MenuInformation* m_information;
};