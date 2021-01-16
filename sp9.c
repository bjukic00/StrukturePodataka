#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum _result;
typedef enum _result Result;

enum _result {

	EMPTY,
	SUCCESS,
	EMPTY_LIST,
	ELEMENT_NOT_FOUND,
};

struct _tree;
typedef struct _tree* PositionT;
typedef struct _tree tree;

struct _tree {
	
	int el;
	PositionT left;
	PositionT right;
};

PositionT CreateNode(int);
PositionT AddNewElement(PositionT, int);
PositionT FindElement(PositionT, int);
PositionT FindPrevElement(PositionT, int);

Result DeleteElement(PositionT, int);
Result DeleteEdgeElement(PositionT, int);
Result DeleteMiddleElement(PositionT, int);
Result DeleteHeadElement(PositionT);
Result DeleteTree(PositionT);
Result Print(PositionT);

int main()
{
	char c;
	int x;

	tree MainNode;
	PositionT temp = NULL;

	MainNode.left = MainNode.right = NULL;
	MainNode.el = EMPTY;

	while (1)
	{
		printf("\n-----MENU-----\n");
		printf("If you want to add a new element, write command a\n");
		printf("If you want to check if element is on the list, press f\n");
		printf("If you want to delete some element, press d\n");
		printf("If you want to print the list, pres p\n");
		printf("If you want to exit, press e\n\n");

		scanf(" %c", &c);

		switch (c)
		{
		case 'a': 

			printf("Enter element you want to add:\t");
			scanf("%d", &x);

			if (MainNode.el == EMPTY)
				MainNode.el = x;
			else
				AddNewElement(&MainNode, x);

			break;

		case 'f':

			printf("Enter element you want to find:\t");
			scanf("%d", &x);

			temp = FindElement(&MainNode, x);

			if (!temp)
				printf("Element not found!\n");

			else
				printf("Element %d is found in the list.\n", temp->el);

			break;

		case 'd':
			printf("Enter element you want to delete: ");
			scanf("%d", &x);

			x = DeleteElement(&MainNode, x);

			if (x == SUCCESS)
				printf("Success, element is deleted!\n");

			else
				printf("Error, element not found!\n");

			break;

		case 'p':
			Print(&MainNode);
			break;

		case 'e':
			return 0;
			break;

		default:
			printf("Error! You entered wrong command.\n");
		}
	}

	DeleteTree(&MainNode);

	return EXIT_SUCCESS;
}

PositionT CreateNode(int x)
{
	PositionT p = NULL;

	p = (PositionT)malloc(sizeof(tree));

	if (!p)
	{
		printf("Memory allocation failed!");
		return p;
	}

	p->left = p->right = NULL;
	p->el = x;

	return p;
}

PositionT AddNewElement(PositionT current, int x)
{
	PositionT p = NULL;

	if (current == NULL)
	{
		p = CreateNode(x);

		return p;
	}

	else if (x < current->el)
		current->left = AddNewElement(current->left, x);

	else
		current->right = AddNewElement(current->right, x);

	return current;
}

Result Print(PositionT current)
{
	if (current == NULL)
		return EMPTY_LIST;

	if (current->el == EMPTY)
	{
		printf("List is empty!\n");
		return EMPTY_LIST;
	}
	
	else if (current->left == NULL && current->right == NULL)
	{
		printf("%d\t", current->el);
		return SUCCESS;
	}

	Print(current->left);
	printf("%d\t", current->el);
	Print(current->right);

	return SUCCESS;
}

PositionT FindElement(PositionT current, int x)
{
	if (current == NULL)
		return current;

	if (current->el == x)
		return current;

	else if (x < current->el)
		return current = FindElement(current->left, x);

	else
		return current = FindElement(current->right, x);
}

PositionT FindPrevElement(PositionT current, int x)
{
	if (current->left == NULL && current->right == NULL)
		return current;

	if(current->left != NULL)
		if (current->left->el == x)
			return current;

	if(current->right != NULL)
		if (current->right->el == x)
			return current;

	if (x < current->el)
		return current = FindElement(current->left, x);

	else
		return current = FindElement(current->right, x);
}

Result DeleteEdgeElement(PositionT current, int x)
{
	PositionT temp = FindPrevElement(current, x);
	PositionT temp2 = NULL;

	if (!temp)
		return ELEMENT_NOT_FOUND;

	if (temp->left != NULL)
	{
		if (temp->left->el == x)
		{
			temp2 = temp->left;
			temp->left = NULL;
			free(temp2);
		}
	}

	else if (temp->right != NULL)
	{
		if (temp->right->el == x)
		{
			temp2 = temp->right;
			temp->right = NULL;
			free(temp2);
		}
	}

	return SUCCESS;
}

Result DeleteMiddleElement(PositionT current, int x)
{
	PositionT temp = FindElement(current, x);
	PositionT temp2 = NULL;

	if (!temp)
		return ELEMENT_NOT_FOUND;

	if (temp->right != NULL)
	{
		temp2 = temp->right;

		temp->el = temp2->el;
		temp->right = NULL;
		free(temp2);
	}

	else if (temp->left != NULL)
	{
		temp2 = temp->left;

		temp->el = temp2->el;
		temp->left = NULL;
		free(temp2);
	}

	return SUCCESS;
}

Result DeleteHeadElement(PositionT current)
{
	current->el = EMPTY;

	return SUCCESS;
}

Result DeleteElement(PositionT current, int x)
{
	PositionT temp = FindElement(current, x);

	if (current->left == NULL && current->right == NULL)
		return DeleteHeadElement(current);

	else if (temp->left == NULL && temp->right == NULL)
		return DeleteEdgeElement(current, x);

	else
		return DeleteMiddleElement(current, x);
}

Result DeleteTree(PositionT MainNode)
{
	if (MainNode == NULL)
		return SUCCESS;

	DeleteTree(MainNode->left);
	DeleteTree(MainNode->right);
	free(MainNode);

	return SUCCESS;
}


