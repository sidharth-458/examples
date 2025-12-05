#include<string.h>
#include<stdio.h>
#include<stdlib.h>
char * sum(char *a, char *b){
	int lena = strlen(a);
	int lenb = strlen(b);
	int carry = 0;
	int ia = lena - 1;
	int ib = lenb - 1;
	char * ans = malloc(lena>lenb?lena+1:lenb+1);
	int max = lena>lenb?lena:lenb;
	int ians = 0;
	while(ia>=0 || ib>=0 || carry){
		int dig_a = ia>=0? a[ia] - '0':0;
		int dig_b = ib>=0? b[ib] - '0':0;

		int sum = dig_a + dig_b + carry;
		carry = sum/10;
		sum = sum%10;
		printf("%d %d\n",ians,max);
		ans[ians] = sum +'0';
		
		ians++;
		ia--;
		ib--;
	}

	for(int i = 0; i < ians/2 ;i++){
		char temp = ans[ians - i -1];
		ans[ians - i - 1] = ans[i];
		ans[i] = temp;
	}
	return ans;
}

int main(){
	char arr1[] = "1234";
	char arr2[] = "1";

	char * ans = sum(arr1,arr2);
	printf("ans %s\n",ans);
	free(ans);
}
