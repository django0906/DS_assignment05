/*
	자료구조 5번째 숙제 풀이.
	CC BY-NC-SA

	오류에 대한 commit은 언제나 환영입니다.
*/

#include <stdio.h>	// 기본 입출력
#include <stdlib.h>	// malloc 사용
#include <string.h>	// strcmp 사용

// 이름을 저장하는 nameNode
typedef struct nameNode {
	char name[20];
	struct nameNode *nextName;
	struct node *nextNode;
}nameNode;

// 성적을 저장하는 node
typedef struct node {
	int data;
	struct node *link;
}node;

/* 
	**********  함수 설명 **********

	createNode		I: 첫 노드에 들어갈 이름; O: 첫 이름노드의 주소
: 새로운 이름노드를 생성, 그 주소를 main의 addNode로 리턴.
	addName		I: 첫번째 주소, 추가할 이름노드, 성적; O: void
: 이름노드를 추가
	addNumber		I: 노드의 주소, 성적; O: 만들어진 성적 노드의 주소값 (node*)
: 성적 노드를 만들고 성적 저장후 그 노드의 주소를 리턴. 에러발생시 종료한다.
	newNumber		I: 노드의 주소, 성적; O: 없음
: 새롭게 만들어진 성적노드를 기존 이름노드의 주소에 저장한다.
	printElements		I: 첫 이름노드의 주소; O: 없음
: 모든 이름노드를 출력하는 함수. printNodes를 포함하고 있다.
	printNodes 		I: 해당 이름노드의 첫번째 주소; O: 없음
: 모든 성적노드를 출력하는 함수. 점수노드의 끝까지 출력한다. (재귀)
	printSpecificData 	I: 첫 이름노드의 주소, 찾을 이름; O: 없음
: 특정 이름을 검색한다. 만약 해당하는 이름이 없다면 실패했다는 메시지를 보여준다.
	insertNode		I: 첫 이름노드의 주소, 추가할 이름, 성적; O: 없음
: 노드를 추가. 만약 해당하는 이름이 있다면 그 이름을 정렬된 상태로 저장한다.
	deleteNode		I: 첫 이름노드의 주소, 추가할 이름, 성적; O: 없음
: 노드를 삭제. 만약 해당하는 이름이 없다면 실패했다는 메시지를 보여준다.
: 만약 score로 -1을 받았다면 해당 이름과 모든 성적을 리스트에서 삭제한다.

	********** ********** **********
*/
nameNode* createNode(char *name);
void addName(nameNode **first, nameNode** addNode, int score);
node* addNumber(node *addr, int data);
void newNumber(node *addr, int data);
void printElements(nameNode **first);
void printNodes(node *firstNode);
void printSpecificData(nameNode **first, char *name);
void insertNode(nameNode **first, char *name, int score);
void deleteNode(nameNode **first, char *name, int score);


int main(void)
{
	nameNode *first = NULL;
	nameNode *addNode;
	FILE *data;
		// 성적저장 리스트의 첫번째 주소 저장용 포인터
		// 노드 생성 주소를 받기위한 포인터
		// 파일 포인터

	char fileName[30] = {0, };
	char studentName[20] = {0, };
	char toSearch[20] = { 0, };
	int score = 0;
	int temp = 0;
		// 파일 이름변수 (fileName)
		// 점수 저장용 임시변수(studentName, score)
		// 검색, 삭제용 학생이름(toSearch, temp)

	while (1)
		// 메뉴를 생성, 무한루프를 돌린다.
	{
		printf("1: load, 2: print list, 3: search, 4. insert data, 5. delete data from list, 6: quit ");
		scanf("%d", &temp);
		// 메뉴 선택

		switch (temp)
		{
			case 1:	// 파일을 읽어온다.
			{
				printf("enter the file name: ");
				scanf("%s", fileName);
				data = fopen(fileName, "r");		// 파일 스트림 오픈.
				if (data == NULL)			// 만일 실패하면? 종료.
				{
					printf("file read error!");
					exit(1);
				}
				while (!feof(data))			// 파일의 끝까지 읽는다.
				{
					fscanf(data, "%s %d", studentName, &score);
					addNode = createNode(studentName);
					addName(&first, addNode, score);
				}
				printf("file read completed successfully!\n");
				break;
			}
			case 2:	// 불러온 파일의 리스트를 출력한다.
			{
				printElements(&first);
				break;
			}
			case 3:	// 검색할 이름을 찾는다.
					// 리스트에 없는 이름이라면 에러 메시지를 보낸다.
			{
				printf("put a name to watch scores: ");
				scanf("%s", toSearch);
				printSpecificData(&first, toSearch);
				break;
			}
			case 4:	// 추가할 성적과 성적이 저장될 이름을 입력한다.
					// 리스트에 없는 이름이라면 이름 자체를 추가한다.
			{
				printf("put a name: ");
				scanf("%s", toSearch);
				printf("and a score: ");
				scanf("%d", &temp);
				insertNode(&first, toSearch, temp);
				break;
			}
			case 5:	// 삭제할 성적과 성적이 저장되어있는 이름을 입력한다.
					// 리스트에 없는 이름이라면 에러 메시지를 보낸다.
			{
				printf("put a name: ");
				scanf("%s", toSearch);
				printf("and a score: ");
				scanf("%d", &temp);
				deleteNode(&first, toSearch, temp);
				break;
			}
			case 6:	// 종료 전에 스트림을 닫아준다.
					// heap area 메모리 freeing 과정이 빠져있음! (추가요망)
			{
				fclose(data);
				return 0;
			}
		}
	}
}

