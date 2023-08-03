#pragma once

namespace ssz
{
    class GameObject;
    class Scene;
    class MainCamera
    {
    public:
        static void Initialize();

        static GameObject* GetMainCamera() { return mMainCamera; }
        static void RegistCamera(Scene* pActiveScene);

    private:
        static GameObject* mMainCamera;
    };
}