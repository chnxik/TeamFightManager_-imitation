#pragma once
// pch
#include "GameEnums.h"
#include "CommonDefine.h"

// Engine
#include "sszSceneManager.h"
#include "sszCollisionManager.h"
#include "sszFileManager.h"
#include "sszInput.h"
#include "sszTime.h"
#include "sszFontWrapper.h"
#include "sszScene.h"

// GameObject
#include "sszGameObject.h"	// 게임 오브젝트

// Object Func
#include "sszObject.h"
using namespace ssz::object;

//Resources
#include "sszResources.h"
#include "sszMaterial.h"
#include "sszMesh.h"
#include "sszTexture.h"
#include "sszAnimation.h"
#include "sszAudioClip.h"

// Component
#include "sszCamera.h"
#include "sszTransform.h"
#include "sszRigidbody.h"
#include "sszMeshRenderer.h"
#include "sszCollider2D.h"
#include "sszAnimator.h"
#include "sszLight.h"
#include "sszAudioListener.h"
#include "sszAudioSource.h"
#include "sszText.h"

#include "sszGrayScript.h"
#include "sszMasking.h"

// UI Component
#include "sszUIComponent.h"