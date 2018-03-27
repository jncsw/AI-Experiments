#include<bits/stdc++.h>

using namespace std;
const int MAX = 60;
typedef long long ll;
int total = 0;
int cnt = 0;

struct point
{
    double x,y;
};

struct particle
{
    double fx;
    point speed,pos,pbest;
};

//��ȡ�����
ll getRand(ll a,ll b){
    return (rand() % (b-a+1))+ a;
}

double w,c1,c2;
const int m = 30;

point gbest;
particle *part;


double f(double x,double y){
    if(x>0 && x<=60.00001 && y>0 && y<=60.00001){
        if(x<m && y<m)return 30.0*x-y;
        if(x<m && y>=m)return 30.0*y-x;
        if(x>=m && y<m)return x*x-y/2.0;
        if(x>=m && y>=m)return 20.0*y*y-500.0*x;
    }
    return 0;
}


double f(point p){
    double x = p.x,y = p.y;
    if(x>0 && x<=60.00001 && y>0 && y<=60.00001){
        if(x<m && y<m)return 30.0*x-y;
        if(x<m && y>=m)return 30.0*y-x;
        if(x>=m && y<m)return x*x-y/2.0;
        if(x>=m && y>=m)return 20.0*y*y-500.0*x;
    }
    return 0;
}



bool canGo(point p)
{
    return p.x>0&&p.y>0&&p.x<60&&p.y<60;
}

void show()
{
    cout<<"x\ty\tf\nP_id:\n";
    for(int i=0;i<total;i++)
        cout<<part[i].pos.x<<"\t"<<part[i].pos.y<<"\t"<<part[i].fx<<"\n";
    cout<<"Pgbest:(ȫ������)\n";
    cout<<gbest.x<<"\t"<<gbest.y<<"\t"<<f(gbest)<<"\n";
}


void calcGbest()
{
    for(int i=0;i<total;i++){
        if(part[i].fx>f(gbest))
            gbest=part[i].pos;

    }
}

void calc()
{
    for(int i=0;i<total;i++)
    {
        point ts,tp;
        ts.x=w*part[i].speed.x+c1*rand()/(double)RAND_MAX
        *(part[i].pbest.x-part[i].pos.x)+c2*rand()/(double)RAND_MAX
        *(gbest.x-part[i].pos.x);

        ts.y=w*part[i].speed.y+c1*rand()/(double)RAND_MAX
        *(part[i].pbest.y-part[i].pos.y)+c2*rand()/(double)RAND_MAX
        *(gbest.y-part[i].pos.y);

        tp.x=part[i].pos.x+ts.x;
        tp.y=part[i].pos.y+ts.y;
        if(canGo(tp))
        {
            part[i].pos=tp;
            part[i].speed=ts;
            part[i].fx=f(part[i].pos);
            if(part[i].fx>f(part[i].pbest))
                part[i].pbest=part[i].pos;
        }

    }
}


void calcGbest2()
{
    for(int i=0;i<total;i++){
        if(part[i].fx<f(gbest))
            gbest=part[i].pos;

    }
}

void calc2()
{
    for(int i=0;i<total;i++)
    {
        point ts,tp;
        ts.x=w*part[i].speed.x+c1*rand()/(double)RAND_MAX
        *(part[i].pbest.x-part[i].pos.x)+c2*rand()/(double)RAND_MAX
        *(gbest.x-part[i].pos.x);

        ts.y=w*part[i].speed.y+c1*rand()/(double)RAND_MAX
        *(part[i].pbest.y-part[i].pos.y)+c2*rand()/(double)RAND_MAX
        *(gbest.y-part[i].pos.y);

        tp.x=part[i].pos.x+ts.x;
        tp.y=part[i].pos.y+ts.y;
        if(canGo(tp))
        {
            part[i].pos=tp;
            part[i].speed=ts;
            part[i].fx=f(part[i].pos);
            if(part[i].fx<f(part[i].pbest))
                part[i].pbest=part[i].pos;
        }

    }
}

