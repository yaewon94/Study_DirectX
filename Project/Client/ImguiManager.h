#pragma once

class EditorUI;

// imgui 위젯들을 관리하는 클래스
class ImguiManager final : public Singleton<ImguiManager>
{
	SINGLETON(ImguiManager);

private:
	map<string, EditorUI*> m_mapUI;

public:
	int Init();
	void Progress();

private:
	void Tick();
	void Render();
};