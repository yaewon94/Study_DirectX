#pragma once
#include "EditorUIValues.h"

class EditorUI;

// imgui �������� �����ϴ� Ŭ����
class ImguiManager final : public Singleton<ImguiManager>
{
	SINGLETON(ImguiManager);

private:
	// ����, ������ ������ ���Ͼ�� unordered_map ���� ��
	unordered_map<EDITOR_UI_TYPE, unordered_map<string, EditorUI*>> m_mapUI;

public:
	// EditorUI ���� �̸��� �ߺ����� �ʰ� ó�������Ƿ�, �Ķ���ͷ� �̸��� ���� �ʾƵ� ��
	void AddUI(EditorUI& ui);
	void DeleteUI(EditorUI& ui);
	// @ return : first element
	// TODO : �׻� �� ó�� ���Ե� element�� ��ȯ�ϴ��� üũ
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