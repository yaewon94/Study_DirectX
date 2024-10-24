#pragma once
#include "EditorUIValues.h"

class EditorUI;

// imgui 위젯들을 관리하는 클래스
class ImguiManager final : public Singleton<ImguiManager>
{
	SINGLETON(ImguiManager);

private:
	// 삽입, 삭제시 재정렬 안일어나게 unordered_map 으로 함
	unordered_map<EDITOR_UI_TYPE, unordered_map<string, EditorUI*>> m_mapUI;

public:
	// EditorUI 에서 이름이 중복되지 않게 처리했으므로, 파라미터로 이름을 받지 않아도 됌
	void AddUI(EditorUI& ui);
	void DeleteUI(EditorUI& ui);
	// @ return : first element
	// TODO : 항상 맨 처음 삽입된 element를 반환하는지 체크
	EditorUI* const FindUI(EDITOR_UI_TYPE type);

public:
	int Init();
	void Progress();

private:
	void Tick();
	void Render();

private:
	void CreateDefaultUI();
};