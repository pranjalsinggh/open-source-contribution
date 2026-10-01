
#include <stdio.h>
#define maxsize 10

int stack[maxsize], top = -1;

void push();
void pop();
void display();

static int read_integer(int *value)
{
    int result = scanf("%d", value);
    int character;

    while ((character = getchar()) != '\n' && character != EOF)
    {
    }

    return result == 1;
}

int main()
{
    int choice;
    
    do
    {
        printf("\n----stack----\n");
        printf("Press 1 for push\n");
        printf("Press 2 for pop\n");
        printf("Press 3 for display\n");
        printf("Press 4 for exit\n");
        printf("enter your choice: ");
        if (!read_integer(&choice))
        {
            if (feof(stdin))
            {
                break;
            }

            printf("Invalid choice\n");
            continue;
        }
        
        switch(choice)
        {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: display(); break;
            case 4: break;
            default: printf("Invalid choice\n");
        }
    }while(choice!=4);

    return 0;
}

void push()
{
    int value;

    if(top == maxsize - 1 )
    {
        printf("stack is overflow");
    }
    else
    {
        printf("enter value: ");
        if (!read_integer(&value))
        {
            printf("Invalid value\n");
            return;
        }

        stack[++top] = value;
    }
}
void pop()
{
    if(top == -1){
        printf("stack is empty");
    }
    else
    {
        printf("deleted item %d",stack[top]);
        top--;
    }
}
void display()
{
    if (top == -1)
    {
        printf("stack is empty");
    }
    else
    {
        for(int i =0; i<=top; i++)
        {
            printf("%d\t",stack[i]);
        }
    }
}
