#include <iostream>
using namespace std;

class String
{

private:

	static const int SZ = 80; // ���� ������ ������
	char* str; // ������

	int strlen(char* s) // ����� ������
	{
		for (int i = 0; i < SZ; i++) if (s[i] == '\0')
		{
			return i;
		}
		cout << "Bred" << endl;
	}

	void strcpy(char* s) // �������� ������
	{
		if (strlen(s) < SZ)
			for (int i = 0; i < strlen(s) + 1; i++)
				str[i] = s[i];
	}

	void copy(char* s, int length) // �����������
	{
		int i;
		for (i = 0; i < length + 1; i++)
		{
			str[i] = s[i];
		}
		str[i] = '\0';
	}

	void init() // �������������� ������
	{
		str = new char[SZ]; // ������ ������
		str[0] = '\0'; // ������� ������ � �����
	}

public:

	String()
	{
		init();
	} // ������. ��� ����������

	String(char* s)
	{
		init();
		strcpy(s);
	} // ������. � 1 ���.

	String(String& s)
	{
		init();
		strcpy(s.getstr());
	}

	char* getstr()
	{
		return str;
	}

	int strlen()
	{
		return strlen(str);
	}

	void strcpy(String& s)
	{
		return strcpy(s.getstr());
	}

	void copy(String& s, int length)
	{
		return copy(s.getstr(), length);
	}

	void concat(char* s) // �������� �����
	{
		int j = strlen();
		int k = strlen(s);
		if ((j + k + 1) > SZ)
		{
			cout << "������������" << endl;
			return;
		}
		for (int i = 0; i < k + 1; i++)
		{
			str[j + i] = s[i];
		}

	}

	void concat(String& s) // �������� �����
	{
		concat(s.getstr());
	}

	void split(int n, String& part1, String& part2) // ����������
	{
		int j = strlen();

		part1.copy(str, n - 1);
		part2.copy(str + n, j);
	}

	String insert(int n, String& substr) // �����������
	{
		String str1;
		String str2;

		split(n, str1, str2);
		str1.concat(substr);
		str1.concat(str2);
		return str1;
	}

	int startIndex(String& s) // ������ ������� ���������
	{
		if (s.strlen() > strlen()) // ���������� ����� ������ � ���������
		{
			return -1;
		}

		int q = 0;
		for (int i = 0; i < strlen(); i++) // ���� �� ��������� � ���������� �� �����������
		{
			if (str[i] != s.str[q])
			{
				q = 0;
			}
			if (str[i] == s.str[q])
			{
				q++;
			}

			if (q == s.strlen())
			{
				return i - q + 1; // ������ ������� ���������
			}
		}

		return -1;
	}

	bool search(String& s)
	{
		return startIndex(s) != -1;
	}

	String replace(String& s1, String& s2) //����������� ������
	{
		int index = startIndex(s1);

		if (index == -1)
		{
			return str;
		}

		String str1;
		String str2;
		String str3;
		String str4;

		split(index, str1, str2); //�����, ����������
		str2.split(s1.strlen(), str3, str4);
		str1.concat(s2);
		str1.concat(str4);

		return str1;

	}

	String remove(String& s) //������������ ���������
	{
		String str1((char*)"");
		String str2;
		str2 = replace(s, str1); // ������ �� ������ ������
		return str2;

	}

	void display() // ����� ������
	{
		cout << str << endl;
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");

	String s1((char*)"ABCD");
	String s2((char*)"ZXC");

	// ���������
	String s3((char*)"wewe");
	String s4((char*)"oao");
	String s5((char*)"tratata");

	// ������ ������
	String s6; //������������, ����������, �����������
	String s7; //����������� ������
	String s8; //������������ ���������

	s6.strcpy(s1); s6.display();
	s2.display();

	cout << "" << endl;

	// ������������
	cout << "������������:" << endl;
	s6.concat(s2); s6.display();

	cout << "" << endl;

	// ����������
	cout << "����������:" << endl;
	s6.display();
	s6.split(s1.strlen(), s1, s2);
	s1.display();
	s2.display();

	cout << "" << endl;

	// �����������
	cout << "�����������:" << endl;
	s6.display();
	s3.display();
	s4 = s6.insert(s1.strlen(), s3); s4.display();

	cout << "" << endl;

	// ����������� ������
	cout << "����������� ������:" << endl;
	s4.display();
	s7 = s4.replace(s3, s5); s7.display();

	cout << "" << endl;

	// ������������ ���������
	cout << "������������ ���������:" << endl;
	s7.display();
	s8 = s7.remove(s5); s8.display();

	system("pause");
	return 0;
}