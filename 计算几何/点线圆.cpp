#include <bits/stdc++.h>
#define int long long
mt19937_64 rnd(time(0));
using namespace std;

// cout << fixed << setprecision(15);

const double eps=1e-10;
const int INF=0x7f7f7f7f;
const double pi = acos(-1.0);
int dcmp(double x){
    return (fabs(x)<=eps)?0:(x<0?-1:1);
}
struct Point{
    double x,y;
    Point(double X=0,double Y=0){x=X,y=Y;}
};
inline double DistanceToPoint(Point a,Point b){// 点到直线的距离
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
struct Vector{//向量（数学意义）
    double x,y;
    Vector(double X=0,double Y=0){x=X,y=Y;}
};
inline Vector operator-(Point x,Point y){// 点-点=向量
    return Vector(x.x-y.x,x.y-y.y);
}
inline double operator*(Vector x,Vector y){ // 向量叉积
    return x.x*y.y-x.y*y.x;
}
inline double operator^(Vector x,Vector y){ // 向量点积
    return x.x*y.x+x.y*y.y;
}
inline double len(Vector x){ // 向量模长
    return sqrt(x.x*x.x+x.y*x.y);
}
double calrad(Vector a, Vector b){  //计算向量a与b的夹角
    return fabs(atan2(fabs(a*b),fabs(a^b)));
}
template<typename T>//把一个点或向量逆时针转rad度
T PointRotate(T p,double rad){  
    return T(p.x*cos(rad)-p.y*sin(rad),p.x*sin(rad)+p.y*cos(rad));
}
Point move_point(Point p,Vector v,double l){//将p点沿v方向移动len
    double length=len(v);Point res;
    res.x=p.x+l*(v.x/length);
    res.y=p.y+l*(v.y/length);
    return res;
}
struct Line{        //定义直线
    Point x;Vector y;
    Line(){}
    Line(Point X,Vector Y){x=X,y=Y;}
    Line(Point X,Point Y){x=X,y=Y-X;}
};
inline double DistanceToLine(Point P,Line x){// 点到直线的距离
    Vector v1=x.y, v2=P-x.x;
    return fabs(v1*v2)/len(v1);
}
inline Vector calnVector(Line a){   //计算法向量
    return {a.y.y,-a.y.x};
}
inline Point calIntersection(Line a,Line b){//计算两线交点  必须先用叉积判断两条直线是否平行
    Vector p=a.x-b.x;
    double t=(b.y*p)/(a.y*b.y);
    return {a.x.x+a.y.x*t,a.x.y+a.y.y*t};
}
inline int PointonLine(Point p,Line l){//0点在线上  1在线左侧 -1在线右侧（关于直线的向量）
    double res=(l.y)*(p-l.x);//叉积
    return dcmp(res);
}
inline int LineonLine(Line a,Line b){//0重合 1平行 2垂直 3相交
    if(fabs(a.y*b.y)<=eps){//叉积
        if(fabs(a.y*(a.x-b.x))<=eps)return 0;
        else return 1;//用两条线的点连向量与一条线的向量判断
    }
    else if(fabs(a.y^b.y)<=eps) return 2;//点积
    else return 3;
}
inline Point calProjectiononLine(Point p,Line l){//计算p在直线l上的投影
    double t=(l.y^(p-l.x))/(l.y^l.y);
    return {p.x+l.y.x*t,p.y+l.y.y*t};
}
struct Circle{
    Point o;double r;
    Circle(){}
    Circle(Point O,double R){o=O;r=R;}
};
inline int PointinRound(Point p,Circle o){       //0 圆上 -1 圆内 1 圆外  
    double dis=DistanceToPoint(o.o,p);
    return dcmp(dis-o.r);
}

inline Circle calRound(Point a,Point b,Point c){//给定3个点计算外接圆
    double a1=b.x-a.x,a2=c.x-a.x,b1=b.y-a.y,b2=c.y-a.y;
	double c1=(b.x*b.x-a.x*a.x+b.y*b.y-a.y*a.y);
	double c2=(c.x*c.x-a.x*a.x+c.y*c.y-a.y*a.y);
	Point o={(b2*c1-b1*c2)/(b2*a1*2-b1*a2*2),(a2*c1-a1*c2)/(a2*b1*2-a1*b2*2)};
	return {o,DistanceToPoint(a,o)};		//返回圆心和半径
}
inline int LineinCircle(Line a,Circle o){ //线和圆的关系  0 相切  1 相离 -1 相交
    double d=DistanceToLine(o.o,a);
    return dcmp(d-o.r);
}
inline int CircleinCircle(Circle a,Circle b){// 圆和圆的关系  0重合 1外切 2相离  -1内切 -2 包含 3相交
    if(a.r<b.r)swap(a,b);
    double d=DistanceToPoint(a.o,b.o);
    if(fabs(a.r-b.r)<=eps&&fabs(a.o.x-b.o.x)<=eps&&fabs(a.o.y-b.o.y)<=eps)return 0;
    else if(fabs(d-a.r-b.r)<=eps)return 1;
    else if(fabs(d-(a.r-b.r))<=eps)return -1;
    else if(d>=a.r+b.r)return 2;
    else if(d<=a.r-b.r)return -2;
    else return 3;
}
inline vector<Line> cal_tangent(Point p,Circle o){
    Vector tmp(p-o.o);double d=len(tmp);//点在圆上 一条切线
    if(fabs(o.r-d)<=eps) return {{p,PointRotate(tmp,pi/2)}};
    else if(o.r>d) return {};//点在圆内 无切线
    else{
        double rad=asin(o.r/d);//两条切线 旋转返回
        return {{p,PointRotate(tmp,rad)},{p,PointRotate(tmp,-rad)}};
    }
}

inline double calarea(vector<Point> &poly){ //计算凸包面积，把凸包拆成三角形计算 （凸包开头结尾是同一个点)
    double area=0;
    if(poly.size()==3)return 0;
    for(int i=1;i<poly.size()-2;i++){
        area+=Vector(poly[i]-poly[0])*Vector(poly[i+1]-poly[0]);
    }
    return area/2;      //向量叉积计算面积
}


/***********************************************************************************/

vector<Point> Andrew(vector<Point> poly){ // Andrew算法求凸包 输入下标1开始
    int top=0,n=poly.size()-1;vector<int> used(n+2),stk(n+2);
    sort(poly.begin()+1,poly.end(),[&](Point x,Point y){
        return (x.x==y.x)?(x.y<y.y):(x.x<y.x);
    });
    stk[++top]=1;
    for(int i=2;i<=n;i++){//下面取等则会删除三点共线，否则会保留共线点
        while(top>1&&dcmp((poly[stk[top]]-poly[stk[top-1]])*(poly[i]-poly[stk[top]]))<=0){
            used[stk[top--]]=0;
        }
        used[i]=1;
        stk[++top]=i;
    }
    int tmp=top;
    for(int i=n-1;i;i--){
        if(used[i]) continue;//下面取等则会删除三点共线，否则会保留共线点
        while(top>tmp&&dcmp((poly[stk[top]]-poly[stk[top-1]])*(poly[i]-poly[stk[top]]))<=0){
            used[stk[top--]]=0;
        }
        used[i]=1;
        stk[++top]=i;
    }
    vector<Point> a;//从0开始的凸包 且最后一个点和起点相同
    for(int i=1;i<=top;i++){
        a.push_back(poly[stk[i]]);
    }
    return a;
}
vector<Point> HalfPlane(vector<Line> line){//P&I算法计算半平面交 base1
    sort(line.begin()+1,line.end(),[&](Line x,Line y){
        double a=atan2(x.y.y,x.y.x),b=atan2(y.y.y,y.y.x);
        return fabs(a-b)<=eps?PointonLine(x.x,y)==1:a<b;
    });
    vector<Line> q(line.size());
    int head=0,tail=0;q[tail]=line[1];
    for(int i=2;i<line.size();i++){
        if(fabs(atan2(q[tail].y.y,q[tail].y.x)-
            atan2(line[i].y.y,line[i].y.x))<=eps)continue;
        while(head<tail){//处理队尾
            Point p=calIntersection(q[tail],q[tail-1]);
            if(PointonLine(p,line[i])!=1)tail--;
            else break;
        }
        while(head<tail){//处理队首
            Point p=calIntersection(q[head],q[head+1]);
            if(PointonLine(p,line[i])!=1)head++;
            else break;
        }
        q[++tail]=line[i];
    }
    while(head<tail){//处理队列
        Point p=calIntersection(q[tail],q[tail-1]);
        if(PointonLine(p,q[head])!=1)tail--;
        else break;
    }
	q[++tail]=q[head];
    //返回半平面交直线
    // vector<Line> res(tail-head+1);
    // for(int i=head;i<=tail;i++)res[i-head]=q[i];
    //返回半平面交多边形
    vector<Point> res(tail-head+1);
    for(int i=head;i<tail;i++)res[i-head]=calIntersection(q[i],q[i+1]);
    res[tail-head]=res[0];
    return res;//返回值首尾是同一个元素
}
/**********************************************************************************/

// 旋转卡壳  计算凸包直径  输入一个凸包（0开始,且最后一个点和初始点相同）
double RoatingCalipers(vector<Point> &poly){
    if(poly.size()==3) return len(poly[1]-poly[0]);
    int cur=0;
    double ans=0;
    for(int i=0;i<poly.size()-1;i++){
        Line line(poly[i],poly[i+1]);
        while(DistanceToLine(poly[cur], line) <= DistanceToLine(poly[(cur+1)%poly.size()], line)){
            cur=(cur+1)%poly.size();
        }
        ans=max(ans, max(len(poly[i]-poly[cur]), len(poly[i+1]-poly[cur])));
    }
    return ans;
}


// 旋转卡壳  计算凸包最小矩形覆盖  输入一个凸包（0开始,且最后一个点和初始点)
vector<Point> minSquareCover(vector<Point> poly){   //返回矩形4个节点（且最后一个节点就是第一个节点
    vector<Point> res(5),tmp(5);double area=1e20,tarea=0;
    if(poly.size()<=3)return vector<Point>();   //如果连两个点都没有则返回空数组
    int cur=0,l=0,r=0; //cur对点  l左边点 r右边点
    int flag=1;
    for(int i=0;i<poly.size()-1;i++){
        Line line(poly[i],poly[i+1]);
        while(DistanceToLine(poly[cur], line) <= DistanceToLine(poly[(cur+1)%poly.size()], line)){
            double a=DistanceToLine(poly[cur], line),b=DistanceToLine(poly[(cur+1)%poly.size()], line);
            cur=(cur+1)%poly.size();
        }
        Vector t(poly[i+1]-poly[i]);
        while((t^Vector(poly[(r+1)%poly.size()]-poly[r]))>=-eps){
            r=(r+1)%poly.size();                                
        }
        t=poly[i]-poly[i+1];if(flag){l=cur;flag=0;}
        while((t^Vector(poly[(l+1)%poly.size()]-poly[l]))>=-eps){   
            l=(l+1)%poly.size();
        }
        Vector nvec=calnVector(line);
        tmp[4]=tmp[0]=calIntersection(line,{poly[r],nvec});
        tmp[1]=calIntersection({poly[cur],line.y},{poly[r],nvec});
        tmp[2]=calIntersection({poly[cur],line.y},{poly[l],nvec});
        tmp[3]=calIntersection(line,{poly[l],nvec});
        tarea=calarea(tmp);
        if(tarea<area){
            area=tarea;
            res=tmp;
        }
    }
    return res;
}


/**********************************************************************************/

Circle minCirclecover(vector<Point> a){     //求最小圆覆盖 O(n)
    random_shuffle(a.begin(),a.end());//随机化点集 保证均摊复杂度
    Circle res{a[0],0};
    int n=a.size();
    for(int i=1;i<n;i++){
        if(PointinRound(a[i],res)==1){
            res={a[i],0};
            for(int j=0;j<i;j++){
                if(PointinRound(a[j],res)==1){
                    res.o.x=(a[i].x+a[j].x)/2;
                    res.o.y=(a[i].y+a[j].y)/2;
                    res.r=DistanceToPoint(res.o,a[j]);
                    for(int k=0;k<j;k++){
                        if(PointinRound(a[k],res)==1)
                            res=calRound(a[i],a[j],a[k]);
                    }
                }
            }
        }
    }
    return res;
}
double PlaneNearestPoint(vector<Point> poly){//base1 返回开方后的值
    sort(poly.begin()+1,poly.end(),[&](Point x,Point y){
        return x.x<y.x;
    });
    vector<Point> tmp(poly.size());
    function<double(int,int)> work=[&](int l,int r){
        if(l==r)return 1e100;
        int m=(l+r)/2,k=0;
        double dis=min(work(l,m),work(m+1,r));
        for(int i=l;i<=r;i++)
            if(fabs(poly[m].x-poly[i].x)<=dis)
                tmp[++k]=poly[i];
        sort(tmp.begin()+1,tmp.begin()+k+1,[&](Point x,Point y){
            return x.y<y.y;
        });
        for(int i=1;i<=k;i++)
            for(int j=i+1;j<=k&&tmp[j].y-tmp[i].y<dis;j++)
                dis=min(dis,len(tmp[j]-tmp[i]));
        return dis;
    };
    return work(1,poly.size()-1);
}
double PlaneNearestPoint(vector<Point> poly){//base1 人类智慧算法
    int rad=rnd(),n=poly.size()-1;
    for(int i=1;i<=n;i++)poly[i]=PointRotate(poly[i],rad);
    sort(poly.begin()+1,poly.end(),[&](Point x,Point y){
        return x.x*x.y<y.x*y.y;
    });
    double l=INF;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i&&j<=60;j++){
            double t=len(poly[i]-poly[j+i]);
            if(dcmp(l-t)==1)l=t;
        }
    }
    return l;
}
/******************************************************************/
//三维凸包
namespace _3D{
    double reps(){return (rnd()/(double)INF-0.5)*eps;}
    struct Point{//向量和点
        double x,y,z;
    };
    vector<Point> A;
    void shake(Point &a){a.x+=reps();a.y+=reps();a.z+=reps();}//扰动
    double len(Point a){
        return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
    }
    Point operator-(Point a,Point b){
        return{a.x-b.x,a.y-b.y,a.z-b.z};
    }
    Point operator*(Point a,Point b){//叉积
        return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};
    }
    double operator^(Point a,Point b){//点积
        return a.x*b.x+a.y*b.y+a.z*b.z;
    }
    struct Plane{
        int v[3];//存储3个点 在原来的集合中的坐标
        Point normal(){//计算法向量  法向量的模长的一半是平面面积
            return (A[v[1]]-A[v[0]])*(A[v[2]]-A[v[0]]);
        }
        bool isabove(Point b){//点面关系 上或者下
            return ((b-A[v[0]])^normal())>0;
        }
        double dis(Point p){//点到面的距离
            Point t=normal(); 
            return fabs(((p-A[v[0]])^t)/len(t));
        }
    };
    vector<Plane> Convex_3D(){
        int n=A.size()-1;
        for(int i=1;i<=n;i++)shake(A[i]);
        vector<Plane> res(3*n+1);
        res[1]={1,2,3},res[2]={3,2,1};
        vector<vector<int>> vis(n+1,vector<int>(n+1));
        vector<Plane> tmp(3*n+1);int t=0,cnt=2;
        for(int i=4;i<=n;i++){
            for(int j=1,v;j<=cnt;j++){
                if(!(v=res[j].isabove(A[i])))tmp[++t]=res[j];//记录哪些面要被保留
                //逆时针记录(i,j)方向这个面是否照光
                for(int k=0;k<3;k++)vis[res[j].v[k]][res[j].v[(k+1)%3]]=v;
            }
            for(int j=1;j<=cnt;j++){
                for(int k=0;k<3;k++){
                    int x=res[j].v[k],y=res[j].v[(k+1)%3];
                    //如果这条边的一边被照亮一遍没被照亮，则加面
                    if(vis[x][y]&&!(vis[y][x]))tmp[++t]={x,y,i};
                }
            }
            for(int j=1;j<=t;j++)res[j]=tmp[j];
            cnt=t;t=0;
        }
        res.erase(res.begin()+cnt+1,res.end());
        return res;
    }
    inline void solve(){
        int n;cin>>n;
        A.resize(n+1);
        for(int i=1;i<=n;i++)cin>>A[i].x>>A[i].y>>A[i].z;
        auto res=Convex_3D();
        double area=0;
        for(int i=1;i<res.size();i++)
            area+=len(res[i].normal());
        cout<<area/2<<endl;//面积
        double volume=0;
        //凸包上任意一点，计算所有三棱锥的体积 
        Point p=A[res[1].v[0]];
        for(int i=1;i<res.size();i++)
            volume+=len(res[i].normal())*res[i].dis(p);
        cout<<volume/6<<endl;//面积除2 体积除3 最后处理
    }
};







