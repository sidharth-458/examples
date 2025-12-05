#include<stdio.h>
#include<stdlib.h>

struct node{
	struct node * next;
	int info;
};

int menu(){
	int ch;
	printf(	"1.insert at beginning\n"
		"2.delete at beginning\n"
		"3.print\n"
		"4.middle\n"
		"5.reversal\n"
		"6.exit\n");
	scanf("%d",&ch);
	return ch;
}

struct node * insert(struct node *n){
	if(!n){
		n = malloc(sizeof(struct node));
		n->next = 0;
		printf("enter info\n");
		scanf("%d",&n->info);
	}
	else{
		struct node * cp = n;
		n = malloc(sizeof(struct node));
		n -> next = cp;
		printf("enter info\n");
		scanf("%d",&n->info);
	}
	return n;
}
struct node * delete(struct node *n){
	if(!n){
		printf("list is empty\n");
		return n;
	}
	struct node * cp = n->next;
	free(n);
	return cp;
}
struct node* print(struct node *n){
	struct node * cp = n;
	while(n){
		printf("%d->",n->info);
		n = n->next;
	}
	printf("NULL\n");
	return cp;

}
struct node* middle(struct node *n){
	struct node * f = n, *s = n;
	int i =0, j = 0;
	while(f->next){
		i++;
		f = f->next;
		for(j; j<i/2;j++){
			s = s->next;
		}
	}
	printf("middle is %d\n",s->info);
	return n;
}
struct node * reversal(struct node *n){
	struct node * hd, * temp, * temp2;
	if(!n || !n->next)
		return n;
	hd = n;
	temp = NULL;
	while(hd){
		temp2 = hd->next;
		hd->next = temp;
		temp = hd;
		hd = temp2;
	}
	return temp;

}
struct node * new_exit(struct node *n){
	exit(0);
	return n;
}
struct node * (*fp[])(struct node *) = {insert,delete,print,middle,reversal,new_exit};

int main(){
	struct node * n =NULL;
	for(;;){
		n = fp[menu() - 1](n);
	}
}
