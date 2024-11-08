/*
* @file		ResultManager.h
* @brief	�㏸�ԍ��V�F�[�_�[
* @author	Morita
* @date		2024/07/05
*/

#pragma once

#include <unordered_map>

#include "Library/Shader/UIRenderManager.h"

class RiseNumberShader
{
public:

	//		�R���X�g���N�^
	RiseNumberShader();

	//		�f�X�g���N�^
	~RiseNumberShader();

	//		����������
	void Initialize(int dethCount, int clearTime, int score);

	//		�`�揈��
	void Render(float time);

	//		�I������
	void Finalize();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 number;
		DirectX::SimpleMath::Vector4 time;
	};

	//		�����̎��
	enum NumberType
	{
		DethCount1,		//		���S�P
		DethCount2,		//		���S�Q
		DethCount3,		//		���S�R
		ClearCount1,	//		�N���A����1
		ClearCount2,	//		�N���A����2
		ClearCount3,	//		�N���A����3
		ClearCount4,	//		�N���A����4
		Score1,			//		�X�R�A1
		Score2,			//		�X�R�A2
		Score3,			//		�X�R�A3
		Score4,			//		�X�R�A4
	};

	//		�����̏��
	struct NumberInformation
	{
		DirectX::SimpleMath::Vector2 position;		//		���W
		int number = 0;								//		�`�悷��ԍ�
		int viewNumber = 0;							//		�`�揇
	};

private:

	//		���S���̍���
	const DirectX::SimpleMath::Vector2 DESH_POSITION = { 970.0f, 140.0f };

	//		���S�̊Ԋu
	const float INTERVAL = 60.0f;

	//		�X�R�A�ƃ^�C����X���W
	const float SCORE_TIME_X_POSITION = 910.0f;

	//		�N���A�^�C���̍���
	const float CLEAR_TIME_Y_POSITION = 250.0f;
	
	//		�X�R�A�̍���
	const float SCORE_Y_POSITION = 360.0f;


private:

	//		UI�`��}�l�[�W���[
	std::unique_ptr<UIRenderManager> m_uiRenderManager;

	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;

	//		�����̏��
	std::unordered_map<NumberType, NumberInformation> m_numberinformation;

public:

	/*
	*	�����̍쐻
	* 
	*	@param	(type)		 �����̎��
	*	@param	(position)	 ���W
	*	@param	(viewNumber) �`�揇
	*/
	void CreateNumber(NumberType type, DirectX::SimpleMath::Vector2 position,
		  int viewNumber);
};