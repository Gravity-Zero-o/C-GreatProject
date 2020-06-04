#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;
fstream in;
class City
{
private:
	int number;
	char name[25];
	int x,y;
public:
	City(int num=1000,char na[25]=" ",int xpos=0,int ypos=0)
	{
		number=num;
		strcpy(name,na);
		x=xpos;y=ypos;
	}
	void setNumber(int num)
	{
		number=num;
	}
	void setName(char *na)
	{
		strcpy(name,na);
	}
	void setPosition(int xpos,int ypos)
	{
		x=xpos;y=ypos;
	}
	void getName(char *);
	int getNum()
	{
		return number;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	void show()
	{
		cout.setf(ios::left,ios::adjustfield);
		cout<<setw(8)<<number<<setw(10)<<name<<setw(5)<<x<<setw(5)<<y<<endl;
	}
	friend class Map;
};
void City::getName(char *na)
{
	strcpy(na,name);
}
class Map
{
private:
	City *cities;
	int curCounter,maxCounter;
public:
	Map(int maxc=10)
	{
		curCounter = 0;
		maxCounter = maxc;
		if (maxc)
			cities = new City[maxCounter];
		else
			cities = NULL;
	}
	void ReadCity(char *filename)
	{
		fstream in;
		in.open(filename,ios::in);
		while(!in.eof())
		{
			if(curCounter==maxCounter)
			{
				City *newcities;
				newcities=new City[maxCounter+10];
				for(int i=0;i<curCounter;i++)
				{
					newcities[i]=cities[i];
				}
				delete []cities;
				maxCounter=maxCounter+10;
				cities=newcities;
			}
			in>>cities[curCounter].number>>cities[curCounter].name>>cities[curCounter].x>>cities[curCounter].y;
			curCounter++;
		}
		in.close();
	}
	void ImportDataBase()
	{
		
		in.open("append.txt",ios::in);
		if(in)
		{
			ReadCity("append.txt");
		}
		in.close();
	}
	Map(Map &m)
	{
		cities=new City[maxCounter];
		for(int i=0;i<maxCounter;i++)
		{
			cities[i]=m.cities[i];
			curCounter=m.curCounter;
			maxCounter=m.maxCounter;
		}
	}
	~Map()
	{
		delete [] cities;
	}
	double Distance(int x1,int y1,int x2,int y2)
	{
		double d=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
		d=sqrt(d);
		return d;
	}
	void AddCity(int num,char *na,int x,int y)
	{
		City city(num,na,x,y);
		if(curCounter==maxCounter)
		{
			City *newcities;
			newcities=new City[maxCounter+10];
			for(int i=0;i<curCounter;i++)
			{
				newcities[i]=cities[i];
			}
			delete []cities;
			maxCounter=maxCounter+10;
			cities=newcities;
		}
		cities[curCounter++]=city;
	}
	void DeleteCity(int m)
	{
		int n=0;
		for(int i=0;i<curCounter;i++)
			if(cities[i].number==m)
				for(int j=i;j<curCounter-1;j++)
					cities[j]=cities[j+1];
		curCounter--;
	
	}
	void SaveCity(char *filename)
	{
		fstream outfile;
		outfile.open(filename,ios::out);
		outfile<<curCounter<<endl;
		for(int i=0;i<curCounter;i++)
		{
			outfile.setf(ios::left,ios::adjustfield);
			outfile<<setw(8)<<cities[i].number<<setw(10)<<cities[i].name<<setw(5)<<cities[i].x<<setw(5)<<cities[i].y<<endl;
		}
		outfile.close();
	}
	void UpdateCity(int i,int num,char *na,int x,int y)
	{
		for(int j=0;j<curCounter;j++)
			if(cities[j].number==i)
			{
				cities[i].number=num;
				strcpy(cities[i].name,na);
				cities[i].x=x;
				cities[i].y=y;
			}
	}
	int FindCity(int num)
	{
		for(int i=0;i<curCounter;i++)
			if(cities[i].number==num)
				return i;
		return -1;
	}
	void showCities()
	{
		for(int i=0;i<curCounter;i++)
			cities[i].show();
	}
	int GetCurCounter()
	{
		return curCounter;
	}
	int GetPostionX(int i)
	{
		return cities[i].x;
	}
	int GetPostionY(int i)
	{
		return cities[i].y;
	}
	void ShowCity(int i)
	{
		cities[i].show();
	}
};
class Plane
{
private:
	int number;
	char name[25];
	int x,y;
	double weight;
public:
	Plane(int num=1000,char na[25]=" ",int xpos=0,int ypos=0,double w=0)
	{
		number=num;
		strcpy(name,na);
		x=xpos;y=ypos;
		weight=w;
	}
	void show()
	{
		cout.setf(ios::left,ios::adjustfield);
		cout<<"�ɻ���ţ�"<<setw(8)<<number<<"���ƣ�"<<setw(10)<<name<<"����:"<<setw(5)<<weight<<"���꣨"<<x<<","<<y<<")"<<endl;
	}
	int CanBrake(double sp,double reDistance)
	{
		if(weight==0)
			return -1;
		
		else if(weight*sp/5<reDistance)
			return 1;
		else return 0;
	}
	void RadarFind(double radarRadius,Map mapObj)
	{
		int m=mapObj.GetCurCounter();
		for(int i=0;i<m;i++)
		{
			int x1=mapObj.GetPostionX(i);
			int y1=mapObj.GetPostionX(i);
			if((x1-x)*(x1-x)+(y1-y)*(y1-y)<radarRadius)
				mapObj.ShowCity(i);
		}
	}
	void SetPlane(int num,char *na,double w,int xpos,int ypos)
	{
		number=num;
		strcpy(name,na);
		x=xpos;y=ypos;
		weight=w;
	}
};
void PrintStar()
{
	for(int i=0;i<45;i++)
		cout<<"*";
	cout<<endl;
}
int menu_select()
{
	int i,choice;
	char *m[12]={"1. ���ӳ�����Ϣ",
				 "2. ɾ��������Ϣ",
				 "3. �޸ĳ�����Ϣ",
				 "4. ���������Ϣ���ļ�",
			   	 "5. ���ļ���ȡ������Ϣ",
				 "6. ��ʾ���г�����Ϣ",
				 "7. ���÷ɻ���Ϣ",
				 "8. ��ʾ�ɻ���Ϣ",
			 	 "9. �ж���ɷɻ��Ƿ����ɲ��",
				 "10.��ѯ�ɻ��״�뾶�����г�����Ϣ",
				 "0. �˳�"};

	do{
		system("cls"); //����
		PrintStar();
		for (i=0;m[i];i++)
			cout<<m[i]<<endl;
		PrintStar();
		cout<<"������ѡ��";
		cin>>choice;
	}while(choice<0||choice>10);
	return choice;
}
void appendCity(Map &mapObj)
{
	int num,x,y;
	char na[25]={"\0"};
	cout<<"�������³��б�š����ơ�����(x,y)��";
	cin>>num>>na>>x>>y;
	mapObj.AddCity(num,na,x,y);
}
void delCity(Map &mapObj)
{
	int num;
	cout<<"��������ɾ���ĳ��б�ţ�";
	cin>>num;
	if(mapObj.FindCity(num)!=-1)
	{
		char c;
		cout<<"�Ƿ�ȷ��ɾ���ó���(y/n):";
		cin>>c;
		switch(c)
		{
			case('y'):
				mapObj.DeleteCity(num);
				
			default:break;
		}
	cout<<"��ɾ����"<<endl ;}
	else
		cout<<"�ó��в�����"<<endl;
}
void updCity(Map &mapObj)
{
	int num,x,y;
	char na[25]={"\0"};
	cout<<"��������б�ţ�";
	cin>>num;
	int i=mapObj.FindCity(num);
	if(i!=-1)
	{
		cout<<"�������³��б�š����ơ�����(x,y)��";
		cin>>na>>x>>y;
		mapObj.UpdateCity(i,num,na,x,y);
	}
	else
		cout<<"�ó��в�����"<<endl;
}
void SaveToFile(Map &mapObj)
{
	char name[25]={"\0"};
	cout<<"����������ļ�����";
	cin>>name;
	mapObj.SaveCity(name);
}
void ReadFromFile(Map &mapObj)
{
	char name[25]={"\0"};
	cout<<"����������ļ�����";
	cin>>name;
	mapObj.ReadCity(name);
}
void ShowAllCities(Map &mapObj)
{
	if(mapObj.GetCurCounter()>0)
		mapObj.showCities();
	else 
		cout<<"��ǰû�г�����Ϣ"<<endl;
}
void AddPlane(Plane &planeObj)
{
	int num,x,y,w;
	char na[25]={"\0"};

	cout<<"������ɻ���ţ�";cin>>num;cout<<endl;
	cout<<"������ɻ����ƣ�";cin>>na;cout<<endl;
	cout<<"������ɻ��������֣���";cin>>w;cout<<endl;
	cout<<"������ɻ�����(x,y)��"; cin>>x>>y; 
	
	planeObj.SetPlane(num,na,w,x,y);
}
void ShowPlane(Plane &planeObj)
{
	planeObj.show();
}
void Brake(Plane &planeObj)
{
	double reDistance,sp;
	cout<<"�����뵱ǰ�ɻ����ٶȣ�km/h����";
	cin>>sp;
	cout<<"�������ܵ�ʣ�೤�ȣ�m��:" ;
	cin>>reDistance;
	int a;
	a=planeObj.CanBrake(sp,reDistance);
	if(a==1)
		cout<<"����ɲ��"<<endl;
	else if(a==0)
		cout<<"������ɲ��!!!"<<endl;
	else
		cout<<"û�зɻ���Ϣ"<<endl;
}
void RadarSearch(Plane &planeObj, Map &mapObj)
{
	double radarRadius=0;
	cout<<"�������״�ɨ��뾶��";
	cin>>radarRadius;
	planeObj.RadarFind(radarRadius,mapObj);
}
char Quit(Map &mapObj)
{
	char c;
	cout<<"�Ƿ�ȷ���˳���(y/n)  ";
	cin>>c;
	if(c=='y')
	{
		mapObj.SaveCity("map.txt");
		
		return 'y';
	}
	if(c=='n')
		return 'n';
}
int main()
{
	Map mapObj;
	Plane planeObj;
	int sel=0;
	for(;;)
	{
		switch(sel=menu_select( ))
		{
			 case 1: appendCity(mapObj);
					 system("pause");
					 break;
			 case 2: delCity(mapObj);
				     system("pause");
					 break;
			 case 3: updCity(mapObj);
				     system("pause");
					 break;
			 case 4: SaveToFile(mapObj);
				     system("pause");
					 break;
			 case 5: ReadFromFile(mapObj);
				     system("pause");
					 break;
			 case 6: ShowAllCities(mapObj);
				     system("pause");
					 break;
			 case 7: AddPlane(planeObj);
				     system("pause");break;
					 break;
			 case 8: ShowPlane(planeObj);
				     system("pause");
					 break;
			 case 9: Brake(planeObj);
				     system("pause");
					 break;
			 case 10:RadarSearch(planeObj, mapObj);
				     system("pause");
					 break;
			 case 0: if(Quit(mapObj)=='y')
			         cout<<"Bye";
			         else continue; 
		}
		if(sel==0)
			break;
	}
    return 0;
}//ͨ��
