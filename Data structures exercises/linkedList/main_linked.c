#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int value;
    struct Node* next;
};

typedef struct Node Node;

Node* createNode();
Node* createList();
void printList(Node *head);
void flipList(Node **head);
void middleElement(Node *head);
void destroylist(Node *head);
void addLoop(Node *head);
void findLoop(Node *head);
void findCommin();


int main()
{
    Node *head;
    unsigned int option;
	int cont = 1;

    while(cont)
	{
		printf("Choose option:\n");
		printf("1: Create linked list\n");
		printf("2: Flip linked list\n");
		printf("3: Find middle\n");
		printf("4: Add loop\n");
		printf("5: Find loop\n");
        printf("6: Find commin node\n");
		printf("7: Print linked list\n");
		printf("Any another number - stop\n");
		
		scanf("%x", &option);
		switch(option)
		{
            case 1:
                head = createList();
                break;

            case 2:
                flipList(&head);
                break;

            case 3:
                middleElement(head);
                break;

            case 4:
                addLoop(head);
                break;

            case 5:
                findLoop(head);
                break;

            case 6:
                findCommin();
                break;

            case 7:
                printList(head);
                break;

            default:
                cont = 0;
                break;
        }
    }

    destroylist(head);
    return 0;
}

Node* createList()
{
    int i, size;
    Node *head, *last;
    srand(time(NULL));

    printf("Enter size of linked list: ");
    scanf("%d", &size);

    head = createNode();

    if(head == NULL)
    {
        return NULL;
    }

    last = head;

    for(i = 1; i < size; ++i)
    {
        last->next = createNode();

        if(last->next == NULL)
        {
            break;
        }

        last = last->next;
    }
    return head;
}

Node* createNode()
{
    Node *nodePtr;
    int value = rand()%100 + 1;

    nodePtr = (Node*)malloc(sizeof(Node));

    if(nodePtr == NULL)
    {
        return NULL;
    }

    nodePtr->value = value;
    nodePtr->next = NULL;

    return nodePtr;
}

void printList(Node *head)
{
    Node *temp;
    temp = head;

    if(head == NULL)
    {
        return;
    }

    while(temp != NULL)
    {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }

    printf("%s", "NULL\n");
}

void flipList(Node **head)
{
    Node *prew, *curr, *next;

    if(*head == NULL)
    {
        return;
    }

    prew = NULL;
    curr = *head;
    next = NULL;

    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prew;

        prew = curr;
        curr = next;        
    }
    *head = prew;
}

void middleElement(Node *head)
{
    Node *first, *second;

    if(head == NULL)
    {
        return;
    }

    first = head;
    second = head;

    while(second != NULL && second->next != NULL)
    {    
        first = first->next;    
        second = (second->next)->next;
    }
    
    printf("Middle element: %d\n", first->value);
}

void destroylist(Node *head)
{
    Node *temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void addLoop(Node *head)
{
    Node *loop = createList(); 
    Node *insert = head;

    if(loop == NULL)
    {
        return;
    }

    while(insert->next != NULL)
    {
        insert = insert->next;
    }

    insert->next = loop;

    while(loop->next != NULL)
    {
        loop = loop->next;
    }

    loop->next = insert;
}

void findLoop(Node *head)
{
    Node *first, *second;
    int isLoop = 0;

    if(head == NULL)
    {
        return;
    }

    first = head;
    second = head;

    while(second != NULL && second->next != NULL)
    {    
        first = first->next;    
        second = (second->next)->next;

        if(first == second)
        {
            isLoop = 1;
            break;
        }
    }
    
    if(isLoop)
    {
        printf("Loop is found!\n");
    }
    else
    {
        printf("Loop is not found\n");
    }
}

void findCommin()
{
    Node *firstList, *secondList, *commonList, *temp;

    firstList = createList();
    secondList = createList();
    commonList = createList();

    temp = firstList;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = commonList;

    temp = secondList;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = commonList;

    printList(firstList);
    printList(secondList);
    printList(commonList);
}



