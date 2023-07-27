#pragma once
#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\660Engine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\660Engine.lib")
#endif

namespace ssz
{
	void InitializeScenes();
	void LoadFile();
}