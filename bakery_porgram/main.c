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




int  NumOfpang = 7;




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
    
}

