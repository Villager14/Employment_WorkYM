/*
* @file		BulletCollition.h
* @brief	�e�̓����蔻��
* @author	Morita
* @date		2024/05/06
*/

#pragma once

class BulletCollition
{
public:

	//		�R���X�g���N�^
	BulletCollition();

	//		�f�X�g���N�^
	~BulletCollition();

	void Initialize();

	/*
	*	�����蔻��
	*
	*	@param	(playerPosition)			�v���C���[�̍��W
	*	@param	(playerHeadPosition)		�v���C���[�̓��̍��W
	*	@param	(bulletPosition)			�e�̍��W
	*/	
	bool Collition(const DirectX::SimpleMath::Vector3& playerPosition,
		const DirectX::SimpleMath::Vector3& playerHeadPosition,
		const std::vector<DirectX::SimpleMath::Vector3>& bulletPosition);

private:


};