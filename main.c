//�ֱ�  ���� ��¥: 2022.12.08

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


int earliest_time=100;
int pTotal; //��ü ȯ�� ��  
///////////////////////



int trackInfester(int patient_no, int *detected_time, int *place);
//int isMet();

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    ////////////////////////////
  
    
    int minAge,maxAge; //�޴� 2��
	char placeName[MAX_PLACENAME]; //�޴� 2��-���ڿ� �Է¹��� �� ���
	int cnt; //�޴� 2��,3������ ���. (����� �ο� �� ��)
	int HPlace;//�����ͷ� �̵���� �� �ϳ� (���� ��ȣ) �޾ƿ� ����������
	char HPlaceName[MAX_PLACENAME];//HPlace�� �̵���� �� �ϳ�(���ù�ȣ)�� ��ġ�Ǵ� ���ڿ��� ��ȯ�� �� ����� ���ڿ�
	

    
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
		int i=0;
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
        
        
        //�����͸� �Լ��̿��ؼ� �Ѱ��ָ� �Լ������� ����ü ��� ���� �� ���� ��ȯ����.  
        switch(menu_selection)
        {
            case MENU_EXIT: //0
                printf("Exiting the program... Bye bye.\n");
                break;
                
 //Ư�� ȯ�ڿ� ���� ���� ���  		
//������ ȯ��(��ȣ �Է�)�� ���� ���� ����� ��ȣ, ����, ���� Ȯ������, �׸��� �ֱ� 5�� �̵���Ҹ� ���           
			case MENU_PATIENT: //1  //�ϼ�! 
            {	//ifct element
				printf("Patient index : ");
				scanf("%d", &pIndex); 
				if (pIndex >= 0 && pIndex < pTotal) //if (pIndex ��������� �����̸�)
				 
				ifct_element = ifctdb_getData(pIndex); //pIndex��° ȯ����������ü�� linked list���� ������, void�����ͱ���ü�� ifct_element �����ͺ����� ��ȯ.
				ifctele_printElement(ifct_element);//pIndex��° ȯ������ ��� 
				
				//else (pIndex �������/������/����...) 
				//print �����޽���     
                break;
        	}
        	
//Ư�� ��ҿ��� (����)������ Ȯ�ε� ȯ�� ���� ���� ���
//������ ���(���ڿ� ���·� �Է�)���� �ߺ� Ȯ���� �� ȯ�� ����� ���� ���
            case MENU_PLACE: //2 //�ϼ�!!
            {	cnt=0;
				int i;
				printf("Place Name : ");
				scanf("%s",&placeName); //���ڿ� �Է¹ޱ�
				
				//�Է¹�����... 
				//��� �� ���� ���� ���..=>for loop
				for (i=0;i<pTotal;i++)
				{
					ifct_element = ifctdb_getData(i);//pIndex��° ȯ����������ü�� linked list�κ��� ������ ifct_element�����ͺ����� ��ȯ
					
					//���ڿ��� �����
					HPlace = ifctele_getHistPlaceIndex (ifct_element,4);//���������� ��ҹ�ȣ �˷��ִ� �Լ��� ���� HPlace�� �� ��ҹ�ȣ���� 
					strcpy(HPlaceName, (ifctele_getPlaceName(HPlace)));
					
					//printf("%d\n",HPlace); //test 
					//printf("%s\n",HPlaceName);//test
					
					
					//char* ifctele_getPlaceName(int placeIndex) 
					//int ifctele_getHistPlaceIndex(void* obj, int index)
					
					
					if (strcmp(placeName,ifctele_getPlaceName(ifctele_getHistPlaceIndex(ifct_element, 4)))==0) //�Է¹��� ��Ұ� �������� ������ �̵���ο� ���� ���
					{
						ifctele_printElement(ifct_element);
						cnt++; //�ش���ҿ��� ������ ��� ���� ī��Ʈ +1  
						
					}
					//else
					//�ٽ� ã�ƺ���  
				}  
				//��Ÿ/����/�����ھ��� ������ ��쵵 �����. 
				printf("There are %d patients detected in %s.\n",cnt, placeName);
                break;
        	} 
        	
//Ư�� ������ ���̿� �ش��ϴ� ȯ�� ���� ���� ���
//Ư�� ���� ���̴� �ּ� �� �ִ� ���� �Է� ������, �ּҰ� �̻��̸鼭 �ִ밪 ���� ������ ȯ�� ����� ���� ���
            case MENU_AGE: //3   //�ϼ�!!! 
            {	int i;
			 
				printf("minimal age : ");
                scanf("%d",&minAge);
                printf("maximal age : ");
                scanf("%d", &maxAge); 
            
				//���������� �۵��ϴ� ���
				for(i=0;i<pTotal;i++)
				{
					ifct_element = ifctdb_getData(i); //pIndex��° ȯ����������ü�� linked list�κ��� ������.   
					if ( ifctele_getAge(ifct_element) >= minAge   &&   ifctele_getAge(ifct_element) <=  maxAge) 
					{
						ifctele_printElement(ifct_element); 
						cnt++;
					}
					
				//�ش� ������� ���� ��� (minAge==maxAge�� ��, �Է°� �� �� 0�϶�=>����ü����� �ȵ����� �Ʒ������� ��µ�.
				
				}    
				printf("There are %d patients whose age is between %d and %d.\n", cnt, minAge, maxAge);
				//else =>�Է°��� ������ �̻��� �� (�����̰ų� �ּҰ��� �ִ밪���� Ŭ ��) 
                //print �����޽���  
                break;
        	} 
        	
//���� ��� �� ���� ������ ����				 
//������ ȯ�ڸ� �������� �����ڿ� �������� ���� �� ��Ҹ� ������ ����ϰ� ���� �����ڸ� ���������� ���		 
            case MENU_TRACK: //4  
            {	int i;
				printf("Patient index :");
				scanf("%d",&pIndex); 
				//else patient index�� ������/�ʹ� ū �� �Է½� 
				//print �����޼���  
				ifct_element = ifctdb_getData(pIndex);
//�˰��� 
/* 15���� �����̵� p.15
	���������� �����ڸ� ã�ư�
	�ݺ����� ���� ���� ȯ���� �����ĸ� �ݺ������� ã��
	���̻� �����ڰ� ������ ���� ȯ�ڸ� ���� �����ڷ� ����*/
////////////////////////////////////////////////////////////////////////////	
				
				//����ȯ�� = �Է°�;
				
				//while (����ȯ�ڰ� ������ ����)
				
				{
					//������ = trackInfester(����ȯ��);
			
					//if (�����ڰ� ������)
			
						//printf(��%i ȯ�ڴ� %i ȯ�ڿ��� ���ĵ�\n��, ����ȯ��, ������);
			
				
					//else
						//���������� = ����ȯ��;
				
				//����ȯ�� = ������;
				
				}
/////////////////////////////////////////////////////////////////////////////	

                break;    
        	}
        	
        	
        	
        	
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
       }//switch�� ��  
    
    } while(menu_selection != 0); //do-while�� ��  
    
    
    return 0;
}//main�Լ� ��  



