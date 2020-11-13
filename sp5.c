#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 6031)

#include <stdio.h>
#include <stdlib.h>

struct _skup;
typedef struct _skup* pozicija;
typedef struct _skup skup;

struct _skup
{
	int el;
	pozicija next;
};

FILE* OtvoriDat(const char*);
int UcitajDat(const char*, pozicija);

pozicija NapraviCvor(void);
pozicija UcitajCvor(int);

int UnosP(pozicija, pozicija);
int UnosSort(pozicija, pozicija);
int Ispisi(pozicija);
int Izbrisi(pozicija);

int Unija(pozicija, pozicija, pozicija);
int Presjek(pozicija, pozicija, pozicija);

int main()
{
	char ime[20] = { 0 };

	skup head1, head2, head3, head4;

	head1.next = head2.next = head3.next = head4.next = NULL;

	printf("Unesite ime prve datoteke iz koje zelite ucitati skup: ");
	scanf(" %s", ime);

	UcitajDat(ime, &head1);
	Ispisi(head1.next);

	printf("Unesite ime druge datoteke iz koje zelite ucitati skup: ");
	scanf(" %s", ime);

	UcitajDat(ime, &head2);
	Ispisi(head2.next);

	Unija(head1.next, head2.next, &head3);

	printf("Unija:\n");
	Ispisi(head3.next);

	Presjek(head1.next, head2.next, &head4);

	printf("Presjek:\n");
	Ispisi(head4.next);

	Izbrisi(&head1);
	Izbrisi(&head2);
	Izbrisi(&head3);
	Izbrisi(&head4);

	return 0;
}

//funckija otvara datoteku i provjera je li uspjesno otvorena
FILE* OtvoriDat(const char* imeDat)
{
	FILE* fp = NULL;

	fp = fopen(imeDat, "r");

	if (!fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");

		return fp;
	}

	return fp;
}

//funkcija ucitava elemente iz datoteke i unosi ih u listu
int UcitajDat(const char* imeDat, pozicija head)
{
	FILE* fp = NULL;
	pozicija p = NULL;

	int pom = 0;

	fp = OtvoriDat(imeDat);

	if (fp)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d", &pom);
			p = UcitajCvor(pom);

			UnosSort(head, p);
		}

		fclose(fp);

		return 1;
	}

	return -1;
}

//funckija stvara prazan cvor
pozicija NapraviCvor(void)
{
	pozicija p = NULL;

	p = (pozicija)malloc(sizeof(skup));

	if (!p)
		return p;

	p->next = NULL;

	return p;
}

//funckija unosi ucitane elemente u cvor
pozicija UcitajCvor(int x)
{
	pozicija p = NULL;

	p = NapraviCvor();

	if (p)
	{
		p->el = x;

		return p;
	}

	return p;
}

//funckija unosi element na pocetak liste
int UnosP(pozicija head, pozicija p)
{
	p->next = head->next;
	head->next = p;

	return 2;
}

//funkcija sortirano unosi elemente u listu
int UnosSort(pozicija head, pozicija p)
{
	if (p)
	{
		while (head->next != NULL && head->next->el < p->el)
			head = head->next;

		UnosP(head, p);

		return 3;
	}

	printf("Neuspjesno alociranje memorije!");

	return -3;
}

//funckija ispisuje listu
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
			printf("%d\t", headn->el);

			headn = headn->next;
		}

		printf("\n");

		return 4;
	}
}

//funkcija brise tj. dealocira napravljenu listu
int Izbrisi(pozicija head)
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

//funkcija radi listu koja sadrzi uniju dvije unesene liste
int Unija(pozicija pn, pozicija qn, pozicija head)
{
	pozicija temp = NULL;
	
	while (pn != NULL && qn != NULL)
	{
		if (pn->el < qn->el)
		{
			temp = UcitajCvor(pn->el);

			if (temp)
			{
				UnosP(head, temp);

				head = head->next;
				pn = pn->next;
			}
		}

		else if (qn->el < pn->el)
		{
			temp = UcitajCvor(qn->el);

			if (temp)
			{
				UnosP(head, temp);

				head = head->next;
				qn = qn->next;
			}
		}

		else
		{
			temp = UcitajCvor(qn->el);

			if (temp)
			{
				UnosP(head, temp);

				head = head->next;
				qn = qn->next;
				pn = pn->next;
			}
		}
	}

	while (pn != NULL)
	{
		temp = UcitajCvor(pn->el);

		if (temp)
		{
			UnosP(head, temp);

			head = head->next;
			pn = pn->next;
		}
	}

	while (qn != NULL)
	{
		temp = UcitajCvor(qn->el);

		if (temp)
		{
			UnosP(head, temp);

			head = head->next;
			qn = qn->next;
		}
	}

	temp = NULL;

	return 6;
}

//funkcija radi listu koja sadrzi uniju dvije unesene liste
int Presjek(pozicija pn, pozicija qn, pozicija head)
{
	pozicija temp = NULL; 
	pozicija pom = NULL; //za setanje kroz drugu listu

	for (pn; pn != NULL; pn = pn->next)
	{
		for (pom = qn->next; pom != NULL; pom = pom->next)
		{
			if (pn->el == pom->el)
			{
				temp = UcitajCvor(pn->el);

				if (temp)
				{
					UnosP(head, temp);
					head = head->next;
				}
			}
		}
	}

	return 7;
}