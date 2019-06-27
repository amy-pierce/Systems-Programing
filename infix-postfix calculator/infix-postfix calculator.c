#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 1024

void char_push(char symbol);
char char_pop();
void insert(char ch);
void displaypost(char postfix[]);
float postfixOperation(char postfix[]);
int precedence(char ch);
void intopost(char infix[],char postfix[]);
int main();
float pop();
void push(float symbol);

struct node{
char data;
struct node *next;
} *top=NULL,*temp_top=NULL ;

struct num_node{
float data;
struct num_node *next;
} *num_top=NULL;


void push (float item)
{

    struct num_node *temp;
    temp=(struct num_node *)malloc(sizeof(struct num_node));
    temp->data=item;
    if(num_top==NULL)
    {
     num_top=temp;
     temp->next=NULL;

    }
    else
    {

    temp->next=num_top;
    num_top=temp;

    }
}

float  pop()
{
struct num_node *temp;
float value;
if(num_top==NULL)
{
    printf("stack underflow\n");
    return 0;
}
else
{
temp=num_top;
num_top=num_top->next;
value=temp->data;
free(temp);
temp=NULL;
return value;
}
}



float postfixOperation(char postfix[]){
    int count,negative,finished;
    float myInt,x,y,tot;int i;
    for ( i=0;i<=strlen(postfix)&&postfix[i]!='\0';i++){
            switch(postfix[i]){
case '+':
    x=pop();
    y=pop();
    tot=x+y;
    push(tot);
    break;
case '-':
    if(postfix[i+1]>='0'&& postfix[i+1]<='9'){
    negative=1;
    break;
    }
    x=pop();
    y=pop();
    tot=y-x;
    push(tot);
    break;
case '*':
    x=pop();
    y=pop();
    tot=x*y;
    push(tot);
    break;
case 'X':
    x=pop();
    y=pop();
    tot=x*y;
    push(tot);
case '/':
    x=pop();
    y=pop();
    tot=y/x;
    push(tot);
    break;
case '^':
    x=pop();
    y=pop();
    tot=pow(y,x);
    push(tot);
    break;
case ' ':
    break;
default:
   finished=1;
   count=1;
   while(finished==1){
    if(postfix[i+count]==' '){
            char temp[count+1];int x;
            for( x=0;x<=count;x++){
                 temp[x]=postfix[i+x];
            }
            temp[count+1]='\0';
            myInt=atof(temp);
            if(negative==1){
                myInt*=-1;
                negative=0;
            }
            finished=0;
            i=i+(count-1);
            push(myInt);
    break;
    }
    else{
        count++;
    }
   }
   }
    }
    return tot;
}

void insert(char ch)
{
struct node *current,*temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->next=NULL;
    temp->data=ch;
    current=temp_top;
    if(temp_top==NULL){
    temp_top=temp;
    }
    else{
    while(current->next!=NULL)
    current=current->next;
    current->next=temp;
    }
}
void char_push (char item)
{
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->data=item;
    if(top==NULL){
     top=temp;
     temp->next=NULL;
    }
    else{
    temp->next=top;
    top=temp;
    }
}

char char_pop(){
struct node *temp;
char ch;
if(top==NULL){

   printf("stack empty\n");
    return 0;
}
else{

temp=top;
top=top->next;
ch=temp->data;
free(temp);
temp=NULL;
return ch;
}
}
void displaypost(char postfix[])
{
    int i=0;
    struct node *temp;
    if(temp_top==NULL)
    printf("null");
    else{
    temp=temp_top;
    while(temp!=NULL)
    {
        postfix[i]=temp->data;
        i++;
        temp=temp->next;
    }
    }
}



int precedence(char ch){
if(ch=='^')
return (3);
else if(ch=='*' || ch=='X'|| ch== '/')
return (2);
else if (ch== '+' || ch== '-')
return (1);
else
return (0);
}



void intopost(char infix[], char postfix[]){
    int index=0;
    char item,temp;
    while(strlen(infix)>index){
        item=infix[index];
        switch(item){
        case '(':
       char_push(item);
        break;
        case'.':
        insert(item);
        break;
        case ')':
        temp=char_pop();
        while(temp!='(')
        {
        insert(' ');
        insert(temp);
        temp=char_pop();
        }
        break;
        case '^':
        case '+':
        case '-':
        case '*':
        case 'X':
        case '/':
        if(top==NULL)
        {
           char_push(item);
        }
        else{
        
        while(top!=NULL && (precedence(top->data)>=precedence(item)))
        {
            temp=char_pop();
            insert(temp);
        }
        char_push(item);
        }
        break;
        default:
        insert(item);
    }
    index=index+1;
}

    while(top!=NULL){
              temp=char_pop();
    insert(temp);
    }
    displaypost(postfix);
    return;
}
int main(int argc, char ** argv){
char *filename;
if(argc==1){
    printf("Error: No input filename provided\n");
    printf("Usage: %s <input filename>\n", argv[0]);
    exit(1);
}
else if(argc>2){
    printf("Error: Too many command line parameters\n");
    printf("Usage:%s <input filename>\n", argv[0]);
    exit(1);
}
else{
    filename=argv[1];
}

char postfix[MAX];
char infix[MAX];
FILE *file, *results;
int flag,start,start2;
file=fopen(filename,"r");
strcat(filename,".results");
results=fopen(filename,"w");
const size_t line_size=MAX;
char* line=malloc(line_size);
while(fgets(line,line_size,file)!=NULL){
    flag=0;
    if (line[0]=='i'){
        flag=1;
        start=5;start2=1;
        infix[0]='(';
    }
    else{
        start=7;
        start2=0;
}
int i,j;
    for( i=start,j=start2;i<strlen(line);i++,j++){
            if(line[i]=='\n'){
                if(line[0]=='i'){
                    infix[j]=')';
                    j++;
                }
                infix[j]='\0';

        }
        else{
            infix[j]=line[i];
        }
     } 
    if(flag==1){
        intopost(infix,postfix);
        fseek(results,0,SEEK_END);
        fprintf(results,"%s%.2f\n\n",line,postfixOperation(postfix));
        top=NULL;
        num_top=NULL;
        flag=0;
    }
    else{
        fseek(results,0,SEEK_END);
        fprintf(results,"%s%.2f\n\n",line,postfixOperation(infix));
        top=NULL;
        num_top=NULL; 
   }
}
return 0;
}


