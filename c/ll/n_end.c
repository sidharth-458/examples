#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node{
	struct node * next;
	struct node * prev;
	int info;
};

struct node * add(struct node * curr){
	struct node * ret = malloc(sizeof(*ret));
	if(!ret){
		perror("malloc");
		exit(-1);
	}
	ret->next = 0;
	ret->prev = curr;
	scanf("%d",&ret->info);
	return ret;
}

void print(struct node * h){
	while(h){
		printf("%d->",h->info);
		h = h->next;
	}
	printf("NULL\n");
}
struct node * n_end(struct node *h){
	struct node * fast,*slow;
	int len = 1,dist,i,n;
	printf("enter index\n");
	scanf("%d",&n);
	slow = h;
	fast = h;

	while(fast){
		len++;
		fast = fast->next;
	}
	dist = len - n;
	i = 0;
	while(i++ < dist)
		slow = slow->next;
	return slow;
}
enum {EXIT, ADD,N_END,PRINT};
int menuloop(){
	struct node * curr =NULL;
	struct node * cp = NULL;
	int ch;
	while(1){
		printf("0.EXIT\n1.to add\n2.n end\n3.print\n");
		scanf("%d",&ch);
		switch(ch){
			case EXIT:
				exit(0);
				break;
			case ADD:
				if(!curr){
					curr = add(curr);
					cp = curr;
				}
				else{
					curr->next = add(curr->next);
					curr = curr->next;
				}
				break;
			case N_END:
				printf("nth from end is %d\n",n_end(cp)->info);
				break;
			case PRINT:
				print(cp);
				break;
			default:
				break;
		}
	}
}
int main(){
	menuloop();
}
