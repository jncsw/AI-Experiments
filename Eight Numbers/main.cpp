#include <bits/stdc++.h>
#include <time.h>

#define MAX_OPEN  1234
#define MAX_CLOSE 1234
#define MAX_PATH 1234

using namespace std;
typedef struct {
    int num[3][3];
} matrix;
typedef struct {
    matrix state;
    int depth;   //���
    int dist;    //����
    int fx;      //��������fx=depth+dist
} Open;
typedef struct {
    Open note[MAX_OPEN];
}  Openlist;
typedef struct {
    matrix state;
    int fx;
} Close;
typedef struct {
    Close note[MAX_CLOSE];
} Closelist;
typedef struct {
    Open pa[MAX_PATH];
} Path;

int cho = 1;

bool Equal(matrix a,matrix b){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(a.num[i][j]!=b.num[i][j])
                return false;
    return true;
}
void removeFirst(Openlist &openlist,int num){
    for(int i=0;i<num;i++)
        openlist.note[i]=openlist.note[i+1];
}

int calcDist(matrix a,matrix b){//��������
    int cnt=0;
    if(cho==1){
        for(int i=0;i<9;i++)
            if(a.num[i/3][i%3]!=b.num[i/3][i%3]) cnt++;
        return cnt;
    }else if(cho==2){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(a.num[j/3][j%3]==b.num[i/3][i%3]) cnt+=(abs(i%3-j%3)+abs(i/3-j/3));
            }
        }
        return cnt;
    }

    return cnt;
}

void show(matrix a){ //չʾ����
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            if(a.num[i][j]!=0) cout<<a.num[i][j]<<" ";
            else cout<<"  ";
        cout<<endl;
    }
}

bool canDo(matrix a,matrix b){//�ж��Ƿ��н�
    int tmpA=0,tmpB=0;
    for(int i=1;i<9;i++)
        for(int j=0;j<i;j++){
            if(a.num[j/3][j%3]>a.num[i/3][i%3]&&a.num[j/3][j%3]!=0&&a.num[i/3][i%3]!=0) tmpA++;
            if(b.num[j/3][j%3]>b.num[i/3][i%3]&&b.num[j/3][j%3]!=0&&b.num[i/3][i%3]!=0) tmpB++;
        }
    if(tmpA%2==tmpB%2) return 1;
    return 0;
}
void print(Path path,int num){//���·��
    int cur=num-1,cnt=1;
    Open *procedure;
    procedure=new Open[num];
    procedure[0]=path.pa[cur];
    while(cur>0){
        for(int i=cur;i>=0;i--){
            if(calcDist(path.pa[i].state,path.pa[cur].state)==2){
                cur=i;
                procedure[cnt++]=path.pa[i];
                break;
            }
        }
    }
    for(int i=cnt-1;i>=0;i--){
        cout<<"����:"<<cnt-i-1<<endl;
        show(procedure[i].state);
    }
    cout<<"��������:"<<endl;
    cout<<"�ܲ�����"<<cnt-1<<endl;
}
int findZero(matrix a){//��0��λ��
    for(int i=0;i<9;i++)
        if(a.num[i/3][i%3]==0) return i;
    return 0;
}

void copyMatrix(matrix &a,matrix b){//����matrix
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            a.num[i][j]=b.num[i][j];
}
void calcSub(Open sub[],Open cur){//�ҵ��ڵ�����з�֧
    int num=0,location;
    location=findZero(cur.state);
    //����
    if(location>2){
        copyMatrix(sub[num].state,cur.state);
        sub[num].state.num[location/3][location%3]=cur.state.num[location/3-1][location%3];
        sub[num].state.num[location/3-1][location%3]=cur.state.num[location/3][location%3];
        sub[num].depth=1;
        num++;
    }
    //����
    if(location%3!=2){
        copyMatrix(sub[num].state,cur.state);
        sub[num].state.num[location/3][location%3]=cur.state.num[location/3][location%3+1];
        sub[num].state.num[location/3][location%3+1]=cur.state.num[location/3][location%3];
        sub[num].depth=1;
        num++;
    }
    //����
    if(location<6){
        copyMatrix(sub[num].state,cur.state);
        sub[num].state.num[location/3][location%3]=cur.state.num[location/3+1][location%3];
        sub[num].state.num[location/3+1][location%3]=cur.state.num[location/3][location%3];
        sub[num].depth=1;
        num++;
    }
    //����
    if(location%3!=0){
        copyMatrix(sub[num].state,cur.state);
        sub[num].state.num[location/3][location%3]=cur.state.num[location/3][location%3-1];
        sub[num].state.num[location/3][location%3-1]=cur.state.num[location/3][location%3];
        sub[num].depth=1;
        num++;
    }
}
void calcOpen(Open &child,Open father,matrix end){//����Open�ڵ��еĲ���
    child.depth=father.depth+1;
    child.dist=calcDist(child.state,end);
    child.fx=child.dist+child.depth;
}
bool findOpen(Open a,Openlist &op,int num){//����openlist�Ƿ��е�ǰ�ڵ�
    for(int i=0;i<num;i++)
        if(Equal(a.state,op.note[i].state))  {
            op.note[i].fx=min(op.note[i].fx,a.fx);
            return true;
        }
    return 0;
}
bool findClose(matrix a,Closelist cl,int num){//����closelist�Ƿ��е�ǰ�ڵ�
    for(int i=0;i<num;i++)
        if(Equal(a,cl.note[i].state)) return true;
    return 0;
}

