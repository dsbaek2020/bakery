//
//  bread.c
//  bakery_porgram
//
//  Created by 최서영 on 2020/11/03.
//

#include <stdio.h>
//#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "bread.h"
#include "ui.h"
#include "getch.h"




extern int flag;


UI_BUTTON ButtonBuy={
    30,20,
    {{"╭―――――――――――――――――╮"},
     {"│   1. 구매하기   │"},
     {"╰―――――――――――――――――╯"}}
};

UI_BUTTON ButtonSearch={
    30,23,
    {{"╭―――――――――――――――――╮"},
     {"│   2. 검색하기   │"},
     {"╰―――――――――――――――――╯"}}
};

UI_BUTTON ButtonAdd={
    30,26,
    {{"╭―――――――――――――――――╮"},
     {"│   3. 등록하기   │"},
     {"╰―――――――――――――――――╯"}}
};

UI_BUTTON ButtonSummerize={
    30,29,
    {{"╭―――――――――――――――――╮"},
     {"│   4. 정산하기   │"},
     {"╰―――――――――――――――――╯"}}
};

UI_BUTTON AI_mode={
    30,32,
    {{"╭―――――――――――――――――╮"},
     {"│   5. 자동추천   │"},
     {"╰―――――――――――――――――╯"}}
};

UI_BUTTON ButtonExit={
    30,35,
    {{"╭―――――――――――――――――╮"},
        {"│   0. 취소하기   │"},
        {"╰―――――――――――――――――╯"}}
};



UI_INPUT_TEXT InputTextMenu={
    30,35,
    "Enter your number in the box below",
    {{"+-----------------+"},
    {"|                 |"},
    {"+-----------------+"}}
};



int GetMenuNumber(void){
    
    char keyValue;
    int select;
    //do{
    keyValue= getch();
    //printf("key value1: %c\n",keyValue);
    
    
    if(keyValue==0x1b){
        keyValue= getch();
        //printf("key value2: %x\n",keyValue);
        
        
        if(keyValue==0x5b){
            
            keyValue= getch();
            //printf("your selection3: %x, ", keyValue);
            switch(keyValue){
                case 0x41: printf("UP WAS PRESSED\n"); break;
                case 0x42: printf("DOWN WAS PRESSED\n"); break;
                case 0x44: printf("LEFT WAS PRESSED\n"); break;
                case 0x43: printf("RIGHT WAS PRESSED\n"); break;
                    
                    /*case 72: printf("UP WAS PRESSED\n"); break;
                     case 80: printf("DOWN WAS PRESSED\n"); break;
                     case 75: printf("LEFT WAS PRESSED\n"); break;
                     case 77: printf("RIGHT WAS PRESSED\n"); break;*/
            }
        }
    }
    else{
        //printf("key : %c \n", (char)keyValue);
        select = keyValue - '0';
    }
    
    return select;
}





void DataLoad(BREAD_DATA *ptr, char *number, char *name, int price, char *preference,int count){
    strcpy(ptr->number, number);
    strcpy(ptr->name, name);
    ptr->price = price;
    strcpy(ptr->preference, preference);
    ptr->count = count;
}

void ContactMenuByPointer(BREAD_DATA *p){
    printf("%s : %s : %d : %s : %d : %d \n", p->number, p->name,p->price,
           p->preference, p->count, p->kcal);
}

int MainData(BREAD_DATA *ptr, int NumOfpang){

    //clear();
    gotoxy(1,1);
    
    printf(
    "██████╗  █████╗ ██╗  ██╗███████╗██████╗ ██╗   ██╗\n"
    "██╔══██╗██╔══██╗██║ ██╔╝██╔════╝██╔══██╗╚██╗ ██╔╝\n"
    "██████╔╝███████║█████╔╝ █████╗  ██████╔╝ ╚████╔╝\n"
    "██╔══██╗██╔══██║██╔═██╗ ██╔══╝  ██╔══██╗  ╚██╔╝\n"
    "██████╔╝██║  ██║██║  ██╗███████╗██║  ██║   ██║\n"
    "╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝\n"
    );
    
    printf("번호 |  빵이름    |  가격  |   선호도 | 판매량  | 열량\n");
    for(int i=0; i<NumOfpang; i++){
        ContactMenuByPointer(ptr+i);
    }

    
    printf(" ____  _____ ____  _   _  \n");
    printf("|    || ___ |  _ || | | | \n");
    printf("| | | | ____| | | | |_| | \n");
    printf("|_|_|_|_____)_| |_|____/ \n");
    
    showButton(&ButtonBuy);
    showButton(&ButtonSearch);
    showButton(&ButtonAdd);
    showButton(&ButtonSummerize);
    showButton(&AI_mode);
    showButton(&ButtonExit);


    return 0;
}

