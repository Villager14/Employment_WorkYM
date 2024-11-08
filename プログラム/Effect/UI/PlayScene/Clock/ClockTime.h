/*
* @file		ClockTime.h
* @brief	UI���v�̐���
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

#include "Game/PlayScene/GameManager/GameManager.h"

class ClockTime
{
public:

	//		�R���X�g���N�^
	ClockTime(GameManager* gameManager);

	//		�f�X�g���N�^
	~ClockTime();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(elapsedTime)	�o�ߎ���
	*/
	void Update(float elapsedTime);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�A�X�y�N�g��
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		DirectX::SimpleMath::Vector4 number;			//		����
	};

private:

	//		��(�\�̈�)�̍��Wminutes
	const DirectX::SimpleMath::Vector2 TEN_PLACE_MINUTES_POSITION = { 1060.0f, 560.0f };

	//		��(��̈�)�̍��W
	const DirectX::SimpleMath::Vector2 ONE_PLACE_MINUTES_POSITION = { 1090.0f, 560.0f };

	//		�b(�\�̈�)�̍��W
	const DirectX::SimpleMath::Vector2 TEN_PLACE_SECONDS_POSITION = { 1150.0f, 560.0f };

	//		�b(��̈�)�̍��W
	const DirectX::SimpleMath::Vector2 ONE_PLACE_SECONDS_POSITION = { 1180.0f, 560.0f };

private:

	//		�����̃V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;

	//		����
	int m_time;

	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;

	//		���~�b�g����
	float m_limitTime;

	GameManager* m_gameManager;
};
