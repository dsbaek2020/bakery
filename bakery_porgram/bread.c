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


typedef enum{
	STRING = 1,
	INTEGER
}dataformat_t;
//#define STRING_TYPE	"%s"
//#define INT_TYPE		"%d"
//const char *StingType = "%s";
//const char *IntegerType = "%d";

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

//----MultiThread type scanf  ------------------
void InputTextBox(UI_INPUT_TEXT *textBox, char string[]){

	int i;
	char keyValue;

	i=0;
	do{
		keyValue= getch();
		if(keyValue !='\n'){
			string[i] =keyValue;
			//goto cursor to input area
			gotoxy((textBox->x)+1+i,(textBox->y)+2);
			printf("%c",string[i]);
			i++;
		}
	}while(keyValue !='\n');  //LF (character : \n, Unicode : U+000A, hex : 0x0a): This is simply the '\n'
	string[i] ='\0'; //널문자 추가

}



//----MultiThread type scanf  ------------------
/*void InputNumberBox(UI_INPUT_TEXT *numberInputBox, int *num){

	int i;
	char keyValue;

	i=0;
	do{
		keyValue= getch();

		if(keyValue !='\n'){
			*num =(keyValue - '0');
			//goto cursor to input area
			gotoxy((numberInputBox->x)+1+i,(numberInputBox->y)+2);
			printf("%d",*num);
			i++;
		}
	}while(keyValue !='\n');  //LF (character : \n, Unicode : U+000A, hex : 0x0a): This is simply the '\n'
}*/



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

void DiplayData(BREAD_DATA *p){
    printf("%s : %s : %d : %s : %d : %d \n", p->number, p->name,p->price,
           p->preference, p->count, p->kcal);
}

int DisplayMainPanel(BREAD_DATA *ptr, int NumOfpang){

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
    	DiplayData(ptr+i);
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

int addNewBread(BREAD_DATA AddrInfo[], int i){

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


void buyBread(BREAD_DATA breads[]){
    
	char string[20];
	char breadNumber[20];
	int price=0;
	int count;
	int dataNumber;
    
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
		InputTextBox(&InputTextMenu, breadNumber);


		//printf("몇 개 구매하실건가요: ");
		strcpy(InputTextMenu.text,"몇 개 구매하실건가요: ");
		showInputBox(&InputTextMenu);


		//----for MultiThread--------------------------
		InputTextBox(&InputTextMenu, string);
		count = atoi(string);
		//scanf("%d", &count);  <--- non-MultiThread--

		// search from database
		dataNumber=search(breads, 'b', &breadNumber[0]);

		// update database
		price = price + breads[dataNumber].price * count ;
		breads[dataNumber].count = breads[dataNumber].count + count;

		gotoxy(2,35);
		printf("총 %d 원 입니다",price);

		//printf("구매를 마치시겠습니까? (yes/no) ");
		strcpy(InputTextMenu.text,"마치시겠습니까? (yes/no)");
		showInputBox(&InputTextMenu);
		//----for MultiThread--------------------------
		InputTextBox(&InputTextMenu, string);
		//scanf("%s", &string[0]);

		if(  strcmp(string, "yes") == 0){
			printf("구매가 완료됐습니다. 감사합니다.\n");
			sleep(1);
			clear();
			//result = 1;
			break;
		}

    }
 }





int AI_mode_Buy(BREAD_DATA breads[]){
    
	char string[20];
	int result;
	int totalPrice;
	int totalkcal;
	int maxMoney;

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
		InputTextBox(&InputTextMenu, string);
		/*i=0;
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
		*/

		maxMoney = atoi(string); // STRING TO INT

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
        
		//printf("구매를 마치시겠습니까? (yes/no) ");
		strcpy(InputTextMenu.text,"마치시겠습니까? (yes/no)");
		showInputBox(&InputTextMenu);
		//----for MultiThread--------------------------
		InputTextBox(&InputTextMenu, &string);
		//scanf("%s", &cmd[0]);

		if(  strcmp(string, "yes") == 0){
			printf("구매가 완료됐습니다. 감사합니다.\n");
			sleep(1);
			clear();
			//result = 1;
			break;
		}
        
    }
    return result;
    
}