int addUser(BREAD_DATA AddrInfo[], int i){

    int result;
    char cmd[10];


    char name[20];
    char number[20];
    int price;
    char preference[10];

    printf("빵이름을 입력하세요: ");
    scanf("%s", &name[0] );
    printf("빵번호를 입력하세요: ");
    scanf("%s", &number[0]);
    printf("가격을 입력하세요: ");
    scanf("%d", &price );
    printf("선호도 입력하세요: ");
    scanf("%s", &preference[0]);

    printf("등록을 하시겠습니까? (yes/no) ");
    scanf("%s", &cmd[0]);

    if(  strcmp(cmd, "yes") == 0){

        strcpy(AddrInfo[i].name, name);
        strcpy(AddrInfo[i].number, number);
        strcpy(AddrInfo[i].preference,preference);
        AddrInfo[i].price = price;

        printf("등록되었습니다.\n");
        result = 1;
    }
    else{
        printf("취소 되었습니다. \n");
        result =0;
    }

    return result;
    
}

//int calculate()


int search(BREAD_DATA breads[], char searchMethod, char *breadNumber)
{
    char name[20];
    int i=0;
    if(searchMethod == 'n'){
        printf("빵 입력: ");
        scanf("%s", &name[0]);
        
        while(strcmp(breads[i].name, name) != 0){
            i++;
        }
        printf("__________________________________________\n");
        printf("이름 : %s 번호 : %s  가격 : %d 선호도 : %s 판매량 : %d  \n ",
                breads[i].name,breads[i].number,breads[i].price,breads[i].preference,breads[i].count);
     
        printf("__________________________________________\n");
        
        //3초 동안 검색 결과를 표시함
        sleep(3);
        
    }
    else if(searchMethod == 'b'){
        while(strcmp(breads[i].number, breadNumber) != 0){
            i++;
        }
        
    }
    
    
    return i;

}