///////////////////////////           �߰��� �Լ�           ////////////////////////////////////////////////







int trackInfester(int patient_no, int *detected_time, int *place)
{ /*
	 15���� �����̵� p.16
	trackInfester() : �� ȯ�ڿ� ���� �������� ������ �־��������� Ȯ��
	isMet() : �� ȯ�ڰ� ���� �ð��� �����ϴ� �Լ�
	�ȸ������� -1 ��ȯ
	���� ȯ�� �� ���� �̸� �ð��� ���� ȯ�ڸ� �����ڷ� ����
*/
////////////////////////////////////////////////////////////////////////////
	//for (i��° ȯ��)
	
	{
		//�����ð� = isMet(����ȯ��, i��° ȯ��);
	
		//if ( �����ð�> 0) //�����ٸ�
	
		{
			//if (���ݱ��� ȯ�� �� �����ð��� ���� �̸���?)
	
			{
				//������ = i;
	
			}
		}
	}
	//return ������;
	
////////////////////////////////////////////////////////////////////////////
}








int isMet( )
{/* 
	 15���� �����̵� p.17
	isMet() : ��ȯ���� ���� ���� ���
	���� �ð��� ������� �ӹ��� ��� �� ���� ���
	Ư�� �ð� ������ ���� ��ҿ� �־����� Ȯ��
*/
//////////////////////////////////////////////////////////////////////////////
	
	//for (i=2;i<N_HISTORY;i++)
	{
		//����ȯ���� i��° �̵���� ���� ���;
	
		//���� ���������� ���ȯ�� �̵���� ���;
	
		//if (i��° �̵���� == ���ȯ�� �̵����)
		{
			//�����ð� = i��° �̵���� ����;
	
		}
	}
	//return �����ð�;
		
		
//////////////////////////////////////////////////////////////////////////////
}







int convertTimeToIndex(int time, int infestedTime ) 
{	// 15���� �����̵� p.18
	//���� ���� ���� ��� �迭�� index�� �����ϴ� �Լ�
	//����
	//�������� : 13, �˰���� ���� : 11, index : 5 - (13-11)-1 = 2
	//�ش� ������ ���� ��� ������ ������ -1 ��ȯ
	int index =-1;
	
	if (time <= infestedTime && time <infestedTime-N_HISTORY)
	{
		index = N_HISTORY-(infestedTime-time)-1;
	}
	return index;
}


