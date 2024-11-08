/*
* @file		WireUseEffect.h
* @brief	���C���[�g�p�G�t�F�N�g
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "../Billboard/BillboardEffect.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class WireUseEffect
{
public:

	//		�R���X�g���N�^
	WireUseEffect(PlayerInformation* m_playerInformation);

	//		�f�X�g���N�^
	~WireUseEffect();

	//		����������
	void Initialize(int size);

	/*
	*	�X�V����
	*
	*	@param	(index)	�v�f��
	*/
	void Update(DirectX::SimpleMath::Vector3 position, int index);

	/*
	*	�r���{�[�h�̍X�V����
	*
	*	@param	(cameraInformation)	�J�����̏��
	*/
	void BillbordUpdate(PlayerCameraInformation* cameraInformation);

	/*
	*	�`�揈��
	*
	*	@param	(cameraVelocity)	�����x�N�g��
	*/
	void Render(DirectX::SimpleMath::Vector3 position, int index,
		PostEffectFlag::Flag flag);

	//		�I������
	void Finalize();

	struct WireStatas
	{
		bool firstJudgement = true;
		bool sclaeChangeJudgement = true;
		bool resetFlag = false;
		float scale = 30.0f;
		float time = 0.0f;
		float maxScale = 0.0f;
	};

	/*
	*	���C���[���g�����ۂ̃��Z�b�g����
	* 
	*	@param	(index)	�v�f��
	*/
	void ResetProcess(int index);

private:
	//		�r���{�[�h�G�t�F�N�g
	std::unique_ptr<BillboardEffect> m_billboardEffect;

	//		�v���C���[�̏��
	PlayerInformation* m_playerInformation;

	//		���C���[�̃X�e�[�^�X
	std::vector<WireStatas> m_wireStatas;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
};