void PSO(){
    //max
    cout<<"�������ֵ��"<<endl;

    w=0.5;
    c1 = c2 = 1;
    gbest.x=1;
    gbest.y=1;



    part=new particle[total];
    //��ʼ��
    for(int i=0;i<total;i++)
    {
        part[i].speed.x=(rand()+1)/(double)(RAND_MAX+2)*MAX;
        part[i].speed.y=(rand()+1)/(double)(RAND_MAX+2)*MAX;
        part[i].pos.x=(rand()+1)/(double)(RAND_MAX+2)*MAX;
        part[i].pos.y=(rand()+1)/(double)(RAND_MAX+2)*MAX;
        part[i].fx=f(part[i].pos);
        part[i].pbest=part[i].pos;
    }
    calcGbest();
    //PSO���Ĳ���
    for(int i=0;i<cnt;i++)
    {
        calc();//����λ�á��ٶ�
        calcGbest();//����Pgbest
    }
    show();


    double tmpx = gbest.x,tmpy = gbest.y,tmpf = f(gbest);


    //min
    cout<<"������Сֵ��"<<endl;
    w=0.5;
    c1 = c2 = 1;
    gbest.x=1;
    gbest.y=1;



    part=new particle[total];
    //��ʼ��
    for(int i=0;i<total;i++)
    {
        part[i].speed.x=(rand()+1)/(double)(RAND_MAX+2)*MAX;
        part[i].speed.y=(rand()+1)/(double)(RAND_MAX+2)*MAX;
        part[i].pos.x=(rand()+1)/(double)(RAND_MAX+2)*MAX;
        part[i].pos.y=(rand()+1)/(double)(RAND_MAX+2)*MAX;
        part[i].fx=f(part[i].pos);
        part[i].pbest=part[i].pos;
    }
    calcGbest();
    //PSO���Ĳ���
    for(int i=0;i<cnt;i++)
    {
        calc2();//����λ�á��ٶ�
        calcGbest2();//����Pgbest
    }
    show();

    double tmpx2 = gbest.x,tmpy2 = gbest.y,tmpf2 = f(gbest);
    cout<<"���н����"<<endl;
    cout<<"\t\tx\ty\tf\n";
    cout<<"ȫ�����ֵ��\t";
    cout<<tmpx<<"\t"<<tmpy<<"\t"<<tmpf<<"\n";
    cout<<"ȫ����Сֵ��\t";
    cout<<tmpx2<<"\t"<<tmpy2<<"\t"<<tmpf2<<"\n";


}




//����ö��
void boob(){
    double minn = 999999;
    double maxx = -minn;
    double minx,miny,mxx,MAX;
    freopen("print.txt","w",stdout);
    for(double i = 0.0;i<60.0;i+=0.1){
        for(double j=0.0;j<60.0;j+=0.1){
            double x1 = i,x2=j;
            double ans = f(x1,x2);
            printf("%.3f ",ans);

            if(ans>maxx){
                maxx = ans;
                mxx = x1;MAX = x2;
            }
            if(ans<minn){
//                cout<<ans<<" "<<x1<<" "<<x2<<endl;
                minn = ans;
                minx = x1;miny = x2;
            }
//            minn = min(minn,ans);
//            maxx = max(maxx,ans);
        }
        printf("\n");
    }
    freopen("CON","w",stdout);
    printf("MIN = %.8f x1 = %.8f x2 = %.8f \r\nMAX = %.8f x1 = %.8f x2 = %.8f \r\n",minn,minx,miny,maxx,mxx,MAX);
}


int main() {
    srand((unsigned)time(NULL));
    cout<<"********** ��ӭʹ��PSO������� **********"<<endl;
    boob();
    cout<<"������PSO������������:"<<endl;
    cin>>total;
    cout<<"����������:"<<endl;
    cin>>cnt;
    PSO();
//    cout<<"��ͼ��"<<endl;
//    cout<<lossp<<endl;
//    for(int i=0;i<lossp;i++){
//        printf("%.8f\n",loss[i]);
//    }

    return 0;
}


