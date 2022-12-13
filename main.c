//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2


int pTotal; //전체 환자 수  
///////////////////////



int trackInfester(int patient_no, int *detected_time, int *place);
//int isMet();

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    ////////////////////////////
  
    
    int minAge,maxAge; //메뉴 2번
	char placeName[MAX_PLACENAME]; //메뉴 2번-문자열 입력받을 때 사용
	int cnt; //메뉴 2번,3번에서 사용. (결과값 인원 셀 때)
	int HPlace;//포인터로 이동경로 중 하나 (도시 번호) 받아올 정수형변수
	char HPlaceName[MAX_PLACENAME];//HPlace의 이동경로 중 하나(도시번호)에 매치되는 문자열로 변환할 때 사용할 문자열
	

    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r"); //실행할 때  
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    //1-2. loading each patient informations
    //while문을 한번 돌 때 환자정보를 구조체로 만들어서 linked list로 넣는 동작을 함.
	while (3==fscanf(fp,"%d %d %d", &pIndex,&age,&time)) 
	{
		int i=0;
		for (i=0;i<N_HISTORY;i++)//for loop으로 정보읽어들이고 ifctele_genElement함수로 전달. 
		{
			fscanf(fp,"%d",&placeHist[i]); //fscanf로 받아온 정보 모아서 감염정보구조체에 집어넣음. 
		}
		ifct_element = ifctele_genElement(pIndex,age,time,placeHist);//element.c파일로 보내서 구조체만들음.
	
		ifctdb_addTail(ifct_element); //database.c로 구조체 보냄.(linked list에 추가) //ifct_element는 구조체를 가지고 있는 상태. 
		pTotal++; //전체 환자 수 카운트  
		 
	}
	
	
    //1-3. FILE pointer close
    fclose(fp);
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        
        //포인터를 함수이용해서 넘겨주면 함수에서는 구조체 멤버 접근 후 값을 반환해줌.  
        switch(menu_selection)
        {
            case MENU_EXIT: //0
                printf("Exiting the program... Bye bye.\n");
                break;
                
 //특정 환자에 대한 정보 출력  		
//지정된 환자(번호 입력)에 대한 정보 출력은 번호, 나이, 감염 확인일자, 그리고 최근 5개 이동장소를 출력           
			case MENU_PATIENT: //1  //완성! 
            {	//ifct element
				printf("Patient index : ");
				scanf("%d", &pIndex); 
				if (pIndex >= 0 && pIndex < pTotal) //if (pIndex 정상범위의 숫자이면)
				 
				ifct_element = ifctdb_getData(pIndex); //pIndex번째 환자정보구조체를 linked list에서 꺼내고, void포인터구조체를 ifct_element 포인터변수에 반환.
				ifctele_printElement(ifct_element);//pIndex번째 환자정보 출력 
				
				//else (pIndex 범위벗어남/영문자/숫자...) 
				//print 에러메시지     
                break;
        	}
        	
//특정 장소에서 (최종)감염이 확인된 환자 관련 정보 출력
//지정된 장소(문자열 형태로 입력)에서 발병 확인이 된 환자 모두의 정보 출력
            case MENU_PLACE: //2 //완성!!
            {	cnt=0;
				int i;
				printf("Place Name : ");
				scanf("%s",&placeName); //문자열 입력받기
				
				//입력받으면... 
				//출력 값 여러 명일 경우..=>for loop
				for (i=0;i<pTotal;i++)
				{
					ifct_element = ifctdb_getData(i);//pIndex번째 환자정보구조체를 linked list로부터 꺼내서 ifct_element포인터변수에 반환
					
					//문자열로 만들기
					HPlace = ifctele_getHistPlaceIndex (ifct_element,4);//최종감염된 장소번호 알려주는 함수를 통해 HPlace에 값 장소번호저장 
					strcpy(HPlaceName, (ifctele_getPlaceName(HPlace)));
					
					//printf("%d\n",HPlace); //test 
					//printf("%s\n",HPlaceName);//test
					
					
					//char* ifctele_getPlaceName(int placeIndex) 
					//int ifctele_getHistPlaceIndex(void* obj, int index)
					
					
					if (strcmp(placeName,ifctele_getPlaceName(ifctele_getHistPlaceIndex(ifct_element, 4)))==0) //입력받은 장소가 누군가의 마지막 이동경로와 같은 경우
					{
						ifctele_printElement(ifct_element);
						cnt++; //해당장소에서 감염된 사람 숫자 카운트 +1  
						
					}
					//else
					//다시 찾아보기  
				}  
				//오타/숫자/감염자없는 도시의 경우도 출력함. 
				printf("There are %d patients detected in %s.\n",cnt, placeName);
                break;
        	} 
        	
//특정 범위의 나이에 해당하는 환자 관련 정보 출력
//특정 범위 나이는 최소 및 최대 값을 입력 받으며, 최소값 이상이면서 최대값 이하 나이의 환자 모두의 정보 출력
            case MENU_AGE: //3   //완성!!! 
            {	int i;
			 
				printf("minimal age : ");
                scanf("%d",&minAge);
                printf("maximal age : ");
                scanf("%d", &maxAge); 
            
				//정상적으로 작동하는 경우
				for(i=0;i<pTotal;i++)
				{
					ifct_element = ifctdb_getData(i); //pIndex번째 환자정보구조체를 linked list로부터 꺼내옴.   
					if ( ifctele_getAge(ifct_element) >= minAge   &&   ifctele_getAge(ifct_element) <=  maxAge) 
					{
						ifctele_printElement(ifct_element); 
						cnt++;
					}
					
				//해당 결과값이 없는 경우 (minAge==maxAge일 때, 입력값 둘 다 0일때=>구조체출력은 안되지만 아래문장은 출력됨.
				
				}    
				printf("There are %d patients whose age is between %d and %d.\n", cnt, minAge, maxAge);
				//else =>입력값의 범위가 이상할 때 (음수이거나 최소값이 최대값보다 클 때) 
                //print 에러메시지  
                break;
        	} 
        	
//감염 경로 및 최초 전파자 추적				 
//지정된 환자를 시작으로 전파자와 감염당한 시점 및 장소를 순차적 출력하고 최초 전파자를 최종적으로 출력		 
            case MENU_TRACK: //4  //infectee , transmitter, frtInfectee 정의하기! 
            {	
			
			
				void *infectee; //현재 환자  
				void *transmitter; //감염시킨사람 
				void *frtInfectee; //맨 처음 감염자 
				
				int metTime; //감염시점 
			    int metPlace; //감염 장소 
				
				int *detected_time ; //용도?? 
				int *place  ; //용도?? 
				
				/////////////////////////////////
				int i;
				printf("Patient index :");
				scanf("%d",&pIndex); 
				//else patient index로 영문자/너무 큰 값 입력시 
				//print 에러메세지  
				ifct_element = ifctdb_getData(pIndex); //입력된 pIndex 값 가져오기. 
				infectee = (void *)ifct_element;//현재환자 = 입력값;
				
				detected_time = ifctele_getinfestedTime(infectee);
				
				for (i=2; i<N_HISTORY;i++){
					place =  ifctele_getHistPlaceIndex(infectee, i);
					while (infectee!=NULL)//while (현재환자가 누군가 있음){
					{		
							transmitter = trackInfester(pIndex,detected_time , place);			//{int trackInfester(int patient_no, int *detected_time, int *place)
							// printf("%d", ifctele_getAge(transmitter));
							if (transmitter!=NULL) //if (전파자가 있으면)
							{	/*아래 두줄 추가*/ 
								metTime= isMet (infectee, transmitter);//만난 시간 , trackInfester에서 받아오기.  
								metPlace= convertTimeToIndex(metTime); //만난 장소  
								printf(" --> [TRACKING] patient %d is infected by %d (time : %d, place : %s)\n", 
									                    	infectee, transmitter, metTime ,metPlace);//printf(“%i 환자는 %i 환자에게 전파됨\n”, 현재환자, 전파자);
							}  																										
							else //transmitter==NULL일 때 = 전파자가 없는 경우. 
							{
								frtInfectee= infectee;//최초전파자 = 현재환자; // 음수입력해도 같은 결과.			
								printf("%d is first infector!!",frtInfectee);
								infectee=NULL; //while문 반복을 그만하기 위해서 
							}
						//pIndex = ifctele_getpIndex(infectee); //pIndex(입력값)을 바꿔줘서 다음 while문 돌을 때 trackInfester 함수에 전달 . 
						infectee = transmitter; //현재환자 = 전파자; //while문을 반복하기위해(전파자를 계속 찾아서 거슬러올라가기위해서)  
						 
				}	}//체크포인트  
			} //while문 끝 
                break;    
        	
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
       }//switch문 끝  
    
    } while(menu_selection != 0); //do-while문 끝  
    
    
    return 0;
}//main함수 끝  



///////////////////////////           추가한 함수           ////////////////////////////////////////////////
int trackInfester(int patient_no,int *detected_time , int *place) //프로토타입에 이렇게 돼있음. 
{ 	int i;
	void *infectee_ptr; //현재환자 
	void *ith_ptr; //i번째 환자 
	void *transmitter; //전파자  
	int current_metTime=0;
	int metTime_record=1000; //큰 값으로 설정해놓고, 이른 시점(작은 숫자)로 점점 바뀌어가는 구조.  
	
	infectee_ptr=ifctdb_getData(patient_no); //현재환자의 정보 가져오기. 포인터로 가져오면 다시 정보 안가져와도 되나? 
	for (i=0;i<pTotal;i++) //for (i번째 환자) => 환자 n명 중 환자 인덱스 0번부터 n-1번까지 
	{	ith_ptr = ifctdb_getData(i); // i번째 환자의 정보 가져오기.  
		
		current_metTime = isMet( infectee_ptr , ith_ptr ); //i번째 환자로 for문 다시 돌 때마다 값 변함. //& 붙이는 것 맞나? //만난시간 = isMet(현재환자, i번째 환자);
		if (current_metTime > 0) //if ( 만난시간> 0) //만났다면
		{	
			if ( current_metTime < metTime_record )//if (지금까지 환자 중 만난시간이 가장 이른가?) = 만난 시점의 숫자가 더 작은가? 
			{
				metTime_record = current_metTime ; //가장 이른 시점으로 바꿔줌.  
				
				transmitter = (void *)ith_ptr;//전파자 = i;
			}
		}			
	}			
	return transmitter;//return 전파자;	
}








