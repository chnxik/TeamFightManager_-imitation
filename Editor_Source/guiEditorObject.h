#pragma once
#include "..\Engine_SOURCE\sszGameObject.h"

namespace gui
{
	class EditorObject : public ssz::GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}