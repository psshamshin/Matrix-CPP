#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

template <typename T> void FreeMemory(T** matr, int n);
template <typename T> void PrintMatrix(T** matr, int n);
template <typename T> void SetMatrix(T** matr, int n);
template <typename T> void TMatrix(T** matr, T** tMatr, int n);
template <typename T> void CopyMtx(T** matr, T** tMatr, int n);
void Get_matrix(int** matr, int n, int** temp_matr, int indRow, int indCol);
int Det(int** matr, int n);

void main()
{
	srand((unsigned)time(NULL));
	//setlocale(0, "");
	system("chcp 1251>null");
	int n, det, type_of_method;
	type_of_method = 1;
	cout << "Введите размер матрицы: ";
	cin >> n;

	int** matrix = new int* [n];
	
	int* free = new int[n];

	double* unknown = new double[n];
	for (int i = 0; i < n; i++) unknown[i] = 0;

	double** obr_matr = new double* [n];
	double** tobr_matr = new double* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
		obr_matr[i] = new double[n];
		tobr_matr[i] = new double[n];
	}

	int** temp = new int* [n];
	double* t_matr = new double[n];
	for (int i = 0; i < n; i++) {
		temp[i] = new int[n];
	}

	cout << "====== Введите матрицу коэф. ======" << endl;
	SetMatrix(matrix, n);

	cout << "====== Введите свободные члены ======" << endl;
	for (int i = 0; i < n; i++) {
		cin >> free[i];
	}
	cout << "====== Выберете метод: 1(матрич), 2(крамер) ======" << endl;
	cin >> type_of_method;
	double time_init = clock() / 1000.0;

	switch (type_of_method) {
		case 1:
			det = Det(matrix, n);
			cout << "Определитель матрицы = " << det << endl;
			if (det) {
				for (int i = 0; i < n; i++) {
					cout << endl;
					for (int j = 0; j < n; j++) {
						int m = n - 1;
						int** temp_matr = new int* [m];
						for (int k = 0; k < m; k++)
							temp_matr[k] = new int[m];
						Get_matrix(matrix, n, temp_matr, i, j);
						cout << "A" << j << i << " = " << pow(-1.0, i + j + 2) * Det(temp_matr, m) << endl;
						obr_matr[i][j] = pow(-1.0, i + j + 2) * Det(temp_matr, m) / det;
						FreeMemory(temp_matr, m);
					}
				}
			}
			else {
				cout << "Т.е. матрица обратной не имеет" << endl;
				exit(1);
			}

			//Транспонирование матрицы
			TMatrix(obr_matr, tobr_matr, n);
			//Печать обратной матрицы после транспонирования
			PrintMatrix(tobr_matr, n);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					unknown[i] += free[j] * tobr_matr[j][i];
				}
			}
			for (int i = 0; i < n; i++) {
				cout << "x" << i + 1 << " = " << round(unknown[i] * 100) / 100 << endl;
			}
			FreeMemory(tobr_matr, n);
			FreeMemory(matrix, n);
			FreeMemory(obr_matr, n);
			break;
		case 2:
			
			det = Det(matrix, n);
			cout << "delta = " << det << endl;


			for (int i = 0; i < n; i++) {
				CopyMtx(matrix, temp, n);
				for (int j = 0; j < n; j++) {
					temp[i][j] = free[j];
				}
				t_matr[i] = Det(temp, n);
				cout << "delta " << i << " = " << t_matr[i] << endl;
			}
			cout << "===================" << endl;
			for (int i = 0; i < n; i++) {
				cout << "x" << i + 1 << " = " << t_matr[i] / det * 100 / 100 << endl;
			}
			delete[] t_matr;
			FreeMemory(matrix, n);
			break;
	}
	

	
	cout << "runtime = " << clock() / 1000.0 - time_init <<" c"<< endl;
}
//Функция транспонирования матрицы
template <typename T> void TMatrix(T** matr, T** tMatr, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tMatr[j][i] = matr[i][j];
}
//Функция копирования матрицы
template <typename T> void CopyMtx(T** matr, T** tMatr, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tMatr[j][i] = matr[j][i];
}
//Функция освобождения памяти
template <typename T> void FreeMemory(T** matr, int n)
{
	for (int i = 0; i < n; i++)
		delete[] matr[i];
	delete[] matr;
}

//Функция заполнения матрицы
template <typename T> void SetMatrix(T** matr, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matr[j][i];
}

//функция печати матрицы
template <typename T> void PrintMatrix(T** matr, int n)
{
	cout << "======== Обратная матрица ========" << endl;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++)
			cout << matr[i][j] << "\t";
		cout << endl;
	}
	cout << "==================================" << endl;
}
//функция вычеркивания строки и столбца
void Get_matrix(int** matr, int n, int** temp_matr, int indRow, int indCol)
{
	int ki = 0;
	for (int i = 0; i < n; i++) {
		if (i != indRow) {
			for (int j = 0, kj = 0; j < n; j++) {
				if (j != indCol) {
					temp_matr[ki][kj] = matr[i][j];
					kj++;
				}
			}
			ki++;
		}
	}
}


//============= вычисление определителя =============

//функция вычисления определителя матрицы
int Det(int** matr, int n)
{
	int temp = 0;   //временная переменная для хранения определителя
	int k = 1;      //степень
	if (n < 1) {
		cout << "Неверный размер матрицы" << endl;
		exit(1);
	}
	else if (n == 1)
		temp = matr[0][0];
	else if (n == 2)
		temp = matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];
	else {
		for (int i = 0; i < n; i++) {
			int m = n - 1;
			int** temp_matr = new int* [m];
			for (int j = 0; j < m; j++)
				temp_matr[j] = new int[m];
			Get_matrix(matr, n, temp_matr, 0, i);
			temp = temp + k * matr[0][i] * Det(temp_matr, m);
			k = -k;
			FreeMemory(temp_matr, m);
		}
	}
	return temp;
}