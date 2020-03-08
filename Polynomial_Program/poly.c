
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct polyNode
{
	int coef;
	int expon;
	polyNode* next;
}polyNode;


int findPolynomial(polyNode* pHeadNode, int expon)
{
	polyNode* curNode = pHeadNode;
	while ( curNode != NULL )
	{
		if ( curNode->expon == expon )
		{
			return 1;
		}
		curNode = curNode->next;

	}
	return 0;
}

void addPolynomial(polyNode** pHeadNode, int coef, int expon)
{
	if ( findPolynomial(*pHeadNode, expon) )
	{
		printf("Can't!\n");
		return;
	}

	polyNode* newNode = (polyNode*)malloc(sizeof(polyNode));
	newNode->coef = coef;
	newNode->expon = expon;
	newNode->next = NULL;
	polyNode* curNode = (polyNode*)malloc(sizeof(polyNode));
	curNode = *pHeadNode;

	if ( *pHeadNode == NULL )
	{
		*pHeadNode = newNode;
	}
	else
	{
		if ( newNode->expon > curNode->expon )
		{
			newNode->next = *pHeadNode;
			*pHeadNode = newNode;
			return;
		}
		while ( curNode->next != NULL )
		{
			if ( newNode->expon < (curNode->next)->expon ) curNode = curNode->next;
			else break;
		}
		newNode->next = curNode->next;
		curNode->next = newNode;


	}

}
void removePolynomial(polyNode** pHeadNode, int expon)
{
	if ( findPolynomial(*pHeadNode, expon) == 0 )
	{
		printf("there is  no X^%d\n", expon);
		return;
	}
	polyNode* preNode = *pHeadNode;
	polyNode* delNode = NULL;
	if ( (*pHeadNode)->expon == expon )
	{
		delNode = *pHeadNode;
		*pHeadNode = delNode->next;

	}
	else
	{
		delNode = preNode->next;
		while ( 1 )
		{

			if ( delNode->expon == expon )
			{
				preNode->next = delNode->next;
				break;
			}
			preNode = preNode->next;
			delNode = preNode->next;

		}
	}
	free(delNode);

}
polyNode* multiplication(polyNode* A, polyNode* B)
{
	if ( A == NULL || B == NULL )
	{
		printf("Can't!\n");
		return NULL;
	}

	polyNode* AcurNode = A;
	polyNode* BcurNode = B;
	polyNode* resultNode = NULL;
	polyNode* tmpNode = (polyNode*)malloc(sizeof(polyNode));
	polyNode* curNode = (polyNode*)malloc(sizeof(polyNode));
	while ( AcurNode != NULL )
	{
		while ( BcurNode != NULL )
		{
			tmpNode->coef = AcurNode->coef * BcurNode->coef;
			tmpNode->expon = AcurNode->expon + BcurNode->expon;
			if ( findPolynomial(resultNode, tmpNode->expon) )
			{
				curNode = resultNode;
				while ( curNode->expon != tmpNode->expon )
				{
					curNode = curNode->next;
				}
				curNode->coef += tmpNode->coef;
				if ( curNode->coef == 0 )
				{
					removePolynomial(&resultNode, tmpNode->expon);
				}
			}

			else addPolynomial(&resultNode, tmpNode->coef, tmpNode->expon);
			BcurNode = BcurNode->next;
		}
		AcurNode = AcurNode->next;
		BcurNode = B;
	}
	return resultNode;
}
void showPolynomial(polyNode* pHeadNode)
{
	polyNode* curNode = pHeadNode;
	if ( curNode == NULL )
	{
		printf(" \n");
		return;
	}

	while ( curNode->next != NULL )
	{
		printf("%d*X^%d + ", curNode->coef, curNode->expon);
		curNode = curNode->next;
	}
	printf("%d*X^%d\n", curNode->coef, curNode->expon);
}
void clearPolynomial(polyNode** pHeadNode)
{
	polyNode* curNode = *pHeadNode;
	polyNode* delNode = NULL;
	while ( curNode != NULL )
	{
		delNode = curNode;
		curNode = curNode->next;
		free(delNode);
	}
	*pHeadNode = NULL;

}

int main()
{
	int mode, coef, expon;
	char poly;

	polyNode *A, *B, *C;
	A = B = C = NULL;

	do
	{
		printf("\nSelect the mode\n");
		printf("=================\n");
		printf("1: add polynomial\n");
		printf("2: remove polynomial\n");
		printf("3: Multiplication\n");
		printf("4: show polynomial\n");
		printf("5: clear polynomial\n");
		printf("-1: exit the program\n");
		printf("==================\n");
		printf("mode: ");
		scanf_s("%d", &mode);

		switch ( mode )
		{
		case 1:
			printf("\nChoose the polynomial to add ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if ( poly != 'A' && poly != 'B' )
				printf("Please choose right polynomial (A or B)\n");
			else
			{
				//계수와 차수를 입력 받아서 polynomial에 추가하는 함수 실행
				//이미 존재하는 차수를 입력 받을 경우 추가할 수 없음
				printf("input the coef: ");
				scanf("%d", &coef);
				printf("input the expon: ");
				scanf("%d", &expon);

				if ( poly == 'A' )
					addPolynomial(&A, coef, expon);
				else
					addPolynomial(&B, coef, expon);
			}
			break;
		case 2:
			printf("\nChoose the polynomial to remove ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if ( poly != 'A' && poly != 'B' )
				printf("Please choose right polynomial (A or B)\n");
			else
			{
				printf("input the expon: ");
				scanf("%d", &expon);
				//차수를 입력 받아서 polynomial에서 제거하는 함수 실행
				if ( poly == 'A' )
					removePolynomial(&A, expon);
				else
					removePolynomial(&B, expon);
			}
			break;
		case 3:
			printf("\nMultiplication with A and B\n");
			//C = A * B 연산을 수행
			C = multiplication(A, B);
			printf("C: ");
			//C의 결과를 출력
			showPolynomial(C);
			break;
		case 4:
			//A,B polynomial 각각 출력
			printf("A: ");
			showPolynomial(A);
			printf("B: ");
			showPolynomial(B);
			break;
		case 5:
			printf("\nChoose the polynomial to clear ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if ( poly != 'A' && poly != 'B' )
				printf("Please choose right polynomial (A or B)\n");
			else
				//해당 polynomial를 초기화 시키는 함수 실행
			{
				if ( poly == 'A' )
					clearPolynomial(&A);
				else
					clearPolynomial(&B);
			}
			break;
		default:
			break;
		}
	}
	while ( mode != -1 );
	return 0;
}
