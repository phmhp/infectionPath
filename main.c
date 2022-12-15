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

//�������� ����  
int pTotal; //��ü ȯ�� ��=> �ٸ� �Լ�( trackInfester() )������ ����ؼ� ���������� ����  

int trackInfester(int patient_no, int *detected_time, int *place); // trackInfester() ����  
int isMet( void *infectee_ptr, void * suspect_ptr); //isMet() ���� 

int main(int argc, const char * argv[]) 
{	//�⺻ ����  
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];

    //�޴� ���� ���� 
    int i; 
	int cnt=0; //����� �ο� �� �� ��� (menu 2, 3) 	
	
	//�޴� 2�� ����
	char placeName[MAX_PLACENAME]; //��� ���ڿ� �Է¹��� �� ���  
	int HPlace;//��� ��ȣ  
	char HPlaceName[MAX_PLACENAME];//HPlace�� ���ڿ��� ��ȯ�� �� ���  
	
	//�޴� 3�� ����
	int minAge,maxAge; //�ּ� ����, �ִ� ���� 

	//�޴� 4�� ����
	void *infectee; //���� ȯ�� ���� ������ ������  
	int infecteeDT; //����ȯ���� Detected Time
	int *detected_time; //infecteeDT ����ų ������  
	int infecteeDP; //Detected Place
	int *detected_place; //infecteeDP ����ų ������  
	int transmitterpIndex = -1; //������(���ȯ��)�� ȯ�� �ε�����ȣ (�ʱⰪ ������ �����ؼ� �����ڰ� �ִ��� ������ ����) 
	int metTime, metPlace; //���� ����, ���� ��� (��������) 
	void *transmitter; //��� ȯ�� ���� ������ ������  
	int metPlaceIndex; //���� ��� ���� ��ȣ 
	//void *frtInfectee; //ù ������ ���� ������ ������  
	int metHistIndex; //���� ������ ���° [�ε���]���� ����  
	int firstpIndex; //�Է°����� ���� ù ����ȯ��  
	int lastpIndex = -1; // ���� ���� ������ �������� ȯ�� �ε��� ( �ʱⰪ ������ �����ؼ� �Է°����� ù �����ڸ� �Է¹������� , �ݺ���ô�ؼ� ���������(=ù ������)�� ã������ ����) 
	int loopcnt=0; //������ ã�� loop�� �ݺ��� Ƚ��  
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r"); //������ ��  
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    
    //1-2. loading each patient informations
    //while���� �ѹ� �� �� ȯ�������� ����ü�� ���� linked list�� �ִ� ������ ��.
	while (3==fscanf(fp,"%d %d %d", &pIndex,&age,&time)) 
	{
		
		for (i=0;i<N_HISTORY;i++)//for loop���� �����о���̰� ifctele_genElement�Լ��� ����. 
		{
			fscanf(fp,"%d",&placeHist[i]); //fscanf�� �޾ƿ� ���� ��Ƽ� ������������ü�� �������. 
		}
		ifct_element = ifctele_genElement(pIndex,age,time,placeHist);//element.c���Ϸ� ������ ����ü������.
	
		ifctdb_addTail(ifct_element); //database.c�� ����ü ����.(linked list�� �߰�) //ifct_element�� ����ü�� ������ �ִ� ����. 
		pTotal++; //��ü ȯ�� �� ī��Ʈ  	
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
        	}
        	
			//------------- MENU 1  --------------           
			case MENU_PATIENT:   
            {	
            		
				printf("Patient index : ");
				scanf("%d", &pIndex); 
				
				//�Է°� ����ó�� (start)
				if (pIndex >= pTotal) //ȯ�� �ε��� ��ȣ�� �ʰ����� ��  
				{	printf("[ERROR] Your input for the patient index (%d) is wrong! input must be 0 ~ 4\n",pIndex);
					break;
				}
				else if (pIndex < 0) //���� �Է� �� 
				{	//ifctdb_getData(pIndex);
					printf("There is no element of index %d.\n",pIndex);
					break;
				} 
				//�Է°� ����ó�� (end)  
				
				//���������� �۵��ϴ� ���  
				else if (pIndex >= 0 && pIndex < pTotal) 
				{  
					ifct_element = ifctdb_getData(pIndex); //�����͸� �Լ� �Ű������� �Ѱ��ָ� �Լ������� ����ü ��� ���� �� ���� ��ȯ����.
													   	   //pIndex��° ȯ����������ü�� linked list���� ������, void*����ü�� ifct_element ������ ������ ��ȯ.
					ifctele_printElement(ifct_element); //pIndex��° ȯ������ ���      
                	break;
            	}
        	}
			
			//------------- MENU 2  --------------
            case MENU_PLACE: 
            {	cnt=0; //�� �ʱ�ȭ  
				
				printf("Place Name : ");
				scanf("%s",&placeName); //���ø�(���ڿ�) �Է¹ޱ�
				for (i=0;i<pTotal;i++) //�ش� ���ÿ��� ������ ��� ã�����ؼ� ȯ�� ��ü ����ŭ �ݺ�  
				{
					ifct_element = ifctdb_getData(i); //i��° ȯ�� ���� �����Ϳ� ���  
 
					HPlace = ifctele_getHistPlaceIndex (ifct_element,4);//i��° ȯ���� �������( [4] ) ��ȣ ����  
					strcpy(HPlaceName, (ifctele_getPlaceName(HPlace))); //���Ŀ� �Է¹��� ��� ���ڿ�(placeName)�� ���ϱ� ���ؼ� ���ڿ��� ����  
			
					if (strcmp(placeName,ifctele_getPlaceName(ifctele_getHistPlaceIndex(ifct_element, 4)))==0) //�Է¹��� ��� ���ڿ��� i��° ȯ���� ������� ( [4] )�� ���ٸ�  
					{
						ifctele_printElement(ifct_element);
						cnt++; //�ش���ҿ��� ������ ��� ���� ī��Ʈ +1  
					}
				}  
				printf("\nThere are %d patients detected in %s.\n",cnt, placeName); //�ش� ��ҿ��� ������ ��ü ��� �� ���  
                break;
        	} 
        	
        	//------------- MENU 3  --------------
            case MENU_AGE: 
            {	
				cnt =0; //�� �ʱ�ȭ 
				printf("minimal age : ");
                scanf("%d",&minAge);
                printf("maximal age : ");
                scanf("%d", &maxAge); 

                //�Է°� ����ó��  (start) 
            	if (minAge < 0 || maxAge <0 ||minAge >maxAge) // �ּҰ�,�ִ밪���� ��ȣ�� ������µ� ��� Ȥ�� �ּҰ��� �ִ밪���� ū ���     
				{	
					printf("[ERROR] input age (%d , %d) is wrong!\n",minAge,maxAge);
					break;
				}
				//�Է°� ����ó��(end) 
				
					
				//���������� �۵��ϴ� ���
				for(i=0;i<pTotal;i++)
				{
					ifct_element = ifctdb_getData(i);
					if ( ifctele_getAge(ifct_element) >= minAge   &&   ifctele_getAge(ifct_element) <=  maxAge)  //i��° ȯ���� ���̰� �ּҰ��̻� �ִ밪������ ���  
					{
						ifctele_printElement(ifct_element); 
						cnt++; //�ش� ���� ������ ���ϴ� ȯ�� �� +1  
					}	
				}    
				printf("There are %d patients whose age is between %d and %d.\n", cnt, minAge, maxAge); //�ش� ���� ������ ���ϴ� ȯ�� �� ���  
                break;
        	} 
        	
        	//------------- MENU 4  --------------
			case MENU_TRACK:
			 {	 
			 	printf("Patient index : "); 
            	scanf("%d",&pIndex);
            	if (pIndex >= pTotal) //ȯ���ε�����ȣ�� ���� �ʰ��ϴ� �� �Է����� ���   
				{	printf("[ERROR] Your input for the patient index (%d) is wrong! input must be 0 ~ %d\n", pIndex,pTotal-1);
					break;
				}
			 	firstpIndex = pIndex; //�������� ����� �� ����ϱ� ���� ù��° �Է°� ����  
			 	
			 	//ȯ������ ��������  
			 	ifct_element = ifctdb_getData(pIndex);
				infectee = (void *)ifct_element;
			 	
				
				 while ( pIndex >=0 ) //���� ȯ�ڰ� �ִ� ���ȿ��� �ݺ�  
				{ 	 transmitterpIndex= -1;
			 		infectee= ifctdb_getData(pIndex); //�ݺ��ϸ鼭 ����ȯ�ڰ� �ٲ���� ���� ������ �ٽ� ȯ������ ������  
			 		
			 		infecteeDT = ifctele_getinfestedTime(infectee);//����ȯ���� �������� 
            		detected_time = &infecteeDT;//trackInfester�Լ��� �Ű������� ���� ���� �����Ϳ� ����  
			 		infecteeDP = ifctele_getHistPlaceIndex(infectee, 4 ); //����ȯ���� �������  
					detected_place = &infecteeDP; //trackInfester�Լ��� �Ű������� ���� ���� �����Ϳ� ����  
			 		transmitterpIndex = trackInfester(pIndex,detected_time ,detected_place); //trackInfester �Լ� ��������� ���ȯ�� �ε�����ȣ ����  
					
					if (transmitterpIndex >= 0) //������ ������ (�ʱⰪ -1���� �ٲ������) 
					{	
						transmitter = ifctdb_getData(transmitterpIndex); //������ ���� ��������  
						metTime =isMet(infectee,transmitter); //�����ڿ� ��������  
						metHistIndex =  metTime-infecteeDT+4;// �����ڿ� ���������� �ε��� 
						metPlaceIndex= ifctele_getHistPlaceIndex(infectee,metHistIndex);  //�����ڿ� ���������� �ε����� ����ִ� ���ù�ȣ  
						printf(" --> [TRACKING] patient %d is infected by %d (time : %d, place : %s)\n", 
								                    	ifctele_getpIndex(infectee), transmitterpIndex, metTime ,ifctele_getPlaceName(metPlaceIndex)); //����ȯ���ε�����ȣ,�������ε�����ȣ,��������,�������(���ڿ�) 
						
						//���� �����ڸ� ã�� ���ؼ� '����ȯ��'�� ������ ���� �ֱ� 
						pIndex = ifctele_getpIndex(transmitter);   
						infectee = (void *)transmitter ; 
						lastpIndex = pIndex; //���� �ֱ� ȯ�� �ε�����ȣ�� ������Ʈ (�Ѹ��̶� ����ȯ�ڰ� �ִ� ��쿡�� 0�̻��� ����) 
						loopcnt ++; //������ ã�� Ƚ�� ī��Ʈ +1 
					}	
					else if (transmitterpIndex == -1 )//������ ������ (�ʱⰪ �״�� -1�̸�)
					{   
						if (loopcnt==0 ) //�ƿ� ù �������� ���  
						{		
							printf("%d is the first infector!!\n", ifctele_getpIndex(infectee));
							pIndex =-1; //while���� ������ ���� -1 ���� 
						} 
						else if (loopcnt > 0 ) //������ ������ ����� ��� (ex-�������� �������� �������� ��������....... 
						{
							pIndex =-1; //whle���� ������ ���ؼ� -1 ���� 
							printf("The first infector of %d is %d\n" , firstpIndex,lastpIndex);
						}
					} 
					
				}//while ��  ��  
				break; 
       		}//case MENU_TRACK: ��  
		    default:
		        printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
		        break;
		}//switch�� ��  
	}	while(menu_selection != 0);  //do-while�� �� 
	
	
	
	
	
	
	
	

	}








   	return 0;	
}//main�Լ� ��  










