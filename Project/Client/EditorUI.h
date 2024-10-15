#pragma once
#include "imgui/imgui.h"

class EditorUI
{
	NO_COPY_ASSIGN(EditorUI);

private:
	static UINT nextID;

private:
	const UINT m_ID;
	// imgui 객체의 이름이 같으면 똑같은 객체로 취급한다
	// ## 뒤의 문자열은 화면에 출력되지 않는다
	// ex) box##1, box##2 이런 식으로 실제 이름은 다르되, 화면에 출력되는 이름은 같게 할 수 있다
	string m_name;
	bool m_isActive;

public:
	EditorUI();
	~EditorUI();

public:
	const string& GetName() { return m_name; }
	bool IsActive() { return m_isActive; }
	
	void SetName(const string& name) { m_name = name + "##" + std::to_string(m_ID); }
	void SetActive(bool isActive) { m_isActive = isActive; }

public:
	virtual void Tick() {}
	virtual void Render() final;
	virtual void RenderUpdate() = 0;
};