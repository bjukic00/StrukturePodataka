#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_SIZE (11)
#define FILE_NAME_SIZE 1024

struct _tree;
typedef struct _tree* PositionT;
typedef struct _tree Tree;

struct _tree {

	char data[MAX_DATA_SIZE];
	PositionT left;
	PositionT right;
};

struct _stack;
typedef struct _stack* PositionS;
typedef struct _stack Stack;

struct _stack {

	PositionT tree;
	PositionS next;
};

PositionT CreateNode(char*);
PositionT pop(PositionS);
PositionT ReadFile(const char*, PositionS);

int push(PositionS, PositionT);
int IsNumber(char*);
int PrintInOrder(PositionT, FILE*);
int WriteInFile(PositionT);

FILE* OpenFileR(const char*); //file for reading
FILE* OpenFileW(void); //file for writing

int main()
{
	char name[FILE_NAME_SIZE] = { 0 };
	Stack head;
	PositionT root = NULL;

	head.next = NULL;

	printf("Insert file name: ");
	scanf(" %s", name);

	root = ReadFile(name, &head);

	WriteInFile(root);

	return EXIT_SUCCESS;
}

PositionT CreateNode(char* data)
{
	PositionT p = NULL;

	p = (PositionT)malloc(sizeof(Tree));

	if (!p)
	{
		printf("Memory allocation failed!");

		return p;
	}

	p->left = p->right = NULL;
	strcpy(p->data, data);

	return p;
}

int push(PositionS head, PositionT current)
{
	PositionS p = NULL;

	p = (PositionS)malloc(sizeof(Stack));

	if (!p)
	{
		printf("Memory allocation failed!\n");

		return EXIT_FAILURE;
	}

	p->tree = current;

	p->next = head->next;
	head->next = p;

	return 1;
}

PositionT pop(PositionS head)
{
	PositionT p = NULL;
	PositionS temp = head->next;

	if (head->next == NULL)
		return NULL;

	p = temp->tree;

	head->next = temp->next;
	free(temp);

	return p;
}

FILE* OpenFileR(const char* name)
{
	FILE* fp = NULL;

	fp = fopen(name, "r");

	if (!fp)
	{
		printf("File doesn't exist or you don't have permission!\n");

		return fp;
	}

	return fp;
}

FILE* OpenFileW(void)
{
	FILE* fp = NULL;

	fp = fopen("expression.txt", "w");

	if (!fp)
	{
		printf("File doesn't exist or you don't have permission!\n");

		return fp;
	}

	return fp;
}

PositionT ReadFile(const char* name, PositionS head)
{
	FILE* fp = OpenFileR(name);
	PositionT result = NULL;

	if (!fp)
		return NULL;

	while (!feof(fp))
	{
		PositionT node = NULL;
		char data[MAX_DATA_SIZE] = { 0 };

		fscanf(fp, " %s", data);

		if (strlen(data) == 0)
			break;

		node = CreateNode(data);

		if (!node)
		{
			fclose(fp);
			return NULL;
		}

		if (IsNumber(data))
			push(head, node);

		else
		{
			node->right = pop(head);

			if (!node->right)
			{
				printf("Postfix written in file %s is not good!\n", name);
				fclose(fp);
				return NULL;
			}

			node->left = pop(head);

			if (!node->left)
			{
				printf("Postfix written in file %s is not good!\n", name);
				fclose(fp);
				return NULL;
			}

			push(head, node);
		}
	}

	fclose(fp);

	result = pop(head);

	if (!result)
	{
		printf("Postfix written in file %s is not good!\n", name);
		return NULL;
	}

	if (pop(head) != NULL)
	{
		printf("Postfix written in file %s is not good!\n", name);
		return NULL;
	}

	return result;
}

int IsNumber(char* data)
{
	int x = 0;

	if (sscanf(data, "%d", &x) == 1)
		return 1;

	return 0;
}

int PrintInOrder(PositionT root, FILE* fp)
{
	fputc('(', fp);

	if (root->left == NULL && root->right == NULL)
	{
		fputs(root->data, fp);
		fputc(')', fp);
		return EXIT_SUCCESS;
	}

	PrintInOrder(root->left, fp);
	fputs(root->data,fp);
	PrintInOrder(root->right, fp);

	fputc(')', fp);

	return EXIT_SUCCESS;
}

int WriteInFile(PositionT root)
{
	FILE* fp = NULL;

	fp = OpenFileW();

	if (!fp)
		return EXIT_FAILURE;

	PrintInOrder(root, fp);

	return EXIT_SUCCESS;
}