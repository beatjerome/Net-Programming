#include"Header.h" 

Status CreateVexs(char *vexs){
//创建顶点数组
	for(int i=0;i<MaxSize;i++){
		vexs[i]='0'+i;
	}
	return OK;
}

Status CreateArcs(ArcInfo *arcs,int n){
//创建关系数组
	
	int i=0;
	for(int j=0;j<n;j++){
		for(int k=j+1;k<n;k++){
			arcs[i].v='0'+j;
			arcs[i].w='0'+k;
			i++;
		}
	}

	/*
	arcs[0].v='0';
	arcs[0].w='1';
	
	arcs[1].v='0';
	arcs[1].w='2';
	
	arcs[2].v='0';
	arcs[2].w='3';
	
	arcs[3].v='1';
	arcs[3].w='2';
	
	arcs[4].v='1';
	arcs[4].w='3';
	
	arcs[5].v='2';
	arcs[5].w='3';	*/
	return OK;
}

int LocateVex(Graph G, char v){
//获取顶点相应的位序
	for(int i=0;i<G.n;i++){
		if(G.vexs[i]==v)
			return i;
	}	
	return -1;
}

int FirstAdjVex(Graph G,int k){
//寻找第一个邻接节点
	if(k<0 || k>=G.n)
		return -1;
	for(int i=0;i<G.n;i++){
		if(G.arcs[k][i]!=INFINITY)	
			return i;	
	}	
	return -1;
}

int NextAdjVex(Graph G,int k,int m){
//寻找下一个邻接节点
	if(k<0 || k>=G.n)
		return -1;
	for(int i=m+1;i<G.n;i++)
		if(G.arcs[k][i]!=INFINITY)
			return i;
	return -1;	
}

Status InitGraph(Graph &G,char *vexs,int n,ArcInfo *arcs,int e){
//初始化路由表
	char v,w;
	G.n=n;			//初始化顶点数 
	G.e=e;			//初始化边数 
	G.vexs=(char *)malloc(sizeof(char)*G.n);			//给顶点数组分配空间 
	G.tags=(int *)malloc(sizeof(int)*G.n);				//给访问状态数组分配空间
	G.arcs=(int **)malloc(sizeof(int *)*G.n);			//给关系数组分配空间
	for(int i=0;i<G.n;i++)								//分配空间 
		G.arcs[i]=(int *)malloc(sizeof(int)*G.n); 
	for(int i=0;i<G.n;i++){								//初始化关系数组
		for(int j=0;j<G.n;j++)
			G.arcs[i][j]=INFINITY;		
	}
	for(int i=0;i<G.n;i++){ 
		G.vexs[i]=vexs[i];					//依次为顶点赋值 
		G.tags[i]=UNVISITED;				//初始化访问状态 
	}
	cout<<"初始化路由表成功"<<endl;
	return OK;	
}

Status CreateGraph(Graph &G,ArcInfo *arcs){
//创建路由表
	int i,j,Weight;
	for(int k=0;k<G.e;k++){
		i=LocateVex(G,arcs[k].v);					//获取顶点相应的位序 
		j=LocateVex(G,arcs[k].w);
		if(i<0 || j<0)
			return ERROR;
		cout<<"请输入第"<<i<<"个节点到第"<<j<<"个节点的权值："; 
		cin>>Weight;
		G.arcs[i][j]=Weight;		
		G.arcs[j][i]=Weight;
	}
	cout<<"创建路由表成功"<<endl; 
	return OK;	
}

Status Dijkstra(Graph G,int i,pDistInfo &Dist){
//迪杰斯特拉算法寻找最短路径
	int k,min;
	Dist=(DistInfo *)malloc(sizeof(DistInfo)*G.n);		//分配空间 
	for(int j=0;j<G.n;j++){
		Dist[j].shortest=INFINITY;		//初始化一开始顶点i到顶点j的最短路径长度都为无限大 
		G.tags[j]=UNSELECTED;			//初始化访问状态 
	}
	Dist[i].prev=-1;					//初始化顶点i的前驱 
	Dist[i].shortest=0;					//初始化最短距离 
	G.tags[i]=SELECTED;					//更新访问状态 
	
	for(int j=FirstAdjVex(G,i);j>=0;j=NextAdjVex(G,i,j)){
		Dist[j].prev=i;						//更新顶点i邻接节点的前驱 
		Dist[j].shortest=G.arcs[i][j];		//顶点i到邻接顶点j的最短路径
	}	
	
	for(int m=1;m<G.n;m++){					//按路径长度升序，依次求源点到其他顶点的最短路径
		min=INFINITY;
		k=0;
		for(int j=0;j<G.n;j++){
			if(G.tags[j]==UNSELECTED && Dist[j].shortest<min){	//找到最短的 
				k=j;
				min=Dist[k].shortest;
			}
		}
		G.tags[k]=SELECTED;				//更新访问状态 
		
		for(int j=FirstAdjVex(G,k);j>=0;j=NextAdjVex(G,k,j)){		//更新Dist数组 
			if(G.tags[j]==UNSELECTED && Dist[k].shortest!=INFINITY && Dist[k].shortest+G.arcs[k][j]<Dist[j].shortest){		
			//到j最短路径为 从源点直接到j的弧；或者是经过已某条求得的最短路径再到j																							
				Dist[j].shortest=Dist[k].shortest+G.arcs[k][j];
				//更新最短路径 
				Dist[j].prev=k;				//更新前驱节点 
			}
		}
	}
}

