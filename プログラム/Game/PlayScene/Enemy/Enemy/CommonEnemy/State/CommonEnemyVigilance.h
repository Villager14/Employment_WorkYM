/*
* @file		CommonEnemyVigilance.h
* @brief	��ʓI�ȓG�x�����
* @author	Morita
* @date		2024/05/01
*/

#pragma once

#include "../ICommonEnemy.h"

class CommonEnemy;

class CommonEnemyVigilance : public ICommonEnemy
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(commonEnemy)	��ԊǗ��N���X�̃|�C���^
	*/
	CommonEnemyVigilance(CommonEnemy* commonEnemy);

	//		�f�X�g���N�^
	~CommonEnemyVigilance();

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

	//		�N�[���^�C��
	float m_coolTime;
};