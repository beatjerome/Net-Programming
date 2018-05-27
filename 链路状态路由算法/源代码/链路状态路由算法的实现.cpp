#include"Header.h" 

Status CreateVexs(char *vexs){
//������������
	for(int i=0;i<MaxSize;i++){
		vexs[i]='0'+i;
	}
	return OK;
}

Status CreateArcs(ArcInfo *arcs,int n){
//������ϵ����
	
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
//��ȡ������Ӧ��λ��
	for(int i=0;i<G.n;i++){
		if(G.vexs[i]==v)
			return i;
	}	
	return -1;
}

int FirstAdjVex(Graph G,int k){
//Ѱ�ҵ�һ���ڽӽڵ�
	if(k<0 || k>=G.n)
		return -1;
	for(int i=0;i<G.n;i++){
		if(G.arcs[k][i]!=INFINITY)	
			return i;	
	}	
	return -1;
}

int NextAdjVex(Graph G,int k,int m){
//Ѱ����һ���ڽӽڵ�
	if(k<0 || k>=G.n)
		return -1;
	for(int i=m+1;i<G.n;i++)
		if(G.arcs[k][i]!=INFINITY)
			return i;
	return -1;	
}

Status InitGraph(Graph &G,char *vexs,int n,ArcInfo *arcs,int e){
//��ʼ��·�ɱ�
	char v,w;
	G.n=n;			//��ʼ�������� 
	G.e=e;			//��ʼ������ 
	G.vexs=(char *)malloc(sizeof(char)*G.n);			//�������������ռ� 
	G.tags=(int *)malloc(sizeof(int)*G.n);				//������״̬�������ռ�
	G.arcs=(int **)malloc(sizeof(int *)*G.n);			//����ϵ�������ռ�
	for(int i=0;i<G.n;i++)								//����ռ� 
		G.arcs[i]=(int *)malloc(sizeof(int)*G.n); 
	for(int i=0;i<G.n;i++){								//��ʼ����ϵ����
		for(int j=0;j<G.n;j++)
			G.arcs[i][j]=INFINITY;		
	}
	for(int i=0;i<G.n;i++){ 
		G.vexs[i]=vexs[i];					//����Ϊ���㸳ֵ 
		G.tags[i]=UNVISITED;				//��ʼ������״̬ 
	}
	cout<<"��ʼ��·�ɱ�ɹ�"<<endl;
	return OK;	
}

Status CreateGraph(Graph &G,ArcInfo *arcs){
//����·�ɱ�
	int i,j,Weight;
	for(int k=0;k<G.e;k++){
		i=LocateVex(G,arcs[k].v);					//��ȡ������Ӧ��λ�� 
		j=LocateVex(G,arcs[k].w);
		if(i<0 || j<0)
			return ERROR;
		cout<<"�������"<<i<<"���ڵ㵽��"<<j<<"���ڵ��Ȩֵ��"; 
		cin>>Weight;
		G.arcs[i][j]=Weight;		
		G.arcs[j][i]=Weight;
	}
	cout<<"����·�ɱ�ɹ�"<<endl; 
	return OK;	
}

Status Dijkstra(Graph G,int i,pDistInfo &Dist){
//�Ͻ�˹�����㷨Ѱ�����·��
	int k,min;
	Dist=(DistInfo *)malloc(sizeof(DistInfo)*G.n);		//����ռ� 
	for(int j=0;j<G.n;j++){
		Dist[j].shortest=INFINITY;		//��ʼ��һ��ʼ����i������j�����·�����ȶ�Ϊ���޴� 
		G.tags[j]=UNSELECTED;			//��ʼ������״̬ 
	}
	Dist[i].prev=-1;					//��ʼ������i��ǰ�� 
	Dist[i].shortest=0;					//��ʼ����̾��� 
	G.tags[i]=SELECTED;					//���·���״̬ 
	
	for(int j=FirstAdjVex(G,i);j>=0;j=NextAdjVex(G,i,j)){
		Dist[j].prev=i;						//���¶���i�ڽӽڵ��ǰ�� 
		Dist[j].shortest=G.arcs[i][j];		//����i���ڽӶ���j�����·��
	}	
	
	for(int m=1;m<G.n;m++){					//��·����������������Դ�㵽������������·��
		min=INFINITY;
		k=0;
		for(int j=0;j<G.n;j++){
			if(G.tags[j]==UNSELECTED && Dist[j].shortest<min){	//�ҵ���̵� 
				k=j;
				min=Dist[k].shortest;
			}
		}
		G.tags[k]=SELECTED;				//���·���״̬ 
		
		for(int j=FirstAdjVex(G,k);j>=0;j=NextAdjVex(G,k,j)){		//����Dist���� 
			if(G.tags[j]==UNSELECTED && Dist[k].shortest!=INFINITY && Dist[k].shortest+G.arcs[k][j]<Dist[j].shortest){		
			//��j���·��Ϊ ��Դ��ֱ�ӵ�j�Ļ��������Ǿ�����ĳ����õ����·���ٵ�j																							
				Dist[j].shortest=Dist[k].shortest+G.arcs[k][j];
				//�������·�� 
				Dist[j].prev=k;				//����ǰ���ڵ� 
			}
		}
	}
}

