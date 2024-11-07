template<typename T>
class ODT{
public:
    struct node{
        int l, r;mutable T v;//确保v可变
        //按区间左端点排序
        bool operator <(const node&x)const{return l<x.l;}
    };
    set<node> odt;
    ODT(int l,int r,T x){odt.insert({l,r,x});}
    auto split(int pos){  //分解区间，变成[l,pos-1]和[pos,r]
        auto it=odt.lower_bound({pos,-1,0});//找到所需的pos的迭代器
        if(it!=odt.end()&&it->l==pos)return it;
        --it;//不是的话就说明肯定是在前一个里面
        int l=it->l;
        int r=it->r;
        T v=it->v;
        odt.erase(it);//我们删掉这个区间
        odt.insert({l,pos-1,v});//重新塞入两个区间[l,pos-1],[pos,r]
        return odt.insert({pos,r,v}).first;//返回以pos开头的区间的迭代器
    }
    void assign(int l,int r,T x){//给[l,r]赋值x
        auto itr=split(r+1),itl=split(l);//先找到r+1的迭代器位置，再找l的迭代器位置
        odt.erase(itl,itr);//删掉这一段迭代器
        odt.insert({l,r,x});//重新插入所需区间
    }
    void perf(int l, int r){ //按需修改
        auto itr=split(r+1),itl=split(l);
        for(;itl!=itr;++itl){   
            
        }
    }
};