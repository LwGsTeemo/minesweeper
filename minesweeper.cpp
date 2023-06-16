#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<iomanip> 
using namespace std;
int end=0;
#define MINE 5 //�a�p�ƶq 
#define BORDER 7 // �a����� 
struct Mine{
	int value=0;
	bool status=0;
	bool flag=0;
}mine[BORDER][BORDER]; //�Q��struct�ŧi�a�Ϥ��Ҧ���m�A�N�i�H�]�t��L��T 

void calc(int x,int y,int z){ //(1.�N�a�p�P��Ʀr+1)��(2.�I�}�P�򪺮�l)��function(��int z�ӿ��)
	for(int i=x-1;i<=x+1;i++){
		for(int j=y-1;j<=y+1;j++){
			if(i<0 || i>=BORDER || j<0 || j>=BORDER || (i==x&&j==y)){ //��W�X��ɩάO�Ӧa�p��m�ɴN���L
				continue;
			}
			if(mine[i][j].value==9){continue;} //�p�G�P�򦳹J��a�p�]���L
			
			if(z==1){mine[i][j].value+=1;} //�N�a�p�P��Ʀr+1
			else if(z==2){
				if(mine[i][j].value==0 && mine[i][j].status==0){//�z�L���j�A�۰ʮi�}�Ҧ�����S���a�p���a��
					mine[i][j].status=1;
					calc(i,j,2);
				}
				mine[i][j].status=1;
			}
			
		}
	}
}

void boom(){ //��ܩҦ��a�p��m 
	system("cls"); //���M�ù� 
	for(int i=0;i<BORDER;i++){
		cout<<setfill('-')<<setw(2*BORDER+1)<<""<<endl; //�e�a����ɡA�|�H�ۦa�Ϥj�p���� 
		cout<<"|";
		for(int j=0;j<BORDER;j++){
			if(mine[i][j].value==9){cout<<"*"<<"|";}//��ܩҦ��a�p��m
			else if(mine[i][j].status==1){cout<<mine[i][j].value<<"|";}
			else{cout<<" "<<"|";}
		}
		cout<<endl;
	}
	cout<<setfill('-')<<setw(2*BORDER+1)<<""<<endl;
}

void map(int x,int y){ //�e�a��
	system("cls"); //���M�ù� 
	for(int i=0;i<BORDER;i++){
		cout<<setfill('-')<<setw(2*BORDER+1)<<""<<endl; //�e�a����ɡA�|�H�ۦa�Ϥj�p���� 
		cout<<"|";
		for(int j=0;j<BORDER;j++){
			if(i==x &&j==y){ //�ثe��m�P�X�l���|(0)
				if(mine[i][j].flag==1){cout<<"Q"<<"|";}
				else{cout<<"O"<<"|";}
				continue;
			}
			if(mine[i][j].status==0){ //�p�G�٨S�I�}�ӹL�A��ܪŮ�κX�l
				if(mine[i][j].flag==1){cout<<"P"<<"|";}
				else{cout<<" "<<"|";}
			}
			else{ //�p�G�I�}�ӹL�A��ܸӼƦr
				if(mine[i][j].value==0){calc(i,j,2);} //�p�G�P�򳣨S���a�p�A�N�۰ʱN�P���I�} 
				else if(mine[i][j].value==9){ //���a�p 
					boom();
					end=2;
					break;
				}
				cout<<mine[i][j].value<<"|";
				if(mine[i][j].flag==1){mine[i][j].flag=0;}
			}
		}
		if(end==2){break;}
		cout<<endl;
	}
	cout<<setfill('-')<<setw(2*BORDER+1)<<""<<endl;
}

int check(){ //�ˬd�O�_���� 
	int cnt=0;
	for(int i=0;i<BORDER;i++){
		for(int j=0;j<BORDER;j++){
			if(mine[i][j].status==0 && mine[i][j].flag==0){
				return 0;
			}
			if(mine[i][j].flag==1){cnt++;}
		}
	}
	if(cnt!=MINE){return 0;}
	return 1;
}

int main(){
//�e�m�@�~(�a�ϫظm)
	//�H�����a�p 
	srand(time(NULL));
	int i,j,temp;
	int num[MINE];
	for(i=0;i<MINE;i++){
	    temp = (rand()%(BORDER*BORDER)); //����0~�a���������Ӽ� 
	    for(j=0;j<i;j++){
	        if(temp == num[j]){ //�ˬd�üƬO�_�X�{�L 
	            i--; //�p�G���A�N���s�A�]�@�� 
	            break;
	        }
	    }
	    if(temp != num[j]) //�T�w�S�����ƴN�N�Ʀr�x�s�U�� 
	        num[i] = temp;
	        mine[temp/BORDER][temp%BORDER].value=9; //�ӼƦr������a�Ϥ���������m�A�ñN�Ӧ�m���ƭȭq��9(�a�p) 
	}
	//�p��a�p�H�~����m���Ʀr 
	for(int i=0;i<BORDER;i++){
		for(int j=0;j<BORDER;j++){
			if(mine[i][j].value==9){calc(i,j,1);} //�N�a�p�P�򪺼Ʀr+1 
		}
	}
//�}�l�C�� 
	int k,posX=0,posY=0;
	map(posX,posY);
	while(true){
		if(end==1){cout<<endl<<"!!!!!Congratulation!!!!!"<<endl;break;}//�P�_�O�_�q�� 
		else if(end==2){cout<<endl<<"~~~GAME OVER~~~"<<endl;break;}
		
		k = _getch();
		switch(k){		
			case 72: //��L"�W" 
				if(posX>0){posX--;}
				map(posX,posY);
				break;
			case 80: //��L"�U" 
				if(posX<BORDER-1){posX++;}
				map(posX,posY);
				break;
			case 75: //��L"��" 
				if(posY>0){posY--;}
				map(posX,posY);
				break;
			case 77: //��L"�k" 
				if(posY<BORDER-1){posY++;}
				map(posX,posY);
				break;
			case 122: //��L"Z" 
				if(mine[posX][posY].flag==0){mine[posX][posY].status=1;}
				map(posX,posY);
				end = check();
				break;
			case 120: //��L"X" 
				if(mine[posX][posY].flag==0&&mine[posX][posY].status==0){mine[posX][posY].flag=1;}
				else if(mine[posX][posY].flag==1){mine[posX][posY].flag=0;}
				map(posX,posY);
				end = check();
				break;
		}
	}
} 
