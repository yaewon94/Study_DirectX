#pragma once
#include "ImguiManager.h"
#include "imgui/imgui.h"

#define SAMELINE_VALUE 130
#define MAIN_TITLE_SAMELINE_VALUE 80
#define SMALL_TITLE_SAMELINE_VALUE 50

#define CHILDSIZE_ROW 35

class ComponentUI;
class EditorUI;

typedef void(EditorUI::* EUI_CALLBACK)(void*);

// 에디터모드 모든 UI들의 최상위 클래스 (추상클래스)
// TODO : 게임오브젝트 생성 기능
// TODO : 각 EditorUI의 X 표시를 누르면 해당 컴포넌트 제거 (TransformUI 제외)
// TODO : UI 사이즈 스크립트에서 조절
class EditorUI
{
	NO_COPY_ASSIGN(EditorUI);

// static members
private:
	static UINT nextID;

// about EditorUI
private:
	bool m_isActive;
	bool m_isModal;	// 모달 윈도우가 활성화 되어있는 동안은, 다른 작업을 할 수 없다

	// imgui 객체의 이름이 같으면 똑같은 객체로 취급한다
	// ## 뒤의 문자열은 화면에 출력되지 않는다
	// ex) box##1, box##2 이런 식으로 실제 이름은 다르되, 화면에 출력되는 이름은 같게 할 수 있다
	const string m_name;

	EditorUI* m_parent;
	map<EDITOR_UI_TYPE, EditorUI*> m_children;

// Destructor
protected:
	virtual ~EditorUI();

// Constructor, call Destructor
public:
	EditorUI(const string& name);
	void Destroy();

// [public] Getter, Setter
public:
	virtual EDITOR_UI_TYPE GetType() = 0;

	bool IsActive() { return m_isActive; }
	void SetActive(bool isActive);

	bool IsModal() { return m_isModal; }
	void SetModal(bool isModal) { m_isModal = isModal; }

	const string& GetName() const { return m_name; }

	const EditorUI* const GetParent() { return m_parent; }
	virtual ImVec2 GetChildSize() { return ImVec2(0, 0); }
	
	template<typename T> requires std::derived_from<T, EditorUI>
	T* const GetChild()
	{
		const auto iter = m_children.find(T::Type);
		if (iter != m_children.end()) return (T*)(iter->second);
		else return nullptr;
	}

protected:
	template<typename T> requires std::derived_from<T, EditorUI>
	T* const AddChild()
	{
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("이미 가지고 있는 UI 입니다");
		}

		T* t = new T;
		m_children.insert(make_pair(T::Type, t));
		t->m_parent = this; // 부모 설정
		ImguiManager::GetInstance()->AddUI(*t); // ImguiManager에 등록
		return t;
	}

	void DeleteChildren();

// about EditorUI functions called every frame
public:
	virtual void Tick() {}
	virtual void Render();

// functions for overriding
protected:
	virtual void RenderUpdate() = 0;

	virtual void ActivateOnOff() {}

protected:
	// 타이틀 렌더링
	void RenderTitle();

private:
	void RenderModal();
	void RenderModalless();
	void RenderChild();
};