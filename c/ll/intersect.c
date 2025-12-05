#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node{
	struct node * next;
	struct node * prev;
	int info;
};

struct node * add(struct node * curr,bool is_inter,int inf){
	struct node * ret = malloc(sizeof(*ret));
	if(!ret){
		perror("malloc");
		exit(-1);
	}
	ret->next = 0;
	ret->prev = curr;
	if(is_inter)
		scanf("%d",&ret->info);
	else
		ret->info = inf;
	return ret;
}

void print(struct node * h){
	while(h){
		printf("%d->",h->info);
		h = h->next;
	}
	printf("NULL\n");
}
/*
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
					curr = add(curr,true,0);
					cp = curr;
				}
				else{
					curr->next = add(curr->next,true,0);
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
*/
int len(struct node * a){
	int i =1;
	while(a){
		a = a->next;
		i++;
	}
	return i;
}
bool is_intersect(struct node * a, struct node * b){
	bool ret = false;
	struct node * major,*minor;
	
	int lena,lenb,step,i,maxlen;
	lena = len(a);
	lenb = len(b);
	
	major = lena>lenb? a:b;
	minor = major==a?  b:a;
	step = lena>lenb? lena - lenb:lenb - lena;
	i = 1;
	while(i++ < step)
		major = major->next;
	
	while(major && minor){
		if(major == minor){
			ret = true;
			break;
		}
		major = major->next;
		minor = minor -> next;
	}
	return ret;
}
	


int main(){
	//1->2->3->4
	struct node * h1 = add(NULL,false,1);
	h1->next = add(h1->next,false,2);
	h1->next->next = add(h1->next->next,false,3);
	h1->next->next->next = add(h1->next->next->next, false, 4);
	// 1-> 2-> 3-> 4
	//-1->-2->
	struct node * h2 = add(NULL,false,-1);
	h2->next = add(h1->next,false,-2);
//	h2->next->next = h1->next->next;

	printf("is intersect %d\n",is_intersect(h1,h2));
//	menuloop();
}
