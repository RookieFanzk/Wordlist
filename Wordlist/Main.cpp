#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>

using namespace std;
struct node
{
	string nodeword;//����
	char head;//����ĸ
	char tail;//β��ĸ
	vector<int> next;//����ĩβ���ӵ���һ���������
	int wordlen;//���ʳ���
};

void readfile(string filepath);
void newnode(string word);
void addtomap(node newword);
void printmap();
void printnode(node n);
vector<vector<int>> next(int root);
void printforest();
void findmostwords(char head, char tail);
void printdetail(int index);
void wordlist(string filepath);
void toforest2();
void next1(vector<int> forward, int root);
void next2(vector<int> forward, int root);
void findlongest();
int listlength(int index);
void printtofile(int index);
vector<node> map;//����ͼ
vector<vector<int>> forest;
bool if_w = false;
bool if_c = false;
bool if_h = false;
bool if_t = false;
bool if_r = false;
char head_alpha = ' ';
char tail_alpha = ' ';
/*----------------------------------------------------------------*/
int main(int argc, char* argv[])
{	
	string filepath;
	char* parameter;
	int i = 0;
	/*----------------------�����в�������---------------------------*/
	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
		{
			parameter = argv[i];
			if (strcmp(parameter, "-h") == 0)
			{
				if (if_h)
				{
					cout << "����-h�����ظ�" << endl;
				}
				if_h = true;
				i++;
				parameter = argv[i];
				if (strlen(parameter) == 1 && isalpha(parameter[0]))
				{
					head_alpha = parameter[0];
				}
				else
				{
					cout << "����-h��û����ĸ" << endl;
				}
			}
			else if (strcmp(parameter, "-t") == 0)
			{
				if (if_t)
				{
					cout << "����-t�����ظ�" << endl;
				}
				if_t = true;
				i++;
				parameter = argv[i];
				if (strlen(parameter) == 1 && isalpha(parameter[0]))
				{
					tail_alpha = parameter[0];
				}
				else
				{
					cout << "����-t��û����ĸ" << endl;
				}
			}
			else if (strcmp(parameter, "-r") == 0)
			{
				if (if_r)
				{
					cout << "����-r�����ظ�" << endl;
				}
				if_r = true;
			}
			else if (strcmp(parameter, "-w") == 0)
			{
				if (if_w || if_c)
				{
					cout << "����-w\-c�����ظ�" << endl;
				}
				if_w = true;
				i++;
				filepath = argv[i];
//				readfile(filepath);				
			}
			else if (strcmp(parameter, "-c") == 0)
			{
				if (if_w || if_c)
				{
					cout << "����-w\-c�����ظ�" << endl;
				}
				if_c = true;
				i++;
				filepath = argv[i];
//				readfile(filepath);
			}
			else {
				cout << "���󣺲�������" << endl;
			}
		}
	}
	else {
		cout << "��������" << endl;
	}
	wordlist(filepath);
	return 0;
}
void wordlist(string filepath)
{

	readfile(filepath);
//	printmap();
//	toforest();
	toforest2();
//	printforest();
	if (if_w)
	{
		findmostwords(head_alpha,tail_alpha);
	}
	else if (if_c)
	{
		findlongest();
	}
//	findmostwords();
	
}
void findmostwords(char head, char tail)//�ҳ����������� -w
{
	int i = 0;
	int tempmax = 0;
	int tempindex = -1;
	if (isalpha(head) && !isalpha(tail))//ֻ�涨����������ĸ
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
	else if (!isalpha(head) && isalpha(tail))//ֻ�涨������β��ĸ
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
	else if(isalpha(head) && isalpha(tail)){//�涨����ĸ��β��ĸ
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax && map[forest[i][0]].head == head && map[forest[i].back()].tail == tail)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	else {//û�й涨
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
		printdetail(tempindex);
		printtofile(tempindex);
	}
}
void printdetail(int index)
{
	int i = 0;
	for (i = 0; i < forest[index].size(); i++) 
	{
		cout << map[forest[index][i]].nodeword << endl;
	}
}

