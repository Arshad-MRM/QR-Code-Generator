#include <stdio.h>
#include<string.h>
#include<ctype.h>

int change_r(int r);    //CHANGING HASHED STRING POSITION FOR SMALL QR
int change_i(int i,int w);  //CHANGING ROW POSITION IF NEEDED FOR SMALL QR
int change_j(int i,int j);  //CHANGING COLOUM POSITION IF NEEDED FOR SMALL QR
int change_r_big(int r);     //CHANGING HASHED STRING POSITION FOR BIG QR
int change_i_big(int i,int j);  //CHANGING ROW POSITION IF NEEDED FOR BIG QR
int change_j_big(int i,int j);   //CHANGING COLOUM POSITION IF NEEDED FOR BIG QR
void moveup(int row);       //MOVEUP CURSER
void movedown(int row);     //MOVEDOWN CURSER
void moveright(int x);      //MOVERIGHT CURSER
void moveleft(int row);     //MOVELEFT CURSER
void moveto(int row,int col); //MOVING CURSER SPECIFIED POSITION
void clear_screen(void);     //CLEAR THE SCREEN
void con_box(int x,int y,int color);  //PRINTING THE UNCHANGED CORNER BOX IN SPECIFIED POINT(x,y)
void border(int x,int y, int z);    //PRINTING THE BORDER (FOR SMALL Z=0, FOR BIG Z=1)
void printing(int c,int d,unsigned char w,int color); //PRINTING MINI 9 BOX QR AT SPECIFIED POINT

