/*
* @file		MenuClose.h
* @brief	���j���[����鎞�̏���
* @author	Morita
* @date		2024/07/11
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class MenuClose : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	()
	*/
	MenuClose(MenuManager* menuManager);

	//		�f�X�g���N�^
	~MenuClose();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	//		���j���[�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	MenuManager* m_menuManager;

	//		�X�P�[��
	float m_scale;

	//		�ړ�
	float m_move;

	float m_mainClose;
};