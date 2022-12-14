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


int pTotal; //��ü ȯ�� ��  
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
        
        
        //�����͸� �Լ��̿��ؼ� �Ѱ��ָ� �Լ������� ����ü ��� ���� �� ���� ��ȯ����.  
        switch(menu_selection)
        {	
			case MENU_TRACK: //4
			 {	//���� ���� ����(start)
			 	int i;
			 	void *infectee;
			 	int infecteeDT; //Detected Time
			 	int *detected_time;
			 	int infecteeDP; //Detected Place
			 	int *detected_place;
			 	
			 	
			 	
			 	//���� ���� ���� (end) 
			 
			 	printf("Patient index : "); 
            	scanf("%d",&pIndex);
			 	
			 	ifct_element = ifctdb_getData(pIndex);
			 	infectee = (void *)ifct_element;
			 	if (infectee != NULL ) { //while���� ���ѹݺ������ʵ���.. 
			 		
			 		infecteeDT = ifctele_getinfestedTime(infectee) ;
            		detected_time = &infecteeDT;
			 		infecteeDP = ifctele_getHistPlaceIndex(infectee, i );
					detected_place = &infecteeDP;
			 		int transmitterpIndex;
			 		
					 
					 
					 
					///�ٽ� �����ؾ��� �κ�(isMet�Լ� �׽�Ʈ ����) 
					 ///////////////
			 		void *temp ; 
			 		int ttime;
					temp =  ifctdb_getData(2);
			 		ttime=isMet(infectee,temp);
			 		printf("main �Լ��� ttime= %d\n" , ttime);
			 		////////////
			 		
			 		
			 		
			 		
			 		//transmitterpIndex = trackInfester(pIndex,detected_time ,detected_place);			//{int trackInfester(int patient_no, int *detected_time, int *place)
					//printf("transmitterpIndex = %d", transmitterpIndex);
				 }
			 	
			 	
			 	
			 break;   
			}
				
       } //switch�� ��  	
    
    } while(menu_selection != 0); //do-while�� ��  
    
    
    return 0;
}//main�Լ� ��  






//
/*
int trackInfester(int patient_no,int *detected_time , int *place) //������Ÿ�Կ� �̷��� ������. 
{	//���� ���� ���� 
	int i; 
	void * infectee_track;
	void * ith_track; 
	int current_metTime = -1;
	 
	//���� ���� ���� 
	//int pIndex = patient_no; //�߰� �� ���� (patient_no =>pIndex 
	
	
	
	infectee_track = ifctdb_getData(patient_no); 

	for (i=0;i<pTotal;i++) //ȯ�� ��ü �ο���ŭ �ݺ� 
		
	{	
		ith_track = ifctdb_getData(i);
		//printf("track count : %d \n",i);
		printf("here\n");
		//current_metTime = isMet (infectee_track, ith_track); //����ȯ�ڶ� i��° ȯ�ڶ� ���� ���� (���� �����ִ� for������ �ٷ� ã�Ƴ� ���
		 
	}
 	
}

*/







//

int isMet( void *infectee_ptr, void * suspect_ptr) //����ȯ��,i��° ȯ�� �޴°Ŷ�� �����ڵ忡 ��������.  
{	//���� ���� ���� 
	int i; 
	void * infectee;
	infectee = (void *)infectee_ptr;
	void * suspect;
	suspect = (void*)suspect_ptr;
	int infectee_ithPlaceTime;
	int suspect_ithPlace;
	int infectee_ithPlace; 
	int suspect_infestedTime;	
	
	int metTime_isMet =-1;
	
	//���� ���� ���� 
	
	 
	for (i=0; i<3; i++){
		//���� ȯ���� i��° �̵���� ���� ���
		//=> ȯ�� ������ +�ε��� -4
		//=>   ifctele_getinfestedTime(infectee) + i -4 
		printf("--------------------------------------------------------------------------------------------------";) 
		infectee_ithPlaceTime = (ifctele_getinfestedTime(infectee))+i-4;
		printf("1_ ����ȯ���� i��° �̵���� ���� ���  = infectee_ithPlaceTime = %d \n", infectee_ithPlaceTime);//����� �� 	
		
		
		//���� ���������� ���ȯ�� �̵���� ���
		suspect_infestedTime = ifctele_getinfestedTime(suspect);
		printf("2_ ���� ���������� ���ȯ�� �̵� ��� ���(���� �غ�) = suspect_infestedTime = %d \n", suspect_infestedTime);//����� ��  
		
		//���� ���������� ���ȯ�� �̵���� ��� 
		suspect_ithPlace = convertTimeToIndex( infectee_ithPlaceTime, suspect_infestedTime );
		printf("3_ ���� ���������� ���ȯ�� �̵���� ���  = suspect_ithPlace = %d \n", suspect_ithPlace);  //error
		
		
		//���� ȯ���� i��° �̵� ��� (if���� ���� �ʿ��� ���� ����)
		infectee_ithPlace = ifctele_getHistPlaceIndex(infectee, i );
		printf("4_ ���� ȯ���� i��° �̵���� ��� infectee_ithPlace = %d \n ",infectee_ithPlace); //����� ��  
		
		
		
		
		//if ���� ȯ���� i��° �̵���� ==���ȯ�ڟ� �ش���� �̵���� ��� 
		//��� �ε��� ��ȣ�� ��  
		if (infectee_ithPlace  == suspect_ithPlace )
		{	
			
			//���� �ð� = i��° �̵���� ���� ; 
			metTime_isMet = infectee_ithPlaceTime;
			printf("���� �ð� = metTime_isMet = %d \n", metTime_isMet); 
		}
	}
	
	
	
	return metTime_isMet;
} 



int convertTimeToIndex( int time, int infestedTime) 
{	//printf("\n\n\ntime =%d\n",time); //����� ����  
	//printf("infestedTime = %d\n\n\n",infestedTime); //����� ����  

	int index =-1;

	if (time <= infestedTime && time> infestedTime - N_HISTORY)
	{	//printf("here is convert\n");
		index = N_HISTORY-(infestedTime-time)-1;
	}

	//printf("in convert, index = %d \n", index);
	return index;
}