//--------------------------- trackInfester function  ------------------------------  
int trackInfester(int patient_no,int *detected_time , int *place)  
{	
	//���� ���� ���� 
	int i; 
	void * infectee_track; //���� ȯ��  
	void * ith_track;  //��� ȯ��  	
	int current_metTime = -1; //���� �����ִ� loop�� ���� ���� (�ȸ��� ��쿡�� �ʱⰪó�� -1) 
	int metTime_record =1000; //���� ������ �߿� ���� �̸� ������ �����ϴ� ����(���ذ��鼭 ���� �� �̸� ������ ����Ǵ� ����)  
	int passing_pIndex = -1; //��ȯ��(�������� ȯ���ε��� ��ȣ)  
	//���� ���� ���� 

	infectee_track = ifctdb_getData(patient_no); //����ȯ�� ���� ��������  

	for (i=0;i<pTotal;i++) //������ ã�� ���� ȯ�� ��ü �ο���ŭ �ݺ� 	
	{	
		ith_track = ifctdb_getData(i); //i��° ȯ�� ���� �������� 
		current_metTime = isMet (infectee_track, ith_track); //���� �����ִ� loop���� ����ȯ�ڶ� i��° ȯ�ڰ�  ���� ���� 
		if (current_metTime > 0 ) //���� ȯ�ڿ� i��° ȯ�ڰ� ���� ���� ������  
		{	if (current_metTime < metTime_record)  //���� ���� �������� ���غ���  
			{
				metTime_record = current_metTime; 
				passing_pIndex = ifctele_getpIndex(ith_track); //���� ���� ������ ������ �� ������ ������ ������(���絹���ִ� loop�� i��° ȯ��)�� �ε�����ȣ�� ��ȯ�ϱ����� ����  
			}			
		}
	}
	
 	return passing_pIndex; //������ ȯ���ε��� ��ȣ ��ȯ 
}