int buyBread(BREAD_DATA breads[]){

    char keyValue;
    int result;
    char cmd[10];
    int price=0;
    char number[20];
    int count;
    int dataNumber;
    int i=0;

    
    
    
    UI_OUTLINE outLine={
        1,20,
        {  { "╭―――――――――――――――――――――――――╮"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"╰―――――――――――――――――――――――――╯"}}
    };
    
    UI_INPUT_TEXT InputTextMenu={
        3,22,
        "빵번호를 입력하세요: ",
        {{"+-----------------+"},
         {"|                 |"},
         {"+-----------------+"}}
    };

    
    
    showOutLine(&outLine);
    
    

    while(1){

        //printf("빵번호를 입력하세요: ");
        strcpy(InputTextMenu.text,"빵번호를 입력하세요: ");
        showInputBox(&InputTextMenu);
        
        
        //----for MultiThread--------------------------
        i=0;
        do{
            keyValue= getch();
            if(keyValue !='\n'){
                number[i] =keyValue;
                //goto cursor to input area
                gotoxy((InputTextMenu.x)+1+i,(InputTextMenu.y)+2);
                printf("%c",number[i]);
                i++;
            }
        }while(keyValue !='\n');  //LF (character : \n, Unicode : U+000A, hex : 0x0a): This is simply the '\n'
        number[i] ='\0'; //널문자 추가
        
        
        /*
        flag =1;   // 세마포어
        scanf("%s", &number[0]);   //<--- non-MultiThread--
        //scanf 실행후 (번호입력하고 엔터 입력) getch가 실행되면 getch는 scanf시 엔터키의 값 LF 문자를 읽어옮(scanf후에 입력버퍼에 LF 가 남아 있음
        flag =0;
         */
        
        //printf("몇 개 구매하실건가요: ");
        strcpy(InputTextMenu.text,"몇 개 구매하실건가요: ");
        showInputBox(&InputTextMenu);
        
        //usleep(1000000);  // debug code
        
        
        //----for MultiThread-----------------------------
        i=0;
        keyValue =0;
        do{
            keyValue= getch();
            
            //debug code
            /*flag =1;
            printf("key value1: %x\n",keyValue);
            usleep(5000000);
            flag =0;*/
            
            if(keyValue !='\n'){
                count =keyValue - '0';   // for ascii to int
                //goto cursor to input area
                gotoxy((InputTextMenu.x)+1+i,(InputTextMenu.y)+2);
                printf("%d",count);
                i++;
            }
        }while(keyValue !='\n');  //LF (character : \n, Unicode : U+000A, hex : 0x0a): This is simply the '\n'
        //scanf("%d", &count);  <--- non-MultiThread--

        dataNumber=search(breads, 'b', &number[0]);

        price = price + breads[dataNumber].price * count ;
        breads[dataNumber].count = breads[dataNumber].count + count;
        
        gotoxy(2,35);
        printf("총 %d 원 입니다",price);
/*
        //printf("구매를 마치시겠습니까? (yes/no) ");
        strcpy(InputTextMenu.text,"마치시겠습니까? (yes/no)");
        showInputBox(&InputTextMenu);
        scanf("%s", &cmd[0]);

        if(  strcmp(cmd, "yes") == 0){

         printf("구매가 완료됐습니다. 감사합니다.\n");
         result = 1;
         
           break;
        }
        else{
         //printf("취소 되었습니다. \n");
      // 질문 계속
         result =0;
        }
 */
    }
    return result;
     
 }





int AI_mode_Buy(BREAD_DATA breads[]){
    
    char keyValue;
    int result;
    int totalPrice;
    int totalkcal;
    int maxMoney;
    char strDecValue[10];
    

    int i;
    
    int itemBasket[10];
    int numOfItem;
    int itemNumber;
    
    
    
    
    
    UI_OUTLINE outLine={
        1,20,
        {  { "╭―――――――――――――――――――――――――╮"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"│                         │"},
            {"╰―――――――――――――――――――――――――╯"}}
    };
    
    UI_INPUT_TEXT InputTextMenu={
        3,22,
        "예산을 입력하세요: ",
        {{"+-----------------+"},
         {"|                 |"},
         {"+-----------------+"}}
    };
    
    
    
    showOutLine(&outLine);
    
    
    
    while(1){
        
        strcpy(InputTextMenu.text,"예산을 입력하세요: ");
        showInputBox(&InputTextMenu);
        
        //----for MultiThread--------------------------
        i=0;
        do{
            keyValue= getch();
            if(keyValue !='\n'){
                strDecValue[i] =keyValue;
                //goto cursor to input area
                gotoxy((InputTextMenu.x)+1+i,(InputTextMenu.y)+2);
                printf("%c",strDecValue[i]);
                i++;
            }
        }while(keyValue !='\n');  //LF (character : \n, Unicode : U+000A, hex : 0x0a): This is simply the '\n'
        strDecValue[i] ='\0'; //널문자 추가
        
        maxMoney = atoi(strDecValue);
        
        numOfItem =0;
        itemNumber =0;
        totalPrice=0;
        totalkcal=0;
        while(totalPrice+breads[itemNumber].price < maxMoney){
            
            //아이템 추가
            itemBasket[numOfItem++]=itemNumber;
            
            //총가격 계산
            totalPrice +=breads[itemNumber].price;
            
            //총칼로리 계산
            totalkcal +=breads[itemNumber].kcal;
            
            //판매 수량 업데이트
            breads[itemNumber].count +=1;
            
            itemNumber++;
        }
        
        gotoxy(2,35);
        printf("총 %d 원 입니다.\n",totalPrice);
        printf("그리고 총 %d 칼리로리 입니다.\n",totalkcal);
        
    }
    return result;
    
}
