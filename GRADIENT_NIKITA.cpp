#include <iostream>

using namespace std;

double smatvec(double** matrix, double* vector, int n) {
	// Находим скалярное произведение и заполняем новую матрицу
	double result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result += matrix[i][j] * vector[j];
		}
	}
	return result;
}

double svec(double* vector1, double* vector2, int n) {
	double result = 0;
	for (int i = 0; i < n; i++) {
		result += vector1[i] * vector2[i];
	}
	return result;
}

void vmatvec(double** matrix, double* vector, int n, double* result) {
	for (int i = 0; i < n; i++) {
		result[i] = 0;
		for (int j = 0; j < n; j++) {
			result[i] += matrix[i][j] * vector[j];
		}
	}
}

void vvec(double* vector1, double* vector2, int n, double* result) {
	for (int i = 0; i < n; i++) {
		result[i] = vector1[i] * vector2[i];
	}
}

void vminusv(double* vector1, double* vector2, int n, double* result) {
	for (int i = 0; i < n; i++) {
		result[i] = vector1[i] - vector2[i];
	}
}

void mnum(double** matrix, double num, int n, double** result) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result[i][j] = matrix[i][j] * num;
		}
	}
}

void vnum(double* vector, double num, int n, double* result) {
	for (int i = 0; i < n; i++) {
		result[i] = vector[i] * num;
	}
}

void vplusv(double* vector1, double* vector2, int n, double* result) {
	for (int i = 0; i < n; i++) {
		result[i] = vector1[i] + vector2[i];
	}
}

int main() {
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "Васт приветствует мастер-установщик виндовс\n" << endl;
	cin >> n;
	double al, bt, sr, sAr, srtr, sArtr, sAtrtr, E, e;
	double* r = new double[n];
	double* tr = new double[n];
	double* x = new double[n];
	double* Ax = new double[n];
	double* Ar = new double[n];
	double* Atr = new double[n];

	double** A = new double* [n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	cout << "Введите первую матрицу\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "Введите " << i << " - строку, " << j << " - столбец \n";
			cin >> A[i][j];
			/*
			while (!cin)
			{
				cout << "Вы ввели не число! Повторите ввод A[" << i << "][" << j << "]: ";
				cin.clear();
				while (cin.get() != '\n') continue;
				cin >> A[i][j];
			}
			*/
		}
	}

	double* B = new double[n];

	// Ввод матрицы B
	cout << "Введите матрицу В(" << n << "х1):\n";
	for (int i = 0; i < n; i++) {
		cout << "Введите строку " << i << "\n";
		cin >> B[i];
		/*
		while (!cin)
		{
			cout << "Вы ввели не число! Повторите ввод B[" << i << "]";
			cin.clear();
			while (cin.get() != '\n') continue;
			cin >> B[i];
		}
		*/
	}

	cout << "Введите погрешность\n";
	cin >> E;

	// первая итерация
	x[0] = 1;
	for (int i = 1; i < n; i++) {
		x[i] = 0;
	}

	vmatvec(A, x, n, Ax);
	vminusv(Ax, B, n, r);
	sr = svec(r, r, n);
	vmatvec(A, r, n, Ar);
	sAr = svec(Ar, r, n);
	bt = -(sr / sAr);
	vnum(r, bt, n, tr);
	vplusv(x, tr, n, x);
	//cout << "sr=" << sr << ", sAr=" << sAr << ", bt=" << bt;
	//cout << "x=" << endl;
	//for (int i = 0; i < 3; i++) { cout << "x[i]" << "i=" << i << "  ---  " << x[i] << "\n"; }

	do {

		vmatvec(A, x, n, Ax);
		vminusv(Ax, B, n, r);
		vmatvec(A, r, n, Ar);
		vmatvec(A, tr, n, Atr);
		sr = svec(r, r, n);
		srtr = svec(r, tr, n);
		sArtr = svec(Ar, tr, n);
		sAr = svec(Ar, r, n);
		sAtrtr = svec(Atr, tr, n);
		al = (((sr * sArtr) - (srtr * sAr)) / ((sAtrtr * sAr) - (sArtr * sArtr)));
		bt = (((srtr * sArtr) - (sr * sAtrtr)) / ((sAtrtr * sAr) - (sArtr * sArtr)));
		vnum(tr, al, n, tr);
		vnum(r, bt, n, r);
		vplusv(tr, r, n, tr);
		vplusv(x, tr, n, x);

		for (int i = 1; i < n; i++) {
			if (fabs(tr[i]) > fabs(tr[i - 1])) {
				e = fabs(tr[i]);
			}
			else { e = fabs(tr[i - 1]); }
		}
		cout << "e = " << e << "                        check this out!" << "E = " << E << endl;

	} while (e > E);

	cout << "sr=" << sr << ", sAr=" << sAr << ", bt=" << bt;
	cout << "x=" << endl;
	for (int i = 0; i < 3; i++) { cout << "x[" << i << "]" << "  ---- " << x[i] << "\n"; }



	system("pause");
}
