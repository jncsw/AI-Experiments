#include<bits/stdc++.h>

using namespace std;
const int MAX = 100000;
typedef long long ll;
int total = 0;
int cnt = 0;
//获取随机数
ll getRand(ll a,ll b){
    return (rand() % (b-a+1))+ a;
}
ll gene2[MAX];//变异后
ll gene3[MAX];//后代

int p = 0;
double x1,x2;
double loss[MAX];
int lossp = 0;

double getVal(ll g){
    //计算x1,x2
    x1 = ((g&0xfff) - 2048) * 0.001;
    x2 = ((g>>12) - 2048) * 0.001;
//    printf("x1 = %.8f and x2 = %.8f \r\n",x1,x2);

    double ans = 100.0 * (x1*x1 - x2) * (x1*x1 - x2) + (1.0 - x1) * (1.0 - x1);
//    printf("ans = %.8f\r\n",ans);

    return ans;

}

void printGA(ll g){//输出结果

    cout<<"x1 = "<<((g&0xfff) - 2048) * 0.001<<", x2 = "<<((g>>12) - 2048) * 0.001<<", f(x1,x2) = ";
    double ans = getVal(g);
    loss[lossp++] = ans;

    printf("%.8f\r\n",ans);

}

bool cmp(ll x,ll y){//排序用
    double val = getVal(x)-getVal(y);
    return (val<0.0?0:1);

}
ll genet[MAX*20];
void GA(){//遗传算法
    ll gene[total+MAX];
    //生成初始DNS
    for(int i=0;i<total;i++){
        gene[i] = getRand(0,(1<<24)-1);
    }

    for(int ti=0;ti<cnt;ti++){
        cout<<"Time "<<ti<<": ";
        //随机单个变异
        for(int i = 0;i<total;i++){
            gene2[i] = gene[i] ^ (1<<getRand(0,23));
        }
        p=0;
        //产生后代
        for(int i=0;i<total;i++){
            for(int j=0;j<total;j++){
                if(i==j)continue;
                ll mask = (1<<getRand(0,23))-1;
                ll g1 = gene[i];
                ll g2 = gene[j];
                gene3[p++] = (g2 & ~mask | g1 & mask);
                gene3[p++] = (g1 & ~mask | g2 & mask);

            }
        }
        //DNS汇总
        int st = 0;
        for(int i=0;i<total;i++){
            genet[st++] = gene[i];
            genet[st++] = gene2[i];
        }
        for(int i=0;i<p;i++){
            genet[st++] = gene3[i];
        }
        //优胜劣汰
        sort(genet,genet+st,cmp);
        for(int i=0;i<total;i++)gene[i] = genet[i];
        //展示最优结果
        printGA(gene[0]);
    }

}


void boob(){
    double minn = 999999;
    double maxx = -minn;
    double minx,miny,mxx,mxy;
    for(double i = -2.048;i<2.048;i+=0.001){
        for(double j=-2.048;j<2.048;j+=0.001){
            double x1 = i,x2=j;
            double ans = 100.0 * (x1*x1 - x2) * (x1*x1 - x2) + (1.0 - x1) * (1.0 - x1);
            if(ans>maxx){
                maxx = ans;
                mxx = x1;mxy = x2;
            }
            if(ans<minn){
                minn = ans;
                minx = x1;miny = x2;
            }
//            minn = min(minn,ans);
//            maxx = max(maxx,ans);
        }
    }
    printf("MIN = %.8f x1 = %.8f x2 = %.8f \r\nMAX = %.8f x1 = %.8f x2 = %.8f \r\n",minn,minx,miny,maxx,mxx,mxy);
}


int main() {
    srand((unsigned)time(NULL));
    cout<<"********** 欢迎使用遗传算法程序 **********"<<endl;
    boob();
    cout<<"请输入种群个体数:"<<endl;
    cin>>total;
    cout<<"请输入轮数:"<<endl;
    cin>>cnt;
    GA();
//    cout<<"绘图："<<endl;
//    cout<<lossp<<endl;
//    for(int i=0;i<lossp;i++){
//        printf("%.8f\n",loss[i]);
//    }

    return 0;
}

