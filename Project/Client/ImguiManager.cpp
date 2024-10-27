#include "pch.h"
#include "ImguiManager.h"
#include "EditorUI.h"
#include "InspectorUI.h"
#include "ListUI.h"
#include "MenuUI.h"
#include "OutlinerUI.h"

#include "Engine/Engine.h"
#include "Engine/Device.h"
#include "Engine/KeyManager.h"
#include "Engine/LevelManager.h"
#include "Engine/GameObject.h"

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
    auto iter = m_mapUI.begin();
    while(iter != m_mapUI.end())
    {
        bool iterDeleted = false;
        auto iter2 = iter->second.begin();
        while (iter2 != iter->second.end())
        {
            if (iter2->second->GetParent() == nullptr)
            {
                if (iter->second.size() == 1)
                {
                    iter2->second->Destroy();
                    iterDeleted = true; // iter이 가리키는 것 자체가 삭제되었으므로
                    break;
                }
                else
                {
                    iter2->second->Destroy();
                    iter2 = iter->second.begin();
                }
            }
            else
            {
                ++iter2;
            }
        }

        if (iterDeleted) iter = m_mapUI.begin();
        else ++iter;
    }
}

void ImguiManager::AddUI(EditorUI& ui)
{
    const auto iter = m_mapUI.find(ui.GetType());

    if(iter != m_mapUI.end())
    {
        for (auto& pair : iter->second)
        {
            if (pair.first == ui.GetName()) throw std::logic_error("이미 등록된 UI 입니다");
        }

        iter->second.insert(make_pair(ui.GetName(), &ui));
        iter->second.emplace();
    }
    else
    {
        m_mapUI.insert(make_pair(ui.GetType(), unordered_map<string, EditorUI*>()));
        m_mapUI.find(ui.GetType())->second.insert(make_pair(ui.GetName(), &ui));
    }
}

void ImguiManager::DeleteUI(EditorUI& ui)
{
    const auto iter = m_mapUI.find(ui.GetType());

    if (iter != m_mapUI.end())
    {
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
        {
            if (ui.GetName() == iter2->first)
            {
                iter->second.erase(iter2);
                break;
            }
        }

        auto& test = iter->second;

        if (iter->second.empty())
        {
            m_mapUI.erase(iter);
            auto& test = m_mapUI;
        }
    }
    else
    {
        throw std::logic_error("등록된 UI가 아닙니다");
    }
}

EditorUI* const ImguiManager::FindUI(EDITOR_UI_TYPE type)
{
    const auto iter = m_mapUI.find(type);

    if (iter != m_mapUI.end()) return iter->second.begin()->second;
    else return nullptr;
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
    
    CreateDefaultUI();

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
        for (const auto& pair2 : pair.second)
        {
            pair2.second->Tick();
        }
    }
}

// ERROR : imgui 위젯을 윈도우 바깥으로 Drag,Drop 하면 렌더링이 안됨
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
        for (const auto& pair2 : pair.second)
        {
            if (pair2.second->GetParent() == nullptr) pair2.second->Render();
        }
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

void ImguiManager::CreateDefaultUI()
{
    EditorUI* ui = nullptr;

    // List UI
    ui = new ListUI;
    ui->SetActive(false);
    ui->SetModal(true);
    AddUI(*ui);

    // Menu UI
    ui = new MenuUI;
    AddUI(*ui);

    // OutlinerUI
    ui = new OutlinerUI;
    AddUI(*ui);

    //// Inspector
    ////Ptr<GameObject> obj = LevelManager::GetInstance()->GetGameObject(LAYER_TYPE::PLAYER);
    ////Ptr<GameObject> obj = LevelManager::GetInstance()->GetGameObject(LAYER_TYPE::CAMERA);
    ////Ptr<GameObject> obj = LevelManager::GetInstance()->GetGameObject(LAYER_TYPE::LIGHT);
    //Ptr<GameObject> obj = LevelManager::GetInstance()->GetGameObject(LAYER_TYPE::MONSTER);
    //ui = new InspectorUI(obj);
    //AddUI(*ui);
}