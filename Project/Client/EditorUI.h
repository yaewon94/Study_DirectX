#pragma once
#include "ImguiManager.h"
#include "imgui/imgui.h"

#define SAMELINE_VALUE 130
#define CHILDSIZE_ROW 35

class ComponentUI;
class EditorUI;

typedef void(EditorUI::* EUI_CALLBACK)(void*);

// �����͸�� ��� UI���� �ֻ��� Ŭ���� (�߻�Ŭ����)
// TODO : ���ӿ�����Ʈ ���� ���
// TODO : �� EditorUI�� X ǥ�ø� ������ �ش� ������Ʈ ���� (TransformUI ����)
// TODO : UI ������ ��ũ��Ʈ���� ����
class EditorUI
{
	NO_COPY_ASSIGN(EditorUI);

// static members
private:
	static UINT nextID;

// about EditorUI
private:
	bool m_isActive;
	bool m_isModal;	// ��� �����찡 Ȱ��ȭ �Ǿ��ִ� ������, �ٸ� �۾��� �� �� ����

	// imgui ��ü�� �̸��� ������ �Ȱ��� ��ü�� ����Ѵ�
	// ## ���� ���ڿ��� ȭ�鿡 ��µ��� �ʴ´�
	// ex) box##1, box##2 �̷� ������ ���� �̸��� �ٸ���, ȭ�鿡 ��µǴ� �̸��� ���� �� �� �ִ�
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
			throw std::logic_error("�̹� ������ �ִ� UI �Դϴ�");
		}

		T* t = new T;
		m_children.insert(make_pair(T::Type, t));
		t->m_parent = this; // �θ� ����
		ImguiManager::GetInstance()->AddUI(*t); // ImguiManager�� ���
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
	// Ÿ��Ʋ ������
	void RenderTitle();

private:
	void RenderModal();
	void RenderModalless();
	void RenderChild();
};