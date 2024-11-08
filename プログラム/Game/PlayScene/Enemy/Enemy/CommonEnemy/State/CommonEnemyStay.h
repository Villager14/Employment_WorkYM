/*
* @file		CommonEnemyStay.h
* @brief	��ʓI�ȓG�ҋ@���
* @author	Morita
* @date		2024/05/01
*/

#pragma once

#include "../ICommonEnemy.h"

class CommonEnemy;

class CommonEnemyStay : public ICommonEnemy
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(commonEnemy)	��ԊǗ��N���X�̃|�C���^
	*/
	CommonEnemyStay(CommonEnemy* commonEnemy);

	//		�f�X�g���N�^
	~CommonEnemyStay();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:
	//		��ԊǗ��N���X�̃|�C���^
	CommonEnemy* m_commonEnemy;

	
};