nameNode* createNode(char *name)
// 새로운 이름노드를 생성하고 이름을 복사한 후 그 주소를 리턴.
{
	nameNode *addNode = (nameNode*)malloc(sizeof(nameNode));

	strncpy(addNode->name, name, sizeof(addNode->name));
	addNode->nextName = NULL;
	addNode->nextNode = NULL;

	return addNode;
}

void addName(nameNode **first, nameNode *addNode, int score)
// 성적 리스트에 대한 포인터를 통하여 이름과 점수를 추가한다.
// 리스트에 추가하면서 정렬을 실시한다.
{
	nameNode *nameAddr = (*first);	// 성적 리스트를 참조하기 위한 포인터
	nameNode *before = NULL;		// nameAddr 포인터의 바로 이전값을 참조.

	if (*first == NULL)
		// 이름노드가 비어있다면? addNode가 첫번째 이름노드가 된다.
	{
		*first = addNode;
		nameAddr = (*first);
		nameAddr->nextNode = addNumber(nameAddr->nextNode, score);
	}
	else
	{
		while (nameAddr->nextName != NULL)
			// 전체 리스트를 순회하는 조건.
		{
			if (strcmp((addNode->name), (nameAddr->name)) < 0)
			{
				if (strcmp((addNode->name), ((*first)->name)) < 0)
					// addNode가 first보다 사전적으로 앞에있다면?
				{
					*first = addNode;
					(*first)->nextName = nameAddr;
					(*first)->nextNode = addNumber((*first)->nextNode, score);
					// addNode가 first노드가 되고 나머지 노드들에 대해 포인터연산 실시.
					return;
				}
				else
				{
					addNode->nextName = nameAddr;
					before->nextName = addNode;
					before->nextName->nextNode = NULL;
					before->nextName->nextNode = addNumber(before->nextName->nextNode, score);
					return;
				}
			}
			else
			{
				if (strcmp((addNode->name), (nameAddr->name)) == 0)
					// 이름값이 같다면 노드만 추가.
				{
					addNode->nextNode = addNumber(addNode->nextNode, score);
					newNumber(nameAddr, score);
					return;
				}
				else
				{
					before = nameAddr;
					nameAddr = nameAddr->nextName;
					continue;
					
				}
			}
			nameAddr = nameAddr->nextName;
		}

		/* 
			이 아래 연산들은
			포인터 연산의 한계(어쩌면 본인의 한계)로 인하여 
			nameAddr의 맨 마지막을 연산하지 못하게 되는데
			그 끝영역을 체크하는 연산이다.
		*/
		if (strcmp((addNode->name), (nameAddr->name)) < 0)
		{
			addNode->nextName = nameAddr;
			before->nextName = addNode;
			before->nextName->nextNode = NULL;
			before->nextName->nextNode = addNumber(before->nextName->nextNode, score);
			return;
		}
		else if (strcmp((addNode->name), (nameAddr->name)) == 0)
			// 이름값이 같다면 노드만 추가.
		{
			addNode->nextNode = addNumber(addNode->nextNode, score);
			newNumber(nameAddr, score);
			return;
		}
		else
		{
			nameAddr->nextName = addNode;
			addNode->nextNode = addNumber(addNode->nextNode, score);
		}

	}
}

node* addNumber(node *next, int data)
// 성적 노드를 만들고 성적 저장후 그 노드의 주소를 리턴. 에러발생시 종료한다.
{
	node *nextNode = NULL;	// 의미없음. 설명하라 하면 할말없다.
	node *temp = (node*)malloc(sizeof(node));

	if (next == NULL)
		// 다음노드를 추가한다.
	{
		next = temp;
		temp->data = data;
		temp->link = NULL;
	}
	else
		// 본인이 짠 로직대로 작동하지 않았을 때 사용하던 소스코드이다.
		// 미처 삭제하지 못함.....
	{
		fprintf(stderr, "error occured!");
		exit(1);
	}
	return temp;
}

void newNumber(nameNode *addr, int data)
// 새 노드를 추가할 때의 방식.
// 이름노드 바로 다음에 새로운 성적노드를 추가한다.
{
	node *temp = (node*)malloc(sizeof(node));
	temp->link = addr->nextNode;
	temp->data = data;

	addr->nextNode = temp;
}

void printElements(nameNode **first)
// 모든 이름노드를 출력하는 함수. printNodes를 포함하고 있다.
{
	nameNode *tempPrint = (*first); // 성적 리스트를 참조하기 위한 포인터
	while (tempPrint != NULL)
	{
		printf("%s: ", tempPrint->name);
		printNodes(tempPrint->nextNode);
		tempPrint = tempPrint->nextName;
	}
}

