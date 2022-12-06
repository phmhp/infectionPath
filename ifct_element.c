///���� �ֱ�  ���� ��¥: 2022.12.06 


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
} place_t; //enum place p1; ��� place_t p1;  (+ �迭�� �ؾ���.)

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

//1.����ü ���� -> �ϼ�. 
typedef struct ifs_ele
 {
	//��ȣ -> ���� 
	int pIndex;
	//���� -> ����
	int pAge; 
	//���� ���� -> ���� 
	int time; 
	//���� ���� �̵���� -> (enum) place_t �迭  ũ��=N_HISTORY��ŭ. 
	place_t placeHist[N_HISTORY];
} ifs_ele_t; 





//2.����ü instance ���� //static(��������)����ü �迭. 
static ifs_ele_t ifsarray[20];   //linked list �� �ٲ� ����. 

//�������� ���·� ����� ����ü ������ �����ϴ� ���� ���� ����
static int ifs_cnt; //����� ȯ�������� ����ִ��� ī��Ʈ. 
 
 //3.����ü ���� ���� 
 void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
 {
 	ifsarry[ifs_cnt].pIndex = index;
 	ifsarry[ifs_cnt].pAge = age;
 	ifsarry[ifs_cnt].time = detected_time;
 	for (i=0;i<N_HISTORY;i++)
	 	{
 		ifsarry[ifs_cnt].placeHist[i] = history_place[i]; //�迭 ��� ���� (�ӽ�->�����ؾ��� ���� ����.) 
		 } 
  
 	ifs_cnt++; //����� ȯ�� ��. 
 	
 	return (void*)&ifsarray[ifs_cnt-1]; //����ü�� ����Ű�� �����͸� �˷�����ؼ� �ּҸ� ���ϴ� &�� �ٿ�����ϰ�, �� ��Ȯ�ϰԴ� ����ȯ�ؼ� (void*)���� ��. 
 	  //main.c����(1-2�κп���) fscanf�� �޾Ƽ� ���� ��±��� �غ���.=> �Լ��� �ҷ��� ���� ������ ������ �Լ� Ȱ���� �� ���� ��. 
	 //ifs_cnt �ڸ��� index�� �ش��ϴ� �� �Է��ؾ��ϴµ� => �̹� ���� ȯ�ڸ� ���� ifs_cnt++�� �� ���´ϱ�, ������ ��(return)�� ���� �ٽ� ifs_cnt-1 ����� �� �Ͱ���. 
	  
  }


//4.����ü ���� �м�  
//    ifctele_getAge /  ifctele_getHistPlaceIndex  / ifctele_getinfestedTime

//4-1. ���� 
int ifctele_getAge(void* obj) 
{ 
	//�����ʹ� ���������� �Ű�����(����ü)�� ������� �𸣴ϱ� void�����ͷ� �����ִ´�... 
	//����ü�����ͷ� �Ű������� �ްԲ�.(����Ű�Բ�)
	//Ÿ��ĳ�����ؼ� ����ü������ �ϳ� �����ϰ�, obj�� �ްԲ�(���� �����͸� ����Ű�Բ�) �� ������  
	//obj�� Ÿ��ĳ������ ��Ű�� ��.  
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;	//(����� ������ �ʿ����.) 
	
	//�� ������ strPtr�� ����Ű�� �޸𸮵���� ���̸� ����ϵ��� �ϴ� ��. 
	//����ü �����͸� ������ ����ü ����� ������ ��� �ϴ��� ������ ��...   (-> �̰�? ) 
	return (strPtr->pAge); //strPtr[index]=>pAge ?? �� �𸣰���. 
	
};




//4-2. ���� ���� �̵����. =>�迭? linked list? 
 int ifctele_getHistPlaceIndex(void* obj, int index)
 {
 		ifs_ele_t *strPtr = (ifs_ele_t *)obj;
 		return (strPtr->age);  //�� �𸣰���~~~ 
 }
 
 
 
//4-3.���� ����. 
unsigned int ifctele_getinfestedTime(void* obj)
{
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
 		return (strPtr->time); //strPtr[index]=>time ?? �� �𸣰���. 
}


 
//5. ����ü ���� ���. 
void ifsele_printElement(void* obj) {
	ifs_ele_t *strPtr = (ifs_ele_t *)obj; 
	
	//print elements
}



