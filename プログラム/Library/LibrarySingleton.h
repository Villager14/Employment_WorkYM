/*
* @file		LibraySingleton.h
* @brief	���C�u�����V���O���g��
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "DeviceResources.h"

#include <SpriteFont.h>

#include <random>

#include "Common/BinaryFile.h"

class LibrarySingleton final
{
private:

	//		�R���X�g���N�^
	LibrarySingleton();

public:

	//		�f�X�g���N�^
	~LibrarySingleton();

	/*
	*	LibrarySingleton�̃C���X�^���X���󂯎��
	*
	*	@return LibrarySingleton
	*/
	static LibrarySingleton* const GetInstance();

	//		����������
	void Initialize();

public:

	//		�`�拗���i�ő�j
	const float DRAWING_DISTANCE_MAX = 370.0f;

	//		�`�拗���i�ŏ��j
	const float DRAWING_DISTANCE_MIN = 0.1f;

private:

	//		LibrarySingleton�N���X�̃C���X�^���X�̃|�C���^
	static std::unique_ptr<LibrarySingleton> m_library;

	//		�X�N���[���̃T�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;

	//		�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	//		�ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;

	//		�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_commonState;

	//		�f�o�C�X���\�[�X
	std::unique_ptr<DX::DeviceResources> m_device;

	//		�X�e�b�v�^�C�}�[
	DX::StepTimer* m_timer;
	
	//		�L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardStateTracker;

	//		�}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker* m_buttonStateTracker;

	//		�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//		�X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	//		�o�[�e�b�N�X�|�W�V�����J���[
	std::unique_ptr<DirectX::PrimitiveBatch
		<DirectX::VertexPositionColor>> m_vertexPositionColor;

	//		�o�[�e�b�N�X�|�W�V�����J���[�e�N�X�`��
	std::unique_ptr<DirectX::PrimitiveBatch
		<DirectX::VertexPositionColorTexture>> m_vertexPositionColorTexture;

	//		�G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;

	//		�f�o�b�N�\�������邩�ǂ���
	bool m_debugViewJudgment;

