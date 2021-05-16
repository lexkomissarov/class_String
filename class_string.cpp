#include <iostream>
using namespace std;

class String
{

private:

	static const int SZ = 80; // макс размер строки
	char* str; // строка

	int strlen(char* s) // длина строки
	{
		for (int i = 0; i < SZ; i++) if (s[i] == '\0')
		{
			return i;
		}
		cout << "Bred" << endl;
	}

	void strcpy(char* s) // копируем строку
	{
		if (strlen(s) < SZ)
			for (int i = 0; i < strlen(s) + 1; i++)
				str[i] = s[i];
	}

	void copy(char* s, int length) // копирование
	{
		int i;
		for (i = 0; i < length + 1; i++)
		{
			str[i] = s[i];
		}
		str[i] = '\0';
	}

	void init() // инициализируем строку
	{
		str = new char[SZ]; // размер строки
		str[0] = '\0'; // нулевой символ в конце
	}

public:

	String()
	{
		init();
	} // констр. без параметров

	String(char* s)
	{
		init();
		strcpy(s);
	} // констр. с 1 пар.

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

	void concat(char* s) // сложение строк
	{
		int j = strlen();
		int k = strlen(s);
		if ((j + k + 1) > SZ)
		{
			cout << "ѕереполнение" << endl;
			return;
		}
		for (int i = 0; i < k + 1; i++)
		{
			str[j + i] = s[i];
		}

	}

	void concat(String& s) // сложение строк
	{
		concat(s.getstr());
	}

	void split(int n, String& part1, String& part2) // разделение
	{
		int j = strlen();

		part1.copy(str, n - 1);
		part2.copy(str + n, j);
	}

	String insert(int n, String& substr) // подстановка
	{
		String str1;
		String str2;

		split(n, str1, str2);
		str1.concat(substr);
		str1.concat(str2);
		return str1;
	}

	int startIndex(String& s) // первый элемент подстроки
	{
		if (s.strlen() > strlen()) // сравниваем длину строки и подстроки
		{
			return -1;
		}

		int q = 0;
		for (int i = 0; i < strlen(); i++) // идем по элементам и запоминаем их колличество
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
				return i - q + 1; // первый элемент подстроки
			}
		}

		return -1;
	}

	bool search(String& s)
	{
		return startIndex(s) != -1;
	}

	String replace(String& s1, String& s2) //контекстна€ замена
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

		split(index, str1, str2); //делим, складываем
		str2.split(s1.strlen(), str3, str4);
		str1.concat(s2);
		str1.concat(str4);

		return str1;

	}

	String remove(String& s) //вычеркивание подстроки
	{
		String str1((char*)"");
		String str2;
		str2 = replace(s, str1); // замена на пустую строку
		return str2;

	}

	void display() // показ строки
	{
		cout << str << endl;
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");

	String s1((char*)"ABCD");
	String s2((char*)"ZXC");

	// ѕодстроки
	String s3((char*)"wewe");
	String s4((char*)"oao");
	String s5((char*)"tratata");

	// ѕустые строки
	String s6; //конкатинаци€, разделение, подстановка
	String s7; //контекстна€ замена
	String s8; //вычеркивание подстроки

	s6.strcpy(s1); s6.display();
	s2.display();

	cout << "" << endl;

	//  онкатенаци€
	cout << " онкатенаци€:" << endl;
	s6.concat(s2); s6.display();

	cout << "" << endl;

	// –азделение
	cout << "–азделение:" << endl;
	s6.display();
	s6.split(s1.strlen(), s1, s2);
	s1.display();
	s2.display();

	cout << "" << endl;

	// ѕодстановка
	cout << "ѕодстановка:" << endl;
	s6.display();
	s3.display();
	s4 = s6.insert(s1.strlen(), s3); s4.display();

	cout << "" << endl;

	//  онтекстна€ замена
	cout << " онтекстна€ замена:" << endl;
	s4.display();
	s7 = s4.replace(s3, s5); s7.display();

	cout << "" << endl;

	// ¬ычеркивание подстроки
	cout << "¬ычеркивание подстроки:" << endl;
	s7.display();
	s8 = s7.remove(s5); s8.display();

	system("pause");
	return 0;
}