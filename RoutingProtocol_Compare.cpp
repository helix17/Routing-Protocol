#include<iostream>
#include<ctime>
#include<time.h>
#define INFINITY 9999
#define MAX 20
using namespace std;
class timer {
	long sTime;
	public:
		void start(){
			sTime=clock();
		}
		long elapsedTime(){
			return ((long) clock()-sTime);
		}
};
void linkstate(int G[MAX][MAX],int n,int startnode){
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==-1)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
	for(i=0;i<n;i++){
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count<n-1){
		mindistance=INFINITY;
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i]){
				mindistance=distance[i];
				nextnode=i;
			}
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i]){
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
	cout<<"\n\tDistance\tPath\n";
	for(i=0;i<n;i++)
		if(i!=startnode){
            cout<<"Node "<<i+1<<":\t"<<distance[i]<<"\t\t"<<i+1;
			j=i;
			do
			{
				j=pred[j];
				cout<<"<-"<<j+1;
			}while(j!=startnode);
			printf("\n");
        }
}
int main(){
    int i,j,k,n,graph[20][20],tab[20][20][20],rt[20][20],upd[20][20];
    long t1,t2;
    timer t;
    cout<<"Enter Number of Nodes: ";
    cin>>n;
    cout<<"\t\tNODES\t  ";
    for(i=0;i<n;i++)
        cout<<i+1<<"  ";
    cout<<endl;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            rt[i][j]=-1;
            graph[i][j]=-1;
            if(j==i)
                graph[i][j]=0;
        }
    for(i=0;i<n;i++){
        cout<<"Enter Weights for Node "<<i+1<<":";
        for(j=0;j<n;j++){
            if(j>i){
                cin>>graph[i][j];
                graph[j][i]=graph[i][j];
            }
            else
                cout<<" - ";
        }
    }
    cout<<"\n---Distance Vector---\n";
    t.start();
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                if(graph[i][j]>-1 && graph[j][k]>-1)
                    tab[i][j][k]=graph[i][j]+graph[j][k];
                else
                    tab[i][j][k]=-1;
            }
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            upd[i][j]=graph[i][j];
            rt[i][j]=i;
            for(k=0;k<n;k++){
                if(upd[i][j]>tab[i][k][j] || upd[i][j]==-1){
                    if(tab[i][k][j]>-1){
                        upd[i][j]=tab[i][k][j];
                        rt[i][j]=k;
                    }
                }
            }
            if(upd[i][j]==-1){
                for(k=0;k<n;k++){
                    if(upd[i][k]!=-1 && upd[k][j]!=-1){
                        if(upd[i][j]==-1 || (upd[i][j]!=-1 && upd[i][j]>upd[i][k]+upd[k][j])){
                            if(upd[i][k]+upd[k][j]>-1){
                                upd[i][j]=upd[i][k]+upd[k][j];
                                if(rt[i][k]!=i)
                                    rt[i][j]=rt[i][k];
                                else
                                    rt[i][j]=k;
                            }
                        }
                    }
                }
            }
        }
    }
    for(i=0;i<n;i++){
        cout<<"\nNode "<<i+1<<"\nTo\tCost\tNext\n";
        for(j=0;j<n;j++){
            cout<<j+1<<"\t"<<upd[i][j]<<"\t";
            if(rt[i][j]==i)
                cout<<"-";
            else
                cout<<rt[i][j]+1;
            cout<<endl;
        }
    }
    t1=t.elapsedTime();
    cout<<"\nClocks taken By Distance Vector: "<<t1<<"\n";
    cout<<"\n---Link State---\n";
    t.start();
	for(i=0;i<n;i++){
        cout<<"\n---For Node "<<i+1<<"---";
        linkstate(graph,n,i);
	}
	t2=t.elapsedTime();
	cout<<"\nClocks Taken By Link State: "<<t2<<"\n";
	if(t1>t2)
        cout<<"\nCONCLUSION: Link State is better than Distance Vector";
    else if(t2>t1)
        cout<<"\nCONCLUSION: Distance Vector is better than Link State";
    else if(t1==t2)
        cout<<"\nCONCLUSION: Distance Vector and Link State have same performance";
}
