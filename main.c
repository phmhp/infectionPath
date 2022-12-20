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

//전역변수 선언  
int pTotal; //전체 환자 수=> 다른 함수( trackInfester() )에서도 사용해서 전역변수로 선언  

int trackInfester(int patient_no, int *detected_time, int *place); // trackInfester() 선언  
int isMet( void *infectee_ptr, void * suspect_ptr); //isMet() 선언 

int main(int argc, const char * argv[]) 
{	//기본 변수  
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];

    //메뉴 공통 변수 
    int i; 
	int resultCount=0; //결과값 인원 셀 때 사용 (menu 2, 3) 	
	
	//메뉴 2번 변수
	char placeName[MAX_PLACENAME]; //장소 문자열 입력받을 때 사용  
	int finalPlaceNum;//장소 번호  
	char finalPlaceName[MAX_PLACENAME];//HPlace를 문자열로 변환할 때 사용  
	
	//메뉴 3번 변수
	int minAge,maxAge; //최소 나이, 최대 나이 

	//메뉴 4번 변수
	void *infectee; //현재 환자 정보 저장할 포인터  
	int infecteeDT; //현재환자의 Detected Time
	int *detectedTime; //infecteeDT 가리킬 포인터  
	int infecteeDP; //infectee의 Detected Place
	int *detectedPlace; //infecteeDP 가리킬 포인터  
	int spreaderPIndex = -1; //전파자(대상환자)의 환자 인덱스번호 (초기값 음수로 설정해서 전파자가 있는지 없는지 구분) 
	int metTime, metPlace; //만난 시점, 만난 장소 (정수형태) 
	void *spreader; //대상 환자 정보 저장할 포인터  
	int metPlaceNum; //만난 장소 도시 번호 
	int metTimeIndex; //만난 시점이 몇번째 [인덱스]인지 저장  
	int firstPIndex; //입력값으로 받은 첫 현재환자  
	int lastPIndex = -1; // 가장 빨리 감염된 전파자의 환자 인덱스 
	int loopCount=0; //전파자 찾기 loop을 반복한 횟수 
	//(반복횟수를 통해서 입력받은 환자번호가 아예 첫 감염자인지 / 입력받은 환자번호의 전파자를 거슬러올라가서 추적한 결과 가장 먼저 감염된 전파자인지 구분)  
    
    
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
        
        
        //--------------------------- main function _ MENU. ------------------------------  
        switch(menu_selection)
        {
        	//------------- MENU 0  --------------
			case MENU_EXIT: //0
            {
				printf("Exiting the program... Bye bye.\n");
                break;
        	}// case MENU_EXIT: 끝  
        	
			//------------- MENU 1  --------------           
			case MENU_PATIENT:   
            {			
				printf("Patient index : ");
				scanf("%d", &pIndex); 
				
				//입력값 예외처리 (start)
				if (pIndex >= pTotal) //환자 인덱스 번호를 초과했을 때  
				{	printf("[ERROR] Your input for the patient index (%d) is wrong! input must be 0 ~ 4\n",pIndex);
					break;
				}
				else if (pIndex < 0) //음수 입력 시 
				{	
					printf("There is no element of index %d.\n",pIndex);
					break;
				} 
				//입력값 예외처리 (end)  
				
				
				//정상적으로 작동하는 경우  
				else if (pIndex >= 0 && pIndex < pTotal) 
				{  
					ifct_element = ifctdb_getData(pIndex); //포인터를 함수 매개변수로 넘겨주면 함수에서는 구조체 멤버 접근 후 값을 반환해줌.
													   	   //pIndex번째 환자정보구조체를 linked list에서 꺼내고, void*구조체를 ifct_element 포인터 변수에 반환.
					ifctele_printElement(ifct_element); //pIndex번째 환자정보 출력      
                	break;
            	}
        	} //case MENU_PATIENT: 끝  
			
			//------------- MENU 2  --------------
            case MENU_PLACE: 
            {	resultCount=0; //값 초기화  
            
				printf("Place Name : ");
				scanf("%s",&placeName); //도시명(문자열) 입력받기
				
				for (i=0;i<pTotal;i++) //해당 도시에서 감염된 사람 찾기위해서 환자 전체 수만큼 반복  
				{
					ifct_element = ifctdb_getData(i); //i번째 환자 정보 포인터에 담기  
					finalPlaceNum = ifctele_getHistPlaceIndex (ifct_element,4);//i번째 환자의 감염장소( [4] ) 번호 저장  
					strcpy(finalPlaceName, (ifctele_getPlaceName(finalPlaceNum))); //이후에 입력받은 장소 문자열(placeName)와 비교하기 위해서 문자열로 저장  
					if (strcmp(placeName,finalPlaceName)==0) //입력받은 장소 문자열과 i번째 환자의 감염장소 ( [4] )가 같다면  
					{
						ifctele_printElement(ifct_element);
						resultCount++; //해당장소에서 감염된 사람 숫자 카운트 +1  
					}
				}  
				printf("\nThere are %d patients detected in %s.\n",resultCount, placeName); //해당 장소에서 감염된 전체 사람 수 출력  
                break;
        	} //case MENU_PLACE: 끝  
        	
        	//------------- MENU 3  --------------
            case MENU_AGE: 
            {	
				resultCount =0; //값 초기화 
				printf("minimal age : ");
                scanf("%d",&minAge);
                printf("maximal age : ");
                scanf("%d", &maxAge); 

                //입력값 예외처리  (start) 
            	if (minAge < 0 || maxAge <0 ||minAge >maxAge) // 최소값,최대값으로 번호로 음수출력된 경우 혹은 최소값이 최대값보다 큰 경우     
				{	
					printf("[ERROR] input age (%d , %d) is wrong!\n",minAge,maxAge);
					break;
				}
				//입력값 예외처리(end) 
				
					
				//정상적으로 작동하는 경우
				for(i=0;i<pTotal;i++)
				{
					ifct_element = ifctdb_getData(i);
					if ( ifctele_getAge(ifct_element) >= minAge   &&   ifctele_getAge(ifct_element) <=  maxAge)  //i번째 환자의 나이가 최소값이상 최대값이하인 경우 (정상범위) 
					{
						ifctele_printElement(ifct_element); 
						resultCount++; //마지막에 결과 출력을 위해 해당 나이 범위에 속하는 환자 수 +1  
					}	
				}    
				printf("There are %d patients whose age is between %d and %d.\n",resultCount, minAge, maxAge); //해당 나이 범위에 속하는 환자 수 출력  
                break;
        	}//case MENU_AGE: 끝
        	
        	//------------- MENU 4  --------------
			case MENU_TRACK:
			{	 
			 	printf("Patient index : "); 
            	scanf("%d",&pIndex);
            	
            	//입력값 예외처리(start)  
            	if (pIndex >= pTotal) //환자인덱스번호로 범위 초과하는 값 입력했을 경우   
				{	printf("[ERROR] Your input for the patient index (%d) is wrong! input must be 0 ~ %d\n", pIndex,pTotal-1);
					break;
				}
				//입력값 예외처리(end) 
				
				 
			 	firstPIndex = pIndex; //마지막에 출력할 때 사용하기 위해 입력값(환자번호) 저장  
			 	
				 //환자정보 가져오기  
			 	ifct_element = ifctdb_getData(pIndex);
				infectee = (void *)ifct_element;
				
				while ( pIndex >=0 ) //현재 환자가 있는 동안에만 반복  
				{	
					spreaderPIndex= -1; //전파자번호 초기화(loop을 돌면서 전파자를 새로 찾아야하는데, 전파자가 없을 수도 있으니까 초기값 -1로 설정)  
			 		infectee= ifctdb_getData(pIndex); //반복하면서 현재환자가 바뀌었을 수도 있으니 다시 환자정보 가져옴  
			 		
			 		
			 		//trackInfester 함수에 넘길 변수에 값 저장 (start)
					 infecteeDT = ifctele_getinfestedTime(infectee);//현재환자의 감염시점 
            		detectedTime = &infecteeDT;//trackInfester함수의 매개변수로 쓰기 위해 포인터에 담음  
					infecteeDP = ifctele_getHistPlaceIndex(infectee, 4 ); //현재환자의 감염장소  
					detectedPlace = &infecteeDP; //trackInfester함수의 매개변수로 쓰기 위해 포인터에 담음  
			 		//trackInfester 함수에 넘길 변수에 값 저장 (end) 
					  
					  
					spreaderPIndex = trackInfester(pIndex,detectedTime ,detectedPlace ); //trackInfester 함수 결과값으로 대상환자 인덱스번호 저장  
					
					if (spreaderPIndex >= 0) //전파자 있으면 (초기값 -1에서 바뀌었으면) 
					{	
						spreader  = ifctdb_getData(spreaderPIndex); //전파자 정보 가져오기  
						
						//TRACKING결과 출력을 위해 변수에 값 저장(start) 
						metTime =isMet(infectee,spreader); //전파자와 만난시점  
						metTimeIndex =  metTime-infecteeDT+4;// 전파자와 만난시점의 인덱스 
						metPlaceNum = ifctele_getHistPlaceIndex(infectee,metTimeIndex);  //전파자와 만난시점의 인덱스에 들어있는 도시번호  
						//TRACKING결과 출력을 위해 변수에 값 저장(end) 
						printf(" --> [TRACKING] patient %d is infected by %d (time : %d, place : %s)\n", 
								                    	ifctele_getpIndex(infectee), spreaderPIndex, metTime ,ifctele_getPlaceName(metPlaceNum)); //현재환자인덱스번호,전파자인덱스번호,감염시점,감염장소(문자열) 
						
						//다음 전파자를 찾기 위해서 '현재환자'에 전파자 정보 넣기 
						pIndex = ifctele_getpIndex(spreader); //이번 loop의 전파자의 pIndex를 다음 loop의 pIndex가 되도록 함.    
						infectee = (void *)spreader ; //다음 loop에서 '현재환자'가 지금의 전파자로 대체됨. 
						lastPIndex = pIndex; //누구에게 감염된 것인지 출력할 때 사용하기 위해 가장 최근 환자 인덱스번호로 업데이트 (한명이라도 현재환자가 있던 경우에는 0이상의 숫자) 
						loopCount ++; //while문 반복 횟수 카운트 +1 
					}	
					else if (spreaderPIndex == -1 )//전파자 없으면 (초기값 그대로 -1이면)
					{   
						if (loopCount==0 ) //아예 첫 전파자인 경우  
						{		
							printf("%d is the first infector!!\n", ifctele_getpIndex(infectee));
							pIndex =-1; //while문을 나가기 위해 -1 대입 
						}//if문 끝  
						else if (loopCount > 0 ) //마지막 추적의 결과인 경우 (ex-전파자의 전파자의 전파자의 전파자의.......전파자! )
						{
							pIndex =-1; //whle문을 나가기 위해서 -1 대입 
							printf("The first infector of %d is %d\n" , firstPIndex ,lastPIndex);
						}//else if 문(2)  끝
					}//else-if문(1)  끝
				}//while 문  끝  
				loopCount = 0; //반복 끝났으니까 반복횟수 0으로 초기화  
				break; 
       		}//case MENU_TRACK: 끝  
		    default:
		    {   printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
		        break;
		    }//case default: 끝  
		}//switch문 끝  
	}	while(menu_selection != 0);  //do-while문 끝 
   	return 0;	
}//main함수 끝  










