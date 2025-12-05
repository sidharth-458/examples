#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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
struct node *rotate(struct node * h, int a){
	struct node * curr = h;
	struct node * oldhead = h;
	struct node * newhead = NULL;
	int len = 1;
	while(curr->next){
		curr = curr->next;
		len++;
	}
	curr->next = oldhead;

	if(a > len)
		a = a%len;
	while(--a)
		curr = curr->next;
	newhead = curr->next;
	curr->next = NULL;
	return newhead;

}

struct node * reverse(struct node * h){
	struct node * curr = h;
	struct node * prev = NULL;
	struct node * next = h->next;

	while(curr){
		next = curr->next;//save next in scratch
		curr->next = prev;//repoint back
		prev = curr;
		curr = next;
	}
	return prev;
}
bool palin(struct node * h){
	struct node * curr = h;
	struct node * mid = h;
	struct node * sechead = NULL;
	//traverse array to mid point
	while(curr->next->next){
		curr = curr->next->next;
		mid = mid->next;
	}
	//split array
	sechead = mid->next;
	mid->next = NULL;

	//reverse second half
	sechead = reverse(sechead);
	curr = h;
	while(curr && sechead){
		if(curr->info != sechead->info)
			return false;
		curr=curr->next;
		sechead= sechead->next;
	}
	return true;

}
struct node * deep_cp_rand(struct node * h){
	
};
int main(){
	struct node * head1 = add(1);
	head1->next= add(3);
	head1->next->next = add(3);
	head1->next->next->next = add(0);
	print(head1);

	struct node * head2 = add(2);
	head2->next= add(4);
	head2->next->next = add(6);
	head2->next->next->next = add(8);
//	print(head2);

	//print(rotate(head1,10));
	
	printf("%d\n",palin(head1));
}
