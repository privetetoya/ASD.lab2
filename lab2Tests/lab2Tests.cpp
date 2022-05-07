#include "pch.h"
#include "CppUnitTest.h"

#include "../ASD.lab2/List.h"
#include "../ASD.lab2/Map.h"
#include "../ASD.lab2/ShannonFano.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab2Tests
{
	TEST_CLASS(lab2Tests)
	{
	public:

		TEST_METHOD(ConstructorTest) {
			Map<char, int> MyCustomMap;
			MyCustomMap.insert('a', 1);
			int letters = 1;
			string original = "a";
			ShannonFano Tester(MyCustomMap, letters, original);
			Assert::IsTrue(Tester.sizeOfOriginalText() == 8);
		}
		TEST_METHOD(OriginalTextSizeTest) {
			Map<char, int> map;
			map.insert('a', 1);
			int letters = 1;
			string original = "a";
			ShannonFano coder(map, letters, original);
			Assert::IsTrue(coder.sizeOfOriginalText() == 8);
		}
		TEST_METHOD(EncodedTextSizeTest) {
			Map<char, int> map;
			map.insert('a', 1);
			map.insert('b', 1);
			int letters = 2;
			string original = "ab";
			ShannonFano Tester(map, letters, original);
			Tester.ShannonFanoEncodeHelper(0, 1);
			Assert::IsTrue(Tester.sizeOfEncodedText() == 2);
		}
			TEST_METHOD(EncodingTest) {
				Map<char, int> MyCustomMap;
				MyCustomMap.insert('a', 1);
				MyCustomMap.insert('b', 1);
				int letters = 2;
				string original = "ab";
				ShannonFano Tester(MyCustomMap, letters, original);
				Assert::IsTrue(Tester.sizeOfOriginalText() == 16);
				Tester.ShannonFanoEncodeHelper(0, 1);
				Assert::IsTrue(Tester.encodedText() == "10");
			}
			TEST_METHOD(RatioTest) {
				Map<char, int> map;
				map.insert(1, 1);
				map.insert(2, 1);
				int letters = 2;
				string original = "12";
				ShannonFano tester(map, letters, original);
				tester.ShannonFanoEncodeHelper(0, 1);
				Assert::IsTrue((tester.sizeOfOriginalText() / 1.0f) / (tester.sizeOfEncodedText() / 1.0f) == 8);
			}
			TEST_METHOD(DecoderTest) {
				Map<char, int> map;
				map.insert('a', 1);
				map.insert('b', 1);
				int letters = 2;
				string original = "ab";
				ShannonFano Tester(map, letters, original);
				Assert::IsTrue(Tester.sizeOfOriginalText() == 16);
				Tester.ShannonFanoEncodeHelper(0, 1);
				Assert::IsTrue(Tester.encodedText() == "10");
				Assert::IsTrue(Tester.decodedText() == "ab");
			}
		};
	}
