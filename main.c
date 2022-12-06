//���� �ֱ�  ���� ��¥: 2022.12.06 


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
   			//fscanf�� �޾ƿ� ������ ��Ƽ� ������������ü�� ������� ��.  
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


                 //�����͸� �Լ��� ���� �Ѱ��ָ�, �� �Լ����� ����ü ���(����)�� �����ؼ� ���� �Լ��� ��Ÿ���ִ� ��.
				//main.c�� ����ü ������ ��. �׷��� ifctele.getAge�Լ��� ���� ����ü ���(����)���� �������� ��. 
            case MENU_PATIENT: //1
            {	//ifct_element                                                                                              => �״�� Ÿ����? 
            	printf("Patient index :");
                scanf("%d", &pIndex);//����ڷκ��� ȯ�ڹ�ȣ�� �Է¹���
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
                scanf("%s",&Pname); //����ڷκ��� ��Ҹ� �Է¹���
                printf("--------------------------------------------\n");
                //if (strcmp(Pname,ifctele_getPlaceName(placeHist[4]))==0)
            //���⼭ ���� �������� �ѹ� ��������� �� ����. 
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
			//���⼭ ���� �������� �ѹ� ��������� �� ����. 	
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
            { 	//������ ������ ù �����ڴ� printf("%d is first infector!!",PID); ����ؾ���.
                printf("Patient index :");
				scanf("%d",&pIndex); //����ڰ� �� ȯ���� ��ȣ
				
               //���� �ñ⿡ ���� ��ҿ� �ִ� ��츦 �˾Ƴ���
			   //�񱳴���� ����Ȯ�ν����� ��  �̸���  ������. =>�³�? 
			   //�� ������ ��� �ݺ� (�� �̻� ���� �ñ�/���� ��ҿ� �ִ� ����� �� �� �̸� ����� ���� �� ����... 
				for () {
				printf("[TRACKING] patient %d is infected by %d (time : %d, place : %s)\n",pIndex,  infected_pIndex,  infected_time,  infected_place);  //infected_pIndex , infected_time , infected_place �߰��� �����ص� �Ǵ���? 
                } 
                printf("The first infector of %d is %d", pIndex,infcted_pIndex); 
				break;
            }
             
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        } //switch�� �������. 
    
    } while(menu_selection != 0);
    
    
    return 0;
}
