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
bool isloop(struct node * h){
	struct node * fast, * slow;
	bool ret;
	fast = h;
	slow = h;
	ret = false;
	while(fast->next->next){
		fast = fast->next->next;
		slow = slow->next;
		if(slow == fast){
			ret = true;
			break;
		}
	}
	return ret;
}
enum {EXIT, ADD, LOOP, DETECT,PRINT};
void editloop(struct node * h){
	int loopid,i;
	struct node * loop = NULL;
	printf("enter loop to index\n");
	scanf("%d",&loopid);
	i = 1;
	while(h->next){
		if(i == loopid)
			loop = h;
		h = h->next;
		i++;
	}
	h->next = loop;
}
int menuloop(){
	struct node * curr =NULL;
	struct node * cp = NULL;
	int ch;
	while(1){
		printf("0.EXIT\n1.to add\n2.to loop\n3.detect\n4.print\n");
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
			case LOOP:
				editloop(cp);
				break;
			case DETECT:
				printf("is loop %d\n",isloop(cp));
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
