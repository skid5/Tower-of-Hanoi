#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_DISKS 4 //change this to change difficulty
//linked list structure
typedef struct node {
	int data;
	struct node *next;
	} node_type;

node_type * create_node(int data) {
	node_type *new = malloc(sizeof(node_type));

	new->data = data;
	new->next = NULL;
	return new;
}

void push(node_type **tower, int data) {
	node_type *new = create_node(data);
 	
	new->next = *tower;
	*tower = new;
}

int pop(node_type **tower) {
	node_type *x = *tower;
	*tower = (*tower)->next;

	int pop = x->data;
	free(x);
	return pop;
}
//moves a value from one stack to another,
//if possible under the rules of towers of hanoi
void move(node_type **tower1, node_type **tower2) {
	int x;
	x = pop(tower1);
	if(x < (*tower2)->data || (*tower2)->data == 0) {
		push(tower2, x);
		printf("%d moved\n", x);
	}
	else {
		push(tower1, x);
		printf("can't move %d\n", x);
	}
}
//prints the values of the towers
void print_towers(node_type *tower1, node_type *tower2, node_type *tower3) {
	node_type *x = tower1;
	node_type *y = tower2;
	node_type *z = tower3;
	
	printf("tower1 has values: ");
	printf("%d ", x->data);
	while(x->next != NULL) {
		x = x->next;
		printf("%d ", x->data);
	}
	printf("\n");

	printf("tower2 has values: ");
	printf("%d ", y->data);
	while(y->next != NULL) {
		y = y->next;
		printf("%d ", y->data);
	}
	printf("\n");

	printf("tower3 has values: ");
	printf("%d ", z->data);
	while(z->next != NULL) {
		z = z->next;
		printf("%d ", z->data);
	}
	printf("\n");
}

void usage() {
	printf("Usage: inputs 'r' 't' 'f' 'g' 'v' 'b'\n");
	printf("Press:   r to move from tower1 to tower3\n\t t to move from tower1 to tower2\n\t f to move from tower2 to tower1\n\t g to move from tower2 to tower3\n\t v to move from tower3 to tower2\n\t b to move from tower3 to tower1\n\t (q to quit)\n");
}

//returns true if first tower is empty and one of the others is also empty
//meaning that the disks have fully moved to one tower other than the first
int win_condition(node_type *tower1, node_type *tower2, node_type *tower3) {
	return (!tower1->data && (!tower2->data || !tower3->data));
}

//makes an ascii representation of game state
//prints '-' to represent disks and '|' to represent empty space
//towers are displayed vertically
//(possible improvement would be to display them horizontally)
void tower_visual(node_type *tower1, node_type *tower2, node_type *tower3) {
	node_type *x = tower1;
	node_type *y = tower2;
	node_type *z = tower3;

	int i;
	int j;
	
	printf("Tower1\n");
	printf("************************\n\n");
	for(i=0; i < NUMBER_OF_DISKS; i++) {
		if(x->next == NULL) {
			for(i; i < NUMBER_OF_DISKS; i++) {
				printf("|");
				printf("\n");
			}
			break;
		}
		for(j=0; j<x->data; j++) {
			printf("-");
		}
		printf("\n");
		x = x->next;
	}
	printf("\n************************\n");

	printf("Tower2\n");
	printf("************************\n\n");
	for(i=0; i < NUMBER_OF_DISKS; i++) {
		if(y->next == NULL) {
			for(i; i < NUMBER_OF_DISKS; i++) {
				printf("|");
				printf("\n");
			}
			break;
		}
		for(j=0; j<y->data; j++) {
			printf("-");
		}
		printf("\n");
		
		y = y->next;
	}
	printf("\n************************\n");

	printf("Tower3\n");
	printf("************************\n\n");
	for(i=0; i < NUMBER_OF_DISKS; i++) {
		if(z->next == NULL) {
			for(i; i < NUMBER_OF_DISKS; i++) {
				printf("|");
				printf("\n");
			}
			break;
		}
		for(j=0; j<z->data; j++) {
			printf("-");
		}
		printf("\n");
		
		z = z->next;
	}
	printf("\n************************\n");
}

//loop that takes care of the game logic
void game_loop(node_type **tower1, node_type **tower2, node_type **tower3) {
	char c;
	print_towers(*tower1,*tower2, *tower3);
	tower_visual(*tower1,*tower2, *tower3);
	for(;;) {
		usage();
		c = getchar();

		switch(c) {
			case 'r' :
				move(tower1, tower3);
				break;
			case 't' :
				move(tower1, tower2);
				break;
			case 'f' :
				move(tower2, tower1);
				break;
			case 'g' :
				move(tower2, tower3);
				break;
			case 'v' : 
				move(tower3, tower2);
				break;
			case 'b' :
				move(tower3, tower1);
				break;
			case 'q' :
				printf("Thanks for playing\n");
				exit(1);
			default :
				printf("\n");
		}
		print_towers(*tower1,*tower2, *tower3);
		tower_visual(*tower1,*tower2, *tower3);
		if(win_condition(*tower1, *tower2, *tower3)) {
				printf("Gratz! You won!\n");
				return;
		}
	}
}

//towers are initialized under main
//the the game loop is run
int main(void) {
	node_type *tower1 = create_node(0);
	node_type *tower2 = create_node(0);
	node_type *tower3 = create_node(0);
	
	int i;
	for(i=NUMBER_OF_DISKS; i > 0; i--) {
		push(&tower1, i);
	}

	game_loop(&tower1, &tower2, &tower3);
}
