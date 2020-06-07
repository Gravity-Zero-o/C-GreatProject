#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;
fstream in,out;
class City
{
	private:
		int number;//城市编号 
		char name[25];//城市名称 
		int x,y;//城市坐标 
	public:
		//构造函数 
		City(int num=1000, char na[25]=" ",int xpos=0,int ypos=0)
		{
			number=num;
			strcpy(name,na);
			x=xpos;
			y=ypos;
		}
		//设置城市编号 
		void setNumber(int num)
		{
			number=num;
		}
		//设置名称 
		void setName(char *na)
		{
			strcpy(name,na);
		}
		//设置坐标 
		void setPosition(int xpos,int ypos)
		{
			x=xpos;
			y=ypos;
		}
		//读取名称 ，在city类之后有定义 
		void getName(char *);
		//读取编号 
		int getNum()
		{
			return number;
		}
		//读取x,同理下一个函数 
		int getX()
		{
			return x;
		}
		int getY()
		{
			return y;
		}
		//显示城市信息 
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
		City *cities;//指向一个动态申请的对象数组 
		int curCounter,maxCounter;//现有城市计数和线性表最大长度计数 
	public:
		//申请动态空间，初始化城市信息列表 
		Map(int maxc=10)
		{
			curCounter = 0;
			maxCounter = maxc;
			if (maxc)
				cities = new City[maxCounter];
			else
				cities = NULL;
		}//将文件读入cities【】 
		void ReadCity(char *filename)
		{
			
			in.open(filename,ios::in);
			while(!in.eof())
			{
				if(curCounter==maxCounter)
				{
					City *newcities;
					newcities=new City[maxCounter+10];
					for(int i=0; i<curCounter; i++)
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
		//判断文件是否存在，若存在，调用 ReadCity函数 
		void ImportDataBase()
		{

			in.open("database.txt",ios::in);
			if(in)
			{
				ReadCity("database.txt");
			}

			in.close();
		}
		//拷贝构造函数 
		Map(Map &m)
		{
			cities=new City[maxCounter];
			for(int i=0; i<maxCounter; i++)
			{
				cities[i]=m.cities[i];
				curCounter=m.curCounter;
				maxCounter=m.maxCounter;
			}
		}
		//折构函数 
		~Map()
		{
			delete [] cities;
		}
		//计算距离 
		double Distance(int x1,int y1,int x2,int y2)
		{
			double d=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
			d=sqrt(d);
			return d;
		}
	    //在信息列表最后增加一个新城市信息 
		void AddCity(int num,char *na,int x,int y)
		{
			City city(num,na,x,y);
			if(curCounter==maxCounter)
			{
				City *newcities;
				newcities=new City[maxCounter+10];
				for(int i=0; i<curCounter; i++)
				{
					newcities[i]=cities[i];
				}
				delete []cities;
				maxCounter=maxCounter+10;
				cities=newcities;
			}
			cities[curCounter++]=city;
		}
		//删除选中的城市信息 
		void DeleteCity(int m)
		{
			int n=0;
			for(int i=0; i<curCounter; i++)
				if(cities[i].number==m)
					for(int j=i; j<curCounter-1; j++)
						cities[j]=cities[j+1];
			curCounter--;

		}
		//保存至文件 
		void SaveCity(char *filename)
		{

			out.open(filename,ios::out);
			out<<curCounter<<endl;
			for(int i=0; i<curCounter; i++)
			{
				out.setf(ios::left,ios::adjustfield);
				out<<setw(8)<<cities[i].number<<setw(10)<<cities[i].name<<setw(5)<<cities[i].x<<setw(5)<<cities[i].y<<endl;
			}
			out.close();
		}
		//更改城市信息 
		void UpdateCity(int i,int num,char *na,int x,int y)
		{
			for(int j=0; j<curCounter; j++)
				if(cities[j].number==i)
				{
					cities[j].number=num;
					strcpy(cities[j].name,na);
					cities[j].x=x;
					cities[j].y=y;
				}
		}
		//查找下标为i的城市信息 
		int FindCity(int num)
		{
			for(int i=0; i<curCounter; i++)
				if(cities[i].number==num)
					return i;
			return -1;
		}
		//显示全部城市信息 
		void showCities()
		{
			for(int i=0; i<curCounter; i++)
				cities[i].show();
	    }
	    //读取当前城市数量 
		int GetCurCounter()
		{
			return curCounter;
		}
		//返回下标为i的城市x坐标 
		int GetPostionX(int i)
		{
			return cities[i].x;
		}
		//同上 
		int GetPostionY(int i)
		{
			return cities[i].y;
		}
		//显示城市 
		void ShowCity(int i)
		{
			cities[i].show();
		}
};
class Plane
{
	private:
		int number;//飞机编号 
		char name[25];//飞机名称 
		int x,y;//飞机坐标 
		double weight;//飞机重量 
	public:
		//构造函数 
		Plane(int num=1000,char na[25]=" ",int xpos=0,int ypos=0,double w=0)
		{
			number=num;
			strcpy(name,na);
			x=xpos;
			y=ypos;
			weight=w;
		}
		//设置飞机信息 
		void SetPlane(int num,char *na,double w,int xpos,int ypos)
		{
			number=num;
			strcpy(name,na);
			x=xpos;
			y=ypos;
			weight=w;
		}
		//显示飞机信息 
		void show()
		{
			cout.setf(ios::left,ios::adjustfield);
			cout<<"飞机编号："<<setw(8)<<number<<"名称："<<setw(10)<<name<<"重量:"<<setw(5)<<weight<<"坐标（"<<x<<","<<y<<")"<<endl;
		}
		//判断刹车 
		int CanBrake(double sp,double reDistance)
		{
			if(weight==0)
				return -1;

			else if(weight*sp/5<reDistance)
				return 1;
			else return 0;
		}
		//根据当前坐标和雷达半径，扫描地图信息，显示半径内的城市信息 
		void RadarFind(double radarRadius,Map mapObj)
		{
			int m=mapObj.GetCurCounter();
			for(int i=0; i<m; i++)
			{
				int x1=mapObj.GetPostionX(i);
				int y1=mapObj.GetPostionX(i);
				if((x1-x)*(x1-x)+(y1-y)*(y1-y)<radarRadius)
					mapObj.ShowCity(i);
			}
		}
	
};
//星星 
void PrintStar()
{
	for(int i=0; i<45; i++)
		cout<<"*";
	cout<<endl;
}
//菜单函数 
int menu_select()
{
	int i,choice;
	char *m[12]= {"1. 增加城市信息",
	              "2. 删除城市信息",
	              "3. 修改城市信息",
	              "4. 保存城市信息至文件",
	              "5. 从文件读取城市信息",
	              "6. 显示所有城市信息",
	              "7. 设置飞机信息",
	              "8. 显示飞机信息",
	              "9. 判断起飞飞机是否可以刹车",
	              "10.查询飞机雷达半径内所有城市信息",
	              "0. 退出"
	             };

	do
	{
		system("cls"); //清屏
		PrintStar();
		for (i=0; m[i]; i++)
			cout<<m[i]<<endl;
		PrintStar();
		cout<<"请输入选择：";
		cin>>choice;
	}
	while(choice<0||choice>10);
	return choice;
}
//追加城市记录 
void appendCity(Map &mapObj)
{
	int num,x,y;
	char na[25]= {"\0"};
	cout<<"请输入城市编号：";
	cin>>num;
	cout<<"请输入名称：";
	cin>>na;
	cout<<"请输入坐标：";
	cin>>x>>y;
	mapObj.AddCity(num,na,x,y);
}
//删除城市记录 
void delCity(Map &mapObj)
{
	int num;
	cout<<"请输入想删除的城市编号：";
	cin>>num;
	if(mapObj.FindCity(num)!=-1)
	{       
                mapObj.ShowCity(mapObj.FindCity(num));
		char c;
		cout<<"是否确定删除该城市(y/n):";
		cin>>c;
		switch(c)
		{
			case('y'):
				mapObj.DeleteCity(num);

			default:
				break;
		}
		cout<<"已删除！"<<endl ;
	}
	else
		cout<<"该城市不存在"<<endl;
}
//修改城市记录 
void upCity(Map &mapObj)
{
	int num,x,y;
	char na[25]= {"\0"};
	cout<<"请输入城市编号：";
	cin>>num;
	int i=mapObj.FindCity(num);
	
	if(i!=-1)
	{
    
	cout<<"请输入新城市编号：";
	cin>>num;
	cout<<"请输入新名称：";
	cin>>na;
	cout<<"请输入坐标：";
	cin>>x>>y;
	    mapObj.DeleteCity(i);
		mapObj.UpdateCity(i,num,na,x,y);
		mapObj.AddCity(num,na,x,y);
	}
	else
		cout<<"该城市不存在"<<endl;
}
//保存，写入文件 
void SaveToFile(Map &mapObj)
{
	char name[25]= {"\0"};
	cout<<"请输入磁盘文件名：";
	cin>>name;
	mapObj.SaveCity(name);
}
//从文件中读取 
void ReadFromFile(Map &mapObj)
{
	char name[25]= {"\0"};
	cout<<"请输入磁盘文件名：";
	cin>>name;
	mapObj.ReadCity(name);
}
//显示所有城市信息 
void ShowAllCities(Map &mapObj)
{
	if(mapObj.GetCurCounter()>0)
		mapObj.showCities();
	else
		cout<<"当前没有城市信息"<<endl;
}
//输入飞机信息 
void AddPlane(Plane &planeObj)
{
	int num,x,y,w;
	char na[25]= {"\0"};

	cout<<"请输入飞机编号：";
	cin>>num;
	cout<<endl;
	cout<<"请输入飞机名称：";
	cin>>na;
	cout<<endl;
	cout<<"请输入飞机重量（吨）：";
	cin>>w;
	cout<<endl;
	cout<<"请输入飞机坐标(x,y)：";
	cin>>x>>y;

	planeObj.SetPlane(num,na,w,x,y);
}
//显示飞机信息 
void ShowPlane(Plane &planeObj)
{
	planeObj.show();
}
//刹车 
void Brake(Plane &planeObj)
{
	double reDistance,sp;
	cout<<"请输入当前飞机的速度（km/h）：";
	cin>>sp;
	cout<<"请输入跑道剩余长度（m）:" ;
	cin>>reDistance;
	int a;
	a=planeObj.CanBrake(sp,reDistance);
	if(a==1)
		cout<<"可以刹车"<<endl;
	else if(a==0)
		cout<<"不可以刹车!!!"<<endl;
	else
		cout<<"没有飞机信息"<<endl;
}
//计算城市距离，飞机雷达范围 
void RadarSearch(Plane &planeObj, Map &mapObj)
{
	double radarRadius=0;
	cout<<"请输入雷达扫描半径：";
	cin>>radarRadius;
	planeObj.RadarFind(radarRadius,mapObj);
}
//退出 
char Quit(Map &mapObj)
{
	char c;
	cout<<"是否确定退出：(y/n)  ";
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
			case 1:
				appendCity(mapObj);
				system("pause");
				break;
			case 2:
				delCity(mapObj);
				system("pause");
				break;
			case 3:
				upCity(mapObj);
				system("pause");
				break;
			case 4:
				SaveToFile(mapObj);
				system("pause");
				break;
			case 5:
				ReadFromFile(mapObj);
				system("pause");
				break;
			case 6:
				ShowAllCities(mapObj);
				system("pause");
				break;
			case 7:
				AddPlane(planeObj);
				system("pause");
				break;
				break;
			case 8:
				ShowPlane(planeObj);
				system("pause");
				break;
			case 9:
				Brake(planeObj);
				system("pause");
				break;
			case 10:
				RadarSearch(planeObj, mapObj);
				system("pause");
				break;
			case 0:
				if(Quit(mapObj)=='y')
					cout<<"Bye";
				else continue;
		}
		if(sel==0)
			break;
	}
	return 0;
}
