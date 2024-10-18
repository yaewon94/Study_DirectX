#pragma once

class EditorUI;

// imgui 위젯들을 관리하는 클래스
class ImguiManager final : public Singleton<ImguiManager>
{
	SINGLETON(ImguiManager);

private:
	unordered_map<string, EditorUI*> m_mapUI;

public:
	// EditorUI 에서 이름이 중복되지 않게 처리했으므로, 파라미터로 이름을 받지 않아도 됌
	void AddUI(EditorUI& ui);
	void DeleteUI(const EditorUI& ui);

public:
	int Init();
	void Progress();

private:
	void Tick();
	void Render();

private:
	void Test_CreateEditorUI();
};