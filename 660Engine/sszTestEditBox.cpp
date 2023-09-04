#include "sszTestEditBox.h"
#include "CommonObjHeader.h"

extern wchar_t g_strText[_MAX_FNAME];        // �ؽ�Ʈ�� �����ϱ� ���� ����
extern wchar_t g_strCombine[10];             // ���� ���� ����
extern wchar_t g_strSpecial[_MAX_FNAME];     // Ư�� ���ڸ� ���� ����namespace ssz

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