// 
//  ifct_database.h
//  infection Path
//
//  Created by Juyeop Kim on 2022/10/20.
//

#ifndef ifct_database_h
#define ifct_database_h

//���� ���� 4���� �̿��ϸ� ��.  
int ifctdb_addTail(void* obj);          //add data to tail 
//void* obj == ���ο� ������ �߰� 
//linked list �ڷᱸ���� ������� ������ (������ ����ü�� �������)  

int ifctdb_deleteData(int index);       //delete data 
int ifctdb_len(void);                   //get database length //��� ����ֳ� -> ������� �������� ������ ���� ��.  
void* ifctdb_getData(int index);        //get index'th data //void�������� ȭ��ǥ�� ��ȯ //�ù���ڸ� �����´� ~.... 

#endif /* ifct_database_h */
