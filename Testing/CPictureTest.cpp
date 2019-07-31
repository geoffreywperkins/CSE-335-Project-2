#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>

#include "Picture.h"
#include "Actor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;
using namespace std;


namespace Testing
{
	TEST_CLASS(CPictureTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestPictureConstruct)
		{
			CPicture picture;
		}

		TEST_METHOD(TestPictureGetterSetter)
		{
			CPicture picture;

			Size size = picture.GetSize();
			Assert::IsTrue(size.Width == 800);
			Assert::IsTrue(size.Height == 600);

			picture.SetSize(Size(200, 400));

			size = picture.GetSize();
			Assert::IsTrue(size.Width == 200);
			Assert::IsTrue(size.Height == 400);
		}

		TEST_METHOD(TestCPictureIterator)
		{
			CPicture picture;

			auto iter1 = picture.begin();
			auto iter2 = picture.end();

			// Test to ensure an iterator on an empty picture works
			Assert::IsFalse(iter1 != iter2);

			// Add some actors
			shared_ptr<CActor> actor1 = make_shared<CActor>(L"Bob");
			shared_ptr<CActor> actor2 = make_shared<CActor>(L"Ted");
			shared_ptr<CActor> actor3 = make_shared<CActor>(L"Carol");
			shared_ptr<CActor> actor4 = make_shared<CActor>(L"Alice");

			Assert::IsNull(actor1->GetPicture());

			picture.AddActor(actor1);
			picture.AddActor(actor2);
			picture.AddActor(actor3);
			picture.AddActor(actor4);

			// Test the associations
			Assert::IsTrue(actor1->GetPicture() == &picture);
			Assert::IsTrue(actor2->GetPicture() == &picture);
			Assert::IsTrue(actor3->GetPicture() == &picture);
			Assert::IsTrue(actor4->GetPicture() == &picture);

			iter1 = picture.begin();
			iter2 = picture.end();
			Assert::IsTrue(*iter1 == actor1);
			++iter1;
			Assert::IsTrue(*iter1 == actor2);
			++iter1;
			Assert::IsTrue(*iter1 == actor3);
			++iter1;
			Assert::IsTrue(*iter1 == actor4);
			++iter1;

			// Ensure we are at the end
			Assert::IsFalse(iter1 != iter2);
		}

		TEST_METHOD(TestCPictureGetTimeline)
		{
			CPicture picture;

			CTimeline *timeline = picture.GetTimeline();
			Assert::IsNotNull(timeline);
		}
	};
}