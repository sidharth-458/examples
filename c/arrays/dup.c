#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
int dup(int * arr, int size){
	int * map = NULL;
	int mapsize = 0;
	int repeats = 0;
	for(int i = 0; i< size;i++){
		bool found = false;
		for(int z = 0; z<mapsize;z++){
			if( arr[i] == map[z]){
				found = true;
			}
		}
		if(!found){
			mapsize++;
			map = reallocarray(map,mapsize, sizeof(int));
			map[mapsize -1] = arr[i];
			int localrepeats = 0;
			for(int j = 0;j<size;j++){
				if(arr[i] == arr[j]){
					localrepeats++;
				}
			}
			if(localrepeats > 1){
				repeats+= localrepeats -1;
			}
		}
	}
	free(map);
	return repeats;
}

int main(){
	int arr[] = {1,2,3,1,2,2,2};
	int sz = sizeof(arr)/sizeof(int);

	printf("dups found are %d\n",dup(arr,sz));
}
