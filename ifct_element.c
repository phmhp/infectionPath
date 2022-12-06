///가장 최근  수정 날짜: 2022.12.06 


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
} place_t; //enum place p1; 대신 place_t p1;  (+ 배열로 해야함.)

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

//1.구조체 정의 -> 완성. 
typedef struct ifs_ele
 {
	//번호 -> 정수 
	int pIndex;
	//나이 -> 정수
	int pAge; 
	//감염 시점 -> 정수 
	int time; 
	//감염 직전 이동경로 -> (enum) place_t 배열  크기=N_HISTORY만큼. 
	place_t placeHist[N_HISTORY];
} ifs_ele_t; 





//2.구조체 instance 생성 //static(전역변수)구조체 배열. 
static ifs_ele_t ifsarray[20];   //linked list 로 바꿀 예정. 

//전역변수 형태로 저장된 구조체 개수를 저장하는 정수 변수 선언
static int ifs_cnt; //몇명의 환자정보가 들어있는지 카운트. 
 
 //3.구조체 내용 저장 
 void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
 {
 	ifsarry[ifs_cnt].pIndex = index;
 	ifsarry[ifs_cnt].pAge = age;
 	ifsarry[ifs_cnt].time = detected_time;
 	for (i=0;i<N_HISTORY;i++)
	 	{
 		ifsarry[ifs_cnt].placeHist[i] = history_place[i]; //배열 요소 복사 (임시->수정해야할 수도 있음.) 
		 } 
  
 	ifs_cnt++; //저장된 환자 수. 
 	
 	return (void*)&ifsarray[ifs_cnt-1]; //구조체를 가리키는 포인터를 알려줘야해서 주소를 뜻하는 &를 붙여줘야하고, 더 정확하게는 형변환해서 (void*)붙인 것. 
 	  //main.c에서(1-2부분에서) fscanf로 받아서 값을 출력까지 해봤음.=> 함수를 불러서 값을 적절히 넣으면 함수 활용할 수 있을 것. 
	 //ifs_cnt 자리에 index에 해당하는 값 입력해야하는데 => 이미 다음 환자를 위해 ifs_cnt++를 한 상태니까, 돌려줄 때(return)할 때는 다시 ifs_cnt-1 해줘야 할 것같음. 
	  
  }


//4.구조체 내용 분석  
//    ifctele_getAge /  ifctele_getHistPlaceIndex  / ifctele_getinfestedTime

//4-1. 나이 
int ifctele_getAge(void* obj) 
{ 
	//포인터는 갖고있지만 매개변수(구조체)의 생김새를 모르니까 void포인터로 갖고있는다... 
	//구조체포인터로 매개변수를 받게끔.(가리키게끔)
	//타입캐스팅해서 구조체포인터 하나 선언하고, obj를 받게끔(들어온 포인터를 가리키게끔) 한 다음에  
	//obj도 타입캐스팅을 시키는 것.  
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;	//(여기는 수정할 필요없음.) 
	
	//그 다음에 strPtr이 가리키는 메모리덩어리의 나이를 출력하도록 하는 것. 
	//구조체 포인터를 가지고 구조체 멤버에 접근을 어떻게 하는지 적으면 됨...   (-> 이거? ) 
	return (strPtr->pAge); //strPtr[index]=>pAge ?? 잘 모르겠음. 
	
};




//4-2. 감염 직전 이동경로. =>배열? linked list? 
 int ifctele_getHistPlaceIndex(void* obj, int index)
 {
 		ifs_ele_t *strPtr = (ifs_ele_t *)obj;
 		return (strPtr->age);  //잘 모르겠음~~~ 
 }
 
 
 
//4-3.감염 시점. 
unsigned int ifctele_getinfestedTime(void* obj)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
 		return (strPtr->time); //strPtr[index]=>time ?? 잘 모르겠음. 
}


 
//5. 구조체 내용 출력. 
void ifsele_printElement(void* obj) {
	ifs_ele_t *strPtr = (ifs_ele_t *)obj; 
	
	//print elements
}