//--------------------------- isMet function  ------------------------------  
int isMet( void *infectee_ptr, void * suspect_ptr) 
{	//���� ���� ���� 
	int i; 
	int k;
	void * infectee; //����ȯ��  
	infectee = (void *)infectee_ptr;
	void * suspect; //���ȯ��  
	suspect = (void*)suspect_ptr;
	int infectee_ithPlaceTime; //����ȯ���� i��° ��� ����  
	int suspect_ithPlace; //���ȯ���� i��° ���  
	int infectee_ithPlace; //����ȯ���� i��° ��� 
	int suspect_infestedTime; //���ȯ���� ��������  
	
	int ithTime; //
	int kthTime; //
	
	int suspect_kthPlace; 
	int metTime_isMet =-1;
	
	//���� ���� ���� 
	
	 
	for (i=0; i<3; i++) //����ȯ�ڰ� ������ �� �ִ� �������� �ݺ� ( [0], [1], [2] ) 
	{
		infectee_ithPlace = ifctele_getHistPlaceIndex(infectee, i );  	//���� ȯ�ڰ� i��°�� �ִ� ��� 
		for (k= 3; k<N_HISTORY;k++) //���ȯ�ڰ� ������ų �� �ִ� �������� �ݺ� ( [3], [4] ) 
		{
			suspect_kthPlace = ifctele_getHistPlaceIndex(suspect, k );	//���ȯ�ڰ� k��°�� �ִ� ���
			if ( infectee_ithPlace == suspect_kthPlace )	//���� ��ҿ� �ִ� ���� �´ٸ� => //���� �������� �� 
			{
				//����ȯ�� i��° ��ҿ� �ִ� ���� = �����������Լ�(����ȯ��)+i-4;
				ithTime=ifctele_getinfestedTime(infectee)+i-4;
				//���ȯ�� i��° ��ҿ� �ִ� ���� = �����������Լ�(���ȯ��)+k-4;
				kthTime=ifctele_getinfestedTime(suspect)+k-4;
				
				
				if (ithTime ==kthTime)//������ ���ٸ�  
				{
				 	metTime_isMet = ithTime ; //���� �ð�==ithTime ==kthTime 
				} 
			}
		}
	}	 
	return metTime_isMet;  
}




