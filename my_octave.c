// Nastase Cristian-Gabriel 315CA
#include <stdio.h>
#include <stdlib.h>
#define MOD 10007

// vectori de matrici care stocheaza elementele matricei
// si totodata si dimensiunile acesteia.
struct matrice {
	int m, n;
	int **a;
};

// aceasta functie corespunde operatiei L si
// presupune citirea dimensiunilor si a elementelor matricii;
void citire_matrice(int numar_matrice, struct matrice *v)
{
	scanf("%d%d", &v[numar_matrice].m, &v[numar_matrice].n);
	v[numar_matrice].a = (int **)malloc(v[numar_matrice].m * sizeof(int *));

	for (int i = 0; i < v[numar_matrice].m; i++)
		v[numar_matrice].a[i] = (int *)malloc(v[numar_matrice].n * sizeof(int));

	for (int i = 0; i < v[numar_matrice].m; i++)
		for (int j = 0; j < v[numar_matrice].n; j++)
			scanf("%d", &v[numar_matrice].a[i][j]);
}

int verificare_existenta_matrice(int index, int numar_matrice)
{
	if (index > numar_matrice || index < 0) {
		printf("No matrix with the given index\n");
		return 0;
	}
	return 1;
}

// aceasta functie este corespunzatoare operatiei 'P';
// afiseaza matricea in cazul in care indexul
// citit corespunde unei matrici existente;
int afisare_matrice(int numar_matrice, struct matrice *v)
{
	int index;
	scanf("%d", &index);
	if (!verificare_existenta_matrice(index, numar_matrice))
		return 0;
	for (int i = 0; i < v[index].m; i++) {
		for (int j = 0; j < v[index].n; j++)
			printf("%d ", v[index].a[i][j]);
		printf("\n");
	}
	return 1;
}

// aceasta functie este corespunzatoare operatiei 'D';
void afisare_dimensiuni_matrice(int numar_matrice, struct matrice *v)
{
	int index;
	scanf("%d", &index);
	if (index > numar_matrice)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", v[index].m, v[index].n);
}

// aceasta functie este corespunzatoare operatiei 'C';
// aceasta functie modifica matricea corespunzatoare variabilei index
// in functie de liniile si coloanele introduse;
int redimensionare_matrice(struct matrice *v, int numar_matrice)
{
	int index, linii, coloane, *v_linii, *v_coloane;
	scanf("%d", &index);
	if (!verificare_existenta_matrice(index, numar_matrice))
		return 0;

	scanf("%d", &linii);
	v_linii = (int *)malloc(linii * sizeof(int));
	if (!v_linii)
		printf("Nu s-a reusit alocarea a vectorului v_linii\n");

	for (int i = 0; i < linii; i++)
		scanf("%d", &v_linii[i]);

	scanf("%d", &coloane);
	v_coloane = (int *)malloc(coloane * sizeof(int));
	if (!v_coloane)
		printf("Nu s-a reusit alocarea a vectorului v_coloane\n");

	for (int i = 0; i < coloane; i++)
		scanf("%d", &v_coloane[i]);

	int **matrice_noua = (int **)malloc(linii * sizeof(int *));
	for (int i = 0; i < linii; i++)
		matrice_noua[i] = (int *)malloc(coloane * sizeof(int));

	for (int i = 0; i < linii; i++)
		for (int j = 0; j < coloane; j++)
			matrice_noua[i][j] = v[index].a[v_linii[i]][v_coloane[j]];

	for (int i = v[index].m - 1; i >= 0; i--)
		free(v[index].a[i]);
	free(v[index].a);

	v[index].m = linii;
	v[index].n = coloane;

	v[index].a = (int **)malloc(linii * sizeof(int *));
	for (int i = 0; i < linii; i++)
		v[index].a[i] = malloc(coloane * sizeof(int *));

	for (int i = 0; i < linii; i++)
		for (int j = 0; j < coloane; j++)
			v[index].a[i][j] = matrice_noua[i][j];

	for (int i = linii - 1; i >= 0; i--)
		free(matrice_noua[i]);
	free(matrice_noua);
	free(v_linii);
	free(v_coloane);
	return 1;
}