//--------------------------- trackInfester function  ------------------------------  
int trackInfester(int patient_no,int *detected_time , int *place)  
{	
	//변수 선언 영역 
	int i; 
	void * infectee_track; //현재 환자  
	void * ithSuspect_track;  //대상 환자  	
	int  thisLoopMetTime = -1; //현재 돌고있는 loop의 만난 시점 (안만난 경우에는 초기값처럼 -1) 
	int earliestMetTime =1000; //만난 시점들 중에 가장 이른 시점을 저장하는 변수(비교해가면서 점점 더 이른 시점이 저장되는 구조)  
	int spreaderPIndex = -1; //반환값(전파자의 환자인덱스 번호)  
	//변수 선언 영역 

	infectee_track = ifctdb_getData(patient_no); //현재환자 정보 가져오기  

	for (i=0;i<pTotal;i++) //전파자 찾기 위해 환자 전체 인원만큼 반복 	
	{	
		ithSuspect_track = ifctdb_getData(i); //i번째 환자 정보 가져오기 
		thisLoopMetTime = isMet (infectee_track, ithSuspect_track); //현재 돌고있는 loop에서 현재환자랑 i번째 환자가  만난 시점 
		if ( thisLoopMetTime  > 0 ) //현재 환자와 i번째 환자가 만난 적이 있으면  
		{	if ( thisLoopMetTime  < earliestMetTime )  //가장 빠른 시점인지 비교해보기  
			{
				earliestMetTime =  thisLoopMetTime ; 
				spreaderPIndex = ifctele_getpIndex(ithSuspect_track); //가장 빠른 시점이 맞으면 그 시점에 만났던 전파자(현재돌고있는 loop의 i번째 환자)의 인덱스번호를 반환하기위해 저장  
			}			
		}
	}
 	return  spreaderPIndex ; //전파자 환자인덱스 번호 반환 
}









