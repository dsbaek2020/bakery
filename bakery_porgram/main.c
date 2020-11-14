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




int  NumOfpang = 7;


// 쓰레드 함수
void *test(void *data)
{
    int i=0;
    char bar[102];
    memset(bar, 0, sizeof(bar));
    const char *lable = "|/-\\";
    

    while(i <= 101)
    {
        gotoxy(1,40);
        printf("[%-100s][%d%%][%c]\r", bar, i, lable[i %4 ]);
        fflush(stdout);
        bar[i++] = '#';
        usleep(100000);
    }
    
    
    /*int a = *(int *)data;
    
    for (i = 0; i < 10; i++)
    {
        gotoxy(1,40);
        printf("%d \n", i*a);
        sleep(2);
    }
     */
    return (void *)(i * 100);
    
    
}
                  

int main(){
    int result;
    
    int value =0;
    BREAD_DATA breads[10] = { {"chocosora" ,"123",2500,"****" , 0},
                             {"soboropang","124",2000,"**"   , 0},
                             {"melonpang" ,"125",3500,"*****", 0},
                             {"gamjapang" ,"126",2500,"**"   , 0},
                             {"raspberry" ,"127",3000,"****" , 0},
                             {"cookies"   ,"128",2000,"***"  , 0},
                             {"creamchee" ,"129",3500,"*****", 0} };
    
    int a = 100;
    pthread_t thread_t;
    int status;
    
    // 쓰레드를 생성한다.
    if (pthread_create(&thread_t, NULL, test, (void *)&a) < 0)
    {
        perror("thread create error:");
        exit(0);
    }
    
    
    while(1){
        
       
        
        value = MainData(&breads[0], NumOfpang);
       
        if(value == 3){ //추가함수
            result = addUser(breads, NumOfpang);
            if( result == 1)
            {
                NumOfpang++;
            }
        }
        
        else if(value == 2){ //검색 함수호출
            search(breads, 'n',0);
        }
        else if(value == 1){
            buyBread(breads);
        }
            
        else if(value == 4){ //정산하기
           
        }
        
        else if(value == 0){
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

