#include"stack.h"

template <typename T> class binNode{
public:
    T _data;
    binNode * fath;//父节点
    binNode * leftC;//左子节点
    binNode * rightC;//右子节点
    int _height;//高度
    //目前没有颜色
    binNode():
    fath(NULL), leftC(NULL), rightC(NULL), _height(0){}
    binNode(T e):
    _data(e), fath(NULL), leftC(NULL), rightC(NULL), _height(0){}
//操作函数：
    //高度更新：
    void height_renew(){
    if(leftC!=NULL&&rightC!=NULL)_height=(leftC->_height>rightC->_height)?(1+leftC->_height):(1+rightC->_height);//当两个子节点都不为空时，取子节点高度大者加一
    if(leftC!=NULL&&rightC==NULL)_height=leftC->_height+1;
    if(leftC==NULL&&rightC!=NULL)_height=rightC->_height+1;
    }
    //插入节点：
    void insertL_node(binNode<T> &E){
        if(this->leftC!=NULL) std::cout<<"A left child node is replaced."<<std::endl;
        this->leftC=&E; E.fath=this; this->height_renew();}//插入左子节点
    void insertR_node(binNode<T> &E){
        if(this->rightC!=NULL) std::cout<<"A right child node is replaced."<<std::endl;
        this->rightC=&E; E.fath=this; this->height_renew();}//插入右子节点
    void insertL_T(T E){binNode<T> * X = new binNode;
        /*创建一个新的节点，把节点的内容赋值完成，余下处理同节点插入*/
        X->_data = E;
        if(this->leftC!=NULL) std::cout<<"A left child node is replaced."<<std::endl;
        this->leftC=X; X->fath=this;this->height_renew();
        std::cout<<"新节点的height:"<<_height<<std::endl;}//插入左子节点的内容
    void insertR_T(T E){binNode<T> * X = new binNode; X->_data = E;
        if(this->rightC!=NULL) std::cout<<"A right child node is replaced."<<std::endl;
        this->rightC=X; X->fath=this; this->height_renew();}
    //删除节点：
    void remove_left(){this->leftC = NULL;_height--;}
    void remove_right(){this->rightC = NULL;_height--;}
};

template <typename T> class binTree{
public:
    int _size;
    binNode<T> * root;
//构造函数：
    binTree():
    _size(0), root(NULL){}
    binTree(binNode<T> E):
    _size(1), root(&E){}
    binTree(binNode<T> * E):
    _size(1), root(E){}
//根节点插入函数：
    void ROOT(binNode<T> * E){root = E;}
    void ROOT(T e){root = new binNode<T>(e);}
    void ROOT(){root = new binNode<T>;}
    /*函数重载*/
//成员函数：
    //virtual int _tree_height_update(binNode<T> * Tr);//更新节点Tr的高度，利用虚函数以实现多态
    void _above_height_update(binNode<T> * Tr){binNode<T> * E;
        for(E=Tr;E!=root;E=E->fath) E->height_renew();
        root->height_renew();
    }//更新节点Tr以上的所有节点高度
//节点插入：
    void lc_insert(binNode<T> &E, binNode<T> &X){/*E为需要插入的节点，X为已经在树中的节点*/
        X.insertL_node(E); _size++; _above_height_update(&X);}
    void lc_insert(T const& e, binNode<T> &X){
        X.insertL_T(e); _size++; _above_height_update(&X);}
    void rc_insert(binNode<T> &E, binNode<T> &X){/*E为需要插入的节点，X为已经在树中的节点*/
        X.insertR_node(E); _size++; _above_height_update(&X);}
    void rc_insert(T const& e, binNode<T> &X){
        X.insertR_T(e); _size++; _above_height_update(&X);}
//节点删除：
    void lc_remove(binNode<T> &X){X.remove_left(); _size--; _above_height_update(&X);}//左节点删除，暂时只支持单个节点的删除
    void rc_remove(binNode<T> &X){X.remove_right(); _size--; _above_height_update(&X);}
};

int main(){
    binNode<int> X1(1);
    binNode<int> X2(2);
    binNode<int> X3(3);
    binTree<int> tree1;
    tree1.ROOT();
    tree1.lc_insert(X1, *tree1.root);
    tree1.lc_insert(X2, X1);
    std::cout<<"X1的高度："<<X1._height<<std::endl;
    std::cout<<"根节点的高度："<<tree1.root->_height<<std::endl;
    std::cout<<tree1._size<<std::endl;
    tree1.lc_remove(X1);
    std::cout<<X1._height<<std::endl;
    std::cout<<tree1._size<<std::endl;
    return 0;
}

//2020.8.8创建一个文件来完成二叉树的代码。
  /*试写binnode的代码。最终完成了binNode类全部和部分binTree的编写。
  问题：binNode的_height变量无法正常更新*/
//2020.8.9完成了_height的正常更新。
  /*C++的函数传参需要各个方式有不同，直接传不能改变参数的值，必须要利用引用和地址
   完成了祖先高度更新函数（_above_height_update）和节点高度更新函数（_height_renew）*/
//2020.8.10在程序中添加栈与队列的结构，以期能辅助二叉树的遍历。
  /*在stack.h头文件之中完成了部分栈的函数功能*/