void toforest2()
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
void next1(vector<int>forward, int root)
{
	int i = 0;
	for (i = 0; i < forward.size(); i++) {
		if (forward[i] == root)//�л�
		{
			if (!if_r)
			{
				cout << "���� ���е��ʻ�" << endl;
				
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
void next2(vector<int>forward,int root)//ϸ��
{
	int i = 0;
	for (i = 0; i < forward.size(); i++) {
		if (forward[i] == root)//�л�
		{
			if (!if_r)
			{
				cout << "���� ���е��ʻ�" << endl;

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
vector<vector<int>> next(int root)
{
	vector<vector<int>> nodes;
	int i = 0;
	if (map[root].next.size() == 0)
	{
		vector<int> singlenode;
		singlenode.push_back(root);
		nodes.push_back(singlenode);
		return nodes;
	}
	else {
		for (i = 0; i < map[root].next.size(); i++)
		{
			vector<vector<int>> tempnodes;
			tempnodes = next(map[root].next[i]);
			int j = 0;
			for (j = 0; j < tempnodes.size(); j++)
			{
				tempnodes[j].insert(tempnodes[j].begin(), root);
			}
			nodes.insert(nodes.end(), tempnodes.begin(), tempnodes.end());
		}
		return nodes;
	}
}
void newnode(string word)//����µ���
{
	node newword;
	newword.nodeword = word;
	newword.head = word[0];
	newword.tail = word.back();
	newword.wordlen = word.length();
	//�ѵ��ʼ���ͼ
	addtomap(newword);
}
void addtomap(node newword) 
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
	for (i = 0 ; i < index; i++)
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
void printmap() 
{
	cout << "------------Map Detail------------" << endl;
	int i = 0;
	for (i = 0; i < map.size(); i++)
	{
		cout << i << "  ";
		printnode(map[i]);
	}
}
void printnode(node n) {
	cout << n.nodeword << "  ";
	int i = 0;
	for (i = 0; i < n.next.size(); i++)
	{
		cout << n.next[i] << "  ";
	}
	cout << endl;
}
void printforest()
{
	cout << "----------All List---------" << endl;
	int i = 0;
	int j = 0;
	cout << "forest_size = " << forest.size() << endl;
	for (i = 0; i < forest.size(); i++)
	{
		for (j = 0; j < forest[i].size(); j++)
		{
			cout << forest[i][j] << " --> ";
		}
		cout << endl;
	}
}
void readfile(string filepath)
{
	ifstream infile;
	infile.open(filepath);
	if (!infile)
	{
		cout << "�ļ�������" << endl;
	}
	char ch;
	string word;
	while (!infile.eof())
	{
		ch = infile.get();
		if (isalpha(ch))
		{
			if (isupper(ch))//��дת��ΪСд
			{
				ch = tolower(ch);
			}
			word += ch;
		}
		else{
			if (word.length() > 0)
			{
				//cout << word << endl;
				//�������ʺ�Ĳ������ѵ��ʼ��뵥�ʱ�
				newnode(word);

				word.erase();
			}
		}
	}
	infile.close();
}

void findlongest()//����ĸ������
{
	int i = 0;
	int templong = 0;
	int tempindex = -1;
	int length = 0;
	if (if_h && !if_t)
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (map[forest[i][0]].head == head_alpha)
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
			if (map[forest[i].back()].tail == tail_alpha)
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
			if (map[forest[i][0]].head == head_alpha && map[forest[i].back()].tail == tail_alpha)
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
	if (forest[tempindex].size() > 1)
	{
		printdetail(tempindex);
		printtofile(tempindex);
	}
	
}
int listlength(int index)
{
	int sum = 0;
	int i = 0;
	for (i = 0; i < forest[index].size(); i++)
	{
		sum += map[forest[index][i]].wordlen;
	}
	return sum;
}
void printtofile(int index)
{
	ofstream outfile;
	outfile.open("solution.txt");
	int i = 0;
	for (i = 0; i < forest[index].size(); i++)
	{
		outfile << map[forest[index][i]].nodeword << endl;
	}
	outfile.close();
}