public:

	/*
	*	�t�H���g��`�悷��
	* 
	*	@param	(string)		�`�悷�镶���̏��
	*	@param	(position)		���W
	*/
	void DrowFont(const wchar_t* string, DirectX::SimpleMath::Vector2 position)
	{
		//		�f�o�b�N�\�����I�t�̏ꍇ���������Ȃ�
		if (!m_debugViewJudgment) return;

		m_spriteBatch->Begin();
		m_spriteFont->DrawString(m_spriteBatch.get(), string, position);
		m_spriteBatch->End();
	}

	/*
	*	�f�o�b�N�t�H���g
	*	
	*	@param	(information)	�����̏��
	*	@param	(number)		����
	*	@param	(x)				X���W
	*	@param	(y)				Y���W
	*/
	void DebugFont(const wchar_t* information,
				  float number, int x, int y)
	{
		//		�f�o�b�N�\�����I�t�̏ꍇ���������Ȃ�
		if (!m_debugViewJudgment) return;

		//		�f�o�b�N�t�H���g
		std::wostringstream oss;

		oss << information << " : " << number;

		DrowFont(oss.str().c_str(), 
		DirectX::SimpleMath::Vector2(static_cast<float>(x), static_cast<float>(y)));
	}

	/*
	*	�X�N���[���̃T�C�Y��ݒ肷��
	*
	*	@param(width)	�X�N���[���̉��T�C�Y
	*	@param(height)	�X�N���[���̏c�T�C�Y
	*/
	void SetScreenSize(const int& width, const int& height)
	{
		m_screenSize = { static_cast<float>(width),
						 static_cast<float>(height) };
	}

	//		�f�o�b�N�\�������邩�ǂ���
	void ChangeDebugView()
	{
		//		�\����ԂȂ��\���ɔ�\����ԂȂ�\���ɂ���
		if (m_debugViewJudgment) { m_debugViewJudgment = false; }
		else { m_debugViewJudgment = true; }
	}

	/*
	*	�f�o�b�N�����邩�ǂ������󂯎��
	* 
	*	@return	true : �f�o�b�N�\�� false : �f�o�b�N��\�����Ȃ�
	*/
	bool GetDebugJudgement() { return m_debugViewJudgment; }

	/*
	*	�͈͓��̃����_���Ȑ������󂯎��
	* 
	*	@param	(min)	�ŏ��l
	*	@param	(max)	�ő�l
	*	@return �����_���Ȓl
	*/
	float Random(float min, float max);

	/*
	*	�s�N�Z���V�F�[�_�[�̍쐻
	* 
	*	@param	(path)	�t�@�C���p�X
	*/
	Microsoft::WRL::ComPtr<ID3D11PixelShader> CreatePSShader(const wchar_t* path);

	/*
	*	���_�V�F�[�_�[�̍쐬
	* 
	*	@param	(path)	�t�@�C���p�X
	*/
	BinaryFile CreateVSShader(const wchar_t* path, Microsoft::WRL::ComPtr<ID3D11VertexShader>* vsshader);

	/*
	*	�W�I���g���V�F�[�_�[�̍쐬
	*
	*	@param	(path)	�t�@�C���p�X
	*/
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> CreateGSShader(const wchar_t* path);

	/*
	*	�X�N���[���̃T�C�Y���󂯎��
	*
	*	@return �T�C�Y
	*/
	const DirectX::SimpleMath::Vector2& GetScreenSize() { return m_screenSize; }

	/*
	*	�R�����X�e�[�g�̃C���X�^���X���󂯎��
	* 
	*	@return �C���X�^���X
	*/
	DirectX::CommonStates* GetCommonState() const { return m_commonState.get(); }

	/*
	*	�f�o�C�X���\�[�X�̃C���X�^���X���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	DX::DeviceResources* GetDeviceResources() const { return m_device.get(); }

	/*
	*	�o�[�e�b�N�X�|�W�V�����J���[�e�N�X�`�����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* GetVertexPositionColor()
	{ return m_vertexPositionColor.get(); }

	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture >* GetVertexPositionColorTexture()
	{ return m_vertexPositionColorTexture.get(); }


	/*
	*	�G�t�F�N�g�t�@�N�g���[���󂯎��
	* 
	*	@return �C���X�^���X
	*/
	DirectX::EffectFactory* GetEffectFactory()
	{ return m_effectFactory.get(); }

	/*
	*	�r���[�s���ݒ肷��
	* 
	*	@param	(view) �r���[�s��
	*/
	void SetView(const DirectX::SimpleMath::Matrix& view) { m_view = view; }

	/*
	*	�r���[�s����󂯎��
	* 
	*	@return �s��
	*/
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }

	/*
	*	�ˉe�s���ݒ肷��
	* 
	*	@param	(proj) �ˉe�s��
	*/
	void SetProj(const DirectX::SimpleMath::Matrix& proj) { m_proj = proj; }

	/*
	*	�ˉe�s����󂯎��
	* 
	*	@return �s��
	*/
	DirectX::SimpleMath::Matrix& GetProj() { return m_proj; }

	/*
	*	�X�e�b�v�^�C�}�[��ݒ肷��
	* 
	*	@param	(timer) �X�e�b�v�^�C�}�[
	*/
	void SetStepTimer(DX::StepTimer& timer) { m_timer = &timer; }

	/*
	*	�X�e�b�v�^�C�}�[���󂯎��
	* 
	*	@return �X�e�b�v�^�C�}�[
	*/
	const DX::StepTimer& GetStepTimer() { return *m_timer; }

	/*
	*	�L�[�{�[�h��ݒ肷��
	* 
	*	@param	(keyboardStateTracker)�@�L�[�{�[�h�X�e�[�g�g���b�J�[�̃C���X�^���X�̃|�C���^
	*/
	void SetKeyboardTracker(DirectX::Keyboard::KeyboardStateTracker* keyboardStateTracker)
							{ m_keyboardStateTracker = keyboardStateTracker; }

	/*
	*	�L�[�{�[�h���󂯎��
	* 
	*	@return �L�[�{�[�h�X�e�[�g�g���b�J�[�̃|�C���^
	*/
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker()
							const { return m_keyboardStateTracker; }

	/*
	*	�}�E�X��ݒ肷��
	* 
	*	@param	(buttonStateTracker)	�{�^���X�e�[�g�g���b�J�[�̃C���X�^���̃|�C���^
	*/
	void SetButtonStateTracker(DirectX::Mouse::ButtonStateTracker* buttonStateTracker)
							{ m_buttonStateTracker = buttonStateTracker; }

	/*
	*	�}�E�X���󂯎��
	* 
	*	@return	�{�^���X�e�[�g�g���b�J�[�̃|�C���^
	*/
	DirectX::Mouse::ButtonStateTracker* GetButtonStateTracker()
							const {return m_buttonStateTracker;}

	/*
	*	�o�ߕb�����󂯎��
	* 
	*	@return �o�ߕb��
	*/
	float GetElpsedTime() { return static_cast<float>(m_timer->GetElapsedSeconds());}
};


