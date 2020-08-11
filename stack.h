#include<iostream>

template <typename T> class node{
public:
    T _data;
    node * succ;
    node * pred;
//构造函数:
    node():succ(NULL), pred(NULL){}
    node(T const& e):succ(NULL), pred(NULL), _data(e){}
//添加与删除后继:
    /*这里不需要复杂的功能，目的在于利用列表实现栈与队列，只保留最简单的功能。*/
    void add_succ(T const& e){
        node<T> * E = new node(e); E->pred = this;//创建一个新节点
        if(this->succ){//若当前节点的后继非空
            this->succ->pred = E;//当前节点的后继的前驱为添加的节点
            E->succ = this->succ;//添加节点的后继为当前节点的后继
        }
        this->succ = E;//当前节点的后继为添加节点
    }
    void add_succ(node<T> * E){//这里函数进行重载。与上面那个函数类似，缺少了新建节点步骤
        E->pred = this;
        if(this->succ){
            this->succ->pred = E;
            E->succ = this->succ;
        }
        this->succ = E;
    }
    void remove_succ(){
        if(!(this->succ)){std::cout<<"This node has no succ to remove."<<std::endl; return;}//判断有无后继
        node<T> * X = this->succ;//把当前节点的后继存储起来
        if(this->succ->succ){//判断后继是否是尾节点
            this->succ->succ->pred = this;//当前节点的后继的后继的前驱指向当前节点
            this->succ = this->succ->succ;//当前节点的后继指向当前节点的后继的后继
            return;
        }
        else {this->succ = NULL;}
        delete X;
    }
};

template <typename T> class stack{//栈的功能实现
public:
    int _size;
    node<T> * _header, _trailer;
//构造函数:
    stack():_size(0){_header->succ = _trailer; _trailer->pred = _header;}
//功能函数:
    void pop(T const& e){//压入栈内
        _trailer->pred->add_succ(e);
    }
    void pop(node<T> * E){
        _trailer->pred->add_succ(E);
    }
};

//2020.8.10完成了列表的节点的定义，还有部分栈的功能，打算直接跳过列表定义栈与队列类。
