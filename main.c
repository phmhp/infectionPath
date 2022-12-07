//최근  수정 날짜: 2022.12.07


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


int trackInfester(int patient_no, int *detected_time, int *place);
int isMet();
int convertTimeToIndex(int time, int infestedTime );

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element; //구조체정보 반환받을 때 사용 
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    ///////////////////////////////////////
    int	pTotal=0; //전역변수로해야하나? 
    int minAge, maxAge ; //menu 2번 
    char placeName[100]; //menu 2번 입력받을 때 사용  
    int cnt++; //menu 2,3번 환자수 세는 변수. 
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    #if  
    //1-2. loading each patient informations
	//while문을 한번 돌 때 환자정보를 구조체로 만들어서 linked list로 넣는 동작을 함. 
    while (3 == fscanf(fp, "%d %d %d" , &pIndex, &age, &time))
    {	
		int i =0;
    	for( i=0;i<N_HISTORY;i++)//for loop으로 받아서 밑에 함수로 전달. 
		{
   			fscanf(fp, "%d" , &placeHist[i]);
   			//fscanf로 받아온 정보를 모아서 감염정보구조체에 집어넣을 것.  
		}
		ifct_element = ifctele_genElement(pIndex, age , time, placeHist[N_HISTORY] );  
		//element.c파일로 각 변수에 담긴 값들을 보내서 구조체로 만들음.
		 
		ifctdb_addTail(ifct_element); 
		pTotal++; //전체 환자수 카운트  
		//이 함수를 실행하면 database.c로 구조체를 보낼 수 있음. 
		//ifct_element라는 포인터는 바로 위에서  ifctele_genElement함수를 통해 구조체정보를 저장하고있는 상태. 
	}
   
	 
    #endif
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
        
        switch(menu_selection)
        {
            case MENU_EXIT: //0
                printf("Exiting the program... Bye bye.\n");
                break;


            //포인터를 함수를 통해 넘겨주면, 그 함수에서 구조체 멤버(나이)에 접근해서 값을 함수로 나타내주는 것.
			//main.c는 구조체 정보를 모름. 그래서 ifctele.getAge함수를 통해 구조체 멤버(나이)값을 가져오는 것. 
            case MENU_PATIENT: //1  
            {	
				//ifct_element                                                                                              => 그대로 타이핑? 
            	printf("Patient index :");
                scanf("%d", &pIndex);//사용자로부터 환자번호를 입력받음
   
    			if (pIndex >= 0 && pIndex < pTotal) //if (pIndex 정상범위의 숫자이면)
    			
    //특정 환자에 대한 정보 출력
    //지정된 환자(번호 입력)에 대한 정보 출력은 번호, 나이, 감염 확인일자, 그리고 최근 5개 이동장소를 출력 
                ifct_element = ifctdb_getData(pIndex);//pIndex 번째 환자정보구조체를 linked list로부터 꺼내고, 
														   //void*구조체를 (void*)ifct_element 포인터변수에 반환받음.
                ifctele_printElement(ifct_element); //확인해봐야함.  
    //한명의 정보만 출력하면됨. 
				
				//elif  (pIndex 인덱스번호 범위 밖_(너무 크거나 음수일때) / 영문자나 특수문자)
				//print 에러메세지 
				break;
			}   
			
			
			
            case MENU_PLACE: //2
            {         
                cnt=0;
				printf("Place Name : ");
                scanf("%s",&placeName); //문자열입력  
				
				//입력받으면 
								
	//특정 장소에서 (최종)감염이 확인된 환자 관련 정보 출력
	//지정된 장소(문자열 형태로 입력)에서 발병 확인이 된 환자 모두의 정보 출력
				
				//출력해야하는 값이 여러명일 수도 있음.=> for
				for(i=0;i<pTotal;i++)
				{	
					ifct_element = ifctdb_getData(i);//pIndex 번째 환자정보구조체를 linked list로부터 꺼내고, 
														   //void*구조체를 (void*)ifct_element 포인터변수에 반환받음.
					if (strcmp(  placeName ,ifctele_getPlaceName( ifct_element->place[4] )==0 ) //place ? placeHist? 
					{																				//문자열 비교
						ifctele_printElement(ifct_element); //확인해봐야함. 
	 					cnt++;
					}
	 				//else 
	 				//다시 반복. 
	 				
				}
	 			
				//default //오타나거나 숫자입력하거나 감염자 없는 도시여도 결과값 똑같이출력됨. 
				printf("There are %d patients detected in %s.\n",cnt, placeName);
				 break;
			}   
			
			
			
            case MENU_AGE: //3
            {
				printf("minimal age : ");
                scanf("%d",&minAge);
                printf("maximal age : ");
                scanf("%d", &maxAge); 
	//특정 범위의 나이에 해당하는 환자 관련 정보 출력
	//특정 범위 나이는 최소 및 최대 값을 입력 받으며, 최소값 이상이면서 최대값 이하 나이의 환자 모두의 정보 출력
				
				//입력값의 범위가 정상일때 (=/=음수,영어....=>?)  
				for (i=0;i<pTotal<i++)
				{
					ifct_element = ifctdb_getData(i);//pIndex 번째 환자정보구조체를 linked list로부터 꺼내고, 
														   //void*구조체를 (void*)ifct_element 포인터변수에 반환받음.
					if ((ifct_element->age) >= minAge   &&  (ifct_element->age) <=  maxAge)
					{
						ifctele_printElement(ifct_element); //확인해봐야함.
						cnt++;
				 	}
				//같은 값일 때, 0일때,영문자 입력 시  구조체 출력은 안되지만 결과값은 나옴.  
				printf("There are %d patients whose age is between %d and %d.\n", count, minAge, maxAge);

				}
				//else 입력값의 범위가 이상할때 ( 음수 / 최소값이 더 클 때 )
                //print 에러메시지  
				break;
			}
			    
				
				 
				
            case MENU_TRACK: //4
            { 	
	//지정된 환자를 시작으로 전파자와 감염당한 시점 및 장소를 순차적 출력하고 최초 전파자를 최종적으로 출력
    //감염 경로 및 최초 전파자 추적
	            printf("Patient index :");
				scanf("%d",&pIndex); 
				ifct_element = ifctdb_getData(pIndex);//pIndex 번째 환자정보구조체를 linked list로부터 꺼내고, 
														   //void*구조체를 (void*)ifct_element 포인터변수에 반환받음.

				//알고리즘 
				현재환자 = 입력값;
				while (현재환자가 누군가 있음)
				{
				전파자 = trackInfester(현재환자);
				if (전파자가 있으면)
				printf(“%i 환자는 %i 환자에게 전파됨\n”, 현재환자, 전파자);
				else
				최초전파자 = 현재환자;
				현재환자 = 전파자;
				/*? 순차적으로 전파자를 찾아감
					반복문을 통해 현재 환자의 전자파를 반복적으로 찾음
					더이상 전파자가 없으면 현재 환자를 최초 전파자로 간주*/
					
				for (i번째 환자)
				{
				만난시간 = isMet(현재환자, i번째 환자);
				if ( 만난시간> 0) //만났다면
				{
				if (지금까지 환자 중 만난시간이 가장 이른가?)
				{
				전파자 = i;
				}
				}
				}
				return 전파자;	
				}
				
				
				
				
				
				
				
				//if 첫 감염자 아니고 일반 감염자일 때 
				for () 
				{ //전파자가 몇명이냐에 따라 반복 횟수 달라짐. 
				//infected_pIndex , infected_time , infected_place 변수정의? get~함수 써서? 
					printf("[TRACKING] patient %d is infected by %d (time : %d, place : %s)\n",pIndex,  infected_pIndex,  infected_time,  infected_place);  
                } 
                printf("The first infector of %d is %d", pIndex,infcted_pIndex); 
			
               	
           		//elif patient index로 영문자/너무 큰 값 입력시 
				//print 에러메세지  
             	
				//elif 첫번재 감염자 /음수 입력시
				printf("%d is first infector!!",PID);
				break; 
			}
			
			
			
            default: //메뉴번호 잘못 입력했을 때 
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        } //switch문 여기까지. 
    
    } while(menu_selection != 0);
    
    
    return 0;
}



