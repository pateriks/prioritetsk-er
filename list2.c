#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_EVENTS 100
#define MAX_RAND 1000

typedef struct eventlist{
  double prio;
  struct eventlist* prev;
  struct eventlist* next;
}eventlist;

int allocated_memory = 0;

//struct eventlist *list = NULL;
struct eventlist *firstNode = NULL;
struct eventlist *lastNode = NULL;

struct eventlist* construct(double p){
  struct eventlist* new_element = (eventlist*) malloc(sizeof(eventlist));
  new_element->prio = p;
  new_element->prev = NULL;
  new_element->next = NULL;
  return new_element;
}


void insertBack(struct eventlist *node){
  struct eventlist *tmp = lastNode;
  double p = node->prio;
  while((tmp != NULL) && (p < tmp->prio)){
    tmp = tmp->prev;
  }
  if(tmp == NULL){
    firstNode->prev = node;
    node->next = firstNode;
    node->prev = NULL;
    firstNode = node;
    return;
  }else if(tmp == lastNode){
    lastNode->next = node;
    node->prev = lastNode;
    node->next = NULL;
    lastNode = node;
    return;
  }else{
    struct eventlist *tmp_next = tmp->next;
    node->next = tmp_next;
    node->prev = tmp;
    tmp_next->prev = node;
    tmp->next = node;
    return;
  }
}

void insertFront(struct eventlist *node){
  struct eventlist *tmp = firstNode;
  double p = node->prio;
  while((tmp != NULL) && (p >= tmp->prio)){
    tmp = tmp->next;
  }
  if(tmp == NULL){
    lastNode->next = node;
    node->prev = lastNode;
    node->next = NULL;
    lastNode = node;
    return;
  }else if(tmp == firstNode){
    node->next = firstNode;
    firstNode->prev = node;
    node->prev = NULL;
    firstNode = node;
    return;
  }else{
    struct eventlist *tmp_prev = tmp->prev;
    tmp_prev->next = node;
    tmp->prev = node;
    node->next = tmp;
    node->prev = tmp_prev;
    return;
  }

}

void insert(double p){
  struct eventlist *element = construct(p);
  if((firstNode == NULL) && (lastNode == NULL)){
    firstNode = element;
    lastNode = element;
    return;
  }
  if(firstNode == lastNode){
    if(p < firstNode->prio){
      element->next = lastNode;
      lastNode->prev = element;
      firstNode = element;
      return;
    }else{
      element->prev = firstNode;
      firstNode->next = element;
      lastNode = element;
      return;
    }
  }
  double firstprio = firstNode->prio;
  double lastprio = lastNode->prio;
  if(p > ((lastprio + firstprio) / 2)){
    insertFront(element);
  }else{
    insertBack(element);
  }
}

//delete tar bort elementet längst fram och skapar NUMBER_EVENTS nya events med random prioritet
void delete(){

  if(firstNode != NULL){
    struct eventlist *delElem = firstNode;
    double t = delElem->prio;
    firstNode = firstNode->next;
    if(firstNode != NULL){
      firstNode->prev = NULL;
    }
    free(delElem);

    for(int i = 0; i < NUMBER_EVENTS; i++){
      double p = t + (rand() % MAX_RAND);
      insert(p);
    }
  }else{
    printf("CANNOT DELETE FROM EMPTY QUEUE! ");
  }
}

void display_list(){
  struct eventlist *tmp = firstNode;
  while(tmp != NULL){
    printf(" %lf,", tmp->prio);
    tmp = tmp->next;
  }
  printf("\n");
}

//DRIVER PROGRAM
int main(int argc, char *argv[]){
	srand(time(0));
	struct timespec t_start, t_stop;
	clock_gettime(CLOCK_MONOTONIC_COARSE, &t_start);

	int input = argv[1] != NULL ? atoi(argv[1]) : 0;
	int input2 = argv[2] != NULL ? atoi(argv[2]) : 0;
	if (input2 == -1) {
		int inc = 1;
		//best case
		for (int i = 0; i < input; i++) {
			insert(inc);
		}
	}
	else if (input2 == -2) {
		//worst case
		int inc = 1;
		int shift = 1;
		for (int i = 0; i < input - 2; i++) {
			if (shift == -1) {
				insert(input - inc * shift);
				if (input > input - 10) {
					//printf("input = %ld\n", input + inc * shift);
				}
				shift = shift * -1;
			}
			else {
				insert(inc);
				if (input > input - 10) {
					//printf("input = %ld\n", inc);
				}
				shift = shift * -1;
				inc++;
			}
		}
	}
	else {
		insert(1);
		insert(1);
		insert(1);
		for (int i = 0; i < input; i++) {
			delete();
		}
	}
	clock_gettime(CLOCK_MONOTONIC_COARSE, &t_stop);
	long wall_sec = t_stop.tv_sec - t_start.tv_sec;
	long wall_nsec = t_stop.tv_nsec - t_start.tv_nsec;
	long wall_msec = (wall_sec * 1000) + (wall_nsec / 1000000);
	printf("%ld", wall_msec);
	return 0;
}
