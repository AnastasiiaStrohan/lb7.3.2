#include "pch.h"
#include "CppUnitTest.h"
#include "../lb7.3.2/lb7.3.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest732
{
	TEST_CLASS(UnitTest732)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int rowCount = 2;
			int colCount = 2;
			int Low = -10, High = 10;

			int** a = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				a[i] = new int[colCount];

			
			Create(a, rowCount, colCount, Low, High);

			
			for (int i = 0; i < rowCount; i++)
			{
				for (int j = 0; j < colCount; j++)
				{
					Assert::IsTrue(a[i][j] >= Low && a[i][j] <= High);
				}
			}

			
			for (int i = 0; i < rowCount; i++)
				delete[] a[i];
			delete[] a;
		}
	};
}
