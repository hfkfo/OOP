#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Link //儲存輸入的Link資料
{
public:
    int LinkID;
    int Node1;
    int Node2;
    int oldW;//舊的Weight
    int newW;//新的Weight
};
class Link Link[5000];
class Node //儲存各點對應到各終點的數值
{
public:
    map<int,int> Next_Node_ID;//<destination_ID,next_node_ID>
    map<int,int> Weight;//<destination_ID,sum of weight>
    map<int,int> visit;//判斷此點是否已走過
};
class Node nd[500];
vector<int> LinkID[5000];//儲存每個點所連接的LinkID
int Nodes,Dsts,Links;
void shortest_path(int,int,int);
int main()
{
    cin >>Nodes>>Dsts>>Links;
    vector<int> DstID;
    for(int i=0;i<Dsts;i++)
    {
        int tmp;
        cin >>tmp;
        DstID.push_back(tmp);
    }
    for(int i=0;i<Links;i++)
    {
        int tmp,tmp1;
        cin >> Link[i].LinkID >> Link[i].Node1>> Link[i].Node2>>Link[i].oldW>>Link[i].newW;
        tmp=Link[i].Node1;
        tmp1=Link[i].LinkID;
        LinkID[tmp].push_back(tmp1);//將點對應到的LinkID存入
        tmp=Link[i].Node2;
        LinkID[tmp].push_back(tmp1);//將點對應到的LinkID存入
    }
    for(int i=0;i<Dsts;i++)//執行舊Weight的shortest path
    {
        nd[DstID[i]].Next_Node_ID[DstID[i]]=-1;//將終點的Next Node設為-1
        nd[DstID[i]].Weight[DstID[i]]=0;//將終點的sum of Weight 設為 0
        shortest_path(DstID[i],DstID[i],0);//(現在執行的點,終點,判斷是新或舊)
    }
    for(int i=0;i<Dsts;i++)
    {
        nd[DstID[i]].Next_Node_ID[DstID[i]+Nodes]=-1;//將終點的Next Node設為-1，將對應的終點加上Nodes避免影響到舊的
        nd[DstID[i]].Weight[DstID[i]+Nodes]=0;//將終點的sum of Weight 設為 0，將對應的終點加上Nodes避免影響到舊的
        shortest_path(DstID[i],DstID[i]+Nodes,1);//(現在執行的點,終點+Nodes,判斷是新或舊)
    }
    for(int i=0;i<Nodes;i++)
    {
        cout<<i<<endl;
        for(int j=0;j<Dsts;j++)
        {
            if(nd[i].Next_Node_ID[DstID[j]]!=-1)//此點為終點的話，不必輸出
            {
                cout<<DstID[j]<<" "<<nd[i].Next_Node_ID[DstID[j]]<<endl;
            }
        }
    }
    for(int i=0;i<Nodes;i++)
    {
        int tmp=0;
        for(int j=0;j<Dsts;j++)
        {
            if(nd[i].Next_Node_ID[DstID[j]]!=nd[i].Next_Node_ID[DstID[j]+Nodes])//判斷是否有差別
            {
                if(tmp==0)//需先輸出該點
                {
                    cout<<i<<endl;
                    tmp=1;
                }
                cout<<DstID[j]<<" "<<nd[i].Next_Node_ID[DstID[j]+Nodes]<<endl;
            }
        }
    }
}
void shortest_path(int Node,int Dst,int old_or_new)//執行shortest path
{
    nd[Node].visit[Dst]=1;//將此點標記為使用過
    for(int i=0;i<LinkID[Node].size();i++)//開始尋找Node與那些點有Link
    {
        int tmp,tmp1;
        tmp=LinkID[Node][i];//避免每次都打太長
        if(old_or_new==0)
        {
            tmp1=nd[Node].Weight[Dst]+Link[tmp].oldW;//避免每次都打太長
        }
        else if(old_or_new==1)
        {
            tmp1=nd[Node].Weight[Dst]+Link[tmp].newW;//避免每次都打太長
        }
        if(Link[tmp].Node1!=Node)//如果Link的點在Node1
        {
            if(nd[Link[tmp].Node1].Weight[Dst]==0)//該點尚未走過，但可能是終點
            {
                if(old_or_new==0)//排除是終點的情況
                {
                    if(Link[tmp].Node1!=Dst)
                    {
                        nd[Link[tmp].Node1].Weight[Dst]=tmp1;
                        nd[Link[tmp].Node1].Next_Node_ID[Dst]=Node;
                    }
                }
                else//排除是終點的情況
                {
                    if(Link[tmp].Node1!=Dst-Nodes)
                    {
                        nd[Link[tmp].Node1].Weight[Dst]=tmp1;
                        nd[Link[tmp].Node1].Next_Node_ID[Dst]=Node;
                    }
                }
            }
            else if(nd[Link[tmp].Node1].Weight[Dst]>tmp1)//新的路線之Weight比原本的小
            {
                nd[Link[tmp].Node1].Weight[Dst]=tmp1;
                nd[Link[tmp].Node1].Next_Node_ID[Dst]=Node;
            }
            else if(nd[Link[tmp].Node1].Weight[Dst]==tmp1)//新的路線之Weight與原本一樣
            {
                if(nd[Link[tmp].Node1].Next_Node_ID[Dst] > Node)//判斷連接的點是否比較小
                {
                    nd[Link[tmp].Node1].Weight[Dst]=tmp1;
                    nd[Link[tmp].Node1].Next_Node_ID[Dst]=Node;
                }
            }
        }
        else//如果Link的點在Node
        {
            if(nd[Link[tmp].Node2].Weight[Dst]==0)//該點尚未走過，但可能是終點
            {
                if(old_or_new==0)//排除是終點的情況
                {
                    if(Link[tmp].Node2!=Dst)
                    {
                        nd[Link[tmp].Node2].Weight[Dst]=tmp1;
                        nd[Link[tmp].Node2].Next_Node_ID[Dst]=Node;
                    }
                }
                else//排除是終點的情況
                {
                    if(Link[tmp].Node2!=Dst-Nodes)
                    {
                        nd[Link[tmp].Node2].Weight[Dst]=tmp1;
                        nd[Link[tmp].Node2].Next_Node_ID[Dst]=Node;
                    }
                }
            }
            else if(nd[Link[tmp].Node2].Weight[Dst]>tmp1)//新的路線之Weight比原本的小
            {
                nd[Link[tmp].Node2].Weight[Dst]=tmp1;
                nd[Link[tmp].Node2].Next_Node_ID[Dst]=Node;
            }
            else if(nd[Link[tmp].Node2].Weight[Dst]==tmp1)//新的路線之Weight與原本一樣
            {
                if(nd[Link[tmp].Node2].Next_Node_ID[Dst] > Node)//判斷連接的點是否比較小
                {
                    nd[Link[tmp].Node2].Weight[Dst]=tmp1;
                    nd[Link[tmp].Node2].Next_Node_ID[Dst]=Node;
                }
            }
        }
    }
    int tmp=-1;
    for(int i=0;i<Nodes;i++)//判斷已走過的點中誰的 sum of Weight 最小，且尚未使用過
    {
        if(nd[i].visit[Dst]==0 && nd[i].Weight[Dst]!=0 && tmp==-1)
        {
            tmp=i;
        }
        else if(nd[i].visit[Dst]==0 && nd[i].Weight[Dst]!=0)
        {
            if(nd[i].Weight[Dst]<nd[tmp].Weight[Dst])
            {
                tmp=i;
            }
        }
    }
    if(tmp!=-1)//將得到的點繼續遞迴下去
    {
        shortest_path(tmp,Dst,old_or_new);
    }
}
