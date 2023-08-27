#pragma once
#include "sszGameObject.h"

namespace ssz
{
	class Champ;

    class Shadow : public GameObject
    {
	public:
		Shadow();
		virtual ~Shadow();

		virtual void Initialize() override;

		void RegistChamp(Champ* owner);

    private:

    };
}