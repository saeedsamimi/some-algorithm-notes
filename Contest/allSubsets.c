#include <stdio.h>
#include <stdlib.h>

struct node {
  struct node* prev;
  char data;
  struct node* next;
};

struct node* head = NULL;

// functions for doubly linked list
void push_back(char);
void pop_back();
void insort_print();
struct node* create_node(char);
void free_memory();

void getAllSubsets(char,char);

int main(){
  int n;
  scanf("%d",&n);
  getAllSubsets(n,0);
  free_memory();
  return 0;
}

void getAllSubsets(char n,char index){
  insort_print();
  for(char i = index;i<n;i++){
    push_back(i+1);
    getAllSubsets(n,i+1);
    pop_back();
  }
}

struct node* create_node(char data) {
  struct node *new_node = (struct node *) malloc(sizeof(struct node));
  if (!new_node)
    return NULL;
  new_node->prev = NULL;
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

void push_back(char data){
  struct node* new_node = create_node(data);
  if (!new_node)
    printf("Memory not allocated!");
  else if (!head)
    head = new_node;
  else{
    struct node* temp = head;
    //traverse to the last node
    while (temp->next)
      temp = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
  }
}

void pop_back(){
  if (head){
    struct node* temp = head;
    char data = 0;
    while (temp->next)
      temp = temp->next;
    if (!temp->prev)
      head = NULL;
    else
      temp->prev->next = temp->next;
    data = temp->data;
    free(temp);
  }
}

void insort_print() {
  struct node *temp = head;
  printf("{");
  if(temp){
    printf("%d", temp->data);
    temp = temp->next;
  }
  while(temp){
    printf(", %d",temp->data);
    temp = temp->next;
  }
  printf("}\n");
}

void free_memory() {
  struct node* temp = head;
  struct node* current;
  while(temp){
    current = temp;
    temp = temp->next;
    free(current);
  }
}