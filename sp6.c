#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 6031)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _cvor;
struct _pointer;
typedef struct _cvor cvor;
typedef struct _pointer pokazivac;
typedef struct _cvor* pozicija;
typedef struct _pointer* polozaj;

struct _pointer {
	pozicija last;
	pozicija first;
};

struct _cvor {
	int el;
	pozicija next;
};

pozicija StvoriCvor();

int StaviNaKraj(pozicija, polozaj);
int* SkiniPocetak(pozicija, polozaj);

int push(pozicija);
int* pop(pozicija);
int ispis(pozicija);

int main()
{
	cvor heads, headr;
	pokazivac p;
	char c;
	int* x = NULL;

	heads.next = headr.next = NULL;
	p.last = p.first = NULL;

	srand((unsigned)time(NULL));

	while (1)
	{
		printf("Ako zelite unijeti element na stog, unesite u\n");
		printf("Ako zelite obrisati element sa stoga, unesite o\n");
		printf("Ako zelite unijeti element u red, unesite e\n");
		printf("Ako zelite obrisati element iz reda, unesite d\n");
		printf("Ako zelite ispisati stog, unesite s\n");
		printf("Ako zelite ispisati red, unesite r\n");
		printf("Ako zelite izaci iz programa, upisite i\n");

		scanf(" %c", &c);

		switch (c)
		{
		case 'u':
			push(&heads);
			break;

		case 'e':
			StaviNaKraj(&headr, &p);
			break;

		case 'd':
			x = SkiniPocetak(&headr, &p);

			if (x != NULL)
				printf("%d\n", *x);

			else
				return 0;
			break;

		case 'o':
			x = pop(&heads);

			if (x != NULL)
				printf("%d\n", *x);

			else
				return 0;
			break;

		case 's':
			ispis(heads.next);
			printf("\n");
			break;

		case 'r':
			ispis(headr.next);
			printf("\n");
			break;

		case 'i':
			return 0;
			break;
		}
	}

	return 0;
}

//funckija radi prazan cvor
pozicija StvoriCvor(void)
{
	pozicija q = (pozicija)malloc(sizeof(cvor));

	if (!q)
		return q;

	return q;
}

//funkcija ubacuje novi element na pocetak liste
int push(pozicija head)
{
	pozicija q = StvoriCvor();

	if (q)
	{
		q->el = 10 + rand() % 91;
		q->next = head->next;
		head->next = q;
	}

	else
		printf("Neuspjesna alokacija memorije!");

	return 1;
}

//funkcija vraca element s pocetka liste pa ga izbrise
int* pop(pozicija head)
{
	int* pom = NULL;
	pozicija temp = NULL;

	if (head->next != NULL)
	{
		pom = (int*)malloc(sizeof(int));

		if (pom != NULL)
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

//funkcija stavlja novi element na kraj reda
int StaviNaKraj(pozicija head, polozaj p)
{
	pozicija q = StvoriCvor();

	if (head->next == NULL)
	{
		push(head);
		p->last = head->next;
	}

	else
	{
		push(p->last);
		p->last = p->last->next;
	}

	return 3;
}

//funckija skida element reda s pocetka i vraca ga
int* SkiniPocetak(pozicija head, polozaj p)
{
	int* pom = NULL;

	if (head->next != NULL)
	{
		pom = (int*)malloc(sizeof(int));

		if (pom != NULL)
		{
			*pom = head->next->el; //sprema element s pocetka liste

			p->first = head->next;
			head->next = p->first->next;
			free(p->first);

			if (head->next == NULL)
				p->last = head;

			return pom;
		}

		else
			printf("Neuspjesna alokacija memorije!");
	}

	return pom;
}

//funckija ispisuje stog ili red, a prima adresu prvog elementa
int ispis(pozicija headn)
{
	if (headn == NULL)
	{
		printf("Unesena stog ili uneseni red je prazan!");
		return -2;
	}

	while (headn != NULL)
	{
		printf("%d ", headn->el);
		headn = headn->next;
	}

	return 2;
}