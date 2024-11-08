/*
* @file		CollitionInformation.h
* @brief	�����蔻��̏��
* @author	Morita
* @date		2024/05/16
*/

#pragma once

class CollitionInformation
{
public:

	//		�R���X�g���N�^
	CollitionInformation();

	//		�f�X�g���N�^
	~CollitionInformation();

	//		�����蔻��̏����N���A����
	void Clear();

	/*
	*	�����b�V���̏��
	* 
	*	@param	(floorHitPosition)	���ɓ��������|�C���g
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void FloorMeshInformation(
		const std::vector<DirectX::SimpleMath::Vector3>& floorhitPoint,
		const std::vector<DirectX::SimpleMath::Vector3>& floorNormalize,
		const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	�ǃ��b�V���̏��
	* 
	* 
	*/
	DirectX::SimpleMath::Vector3 WallMeshInformation(
		const std::vector<DirectX::SimpleMath::Vector2>& wallHitVelocity,
		const std::vector<DirectX::SimpleMath::Vector3>& wallHitNormalize,
		const std::vector<DirectX::SimpleMath::Vector3>& wallWalkPosition,
		const DirectX::SimpleMath::Vector3& playerPosition);

	//		�I������
	void Finalize();

private:

	//		���ɓ��������|�C���g
	std::vector<DirectX::SimpleMath::Vector3> m_floorhitPoint;

	//		���ɓ��������@��
	std::vector<DirectX::SimpleMath::Vector3> m_floorNormalize;

	//		�ǂɓ��������x���V�e�B���󂯎��
	std::vector<DirectX::SimpleMath::Vector2> m_wallHitVelocity;

	//		�ǂɓ��������@�����󂯎��
	std::vector<DirectX::SimpleMath::Vector3> m_wallHitNormalize;

	//		�Ǖ������̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wallWalkPosition;

	//		���ɓ������Ă��邩
	bool m_ceilingHitJudgement;
public:

	/*
	*	���b�V�����̓��������|�C���g���󂯎��
	*
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetFloorMeshHitPoint()
	{ return m_floorhitPoint; }

	/*
	*	���b�V�����̓��������@�����󂯎��
	* 
	*	@return �@��
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetFloorMeshHitNormalize()
	{return m_floorNormalize;}


	/*
	*	���b�V���̕ǂ̓��������x�N�g�����󂯎��
	*
	*	@return �x�N�g��
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetWallHitVelocity() { return m_wallHitVelocity; }


	/*
	*	���b�V���ǂɓ��������@�����󂯎��
	*
	*	@return �@��
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetMeshWallNormalize() { return m_wallHitNormalize; }

	/*
	*	�Ǖ������̃v���C���[�̍��W���󂯎��
	*
	*	@return �Ǖ������̃v���C���[�̍��W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallWalkPlayerPosition() { return m_wallWalkPosition; }

	bool GetCeilingJudgement() { return m_ceilingHitJudgement; }

	void SetCeilingJudgement(bool judgement) { m_ceilingHitJudgement = judgement; }
};
