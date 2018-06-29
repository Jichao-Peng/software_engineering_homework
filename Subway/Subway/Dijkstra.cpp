//Created by 王希 娄宁


#include"Dijkstra.h"
#include<fstream>
#include <math.h>
//构造函数
Graph_DG::Graph_DG(int vexnum , int edge) {
	//初始化顶点数和边数
	this->vexnum = vexnum;
	this->edge = edge;
	//为邻接矩阵开辟空间和赋初值
	arc = new double*[this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new double[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			//邻接矩阵初始化为无穷大
			arc[i][k] = INT_MAX;
		}
	}
}
Graph_DG::Graph_DG(int vexnum=452)
	:vexnum{vexnum}
{
	//为邻接矩阵开辟空间和赋初值
	arc = new double*[this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new double[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			//邻接矩阵初始化为无穷大
			arc[i][k] = INT_MAX;
		}
	}
}
//析构函数
Graph_DG::~Graph_DG() {
	delete[] dis;
	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
	}
	delete arc;
	IndexRoute.clear();
	returnpath.clear();
	returnindex.clear();
	cout << "sdsfsafdsaf" << endl;
}

// 判断我们每次输入的的边的信息是否合法
//顶点从1开始编号
bool Graph_DG::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

vector<int> Graph_DG::Search_Same_Station(string name,const vector<string>&StationName)
{
	vector<int> Same_Station;
	for (int i = 0; i<StationName.size();i++)
	{
		if (name == StationName[i])
		{
			Same_Station.push_back(i);
			//cout << StationName[i] << endl;
			//cout << i << endl;
		}
	}
	return Same_Station;
}

void Graph_DG::createGraph() {
	for (int i = 0; i < StationName.size(); i++)
	{
		for (int j = 0; j < StationName.size(); j++)
		{
			if (i == j)
				arc[i][j] = INT_MAX;
			if ((i-j) == 1||(j-i)==1)
			{
				arc[i][j] = 1;
				arc[j][i] = 1;
			}
		}
	}
	arc[27][28] = INT_MAX;
	arc[28][27] = INT_MAX;
	arc[57][58] = INT_MAX;
	arc[58][57] = INT_MAX;
    arc[86][87]=INT_MAX;
    arc[87][86]=INT_MAX;
	arc[112][113] = INT_MAX;
	arc[113][112] = INT_MAX;
	arc[123][124] = INT_MAX;
	arc[124][123] = INT_MAX;
	arc[151][152] = INT_MAX;
	arc[152][151] = INT_MAX;
	arc[184][185] = INT_MAX;
	arc[185][184] = INT_MAX;
	arc[214][215] = INT_MAX;
	arc[215][214] = INT_MAX;
	arc[249][250] = INT_MAX;
	arc[250][249] = INT_MAX;
	arc[277][278] = INT_MAX;
	arc[278][277] = INT_MAX;
	arc[304][305] = INT_MAX;
	arc[305][304] = INT_MAX;
	arc[334][335] = INT_MAX;
	arc[335][334] = INT_MAX;
	arc[366][367] = INT_MAX;
	arc[367][366] = INT_MAX;
	arc[398][399] = INT_MAX;
	arc[399][398] = INT_MAX;
	arc[417][418] = INT_MAX;
	arc[418][417] = INT_MAX;
	arc[430][431] = INT_MAX;
	arc[431][430] = INT_MAX;
	arc[432][433] = INT_MAX;
	arc[433][432] = INT_MAX;
	arc[445][446] = INT_MAX;
	arc[446][445] = INT_MAX;

	vector<string> StationName2 = StationName;
	for (int i = 0; i < StationName.size(); i++)
	{
		StationName2[i] = "";
		vector<int> Same_Station;
		Same_Station = Search_Same_Station(StationName[i], StationName2);
		for (int j = 0; j < Same_Station.size();j++)
		{
			//cout << "mark" << Same_Station[j] << endl;
			//cout << StationName[Same_Station[j]] << endl;
			if (i != Same_Station[j])
			{
				arc[i][Same_Station[j]] = INT_MAX;
				arc[Same_Station[j]][i] = INT_MAX;
				if (i != 0 && i != 28 && i != 58 && i != 87 && i != 113 && i != 124 && i != 152 && i != 185 && i != 215 && i != 250 && \
					i != 278 && i != 305 && i != 335 && i != 367 && i != 399 && i != 418 && i != 431 && i != 433 && i != 446)
				{
					arc[Same_Station[j]][i - 1] = 1.5;
					arc[i - 1][Same_Station[j]] = 1.5;
				}
				if (i != 27 && i != 57 && i != 86 && i != 112 && i != 123 && i != 151 && i != 184 && i != 214 && i != 249 && \
					i != 277 && i != 304 && i != 334 && i != 366 && i != 398 && i != 417 && i != 430 && i != 432 && i != 445 && i != 451)
				{
					arc[Same_Station[j]][i + 1] = 1.5;
					arc[i + 1][Same_Station[j]] = 1.5;
				}
					
				if (Same_Station[j] != 0 && Same_Station[j] != 28 && Same_Station[j] != 58 && Same_Station[j] != 87 && Same_Station[j] != 113 && Same_Station[j] != 124 && Same_Station[j] != 152 && Same_Station[j] != 185 && Same_Station[j] != 215 && Same_Station[j] != 250 && \
					Same_Station[j] != 278 && Same_Station[j] != 305 && Same_Station[j] != 335 && Same_Station[j] != 367 && Same_Station[j] != 399 && Same_Station[j] != 418 && Same_Station[j] != 431 && Same_Station[j] != 433 && Same_Station[j] != 446)
				{
					arc[i][Same_Station[j] - 1] = 1.5;
					arc[Same_Station[j] - 1][i] = 1.5;
				}
				if (Same_Station[j] != 27 && Same_Station[j] != 57 && Same_Station[j] != 86 && Same_Station[j] != 112 && Same_Station[j] != 123 && Same_Station[j] != 151 && Same_Station[j] != 184 && Same_Station[j] != 214 && Same_Station[j] != 249 && \
					Same_Station[j] != 277 && Same_Station[j] != 304 && Same_Station[j] != 334 && Same_Station[j] != 366 && Same_Station[j] != 398 && Same_Station[j] != 417 && Same_Station[j] != 430 && Same_Station[j] != 432 && Same_Station[j] != 445 && Same_Station[j] != 451)
				{
					arc[i][Same_Station[j] + 1] = 1.5;
					arc[Same_Station[j] + 1][i] = 1.5;
				}
			}
		}
	}

	//cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
	//int start;
	//int end;
	//int weight;
	//int count = 0;
	//while (count != this->edge) {
	//	cin >> start >> end >> weight;
	//	//首先判断边的信息是否合法
	//	while (!this->check_edge_value(start, end, weight)) {
	//		cout << "输入的边的信息不合法，请重新输入" << endl;
	//		cin >> start >> end >> weight;
	//	}
	//	//对邻接矩阵对应上的点赋值
	//	arc[start - 1][end - 1] = weight;
	//	//无向图添加上这行代码
	//	//arc[end - 1][start - 1] = weight;
	//	++count;
	//}
}

