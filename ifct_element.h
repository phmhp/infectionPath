//최근  수정 날짜: 2022.12.07
 

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

void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]); //수업시간에 함. 
char* ifctele_getPlaceName(int placeIndex); //수업시간에 함. 
int ifctele_getHistPlaceIndex(void* obj, int index); //13주차 4번 참고. 
unsigned int ifctele_getinfestedTime(void* obj); //13주차 4번 참고. 
int ifctele_getAge(void* obj); //13주차 4번 참고. 
void ifctele_printElement(void* obj); //13주차 5번 참고. 
#endif /* ifct_element_h */
