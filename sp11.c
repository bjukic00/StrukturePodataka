#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGHT 50
#define TABLE_SIZE 11

enum _result;
typedef enum _result Result;

enum _result
{
	SUCCESS,
	FAILURE,
	ALLOCATION_FAILED
};

struct _student;
typedef struct _student* Position;
typedef struct _student* List;
typedef struct _student Student;

struct _student
{
	char name[MAX_NAME_LENGHT];
	char surname[MAX_NAME_LENGHT];
	int  iden_num;
	Position next;
};

Result Initialization(Position*);
Result AddToTable(Position*);
Result SortEntry(Position, Position);
Result Print(Position*);
Result Find(Position*, const char*, const char*);
Result Delete(Position*);

Position MakeStudent();

int Key(const char* c);

int main()
{
	List HashTable[TABLE_SIZE];

	char c;
	char name[MAX_NAME_LENGHT];
	char surname[MAX_NAME_LENGHT];

	Initialization(HashTable);

	while (1)
	{
		printf("\n--------MENU--------\n");
		printf("If you want to add a new student, press a.\n");
		printf("If you want print hash table, press p.\n");
		printf("If you want to see identification number of a student, press i.\n");
		printf("If you want to exit, press e\n\n");

		scanf(" %c", &c);

		switch (c)
		{
		case 'a':
			AddToTable(HashTable);
			break;

		case 'p':
			Print(HashTable);
			break;

		case 'i':
			printf("Insert name of a student: ");
			scanf(" %s", name);

			printf("Insert surname of a student: ");
			scanf(" %s", surname);

			Find(HashTable, name, surname);
			break;

		case 'e':
			return 0;
			break;

		default:
			printf("You pressed the wrong button!");
			break;
		}
	}

	Delete(HashTable);
	
	for (int i = 0; i < TABLE_SIZE; i++)
		free(HashTable[i]);

	return EXIT_SUCCESS;
}

Result Initialization(Position* s)
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
		*(s + i) = (Position)malloc(sizeof(Student));

	
	for (i = 0; i < TABLE_SIZE; i++)
	{
		if (*(s + i) == NULL)
			return ALLOCATION_FAILED;

		else
			(*(s + i))->next = NULL;
	}

	return SUCCESS;
}

Result AddToTable(Position* HashRow)
{
	Position q = MakeStudent();

	int key = Key(q->surname);

	SortEntry(*(HashRow + key), q);

	return SUCCESS;
}

Result SortEntry(Position head, Position q)
{
	if (q == NULL)
		return ALLOCATION_FAILED;

	if (strcmp(head->surname, q->surname) != 0)
	{
		while (head->next != NULL && strcmp(q->surname, head->surname) > 0)
			head = head->next;

		q->next = head->next;
		head->next = q;
	}

	else
	{
		while (head->next != NULL && strcmp(q->name, head->name) > 0)
			head = head->next;

		q->next = head->next;
		head->next = q;
	}

	return SUCCESS;
}

Position MakeStudent()
{
	Position q = NULL;
	char name[MAX_NAME_LENGHT] = { 0 };
	int num;

	q = (Position)malloc(sizeof(Student));

	if (!q)
	{
		printf("Memory allocation failed!");
		return NULL;
	}

	printf("Insert name of a student: ");
	scanf("%s", name);

	strcpy(q->name, name);

	printf("Insert surname of a student: ");
	scanf("%s", name);

	strcpy(q->surname, name);

	printf("Insert identification number of a student: ");
	scanf("%d", &num);

	q->iden_num = num;
	q->next = NULL;

	return q;
}

int Key(const char* c)
{
	int i;
	int val = 0;

	for (i = 0; i < 5; i++)
		val += *(c + i);

	return val % TABLE_SIZE;
}

Result Print(Position* HashRow)
{
	Position temp;
	int i;

	printf("\n-----HASH TABLE-----\n");

	for (i = 0; i < TABLE_SIZE; i++)
	{
		printf("%d.", i);

		if ((*(HashRow + i))->next == NULL)
			printf("\t----empty----\n");

		else
		{
			temp = (*(HashRow + i))->next;

			while (temp != NULL)
			{
				printf("\t%s %s --->", temp->name, temp->surname);
				temp = temp->next;
			}

			printf("\n");
		}
	}

	return SUCCESS;
}

Result Find(Position* HashRow, const char* name, const char* surname)
{
	Position temp = NULL;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if ((*(HashRow + i))->next != NULL)
		{
			temp = (*(HashRow + i))->next;

			while (temp != NULL)
			{
				if (strcmp(temp->surname, surname) == 0 && strcmp(temp->name, name) == 0)
				{
					printf("\nIdentification number of %s %s is %d\n", temp->name, temp->surname, temp->iden_num);
					return SUCCESS;
				}

				temp = temp->next;
			}
		}
	}
	
	printf("Person not found!");

	return FAILURE;
}

Result Delete(Position* HashRow)
{
	Position temp = NULL;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if ((*(HashRow + i))->next != NULL)
		{
			while ((*(HashRow + i))->next != NULL)
			{
				temp = (*(HashRow + i))->next;

				(*(HashRow + i))->next = temp->next;

				free(temp);
			}
		}
	}

	return SUCCESS;
}