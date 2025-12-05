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
struct node * rev(struct node * h){
	struct node * curr = h, *prev =NULL,*next;
	while(curr){
		next = curr->next;//save
		curr->next = prev;//assign reverse
		prev = curr;//traverse 
		curr = next;
	}
	return prev;
}
void is_palin(struct node * h){
	struct node *fast,*slow;
	
	int i = 0;
	fast = h;
	slow = h;
	while(fast){
		fast = fast->next;
		if(fast)
			fast = fast->next;
		else
			break;
		slow = slow->next;
		i++;
	}
	printf("mid %d\n",i);
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

	print(rev(head1));
}
