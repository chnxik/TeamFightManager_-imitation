#pragma once

namespace ssz
{
    class GameObject;
    class Scene;
    class Cursor
    {
    public:
        static void Initialize();

        static GameObject* GetCursor() { return mCursor; }
        static void RegistCursor(Scene* pActiveScene);

    private:
        static GameObject* mCursor;
    };
}