void Graph_DG::print() {
	cout << "图的邻接矩阵为：" << endl;
	int count_row = 0; //打印行的标签
	int count_col = 0; //打印列的标签
	//开始打印
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == INT_MAX)
				cout << "∞" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}
void Graph_DG::Dijkstra(int begin){
	//首先初始化我们的dis数组
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//设置当前的路径
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
	}
	//设置起点的到起点的路径为0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
	while (count != this->vexnum) {
		//temp用于保存当前dis数组中最小的那个下标
		//min记录的当前的最小值
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//cout << temp + 1 << "  "<<min << endl;
		//把temp对应的顶点加入到已经找到的最短路径的集合中
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//注意这里的条件arc[temp][i]!=INT_MAX必须加，不然会出现溢出，从而造成程序异常
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
			}
		}
	}

}

void Graph_DG::Dijkstra(string name,string end, string& a, vector<int>& returnindex){
	//首先初始化我们的dis数组
	int i;
	int begin = WhichStation(name);
	for (i = 0; i < this->vexnum; i++) {
		//设置当前的路径
		vector<int> iRoute;
		IndexRoute.push_back(iRoute);
		IndexRoute[i].push_back(begin);
		IndexRoute[i].push_back(i);
        dis[i].path = "【"+WhichLine(begin) + "】:";
		if (WhichLine(begin) == WhichLine(i))
		dis[i].path =dis[i].path+ StationName[begin] + "-->" + StationName[i];
		else
		{
			dis[i].path = dis[i].path + StationName[begin] + "-->" + WhichLine(i) + ":" + StationName[i];
		}
		dis[i].value = arc[begin ][i];
	}
	//设置起点的到起点的路径为0
	dis[begin].value = 0;
	dis[begin].visit = true;
	/*for (i = 1; i < vexnum; i++)
		cout << "dis" << dis[i].value << endl;*/

	int count = 1;
	//计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
	while (count != this->vexnum) {
		//temp用于保存当前dis数组中最小的那个下标
		//min记录的当前的最小值
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//cout << temp + 1 << "  "<<min << endl;
		//把temp对应的顶点加入到已经找到的最短路径的集合中
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//注意这里的条件arc[temp][i]!=INT_MAX必须加，不然会出现溢出，从而造成程序异常
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
				dis[i].value = dis[temp].value + arc[temp][i];
				//cout << "arc["<<temp<<"]["<<i<<"]=" << arc[temp][i] << "value=" << dis[i].value << endl;
				//cout << dis[i].path << endl;
				//IndexRoute[temp].push_back(i);
				IndexRoute[i] = IndexRoute[temp];
				IndexRoute[i].push_back(i);
				if (WhichLine(temp) == WhichLine(i))
					dis[i].path = dis[temp].path + "-->" +  StationName[i];
				else
				{
                    dis[i].path = dis[temp].path + "\n" + "\n【"+WhichLine(i)+"】:" + StationName[i];
				}
			}
		}
	}
	/*for (i = 1; i < vexnum; i++)
		cout << "dis2" << dis[i].value << endl;*/
	 i = WhichStation(end);
	 if (dis[i].value != INT_MAX)
		 //cout << dis[i].path << "=" << dis[i].value << endl;
	 {
		 returnindex = IndexRoute[i];
		 a = dis[i].path;
	 }
}

