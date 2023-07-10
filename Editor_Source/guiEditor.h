#pragma once
#include "Commoninclude.h"
#include "sszEngine.h"
#include "guiWidget.h"
#include "guiEditorObject.h"
#include "guiDebugObject.h"
#include "sszGraphics.h"

namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const ssz::graphics::DebugMesh& mesh);

	private:
		static std::vector<Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugObject*> mDebugObjects;
	};
}