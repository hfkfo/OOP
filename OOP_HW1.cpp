#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Link //�x�s��J��Link���
{
public:
    int LinkID;
    int Node1;
    int Node2;
    int oldW;//�ª�Weight
    int newW;//�s��Weight
};
class Link Link[5000];
class Node //�x�s�U�I������U���I���ƭ�
{
public:
    map<int,int> Next_Node_ID;//<destination_ID,next_node_ID>
    map<int,int> Weight;//<destination_ID,sum of weight>
    map<int,int> visit;//�P�_���I�O�_�w���L
};
class Node nd[500];
vector<int> LinkID[5000];//�x�s�C���I�ҳs����LinkID
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
        LinkID[tmp].push_back(tmp1);//�N�I�����쪺LinkID�s�J
        tmp=Link[i].Node2;
        LinkID[tmp].push_back(tmp1);//�N�I�����쪺LinkID�s�J
    }
    for(int i=0;i<Dsts;i++)//������Weight��shortest path
    {
        nd[DstID[i]].Next_Node_ID[DstID[i]]=-1;//�N���I��Next Node�]��-1
        nd[DstID[i]].Weight[DstID[i]]=0;//�N���I��sum of Weight �]�� 0
        shortest_path(DstID[i],DstID[i],0);//(�{�b���檺�I,���I,�P�_�O�s����)
    }
    for(int i=0;i<Dsts;i++)
    {
        nd[DstID[i]].Next_Node_ID[DstID[i]+Nodes]=-1;//�N���I��Next Node�]��-1�A�N���������I�[�WNodes�קK�v�T���ª�
        nd[DstID[i]].Weight[DstID[i]+Nodes]=0;//�N���I��sum of Weight �]�� 0�A�N���������I�[�WNodes�קK�v�T���ª�
        shortest_path(DstID[i],DstID[i]+Nodes,1);//(�{�b���檺�I,���I+Nodes,�P�_�O�s����)
    }
    for(int i=0;i<Nodes;i++)
    {
        cout<<i<<endl;
        for(int j=0;j<Dsts;j++)
        {
            if(nd[i].Next_Node_ID[DstID[j]]!=-1)//���I�����I���ܡA������X
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
            if(nd[i].Next_Node_ID[DstID[j]]!=nd[i].Next_Node_ID[DstID[j]+Nodes])//�P�_�O�_���t�O
            {
                if(tmp==0)//�ݥ���X���I
                {
                    cout<<i<<endl;
                    tmp=1;
                }
                cout<<DstID[j]<<" "<<nd[i].Next_Node_ID[DstID[j]+Nodes]<<endl;
            }
        }
    }
}
void shortest_path(int Node,int Dst,int old_or_new)//����shortest path
{
    nd[Node].visit[Dst]=1;//�N���I�аO���ϥιL
    for(int i=0;i<LinkID[Node].size();i++)//�}�l�M��Node�P�����I��Link
    {
        int tmp,tmp1;
        tmp=LinkID[Node][i];//�קK�C�������Ӫ�
        if(old_or_new==0)
        {
            tmp1=nd[Node].Weight[Dst]+Link[tmp].oldW;//�קK�C�������Ӫ�
        }
        else if(old_or_new==1)
        {
            tmp1=nd[Node].Weight[Dst]+Link[tmp].newW;//�קK�C�������Ӫ�
        }
        if(Link[tmp].Node1!=Node)//�p�GLink���I�bNode1
        {
            if(nd[Link[tmp].Node1].Weight[Dst]==0)//���I�|�����L�A���i��O���I
            {
                if(old_or_new==0)//�ư��O���I�����p
                {
                    if(Link[tmp].Node1!=Dst)
                    {
                        nd[Link[tmp].Node1].Weight[Dst]=tmp1;
                        nd[Link[tmp].Node1].Next_Node_ID[Dst]=Node;
                    }
                }
                else//�ư��O���I�����p
                {
                    if(Link[tmp].Node1!=Dst-Nodes)
                    {
                        nd[Link[tmp].Node1].Weight[Dst]=tmp1;
                        nd[Link[tmp].Node1].Next_Node_ID[Dst]=Node;
                    }
                }
            }
            else if(nd[Link[tmp].Node1].Weight[Dst]>tmp1)//�s�����u��Weight��쥻���p
            {
                nd[Link[tmp].Node1].Weight[Dst]=tmp1;
                nd[Link[tmp].Node1].Next_Node_ID[Dst]=Node;
            }
            else if(nd[Link[tmp].Node1].Weight[Dst]==tmp1)//�s�����u��Weight�P�쥻�@��
            {
                if(nd[Link[tmp].Node1].Next_Node_ID[Dst] > Node)//�P�_�s�����I�O�_����p
                {
                    nd[Link[tmp].Node1].Weight[Dst]=tmp1;
                    nd[Link[tmp].Node1].Next_Node_ID[Dst]=Node;
                }
            }
        }
        else//�p�GLink���I�bNode
        {
            if(nd[Link[tmp].Node2].Weight[Dst]==0)//���I�|�����L�A���i��O���I
            {
                if(old_or_new==0)//�ư��O���I�����p
                {
                    if(Link[tmp].Node2!=Dst)
                    {
                        nd[Link[tmp].Node2].Weight[Dst]=tmp1;
                        nd[Link[tmp].Node2].Next_Node_ID[Dst]=Node;
                    }
                }
                else//�ư��O���I�����p
                {
                    if(Link[tmp].Node2!=Dst-Nodes)
                    {
                        nd[Link[tmp].Node2].Weight[Dst]=tmp1;
                        nd[Link[tmp].Node2].Next_Node_ID[Dst]=Node;
                    }
                }
            }
            else if(nd[Link[tmp].Node2].Weight[Dst]>tmp1)//�s�����u��Weight��쥻���p
            {
                nd[Link[tmp].Node2].Weight[Dst]=tmp1;
                nd[Link[tmp].Node2].Next_Node_ID[Dst]=Node;
            }
            else if(nd[Link[tmp].Node2].Weight[Dst]==tmp1)//�s�����u��Weight�P�쥻�@��
            {
                if(nd[Link[tmp].Node2].Next_Node_ID[Dst] > Node)//�P�_�s�����I�O�_����p
                {
                    nd[Link[tmp].Node2].Weight[Dst]=tmp1;
                    nd[Link[tmp].Node2].Next_Node_ID[Dst]=Node;
                }
            }
        }
    }
    int tmp=-1;
    for(int i=0;i<Nodes;i++)//�P�_�w���L���I���֪� sum of Weight �̤p�A�B�|���ϥιL
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
    if(tmp!=-1)//�N�o�쪺�I�~�򻼰j�U�h
    {
        shortest_path(tmp,Dst,old_or_new);
    }
}