void listSort(Openlist &op,int num){//openlist��������������С��������
    Open temp;
    int index;
    for(int i=0;i<num;i++){
        index=i;
        for(int j=i+1;j<num;j++){
            if(op.note[j].fx<op.note[index].fx){
                temp=op.note[index];
                op.note[index]=op.note[j];
                op.note[j]=temp;
            }
        }
    }
}
void AStar(matrix start,matrix end){
    int open_num=0,close_num=0,path_num=0;
    Openlist openlist;
    Closelist closelist;
    Open head;
    Path path;
    openlist.note[open_num].state=start;
    openlist.note[open_num].depth=0;
    openlist.note[open_num].dist=calcDist(start,end);
    openlist.note[open_num].fx=openlist.note[open_num].dist+openlist.note[open_num].depth; //��ʼ��openlist
    open_num++;
    while(open_num!=0){                       //open��Ϊ��
        head=openlist.note[0];                 //headΪopenlistͷ���
        path.pa[path_num++]=head;              //����ǰ�ڵ����·��
        removeFirst(openlist,open_num);
        open_num--;
        if(Equal(head.state,end)){
            print(path,path_num);
            break;
        }
        Open sub[4];
        calcSub(sub,head);
        for(int i=0;i<4;i++){
            if(sub[i].depth==1){
                calcOpen(sub[i],head,end);
                if(!findOpen(sub[i],openlist,open_num)&&!findClose(sub[i].state,closelist,close_num)){//�ڵ㲻��openlist��closelist�У����ڵ����openlist
                    openlist.note[open_num]=sub[i];
                    open_num++;
                    continue;
                }
                if(findOpen(sub[i],openlist,open_num))   continue;  //�ڵ���openlist��������openlist�д˽ڵ����������fx
                if(findClose(sub[i].state,closelist,close_num))  continue; //�ڵ���closelist������
            }
        }
        closelist.note[close_num].state=head.state;
        closelist.note[close_num].fx=head.fx;
        close_num++;//��head����closelist
        listSort(openlist,open_num);
    }
}
int main()
{
    matrix start,end;
    bool ok = 1;
    while (ok){
        ok = 0;
        cout<<"************* ��ӭʹ�ð��������������� *************"<<endl;
        cout<<"����ʾ����\n";
        cout<<"����1 2 3 8 0 4 7 6 5 \n";
        cout<<"��ʾ:\n";
        cout<<"\t1 2 3\n\t8   4\n\t7 6 5\n";
        cout<<"�������̬:\n";
        for (int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>start.num[i][j];
        cout<<"������ĳ�̬:\n";
        show(start);

        cout<<"������K̬:\n";
        for (int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>end.num[i][j];
        cout<<"������ĽK̬:\n";
        show(end);

        cout<<"��ѡ�������������������ͣ�"<<endl;
        cout<<"1. �����벻�ڵ�λ��"<<endl;
        cout<<"2. �����뵱ǰ��λ����ȷλ����֮��"<<endl;
        cout<<"���������������ͱ�ţ�";
        cin>>cho;
        cout<<"������������������ͣ�";
        switch (cho){
            case 1:
                cout<<"�����벻�ڵ�λ��"<<endl;
                break;
            case 2:
                cout<<"�����뵱ǰ��λ����ȷλ����֮��"<<endl;
                break;
            default:
                cout<<"��������"<<endl;
                break;
        }

        if(canDo(start,end)){
            cout<<"״̬�н�:\n";
            clock_t start_time=clock();
            AStar(start,end);
            clock_t end_time=clock();
            cout<< "Running time is: "<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��
        }
        else cout<<"��״̬�޽�!"<<endl;
        cout<<"��Ҫ������~��Y/N��"<<endl;
        char c;
        cin>>c;
        if(c=='y' || c=='Y') ok = 1;
    }
    cout<<"Bye~"<<endl;
    return 0;
}
/*
 * Sample input:
 * 2 5 4 1 3 0 8 7 6
 * 1 2 3 8 0 4 7 6 5
 */
