#include <iostream>
using namespace std;

//Индекс первого вхождения минимального значения среди отрицательных чисел массива
int func1static(int mas[], int n) {
    int min_i = -1;
    int neg_num = 0;
    for (int i = 0; i < n; i++)
    {
        if (mas[i] < neg_num) {
            neg_num = mas[i];
            min_i = i;
        }
    }
    if (min_i != -1)
        return min_i;
    else
        return -1;
}


int func2static(int mas[], int n, int n_max, int newelem) 
{
	//определяем, есть ли место для нового элемента
	if (n == n_max)
		return -1;

    //нахождение индекса минимального элемента массива
    int min_elem = mas[0];
    int min_i = 0;
    for (int i = 1; i < n; i++)
    {
        if (mas[i] < min_elem) {
            min_elem = mas[i];
            min_i = i;
        }
    }

	//сдвигаем правую часть массива на 1 элемент и вставляем новый элемент
	for (int j = n; j > min_i; j--)
		mas[j] = mas[j - 1];
	mas[min_i+1] = newelem;
	return 0;
}

void func3static(int mas[], int& n, int k) //Удалить все элементы массива равные минимальному значению в массиве среди отрицательных чисел
{
    int p = mas[k];
    for (int i = 0; i < n; i++)
        if (k != -1 && mas[i] == p) {
            for (int j = i; j < n - 1; j++) //удаление переносом
                mas[j] = mas[j + 1];
            i--;
            n--;
        }
}



int main()
{
    
    setlocale(0, "russian");
    int menu, n_static, tempint, kolv_min_el;
    int k = 1;
    const int n_static_max = 10;
    do {
        cout << "1:static, 2:dynamic, 3:vector\n";
        cin >> menu;
        switch (menu)
        {
        case 1: //static
            int mas_static[n_static_max];
            cout << "Сколько ввести элементов(не больше 10): ";
            n_static = 0;
            do
            {
                if (n_static > 10) {
                    cout << "Можно ввести не больше 10 элементов. Введите ещё раз:";
                }
                cin >> n_static;
            } while (n_static > n_static_max);
            cout << "Введите " << n_static << " элементов: ";
            for (int i = 0; i < n_static; i++) cin >> mas_static[i];
            cout << "Полученный массив: ";
            for (int j = 0; j < n_static; j++) cout << mas_static[j] << " ";
            cout << endl;

            do {
                cout << "\n1:Нахождение индекса первого вхождения минимального значения среди отрицательных чисел массива;\n2:Вставить новый элемент после первого минимального элемента массива;\n3:Удалить все элементы массива равные минимальному значению в массиве среди отрицательных чисел(если такие есть);\n";
                cin >> menu;
                switch (menu) {
                case 1:
                    switch (func1static(mas_static, n_static)) {
                    case -1:
                        cout << "В массиве нет отрицательных чисел.\n";
                        break;
                    default:
                        cout << "Индекс минимального отрицательного числа равен: " << func1static(mas_static, n_static) << endl;
                        break;
                    }
                    break;
                case 2:
                    cout << "Новый элемент: ";
                    cin >> tempint;
                    switch (func2static(mas_static, n_static, n_static_max, tempint))
                    {
                    case -1:
                        cout << "Переполнение памяти\n";
                        break;
                    case 0:
                        cout << "Массив: ";
                        n_static += 1;
                        for (int j = 0; j < n_static; j++) cout << mas_static[j] << " ";
                        cout << endl;
                        break;
                    }
                    break;
                case 3:
                    int k = func1static(mas_static, n_static);
                    func3static(mas_static, n_static, k);
                    if (k == -1)
                        cout << "Нет отрицательных чисел в массиве. Массив остался таким же: ";
                    for (int j = 0; j < n_static; j++) cout << mas_static[j] << " ";
                    cout << endl;
                }
            } while (menu != 0);

        }
    } while (menu != 0);
}