int trackInfester(int patient_no, int *detected_time, int *place)//trackInfester() : 각 환자에 대해 감염가능 시점에 있었는지여부 확인



int isMet(){
	for (i=2;i<N_HISTORY;i++)
	{
	현재환자의 i번째 이동장소 시점 계산;
	계산된 시점에서의 대상환자 이동장소 계산;
	if (i번째 이동장소 == 대상환자 이동장소)
	{
	만난시간 = i번째 이동장소 시점;
	}
	}
	return 만난시간;		
}//isMet() : 두 환자가 만난 시간을 산출하는 함수
// 안만났으면 -1 반환
//만난 환자 중 가장 이른 시간에 만난 환자를 전파자로 간주

//? isMet() : 두환자의 전파 시점 계산 
//감염 시간을 기반으로 머무른 장소 별 시점 계산 
//특정 시간 구간에 같은 장소에 있었는지 확인


int convertTimeToIndex(int time, int infestedTime ) //시점 값을 통해 장소 배열의 index를 산출하는 함수
{
	int index =-1;
	
	if (imte <= infestedTime && time <infestedTime-N-HiSTORY){
		index = N_HISTORY-(infestedTime-time)-1;
	}
}
//예시
//감염시점 : 13, 알고싶은 시점 : 11, index : 5 - (13-11)-1 = 2
//해당 시점에 대한 장소 정보가 없으면 -1 반환
