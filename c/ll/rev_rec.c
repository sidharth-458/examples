#include<stdio.h>
#include<stdlib.h>
struct node{
	int info;
	struct node * next;
};

int takeInp(void){
	int a;
	printf("enter inp\n");
	scanf("%d",&a);
	return a;
}

struct node * add(struct node * hd){
	struct node * cp;
	cp = hd;
	if(!cp){
		cp = malloc(sizeof(*cp));
		cp->next = 0;
		cp->info = takeInp();
		return cp;
	}
	while(cp->next)
		cp = cp->next;
	cp->next = malloc(sizeof(*cp));
	cp->next->next = 0;
	cp->next->info = takeInp();
	return hd;
}

struct node * rev(struct node * head){
	if(!head || !head->next)
		return head;
	//recure build stack and coming back bring back the new head safely
	struct node * new = rev(head->next);
	head->next->next = head;
	head->next= NULL;
	return new;
}


void print(struct node * hd){
	if(!hd){
		perror("empty\n");
		return;
	}
	while(hd){
		printf("%d->",hd->info);
		hd = hd->next;
	}
	printf("NULL\n");
}

void menu(){
	struct node * hd = NULL;
	int inp;
	while(1){
		printf("Enter -1 to exit\n"
			"0 to add\n"
			"1 to reverse\n"
			"2 to print\n");
		scanf("%d",&inp);
		switch(inp){
			case(-1):
				exit(0);
				break;
			case(0):
				hd = add(hd);
				break;
			case(1):
				hd = rev(hd);
				break;
			case(2):
				print(hd);
				break;
			default:
				break;
		}
	}
}
int main(){
	menu();	
}
