//�ֱ�  ���� ��¥: 2022.12.07
 

//  ifct_element.h
//  infection path
//
//  Created by Juyeop Kim on 2022/10/20.
//

#ifndef ifct_element_h
#define ifct_element_h

#define N_PLACE                     40
#define N_HISTORY                   5
#define MAX_PLACENAME               100

void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]); //�����ð��� ��. 
char* ifctele_getPlaceName(int placeIndex); //�����ð��� ��. 
int ifctele_getHistPlaceIndex(void* obj, int index); //13���� 4�� ����. 
unsigned int ifctele_getinfestedTime(void* obj); //13���� 4�� ����. 
int ifctele_getAge(void* obj); //13���� 4�� ����. 
void ifctele_printElement(void* obj); //13���� 5�� ����. 
#endif /* ifct_element_h */