//--------------------------- isMet function  ------------------------------  
int isMet( void *infectee_ptr, void * suspect_ptr) 
{	//변수 선언 영역 
	int i; 
	int k;
	void * infectee; //현재환자  
	infectee = (void *)infectee_ptr;
	
	void * suspect; //대상환자  
	suspect = (void*)suspect_ptr;
	
	int infectee_ithPlace; //현재환자의 i번째 장소 
	int infectee_ithTime; //현재환자의 i번째 장소 당시 시점
	
	int suspect_kthPlace; //대상환자의 k번째 장소  
	int suspect_kthTime; //대상환자의 k번째 장소 당시 시점  
	
	int metTime_isMet =-1; //안만났을 경우를 대비해서 초기값을 -1으로 설정  
	//변수 선언 영역 
	
	 
	for (i=0; i<3; i++) //현재환자가 감염될 수 있는 시점동안 반복 ( [0], [1], [2] ) 
	{
		infectee_ithPlace = ifctele_getHistPlaceIndex(infectee, i );  	//현재 환자가 i번째에 있던 장소 
		for (k= 3; k<N_HISTORY;k++) //대상환자가 감염시킬 수 있는 시점동안 반복 ( [3], [4] ) 
		{
			suspect_kthPlace = ifctele_getHistPlaceIndex(suspect, k );	//대상환자가 k번째에 있던 장소
			if ( infectee_ithPlace == suspect_kthPlace )	//같은 장소에 있던 것이 맞다면(현재환자의 i번째 장소 == 대상환자의 k번째 장소인지) => //같은 시점인지 비교 
			{
				//현재환자 i번째 장소에 있던 시점 = 최종감염일함수(현재환자)+i-4;
				infectee_ithTime=ifctele_getinfestedTime(infectee)+i-4;
				//대상환자 k번째 장소에 있던 시점 = 최종감염일함수(대상환자)+k-4;
				suspect_kthTime=ifctele_getinfestedTime(suspect)+k-4;
				if (infectee_ithTime ==suspect_kthTime)//시점도 같다면 (현재환자 i번째 장소 시점 == 대상환자 k번째 시점) 
				{
				 	metTime_isMet = infectee_ithTime ; //만난 시간==ithTime ==kthTime (초기값인 -1에서 현재환자 i번째 장소시점(=대상환자 k시점과 같음)으로 변경 
				} 
			}
		}
	}	 
	return metTime_isMet; //만난 시점을 반환해줌.   
}




