#include<iostream>
#include<string>
#include <vector>
#include"Core.h"
using std::string;
using std::vector;
using std::cout;
using std::endl;

Core::Core() {}
Core::~Core() {}

int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	int i = 0;
	if ((!isalpha(head) && head != '\0')||(!isalpha(tail) && tail != '\0'))
	{
		throw exception("首尾字母约束不合法");
		return 0;
	}
	if_r = enable_loop;
	if_w = true;
	if_h = isalpha(head);
	if_t = isalpha(tail);
	if (isalpha(head))
	{
		if (isupper(head))
		{
			head = tolower(head);
		}
	}
	if (isalpha(tail))
	{
		if (isupper(tail))
		{
			tail = tolower(tail);
		}
	}
	int resultindex = -1;
	for (i = 0; i < len; i++)
	{
		string word = words[i];
		newnode(word);
	}
	toforest();
	resultindex = findmostwords(head, tail);
	if (resultindex < 0)
	{
		return 0;
	}
	for (i = 0; i < forest[resultindex].size(); i++)
	{
		result[i] = const_cast<char*>(map[forest[resultindex][i]].nodeword.c_str());
	}
	return forest[resultindex].size();
}
int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	int i = 0;
	if ((!isalpha(head) &&head != '\0') || (!isalpha(tail) && tail != '\0'))
	{
		throw exception("首尾字母约束不合法");
		return 0;
	}
	if_r = enable_loop;
	if_c = true;
	if_h = isalpha(head);
	if_t = isalpha(tail);
	if (isalpha(head))
	{
		if (isupper(head))
		{
			head = tolower(head);
		}
	}
	if (isalpha(tail))
	{
		if (isupper(tail))
		{
			tail = tolower(tail);
		}
	}
	int resultindex = -1;
	for (i = 0; i < len; i++)
	{
		string word = words[i];
		newnode(word);
	}
	toforest();
	resultindex = findlongest(head, tail);
	if (resultindex < 0) {
		return 0;
	}
	for (i = 0; i < forest[resultindex].size(); i++)
	{
		result[i] = const_cast<char*>(map[forest[resultindex][i]].nodeword.c_str());
	}
	return forest[resultindex].size();
}

void Core::newnode(string word)
{
	node newword;
	int i = 0;
	if (word.length() == 0)
	{
		throw exception("有单词为空字符串");
		return;
	}
	for (i = 0; i < word.length(); i++)
	{
		if (!isalpha(word[i]))
		{
			throw exception("单词包含非法字符");
			return;
		}
		if (isupper(word[i]))
		{
			word[i] = tolower(word[i]);
		}
	}
	newword.nodeword = word;
	newword.head = word[0];
	newword.tail = word.back();
	newword.wordlen = word.length();
	//把单词加入图
	addtomap(newword);
}

void Core::addtomap(node newword)
{
	int i = 0;
	int index = map.size();
	for (i = 0; i < index; i++)
	{
		if (map[i].nodeword == newword.nodeword)
		{
			return;
		}
	}
	for (i = 0; i < index; i++)
	{
		if (map[i].tail == newword.head)
		{
			map[i].next.push_back(index);
		}
		if (map[i].head == newword.tail)
		{
			newword.next.push_back(i);
		}
	}
	map.push_back(newword);
}
void Core::toforest()
{
	int i = 0;
	if (if_t)
	{
		for (i = 0; i < map.size(); i++)
		{
			vector<int> forward;
			next2(forward, i);
		}
	}
	else {
		for (i = 0; i < map.size(); i++)
		{
			vector<int> forward;
			next1(forward, i);
		}
	}
}
void Core::next1(vector<int> forward, int root)
{
	int i = 0;
	for (i = 0; i < forward.size(); i++) {
		if (forward[i] == root)//有环
		{
			if (!if_r)
			{				
//				cout << "错误： 含有单词环" << endl;
				throw exception("单词文本隐含单词环");			
			}
			else {
				if (forward.size() > 1)
				{
					forest.push_back(forward);
				}
			}
			return;
		}
	}
	forward.push_back(root);
	if (map[root].next.size() == 0 && forward.size() > 1)
	{
		forest.push_back(forward);
		return;
	}
	else {
		int j = 0;
		for (j = 0; j < map[root].next.size(); j++)
		{
			next1(forward, map[root].next[j]);
		}
	}
}
void Core::next2(vector<int> forward, int root)
{
	int i = 0;
	for (i = 0; i < forward.size(); i++) {
		if (forward[i] == root)//有环
		{
			if (!if_r)
			{
//				cout << "错误： 含有单词环" << endl;
				throw exception("单词文本隐含单词环");
			}
			else {
				if (forward.size() > 1)
				{
					forest.push_back(forward);
				}
			}
			return;
		}
	}
	forward.push_back(root);
	if (forward.size() > 1)
	{
		forest.push_back(forward);
	}
	if (map[root].next.size() == 0)
	{
		return;
	}
	else {
		int j = 0;
		for (j = 0; j < map[root].next.size(); j++)
		{
			next2(forward, map[root].next[j]);
		}
	}
}
int Core::findmostwords(char head, char tail)
{
	int i = 0;
	int tempmax = 0;
	int tempindex = -1;
	if (isalpha(head) && !isalpha(tail))//只规定单词链首字母
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax && map[forest[i][0]].head == head)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	else if (!isalpha(head) && isalpha(tail))//只规定单词链尾字母
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax && map[forest[i].back()].tail == tail)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	else if (isalpha(head) && isalpha(tail)) {//规定首字母和尾字母
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax && map[forest[i][0]].head == head && map[forest[i].back()].tail == tail)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	else {//没有规定
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	if (tempindex >= 0)
	{
		return tempindex;
	}
	return -1;
}
int Core::findlongest(char head, char tail)
{
	int i = 0;
	int templong = 0;
	int tempindex = -1;
	int length = 0;
	if (if_h && !if_t)
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (map[forest[i][0]].head == head)
			{
				length = listlength(i);
				if (length > templong)
				{
					templong = length;
					tempindex = i;
				}
			}
		}
	}
	else if (if_t && !if_h)
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (map[forest[i].back()].tail == tail)
			{
				length = listlength(i);
				if (length > templong)
				{
					templong = length;
					tempindex = i;
				}
			}
		}
	}
	else if (if_h && if_t)
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (map[forest[i][0]].head == head && map[forest[i].back()].tail == tail)
			{
				length = listlength(i);
				if (length > templong)
				{
					templong = length;
					tempindex = i;
				}
			}
		}
	}
	else {
		for (i = 0; i < forest.size(); i++)
		{
			length = listlength(i);
			if (length > templong)
			{
				templong = length;
				tempindex = i;
			}
		}
	}
	if (tempindex >= 0 && forest[tempindex].size() > 1)
	{
		return tempindex;
	}
	return -1;
}
int Core::listlength(int index)
{
	int sum = 0;
	int i = 0;
	for (i = 0; i < forest[index].size(); i++)
	{
		sum += map[forest[index][i]].wordlen;
	}
	return sum;
}