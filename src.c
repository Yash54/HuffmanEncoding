#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LENGTH 200
#define MAX_SIZE_CODE 50

typedef struct node
{
    char character;
    int freq;
    struct node *left, *right;
}node;

typedef struct frequency
{
    char character;
    int freq;
    int code[MAX_SIZE_CODE];
}frequency;

typedef struct q_node
{
    node *ptr;
    struct q_node *next;
}qnode;

typedef struct queue
{
    qnode *front, *rear;
}priority_queue;

void insert(priority_queue *p_queue, node *temp)
{
	qnode *q_node=(qnode *)calloc(1,sizeof(qnode));
	q_node->ptr=temp;
	q_node->next=NULL;
	if(p_queue->front==NULL)
	{
		p_queue->front=q_node;
		p_queue->rear=q_node;
		return;
	}
	if(q_node->ptr->freq<p_queue->front->ptr->freq)
	{
		q_node->next=p_queue->front;
		p_queue->front=q_node;		
		return;
	}
	qnode *t=p_queue->front;
	while(t->next!=NULL && t->next->ptr->freq<=q_node->ptr->freq)
	{
		t=t->next;
	}
	q_node->next=t->next;
	if(t->next==NULL)
	    p_queue->rear=q_node;
	t->next=q_node;
}

priority_queue *create_priority_queue(frequency *freq, int size)
{
	priority_queue *ptr=(priority_queue *)calloc(1,sizeof(priority_queue));
	ptr->front=NULL;
	ptr->rear=NULL;
	for(int i=0; i<size; i++)
	{
		node *temp=(node *)calloc(1,sizeof(node));
		temp->character=freq[i].character;
		temp->freq=freq[i].freq;
		temp->left=temp->right=NULL;
		insert(ptr,temp);
	}
                return ptr;
}

void calculate_frequency(char *data, int size, frequency *freq, int *distinct_characters)
{
    int i=0, k=0;
    for(i=0;i<size;i++)
    {
        freq[k].freq=0;
        if(data[i]==-1)
            continue;
        freq[k].character=data[i];
        freq[k].freq++;
        for(int j=i+1;j<size;j++)
        {
            if(data[j]==data[i])
            {
                freq[k].freq++;
                data[j]=-1;
            }
        }
        k++;
    }
    *distinct_characters=k;
}

qnode *dequeue(priority_queue *p_queue)
{
    return NULL;
}


void merge_two(qnode *q1, qnode *q2, priority_queue *p_queue) 
{
   
}

node *create_huffman_tree(priority_queue *p_queue, int distinct_characters)
{
    return NULL;
}


void print_array(int arr[], int n) 
{ 
}
  

void copy_array(int *arr2, int *arr1, int size)
{
    arr2[0]=size; //index 0 stores size of array
    for(int i=1; i<=size; i++)
    {
        arr2[i]=arr1[i-1];
    }
}

void generate_code(node *root, int arr[], int top, int distinct_characters, frequency *freq)   
{ 
	if (root->left) 
    { 
        arr[top] = 0; 
        generate_code(root->left, arr, top + 1, distinct_characters, freq); 
    } 
  
     
    if (root->right) 
    { 
        arr[top] = 1; 
        generate_code(root->right, arr, top + 1, distinct_characters, freq); 
    } 
    
    if (root->left==NULL && root->right==NULL) 
    { 
        if(distinct_characters==1)  //condition is executed when only one type of character is present in data
        {
            freq[0].character=root->character;
            freq[0].code[0]=1;  //size of code is 1
            freq[0].code[1]=0;
            return;
        }
        for(int i=0; i<distinct_characters; i++)
        {
            if(freq[i].character==root->character)
            {
                copy_array(freq[i].code,arr,top);
                break;
            }
        }
    }      

} 

void display_huffman_code(frequency *freq, int distinct_characters)
{
	 printf("###### HUFFMAN CODES ######\n\n");
    for(int i=0; i<distinct_characters; i++)
    {
        printf("%c --> ", freq[i].character);
        print_array(freq[i].code, freq[i].code[0]);
        printf("\n");
    }
}

int main() 
{
    char data[MAX_LENGTH];
    data[0]='\0';
    printf("Enter data to be encoded: ");
    scanf("%[^\n]%*c",data);
    int size=strlen(data);
    if(data[0]=='\0')
    {
        printf("\nNo data is entered\n");
        exit(0);
    }
    char temp[size];
    strcpy(temp,data);
    frequency freq[size];
    int distinct_characters=0;
    calculate_frequency(temp,size,freq,&distinct_characters);
    priority_queue *p_queue=(priority_queue *)calloc(1,sizeof(priority_queue));
    p_queue=create_priority_queue(freq,distinct_characters);
    node *root=NULL;
    root=create_huffman_tree(p_queue,distinct_characters);
    int arr[MAX_SIZE_CODE];
    generate_code(root, arr, 0, distinct_characters, freq);
    printf("\nEncoded Message:  ");
    for(int i=0; i<strlen(data); i++)
    {
        for(int j=0; j<distinct_characters; j++)
        {
            if(data[i]==freq[j].character)
            {
                print_array(freq[j].code,freq[j].code[0]); //index 0 stores size of code array 
                break;
            }
        }
    }
    printf("\n\n");
    display_huffman_code(freq,distinct_characters);
    return 0;
}