int main(int argc, char **argv){
    char word[119];             //INPUT URL
    unsigned char arr1[133];    //HASHED STRING
    int i,j,n,r=16,h,s,e=0,l,g,z,x;
    char temp;
    int color=40;   //COLOR VALUE

    int v;
    if(argc==3){     //CHANGING TO LOWER LETTER THE ARGUMENT COLOR
        for(v=0;v<=strlen(argv[2]);v++){
            if(argv[2][v]>=65 && argv[2][v]<=90){
                argv[2][v]=argv[2][v]+32;
            }
        }
    }

    if( argc>3 || (argc==2 && strcmp(argv[1],"-h")!=0 ) || (argc==3 && strcmp(argv[1],"-c")!=0) ){  //CHECK WHETHWR ITS CORRECT ARGUMENT
        printf("Incorrect usage of arguments.\n");
        printf("usage :\n");
        printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
        printf("%s -h for the help about the program\n",argv[0]);
    }else if( (argc==2 && strcmp(argv[1],"-h")==0) ){           //PRINTING USAGE
        printf("usage :\n");
        printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
        printf("%s -h for the help about the program\n",argv[0]);
    }else if( argc==3 && (strcmp(argv[2],"black")!=0 && strcmp(argv[2],"red")!=0 && strcmp(argv[2],"green")!=0 && strcmp(argv[2],"yellow")!=0 && strcmp(argv[2],"blue")!=0 && strcmp(argv[2],"magenta")!=0 && strcmp(argv[2],"cyan")!=0)){
        printf("Invalid argument for color.\n");                //PRINTING IF COLOR IS INVALID
        printf("usage :\n");
        printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
        printf("%s -h for the help about the program\n",argv[0]);
    }else if(argc==1 || (argc==3 && strcmp(argv[1],"-c")==0 &&(strcmp(argv[2],"black")==0 || strcmp(argv[2],"red")==0 || strcmp(argv[2],"green")==0 || strcmp(argv[2],"yellow")==0 || strcmp(argv[2],"blue")==0 || strcmp(argv[2],"magenta")==0 || strcmp(argv[2],"cyan")==0)) ) {
            if(strcmp(argv[2],"black")==0)             //CHANGE COLOR CODE IF ARGUMENT IS VALID
                color=40;
            else if(strcmp(argv[2],"red")==0)        //CHANGE COLOR CODE IF ARGUMENT IS VALID
                color=41;                            //COLOR CODE CHANGE
            else if(strcmp(argv[2],"green")==0)      //CHANGE COLOR CODE IF ARGUMENT IS VALID
                color=42;                            //COLOR CODE CHANGE
            else if(strcmp(argv[2],"yellow")==0)     //CHANGE COLOR CODE IF ARGUMENT IS VALID
                color=43;                            //COLOR CODE CHANGE
            else if(strcmp(argv[2],"blue")==0)       //CHANGE COLOR CODE IF ARGUMENT IS VALID
               color=44;                             //COLOR CODE CHANGE
            else if(strcmp(argv[2],"magenta")==0)    //CHANGE COLOR CODE IF ARGUMENT IS VALID
                color=45;                            //COLOR CODE CHANGE
            else if(strcmp(argv[2],"cyan")==0)       //CHANGE COLOR CODE IF ARGUMENT IS VALID
                color=46;                            //COLOR CODE CHANGE

            printf("Enter the URL: ");      //PRINTING "Enter the URL: "
            scanf("%s",word);               //SCANNING URL

            if(strlen(word)<=3)            //DECIDE WHETHER STRING IS TOO SHORT
                printf("String is too short. Not supported by available QR versions\n");    //PRINTING IF STRING IS TOO SHORT
            else if(strlen(word)>=120)     //DECIDE WHETHER STRING IS TOO LONG
                printf("String is too long. Not supported by available QR versions\n");     //PRINTING IF STRING IS TOO LONG
            else{                          //DECIDE WHETHER STRING IS CORRECT
                n=strlen(word);         //DECIDE WHETHER STRING IS TOO SHORT

                if(n>3 && n<=20){               //CHECK WHETHER QR IS SMALL QR
                    arr1[0]=50+n;               //1ST CHARACTER OF ASKI VALUE
                    for(s=1;s<24;s++){              //assigning hashed string 24
                        arr1[s]=word[e];
                        e++;
                        if(e==n){         //CHECK WANTS TO ADD PLUS ONE TO URL STRING FOR REMAINING HASHED STRING CHARACTER
                            e=0;
                            for(l=0;l<n;l++){       //MAKING ANOTHER LOOP BY ADDING 1 TO EACH CHARACTER
                                word[l]=word[l]+1;  //ADD PLUS ONE TO URL STRING
                            }
                        }
                    }
                    arr1[24]='\0';                      //END OF HASHED STRING OF SMALL QR BY ASSIGNING "\0"
                    g=(23-n)/2;                 //CHECK HOW MANY CHARACTERS WANT TO SWAPE
                    x=23;                       //HASHED LAST CHARACTER'S POSITION IS 23 FOR SMALL QR
                    for(z=n+1;z<n+g+1;z++){             //REVERSE THE HASHED STRING BY SWAPPING
                        temp=arr1[z];           //ASSIGNING THE 1ST REAL CHARACTER TO VARIABLE
                        arr1[z]=arr1[x];        //SWAPPING THE CHARACTER
                        arr1[x]=temp;           //ASSIGNING THE LAST REAL CHARACTER FROM VARIABLE
                        x--;               //ADD MINUS 1 X
                    }
                    arr1[24]='\0';              //END OF HASHED STRING OF SMALL QR BY ASSIGNING "\0"
                }else if(n>20 && n<120){                //start of hashed 132 characters string
                    arr1[0]=50+n;                       //1st character of hashed 132 string
                    for(s=1;s<132;s++){                 //assigning hashed string 132
                    arr1[s]=word[e];
                    e++;
                        if(e==n){    //CHECK WANTS TO ADD PLUS ONE TO URL STRING FOR REMAINING HASHED STRING CHARACTER
                            e=0;
                            for(l=0;l<n;l++){
                                word[l]=word[l]+1;  //ADD PLUS ONE TO URL STRING
                            }
                        }
                    }
                    arr1[132]='\0';         //last value of hashed 132 string
                    g=(131-n)/2;            //CHECK HOW MANY CHARACTERS WANT TO SWAPE IN BIG QR
                    int xx;
                    xx=131;
                    for(z=n+1;z<n+g+1;z++){ //REVERSE THE HASHED STRING BY SWAPPING
                        temp=arr1[z];       //ASSIGNING THE 1ST REAL CHARACTER TO VARIABLE
                        arr1[z]=arr1[xx];   //SWAPPING THE CHARACTER
                        arr1[xx]=temp;      //ASSIGNING THE LAST REAL CHARACTER FROM VARIABLE
                        xx--;               //ADD MINUS 1 TO XX
                    }
                    arr1[132]='\0';                      //hashed 132 string finished
                }
                if(n>3 && n<=20){               //CHECK WHETHER PRINT QR SMALL
                    clear_screen();             //CLEAR THE SCREEN
                    moveto(1,1);                //MOVE TO START POINT OF CLER SCREEN
                    border(1,1,0);              //WHITE BORDER FOR SMALL QR
                    con_box(2,3,color);         //1ST CORNER BOX
                    con_box(2,27,color);        //2ND CORNER BOX
                    con_box(14,3,color);        //3RD CORNER BOX

                    for(i=1;i<17;i=i+3){                    // PRINTING THE MINI 9 BOX QR FOR EACH CHARACTER
                        for(j=2;j<35;j=j+6){
                            h=i;                            //MAKES h EQALS TO i
                            i=change_i(i,j);                //CHANGING POSITION i
                            j=change_j(h,j);                //CHANGING POSITION j
                            printing(i,j,arr1[r],color);    //PRINTING MINI 9 BOX QR
                            r++;                            //ADD VALUE 1 TO r
                            r=change_r(r);                 //CHANGING POSITION r
                            h=i;
                        }
                    }
                    moveto(22,1);   //FOR SMALL QR ENDS UP
                }
                else if(n>20 && n<120){         //CHECK WHETHER BIG QR PRINTING
                    r=100;                      //big QR start from 100th letter
                    clear_screen();             //CLEAR THE SCREEN
                    moveto(1,1);                //MOVE TO START POINT OF CLER SCREEN
                    border(1,1,1);              //WHITE BORDER FOR BIG QR
                    con_box(2,3,color);         //1ST CORNER BOX
                    con_box(2,63,color);        //2ND CORNER BOX
                    con_box(32,3,color);        //3RD CORNER BOX

                    for(i=1;i<35;i=i+3){                   // PRINTING THE MINI 9 BOX QR FOR EACH CHARACTER
                        for(j=2;j<70;j=j+6){
                            h=i;                            //MAKES h EQALS TO i
                            i=change_i_big(i,j);                //CHANGING POSITION j
                            j=change_j_big(h,j);                //CHANGING POSITION r
                            printing(i,j,arr1[r],color);        //PRINTING MINI 9 BOX QR
                            r++;                                //ADD VALUE 1 TO r
                            r=change_r_big(r);                 //CHANGING POSITION r
                            h=i;
                        }
                    }
                    moveto(40,1);   //FOR BIG QR ENDS UP
                }
            }
        }
    return 0;
}
int change_r(int r){         //CHANGING HASHED STRING POSITION FOR SMALL QR
    if(r==22)       //CHANGE HASHED POSITION
        r=0;
    else if(r==4)   //CHANGE HASHED POSITION
        r=22;
    else if(r==24)  //CHANGE HASHED POSITION
        r=4;
    return r;   //RETURN NEW r
}
int change_i(int i,int w){  //CHANGING ROW POSITION IF NEEDED FOR SMALL QR
    if(i==1 && w==26){           //CHANGE NEW ROW POSITION i
        i=4;
        w=14;
    }else if(i==1 && w==2){     //CHANGE NEW ROW POSITION i
        w=14;
    }else if(i==4 && w==26){    //CHANGE NEW ROW POSITION i
        i=7;
        w=2;
    }else if(i==13 && w==2){    //CHANGE NEW ROW POSITION i
        w=14;
    }else if(i==16 && w==2){    //CHANGE NEW ROW POSITION i
        w=14;
    }else{
        i=i;
        w=w;
    }
return i;       //RETURN NEW i
}
int change_j(int i,int j){  //CHANGING COLOUM POSITION IF NEEDED FOR SMALL QR
    if(i==1 && j==26){           //CHANGE NEW COLOUMN POSITION j
        j=14;
    }else if(i==1 && j==2){      //CHANGE NEW COLOUMN POSITION j
        j=14;
    }else if(i==4 && j==26){     //CHANGE NEW COLOUMN POSITION j
        i=7;
        j=2;
    }else if(i==13 && j==2){     //CHANGE NEW COLOUMN POSITION j
        j=14;
    }else if(i==16 && j==2){     //CHANGE NEW COLOUMN POSITION j
        j=14;
    }
return j;       //RETURN NEW j
}
int change_r_big(int r){    //CHANGING HASHED STRING POSITION FOR BIG QR
    if(r==118)
        r=0;
    else if(r==10)
        r=118;
    else if(r==120)
        r=10;
    else if(r==20)
        r=120;
    else if(r==122)
        r=20;
    else if(r==30)
        r=122;
    else if(r==124)
        r=30;
    else if(r==40)
        r=124;
    else if(r==126)
        r=40;
    else if(r==50)
        r=126;
    else if(r==128)
        r=50;
    else if(r==60)
        r=128;
    else if(r==130)
        r=60;
    else if(r==70)
        r=130;
    else if(r==132)
        r=70;

return r;
}
int change_i_big(int i,int j){  //CHANGING ROW POSITION IF NEEDED FOR BIG QR
    if(i==1 && j==2){                     //change i,j   for big qr
        i=1;
        j=14;
    }else if(i==1 && j==62){
        i=4;
        j=14;
    }else if(i==4 && j==62){
        i=7;
        j=2;
    }else if(i==31 && j==2){
        i=31;
        j=14;
    }else if(i==34 && j==2){
        i=34;
        j=14;
    }else{
        i=i;
        j=j;
    }
return i;
}
int change_j_big(int i,int j){  //CHANGING COLOUM POSITION IF NEEDED FOR BIG QR
    if(i==1 && j==2){                     //change i,j   for big qr
        i=1;
        j=14;
    }else if(i==1 && j==62){
        i=4;
        j=14;
    }else if(i==4 && j==62){
        i=7;
        j=2;
    }else if(i==31 && j==2){
        i=31;
        j=14;
    }else if(i==34 && j==2){
        i=34;
        j=14;
    }else{
        i=i;
        j=j;
    }
return j;
}
void moveup(int row){       //MOVEUP CURSER
    printf("\x1b[%dA",row);
}
void movedown(int row){     //MOVEDOWN CURSER
    printf("\x1b[%dB",row);
}
void moveright(int x){      //MOVERIGHT CURSER
    printf("\x1b[%dC",x);
}
void moveleft(int row){     //MOVELEFT CURSER
    printf("\x1b[%dD",row);
}
void moveto(int row,int col){   //MOVING CURSER SPECIFIED POSITION
    printf("\x1b[%d;%df",row,col);
}
void clear_screen(void){    //CLEAR THE SCREEN
    printf("\x1b[2J");
}
void con_box(int x,int y,int color){    //PRINTING THE UNCHANGED CORNER BOX IN SPECIFIED POINT(x,y)
    moveto(x,y);
    int i;
    for(i=0;i<12;i++){     //1SR ROW
        printf("\x1b[%im \x1b[0m",color);
    }
    movedown(1);         //MOVE 1 DOWN
    moveleft(12);       //MOVE 12 LEFT
    for(i=0;i<12;i++){   //2ND ROW
        if(i==0 || i==1 || i==10 || i==11){
            printf("\x1b[%im \x1b[0m",color);
        }else{
            printf("\x1b[47m \x1b[0m");
        }
    }
    movedown(1);         //MOVE 1 DOWN
    moveleft(12);       //MOVE 12 LEFT
    for(i=0;i<12;i++){   //3RD ROW
        if(i==2 || i==3 || i==8 || i==9){
            printf("\x1b[47m \x1b[0m");
        }else{
            printf("\x1b[%im \x1b[0m",color);
        }
    }
    movedown(1);         //MOVE 1 DOWN
    moveleft(12);       //MOVE 12 LEFT
    for(i=0;i<12;i++){   //4TH ROW
        if(i==2 || i==3 || i==8 || i==9){
            printf("\x1b[47m \x1b[0m");
        }else{
            printf("\x1b[%im \x1b[0m",color);
        }
    }
    movedown(1);         //MOVE 1 DOWN
    moveleft(12);       //MOVE 12 LEFT
    for(i=0;i<12;i++){   //5TH ROW
        if(i==0 || i==1 || i==10 || i==11){
            printf("\x1b[%im \x1b[0m",color);
        }else{
            printf("\x1b[47m \x1b[0m");
        }
    }
    movedown(1);         //MOVE 1 DOWN
    moveleft(12);       //MOVE 12 LEFT
    for(i=0;i<12;i++){    //6TH ROW
        printf("\x1b[%im \x1b[0m",color);
    }
}
void border(int x,int y, int z){    //PRINTING THE BORDER (FOR SMALL Z=0, FOR BIG Z=1)
    moveto(x,y);
    int i,j;
    if(z==0){       //Z=0 FOR SMALL QR BORDER
        for(i=0;i<20;i++){      //PRINTING SMALL BORDER
            for(j=0;j<40;j++){
            if(i==0 || i==19 || j==0 || j==1 || j==38 || j==39){
                printf("\x1b[47m \x1b[0m");
            }else{
                printf("\x1b[40m \x1b[0m");
            }
            }
            printf("\n");
        }
     }else if(z==1){        //Z=1 FOR BIG QR BORDER
         for(i=0;i<38;i++){ //PRINTING BIG BORDER
            for(j=0;j<76;j++){
                if(i==0 || i==37 || j==0 || j==1 || j==74 || j==75){
                    printf("\x1b[47m \x1b[0m");
                }else{
                    printf("\x1b[40m \x1b[0m");
                }
            }
            printf("\n");
        }
     }
}
void printing(int c,int d,unsigned char w,int color){   //PRINTING MINI 9 BOX QR AT SPECIFIED POINT
    int a,i,b=0;
    int m[9];        //BINARY ARRAY
    for(i=8;i>=0;i--){   //BINARY CONVERTING
        a=w/2;
        m[i]=w%2;
        w=a;
    }
    moveto(c+1,d+1);       //MOVE TO SPECIFIED POSITION
    for(i=0;i<3;i++){      //1 ROW PRINTING
        if(m[b]==1)        //CHECK BINARY IS 1 OR NOT
            printf("\x1b[%im  \x1b[0m",color);
        else                //CHECK BINARY IS 0 OR NOT
            printf("\x1b[47m  \x1b[0m");
        b++;
    }
    movedown(1);          //MOVE DOWN 1
    moveleft(6);          //MOVELEFT6
    for(i=0;i<3;i++){     //2ND ROW PRINTING
        if(m[b]==1)
            printf("\x1b[%im  \x1b[0m",color);
        else
            printf("\x1b[47m  \x1b[0m");
        b++;
    }
    movedown(1);         //MOVE DOWN 1
    moveleft(6);         //MOVELEFT6
    for(i=0;i<3;i++){    //3RD ROW PRINTING
        if(m[b]==1)
            printf("\x1b[%im  \x1b[0m",color);
        else
            printf("\x1b[47m  \x1b[0m");
        b++;
    }
}
