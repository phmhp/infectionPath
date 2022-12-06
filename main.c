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
int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element; //구조체정보 반환받을 때 사용 
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
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
            {	//ifct_element                                                                                              => 그대로 타이핑? 
            	printf("Patient index :");
                scanf("%d", &pIndex);//사용자로부터 환자번호를 입력받음
                printf("--------------------------------------------\n");
                //if (pIndex 정상범위의 숫자이면)
                ifctele_printElement(ifct_element); //확인해봐야함. 
                printf("--------------------------------------------\n");
				
				//elif  (pIndex 인덱스번호 범위 밖_(너무 크거나 음수일때) / 영문자나 특수문자)
				//print 에러메세지 
				break;
			}   
			
			
			
            case MENU_PLACE: //2
            {         
                printf("Place Name : ");
                scanf("%s",&Pname); 
                printf("--------------------------------------------\n");
                //if (strcmp(Pname,ifctele_getPlaceName(placeHist[4]))==0) 
				ifctele_printElement(ifct_element); //확인해봐야함. 
				printf("--------------------------------------------\n");
				//default //오타나거나 숫자입력하거나 감염자 없는 도시여도 결과값 똑같이출력됨. 
				printf("There are %d patients detected in %s.\n", count, Pname);
				 break;
			}   
			
			
			
            case MENU_AGE: //3
            {
				printf("minimal age : ");
                scanf("%d",&minAge);
                printf("maximal age : ");
                scanf("%d", &maxAge);
				//if (age >=minAge && age <=maxAge) 
				//같은 값일 때, 0일때,영문자 입력 시  구조체 출력은 안되지만 결과값은 나옴.  
				printf("--------------------------------------------\n");
				ifctele_printElement(ifct_element); //확인해봐야함. 
				printf("There are %d patients whose age is between %d and %d.\n", count, minAge, maxAge);
                //elif 음수 / 최소값이 더 클 때 
                //print 에러메시지  
				break;
			}    
				
				 
				
            case MENU_TRACK: //4
            { 	
                printf("Patient index :");
				scanf("%d",&pIndex); 
				
				//알고리즘 
				
				
				
				
				
				
				
				
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
