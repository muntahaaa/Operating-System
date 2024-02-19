#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
    int pid,sum=0;
    int arr[]={1,2,3,4,5,6,7,8,9};
    int len = sizeof(arr) / sizeof(arr[0]);
    switch(pid=fork()){
        case 0:{
           for(int i=0;i<len;i++){
            if(arr[i]%2==0)
             sum+=arr[i];
           }   break;
        }
        default:{
                for(int i=0;i<len;i++){
            if(arr[i]%2!=0)
             sum+=arr[i];
           }   break;
        }
    }

    printf("Sum of numbers= %d\n",sum);
   
}