#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab11\Source.cpp"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestFloydWarshall)
		{
			string path = "graph.txt";
			Assert::IsTrue(read(path));
			floydWarshall();
			Assert::AreNotEqual(distances[0][1], INF);
			Assert::AreEqual(distances[0][1], 3U);
			Assert::AreEqual(distances[1][2], 1U);
		}
	};
}
