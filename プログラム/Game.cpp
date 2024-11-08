//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    //m_deviceResources = std::make_unique<DX::DeviceResources>();
    
    m_deviceResources = LibrarySingleton::GetInstance()->GetDeviceResources();

    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    //      シングルトン初期化処理
    LibrarySingleton::GetInstance()->Initialize();

    //      ステップタイマーの取得
    LibrarySingleton::GetInstance()->SetStepTimer(m_timer);

    //      キーボードステートトラッカーを設定する
    LibrarySingleton::GetInstance()->SetKeyboardTracker(&m_keyboardTracker);

    //      ボタンステートトラッカーを設定する
    LibrarySingleton::GetInstance()->SetButtonStateTracker(&m_mouse);

    //      音楽ライブラリの初期化
    MusicLibrary::GetInstance()->Initialize();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

    //      シーンマネージャーの生成
    m_sceneManager = std::make_unique<SceneManager>();

    //      シーンマネージャーの初期化処理
    m_sceneManager->Initialize();
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    //      キーボードステートの取得
    auto keyState = Keyboard::Get().GetState();

    //      キーボードトラッカーの更新処理
    m_keyboardTracker.Update(keyState);

    //      マウスステートの取得
    auto mouseState = Mouse::Get().GetState();

    //      マウスの更新
    m_mouse.Update(mouseState);

    //      デバック表示するかしないかを切り替える
    if (m_keyboardTracker.IsKeyPressed(DirectX::Keyboard::Q))
    {
        LibrarySingleton::GetInstance()->ChangeDebugView();
    }

    //      ゲームを終了する
    if (m_keyboardTracker.IsKeyPressed(DirectX::Keyboard::Escape))
    {
        m_sceneManager->SetEndJudgement(true);
    }

    //      シーンの更新
    m_sceneManager->Update();

    if (m_sceneManager->GetEndJudgement())
    {
        PostQuitMessage(0);
    }

    // TODO: Add your game logic here.
    elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    //      シーンマネージャーの描画
    m_sceneManager->Render();

    //      フレームレート
    LibrarySingleton::GetInstance()->DebugFont(L"FPS",
       static_cast<float>(LibrarySingleton::GetInstance()
           ->GetStepTimer().GetFramesPerSecond())
        , 1000, 0);

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1280;
    height = 720;

    //      スクリーンサイズを設定する
    LibrarySingleton::GetInstance()->SetScreenSize(width, height);
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
