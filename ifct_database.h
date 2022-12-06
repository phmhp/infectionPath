// 
//  ifct_database.h
//  infection Path
//
//  Created by Juyeop Kim on 2022/10/20.
//

#ifndef ifct_database_h
#define ifct_database_h

//여기 적힌 4개만 이용하면 됨.  
int ifctdb_addTail(void* obj);          //add data to tail 
//void* obj == 새로운 데이터 추가 
//linked list 자료구조에 집어넣을 데이터 (보통은 구조체로 집어넣음)  

int ifctdb_deleteData(int index);       //delete data 
int ifctdb_len(void);                   //get database length //몇개가 들어있냐 -> 출력으로 데이터의 개수이 나올 것.  
void* ifctdb_getData(int index);        //get index'th data //void포인터의 화살표를 반환 //택배상자를 가져온다 ~.... 

#endif /* ifct_database_h */
