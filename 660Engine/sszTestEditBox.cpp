#include "sszTestEditBox.h"
#include "CommonObjHeader.h"

extern wchar_t g_strText[_MAX_FNAME];        // 텍스트를 저장하기 위한 변수
extern wchar_t g_strCombine[10];             // 조합 중인 문자
extern wchar_t g_strSpecial[_MAX_FNAME];     // 특수 문자를 위한 변수namespace ssz

namespace ssz
{
	TestEditBox::TestEditBox()
	{
	}

	TestEditBox::~TestEditBox()
	{
	}

	void TestEditBox::Initialize()
	{
		Text* tx = AddComponent<Text>();
		tx->SetFontSize(30.f);
		tx->SetFontColor(255, 255, 255, 255);
	}

	void TestEditBox::Update()
	{
		wstring str = g_strText;
		str += g_strCombine;

		Text* tx = GetComponent<Text>();
		tx->SetString(str);
	}
}