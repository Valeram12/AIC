#include <stdio.h>
#include<stdlib.h>
#include <iostream>
#define NMAX 20
#pragma warning(disable:4996)
using namespace std;

typedef struct OBST {
	int KEYA;
	int KEYB;
	struct OBST* left, * right;
}OBST;


class rational
{
	int n, d;
public:
	rational() : n(1), d(1) {};
	~rational() {};

	void getData(int a, int b)
	{
		n = a;
		d = b;
	}

	int GCD(int n1, int remainder)
	{
		if (remainder == 0)
			return(n1);
		else { return(GCD(remainder, n1 % remainder)); }
	}

	void reduce(int& n, int& d)
	{
		int rdc = 0;
		if (d > n)
			rdc = GCD(d, n);
		else if (d < n)
			rdc = GCD(n, d);
		else
			rdc = GCD(n, d);
		n /= rdc;
		d /= rdc;
		cout << n << "/" << d << endl;
	}
	void prnt(rational temp) {
		reduce(temp.n, temp.d);
	}

};


int ConstM[NMAX][NMAX]; 
int WeightM[NMAX][NMAX]; 
int RootM[NMAX][NMAX]; 
int unsuccesfulS[NMAX]; 
int freq[NMAX]; 

int KeyNum; 
int KEYSA[NMAX];
int KEYSB[NMAX];
OBST* Main;

void COMPUTE_W_C_R() {
	int x, min;
	int h, m;


	for (int i = 0; i <= KeyNum; i++) {
		WeightM[i][i] = unsuccesfulS[i];
		for (int j = i + 1; j <= KeyNum; j++)
			WeightM[i][j] = WeightM[i][j - 1] + freq[j] + unsuccesfulS[j];
	}


	for (int i = 0; i <= KeyNum; i++){ 
		ConstM[i][i] = WeightM[i][i]; 
	}
		
	for (int i = 0; i <= KeyNum - 1; i++) {
		int j = i + 1;
		ConstM[i][j] = ConstM[i][i] + ConstM[j][j] + WeightM[i][j];
		RootM[i][j] = j;
	}
	for (h = 2; h <= KeyNum; h++) {
		for (int i = 0; i <= KeyNum - h; i++) {
			int j = i + h;
			m = RootM[i][j - 1];
			min = ConstM[i][m - 1] + ConstM[m][j];
			for (int k = m + 1; k <= RootM[i + 1][j]; k++) {
				x = ConstM[i][k - 1] + ConstM[k][j];
				if (x < min) {
					m = k;
					min = x;
				}
			}
			ConstM[i][j] = WeightM[i][j] + min;
			RootM[i][j] = m;
		}
	}


	cout<<"\nThe weight matrix WeightM:\n";
	for (int i = 0; i <= KeyNum; i++) {
		for (int j = i; j <= KeyNum; j++) {
			cout << "%d " << WeightM[i][j];
		}
		cout << endl;
	}

	
	cout<<"\nThe cost matrix ConstM:\n";
	for (int i = 0; i <= KeyNum; i++) {
		for (int j = i; j <= KeyNum; j++) {
			cout << "%d " << ConstM[i][j];
		}
		cout << endl;
	}

	

	cout<<"\nThe root matrix RootM:\n";
	for (int i = 0; i <= KeyNum; i++) {
		for (int j = i; j <= KeyNum; j++) {
			cout << "%d " << RootM[i][j];
		}
		cout << endl;
	}
}


OBST* Build(int i, int j) {
	OBST* freq;

	if (i == j) {
		freq = NULL;
	}
	else {
		freq = (OBST*)calloc(1, sizeof(OBST));
		freq->KEYA = KEYSA[RootM[i][j]];
		freq->KEYB = KEYSB[RootM[i][j]];
		freq->left = Build(i, RootM[i][j] - 1); //left subtree
		freq->right = Build(RootM[i][j], j); //right subtree
	}
	return freq;
}


void Show(OBST* Main, int nivel) {
	
	if (Main != 0) {
		Show(Main->right, nivel + 1);
		for (int i = 0; i <= nivel; i++)
			printf(" ");

		rational c1;
		c1.getData(Main->KEYA, Main->KEYB);
		c1.prnt(c1);
		Show(Main->left, nivel + 1);
	}
}
void OPTIMAL_BINARY_SEARCH_TREE()
{
	float average_cost_per_weight;

	COMPUTE_W_C_R();
	printf("ConstM[0] = %d WeightM[0] = %d\n", ConstM[0][KeyNum], WeightM[0][KeyNum]);
	average_cost_per_weight = ConstM[0][KeyNum] / (float)WeightM[0][KeyNum];
	cout<<"The cost per weight ratio is: %f\n"<< average_cost_per_weight;
	Main = Build(0, KeyNum);
}
int main() {
	int k;

	setbuf(stdout, NULL);
	printf("Input number of keys: ");
	cin >> KeyNum;
	
	for (int i = 1; i <= KeyNum; i++) {
		KEYSB[i] = 0;
		printf("key[%d]= ", i);
		cout << "Enter numerator: ";
		cin >> KEYSA[i];
		cout << "Enter denominator: ";
		cin >> KEYSB[i];
		if (KEYSB[i] == 0) {
			cout << "Enter a normal denominator: ";
			cin >> KEYSB[i];
		}
		if(KEYSB[i] <0){
			KEYSA[i] *= -1;
			KEYSB[i] *= -1;
		}
		
		cout<<"frequency = ";
		cin >> freq[i];

	}
	for (int i = 0; i <= KeyNum; i++) {
		cout<<"unsuccesfulS[%d] = "<< i;
		cin >> unsuccesfulS[i];

	}
	do {
		cout<<"\n1.Build tree\n2.Show tree\n3.Exit\n";
		cin >> k;
		switch (k) {
		case 1:
			OPTIMAL_BINARY_SEARCH_TREE();
			break;
		case 2:
			Show(Main, 0);
			break;
		case 3:
			k = -1;
			break;
		}
	} while (k != -1);
}