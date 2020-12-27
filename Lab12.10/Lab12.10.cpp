#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

typedef string Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};

void FLines(string* Check_Identifier_After, int*& lines);
int alines();
void plines(int* lines);
void StTI(Node*& root, string* Check_Identifier_After, int* lines);
void pTree(Node* root, int level);
Node* Insert(Node* p, Info info);
Node* balanceHeight(Node* p);
int BFactor(Node* root);
Node* leftRotation(Node* q);
Node* rightRotation(Node* p);
int Height(Node* root);
Node* FindMin(Node* root);
Node* deleteMin(Node* p);
Node* Delete(Node* p, Info info);
void FindElem(Node*& root, Info info);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Node* root = NULL;
	int action, nodeCount = 1;
	int* lines = new int[alines()];
	string Check_Identifier_After[] = { "char ", "int ", "double ", "string ", "float ", "void ",
									   ", ", "bool " };
	string* TreeElemnts = new string[100];
	bool repeat;
	Info value;

	do
	{
		cout << endl << endl;
		cout << "Оберіть дію: " << endl;
		cout << "1 - Знайти номери рядків, що містять ідентифікатори" << endl;
		cout << "2 - Зберегти номери рядків, ідентифікатори у дерево" << endl;
		cout << "3 - Вивести дерево на екран" << endl;
		cout << "0 - Завершити роботу програми" << endl;
		cout << "Введіть: "; cin >> action;

		switch (action)
		{
		case 1:
			cout << "Рядки в яких знайдено ідентифікатори: ";
			FLines(Check_Identifier_After, lines);
			plines(lines);
			cout << endl << endl << endl;
			break;
		case 2:
			StTI(root, Check_Identifier_After, lines);
			break;
		case 3:
			pTree(root, 0);
			break;
		case 6:
			cin.get(); cin.sync();
			cout << "Введіть: "; getline(cin, value);
			FindElem(root, value);
			pTree(root, 0);
			break;
		case 0:
			exit(0);
		default:
			cout << "\nПомилка!" << endl;
			repeat = 1;
		}

	} while (action == 1 ||
		action == 2 ||
		action == 3 ||
		action == 4 ||
		action == 5 ||
		action == 6 || repeat == 1);

	return 0;
}
void pTree(Node* root, int level)
{
	if (root != NULL)
	{
		pTree(root->right, level + 1);

		for (int i = 1; i <= level; i++)
			cout << "                ";
		cout << root->info << endl;

		pTree(root->left, level + 1);
	}
}
Node* FindMin(Node* root)
{
	if (root->left != NULL)
		return FindMin(root->left);
	else
		return root;
}
Node* deleteMin(Node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = deleteMin(p->left);
	return balanceHeight(p);
}
void StTI(Node*& root, string* Check_Identifier_After, int* lines)
{
	ifstream f("test.txt", ios::in);

	string tmp,
		what_to_save;

	int i = 1,
		j = 0,
		size = alines();

	for (i; i < size; i++)
	{
		getline(f, tmp);

		if (i == lines[j])
		{
			for (int k = 0; k < sizeof(Check_Identifier_After); k++)
			{
				int pos = tmp.find(Check_Identifier_After[k]);

				if (pos != -1)
				{
					pos += Check_Identifier_After[k].length();

					what_to_save += to_string(i) + " ";

					for (pos; pos < tmp.length(); pos++)
					{
						if (tmp[pos] == ';' ||
							tmp[pos] == '(' ||
							tmp[pos] == '=' ||
							tmp[pos] == '[')
							break;
						else
							what_to_save += tmp[pos];
					}
					root = Insert(root, what_to_save);
					what_to_save = "";
				}
			}
			j++;
		}
	}
}
int Height(Node* root)
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);

	return (hL > hR ? hL : hR) + 1;
}
Node* rightRotation(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	return q;
}
Node* leftRotation(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	return p;
}

int BFactor(Node* root)
{
	return Height(root->right) - Height(root->left);
}
Node* balanceHeight(Node* p)
{
	if (BFactor(p) == 2)
	{
		if (BFactor(p->right) < 0)
			p->right = rightRotation(p->right);
		return leftRotation(p);
	}
	if (BFactor(p) == -2)
	{
		if (BFactor(p->left) > 0)
			p->left = leftRotation(p->left);
		return rightRotation(p);
	}
	return p;
}

int alines()
{
	int count = 0;
	ifstream f("test.txt", ios::in);

	string tmp;
	while (!f.eof())
	{
		getline(f, tmp);
		count++;
	}
	return count;
}
void FLines(string* Check_Identifier_After, int*& lines)
{
	ifstream f("test.txt", ios::in);

	string tmp;

	int counter = 0,
		index_arr = 0;

	while (!f.eof())
	{
		getline(f, tmp);

		counter++;
		for (int j = 0; j < sizeof(Check_Identifier_After); j++)
		{
			size_t pos = tmp.find(Check_Identifier_After[j]);
			if (pos != -1)
			{
				lines[index_arr++] = counter;
				break;
			}
		}
	}
	lines[index_arr] = '/0';
}
void plines(int* lines)
{
	int i = 0;
	while (lines[i] != '/0')
		cout << lines[i++] << " ";
}