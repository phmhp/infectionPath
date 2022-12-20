//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

//후보값(도시명)에 대응되는 정수 
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
} place_t; 

 

//도시 번호=>도시명(문자열)  
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



//1.구조체 정의 
typedef struct ifs_ele {
	int index; //번호-> 정수 
	int age; //나이 -> 정수 
	int time; //감염시점 -> 정수 
	place_t placeHist[N_HISTORY]; //감염직전 이동경로 -> place_t 배열  (enum)
}ifs_ele_t; //구조체 instance 생성 



//3.구조체 내용 저장 -메모리를 동적으로 잡은 후에 main.c로 전달. 
void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{	ifs_ele_t* ptr; //ifs_ele 구조체형 포인터 
	ptr=(ifs_ele_t*)malloc(sizeof(ifs_ele_t)); //구조체 하나 만드는 만큼만 크기 지정하면 됨.
	
	//ptr(구조체형포인터)의 멤버로 전달받은 값을 저장.
	ptr->index=index;
	ptr->age=age;
	ptr->time=detected_time;
	ptr->placeHist[0]=history_place[0]; 
	ptr->placeHist[1]=history_place[1];
	ptr->placeHist[2]=history_place[2];
	ptr->placeHist[3]=history_place[3];
	ptr->placeHist[4]=history_place[4];
	
	//여기서 (malloc) free x  
	//다시 main.c에 전달해야하기때문.
	 
	return ptr; //구조체형포인터 ptr 다시 main.c에 전달 
}



//4-2. 감염직전 이동경로를 반환해주는 함수 (배열)   
int ifctele_getHistPlaceIndex(void* obj, int index)
{	//int indexNum;
	//indexNum = index;
	ifs_ele_t *ptr=(ifs_ele_t*)obj;
	return ptr->placeHist[index]; //return ptr->placeHist[indexNum];
}



//최종 감염 시점(ex-28일)을 반환해주는 함수  
unsigned int ifctele_getinfestedTime(void* obj)
{	ifs_ele_t *ptr=(ifs_ele_t *)obj;  //구조체포인터로 void포인터 odj 가리킴 //구조체 인식하도록 구조체로 타입캐스팅한 것. 
	return (ptr->time);  //포인터로 구조체 멤버 반환 
}



//4.구조체 내용 분석 
//4-1. 나이를 반환해주는 함수  
int ifctele_getAge(void* obj)
{	ifs_ele_t* ptr =(ifs_ele_t*)obj; //구조체포인터로 void포인터 odj 가리킴 //구조체 인식하도록 구조체로 타입캐스팅한 것. 
	return ptr->age; //포인터로 구조체 멤버 반환  
}



//환자번호를 반환해주는 함수  
int ifctele_getpIndex(void* obj)
{	ifs_ele_t* ptr =(ifs_ele_t*)obj; //구조체포인터로 void포인터 odj 가리킴 //구조체 인식하도록 구조체로 타입캐스팅한 것. 
	return ptr->index;  //포인터로 구조체 멤버 반환  
}



//5.구조체 내용(환자 정보) 출력 => 메뉴 1,2,3에서 사용 
void ifctele_printElement(void* obj)
{	ifs_ele_t* ptr=(ifs_ele_t*)obj;  //구조체형 포인터로 obj포인터를 받아서 간접참조해서 구조체 내용 출력  
	//print elements
	printf("--------------------------------------------\n");
	printf("Patient index : %d\n", ptr->index );
	printf("Patient age : %d\n", ptr->age );
	printf("Detected time : %d\n", ptr->time );
	printf("Path History : %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)\n",
			 ifctele_getPlaceName(ptr->placeHist[0]),ptr->placeHist[0], 
			 ifctele_getPlaceName(ptr->placeHist[1]),ptr->placeHist[1],
			 ifctele_getPlaceName(ptr->placeHist[2]),ptr->placeHist[2],
			 ifctele_getPlaceName(ptr->placeHist[3]),ptr->placeHist[3],
			 ifctele_getPlaceName(ptr->placeHist[4]),ptr->placeHist[4]    ); 
	printf("--------------------------------------------\n");	
}



//장소번호를 받고 장소이름(문자열)을 반환해주는 함수 
char* ifctele_getPlaceName(int placeIndex) //장소번호를 받으면  
{	return countryName[placeIndex]; //장소번호에 해당하는 장소이름을 반환해줌. 
}




