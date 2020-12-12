#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 6031)

#include <stdio.h>
#include <stdlib.h>

struct _cvor;

typedef struct _cvor cvor;
typedef struct _cvor* pozicija;

struct _cvor {
	int el;
	pozicija next;
};

FILE* OtvoriDat(const char*);
char* UcitajDat(const char*);

pozicija StvoriCvor();

int push(pozicija, int);
int* pop(pozicija);
int ispis(pozicija);

pozicija Postfix(const char*, pozicija);
int operacija(const char, pozicija);

int main()
{
	char* buffer = UcitajDat("datoteka.txt");
	cvor head;
	pozicija p = NULL;

	head.next = NULL;

	p = Postfix(buffer, &head);

	if (p != NULL)
		printf("Rezultat izraza je %d\n", p->el);

	else
		printf("Greska, izraz je neispravno unesen!");

	return 0;
}

//funckija radi i vraca prazan cvor
pozicija StvoriCvor()
{
	pozicija p = (pozicija)malloc(sizeof(cvor));

	if (p)
	{
		p->next = NULL;
		return p;
	}

	return p;
}

//funkcija ubacuje element na pocetak stoga
int push(pozicija head, int x)
{
	pozicija q = StvoriCvor();

	if (q)
	{
		q->el = x;

		q->next = head->next;
		head->next = q;
	}

	else
		printf("Neuspjesna alokacija memorije!");

	return 1;
}

//funckija skida element s pocetka stoga
int* pop(pozicija head)
{
	int* pom = NULL;
	pozicija temp = NULL;

	if (head->next != NULL)
	{
		pom = (int*)malloc(sizeof(int));

		if (pom)
		{
			*pom = head->next->el; //sprema element s pocetka liste

			temp = head->next;
			head->next = temp->next;
			free(temp);

			return pom;
		}

		else
			printf("Neuspjesna alokacija memorije!");
	}

	return pom;
}

//funckija ispisuje elemente stoga, prima adresu prvog cvora, ne heada
int ispis(pozicija headn)
{
	if (headn == NULL)
	{
		printf("Stog je prazan!");
		return -2;
	}

	else
	{
		while (headn != NULL)
		{
			printf("%d", headn->el);
			headn = headn->next;
		}

		return 2;
	}
}

//funckija otvara datoteku
FILE* OtvoriDat(const char* imeDat)
{
	FILE* fp = NULL;

	fp = fopen(imeDat, "r");

	return fp;
}

//funckija ucitaje datoteku i sprema elemente u poslanu varijablu
char* UcitajDat(const char* imeDat)
{
	FILE* fp = OtvoriDat(imeDat);
	char* buffer = NULL;
	int brojac = 0;

	if (fp)
	{
		buffer = (char*)malloc(100 * sizeof(char));

		if (buffer)
		{
			fgets(buffer, 100, fp);
			return buffer;
		}

		else
		{
			printf("Neuspjesna alokacija memorije");

			return NULL;
		}
	}

	else
	{
		printf("Neuspjesno otvaranje datoteke!");

		return NULL;
	}
}

//funckija racuna postifx izraz
pozicija Postfix(const char* buffer, pozicija head)
{
	int val, brojac = 0;
	char c;

	while(*buffer != '\0')
	{
		if (*buffer == '+' || *buffer == '-' || *buffer == '*' || *buffer == '/')
		{
			sscanf(buffer, "%c%n", &c, &brojac);
			operacija(c, head);

			buffer += brojac;
		}

		else
		{
			sscanf(buffer, "%d %n", &val, &brojac);
			push(head, val);

			buffer += brojac;
		}
			
		brojac = 0;
	}

	if (head->next->next == NULL)
		return head->next;

	else
		return NULL;
}

//funkcija za razlicitu operaciju racuna rezultat
int operacija(const char c, pozicija head)
{
	int rez, *x, *y;

	switch (c)
	{
	case '+':
		if ((x = pop(head)) != NULL && (y = pop(head)) != NULL)
		{
			rez = *y + *x;
			push(head, rez);
		}

		else
			printf("Greska, stog je prazan!");

		break;

	case '-':
		if ((x = pop(head)) != NULL && (y = pop(head)) != NULL)
		{
			rez = *y - *x;
			push(head, rez);
		}

		else
			printf("Greska, stog je prazan!");

		break;

	case '*':
		if ((x = pop(head)) != NULL && (y = pop(head)) != NULL)
		{
			rez = (*y) * (*x);
			push(head, rez);
		}

		else
			printf("Greska, stog je prazan!");

		break;

	case '/':
		if ((x = pop(head)) != NULL && (y = pop(head)) != NULL)
		{
			if ((*x) != 0)
			{
				rez = (*y) / (*x);
				push(head, rez);
			}

			else
				printf("Greska, ne moze se dijeliti nulom!");
		}

		else
			printf("Greska, stog je prazan!");

		break;
	}

	return 4;
}