#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#define NUMBER_EVENTS 100
#define MAX_RAND 1000

typedef struct s_heap{
  struct s_heap* right;
  struct s_heap* left;
  double priority;
}s_heap;

void swap(s_heap* a, s_heap* b);

struct s_heap* root = NULL;

struct s_heap *construct(double p){
	struct s_heap *new_element = (s_heap*) malloc(sizeof(s_heap));
	new_element->priority = p;
	new_element->left = NULL;
	new_element->right = NULL;
	return new_element;
}

//swap two heaps
void swap(s_heap* a, s_heap* b) {
	s_heap* temp;
	temp = a;
	a = b;
	b = temp;
}

//merge two heaps and returns pointer to top element
struct s_heap *merge(s_heap *first, s_heap *second){
	if (first == NULL) {
		return second;
	}else if (second == NULL) {
		return first;
	}else {
		if ((first->priority) > (second->priority)) {
			swap(first, second);
		}
		//self adjusting
		swap(first->left, first->right);

		first->left = merge(first->left, second);

		return first;
	}
}

//-------------------------------------------------
void insert(double p){
  struct s_heap* element = construct(p);
  root = merge(root, element);
}

//delete highest priority element
void delete(){
  if(root != NULL){
    struct s_heap *tmp = root;
    tmp = merge(tmp->left, tmp->right);
	free(root);
	root = tmp;
    double t = tmp->priority;

    for (int i = 0; i < NUMBER_EVENTS; i++) {
      double p = t + (rand() % MAX_RAND);
      insert(p);
    }
  }else{
    printf("CANNOT DELETE FROM EMPTY QUEUE");
  }
}
//----------------------------------------------------

void display_skew(s_heap *r){
  if(r != NULL){
    display_skew(r->left);
    printf("%lf  ", r->priority);
    display_skew(r->right);
  }
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
			inc++;
		}
	}

	else if (input2 == -3) {
		//worst case
		int inc = input;
		for (int i = input-1; i >= 0; i--) {
			insert(inc);
			inc--;
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
