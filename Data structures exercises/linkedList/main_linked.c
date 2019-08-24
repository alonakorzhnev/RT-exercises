#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*TEST*/
struct Node
{
    int value;
    struct Node* next;
};

typedef struct Node Node;

Node* createNode();
Node* createList(int size);
void printList(Node *head);
void flipList(Node **head);
void middleElement(Node *head);
void destroyList(Node *head, int size);
int addLoop(Node *head);
void findLoop(Node *head);
void findCommin();


int main()
{
    Node *head;
    unsigned int option;
	int cont = 1, size = 0, loopSize = 0;
    srand(time(NULL)); 

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
                printf("Enter size of linked list: ");
                scanf("%d", &size);
                head = createList(size);
                break;

            case 2:
                flipList(&head);
                break;

            case 3:
                middleElement(head);
                break;

            case 4:
                loopSize = addLoop(head);
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

    destroyList(head, size + loopSize);
    return 0;
}

Node* createList(int size)
{
    int i;
    Node *head, *last;      

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

void destroyList(Node *head, int size)
{
    Node *temp;

    while(size != 0)
    {
        temp = head;
        head = head->next;
        free(temp);
        --size;
    }
}

int addLoop(Node *head)
{
    Node *loop, *insert = head;
    int size;

    printf("Enter size of loop to add: ");
    scanf("%d", &size);

    loop = createList(size); 

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

    return size;
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
    Node *firstList, *secondList, *commonList, *temp, *firstTmp, *secondTmp;
    int difference;
    int firstSize, secondSize, commonSize;

    printf("Enter size of first, second and common linked list: ");
    scanf("%d%d%d", &firstSize, &secondSize, &commonSize);

    firstList = createList(firstSize);
    secondList = createList(secondSize);
    commonList = createList(commonSize);

    if(firstList == NULL || secondList == NULL || commonList == NULL)
    {
        return;
    }

    /*Create lists with commin node*/
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

    /*Find size difference*/
    firstTmp = firstList;
    secondTmp = secondList;

    difference = firstSize - secondSize;
    if(difference > 0)
    {
        while(difference)
        {
            firstTmp = firstTmp->next; 
            --difference;
        }
    }
    else
    {
        difference = abs(difference);
        while(difference)
        {
            secondTmp = secondTmp->next; 
            --difference;
        }
    }
    
    /*Find commin node*/
    while(firstTmp->next != NULL)
    {
        firstTmp = firstTmp->next;    
        secondTmp = secondTmp->next;

        if(firstTmp == secondTmp)
        {
            printf("Commin node: %d\n", firstTmp->value);
            break;
        }
    }

    /*Destroy lists*/
    destroyList(firstList, firstSize + commonSize);
    destroyList(secondList, secondSize);
}



