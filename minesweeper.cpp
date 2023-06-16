#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<iomanip> 
using namespace std;
int end=0;
#define MINE 5 //地雷數量 
#define BORDER 7 // 地圖邊長 
struct Mine{
	int value=0;
	bool status=0;
	bool flag=0;
}mine[BORDER][BORDER]; //利用struct宣告地圖中所有位置，就可以包含其他資訊 

void calc(int x,int y,int z){ //(1.將地雷周圍數字+1)或(2.點開周圍的格子)的function(用int z來選擇)
	for(int i=x-1;i<=x+1;i++){
		for(int j=y-1;j<=y+1;j++){
			if(i<0 || i>=BORDER || j<0 || j>=BORDER || (i==x&&j==y)){ //當超出邊界或是該地雷位置時就跳過
				continue;
			}
			if(mine[i][j].value==9){continue;} //如果周圍有遇到地雷也跳過
			
			if(z==1){mine[i][j].value+=1;} //將地雷周圍數字+1
			else if(z==2){
				if(mine[i][j].value==0 && mine[i][j].status==0){//透過遞迴，自動展開所有附近沒有地雷的地方
					mine[i][j].status=1;
					calc(i,j,2);
				}
				mine[i][j].status=1;
			}
			
		}
	}
}

void boom(){ //顯示所有地雷位置 
	system("cls"); //先清螢幕 
	for(int i=0;i<BORDER;i++){
		cout<<setfill('-')<<setw(2*BORDER+1)<<""<<endl; //畫地圖邊界，會隨著地圖大小改變 
		cout<<"|";
		for(int j=0;j<BORDER;j++){
			if(mine[i][j].value==9){cout<<"*"<<"|";}//顯示所有地雷位置
			else if(mine[i][j].status==1){cout<<mine[i][j].value<<"|";}
			else{cout<<" "<<"|";}
		}
		cout<<endl;
	}
	cout<<setfill('-')<<setw(2*BORDER+1)<<""<<endl;
}

void map(int x,int y){ //畫地圖
	system("cls"); //先清螢幕 
	for(int i=0;i<BORDER;i++){
		cout<<setfill('-')<<setw(2*BORDER+1)<<""<<endl; //畫地圖邊界，會隨著地圖大小改變 
		cout<<"|";
		for(int j=0;j<BORDER;j++){
			if(i==x &&j==y){ //目前位置與旗子重疊(0)
				if(mine[i][j].flag==1){cout<<"Q"<<"|";}
				else{cout<<"O"<<"|";}
				continue;
			}
			if(mine[i][j].status==0){ //如果還沒點開來過，顯示空格或旗子
				if(mine[i][j].flag==1){cout<<"P"<<"|";}
				else{cout<<" "<<"|";}
			}
			else{ //如果點開來過，顯示該數字
				if(mine[i][j].value==0){calc(i,j,2);} //如果周圍都沒有地雷，就自動將周圍點開 
				else if(mine[i][j].value==9){ //踩到地雷 
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

int check(){ //檢查是否結局 
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
//前置作業(地圖建置)
	//隨機取地雷 
	srand(time(NULL));
	int i,j,temp;
	int num[MINE];
	for(i=0;i<MINE;i++){
	    temp = (rand()%(BORDER*BORDER)); //產生0~地圖邊長平方個數 
	    for(j=0;j<i;j++){
	        if(temp == num[j]){ //檢查亂數是否出現過 
	            i--; //如果有，就重新再跑一次 
	            break;
	        }
	    }
	    if(temp != num[j]) //確定沒有重複就將數字儲存下來 
	        num[i] = temp;
	        mine[temp/BORDER][temp%BORDER].value=9; //該數字對應到地圖中相應的位置，並將該位置的數值訂為9(地雷) 
	}
	//計算地雷以外的位置的數字 
	for(int i=0;i<BORDER;i++){
		for(int j=0;j<BORDER;j++){
			if(mine[i][j].value==9){calc(i,j,1);} //將地雷周圍的數字+1 
		}
	}
//開始遊戲 
	int k,posX=0,posY=0;
	map(posX,posY);
	while(true){
		if(end==1){cout<<endl<<"!!!!!Congratulation!!!!!"<<endl;break;}//判斷是否通關 
		else if(end==2){cout<<endl<<"~~~GAME OVER~~~"<<endl;break;}
		
		k = _getch();
		switch(k){		
			case 72: //鍵盤"上" 
				if(posX>0){posX--;}
				map(posX,posY);
				break;
			case 80: //鍵盤"下" 
				if(posX<BORDER-1){posX++;}
				map(posX,posY);
				break;
			case 75: //鍵盤"左" 
				if(posY>0){posY--;}
				map(posX,posY);
				break;
			case 77: //鍵盤"右" 
				if(posY<BORDER-1){posY++;}
				map(posX,posY);
				break;
			case 122: //鍵盤"Z" 
				if(mine[posX][posY].flag==0){mine[posX][posY].status=1;}
				map(posX,posY);
				end = check();
				break;
			case 120: //鍵盤"X" 
				if(mine[posX][posY].flag==0&&mine[posX][posY].status==0){mine[posX][posY].flag=1;}
				else if(mine[posX][posY].flag==1){mine[posX][posY].flag=0;}
				map(posX,posY);
				end = check();
				break;
		}
	}
} 
