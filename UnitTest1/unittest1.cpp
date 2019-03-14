#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Wordlist/Core.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)//-w
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "Algebra","apple","zoo","elephant","under","fox","dog","moon","leaf","trick","peudopseudohypoparathyroidism" };
			char* answer[] = { "algebra","apple","elephant","trick" };
			int answerlen = 4;
			int resultlen = core->gen_chain_word(words, 11, result, '\0', '\0', false);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod2)//-c
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "Algebra","apple","zoo","elephant","under","fox","dog","moon","leaf","trick","peudopseudohypoparathyroidism" };
			char* answer[] = { "peudopseudohypoparathyroidism", "moon" };
			int answerlen = 2;
			int resultlen = core->gen_chain_char(words, 11, result, '\0', '\0', false);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod3)//-h e -w
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "Algebra","apple","zoo","elephant","under","fox","dog","moon","leaf","trick","peudopseudohypoparathyroidism" };
			char* answer[] = { "elephant","trick" };
			int answerlen = 2;
			int resultlen = core->gen_chain_word(words, 11, result, 'e', '\0', false);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod4)//-t t -w
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "Algebra","apple","zoo","elephant","under","fox","dog","moon","leaf","trick","peudopseudohypoparathyroidism" };
			char* answer[] = { "algebra","apple","elephant"};
			int answerlen = 3;
			int resultlen = core->gen_chain_word(words, 11, result, '\0', 't', false);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod5)//-h a -t t -w
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "abbbb","bcccc","cdddd","deee","ct" };
			char* answer[] = { "abbbb","bcccc","ct"};
			int answerlen = 3;
			int resultlen = core->gen_chain_word(words, 5, result, 'a', 't', false);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod6)//-h e -c
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "abb","bccccccccccccccccccccc","eccccccccccccccccccccc","ef","fffffd","dxxx","ccx" };
			char* answer[] = { "eccccccccccccccccccccc","ccx" };
			int answerlen = 2;
			int resultlen = core->gen_chain_char(words, 7, result, 'e', '\0', false);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod7)//-t t -c
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "abb","bccccccccccccccccccccc","eccccccccccccccccccccc","btttt","bt" };
			char* answer[] = { "abb","btttt" };
			int answerlen = 2;
			int resultlen = core->gen_chain_char(words, 5, result, '\0', 't', false);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod8)//-h b -t t -c
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "abb","bccccccccccccccccccccc","cccccccccccccccccccccf","ctttt","cbt" };
			char* answer[] = { "bccccccccccccccccccccc","ctttt" };
			int answerlen = 2;
			int resultlen = core->gen_chain_char(words, 5, result, 'b', 't', false);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod9)//-r -w
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","elephant","tea","alex","box","xob","cccccff","football" };
			char* answer[] = { "apple","elephant","tea","alex","xob","box" };
			int answerlen = 6;
			int resultlen = core->gen_chain_word(words, 8, result, '\0', '\0', true);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod10)//-r -w
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","elephant","tea","alex","box","xob","cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc" };
			char* answer[] = { "cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc" };
			int answerlen = 3;
			int resultlen = core->gen_chain_char(words, 9, result, '\0', '\0', true);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod11)//-t b -r -w
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","elephant","tea","alex","box","xob","cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc"};
			char* answer[] = { "apple","elephant","tea","alex","xob" };
			int answerlen = 5;
			int resultlen = core->gen_chain_word(words, 9, result, '\0', 'b', true);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		TEST_METHOD(TestMethod12)//-t b -r -w
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","elephant","tea","alex","box","xob","cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc" };
			char* answer[] = { "football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc","cccccff" };
			int answerlen = 3;
			int resultlen = core->gen_chain_char(words, 9, result, '\0', 'f', true);
			Assert::AreEqual(resultlen, answerlen);
			int i = 0;
			for (i = 0; i < answerlen; i++)
			{
				string stranswer = answer[i];
				string strresult = result[i];
				Assert::AreEqual(stranswer, strresult);
			}
		}
		//ErrorTest
		TEST_METHOD(ErrorTest1)//包含单词环但是没有-r参数
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","elephant","tea","alex","box","xob","cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc" };
			char* answer[] = { "football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc","cccccff" };
			int answerlen = 3;
			try {
				int resultlen = core->gen_chain_char(words, 9, result, '\0', 'f', false);
			}
			catch (exception e) {
				Assert::AreEqual("单词文本隐含单词环", e.what());
			}
		}
		TEST_METHOD(ErrorTest2)//输入的单词中有非法字符，elephant 的字母l被空格代替
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","e ephant","tea","alex","box","xob","cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc" };
			char* answer[] = { "football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc","cccccff" };
			int answerlen = 3;
			try {
				int resultlen = core->gen_chain_char(words, 9, result, '\0', 'f', false);
			}
			catch (exception e) {
				Assert::AreEqual("单词包含非法字符", e.what());
			}
		}
		TEST_METHOD(ErrorTest3)//首尾字母约束不合法，用 -h *
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","elephant","tea","alex","box","xob","cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc" };
			char* answer[] = { "football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc","cccccff" };
			int answerlen = 3;
			try {
				int resultlen = core->gen_chain_char(words, 9, result, '*', '\0', false);
			}
			catch (exception e) {
				Assert::AreEqual("首尾字母约束不合法", e.what());
			}
		}
		TEST_METHOD(ErrorTest4)//首尾字母约束不合法，用 -t 2
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","elephant","tea","alex","box","xob","cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc" };
			char* answer[] = { "football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc","cccccff" };
			int answerlen = 3;
			try {
				int resultlen = core->gen_chain_char(words, 9, result, 0, 2, false);
			}
			catch (exception e) {
				Assert::AreEqual("首尾字母约束不合法", e.what());
			}
		}
		TEST_METHOD(ErrorTest5)//有单词为空字符串 ""
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "apple","","tea","alex","box","xob","cccccff","football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc" };
			char* answer[] = { "football","lllllllllllllllllllllllllllllllllllllllllllllllllllllllllc","cccccff" };
			int answerlen = 3;
			try {
				int resultlen = core->gen_chain_char(words, 9, result, '\0', '\0', false);
			}
			catch (exception e) {
				Assert::AreEqual("有单词为空字符串", e.what());
			}

		}
	};
}