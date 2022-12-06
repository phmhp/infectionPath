//�ֱ�  ���� ��¥: 2022.12.07


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
    void *ifct_element; //����ü���� ��ȯ���� �� ��� 
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
	//while���� �ѹ� �� �� ȯ�������� ����ü�� ���� linked list�� �ִ� ������ ��. 
    while (3 == fscanf(fp, "%d %d %d" , &pIndex, &age, &time))
    {	
		int i =0;
    	for( i=0;i<N_HISTORY;i++)//for loop���� �޾Ƽ� �ؿ� �Լ��� ����. 
		{
   			fscanf(fp, "%d" , &placeHist[i]);
   			//fscanf�� �޾ƿ� ������ ��Ƽ� ������������ü�� ������� ��.  
		}
		ifct_element = ifctele_genElement(pIndex, age , time, placeHist[N_HISTORY] );  
		//element.c���Ϸ� �� ������ ��� ������ ������ ����ü�� ������.
		 
		ifctdb_addTail(ifct_element); 
		//�� �Լ��� �����ϸ� database.c�� ����ü�� ���� �� ����. 
		//ifct_element��� �����ʹ� �ٷ� ������  ifctele_genElement�Լ��� ���� ����ü������ �����ϰ��ִ� ����. 
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


            //�����͸� �Լ��� ���� �Ѱ��ָ�, �� �Լ����� ����ü ���(����)�� �����ؼ� ���� �Լ��� ��Ÿ���ִ� ��.
			//main.c�� ����ü ������ ��. �׷��� ifctele.getAge�Լ��� ���� ����ü ���(����)���� �������� ��. 
            case MENU_PATIENT: //1
            {	//ifct_element                                                                                              => �״�� Ÿ����? 
            	printf("Patient index :");
                scanf("%d", &pIndex);//����ڷκ��� ȯ�ڹ�ȣ�� �Է¹���
                printf("--------------------------------------------\n");
                //if (pIndex ��������� �����̸�)
                ifctele_printElement(ifct_element); //Ȯ���غ�����. 
                printf("--------------------------------------------\n");
				
				//elif  (pIndex �ε�����ȣ ���� ��_(�ʹ� ũ�ų� �����϶�) / �����ڳ� Ư������)
				//print �����޼��� 
				break;
			}   
			
			
			
            case MENU_PLACE: //2
            {         
                printf("Place Name : ");
                scanf("%s",&Pname); 
                printf("--------------------------------------------\n");
                //if (strcmp(Pname,ifctele_getPlaceName(placeHist[4]))==0) 
				ifctele_printElement(ifct_element); //Ȯ���غ�����. 
				printf("--------------------------------------------\n");
				//default //��Ÿ���ų� �����Է��ϰų� ������ ���� ���ÿ��� ����� �Ȱ�����µ�. 
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
				//���� ���� ��, 0�϶�,������ �Է� ��  ����ü ����� �ȵ����� ������� ����.  
				printf("--------------------------------------------\n");
				ifctele_printElement(ifct_element); //Ȯ���غ�����. 
				printf("There are %d patients whose age is between %d and %d.\n", count, minAge, maxAge);
                //elif ���� / �ּҰ��� �� Ŭ �� 
                //print �����޽���  
				break;
			}    
				
				 
				
            case MENU_TRACK: //4
            { 	
                printf("Patient index :");
				scanf("%d",&pIndex); 
				
				//�˰��� 
				
				
				
				
				
				
				
				
				//if ù ������ �ƴϰ� �Ϲ� �������� �� 
				for () 
				{ //�����ڰ� ����̳Ŀ� ���� �ݺ� Ƚ�� �޶���. 
				//infected_pIndex , infected_time , infected_place ��������? get~�Լ� �Ἥ? 
					printf("[TRACKING] patient %d is infected by %d (time : %d, place : %s)\n",pIndex,  infected_pIndex,  infected_time,  infected_place);  
                } 
                printf("The first infector of %d is %d", pIndex,infcted_pIndex); 
			
               	
           		//elif patient index�� ������/�ʹ� ū �� �Է½� 
				//print �����޼���  
             	
				//elif ù���� ������ /���� �Է½�
				printf("%d is first infector!!",PID);
				break; 
			}
			
			
			
            default: //�޴���ȣ �߸� �Է����� �� 
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        } //switch�� �������. 
    
    } while(menu_selection != 0);
    
    
    return 0;
}
