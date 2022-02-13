#include <iostream>
#include <vector>
using namespace std;

bool oddnumb(int number) //определяет, четное ли количество цифр в числе
{
	int n = 0;
	while (number != 0)
	{
		number /= 10;
		n++;
	}
	return (n % 2 == 0);
}

bool fleq(int number) //определяет, равны ли первая и последняя цифры в числе
{
	int l = number % 10;
	while (abs(number) > 9) number /= 10;
	int f = number % 10;
	return(l == f);
}

bool haszero(int number) //определяет, содержит ли число цифру 0
{
	if (number == 0) return 1;
	bool zero = 0;

	while (number != 0)
	{
		if (number % 10 == 0) zero = 1;
		number /= 10;
	}
	return zero;
}

int func1static(int mas[], int& n, int n_max, int newelem) //Вставить новый элемент в массив перед элементом, у которого четное количество цифр
{
	//определяем, есть ли место для нового элемента
	if (n == n_max)
		return -1;

	//ищем первое вхождение элемента с четным количеством цифр
	bool flag = 0;
	int i = 0;
	while (flag == 0 && i < n)
	{
		if (oddnumb(mas[i])) flag = 1;
		else i++;
	}
	if (flag == 0)
		return -2;

	//сдвигаем правую часть массива на 1 элемент и вставляем новый элемент
	for (int j = n; j > i; j--)
		mas[j] = mas[j - 1];
	mas[i] = newelem;
	n++;
	return 0;
}

int func1dynamic(int*& mas, int& n, int newelem) //Вставить новый элемент в массив перед элементом, у которого четное количество цифр
{
	//ищем первое вхождение элемента с четным количеством цифр
	bool flag = 0;
	int i = 0;
	while (flag == 0 && i < n)
	{
		if (oddnumb(mas[i])) flag = 1;
		else i++;
	}
	if (flag == 0)
		return -2;

	//расширяем область памяти, сдвигаем правую часть массива на 1 элемент и вставляем новый элемент
	mas = (int*)realloc(mas, (n + 1) * sizeof(int));
	for (int j = n; j > i; j--)
		mas[j] = mas[j - 1];
	mas[i] = newelem;
	n++;
	return 0;
}

int func1vector(vector<int>& vec, int newelem) //Вставить новый элемент в массив перед элементом, у которого четное количество цифр
{
	//ищем первое вхождение элемента с четным количеством цифр
	bool flag = 0;
	int i = 0;
	while (flag == 0 && i < vec.size())
	{
		if (oddnumb(vec[i])) flag = 1;
		else i++;
	}
	if (flag == 0)
		return -2;

	vec.insert(vec.begin() + i, newelem);
	return 0;
}

int func2static(int mas[], int n)
{
	int i = 0, last = -1;
	while (i < n)
	{
		if (fleq(mas[i])) last = i;
		i++;
	}
	return last;
}

int func2dynamic(int* mas, int n)
{
	int i = 0, last = -1;
	while (i < n)
	{
		if (fleq(mas[i])) last = i;
		i++;
	}
	return last;
}

int func2vector(vector<int> vec)
{
	int i = 0, last = -1;
	while (i < vec.size())
	{
		if (fleq(vec[i])) last = i;
		i++;
	}
	return last;
}

void func3static(int mas[], int& n) //Удалить элементы массива, значение которого содержит цифру 0
{
	int i = 0;
	while (i < n)
		if (haszero(mas[i]))
		{
			for (int j = i; j < n - 1; j++)
				mas[j] = mas[j + 1];
			n--;
		}
		else i++;
}

void func3dynamic(int*& mas, int& n) //Удалить элементы массива, значение которого содержит цифру 0
{
	int i = 0;
	while (i < n)
		if (haszero(mas[i]))
		{
			for (int j = i; j < n - 1; j++)
				mas[j] = mas[j + 1];
			n--;
			mas = (int*)realloc(mas, n * sizeof(int));
		}
		else i++;
}

void func3vector(vector<int>& vec) //Удалить элементы массива, значение которого содержит цифру 0
{
	int i = 0;
	while (i < vec.size())
		if (haszero(vec[i]))
			vec.erase(vec.begin() + i);
		else i++;
}

