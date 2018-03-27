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
    int depth;   //深度
    int dist;    //距离
    int fx;      //评估函数fx=depth+dist
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

int calcDist(matrix a,matrix b){//计算距离差
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

void show(matrix a){ //展示矩阵
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            if(a.num[i][j]!=0) cout<<a.num[i][j]<<" ";
            else cout<<"  ";
        cout<<endl;
    }
}

bool canDo(matrix a,matrix b){//判断是否有解
    int tmpA=0,tmpB=0;
    for(int i=1;i<9;i++)
        for(int j=0;j<i;j++){
            if(a.num[j/3][j%3]>a.num[i/3][i%3]&&a.num[j/3][j%3]!=0&&a.num[i/3][i%3]!=0) tmpA++;
            if(b.num[j/3][j%3]>b.num[i/3][i%3]&&b.num[j/3][j%3]!=0&&b.num[i/3][i%3]!=0) tmpB++;
        }
    if(tmpA%2==tmpB%2) return 1;
    return 0;
}
void print(Path path,int num){//输出路径
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
        cout<<"步骤:"<<cnt-i-1<<endl;
        show(procedure[i].state);
    }
    cout<<"操作结束:"<<endl;
    cout<<"总步数："<<cnt-1<<endl;
}
int findZero(matrix a){//找0的位置
    for(int i=0;i<9;i++)
        if(a.num[i/3][i%3]==0) return i;
    return 0;
}

void copyMatrix(matrix &a,matrix b){//复制matrix
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            a.num[i][j]=b.num[i][j];
}
void calcSub(Open sub[],Open cur){//找到节点的所有分支
    int num=0,location;
    location=findZero(cur.state);
    //向上
    if(location>2){
        copyMatrix(sub[num].state,cur.state);
        sub[num].state.num[location/3][location%3]=cur.state.num[location/3-1][location%3];
        sub[num].state.num[location/3-1][location%3]=cur.state.num[location/3][location%3];
        sub[num].depth=1;
        num++;
    }
    //向右
    if(location%3!=2){
        copyMatrix(sub[num].state,cur.state);
        sub[num].state.num[location/3][location%3]=cur.state.num[location/3][location%3+1];
        sub[num].state.num[location/3][location%3+1]=cur.state.num[location/3][location%3];
        sub[num].depth=1;
        num++;
    }
    //向下
    if(location<6){
        copyMatrix(sub[num].state,cur.state);
        sub[num].state.num[location/3][location%3]=cur.state.num[location/3+1][location%3];
        sub[num].state.num[location/3+1][location%3]=cur.state.num[location/3][location%3];
        sub[num].depth=1;
        num++;
    }
    //向左
    if(location%3!=0){
        copyMatrix(sub[num].state,cur.state);
        sub[num].state.num[location/3][location%3]=cur.state.num[location/3][location%3-1];
        sub[num].state.num[location/3][location%3-1]=cur.state.num[location/3][location%3];
        sub[num].depth=1;
        num++;
    }
}
void calcOpen(Open &child,Open father,matrix end){//更新Open节点中的参数
    child.depth=father.depth+1;
    child.dist=calcDist(child.state,end);
    child.fx=child.dist+child.depth;
}
bool findOpen(Open a,Openlist &op,int num){//查找openlist是否有当前节点
    for(int i=0;i<num;i++)
        if(Equal(a.state,op.note[i].state))  {
            op.note[i].fx=min(op.note[i].fx,a.fx);
            return true;
        }
    return 0;
}
bool findClose(matrix a,Closelist cl,int num){//查找closelist是否有当前节点
    for(int i=0;i<num;i++)
        if(Equal(a,cl.note[i].state)) return true;
    return 0;
}

void listSort(Openlist &op,int num){//openlist根据评估函数由小到大排序
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
    openlist.note[open_num].fx=openlist.note[open_num].dist+openlist.note[open_num].depth; //初始化openlist
    open_num++;
    while(open_num!=0){                       //open不为空
        head=openlist.note[0];                 //head为openlist头结点
        path.pa[path_num++]=head;              //将当前节点加入路径
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
                if(!findOpen(sub[i],openlist,open_num)&&!findClose(sub[i].state,closelist,close_num)){//节点不在openlist和closelist中，将节点放入openlist
                    openlist.note[open_num]=sub[i];
                    open_num++;
                    continue;
                }
                if(findOpen(sub[i],openlist,open_num))   continue;  //节点在openlist，将更新openlist中此节点的评估函数fx
                if(findClose(sub[i].state,closelist,close_num))  continue; //节点在closelist，跳过
            }
        }
        closelist.note[close_num].state=head.state;
        closelist.note[close_num].fx=head.fx;
        close_num++;//将head加入closelist
        listSort(openlist,open_num);
    }
}
int main()
{
    matrix start,end;
    bool ok = 1;
    while (ok){
        ok = 0;
        cout<<"************* 欢迎使用八数码问题求解程序 *************"<<endl;
        cout<<"输入示范：\n";
        cout<<"输入1 2 3 8 0 4 7 6 5 \n";
        cout<<"表示:\n";
        cout<<"\t1 2 3\n\t8   4\n\t7 6 5\n";
        cout<<"请输入初态:\n";
        for (int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>start.num[i][j];
        cout<<"您输入的初态:\n";
        show(start);

        cout<<"请输入終态:\n";
        for (int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>end.num[i][j];
        cout<<"您输入的終态:\n";
        show(end);

        cout<<"请选择搜索的启发函数类型："<<endl;
        cout<<"1. 八数码不在的位数"<<endl;
        cout<<"2. 八数码当前各位与正确位距离之和"<<endl;
        cout<<"输入启发函数类型编号：";
        cin>>cho;
        cout<<"您输入的启发函数类型：";
        switch (cho){
            case 1:
                cout<<"八数码不在的位数"<<endl;
                break;
            case 2:
                cout<<"八数码当前各位与正确位距离之和"<<endl;
                break;
            default:
                cout<<"输入有误"<<endl;
                break;
        }

        if(canDo(start,end)){
            cout<<"状态有解:\n";
            clock_t start_time=clock();
            AStar(start,end);
            clock_t end_time=clock();
            cout<< "Running time is: "<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间
        }
        else cout<<"该状态无解!"<<endl;
        cout<<"还要继续吗~（Y/N）"<<endl;
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
