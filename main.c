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
int isMet( void *infectee_ptr, void * suspect_ptr);
int convertTo_ith( int time, int infestedTime) ;
int convertTimeToIndex( int time, int infestedTime);


int main(int argc, const char * argv[]) 
{
    
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
		//printf("count : %d \n", pTotal);
		 
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
        {	 case MENU_EXIT: //0
                printf("Exiting the program... Bye bye.\n");
                break;
                
 //특정 환자에 대한 정보 출력  		
//지정된 환자(번호 입력)에 대한 정보 출력은 번호, 나이, 감염 확인일자, 그리고 최근 5개 이동장소를 출력           
			case MENU_PATIENT: //1  //완성! 
            {	void * meme;//ifct element
				printf("Patient index : ");
				scanf("%d", &pIndex); 
				if (pIndex >= 0 && pIndex < pTotal) //if (pIndex 정상범위의 숫자이면)
				 
				ifct_element = ifctdb_getData(pIndex); //pIndex번째 환자정보구조체를 linked list에서 꺼내고, void포인터구조체를 ifct_element 포인터변수에 반환.
				ifctele_printElement(ifct_element);//pIndex번째 환자정보 출력 
				meme = (void *)ifct_element;
				printf("%d",ifctele_getAge(meme));
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
			case MENU_TRACK: //4
			 {	//변수 선언 영역(start)
			 	int i;
			 	void *infectee;
			 	int infecteeDT; //Detected Time
			 	int *detected_time;
			 	int infecteeDP; //Detected Place
			 	int *detected_place;
			 	int transmitterpIndex =-1;
			 	int metTime, metPlace ; 
			 	void *transmitter;
			 	int metPlaceIndex;
				void *frtInfectee;
				int metHistIndex;
				
				int firstpIndex;
				int lastpIndex = -1;
			 	//변수 선언 영역 (end) 
			 
			 	printf("Patient index : "); 
            	scanf("%d",&pIndex);
			 	firstpIndex = pIndex; 
			 	
			 	ifct_element = ifctdb_getData(pIndex);
				infectee = (void *)ifct_element;
			 	while (pIndex >=0  ) { //while문이 무한반복하지않도록.. 
			 		
			 		
			 		infectee= ifctdb_getData(pIndex);
			 		
			 		infecteeDT = ifctele_getinfestedTime(infectee) ;
            		detected_time = &infecteeDT;
			 		infecteeDP = ifctele_getHistPlaceIndex(infectee, i );
					detected_place = &infecteeDP;
			 		transmitterpIndex = trackInfester(pIndex,detected_time ,detected_place);			//{int trackInfester(int patient_no, int *detected_time, int *place)
					
					if (transmitterpIndex >= 0) //전파자 있으면 
					{	
						transmitter = ifctdb_getData(transmitterpIndex);
						metTime =isMet(infectee,transmitter);
						metHistIndex =  metTime-infecteeDT+4;//순서 인덱스를 말하는 거고
						
						metPlaceIndex= ifctele_getHistPlaceIndex(infectee,metHistIndex);  //장소 인덱스를 말하는 것  

						
						metPlace = //장소 숫자 인덱스를 말하는 것
						
						printf(" --> [TRACKING] patient %d is infected by %d (time : %d, place : %s)\n", 
								                    	ifctele_getpIndex(infectee), transmitterpIndex, metTime ,ifctele_getPlaceName(metPlaceIndex));//printf(“%i 환자는 %i 환자에게 전파됨\n”, 현재환자, 전파자);		
						
						pIndex = ifctele_getpIndex(transmitter);
						infectee = (void *)transmitter ; 
						lastpIndex = pIndex;
					}	
					else if (transmitterpIndex < 0){
						if (lastpIndex < 0) 
						{			
							frtInfectee = (void *)infectee;
							printf("%d is the first infector!!\n", ifctele_getpIndex(frtInfectee));
							pIndex =-1; 
							infectee = NULL;
							
						} 
						else if (lastpIndex >=0)
						{
							pIndex =-1; 
							infectee = NULL;
							
							printf("The first infector of %d is %d\n" , firstpIndex,lastpIndex);
						}
					} 
					
			//the first tracker is ~...	
			}//while 문  끝  
			
					
					
						//
			
			
			
			break; 
       		}//case MENU_TRACK: 끝  
		    default:
		                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
		                break;

    
    
 
		}//switch문 끝  


	}	while(menu_selection != 0);  //do-while문 끝 
	
   return 0;	
}//main함수 끝  



