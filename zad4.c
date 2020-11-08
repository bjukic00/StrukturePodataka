#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6013)
#pragma warning(disable : 6031)

#include <stdio.h>
#include <stdlib.h>

struct _polinom;

typedef struct _polinom* pozicija;
typedef struct _polinom polinom;

struct _polinom
{
	int koef;
	int exp;
	pozicija next;

};

FILE* OtvoriDat(const char*);
int UcitajDat(const char*, pozicija);

pozicija NapraviCvor(void);
pozicija UcitajCvor(int koef, int exp);

int ZbrojiPolinome(pozicija, pozicija, pozicija);
int MnoziPolinome(pozicija, pozicija, pozicija);

int UnosP(pozicija, pozicija);
int UnosSort(pozicija, pozicija);
int Ispisi(pozicija);
int Brisi(pozicija);


int main()
{
	char ime[20] = { 0 };
	polinom head1, head2, head3, head4;

	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	head4.next = NULL;
	
	printf("Unesite ime prve datoteke iz koje zelite ucitati polinome: ");
	scanf(" %s", ime);

	UcitajDat(ime, &head1);
	Ispisi(head1.next);

	printf("\nUnesite ime druge datoteke iz koje zelite ucitati polinome: ");
	scanf(" %s", ime);

	UcitajDat(ime, &head2);
	Ispisi(head2.next);

	ZbrojiPolinome(&head1, &head2, &head3);

	printf("\nZbroj ucitanih polinoma:\n");

	Ispisi(head3.next);

	MnoziPolinome(&head1, &head2, &head4);

	printf("\nUmnozak ucitanih polinoma:\n");

	Ispisi(head4.next);

	printf("\n");

	Brisi(&head1);
	Brisi(&head2);
	Brisi(&head3);
	Brisi(&head4);

	return 0;
}

//funckija otvara datoteku i provjerava je li ona uspjesno otvorena
FILE* OtvoriDat(const char* imeDat)
{
	FILE* fp = NULL;

	fp = fopen(imeDat, "r");

	if (!fp)
	{
		printf("Neuspjesno otvaranje datoteke!");

		return fp;
	}

	return fp;
}

//funkcija cita datoteku i uzima njene argumente
int UcitajDat(const char* imeDat, pozicija head)
{
	FILE* fp = NULL;

	pozicija p = NULL;

	int koef = 0;
	int exp = 0;

	fp = OtvoriDat(imeDat);

	if (fp)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d %d", &koef, &exp);

			p = UcitajCvor(koef, exp);
			UnosSort(head, p);
		}

		fclose(fp);

		return 1;
	}

	return -1;
}

//funkcija alocira prostor za prazan cvor koji pokazuje na NULL
pozicija NapraviCvor(void)
{
	pozicija p = NULL;

	p = (pozicija)malloc(sizeof(polinom));

	if (!p)
		return p;

	p->next = NULL;

	return p;
}

//funkcija ucitava elemente u alocirani cvor
pozicija UcitajCvor(int koef, int exp)
{
	pozicija p = NULL;

	p = NapraviCvor();

	if (p)
	{
		p->koef = koef;
		p->exp = exp;

		return p;
	}

	return p;
}

//funkcija unosi novi cvor na pocetak
int UnosP(pozicija head, pozicija p)
{
	p->next = head->next;
	head->next = p;

	return 2;
}


//uzlazno sortira listu
int UnosSort(pozicija head, pozicija p)
{
	if (p)
	{
		while (head->next != NULL && head->next->exp < p->exp)
		{
			head = head->next;
		}

		UnosP(head, p);

		return 3;
	}

	printf("Neuspjesno alociranje memorije!");

	return -3;
}

//funkcija ispisuje listu
int Ispisi(pozicija headn)
{
	if (headn == NULL)
	{
		printf("Lista je prazna!");

		return -4;
	}

	else
	{
		while (headn != NULL)
		{
			if (headn->next != NULL)
				printf("%dx^%d + ", headn->koef, headn->exp);

			else
				printf("%dx^%d ", headn->koef, headn->exp);

			headn = headn->next;
		}

		return 4;
	}
}


//funkcija brise cijelu listu, dealocira memoriju
int Brisi(pozicija head)
{
	pozicija pom = NULL;
	
	while (head->next != NULL)
	{
		pom = head->next;
		head->next = head->next->next;
		free(pom);
	}

	return 5;
}

int BrisiZadnjeg(pozicija head)
{
	pozicija pom = NULL;

	while (head->next->next != NULL)
		head = head->next;

	pom = head->next;
	head->next = head->next->next;
	free(pom);

	return 7;
}


//funkcija zbraja polinome
int ZbrojiPolinome(pozicija p, pozicija q, pozicija head)
{
	pozicija temp = NULL; //pomocni pointer za ucitavanje cvorova
	pozicija temp2 = head; //pomocni pointer umjeto heada, zbog funkcije BrisiZadnjeg

	int pom = 0;

	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL)
	{
		if (abs(p->exp) < abs(q->exp))
		{
			if (p->koef == 0)
				p = p->next;

			else 
			{
				temp = UcitajCvor(p->koef, p->exp);

				if (temp)
				{
					UnosP(head, temp);

					head = head->next;
					p = p->next;
				}
			}
		}

		else if (abs(q->exp) < abs(p->exp))
		{
			if (q->koef == 0)
				q = q->next;

			else
			{
				temp = UcitajCvor(q->koef, q->exp);

				if (temp)
				{
					UnosP(head, temp);

					head = head->next;
					q = q->next;
				}
			}
		}

		else
		{
			pom = q->koef + p->koef;

			if (pom)
			{
				temp = UcitajCvor(pom, q->exp);

				if (temp)
				{
					UnosP(head, temp);

					head = head->next;
				}
			}

			p = p->next;
			q = q->next;
		}
	}

	while (p != NULL)
	{
		if (head->exp != p->exp)
		{
			temp = UcitajCvor(p->koef, p->exp);

			if (temp)
			{
				UnosP(head, temp);

				head = head->next;
				p = p->next;
			}
		}

		else
		{
			head->koef += p->koef;

			if (!head->koef)
				BrisiZadnjeg(temp2);

			p = p->next;
		}
	}

	while (q != NULL)
	{
		if (head->exp != q->exp)
		{
			temp = UcitajCvor(q->koef, q->exp);

			if (temp)
			{
				UnosP(head, temp);

				head = head->next;
				q = q->next;
			}
		}

		else
		{
			head->koef += q->koef;

			if (!head->koef)
				BrisiZadnjeg(temp2);

			q = q->next;
		}
	}

	temp = NULL;

	return 6;
}

int MnoziPolinome(pozicija p, pozicija q, pozicija head)
{
	pozicija temp1 = NULL; //pomocni pointer za prolazak kroz prvu listu
	pozicija temp2 = NULL; //pomocni pointer za prolazak kroz drugu listu
	pozicija pom = NULL; //pomocni pointer za unosit novi cvor

	for (temp1 = p->next; temp1 != NULL; temp1 = temp1->next)
	{
		for (temp2 = q->next; temp2 != NULL; temp2 = temp2->next)
		{
			if (temp1->koef * temp2->koef != 0)
			{
				pom = UcitajCvor(temp1->koef * temp2->koef, temp1->exp + temp2->exp);

				if (pom)
				{
					UnosSort(head, pom);
				}
			}
		}
	}

	return 8;
}
