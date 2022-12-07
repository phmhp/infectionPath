//최근  수정 날짜: 2022.12.07


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
} place_t; //enum place p1; 대신 place_t p1; 

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
typedef struct ifs_ele  {
	int index;//번호 -> 정수 
	int age; //나이 -> 정수
	int time; 	//감염 시점 -> 정수
	place_t place[N_HISTORY];//감염 직전 이동경로 -> (enum) place_t 배열 
	
  //2. 구조체 instance 생성
} ifs_ele_t; 


 
 //3.구조체 내용 저장   //메모리를 동적으로 잡아서 main.c에게 전달해줄 것. 
 void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
 { 
 	ifs_ele_t* ptr; //구조체형 포인터. 
	 
	//지금 여기서는 구조체 하나만 만드는거라 malloc 구조체하나크기만큼 잡음. 
	ptr=(ifs_ele_t*)malloc(sizeof(ifs_ele_t)); 	
	
	//ptr(구조체형 포인터)의 멤버 에 인수로 받은 값을 저장. 
	ptr->index=index;   
	ptr->age=age;
	ptr->time detected_time; 
	ptr->place[0]=history_place[0] ;//배열 요소값 복사 => strcpy로? 아니면 배열[0]=배열[0] ? 
	ptr->place[1]=history_place[1] ;
	ptr->place[2]=history_place[2] ;
	ptr->place[3]=history_place[3] ;
	ptr->place[4]=history_place[4] ;	  
	
	//여기에 바로 free하면 안됨 =>언젠가는 free를 해야한다는 뜻 (당장x) 
	// 지금은 main.c에서 element.c로 구조체 만들 값들을 전달받은 후에 
	//구조체만들고,  다시 main.c에게 줘야해서 여기서 free쓰면 안됨. 
	
 	return ptr; //구조체형 포인터인 ptr을 다시 main.c에게 전달. 
 
  }


//4.구조체 내용 분석  

//4-1. 나이 
int ifctele_getAge(void* obj) 
{ 	
	ifs_ele_t* ptr= (ifs_ele_t*)obj; //구조체로 인식할 수 있게 타입캐스팅하고 포인터로 가리킨 다음  
	return ptr->age; //포인터로 구조쳋  안의 멤버를 반환해주면 됨.  

}




//4-2. 감염 직전 이동경로. (배열) 
 int ifctele_getHistPlaceIndex(void* obj, int index)
 {  
 	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
 	return (strPtr->place_t place[index]);  //place_t 유무 확인해봐야함.  
 }
 
 
 
//4-3.감염 시점. 
unsigned int ifctele_getinfestedTime(void* obj)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
 	return (strPtr->time);  
}


 
//5. 구조체 내용 출력. =>1,2,3번 메뉴에서 사용됨. 
void ifsele_printElement(void* obj) {
	ifs_ele_t *strPtr = (ifs_ele_t *)obj; //구조체형식씌워서 가리키게 한다음에 출력. 
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
			 ifctele_getPlaceName(ptr->place[4]),ptr->place[4]			 ); //수정해야할수도... 
	printf("--------------------------------------------\n");
}


char* ifctele_getPlaceName(int placeIndex) //장소이름과 번호 맵핑  
{
	return countryName[placeIndex];
}

