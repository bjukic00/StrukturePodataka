#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char ime[15];
	char prezime[20];
	int bodovi;

} student;

int prebroji(const char* ime_dat)
{
	int suma = 0;
	char str[50];

	FILE* f = NULL;

	f = fopen(ime_dat, "r");

	if (f == NULL)
	{
		printf("Neuspjesno otvaranje memorije u funkciji!");

		return -3;
	}

	while (fgets(str, 50, f) != NULL)
		suma++;

	fclose(f);

	return suma;
}

int ispisi(const char* ime_dat, int broj_stud)
{
	int i, max = 50;

	student* s = NULL;
	FILE* f = NULL;

	f = fopen(ime_dat, "r");

	if (f == NULL)
	{
		printf("Neuspjesno otvaranje datoteke u funkciji");

		return -2;
	}

	s = (student*)malloc(broj_stud * sizeof(student));

	if (s == NULL)
	{
		printf("Neuspjesno alociranje memorije u funkciji!");

		return -4;
	}

	while (!feof(f))
	{
		for (i = 0; i < broj_stud; i++)
		{
			fscanf(f, "%s %s %d", (s + i)->ime, (s + i)->prezime, &(s + i)->bodovi);
		}
	}

	for (i = 0; i < broj_stud; i++)
	{
		printf("%-8s %-8s %-6d %-4.1f\n", (s + i)->ime, (s + i)->prezime, (s + i)->bodovi, ((double)(s + i)->bodovi / max) * 100);
	}

	fclose(f);

	return 0;
}


int main()
{
	int br_red;

	br_red = prebroji("datoteka.txt");

	printf("U ovoj datoteci ima %d studenata.\n", br_red);
	printf("\n");
	printf("Ime      Prezime Bod(a) Bod(r)\n");

	ispisi("datoteka.txt", br_red);


	return 0;
}