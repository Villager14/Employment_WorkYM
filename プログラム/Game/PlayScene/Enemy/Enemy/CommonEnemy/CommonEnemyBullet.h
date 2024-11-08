/*
* 
* @file		CommonEnemyBullet.h
* @brief	��ʓI�ȓG�̒e
* @author	Morita
* @date		2024/05/06
*/

#pragma once



class CommonEnemyBullet
{
public:

	//		�R���X�g���N�^
	CommonEnemyBullet();

	//		�f�X�g���N�^
	~CommonEnemyBullet();

	//		����������
	void Initialize();

	//		�X�V����
	void Update(float timeSpeed);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	//		���˂��Ă��邩�ǂ���
	bool m_firingJudgement;

	//		���ˍ��W
	DirectX::SimpleMath::Vector3 m_position;

	//		�ړ�����
	DirectX::SimpleMath::Vector3 m_velocity;

	//		�o�ߎ���
	float m_elapsedTime;

	//		���f��
	std::unique_ptr<DirectX::Model> m_model;

public:

	/*
	*	���˂��Ă��邩�ǂ����󂯎��
	* 
	*	@return true : ���˂��Ă��� false : ���˂��Ă��Ȃ�
	*/
	bool GetFiringJudgement() { return m_firingJudgement; }

	/*
	*	���˂��Ă��邩�ǂ�����ݒ肷��
	* 
	*	@param	(judgement)	true : ���˂��Ă��� false : ���˂��Ă��Ȃ�
	*/
	void SetFiringJudgement(bool judgement) { m_firingJudgement = judgement; }

	/*
	*	�e�̏���ݒ肷��
	*	
	*	@param	(position)	���ˍ��W
	*	@param	(velocity)	���˕���
	*/
	void SetBulletInformation(const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& velicity)
	{
		m_position = position;
		m_velocity = velicity;
		m_velocity.Normalize();
	}

	/*
	*	���W���󂯎��
	* 
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
};