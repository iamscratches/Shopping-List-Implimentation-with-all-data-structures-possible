/*COPYRIGHTS ARE ONLY FOR SUBHANKAR BHATTACHARYYA AND WRITTAM MALLICK*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

/*COPYRIGHTS ARE ONLY FOR SUBHANKAR BHATTACHARYYA AND WRITTAM MALLICK*/
//          structure declaration
struct head{
    struct head *next;//next item address
    struct head *prev;//previous item address
    struct prod *add;//address of prod
};
struct prod{
    char p[15];//product
    float c;//cost
};
struct tree{//arranging products according to their name
    struct tree *left;
    struct tree *right;
    struct prod *link;
};
//          variable declaration
int top=-1;
char lseen[100];//to save the last seen product
struct head *strt=NULL;//to save the address of the first product of the cart
struct tree *root=NULL;
//          method declaration
void Push(char *,float );//to store product in the cart and also for sorting the items in a tree form so as to use it in  search operation
void Display();//for displaying elements in the cart
void Search(char *,char );//search for a product and delete the product or display its info accordingly
void Pop();//delete the last element of the stack cart
void Qdelete();//delete the first element from the queue

void Display(){
    if(top==-1){
        printf("\nSry ur cart is empty,nothing to display.please try putting something in  the list first");
        return;
    }
    float total=0.0;
    struct head *q=strt;
    printf("\n\t\t\tHere is ur shopping list so far...");
    printf("\n\t\tITEM NAME\t\tCOST");
    for(int i=0;i<=top;i++){
            total=total+q->add->c;
        printf("\n%24s%24.2f",q->add->p,q->add->c);
        q=q->next;
    }
    printf("\nTotal no.of items=%d\t\tTotal price=$%0.2f",(top+1),total);

return;
}

void Qdelete(){
    if(top==-1){
        printf("\nUr cart is already empty.Try putting somne item in the cart first.");
        return;
    }
    if(top==0){
        strt=NULL;
        printf("\nUr cart is now empty.please try putting some items into it");
        top--;
        return;
    }
    struct head *r=strt;
    strt=r->next;
    strt->prev=NULL;
    top--;

return;
}

void Pop(){
    if(top==-1){
        printf("\nUr cart is already empty.Try putting somne item in the cart first.");
        return;
    }
    if(top==0){
        strt=NULL;
        printf("\nUr cart is now empty.please try putting some items into it");
        top--;
        return;
    }
    struct head *r=strt;
    top--;
    for(int i=0;i<top;i++){
        r=r->next;
    }
    r->next=NULL;
return;
}

void Push(char *item,float value){
    if(top==MAX){
        printf("\nYour shopping cart is full,try to delete some item from ur list");
        return;
    }
    struct head *q=(struct head *)malloc(sizeof(struct head));
    struct tree *t=(struct tree *)malloc(sizeof(struct tree));
    struct prod *w=(struct prod *)malloc(sizeof(struct prod));
    //declaring variable purposes
    q->next=NULL;
    q->add=w;
    w->c=value;
    strcpy(w->p,item);
    t->link=w;
    t->left=NULL;
    t->right=NULL;
    //pushing value at strt
    if(top==-1){
        strt=q;
        q->prev=NULL;
        q->next=NULL;
        q->add=w;
        top++;
        strcpy(w->p,item);
        w->c=value;
        root=t;
        t->link=w;
        t->left=NULL;
        t->right=NULL;
        return;
    }
    //pushing value in stack
    struct head *r=strt;
    for(int i=0;i<top;i++){
        r=r->next;
    }

    q->prev=r;
    r->next=q;
    top++;
    //pushing value in tree
    struct tree *temp=root;
    while(temp!=NULL){
        if(strcmp(temp->link->p,item)<0){
            if(temp->left==NULL){
                temp->left=t;
                break;
            }
            else
                temp=temp->left;
        }
        else{
            if(temp->right==NULL){
                temp->right=t;
                break;
            }
            else
                temp=temp->right;
        }
    }
return;
}

