# include<stdio.h>
# include<time.h>
# include<string.h>
# include<windows.h>
struct Board
{
    int data;
    char dis;
};
int not_unique_combo(int unique[][2],int n)
{
    int i,j;
    for(i=0;i<=n;i++)
    {
        for(j=i+1;j<=n;j++)
        {
            if(unique[i][0]==unique[j][0]&&unique[i][1]==unique[j][1])
                return 1;
        }
    }
    return 0;
}
int row,col,k=1,i,j,a[1000],b[1000],n,d,c=0,unique[1000][2],m=0;
char dif,name[100];
int opened=0,user_r,user_c;
void set_color(int colour)//setting color of text
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (colour & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
void set_background_color(int BackgroundC)//setting background color
{
     WORD wColor = ((BackgroundC & 0x0F) << 4) + (0 & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
void input()
{
    printf("Enter difficulty level:\nEASY(9x9 board with 10 Mines)\nMEDIUM(16x16 board with 40 Mines)\nHARD(24x24 board with 99 Mines)\nCUSTOM(Number of mines and size of grid will be according to your choice)\nEnter E for EASY, M for MEDIUM, H for HARD and C for Custom:");
    fflush(stdin);
    scanf("%c",&dif);
    while(dif!='E'&&dif!='M'&&dif!='H'&&dif!='C')
    {
        printf("You entered something incorrect. Enter again:");
        scanf("%c",&dif);
    }
    switch(dif)
    {
    case 'E':
        row=col=9;
        n=10;
        break;
    case 'M':
        row=col=16;
        n=40;
        break;
    case 'H':
        row=col=24;
        n=99;
        break;
    case 'C':
        printf("Enter number of rows(greater than or equal to 3):");
        scanf("%d",&row);
        while(row<3)
        {
            printf("Number of rows less than 3. Enter Number of Rows Again:");
            scanf("%d",&row);
        }
        printf("Enter number of columns:(greater than or equal to 3):");
        scanf("%d",&col);
        while(col<3)
        {
            printf("Number of columns less than 3. Enter Number of Column Again:");
            scanf("%d",&col);
        }
        printf("Enter the number of mines(not 0 and not greater than or equal to %d):",row*col);
        scanf("%d",&n);
        while(n==0||n>=row*col)
        {
            printf("Not zero and not greater than %d.Enter number of mines again:",row*col);
            scanf("%d",&n);
        }
        break;
    }
}
void print_during(struct Board board[row][col])
{
    for(i=0;i<=col;i++)
    {
        if(i==0)
        {
            set_background_color(0);
            set_color(15);
            printf("   ");
        }
        else
        {
            set_background_color(0);
            set_color(15);
            if(i<10)
                printf(" %d ",i);
            else if(i<100)
                printf("%d ",i);
            else
                printf("%d",i);
        }
    }
    printf(" \n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(j==0)
            {
                set_background_color(0);
                set_color(15);
                if(i+1<10)
                    printf(" %d ",i+1);
                else if(i+1<100)
                    printf("%d ",i+1);
                else
                    printf("%d",i+1);
            }
            if(board[i][j].dis=='M')
            {
                set_color(1);
                if((i+j)%2==0)
                {
                    set_background_color(2);
                    printf(" X ");
                }
                else
                {
                    set_background_color(1);
                    printf(" X ");
                }
            }
            else if(board[i][j].dis=='0')
            {
                set_background_color(15);
                printf("   ");
            }
            else if(board[i][j].dis=='X')
            {
                set_color(1);
                if((i+j)%2==0)
                {
                    set_background_color(2);
                    printf(" %c ",board[i][j].dis);
                }
                else
                {
                    set_background_color(1);
                    printf(" %c ",board[i][j].dis);
                }
            }
            else if(board[i][j].dis=='F')
            {
                set_background_color(6);
                set_color(0);
                printf(" %c ",board[i][j].dis);
            }
            else
            {
                set_background_color(15);
                if(board[i][j].dis=='1')
                    set_color(8);
                else if(board[i][j].dis=='2')
                    set_color(15);
                else
                    set_color(0);
                printf(" %c ",board[i][j].dis);
            }
            if(j==col-1)
            {
                set_background_color(0);
                printf("e");
            }
        }
        set_background_color(0);
        printf(" \n");
    }
}
void update_surroundings(struct Board board[row][col])
{
    for(i=0;i<n;i++)//updating mine in surroundings
     {
        if(a[i]-1>=0&&(b[i]+1>col||b[i]-1<0))
        {
            board[a[i]-1][b[i]].data+=1;
        }
        if(b[i]-1>=0&&(a[i]+1>row||a[i]-1<0))
        {
            board[a[i]][b[i]-1].data+=1;
        }
        if(a[i]+1<row&&(b[i]+1>col||b[i]-1<0))
        {
            board[a[i]+1][b[i]].data+=1;
        }
        if(b[i]+1<col&&(a[i]+1>row||a[i]-1<0))
        {
            board[a[i]][b[i]+1].data+=1;
        }
        if(a[i]+1<row&&b[i]+1<col)
        {
            board[a[i]+1][b[i]+1].data+=1;
        }
        if(a[i]-1>=0&&b[i]+1<col)
        {
            board[a[i]-1][b[i]+1].data+=1;
        }
        if(b[i]-1>=0&&a[i]+1<row)
        {
            board[a[i]+1][b[i]-1].data+=1;
        }
        if(a[i]-1>=0&&b[i]-1>=0)
        {
            board[a[i]-1][b[i]-1].data+=1;
        }
    }
}
void put_mine(struct Board board[row][col])
{
    srand(time(NULL));//to avoid sequence in random integers
    for(i=0;i<n;i++)
    {
        a[i]=(rand()%(row));//getting random rows and columns through rand()
        b[i]=(rand()%(col));//getting random columns
        unique[i][0]=a[i];
        unique[i][1]=b[i];
        if(i!=0)
            if(not_unique_combo(unique,i))
                    i--;
    }
    for(i=0;i<n;i++)
    {
        board[a[i]][b[i]].dis='M';
    }
    update_surroundings(board);
}
void print_start(struct Board board[row][col])
{
    printf("Board:\n");
    set_color(15);
    for(i=0;i<=col;i++)
    {
        if(i==0)
            printf("   ");
        else
        {
            if(i<10)
                printf(" %d ",i);
            else if(i<100)
                printf("%d ",i);
            else
                printf("%d",i);
        }
    }
    printf("\n");
    set_color(1);
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(j==0)
            {
                set_background_color(0);
                set_color(15);
                if(i+1<10)
                    printf(" %d ",i+1);
                else if(i+1<100)
                    printf("%d ",i+1);
                else
                    printf("%d",i+1);
            }
            if((i+j)%2==0)
            {
                set_color(1);
                set_background_color(2);
                printf(" X ");
            }
            else
            {
                set_color(1);
                set_background_color(1);
                printf(" X ");
            }
            if(j==col-1)
            {
                set_background_color(0);//to make the rest of the line black else it was coming out green/blue
                printf("e");
            }
        }
        printf("\n");
    }
}
void print_last(struct Board board[row][col])
{
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(board[i][j].dis=='M')
            {
                set_background_color(12);
                set_color(30);
                printf(" M ");
            }
            else
            {
                set_color(1);
                if((i+j)%2==0)
                {
                    set_background_color(2);
                    printf(" X ");
                }
                else
                {
                    set_background_color(1);
                    printf(" X ");
                }
            }
            if(j==col-1)
            {
                set_background_color(0);
                printf("e");
            }
        }
        printf(" \n");
    }
}
void open(struct Board board[row][col])//to open nearby cells
{
     board[user_r-1][user_c-1].dis=board[user_r-1][user_c-1].data+'0';
     opened++;
     if(user_r-2>=0&&board[user_r-2][user_c-1].dis!='M'&&board[user_r-2][user_c-1].dis=='X')
     {
        board[user_r-2][user_c-1].dis=board[user_r-2][user_c-1].data+'0';
        opened++;
     }
     if(user_c-2>=0&&board[user_r-1][user_c-2].dis!='M'&&board[user_r-1][user_c-2].dis=='X')
     {
        board[user_r-1][user_c-2].dis=board[user_r-1][user_c-2].data+'0';
        opened++;
     }
     if(user_r<row&&board[user_r][user_c-1].dis!='M'&&board[user_r][user_c-1].dis=='X')
     {
        board[user_r][user_c-1].dis=board[user_r][user_c-1].data+'0';
        opened++;
     }
     if(user_c<col&&board[user_r-1][user_c].dis!='M'&&board[user_r-1][user_c].dis=='X')
     {
        board[user_r-1][user_c].dis=board[user_r-1][user_c].data+'0';
        opened++;
     }
     if(user_r-2>=0&&user_c-2>=0&&board[user_r-2][user_c-2].dis!='M'&&board[user_r-2][user_c-2].dis=='X')
     {
        board[user_r-2][user_c-2].dis=board[user_r-2][user_c-2].data+'0';
        opened++;
     }
     if(user_r-2>=0&&user_c<col&&board[user_r-2][user_c].dis!='M'&&board[user_r-2][user_c].dis=='X')
     {
        board[user_r-2][user_c].dis=board[user_r-2][user_c].data+'0';
        opened++;
     }
     if(user_c-2>=0&&user_r<row&&board[user_r][user_c-2].dis!='M'&&board[user_r][user_c-2].dis=='X')
     {
        board[user_r][user_c-2].dis=board[user_r][user_c-2].data+'0';
        opened++;
     }
     if(user_r<row&&user_c<col&&board[user_r][user_c].dis!='M'&&board[user_r][user_c].dis=='X')
     {
        board[user_r][user_c].dis=board[user_r][user_c].data+'0';
        opened++;
     }
}
int main()
{
    printf("Enter the Player Name:");
    fflush(stdin);
    gets(name);
    char wish[5];
    do{
    input();
    struct Board board[row][col];
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            board[i][j].data=0;
            board[i][j].dis='X';
        }
    }
    set_color(4);
    opened=0;
    put_mine(board);
    system("cls");
    print_start(board);
    set_background_color(0);
    while(opened<row*col-n)
    {
        set_background_color(0);
        set_color(12);
        printf("Enter the co-ordinates in form row number followed by column number[rows between 1 and %d and columns between 1 and %d]:",row,col);
        scanf("%d %d",&user_r,&user_c);
        if(user_r==281&&user_c==127)
        {
            system("cls");
            opened=row*col-n;
            break;
        }
        if(user_r>row||user_c>col)
        {
            printf("Wrong Input.\n");
            continue;
        }
        if(m==0&&board[user_r-1][user_c-1].dis=='M')
        {
            set_color(12);
            printf("This is a mine. Since it's your first turn you can try again.\n");
            continue;
        }
        else
            m++;
        system("cls");//screen clear
        if(board[user_r-1][user_c-1].dis=='M')
            break;
        else//opening the surroundings if bomb not in there
        {
            open(board);
            if(opened==row*col-n)
                break;
            print_during(board);

        }
        int flag=1;
        while(flag!=0)
        {
            set_background_color(0);
            set_color(12);
            printf("If you wish to mark any point press 1 else 0:");
            scanf("%d",&flag);
            if(flag==1)
            {
                int flag_r,flag_c;
                printf("Enter co-ordinates of position you wish to mark:");
                scanf("%d %d",&flag_r,&flag_c);
                board[flag_r-1][flag_c-1].dis='F';
                c++;
                system("cls");
                print_during(board);
            }
        }
        if(c!=0)
        {
            int unflag=1;
            while(unflag!=0&&c!=0)
            {
                set_background_color(0);
                set_color(12);
                printf("If you wish to unmark any point press 1 else 0(Unmark only marked positions):");
                scanf("%d",&unflag);
                if(unflag==1)
                {
                    int unflag_r,unflag_c;
                    printf("Currently Marked Positions are:\n");
                    for(i=0;i<row;i++)
                    {
                        for(j=0;j<col;j++)
                        {
                            if(board[i][j].dis=='F')
                            {
                                printf("%d %d\n",i+1,j+1);
                            }
                        }
                    }
                    printf("Enter co-ordinates of position to be unmarked:");
                    scanf("%d %d",&unflag_r,&unflag_c);
                    board[unflag_r-1][unflag_c-1].dis='X';
                    c--;
                    system("cls");
                    print_during(board);
                }
            }
        }
    }
    printf("Mines are:\n");
    for(i=0;i<n;i++)
    {
        printf("(%d, %d)\n",unique[i][0]+1,unique[i][1]+1);
    }
    if(opened==row*col-n)
        printf("%s won the game.The board was:\n",name);
    else
        printf("%s lost. The board was:\n",name);
    set_background_color(2);
    print_last(board);
    set_background_color(0);
    set_color(15);
    system("pause");
    system("cls");
    printf("If you wish to play more enter START else enter EXIT:");
    fflush(stdin);
    gets(wish);
    }while(strcmp(strupr(wish),"START")==0);
    return 0;
}