//

int trackInfester(int patient_no,int *detected_time , int *place) //프로토타입에 이렇게 돼있음. 
{	//변수 선언 영역 
	int i; 
	void * infectee_track;
	void * ith_track; 
	
	int current_metTime = -1;
	int metTime_record =1000;
	int passing_pIndex = -1;
	 
	//변수 선언 영역 
	//int pIndex = patient_no; //추가 및 변경 (patient_no =>pIndex 
	
	
	
	infectee_track = ifctdb_getData(patient_no); 

	for (i=0;i<pTotal;i++) //환자 전체 인원만큼 반복 	
	{	
		ith_track = ifctdb_getData(i);
			current_metTime = isMet (infectee_track, ith_track); //현재환자랑 i번째 환자랑 만난 시점 (현재 돌고있는 for문으로 바로 찾아낸 결과
			if (current_metTime > 0 )
			{	if (current_metTime < metTime_record) 
				{
				metTime_record = current_metTime;
				passing_pIndex = ifctele_getpIndex(ith_track);
				}
				
			}
	
	}
	
 	return passing_pIndex;
}









//

int isMet( void *infectee_ptr, void * suspect_ptr) //현재환자,i번째 환자 받는거라고 수도코드에 나와있음.  
{	//변수 선언 영역 
	int i; 
	int k;
	void * infectee;
	infectee = (void *)infectee_ptr;
	void * suspect;
	suspect = (void*)suspect_ptr;
	int infectee_ithPlaceTime;
	int suspect_ithPlace;
	int infectee_ithPlace; 
	int suspect_infestedTime;	
	
	int ithTime;
	int kthTime;
	
	int suspect_kthPlace; 
	int metTime_isMet =-1;
	
	//변수 선언 영역 
	
	 
	for (i=0; i<3; i++)
	{
		//현재 환자의 i번째 이동장소 시점 계산
		//=> 환자 감염일 +인덱스 -4
		//=>   ifctele_getinfestedTime(infectee) + i -4 
	
		//현재 환자가 i번째에 있던 장소  
		infectee_ithPlace = ifctele_getHistPlaceIndex(infectee, i );
		for (k= 3; k<N_HISTORY;k++) 
		{
		//대상환자가 k번째에 있던 장소  
			suspect_kthPlace = ifctele_getHistPlaceIndex(suspect, k );
			if ( infectee_ithPlace == suspect_kthPlace )	
			{
				//같은 장소에 있던 것이 맞다면
				
				//날짜 비교 
				//현재환자 날짜 변수 = 최종감염일함수(현재환자)+i-4;
				ithTime=ifctele_getinfestedTime(infectee)+i-4;
				
				//해당환자 날짜 변수 = 최종감염일함수(해당환자)+k-4;
				kthTime=ifctele_getinfestedTime(suspect)+k-4;
				
				//if (현재환자 날짜 변수 == 해당환자 날짜 변수)
				if (ithTime ==kthTime)
				{
					//만난시간 = 현재환자 날짜 변수 ; //(어차피 현재환자날짜변수 ==해당환자날짜변수이긴 함 뭘 넣어도 상관없음 ) 
				 	metTime_isMet = ithTime ; 

				 } 
			}
		}
	}	 
return metTime_isMet;  
}




