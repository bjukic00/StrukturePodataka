#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba osoba;

struct _osoba
{
	char ime[MAX];
	char prezime[MAX];
	int godina;
	pozicija next;
};

pozicija StvoriCvor(void);
pozicija StvoriOsobu(const char*, const char*, int);
pozicija PronadiPrezime(pozicija, const char*);
pozicija PronadiPrethodni(pozicija, const char*, const char*, int);

void UnosP(pozicija, pozicija);
void UnosK(pozicija, pozicija);
void Ispis(pozicija);
void Brisi(pozicija, const char*, const char*, int);


int main()
{
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina;
	char c; 

	osoba head;
	pozicija p = NULL;
	pozicija q = NULL;

	head.next = NULL;

	printf("MENU:\n");
	
	while (1)
	{
		printf("\nAko zelite dodati osobu na pocetak, unesite p.\n");
		printf("Ako zelite dodati osobu na kraj, unesite k.\n");
		printf("Ako zelite provjeriti postoji li osoba u listi, unesite l.\n");
		printf("Ako zelite izbrisati osobu iz liste, unesite o.\n");
		printf("Ako zelite ispisati listu, unesite i.\n");
		printf("Ako zelite izaci iz programa, unesite z.\n\n");
		

		scanf(" %c", &c);

		switch (c)
		{
		case 'p':

			printf("\nUnesite ime: ");
			scanf(" %s", ime);

			printf("Unesite prezime: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja: ");
			scanf(" %d", &godina);

			p = StvoriOsobu(ime, prezime, godina);
			UnosP(&head, p);

			break;

		case 'k':

			printf("\nUnesite ime: ");
			scanf(" %s", ime);

			printf("Unesite prezime: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja: ");
			scanf(" %d", &godina);

			p = StvoriOsobu(ime, prezime, godina);
			UnosK(&head, p);

			break;
			
		case 'l':
			printf("\nUnesite prezime koje zelite pronaci: ");
			scanf(" %s", prezime);

			if (p = PronadiPrezime(head.next, prezime))
			{
				printf("Prezime postoji u listi!\n");
			}

			else
				printf("Prezime ne postoji u listi!\n");

			break;

		case 'o':

			printf("\nUnesite ime osobe koju zelite izbrisat: ");
			scanf(" %s", ime);

			printf("Unesite prezime osobe koju zelite izbrisat: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja osobe koje zelite izbrisat: ");
			scanf(" %d", &godina);

			Brisi(&head, ime, prezime, godina);

			break;
		
		case 'i':
			Ispis(head.next);

			break;

		case 'z':
			return 0;
			break;
		}

	}

	return 0;
}

pozicija StvoriCvor(void)
{
	pozicija p = NULL;

	p = (pozicija)malloc(sizeof(osoba));

	if (!p) 
	{
		printf("Neuspjesno alociranje memorije!");

		return p;
	}

	p->next = NULL;

	return p;
}

pozicija StvoriOsobu(const char* ime, const char* prezime, int godina)
{
	pozicija q = StvoriCvor();

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);

	q->godina = godina;

	return q;
}

void UnosP(pozicija head, pozicija p)
{
	p->next = head->next;
	head->next = p;
}

void UnosK(pozicija head, pozicija p)
{
	while (head->next != NULL)
	{
		head = head->next;
	}

	UnosP(head, p);
}

void Ispis(pozicija headn) //salje se adresa prvog elementa koji se zeli ispisat
{
	while (headn != NULL)
	{
		printf("%s %s %d\n", headn->ime, headn->prezime, headn->godina);

		headn = headn->next;
	}
}

pozicija PronadiPrezime(pozicija headn, const char* prezime)
{
	while (headn != NULL && strcmp(headn->prezime, prezime))
	{
		headn = headn->next;
	}

	if (!headn)
		return headn;

		return headn;
}

pozicija PronadiPrethodni(pozicija head, const char* ime, const char* prezime, int godina)
{
	while (head->next != NULL && (strcmp(head->next->ime, ime) || strcmp(head->next->prezime, prezime) || head->next->godina != godina))
		head = head->next;

	if (!head->next)
		return head->next;

	else
		return head;
}

void Brisi(pozicija head, const char* ime, const char* prezime, int godina)
{
	pozicija temp = NULL;

	head = PronadiPrethodni(head, ime, prezime, godina);

	if (head)
	{
		temp = head->next->next;
		free(head->next);
		head->next = temp;
		free(temp);
	}

	else
		printf("Osoba ne postoji u listi!");
}

