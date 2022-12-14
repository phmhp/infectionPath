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
        {	
			case MENU_TRACK: //4
			 {	//변수 선언 영역(start)
			 	int i;
			 	void *infectee;
			 	int infecteeDT; //Detected Time
			 	int *detected_time;
			 	int infecteeDP; //Detected Place
			 	int *detected_place;
			 	
			 	
			 	
			 	//변수 선언 영역 (end) 
			 
			 	printf("Patient index : "); 
            	scanf("%d",&pIndex);
			 	
			 	ifct_element = ifctdb_getData(pIndex);
			 	infectee = (void *)ifct_element;
			 	if (infectee != NULL ) { //while문이 무한반복하지않도록.. 
			 		
			 		infecteeDT = ifctele_getinfestedTime(infectee) ;
            		detected_time = &infecteeDT;
			 		infecteeDP = ifctele_getHistPlaceIndex(infectee, i );
					detected_place = &infecteeDP;
			 		int transmitterpIndex;
			 		
					 
					 
	
			 		transmitterpIndex = trackInfester(pIndex,detected_time ,detected_place);			//{int trackInfester(int patient_no, int *detected_time, int *place)
					printf("main _  transmitterpIndex = %d", transmitterpIndex);
				 }
			 	
			 	
			 	
			 break;   
			}
				
       } //switch문 끝  	
    
    } while(menu_selection != 0); //do-while문 끝  
    
    
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
		//printf("track count : %d \n",i);
		printf("\n\n\n\n trackInfester_ here : (try %d th)\n", i);
		current_metTime = isMet (infectee_track, ith_track); //현재환자랑 i번째 환자랑 만난 시점 (현재 돌고있는 for문으로 바로 찾아낸 결과
		printf("trackInfester_ current_metTime = %d \n", current_metTime);
		if (current_metTime > 0 )
		{	printf("trackInfester_ test for- current_metTime > 0 / current time : %d \n",current_metTime); 
			if (current_metTime < metTime_record) 
			{
			metTime_record = current_metTime;
			passing_pIndex = ifctele_getpIndex(ith_track);
			printf("trackInfester_passing_pIndex = %d\n", passing_pIndex);
			}
			
		}
	printf("trackInfester -----%d번째 환자와 만난 시점 = %d : -----지금까지 가장 이른 시점 : %d\n",i, current_metTime,metTime_record);

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
	
	 
	for (i=0; i<3; i++){
		//현재 환자의 i번째 이동장소 시점 계산
		//=> 환자 감염일 +인덱스 -4
		//=>   ifctele_getinfestedTime(infectee) + i -4 
		
		//infectee_ithPlaceTime = (ifctele_getinfestedTime(infectee))+i-4;
		//printf("1_ 현재환자의 i번째 이동장소 시점 계산  = infectee_ithPlaceTime = %d \n", infectee_ithPlaceTime);//제대로 됨 	
		
	
		//현재 환자가 i번째에 있던 장소  
		infectee_ithPlace = ifctele_getHistPlaceIndex(infectee, i );
		for (k= 3; k<N_HISTORY;k++) {
		//대상환자가 k번째에 있던 장소  
			suspect_kthPlace = ifctele_getHistPlaceIndex(suspect, k );
			if ( infectee_ithPlace == suspect_kthPlace )	{
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
				 	printf("isMet_만난 경우에 metTime  : %d\n",metTime_isMet);
				 	return metTime_isMet;
				 } 
			}
		}
	}	 
printf("isMet_못만난 경우에 metTime : %d\n",metTime_isMet);
return metTime_isMet;
}



int convertTimeToIndex( int time, int infestedTime) 
{	//printf("\n\n\ntime =%d\n",time); //제대로 도착  
	//printf("infestedTime = %d\n\n\n",infestedTime); //제대로 도착  

	int index =-1;

	if (time <= infestedTime && time> infestedTime - N_HISTORY)
	{	//printf("here is convert\n");
		index = N_HISTORY-(infestedTime-time)-1;
	}

	//printf("in convert, index = %d \n", index);
	return index;
}

