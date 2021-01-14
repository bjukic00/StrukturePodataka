#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIR_NAME_LENGHT 256

enum _result;
typedef enum _result Result;

enum _result {

	SUCCESS,
	ALLOCATION_FAILED,
	DUPLICATED_DIRECTORY,
};

struct _dir;
typedef struct _dir* PositionDir;
typedef struct _dir dir;

struct _dir {
	
	char name[DIR_NAME_LENGHT];
	PositionDir child;
	PositionDir sibling;
};

struct _stack;
typedef struct _stack* PositionStack;
typedef struct _stack stack;

struct _stack {

	PositionDir dir;
	PositionStack next;
};

PositionDir cd(PositionDir, PositionStack, char*);
PositionDir CreateDirectory(const char*);
PositionDir FindDirectory(PositionDir, const char*);
PositionDir pop(PositionStack);

Result dirr(PositionDir);
Result md(PositionDir, const char*);
Result push(PositionStack, PositionDir);
Result DeleteTree(PositionDir);

int main()
{
	char niz[10] = { 0 };
	stack head;
	dir MainDir;
	PositionDir current = &MainDir;

	head.next = NULL;
	MainDir.child = NULL;
	MainDir.sibling = NULL;
	strcpy(MainDir.name, ":C");

	while (1)
	{

		printf("\n------MENU------\n");
		printf("To create new directory, write command md and name of directory\n");
		printf("To change directory, write command cd and path\n");
		printf("To go back in previous directory, write command cd..\n");
		printf("To printf the content of directory, write command dir\n");
		printf("To exit terminal, write command exit\n\n");

		scanf("%s", niz);

		if (strcmp(niz, "md") == 0)
		{
			scanf("%s", niz);
			md(current, niz);
		}

		else if (strcmp(niz, "cd") == 0)
		{
			scanf("%s", niz);
			current = cd(current, &head, niz);
		}

		else if (strcmp(niz, "cd..") == 0)
			current = pop(&head);

		else if (strcmp(niz, "dir") == 0)
		{
			printf("\nSubdirectories of %s \n", current->name);
			dirr(current);
		}

		else if (strcmp(niz, "exit") == 0)
			break;

		else
		{
			printf("Command not found!");
			break;
		}
		
	}

	DeleteTree(&MainDir);

	return EXIT_SUCCESS;
}

PositionDir CreateDirectory(const char* name)
{
	PositionDir p = NULL;

	p = (PositionDir)malloc(sizeof(dir));

	if(!p)
	{
	    printf("Memory allocation unsuccessful!");
		return p;
	}

	strcpy(p->name, name);
	p->child = NULL;
	p->sibling = NULL;

	return p;
}

PositionDir FindDirectory(PositionDir current, const char* name)
{
	if (current->child == NULL)
		return NULL;

	current = current->child;

	while (current != NULL && strcmp(current->name, name) != 0)
		current = current->sibling;

	return current;
}

Result md(PositionDir current, const char* name)
{
	PositionDir p = NULL;

	if (FindDirectory(current, name) != NULL)
		return DUPLICATED_DIRECTORY;

	p = CreateDirectory(name);

	if (p == NULL)
		return ALLOCATION_FAILED;

	if (current->child == NULL)
	{
		current->child = p;

		return SUCCESS;
	}

	else if (strcmp(p->name, current->child->name) < 0)
	{
		p->sibling = current->child;
		current->child = p;

		return SUCCESS;
	}

	else
	{
		current = current->child;

		while (current->sibling != NULL && strcmp(p->name, current->sibling->name) > 0)
			current = current->sibling;

		p->sibling = current->sibling;
		current->sibling = p;

		return SUCCESS;
	}
}

Result push(PositionStack head, PositionDir current)
{
	PositionStack p = NULL;

	p = (PositionStack)malloc(sizeof(stack));

	if (!p)
		return ALLOCATION_FAILED;
	else
	{
		p->dir = current;

		p->next = head->next;
		head->next = p;

		return SUCCESS;
	}
}

PositionDir pop(PositionStack head)
{
	PositionDir p = NULL;
	PositionStack temp = head->next;

	if (head->next == NULL)
		return NULL;

	p = temp->dir;

	head->next = temp->next;
	free(temp);

	return p;
}

PositionDir cd(PositionDir current, PositionStack head, char* name)
{
	char temp[DIR_NAME_LENGHT] = { 0 }; //taking part of name till \ sign
	char* temp2 = name; //saving whole name with \ sign to find end of name
	char c = 92;
	unsigned int counter = 0;

	while (counter <= strlen(name))
	{
		sscanf(name, "%[^\\]s", temp);
		counter = strlen(temp) + 1;
		temp2 = name;
		name += counter;
	
		if (strcmp(current->name, temp) != 0)
			current = FindDirectory(current, temp);

		if(*(temp2 + strlen(temp)) == c)
			push(head, current);
	}
	
	return current;
}

Result dirr(PositionDir current)
{
	PositionDir p = current->child;

	if (p == NULL)
	{
		printf("Directory is empty!\n");
		return SUCCESS;
	}

	while (p != NULL)
	{
		printf("%s\n", p->name);
		p = p->sibling;
	}

	return SUCCESS;
}

Result DeleteTree(PositionDir MainDir)
{
	if (MainDir == NULL)
		return SUCCESS;

	DeleteTree(MainDir->sibling);
	DeleteTree(MainDir->child);
	free(MainDir);

	return SUCCESS;
}