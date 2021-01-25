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
    int kcal;
    
}BREAD_DATA;


void DataLoad(BREAD_DATA *ptr, char *name, char *number, int price, char *preference, int count);
void ContactMenuByPointer(BREAD_DATA *p);
int DisplayMainPanel(BREAD_DATA *ptr, int NumOfpang);
int addNewBread(BREAD_DATA AddrInfo[], int i);
int search(BREAD_DATA breads[], char searchMethod, char *breadNumber);
void buyBread(BREAD_DATA breads[]);
int AI_mode_Buy(BREAD_DATA breads[]);
int GetMenuNumber(void);


#endif /* bread_h */