// aceasta functie contine toate conditiile de care avem nevoie
// pentru a afisa errorile corespunzatoare;
int verificare_case_M(int m1, int m2, int numar_matrice, struct matrice *v)
{
	if (m1 > numar_matrice) {
		printf("No matrix with the given index\n");
		return 0;
	}
	if (m2 > numar_matrice) {
		printf("No matrix with the given index\n");
		return 0;
	}
	if (v[m1].n != v[m2].m) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

// aceasta functie este corespunzatoare operatiei 'M'
void inmultire_matrici(struct matrice *v, int m1, int m2, int numar_matrice)
{
	// alocam dinamic cu calloc, deoarece intr o operatie de adunare
	// avem nevoie ca elementele matricii sa fie initializate cu 0;
	v[numar_matrice].a = (int **)calloc(v[m1].m, sizeof(int *));
	for (int i = 0; i < v[m1].m; i++)
		v[numar_matrice].a[i] = (int *)calloc(v[m2].n, sizeof(int));

	v[numar_matrice].m = v[m1].m;
	v[numar_matrice].n = v[m2].n;

	if (!v[numar_matrice].a) {
		printf("Nu s-a reusit alocarea dinamica a matricei noi\n");
		for (int i = 0; i < v[m1].m; i++)
			free(v[numar_matrice].a[i]);
		free(v[numar_matrice].a);
	}

	for (int i = 0; i < v[numar_matrice].m; i++)
		for (int j = 0; j < v[numar_matrice].n; j++)
			for (int k = 0; k < v[m1].n; k++) {
				v[numar_matrice].a[i][j] += v[m1].a[i][k] * v[m2].a[k][j];
				v[numar_matrice].a[i][j] %= MOD;
				if (v[numar_matrice].a[i][j] < 0)
					v[numar_matrice].a[i][j] += MOD;
			}
}

// aceasta functie este de folos pentru sortarea matricilor;
int suma_elemente_matrice(struct matrice *v, int index)
{
	int suma = 0;
	for (int i = 0; i < v[index].m; i++)
		for (int j = 0; j < v[index].n; j++) {
			suma = suma + v[index].a[i][j];
			suma %= MOD;
			if (suma < 0)
				suma += MOD;
		}
	return suma;
}

// aceasta functie este corespunzatoare operatiei 'O';
void sortare_matrici(struct matrice *v, int numar_matrice)
{
	int ok;
	do {
		ok = 1;
		for (int i = 0; i < numar_matrice; i++) {
			int a, b;
			a = suma_elemente_matrice(v, i);
			b = suma_elemente_matrice(v, i + 1);
			if (a > b) {
				struct matrice aux;
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				ok = 0;
			}
		}
	} while (ok == 0);
}

// aceasta functie este corespunzatoare operatiei 'T';
int transpunere_matrice(struct matrice *v, int numar_matrice)
{
	// o sa avem nevoie de o matrice ajutatoare (**m)
	// pentru a putea face transpusa matricii;
	int index, **m, aux;
	scanf("%d", &index);
	if (!verificare_existenta_matrice(index, numar_matrice))
		return 0;

	m = (int **)malloc(v[index].n * sizeof(int *));
	for (int i = 0; i < v[index].n; i++)
		m[i] = (int *)malloc(v[index].m * sizeof(int));

	for (int i = 0; i < v[index].n; i++)
		for (int j = 0; j < v[index].m; j++)
			m[i][j] = v[index].a[j][i];

	// mai intai este nevoie sa dealocam matricea veche
	// pentru a nu exista leak-uri de memorie;
	for (int i = v[index].m - 1; i >= 0; i--)
		free(v[index].a[i]);
	free(v[index].a);

	// inversam dimensiunile matricii;
	aux = v[index].n;
	v[index].n = v[index].m;
	v[index].m = aux;

	// alocam din nou matricea, de data asta
	// cu dimensiunile transpusei;
	v[index].a = malloc(v[index].m * sizeof(int *));
	for (int i = 0; i < v[index].m; i++)
		v[index].a[i] = malloc(v[index].n * sizeof(int));

	// copiem elementele din matricea ajutatoare in
	// matricea corespunzatoare;
	for (int i = 0; i < v[index].m; i++)
		for (int j = 0; j < v[index].n; j++)
			v[index].a[i][j] = m[i][j];

	// nu mai avem nevoie de matricea ajutatoare,
	// asa ca o dealocam;
	for (int i = v[index].m - 1; i >= 0; i--)
		free(m[i]);
	free(m);
	return 1;
}

// aceasta functie contine toate conditiile de care avem nevoie
// pentru a afisa errorile corespunzatoare pentru operatia R;
int verificare_caz_R(int index, int putere, int nr_matrice, struct matrice *v)
{
	if (!verificare_existenta_matrice(index, nr_matrice))
		return 0;
	if (putere < 0) {
		printf("Power should be positive\n");
		return 0;
	}
	if (v[index].m != v[index].n) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

// aceasta functie este corespunzatoare operatiei 'R'
int ridicare_putere_logaritmic(struct matrice *v, int numar_matrice)
{
	int **rezultat, **N, **copie, index, putere;
	scanf("%d%d", &index, &putere);
	if (!verificare_caz_R(index, putere, numar_matrice, v))
		return 0;

	// am declarat 3 matrici ajutatoare, iar acum
	// le alocam dinamic;
	rezultat = (int **)malloc(v[index].m * sizeof(int *));
	N = (int **)malloc(v[index].m * sizeof(int *));
	copie = (int **)malloc(v[index].m * sizeof(int *));
	for (int i = 0; i < v[index].m; i++) {
		rezultat[i] = (int *)malloc(v[index].n * sizeof(int));
		N[i] = (int *)malloc(v[index].n * sizeof(int));
		copie[i] = (int *)malloc(v[index].n * sizeof(int));
	}

	// initializam matricea "copie" cu matricea unitate de tip I (indice n)
	// initializam matricea "rezultat" cu 0 de multe ori de a lungul functiei,
	// deoarece nu dorim ca rezultatul nostru sa se schimbe;
	for (int i = 0; i < v[index].m; i++)
		for (int j = 0; j < v[index].n; j++) {
			rezultat[i][j] = 0;
			N[i][j] = v[index].a[i][j];
			if (i == j)
				copie[i][j] = 1;
			else
				copie[i][j] = 0;
		}

	// aplicam algoritmul de complexitate logaritmica,
	// transformat pentru inmultirea matricilor;
	while (putere) {
		if (putere % 2 == 1) {
			for (int i = 0; i < v[index].m; i++)
				for (int j = 0; j < v[index].n; j++) {
					for (int k = 0; k < v[index].n; k++) {
						rezultat[i][j] += copie[i][k] * N[k][j];
						rezultat[i][j] %= MOD;
					if (rezultat[i][j] < 0)
						rezultat[i][j] += MOD;
					}
					v[index].a[i][j] = rezultat[i][j];
				}
			for (int i = 0; i < v[index].m; i++)
				for (int j = 0; j < v[index].n; j++) {
					copie[i][j] = rezultat[i][j];
					rezultat[i][j] = 0;
				}
		}
		for (int i = 0; i < v[index].m; i++)
			for (int j = 0; j < v[index].n; j++)
				for (int k = 0; k < v[index].n; k++) {
					rezultat[i][j] += N[i][k] * N[k][j];
					rezultat[i][j] %= MOD;
					if (rezultat[i][j] < 0)
						rezultat[i][j] += MOD;
				}

		for (int i = 0; i < v[index].m; i++)
			for (int j = 0; j < v[index].n; j++) {
				N[i][j] = rezultat[i][j];
				rezultat[i][j] = 0;
			}

		putere = putere / 2;
	}

	// am calculat ceea ce ne am dorit, asa ca nu mai avem
	// nevoie de matricile ajutatoare.
	// prin urmare le dealocam;
	for (int i = v[index].m - 1; i >= 0; i--) {
		free(rezultat[i]);
		free(N[i]);
		free(copie[i]);
	}
	free(rezultat);
	free(N);
	free(copie);
	return 1;
}

// aceasta functie este corespunzatoare operatiei 'F'
void eliminare_matrice(struct matrice *v, int index, int numar_matrice)
{
	for (int numar = index; numar < numar_matrice; numar++) {
		// eliberam din memorie matricea pe care vrem
		// sa o eliminam;
		for (int i = v[numar].m - 1; i >= 0; i--)
			free(v[numar].a[i]);
		free(v[numar].a);

		// copiem marimea urmatoarei matrici;
		v[numar].m = v[numar + 1].m;
		v[numar].n = v[numar + 1].n;

		// alocam matricea cu dimensiunile noi;
		v[numar].a = (int **)malloc(v[numar].m * sizeof(int *));
		for (int i = 0; i < v[numar].m; i++)
			v[numar].a[i] = (int *)malloc(v[numar].n * sizeof(int));

		// copiem elementele urmatoarei matrici;
		for (int i = 0; i < v[numar].m; i++)
			for (int j = 0; j < v[numar].n; j++)
				v[numar].a[i][j] = v[numar + 1].a[i][j];
	}

	// dealocam matricea din capat;
	for (int i = v[numar_matrice].m - 1; i >= 0; i--)
		free(v[numar_matrice].a[i]);
	free(v[numar_matrice].a);
}

// aceasta functie este corespunzatoare operatiei 'Q'
void dealocare_matrici(struct matrice *v, int numar_matrice)
{
	for (int numar = numar_matrice; numar >= 0; numar--) {
		for (int i = v[numar].m - 1; i >= 0; i--)
			free(v[numar].a[i]);
		free(v[numar].a);
	}
	free(v);
}

int main(void)
{
	int ok = 1, m1, m2, numar_matrice = -1, index;
	struct matrice *v = (struct matrice *)malloc(0 * sizeof(int)), *tmp;
	char operatie;

	while (ok == 1) {
		scanf("%c", &operatie);

		switch (operatie) {
		case 'L':
			tmp = realloc(v, (++numar_matrice + 1) * sizeof(struct matrice));
			if (tmp)
				v = tmp;
			else
				printf("error\n");
			citire_matrice(numar_matrice, v);
			break;

		case 'D':
			afisare_dimensiuni_matrice(numar_matrice, v);
			break;

		case 'P':
			afisare_matrice(numar_matrice, v);
			break;

		case 'C':
			redimensionare_matrice(v, numar_matrice);
			break;

		case 'M':
			scanf("%d%d", &m1, &m2);
			if (!verificare_case_M(m1, m2, numar_matrice, v))
				break;
			tmp = realloc(v, (++numar_matrice + 1) * sizeof(struct matrice));
			if (tmp)
				v = tmp;
			else
				printf("error\n");
			inmultire_matrici(v, m1, m2, numar_matrice);
			break;

		case 'O':
			sortare_matrici(v, numar_matrice);
			break;

		case 'T':
			transpunere_matrice(v, numar_matrice);
			break;

		case 'R':
			ridicare_putere_logaritmic(v, numar_matrice);
			break;

		case 'F':
			scanf("%d", &index);
			if (!verificare_existenta_matrice(index, numar_matrice))
				break;
			eliminare_matrice(v, index, numar_matrice--);
			if (numar_matrice == -1)
				break;
			tmp = realloc(v, (numar_matrice + 1) * sizeof(struct matrice));
			if (tmp)
				v = tmp;
			else
				printf("error\n");
			break;

		case 'Q':
			dealocare_matrici(v, numar_matrice);
			ok = 0;
			break;

		default:
			if (operatie >= 'A' && operatie <= 'Z')
				printf("Unrecognized command\n");
			break;
		}
	}
	return 0;
}
