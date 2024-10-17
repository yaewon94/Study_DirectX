#pragma once
#include "ImguiManager.h"
#include "imgui/imgui.h"
#include "Engine/GameObject.h"

// 에디터모드 모든 UI들의 최상위 클래스 (추상클래스)
// TODO : 게임오브젝트 생성 기능
// TODO : 게임오브젝트 생성 시 TransformUI는 자동으로 추가되도록 구현
// TODO : 각 EditorUI의 X 표시를 누르면 해당 컴포넌트 제거 (TransformUI 제외)
class EditorUI
{
	NO_COPY_ASSIGN(EditorUI);

// static members
private:
	static UINT nextID;

// about EditorUI
private:
	const UINT m_ID;
	bool m_isActive;
	// imgui 객체의 이름이 같으면 똑같은 객체로 취급한다
	// ## 뒤의 문자열은 화면에 출력되지 않는다
	// ex) box##1, box##2 이런 식으로 실제 이름은 다르되, 화면에 출력되는 이름은 같게 할 수 있다
	string m_name;

	EditorUI* m_parent;
	vector<EditorUI*> m_children;

// about GameObject
private:
	Ptr<GameObject> m_target;

// Constructor, Destructor
public:
	EditorUI(const Ptr<GameObject>& target);
	~EditorUI();

// [protected] Getter, Setter
protected:
	Ptr<GameObject> GetTarget() { return m_target; }

// [public] Getter, Setter
public:
	const string& GetName() { return m_name; }
	bool IsActive() { return m_isActive; }
	const EditorUI& GetParent() { return *m_parent; }
	
	template<typename T> requires std::derived_from<T, EditorUI>
	const EditorUI& GetChild()
	{
		for (EditorUI* child : m_children)
		{
			if (dynamic_cast<T*>(child) != nullptr)
			{
				return *child;
			}
		}

		throw std::logic_error("해당 타입의 UI가 없습니다");
	}

	void SetName(const string& name) { m_name = name + "##" + std::to_string(m_ID); }
	void SetActive(bool isActive) { m_isActive = isActive; }
	template<typename T> requires std::derived_from<T, EditorUI>
	void AddChild()
	{
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("이미 가지고 있는 컴포넌트 입니다");
		}
		else if (m_target->GetRenderComponent() != nullptr)
		{
			throw std::logic_error("렌더링 컴포넌트는 하나만 가질 수 있습니다");
		}
		else
		{
			m_children.push_back(new T);
		}

		// 부모 설정
		m_children.back().m_parent = this;
		
		// ImguiManager에 등록
		ImguiManager::GetInstance()->AddUI(m_children.back());
	}


// about EditorUI functions called every frame
public:
	virtual void Tick() {}
	virtual void Render() final;
	virtual void RenderUpdate() = 0;
};