/*
* @file		CommonEnemyCharge.h
* @brief	��ʓI�ȓG�̃`���[�W
* @author	Morita
* @date		2024/05/06
*/

#pragma once

#include "../ICommonEnemy.h"

class CommonEnemy;

class CommonEnemyCharge : public ICommonEnemy
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(commonEnemy)	��ԊǗ��N���X�̃|�C���^
	*/
	CommonEnemyCharge(CommonEnemy* commonEnemy);

	//		�f�X�g���N�^
	~CommonEnemyCharge();

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

	//		���ߎ���
	float m_chargeTime;
};