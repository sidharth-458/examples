#include<stdio.h>
#include<stdlib.h>

struct node{
	struct node * next;
	int info;
};

struct node * add(int info){
	struct node * ret = malloc(sizeof(*ret));
	if(!ret){
		perror("malloc");
		exit(-1);
	}
	ret->next = 0;
	ret->info = info;
	return ret;
}

void print(struct node * h){
	while(h){
		printf("%d->",h->info);
		h = h->next;
	}
	printf("NULL\n");
}
struct node * merge(struct node * h1, struct node * h2){
	struct node * head;
	struct node dummy={0};
	head = &dummy;

	while(h1 && h2){
		if(h1->info < h2->info){
			head->next = h1;
			h1 = h1->next;
			printf("h1\n");
		}
		else{
			head->next = h2;
			h2 = h2->next;
			printf("h2\n");
		}
		head = head->next;
	}
	head->next = (h1)? h1:h2;
	return dummy.next;
	
}

int main(){
	struct node * head1 = add(1);
	head1->next= add(3);
	head1->next->next = add(5);
	head1->next->next->next = add(7);
	print(head1);

	struct node * head2 = add(2);
	head2->next= add(4);
	head2->next->next = add(6);
	head2->next->next->next = add(8);
	print(head2);

	print(merge(head1,head2));

}
