//
//  bread.h
//  bakery_porgram
//
//  Created by 최서영 on 2020/11/03.
//

#ifndef bread_h
#define bread_h


typedef struct{
    char name[20];
    char number[20];
    int price;
    char preference[20];
    int count;
    
}BREAD_DATA;


void DataLoad(BREAD_DATA *ptr, char *name, char *number, int price, char *preference, int count);
void ContactMenuByPointer(BREAD_DATA *p);
int MainData(BREAD_DATA *ptr, int NumOfpang);
int addUser(BREAD_DATA AddrInfo[], int i);
int search(BREAD_DATA breads[], char searchMethod, char *breadNumber);
int buyBread(BREAD_DATA breads[]);

#endif /* bread_h */
