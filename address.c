#include<stdio.h>
int main()
{
    int i,arr[100],n,*p1=&arr;
    printf("enter number of elements you want to enter in array");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",arr[i])
    }
    for(i=0;i<n;i++)
    {
        printf("address of %d[i]is%u\n",p1)
    }

}
