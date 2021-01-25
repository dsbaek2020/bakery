//
//  main.c
//  bakery_porgram
//
//  Created by 최서영 on 2020/10/29.
//
#include <stdio.h>
#include <string.h>
#include "bread.h"
#include "ui.h"
#include <pthread.h>

#define MAX_NUM_OF_BREAD		10

// Define Global Variable
int NumOfBread;


// 쓰레드 함수
void *pMainUi(void *data)
{
    while(1)
    {
		DisplayMainPanel((BREAD_DATA *)data,NumOfBread);
		usleep(100000);
    }
   return (void *)0; //(void *)(i * 100);
}
                  

int main(){

    int status;
    int result;
    int userCommand =0;
    
    pthread_t thread_t;
    BREAD_DATA breads[MAX_NUM_OF_BREAD] = { {"chocosora" ,"123",2500,"****" , 0, 300},
                             {"soboropang","124",2000,"**"   , 0,  280,},
                             {"melonpang" ,"125",3500,"*****", 0,  220,},
                             {"gamjapang" ,"126",2500,"**"   , 0,  190},
                             {"raspberry" ,"127",3000,"****" , 0,  180},
                             {"cookies"   ,"128",2000,"***"  , 0,  50},
                             {"creamchee" ,"129",3500,"*****", 0,  20} };

    NumOfBread =7;
    
    clear();
    sleep(2);
    
    
    // 쓰레드를 생성한다.
    if (pthread_create(&thread_t, NULL, pMainUi, (void *)&breads) < 0)
    {
        perror("thread create error:");
        exit(0);
    }
    
    
    while(1){

		userCommand = GetMenuNumber();

		if(userCommand == 3){ //추가함수
			result = addNewBread(breads, NumOfBread);
			if( result == 1)
			{
				NumOfBread++;
			}
		}
		else if(userCommand == 2){ //검색 함수호출
			search(breads, 'n',0);
		}
		else if(userCommand == 1){ // buy
			buyBread(breads);
		}
		else if(userCommand == 4){ //정산하기

		}
		else if(userCommand == 5){ //추천모드
			AI_mode_Buy(breads);
		}
		else if(userCommand == 0){ //quit
			break;
		}
		else{
			printf("잘못된 명령을 입력하였습니다 다시입력\n");
		}
        
    }
    printf("Have a nice day^^");
    
    // 쓰레드가 종료되기를 기다린후
    // 쓰레드의 리턴값을 출력한다.
    pthread_join(thread_t, (void **)&status);
    printf("Thread End %d\n", status);
    
}

