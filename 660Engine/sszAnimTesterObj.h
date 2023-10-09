#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class AnimTesterObj :
        public GameObject
    {
    public:
        enum class ObjType
        {
            Common,
            Champ,
            Efc,
            Skill,
            END
        };

        enum class eActiveType
        {
            IDLE,
            MOVE,
            ATTACK,
            DEAD,
            SKILL,
            ULTIMATE,
            END
        };

        void SetAnimKey(eActiveType eType, const std::wstring& key) { vecAnimKey[(UINT)eType] = key; }

        AnimTesterObj();
		virtual ~AnimTesterObj();

		virtual void Initialize();
		virtual void Update();

    private:
        std::wstring vecAnimKey[(UINT)eActiveType::END];

    };
}