void Graph_DG::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "以" << str << "为起点的图的最短路径为：" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << dis[i].path << "是无最短路径的" << endl;
		}
	}
}
int Graph_DG::WhichStation(string name)
{
	for (int i = 0; i < StationName.size(); i++)
	{
		if (StationName[i] == name)
			return i;
	}
}

string Graph_DG::WhichLine(int station)
{
	if (station >= 0 && station < 28)
		return "一号线";
	if (station >=28 && station < 58)
		return "二号线";
	if (station >= 58 && station < 87)
		return "三号线";
	if (station >= 87 && station < 113)
		return "四号线";
	if (station >= 113 && station < 124)
		return "五号线";
	if (station >=124 && station < 152)
		return "六号线";
	if (station >= 152 && station < 185)
		return "七号线";
	if (station >= 185 && station <215)
		return "八号线";
	if (station >= 215 && station < 250)
		return "九号线";
	if (station >= 250 && station < 278)
		return "十号线";
	if (station >= 278 && station < 305)
		return "十号支线";
	if (station >=305 && station < 335)
		return "十一号线";
	if (station >= 335 && station < 367)
		return "十一号支线";
	if (station >= 367 && station < 399)
		return "十二号线";
	if (station >= 399 && station < 418)
		return "十三号线";
	if (station >= 418 && station < 431)
		return "十六号线";
	if (station >= 431 && station < 433)
		return "磁悬浮线";
	if (station >= 433 && station < 446)
		return "十七号线";
	if (station >= 446 && station < 452)
		return "浦江线";
}

string Graph_DG::print_path(string begin, string end)
{
	cout << "以" << begin << "为起点,以" << end << "为终点的最短路径为：" << endl;
	int i = WhichStation(end);
	cout << "mark"<<dis[i].path << "=" << dis[i].value << endl;
	if (dis[i].value != INT_MAX)
	{
		cout << dis[i].path << endl;
	}
	else{
		cout << dis[i].path << "是无最短路径的" << endl;
	}
	return dis[i].path;
}

bool Graph_DG::ReadFile(const string& File)
{
	int i = 0;
	ifstream infile(File.c_str());
	if (!infile)
		return false;
	while (!infile.eof())
	{
		string word;
		infile >> word;
		if (infile)
		{
			StationName.push_back(word);
			//cout <<i<<" "<< word << endl;
			i++;
		}

	}
	infile.close();
	return true;
}

string Graph_DG::ReturnString(int i)
{
	return StationName[i];
}
//string Graph_DG::ReturnRoute(string start, string end)
//{
//	//this->Dijkstra(start);
//	//return this->print_path(start, end);
//	return "s";
//}
vector<int>& Graph_DG::ReturnIndex(string start, string end)
{
	int i = WhichStation(end);
	if (dis[i].value != INT_MAX)
		//cout << dis[i].path << "=" << dis[i].value << endl;
		for (int j = 0; j < IndexRoute[i].size(); j++)
			cout << IndexRoute[i][j] << endl;
		return IndexRoute[i];
}

void Graph_DG::reset()
{
	IndexRoute.clear();
	returnpath.clear();
	returnindex.clear();
	for (int i = 0; i < this->vexnum; i++)
	{
		dis[i].value = 0;
		dis[i].path = "";
		dis[i].visit = false;
	}
}
