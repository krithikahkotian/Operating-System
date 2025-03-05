#include<stdio.h>
#include<conio.h>
int sumofleftdia(int a[][100],int size)
{
    int sum=0;
    for(int i=0;i<size;i++)
    {
        sum+=a[i][i];
    }
    return sum;
}
void sumofcolumnrow(int a[][100],int n,int m){
   for(int i=0;i<m;i++)
   {
       int columnsum=0;
       for(int j=0;j<n;j++)
       {
           columnsum+=a[j][i];
       }
       printf("Sum of column %d is %d\n",i,columnsum);
   }
   printf("\n");
   for(int i=0;i<m;i++)
   {
       int rowsum=0;
       for(int j=0;j<n;j++)
       {
           rowsum+=a[i][j];
       }
       printf("Sum of column %d is %d\n",i,rowsum);
   }
   printf("\n");

}
int countdupl(int a[],int n)
{
    int count;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i]==a[j])
                count++;
        }
    }
    return count;
}
int secondsmallest(int a[],int n)
{
    int first=a[0],second=a[0];
    for(int i=1;i<n;i++)
    {
        if(a[i]<=first)
        {
            second=first;
            first=a[i];
        }
    }
    return second;
}
int secondlargest(int a[],int n)
{
    int first=a[0],second=a[0];
    for(int i=1;i<n;i++)
    {
        if(a[i]>=first)
        {
            second=first;
            first=a[i];
        }
    }
    return second;
}
void delete(int a[],int *n,int pos){
    if(pos>=*n){
        printf("Deletion not posible");
        return;
    }
    printf("Element %d at position %d id deleted",a[pos],pos);
    for(int i=pos;i<*n-1;i++){
        a[i]=a[i+1];
    }
    --*n;
}
void displayoned(int a[],int n)
{
    printf("Elements are\n");
    for(int i=0;i<n;i++){
        printf("%d\t",a[i]);
    }
}
void displaytwod(int a[][100],int row,int col)
{
    printf("Elements are\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }

}
void main(){
    int ar[100],tdar[100][100];
    int row,col,n;
    printf("Enter the size of 1D Array\n");
    scanf("%d",&n);
    printf("Enter the elements\n");
    for(int i=0;i<n;i++){
        scanf("%d",&ar[i]);
    }
    displayoned(ar,n);
    printf("\nEnter the size of row and column of 2D Array\n");
    scanf("%d%d",&row,&col);
    printf("Enter the elements\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d",&tdar[i][j]);
        }
    }
    displaytwod(tdar,row,col);
    printf("1D Array Operation\n");
    int second;
    second=secondsmallest(ar,n);
    printf("Second Smallest element is %d \n",second);
    second =secondlargest(ar,n);
    printf("Second Largest element is %d \n",second);
    int count=countdupl(ar,n);
    printf("Count of Duplicate is %d \n",count);
    int pos;
    printf("Enter the position of the element to be deleted\n");
    scanf("%d",&pos);
    delete(ar,&n,pos);
    printf("\nAfter Deletion\n");
    displayoned(ar,n);
    printf("\n");
    printf("\n2D Array Operation\n");
    int sum;
    sum=sumofleftdia(tdar,row);
    printf("Sum of Diagonal Elements is %d\n",sum);
    sumofcolumnrow(tdar,row,col);

}



