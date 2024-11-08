/*
* @file		CommonEnemyAttack.h
* @brief	��ʓI�ȓG�̍U��
* @author	Morita
* @date		2024/05/06
*/

#pragma once

#include "../ICommonEnemy.h"

class CommonEnemy;

class CommonEnemyAttack : public ICommonEnemy
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(commonEnemy)	��ԊǗ��N���X�̃|�C���^
	*/
	CommonEnemyAttack(CommonEnemy* commonEnemy);

	//		�f�X�g���N�^
	~CommonEnemyAttack();

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

	//		�U������
	float m_attackTime;
};