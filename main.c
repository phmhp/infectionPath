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



//int trackInfester(int patient_no, int *detected_time, int *place);
//int isMet();
int convertTimeToIndex(int time, int infestedTime );

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element=0; //����ü���� ��ȯ���� �� ��� 
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    ///////////////////////////////////////
  	int pTotal=0;  //�����������ؾ��ϳ�? 

    int minAge, maxAge ; //menu 2�� 
    char placeName[100]; //menu 2�� �Է¹��� �� ���  
    //char histPlaceName[100];
    //int histPlaceIndex;
	int cnt; //menu 2,3�� ȯ�ڼ� ���� ����. 
 	int HPlace; //�����ͷ� �̵���� ���� ��ȣ �޾ƿ� ���� 
	char HPlaceName[100];  //HPlace�� �̵���� ���� ��ȣ�� �ش��ϴ� ���ڿ��� ��ȯ�� ���ڿ�����  
    
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
    
    //#if  

    
    
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
		ifct_element = ifctele_genElement(pIndex,age ,time, placeHist );  
		//element.c���Ϸ� �� ������ ��� ������ ������ ����ü�� ������.
		 
		ifctdb_addTail(ifct_element); 
		pTotal++; //��ü ȯ�ڼ� ī��Ʈ
		//�� �Լ��� �����ϸ� database.c�� ����ü�� ���� �� ����. 
		//ifct_element��� �����ʹ� �ٷ� ������  ifctele_genElement�Լ��� ���� ����ü������ �����ϰ��ִ� ����. 
		  
	}
   
	 
    //#endif
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
            {	
				//ifct_element                                                                                              => �״�� Ÿ����? 
            	printf("Patient index :");
                scanf("%d", &pIndex);//����ڷκ��� ȯ�ڹ�ȣ�� �Է¹���
   
    			if (pIndex >= 0 && pIndex < pTotal) //if (pIndex ��������� �����̸�)
    			
    //Ư�� ȯ�ڿ� ���� ���� ���
    //������ ȯ��(��ȣ �Է�)�� ���� ���� ����� ��ȣ, ����, ���� Ȯ������, �׸��� �ֱ� 5�� �̵���Ҹ� ��� 
                ifct_element = ifctdb_getData(pIndex);//pIndex ��° ȯ����������ü�� linked list�κ��� ������, 
														   //void*����ü�� (void*)ifct_element �����ͺ����� ��ȯ����.
                ifctele_printElement(ifct_element); //Ȯ���غ�����.  
    //�Ѹ��� ������ ����ϸ��. 
				
				//elif  (pIndex �ε�����ȣ ���� ��_(�ʹ� ũ�ų� �����϶�) / �����ڳ� Ư������)
				//print �����޼��� 
				break;
			}   
			
			
			
            case MENU_PLACE: //2
            {         
                cnt=0;
                int i; //Q2.�� ���� �÷����ϴ���? 
				printf("Place Name : ");
                scanf("%s",&placeName); //���ڿ��Է�  
				
				//�Է¹����� 
								
	//Ư�� ��ҿ��� (����)������ Ȯ�ε� ȯ�� ���� ���� ���
	//������ ���(���ڿ� ���·� �Է�)���� �ߺ� Ȯ���� �� ȯ�� ����� ���� ���
				
				//����ؾ��ϴ� ���� �������� ���� ����.=> for
				
				for(i=0;i<pTotal;i++)
				{	
					ifct_element = ifctdb_getData( i );//pIndex ��° ȯ����������ü�� linked list�κ��� ������, 
														   //void*����ü�� (void*)ifct_element �����ͺ����� ��ȯ����.
					//���ڿ��� ����� 
					//ifs_ele_t *strPtr = (ifs_ele_t *)obj
					HPlace= ifctele_getHistPlaceIndex (ifct_element,4);
					printf("%d",HPlace);
					//HPlaceName[100]=ifctele_getPlaceName(HPlace);
					if (strcmp(  placeName ,HPlaceName )==0 ) //place ? placeHist? 
					{																				//���ڿ� ��
						ifctele_printElement(ifct_element); //Ȯ���غ�����. 
	 					cnt++;
					}
	 				//else 
	 				//�ٽ� �ݺ�. 
	 				
				}
	 			
				//default //��Ÿ���ų� �����Է��ϰų� ������ ���� ���ÿ��� ����� �Ȱ�����µ�. 
				printf("There are %d patients detected in %s.\n",cnt, placeName);
				 break;
			}   
			
			
			
            case MENU_AGE: //3
            {
				  
				break;
			}
			    
				
				 
	//infected_pIndex , infected_time , infected_place ��������? get~�Լ� �Ἥ? 
            case MENU_TRACK: //4 //infectee , transmitter, frtInfectee
            { 	
	
				break; 
			}
			
			
			
            default: //�޴���ȣ �߸� �Է����� �� 
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        } //switch�� �������. 
    
    } while(menu_selection != 0); //do-while�� �������. 
    
    
    return 0;
} //main�Լ� ��. 