char NextJump(Graph G,DistInfo *Dist,int k){
//寻找路由器的下一跳
	if(Dist[k].prev==-1){
		return 'X';
	}
	else if(Dist[Dist[k].prev].prev==-1){
		return G.vexs[k];
	}
	NextJump(G,Dist,Dist[k].prev);
}

void PrintRoute(Graph G,DistInfo *Dist,int k){
//输出最短路由路径
	if(k==-1)
		return ;
	PrintRoute(G,Dist,Dist[k].prev);		//逆向递归获取路径上的顶点 
	printf("%c  ",G.vexs[k]);				//正向输出顶点 
}


Status OutputGraph(Graph &G,int VEXSSIZE){
//输出路由拓扑图
	int i,j;
	FILE *fp=fopen("Graph.txt","w");
	if(fp==NULL){
		cout<<"The file can't open.";
		exit(0);
	}
	else{
		fprintf(fp,"************路由拓扑表************\n");
		for(int i=0;i<VEXSSIZE;i++){
			for(j=0;j<VEXSSIZE;j++){
				if(G.arcs[i][j]!=INFINITY)
					fprintf(fp,"   %-6d",G.arcs[i][j]);
				else
					fprintf(fp,"   %-6d",0);
			}	
			fprintf(fp,"\n");
		}
		fprintf(fp,"   注 : %d表示无边相连\n",NOLINK);
		fprintf(fp,"*********************************\n");
		fclose(fp);
		cout<<"路由拓扑表Graph.txt输出成功！"<<endl;
	}
	return 0;
}

Status OutputRoute(Graph &G,int VEXSSIZE){
//输出各节点的路由信息
	int i,j;
	FILE *fp=fopen("Route.txt", "w");
	DistInfo *Dist=(DistInfo *)malloc(sizeof(DistInfo)*VEXSSIZE);
	if(fp==NULL){
		cout<<"The file can't open.";
		exit(0);
	}
	else{
		for(i=0;i<VEXSSIZE;i++){
			fprintf(fp,"*********************************************\n");
			Dijkstra(G,i,Dist);
			fprintf(fp,"           \t  %d的路由表\n",i); 
			fprintf(fp,"     目的路由      下一路由      最短距离\n");
			for(j=0;j<VEXSSIZE;j++){
				fprintf(fp,"    \t%d     \t      %c     \t    %d\n",j,NextJump(G,Dist,j),Dist[j].shortest);				
			}
		}
		fprintf(fp,"*********************************************\n");
		fclose(fp);
	}
	cout<<"路由信息表Route.txt输出成功！"<<endl;
	return 0;
}
void TestBoard(){
	int i;
	char x;
	char v; 
	int k,m,start;
	int VEXSSIZE;
	int ARCSSIZE;
	Graph G;
	cout<<"*****************************************"<<endl;
	cout<<"请输入路由节点个数: ";
	cin>>VEXSSIZE;
	ARCSSIZE=VEXSSIZE*(VEXSSIZE-1)/2;
	int D[VEXSSIZE];
	DistInfo *Dist=(DistInfo *)malloc(sizeof(DistInfo)*VEXSSIZE);

	char vexs[VEXSSIZE];
	CreateVexs(vexs);
	ArcInfo arcs[ARCSSIZE];
	CreateArcs(arcs,VEXSSIZE);
	while(1){
		cout<<"*************Operation Table*************"<<endl;
		cout<<" 1.初始化路由表  ";
		cout<<" 2.创建路由表"	<<endl;
		cout<<" 3.查找路由信息  ";
		cout<<" 4.输出路由拓扑"	<<endl;
		cout<<" 5.输出路由表    ";
		cout<<" 6.退出模拟"   	<<endl; 
		cout<<"*****************************************"<<endl;
		cout<<"Enter number to choose operation: ";
    	scanf("%d",&i);
    	switch(i){
    		case 1:{
				InitGraph(G,vexs,VEXSSIZE,arcs,ARCSSIZE);
				break;
			}
			case 2:{
				CreateGraph(G,arcs); 
				break;
			}
			case 3:{
				cout<<"请输入源结点: ";
				cin>>start;
	
				Dijkstra(G,start,Dist);
				for(i=0;i<VEXSSIZE;i++){
					cout<<"*****************************************"<<endl;
					printf("目标结点 : %c\n",G.vexs[i]);
					cout<<"最短路径是 : ";
					PrintRoute(G,Dist,i);
					printf("\n最短路径长度 : %d\n",Dist[i].shortest);
					NextJump(G,Dist,i);
				}
				break;
			}
			case 4:{
				OutputGraph(G,VEXSSIZE);
				break;
			}
			case 5:{
				OutputRoute(G,VEXSSIZE);				
				break;
			}
			case 6:{
				cout<<"退出模拟成功！";
				exit(-1);
				break;
			}
			default:{
				cout<<"操作编号输入错误，请重新选择操作编号"<<endl;
				break;
			} 
		}	 
	}    
} 
int main(){
	TestBoard();
	return 0;
}
