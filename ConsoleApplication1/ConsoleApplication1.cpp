#include <iostream>
#include <vector>
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

int func1vector(vector<int>& vec) {
    int min_i = -1;
    int neg_num = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] < neg_num) {
            neg_num = vec[i];
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

int func2dynamic(int*& mas, int& n, int newelem)
{
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
    
    //расширяем область памяти, сдвигаем правую часть массива на 1 элемент и вставляем новый элемент
    mas = (int*)realloc(mas, (n + 1) * sizeof(int));
    for (int j = n; j > min_i+1; j--)
        mas[j] = mas[j - 1];
    mas[min_i+1] = newelem;
    n++;
    return 0;
}

int func2vector(vector<int>& vec, int newelem) {

    //нахождение индекса минимального элемента массива
    int min_elem = vec[0];
    int min_i = 0;
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] < min_elem) {
            min_elem = vec[i];
            min_i = i;
        }
    }

    vec.insert(vec.begin() + min_i + 1, newelem);

    return 0;
}

//Удалить все элементы массива равные минимальному значению в массиве среди отрицательных чисел
void func3static(int mas[], int& n, int k) 
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

void func3dynamic(int*& mas, int& n, int k)
{
    int p = mas[k];
    for (int i = 0; i < n; i++)
        if (k != -1 && mas[i] == p) {
            for (int j = i; j < n - 1; j++) //удаление переносом
                mas[j] = mas[j + 1];
            i--;
            n--;
            mas = (int*)realloc(mas, n * sizeof(int));
        }
}

void func3vector(vector<int>& vec, int v) {
    if (v != -1)
    {
        int min_znach = vec[v];
        for (int i = 0; i < vec.size(); i++)
            if (vec[i] == min_znach) {
                vec.erase(vec.begin() + i);
                i--;
            }
    }
    else
        cout << "Нет отрицательных чисел в массиве. Массив остался таким же: ";
    
}



int main()
{
    
    setlocale(0, "russian");
    int menu, n_static, tempint, kolv_min_el, n_vector, n_dynamic;
    int* mas_dynamic;
    vector<int> mas_vector;
    int k = 1;
    const int n_static_max = 10;
    do {
        cout << "1: Static, 2: Dynamic, 3: Vector\n";
        cin >> menu;
        switch (menu)
        {

        #pragma region case1
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
                    else
                        cout << "Получившийся массив: ";
                    for (int j = 0; j < n_static; j++) cout << mas_static[j] << " ";
                    cout << endl;
                    break;
                }
            } while (menu != 0);



        #pragma endregion


        case 2: //dynamic
            cout << "Сколько ввести элементов: ";
            n_dynamic = 0;
            cin >> n_dynamic;
            mas_dynamic = new int[n_dynamic];
            cout << "Введите " << n_dynamic << " элементов: ";
            for (int i = 0; i < n_dynamic; i++) cin >> mas_dynamic[i];
            cout << "Полученный массив: ";
            for (int j = 0; j < n_dynamic; j++) cout << mas_dynamic[j] << " ";
            cout << endl;

            do
            {
                cout << "\n1:Нахождение индекса первого вхождения минимального значения среди отрицательных чисел массива;\n2:Вставить новый элемент после первого минимального элемента массива;\n3:Удалить все элементы массива равные минимальному значению в массиве среди отрицательных чисел(если такие есть);\n";
                cin >> menu;
                switch (menu)
                {
                case 1:
                    switch (func1static(mas_dynamic, n_dynamic)) {
                    case -1:
                        cout << "Нет отрицательного числа.\n";
                        break;
                    default:
                        cout << "Индекс минимального отрицательного числа равен: " << func1static(mas_dynamic, n_dynamic) << endl;
                        break;
                    }
                    break;
                case 2:
                    cout << "Новый элемент: ";
                    cin >> tempint;
                    func2dynamic(mas_dynamic, n_dynamic, tempint);
                    cout << "Массив: ";
                    for (int j = 0; j < n_dynamic; j++) cout << mas_dynamic[j] << " ";
                    cout << endl;
                    break;
                case 3:
                    int k = func1static(mas_dynamic, n_dynamic);
                    func3dynamic(mas_dynamic, n_dynamic, k);
                    if (k == -1)
                        cout << "Нет отрицательных чисел в массиве. Массив остался таким же: ";
                    else
                        cout << "Получившийся массив: ";
                    for (int j = 0; j < n_dynamic; j++) cout << mas_dynamic[j] << " ";
                    cout << endl;
                    break;
                }
            } while (menu != 0);
            break;


        case 3: //vector
            cout << "Сколько ввести элементов: ";
            cin >> n_vector;
            cout << "Введите " << n_vector << " элементов: ";
            for (int i = 0; i < n_vector; i++)
            {
                cin >> tempint;
                mas_vector.push_back(tempint);
            }
            cout << "Введенный массив: ";
            for (int j = 0; j < mas_vector.size(); j++) cout << mas_vector[j] << " ";
            cout << endl;

            do
            {
                cout << "\n1:Нахождение индекса первого вхождения минимального значения среди отрицательных чисел массива;\n2:Вставить новый элемент после первого минимального элемента массива;\n3:Удалить все элементы массива равные минимальному значению в массиве среди отрицательных чисел(если такие есть);\n";
                cin >> menu;
                switch (menu)
                {
                case 1: //Найти индекс первого вхождения минимального значения среди отрицательных чисел массива. 
                    switch (func1vector(mas_vector)) {
                    case -1:
                        cout << "В массиве нет отрицательных чисел.\n";
                        break;
                    default:
                        cout << "Индекс минимального отрицательного числа равен: " << func1vector(mas_vector) << endl;
                        break;
                    }
                    break;
                case 2:
                    cout << "Новый элемент: ";
                    cin >> tempint;
                    func2vector(mas_vector, tempint);
                    cout << "Массив: ";
                    for (int j = 0; j < mas_vector.size(); j++) cout << mas_vector[j] << " ";
                    cout << endl;
                    break;
                case 3:
                    int k = func1vector(mas_vector);
                    func3vector(mas_vector, k);
                    if (k != -1)
                        cout << "Получившийся массив: ";
                    for (int j = 0; j < mas_vector.size(); j++) cout << mas_vector[j] << " ";
                    cout << endl;
                    break;
                }
            } while (menu != 0);
            break;
        }
    } while (menu != 0);
}