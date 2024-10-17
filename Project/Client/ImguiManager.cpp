#include "pch.h"
#include "ImguiManager.h"
#include "EditorUI.h"

#include "Engine/Engine.h"
#include "Engine/Device.h"
#include "Engine/KeyManager.h"
#include "Engine/LevelManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

ImguiManager::ImguiManager()
{
}

ImguiManager::~ImguiManager()
{
    // imgui 관련 정리
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // EditorUI 메모리 해제
    for (auto& pair : m_mapUI)
    {
        if (pair.second != nullptr)
        {
            delete pair.second;
            pair.second = nullptr;
        }
    }
}

void ImguiManager::AddUI(EditorUI& ui)
{
    m_mapUI.insert(make_pair(ui.GetName(), &ui));
}

int ImguiManager::Init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    //io.ConfigViewportsNoDefaultParent = true;
    //io.ConfigDockingAlwaysTabBar = true;
    //io.ConfigDockingTransparentPayload = true;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(Engine::GetInstance()->GetHwnd());
    ImGui_ImplDX11_Init(DEVICE.Get(), CONTEXT.Get());

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);
    
#ifdef _DEBUG
    Test_CreateEditorUI();
#endif // _DEBUG

    return S_OK;
}

void ImguiManager::Progress()
{
    Tick();
    Render();
}

void ImguiManager::Tick()
{
    for (const auto& pair : m_mapUI)
    {
        pair.second->Tick();
    }
}

void ImguiManager::Render()
{
    // Render Start
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //// Tick DemoWindow
    //bool bDemo = true;
    //ImGui::ShowDemoWindow(&bDemo);

    // EditorUI 렌더링
    for (const auto& pair : m_mapUI)
    {
        pair.second->Render();
    }
    
    // 화면 내부 UI 들 렌더링
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // 화면 외부로 벗어난 별도의 윈도우에 그려지는 UI 들 렌더링
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

#ifdef _DEBUG
#include "TransformUI.h"
void ImguiManager::Test_CreateEditorUI()
{
   EditorUI* ui = nullptr;
   Ptr<GameObject> player = LevelManager::GetInstance()->GetGameObject(LAYER_TYPE::PLAYER);
   ui = new TransformUI(player);
   ui->SetName("Transform");
   AddUI(*ui);
}
#endif // _DEBUG