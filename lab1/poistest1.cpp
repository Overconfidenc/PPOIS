#include "pch.h"
#include "CppUnitTest.h"
#include "../MarkovAlgorithm.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace poistest1
{
    TEST_CLASS(poistest1)
    {
    public:

        TEST_METHOD(TestAddRule)
        {
            MarkovAlgorithm algorithm;
            algorithm.addRule("a->b");
            algorithm.addRule("b|-stop");

            Assert::AreEqual(size_t(2), algorithm.rules.size());
            Assert::AreEqual(string("a"), algorithm.rules[0].from);
            Assert::AreEqual(string("b"), algorithm.rules[0].to);
            Assert::IsFalse(algorithm.rules[0].isFinal);

            Assert::AreEqual(string("b"), algorithm.rules[1].from);
            Assert::AreEqual(string("stop"), algorithm.rules[1].to);
            Assert::IsTrue(algorithm.rules[1].isFinal);
        }

        TEST_METHOD(TestApplySimple)
        {
            MarkovAlgorithm algorithm;
            algorithm.addRule("a->b");
            algorithm.addRule("b->c");
            algorithm.addRule("c|-stop");

            string result = algorithm.apply("a");
            Assert::AreEqual(string("stop"), result);
        }

        TEST_METHOD(TestApplyNoRuleMatch)
        {
            MarkovAlgorithm algorithm;
            algorithm.addRule("x->y");

            string result = algorithm.apply("abc");
            Assert::AreEqual(string("abc"), result);
        }

        TEST_METHOD(TestReplaceWordInFile)
        {
            // Создаём тестовый файл
            ofstream testFile("test.txt");
            testFile << "Hello world! Hello Markov!";
            testFile.close();

            MarkovAlgorithm algorithm;
            bool replaced = algorithm.replaceWordInFile("test.txt", "Hello", "Hi");

            Assert::IsTrue(replaced);

            // Проверяем содержимое файла
            ifstream resultFile("test.txt");
            ostringstream buffer;
            buffer << resultFile.rdbuf();
            resultFile.close();

            Assert::AreEqual(string("Hi world! Hi Markov!"), buffer.str());
        }

        TEST_METHOD(TestReplaceWordInFileNoMatch)
        {
            // Создаём тестовый файл
            ofstream testFile("test2.txt");
            testFile << "This is a test.";
            testFile.close();

            MarkovAlgorithm algorithm;
            bool replaced = algorithm.replaceWordInFile("test2.txt", "Hello", "Hi");

            Assert::IsFalse(replaced);

            // Проверяем содержимое файла
            ifstream resultFile("test2.txt");
            ostringstream buffer;
            buffer << resultFile.rdbuf();
            resultFile.close();

            Assert::AreEqual(string("This is a test."), buffer.str());
        }
    };
}