int main()
{
	setlocale(0, "russian");
	int menu, n_static, n_dynamic, n_vector, tempint;
	int* mas_dynamic;
	vector<int> mas_vector;
	const int n_static_max = 10;
	do
	{
		cout << "1:static, 2:dynamic, 3:vector\n";
		cin >> menu;
		switch (menu)
		{
		case 1: //static
			int mas_static[n_static_max];
			cout << "сколько ввести элементов: ";
			n_static = 0;
			do
			{
				cin >> n_static;
			} while (n_static > n_static_max);
			cout << "введите " << n_static << " элементов: ";
			for (int i = 0; i < n_static; i++) cin >> mas_static[i];
			cout << "array: ";
			for (int j = 0; j < n_static; j++) cout << mas_static[j] << " ";
			cout << endl;

			do
			{
				cout << "1:func1, 2:func2, 3:func3\n";
				cin >> menu;
				switch (menu)
				{

				case 1:
					cout << "new number: ";
					cin >> tempint;
					switch (func1static(mas_static, n_static, n_static_max, tempint))
					{
					case -1:
						cout << "no space\n";
						break;
					case -2:
						cout << "no number\n";
						break;
					case 0:
						cout << "array: ";
						for (int j = 0; j < n_static; j++) cout << mas_static[j] << " ";
						cout << endl;
						break;
					}
					break;
				case 2://Найти последнее вхождение в массив числа, у которого равны первая и последняя цифры
					tempint = func2static(mas_static, n_static);
					if (tempint > -1)
						cout << "last fleq: " << mas_static[tempint] << " at " << tempint << endl;
					else cout << "no fleq\n";
					break;

				case 3://Удалить элементы массива, значение которого содержит цифру 0
					func3static(mas_static, n_static);
					cout << "array: ";
					for (int j = 0; j < n_static; j++) cout << mas_static[j] << " ";
					cout << endl;
					break;
				}
			} while (menu != 0);
			break;





		case 2: //dynamic
			cout << "сколько ввести элементов: ";
			n_dynamic = 0;
			cin >> n_dynamic;
			mas_dynamic = new int[n_dynamic];
			cout << "введите " << n_dynamic << " элементов: ";
			for (int i = 0; i < n_dynamic; i++) cin >> mas_dynamic[i];
			cout << "array: ";
			for (int j = 0; j < n_dynamic; j++) cout << mas_dynamic[j] << " ";
			cout << endl;

			do
			{
				cout << "1:func1, 2:func2, 3:func3\n";
				cin >> menu;
				bool flag = 0;
				int i = 0, i2 = 0, i3 = 0;
				int last = -1;
				switch (menu)
				{
				case 1:
					cout << "new number: ";
					cin >> tempint;
					switch (func1dynamic(mas_dynamic, n_dynamic, tempint))
					{
					case -2:
						cout << "no number\n";
						break;
					case 0:
						cout << "array: ";
						for (int j = 0; j < n_dynamic; j++) cout << mas_dynamic[j] << " ";
						cout << endl;
						break;
					}
					break;

				case 2://Найти последнее вхождение в массив числа, у которого равны первая и последняя цифры
					tempint = func2dynamic(mas_dynamic, n_dynamic);
					if (tempint > -1)
						cout << "last fleq: " << mas_dynamic[tempint] << " at " << tempint << endl;
					else cout << "no fleq\n";
					break;

				case 3://Удалить элементы массива, значение которого содержит цифру 0
					func3dynamic(mas_dynamic, n_dynamic);
					cout << "array: ";
					for (int j = 0; j < n_dynamic; j++) cout << mas_dynamic[j] << " ";
					cout << endl;
					break;
				}
			} while (menu != 0);
			break;

		case 3: //vector
			cout << "сколько ввести элементов: ";
			cin >> n_vector;
			cout << "введите " << n_vector << " элементов: ";
			for (int i = 0; i < n_vector; i++)
			{
				cin >> tempint;
				mas_vector.push_back(tempint);
			}
			cout << "array: ";
			for (int j = 0; j < mas_vector.size(); j++) cout << mas_vector[j] << " ";
			cout << endl;

			do
			{
				cout << "1:func1, 2:func2, 3:func3\n";
				cin >> menu;
				bool flag = 0;
				int i = 0, i2 = 0, i3 = 0;
				int last = -1;
				switch (menu)
				{

				case 1: //Вставить новый элемент в массив перед элементом, у которого четное количество цифр
					cout << "new number: ";
					cin >> tempint;
					switch (func1vector(mas_vector, tempint))
					{
					case -2:
						cout << "no number\n";
						break;
					case 0:
						cout << "array: ";
						for (int j = 0; j < mas_vector.size(); j++) cout << mas_vector[j] << " ";
						cout << endl;
						break;
					}
					break;
				case 2: //Найти последнее вхождение в массив числа, у которого равны первая и последняя цифры
					tempint = func2vector(mas_vector);
					if (tempint > -1)
						cout << "last fleq: " << mas_vector[tempint] << " at " << tempint << endl;
					else cout << "no fleq\n";
					break;

				case 3: //Удалить элементы массива, значение которого содержит цифру 0
					func3vector(mas_vector);

					cout << "array: ";
					for (int j = 0; j < mas_vector.size(); j++) cout << mas_vector[j] << " ";
					cout << endl;
					break;
				}
			} while (menu != 0);
			break;
		}
	} while (menu != 0);
}