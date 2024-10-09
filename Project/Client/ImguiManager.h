#pragma once

class ImguiManager final : public Singleton<ImguiManager>
{
	SINGLETON(ImguiManager);

public:
	int Init();
	void Progress();

private:
	void Render();
};