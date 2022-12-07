//�ֱ�  ���� ��¥: 2022.12.07


//  ifs_element.c 
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t; //enum place p1; ��� place_t p1; 

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};



//1.����ü ���� 
typedef struct ifs_ele  {
	int index;//��ȣ -> ���� 
	int age; //���� -> ����
	int time; 	//���� ���� -> ����
	place_t place[N_HISTORY];//���� ���� �̵���� -> (enum) place_t �迭 
	
  //2. ����ü instance ����
} ifs_ele_t; 


 
 //3.����ü ���� ����   //�޸𸮸� �������� ��Ƽ� main.c���� �������� ��. 
 void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
 { 
 	ifs_ele_t* ptr; //����ü�� ������. 
	 
	//���� ���⼭�� ����ü �ϳ��� ����°Ŷ� malloc ����ü�ϳ�ũ�⸸ŭ ����. 
	ptr=(ifs_ele_t*)malloc(sizeof(ifs_ele_t)); 	
	
	//ptr(����ü�� ������)�� ��� �� �μ��� ���� ���� ����. 
	ptr->index=index;   
	ptr->age=age;
	ptr->time detected_time; 
	ptr->place[0]=history_place[0] ;//�迭 ��Ұ� ���� => strcpy��? �ƴϸ� �迭[0]=�迭[0] ? 
	ptr->place[1]=history_place[1] ;
	ptr->place[2]=history_place[2] ;
	ptr->place[3]=history_place[3] ;
	ptr->place[4]=history_place[4] ;	  
	
	//���⿡ �ٷ� free�ϸ� �ȵ� =>�������� free�� �ؾ��Ѵٴ� �� (����x) 
	// ������ main.c���� element.c�� ����ü ���� ������ ���޹��� �Ŀ� 
	//����ü�����,  �ٽ� main.c���� ����ؼ� ���⼭ free���� �ȵ�. 
	
 	return ptr; //����ü�� �������� ptr�� �ٽ� main.c���� ����. 
 
  }


//4.����ü ���� �м�  

//4-1. ���� 
int ifctele_getAge(void* obj) 
{ 	
	ifs_ele_t* ptr= (ifs_ele_t*)obj; //����ü�� �ν��� �� �ְ� Ÿ��ĳ�����ϰ� �����ͷ� ����Ų ����  
	return ptr->age; //�����ͷ� �����m  ���� ����� ��ȯ���ָ� ��.  

}




//4-2. ���� ���� �̵����. (�迭) 
 int ifctele_getHistPlaceIndex(void* obj, int index)
 {  
 	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
 	return (strPtr->place_t place[index]);  //place_t ���� Ȯ���غ�����.  
 }
 
 
 
//4-3.���� ����. 
unsigned int ifctele_getinfestedTime(void* obj)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
 	return (strPtr->time);  
}


 
//5. ����ü ���� ���. =>1,2,3�� �޴����� ����. 
void ifsele_printElement(void* obj) {
	ifs_ele_t *strPtr = (ifs_ele_t *)obj; //����ü���ľ����� ����Ű�� �Ѵ����� ���. 
	//print elements
	printf("--------------------------------------------\n");
	pritnf("Patient index : %d\n", ptr->index );
	pritnf("Patient age : %d\n", ptr->age );
	pritnf("Detected time : %d\n", ptr->time );
	pritnf("Path History : %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)\n",
			 ifctele_getPlaceName(ptr->place[0]),ptr->place[0],
			 ifctele_getPlaceName(ptr->place[1]),ptr->place[1],
			 ifctele_getPlaceName(ptr->place[2]),ptr->place[2],
			 ifctele_getPlaceName(ptr->place[3]),ptr->place[3],
			 ifctele_getPlaceName(ptr->place[4]),ptr->place[4]			 ); //�����ؾ��Ҽ���... 
	printf("--------------------------------------------\n");
}


char* ifctele_getPlaceName(int placeIndex) //����̸��� ��ȣ ����  
{
	return countryName[placeIndex];
}

