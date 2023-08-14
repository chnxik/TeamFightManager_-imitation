#pragma once
// pch
#include "GameEnums.h"
#include "CommonDefine.h"

// GamaManger
#include "sszBattleManager.h"
// Engine
#include "sszSceneManager.h"
#include "sszCollisionManager.h"
#include "sszFileManager.h"
#include "sszInput.h"
#include "sszTime.h"
#include "sszScene.h"

// GameObject
#include "sszGameObject.h"	// 게임 오브젝트

#include "sszChamp.h"		// 챔피언 오브젝트
#include "sszColObj.h"		// 콜라이더용 오브젝트
#include "sszPilot.h"
#include "sszTeam.h"

// AI
#include "sszBT.h"
#include "sszAIBB.h"
using namespace ssz::AI;

// Component
#include "sszCamera.h"
#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCollider2D.h"
#include "sszAnimator.h"
#include "sszLight.h"

// Object Func
#include "sszObject.h"
using namespace ssz::object;

// UI Component
#include "sszUIComponent.h"
#include "sszButtonUI.h"

//Resources
#include "sszResources.h"
#include "sszMaterial.h"
#include "sszMesh.h"
#include "sszTexture.h"
#include "sszAnimation.h"