int isMet(void *infectee_ptr , void *suspect_ptr) //현재환자,i번째 환자 받는거라고 수도코드에 나와있음.  
{	
	void * infectee;
	infectee=(void *)infectee_ptr;

	void * suspect;
	suspect=(void *)suspect_ptr;
	printf("%d",ifctele_getinfestedTime(infectee));
	int i,j;
	
	unsigned int infecteePlaceHist;//현재환자의 i번째 이동장소 시점 계산 
	int metTime_isMet;
	//int infecteeHistTime;
	//int ithHistTime;
	//int metTime;
	
	for (i=2;i<N_HISTORY;i++)
	{	
		//현재환자의 i번째 이동장소 시점 계산;
		int temp = i-4;
		infecteePlaceHist = ifctele_getinfestedTime(infectee)- temp;
		
		//계산된 시점에서의 대상환자 이동장소 계산;
		for (j=0; j<=1; j++){
			if (infecteePlaceHist ==( ifctele_getinfestedTime(suspect)-j)) {
				if (   (ifctele_getHistPlaceIndex(infectee,i)) == (ifctele_getHistPlaceIndex(suspect,j))){
					metTime_isMet = infecteePlaceHist;
				}
			}
			else //안만났을 경우 
			{
			metTime_isMet =-1;
			}	
		}
	
	}
	return metTime_isMet; //return 만난시간;		
}







int convertTimeToIndex(int time, int infestedTime ) 
{	// 15주차 슬라이드 p.18
	//시점 값을 통해 장소 배열의 index를 산출하는 함수
	//예시
	//감염시점 : 13, 알고싶은 시점 : 11, index : 5 - (13-11)-1 = 2
	//해당 시점에 대한 장소 정보가 없으면 -1 반환
	int index =-1;
	
	if (time <= infestedTime && time <infestedTime-N_HISTORY)
	{
		index = N_HISTORY-(infestedTime-time)-1;
	}
	return index;
}


