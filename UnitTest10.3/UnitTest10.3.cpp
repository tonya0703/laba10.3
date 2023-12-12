#include "pch.h"
#include "CppUnitTest.h"
#include "..\ap_10.3\10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest103
{
	TEST_CLASS(UnitTest103)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Friend testFriend = { "John Doe", "1234567890", {10, 5, 1995} };

            string testFilename = "t.txt";

            addFriendToFile(testFriend, testFilename);

            ifstream testFile(testFilename);
            Assert::IsTrue(testFile.is_open(), L"Failed to open the test file.");

            string line;
            bool found = false;
            while (getline(testFile, line)) {
                if (line.find(testFriend.name) != string::npos &&
                    line.find(testFriend.phoneNumber) != string::npos &&
                    line.find(to_string(testFriend.birthday[0])) != string::npos &&
                    line.find(to_string(testFriend.birthday[1])) != string::npos &&
                    line.find(to_string(testFriend.birthday[2])) != string::npos) {
                    found = true;
                    break;
                }
            }

            testFile.close();

            Assert::IsTrue(found, L"Added friend not found in the test file.");

            remove(testFilename.c_str());
		}
	};
}
