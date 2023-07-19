#pragma once
#include "..\Engine_SOURCE\sszGameObject.h"

namespace gui
{
	class DebugObject : public ssz::GameObject
	{
	public:
		DebugObject(ssz::enums::eColliderType eType);
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		ssz::enums::eColliderType mType;
	};
}