char NextJump(Graph G,DistInfo *Dist,int k){
//Ѱ��·��������һ��
	if(Dist[k].prev==-1){
		return 'X';
	}
	else if(Dist[Dist[k].prev].prev==-1){
		return G.vexs[k];
	}
	NextJump(G,Dist,Dist[k].prev);
}

void PrintRoute(Graph G,DistInfo *Dist,int k){
//������·��·��
	if(k==-1)
		return ;
	PrintRoute(G,Dist,Dist[k].prev);		//����ݹ��ȡ·���ϵĶ��� 
	printf("%c  ",G.vexs[k]);				//����������� 
}


Status OutputGraph(Graph &G,int VEXSSIZE){
//���·������ͼ
	int i,j;
	FILE *fp=fopen("Graph.txt","w");
	if(fp==NULL){
		cout<<"The file can't open.";
		exit(0);
	}
	else{
		fprintf(fp,"************·�����˱�************\n");
		for(int i=0;i<VEXSSIZE;i++){
			for(j=0;j<VEXSSIZE;j++){
				if(G.arcs[i][j]!=INFINITY)
					fprintf(fp,"   %-6d",G.arcs[i][j]);
				else
					fprintf(fp,"   %-6d",0);
			}	
			fprintf(fp,"\n");
		}
		fprintf(fp,"   ע : %d��ʾ�ޱ�����\n",NOLINK);
		fprintf(fp,"*********************************\n");
		fclose(fp);
		cout<<"·�����˱�Graph.txt����ɹ���"<<endl;
	}
	return 0;
}

Status OutputRoute(Graph &G,int VEXSSIZE){
//������ڵ��·����Ϣ
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
			fprintf(fp,"           \t  %d��·�ɱ�\n",i); 
			fprintf(fp,"     Ŀ��·��      ��һ·��      ��̾���\n");
			for(j=0;j<VEXSSIZE;j++){
				fprintf(fp,"    \t%d     \t      %c     \t    %d\n",j,NextJump(G,Dist,j),Dist[j].shortest);				
			}
		}
		fprintf(fp,"*********************************************\n");
		fclose(fp);
	}
	cout<<"·����Ϣ��Route.txt����ɹ���"<<endl;
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
	cout<<"������·�ɽڵ����: ";
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
		cout<<" 1.��ʼ��·�ɱ�  ";
		cout<<" 2.����·�ɱ�"	<<endl;
		cout<<" 3.����·����Ϣ  ";
		cout<<" 4.���·������"	<<endl;
		cout<<" 5.���·�ɱ�    ";
		cout<<" 6.�˳�ģ��"   	<<endl; 
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
				cout<<"������Դ���: ";
				cin>>start;
	
				Dijkstra(G,start,Dist);
				for(i=0;i<VEXSSIZE;i++){
					cout<<"*****************************************"<<endl;
					printf("Ŀ���� : %c\n",G.vexs[i]);
					cout<<"���·���� : ";
					PrintRoute(G,Dist,i);
					printf("\n���·������ : %d\n",Dist[i].shortest);
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
				cout<<"�˳�ģ��ɹ���";
				exit(-1);
				break;
			}
			default:{
				cout<<"��������������������ѡ��������"<<endl;
				break;
			} 
		}	 
	}    
} 
int main(){
	TestBoard();
	return 0;
}