void printNodes(node *firstNode)
// 모든 성적노드를 출력하는 함수. 점수노드의 끝까지 출력한다. (재귀)
{
	if (firstNode->link == NULL)
		// 재귀는 탈출조건이 명확해야한다!
	{
		printf("%d\n", firstNode->data);
		return;
	}
	else
	{
		printf("%d->", firstNode->data);
		printNodes(firstNode->link);
	}
}

void printSpecificData(nameNode **first, char *name)
// 특정 이름을 검색한다. 만약 해당하는 이름이 없다면 실패했다는 메시지를 보여준다.
{
	nameNode *tempPrint = (*first); // 성적 리스트를 참조하기 위한 포인터
	while (tempPrint != NULL)
	{
		if (strcmp((tempPrint->name), name) == 0)
			// 해당하는 이름을 찾았다면?
		{
			printf("%s: ", tempPrint->name);
			printNodes(tempPrint->nextNode);
			return;
		}
		else
			tempPrint = tempPrint->nextName;
	}
	// 해당하는 이름이 없다면 탐색에 실패했다는 메시지를 보낸다.
	printf("not found.\n");
}

void insertNode(nameNode **first, char *name, int score)
//노드를 추가. 만약 해당하는 이름이 있다면 그 이름을 정렬된 상태로 저장한다.
{
	nameNode *temp = (*first); // 성적 리스트를 참조하기 위한 포인터
	nameNode *addNode = createNode(name);

	while (temp != NULL)
	{
		if (strcmp((temp->name), name) == 0)
		// 해당하는 이름이 있다면? 성적을 추가한다.
		{
			newNumber(temp, score);
			return;
		}
		else
			temp = temp->nextName;
	}
	// 해당하는 이름이 없다면 순서에 맞게 리스트에 추가된다.
	addName(first, addNode, score);
	printf("add completed successfully!\n");
}

void deleteNode(nameNode **first, char *name, int score) 
// 노드를 삭제. 만약 해당하는 이름이 없다면 실패했다는 메시지를 보여준다.
// 만일 성적으로 -1을 받았다면 해당 이름과 모든 성적을 리스트에서 삭제한다.
{
	nameNode *temp = (*first); // 성적 리스트를 참조하기 위한 포인터
	nameNode *delName = NULL;	// 삭제하려는 '이름노드'에 대한 포인터
	nameNode *before = NULL;		// 현재 순회중인 '이름노드' 포인터의 이전값
	node *delNode = NULL;		// 삭제하려는 '점수노드'에 대한 포인터
	node *nodeBefore = NULL;		// 현재 순회중인 '점수노드' 포인터의 이전값
	node *nodeTmp = NULL;		// 삭제하려는 점수노드의 바로 다음 노드에 대한 포인터

	if (score != -1) // 특정 성적을 삭제하고 싶을 때
	{
		while (temp != NULL)
		{
			if (strcmp((temp->name), name) == 0)
				// 해당 이름을 찾았다면?
			{
				if (temp->nextNode->link == NULL)
				{
					free(temp->nextNode);
					temp->nextNode = NULL;
					if (strcmp(temp->name, (*first)->name) == 0)
					{
						delName = (*first)->nextName;
						free((*first));
						*first = delName;
						printf("delete completed successfully!\n");
						return;
					}
					else
					{
						delName = temp->nextName;
						free(temp);
						before->nextName = delName;
						printf("delete completed successfully!\n");
						return;
					}
				}
				else
				{
					delNode = temp->nextNode;
					nodeBefore = delNode;
					while (delNode->data != score)
					{
						nodeBefore = delNode;
						delNode = delNode->link;
					}
					if (temp->nextNode->data == score)
					{
						nodeTmp = delNode->link;
						free(delNode);
						temp->nextNode = nodeTmp;
					}
					else
					{
						nodeTmp = delNode->link;
						free(delNode);
						nodeBefore->link = nodeTmp;
					}
					printf("delete completed successfully!\n");
					return;
				}
			}
			else
			// 다음 이름을 찾기위해 포인터를 수정.
			{
				before = temp;
				temp = temp->nextName;
			}
		}
	}
	else	// 성적에 대한 값으로 -1을 입력받았을 때
	{
		while (temp != NULL)
		{
			if (strcmp((temp->name), name) == 0)
			// 해당 이름을 찾았다면?
			{
				if (strcmp(temp->name, (*first)->name) == 0)
				// 그 이름이 첫번째 이름이라면? 바로 다음 이름이 첫번째가 되도록 조치한다.
				{
					delName = (*first)->nextName;
					free((*first));
					*first = delName;
					printf("delete completed successfully!\n");
					return;
				}
				else
				// 아니면 다음 이름노드에 이어붙이고 삭제한다.
				{
					delName = temp->nextName;
					free(temp);
					before->nextName = delName;
					printf("delete completed successfully!\n");
					return;
				}
			}
			else
			// 다음 성적을 찾기위해 포인터를 수정.
			{
				before = temp;
				temp = temp->nextName;
			}
		}
	}
	// 모든 조건을 충족하지 못했으므로 삭제 실패!
	printf("falied to delete! : name not found.\n");
}