void Search(char *item,char d){//d is used to store the decision of whether to display the item or delete it
    struct tree *temp=root,*a=NULL,*hold;//to store the left and right parent of temp
    int flag;//to indicate whether it is a left or right node....left->0,right->1;
    struct head *temp2=strt,*storage;//to store the previous and next guardian of temp2
    char product[100];
    strcpy(product,item);
    while(temp!=NULL&&strcmp(temp->link->p,product)!=0){
            a=temp;
        if(strcmp(temp->link->p,product)<0){
            temp=temp->left;
            flag=0;//indicates left tree
        }
        else{
            temp=temp->right;
            flag=1;//indicates right tree
        }
    }
    if(d=='s'){
        if(temp!=NULL)
            printf("\nproduct name- %s\t cost- %0.2f",temp->link->p,temp->link->c);
        else
            printf("\nSry ur item doesn't exist in cart.try another search.\n");
    }
    else if(d=='d'){
        //deleting item from stack
        while(temp2!=NULL&&strcmp(temp2->add->p,product)!=0)
            temp2=temp2->next;
        if(top==0&&temp2!=NULL){
            strt=NULL;
            top--;
        }
        else if(temp2!=NULL&&temp2->next!=NULL){
                storage=temp2->next;
                storage->prev=temp2->prev;
                storage=temp2->prev;
                storage->next=temp2->next;
                top--;
            printf("\nUr item has been deleted from cart");
        }
        else if(temp2!=NULL&&temp2->next==NULL){
            storage=temp2->prev;
            storage->next=NULL;
        }
        //deleting element from tree
        if(temp!=NULL){
            if(temp->left==NULL&&temp->right==NULL){
                if(flag==0)
                    a->left=NULL;
                else if(flag==1)
                    a->right=NULL;
                if(strcmp(root->link->p,product)==0)
                    root=a;
            }
            else if(temp->left!=NULL&&temp->right==NULL){
                if(flag==0)
                    a->left=temp->left;
                else if(flag==1)
                    a->right=temp->left;
                if(strcmp(root->link->p,product)==0)
                    root=temp->left;
            }
            else if(temp->left==NULL&&temp->right!=NULL){
                if(flag==0)
                    a->left=temp->right;
                else if(flag==1)
                    a->right=temp->right;
                if(strcmp(root->link->p,product)==0)
                    root=temp->right;
            }
            else if(temp->left!=NULL&&temp->right!=NULL){
                if(temp->right->left==NULL){
                    if(flag==0)
                        a->left=temp->right;
                    else if(flag==1)
                        a->right=temp->right;
                    temp->right->left=temp->left;
                    if(strcmp(root->link->p,product)==0)
                        root=temp->right;
                }
                else{
                    temp=temp->right;
                    hold=temp;
                    while(temp->left->left!=NULL){
                        temp=temp->left;
                    }
                    if(a!=NULL){
                        if(flag==0){
                            temp->left->left=a->left->left;
                            a->left=temp->left;
                        }
                        else if(flag==1){
                            temp->left->left=a->right->left;
                            a->right=temp->left;
                        }
                    }
                    else if(strcmp(root->link->p,product)==0){
                        temp->left->left=root->left;
                        root=temp->left;
                    }
                    temp->left->right=hold;
                    temp->left=temp->left->right;

                }
            }
        }
        else
            printf("\nSry ur item doesn't exist in cart.try another search.\n");

    }
return;
}

int main(){
    char *item=(char *)malloc(sizeof(char));
    float price;
    char choice;
    int i=1;
    printf("\n\t\tWelcome to an amazing software project developed by your's truly.");
    printf("\n\t\t\tPLEASE ENTER EVERYTHING IN CAPS\nEnter what do u want to do-\nA.add product\nD.delete product\nP.pop out last seen\nS.search product\n\C.see cart\nQ.Quit");
    while(choice!='Q'){//menu driven options
        i++;
        if(i%10==0){
            system("cls");
            printf("\n\t\tWelcome to an amazing software project developed by your's truly.");
            printf("\n\t\t\tPLEASE ENTER EVERYTHING IN CAPS\nEnter what do u want to do-\nA.add product\nD.delete product\nP.pop out last seen\nS.search product\n\C.see cart\nQ.Quit");
        }
        printf("\nEnter ur choice- ");
        choice=getche();
        switch(choice){
        case 'A':
            printf("\nEnter product name and cost- ");
            scanf("%s %f",item,&price);
            Push(item,price);
            strcpy(lseen,item);
            break;
        case 'D':
            printf("\n1.delete from last\n2.delete from first\n3.delete a particular product\n");
            choice=getche();
            if(choice=='1')
                Pop();
            else if(choice=='2')
                Qdelete();
            else if(choice=='3'){
                printf("\nEnter product name: ");
                scanf("%s",item);
                Search(item,'d');//to delete a particular product
            }
            break;
        case 'P':
            printf("\n%s is popped out",&lseen);
            Search(lseen,'d');//to delete the last seen item in the list
            break;
        case 'S':
            printf("\nEnter product name: ");
            scanf("%s",item);
            strcpy(lseen,item);
            Search(item,'s');//to search for a particular product's details
            break;
        case 'C':
            Display();
            break;
        case 'Q':
            printf("\n\t\tThanks for using our program!!bye bye!!\n");
            break;
        default:
            printf("\nWrong input!!try again!!\n");
        }
    }
    printf("\n\n\t\t.......copyrights reserved for SUBHANKAR BHATTACHARYYA and WRITTAM MALLICK.......");
    getch();
return 0;
}


/*COPYRIGHTS ARE ONLY FOR SUBHANKAR BHATTACHARYYA AND WRITTAM MALLICK*/

/*
1.LAST SEEN DELETION AND SAVING NOT WORKING PROPERLY
2.DELETION SEARCH IS NOT WORKING PROPERLY
*/


/*
int main(){
    char *temp="hello";
    char temp2[]=temp;
    char *temp3=temp;
    printf("%s %s",temp1,temp2);
    temp="world";
    printf("%s %s",temp1,temp2);
}
int main(){
    char *temp=(char *)malloc(sizeof(char));
    scanf("%s",temp);
    printf("%s",temp);
    return 0;

}
int main()
{
    q=(struct Node*)malloc(sizeof(struct Node));
    s_list[0]=q;
    q->item="hello world";
    printf("%s",s_list[0]->item);
    return 0;
}
category(fashion,
item name
price
specs

void push(char *prod,double price){
    if(top==14)
        printf("sorry!ur shopping list is full\npop out some item from the list to continue");
    else{
        q=(struct Node*)malloc(sizeof(struct Node));
        head=(top==-1)?q:NULL;
        s_list[top]=q;
        q->item=prod;
        q->cost=price;
        q->link=NULL;
        s_list[top-1]->link=q;
        top++;
    }
return;
}
void pop(){
    if(top==-1)
            printf("sorry!ur shopping list is empty\n");
    else
        q=s_list[top];
}
void d_item(char *prod){
    int i;
    int index=search(prod);
    if(index==0){

    }
return;
}
*/
/*COPYRIGHTS ARE ONLY FOR SUBHANKAR BHATTACHARYYA AND WRITTAM MALLICK*/
