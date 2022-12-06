//가장 최근  수정 날짜: 2022.12.06 


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
    void *ifct_element;
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
    
    //1-2. loading each patient informations
    while (3 == fscanf(fp, "%d %d %d" , &pIndex, &age, &time))
    {	int i =0;
    	for( i=0;i<N_HISTORY;i++)
		{
   			fscanf(fp, "%d" , &placeHist[i]);
   			//fscanf로 받아온 정보를 모아서 감염정보구조체에 집어넣을 것.  
		}
	ifctele_genElement(pIndex,age, time, placeHist[N_HISTORY]);
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
                //if (pID == pIndex)
				printf("Patient index : %d\n",pIndex);
                printf("Patient age : %d\n", ifctele_getAge(ifct_element));
                printf("Detected time : %d\n",  ifctele_getinfestedTime(ifct_element));
				printf("Path History : %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)\n", 
				ifctele_getPlaceName(placeHist[0]),ifctele_getHistPlaceIndex(placeHist[0]), 
				ifctele_getPlaceName(placeHist[1]),ifctele_getHistPlaceIndex(placeHist[1]), 
				ifctele_getPlaceName(placeHist[2]),ifctele_getHistPlaceIndex(placeHist[2]), 
				ifctele_getPlaceName(placeHist[3]),ifctele_getHistPlaceIndex(placeHist[3]), 
				ifctele_getPlaceName(placeHist[4]),ifctele_getHistPlaceIndex(placeHist[4]));
				   break;
			}   
			
			
			
            case MENU_PLACE: //2
            {         
                printf("Place Name : ");
                scanf("%s",&Pname); //사용자로부터 장소를 입력받음
                printf("--------------------------------------------\n");
                //if (strcmp(Pname,ifctele_getPlaceName(placeHist[4]))==0)
            //여기서 뭔가 조건으로 한번 묶어줘야할 것 같음. 
				{
				printf("Patient index : %d\n",pIndex);
                printf("Patient age : %d\n", ifctele_getAge(ifct_element));
                printf("Detected time : %d\n",  ifctele_getinfestedTime(ifct_element));
				printf("Path History : %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)\n", 
				ifctele_getPlaceName(placeHist[0]),ifctele_getHistPlaceIndex(placeHist[0]), 
				ifctele_getPlaceName(placeHist[1]),ifctele_getHistPlaceIndex(placeHist[1]), 
				ifctele_getPlaceName(placeHist[2]),ifctele_getHistPlaceIndex(placeHist[2]), 
				ifctele_getPlaceName(placeHist[3]),ifctele_getHistPlaceIndex(placeHist[3]), 
				ifctele_getPlaceName(placeHist[4]),ifctele_getHistPlaceIndex(placeHist[4]));
				printf("--------------------------------------------\n");
				}
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
			//여기서 뭔가 조건으로 한번 묶어줘야할 것 같음. 	
				{
				printf("--------------------------------------------\n");
				printf("Patient index : %d\n",pIndex);
                printf("Patient age : %d\n", ifctele_getAge(ifct_element));
                printf("Detected time : %d\n",  ifctele_getinfestedTime(ifct_element));
				printf("Path History : %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)-> %s(%d)\n", 
				ifctele_getPlaceName(placeHist[0]),ifctele_getHistPlaceIndex(placeHist[0]), 
				ifctele_getPlaceName(placeHist[1]),ifctele_getHistPlaceIndex(placeHist[1]), 
				ifctele_getPlaceName(placeHist[2]),ifctele_getHistPlaceIndex(placeHist[2]), 
				ifctele_getPlaceName(placeHist[3]),ifctele_getHistPlaceIndex(placeHist[3]), 
				ifctele_getPlaceName(placeHist[4]),ifctele_getHistPlaceIndex(placeHist[4]));
				printf("--------------------------------------------\n");
				}
				printf("There are %d patients whose age is between %d and %d.\n", count, minAge, maxAge);
                break;
			}    
				
				
				
            case MENU_TRACK: //4
            { 	//감염의 시작인 첫 감염자는 printf("%d is first infector!!",PID); 출력해야함.
                printf("Patient index :");
				scanf("%d",&pIndex); //사용자가 고른 환자의 번호
				
               //같은 시기에 같은 장소에 있던 경우를 알아내고
			   //비교대상의 감염확인시점이 더  이르면  감염자. =>맞나? 
			   //이 과정을 계속 반복 (더 이상 같은 시기/같은 장소에 있던 사람들 중 더 이른 사람이 없을 때 까지... 
				for () {
				printf("[TRACKING] patient %d is infected by %d (time : %d, place : %s)\n",pIndex,  infected_pIndex,  infected_time,  infected_place);  //infected_pIndex , infected_time , infected_place 추가로 정의해도 되는지? 
                } 
                printf("The first infector of %d is %d", pIndex,infcted_pIndex); 
				break;
            }
             
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        } //switch문 여기까지. 
    
    } while(menu_selection != 0);
    
    
    return 0;
}
