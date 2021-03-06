#ifndef _BINNODE_H
#define _BINNODE_H

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p) -> height : -1)
typedef enum { RB_RED, RB_BLACK } RBColor;

#define IsRoot(x) (!(x).parent)
#define IsLChild(x) (!IsRoot(x) && ((x).parent->lChild == &(x)))
#define IsRChild(x) (!IsRoot(x) && ((x).parent->rChild == &(x)))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild != nullptr)
#define HasRChild(x) ((x).rChild != nullptr)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rChild : (p)->parent->lChild)
#define uncle(p) (IsLChild(*((p)->parent)) ? (p)->parent->parent->rChild : (p)->parent->parent->lChild)

template <typename T> struct BinNode {
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lChild;
    BinNodePosi(T) rChild;
    int height;
    int npl;
    RBColor color;

    BinNode()
    : parent(nullptr), lChild(nullptr), rChild(nullptr) { }
    BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, 
            BinNodePosi(T) rc = nullptr, int h = 0, int l = 0, RBColor c = RB_RED)
        : data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) { }

    //int size();
    BinNodePosi(T) insertAsLC(const T&);
    BinNodePosi(T) insertAsRC(const T&);
    //BinNodePosi(T) succ();
    template <typename VST>
    void travLevel(VST&);
    template <typename VST>
    void travPre(VST&);
    template <typename VST>
    void travIn(VST&);
    template <typename VST>
    void travPost(VST&);

    bool operator<(const BinNode& bn) {
        return data < bn.data;
    }
    bool operator=(const BinNode& bn) {
        return data == bn.data;
    }
};


template <typename T>
struct printVST {
    void operator()(const T& e) { std::cout << e << " "; }
};

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(const T& e) {
    return lChild = new BinNode(e, this);
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(const T& e) {
    return rChild = new BinNode(e, this);
}
/*
template <typename T>
int BinNode<T>::size() {

}
template <typename T>
BinNodePosi(T) BinNode<T>::succ() {

}
*/
template <typename T, typename VST> 
void travPre_R(BinNodePosi(T) x, VST& visit) {
    if (x != nullptr) {
        visit(x->data);
        travPre_R(x->lChild, visit);
        travPre_R(x->rChild, visit);
    }
}
template <typename T, typename VST> 
void travIn_R(BinNodePosi(T) x, VST& visit) {
    if (x != nullptr) {
        travIn_R(x->lChild, visit);
        visit(x->data);
        travIn_R(x->rChild, visit);
    }
}
template <typename T, typename VST> 
void travPost_R(BinNodePosi(T) x, VST& visit) {
    if (x != nullptr) {
        travPost_R(x->lChild, visit);
        travPost_R(x->rChild, visit);
        visit(x->data);
    }
}

template <typename T, typename VST>
void travPre_I1(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> s;
    while (x != nullptr) {
        visit(x->data);
        if (HasRChild((*x)) == true) {
            s.push(x->rChild);
        }
        if (HasLChild((*x)) == true) {
            x = x->lChild;
        } else {
            if (s.empty() == true) {
                break;
            }
            x = s.top();
            s.pop();
        }
    }
}

template <typename T, typename VST>
void visitAlongLeftAfterBranch(BinNodePosi(T) x, VST& visit, stack<BinNodePosi(T)>& s) {
    while (x != nullptr) {
        visit(x->data);
        s.push(x->rChild);
        x = x->lChild;
    }
}
template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> s;
    while (true) {
        visitAlongLeftAfterBranch(x, visit, s);
        if (s.empty() == true) {
            break;
        }
        x = s.top();
        s.pop();
    }
}

template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> s;
    while (x != nullptr || !s.empty()) {
        while (x != nullptr) {
            s.push(x);
            // cout << "push: " << x->data << endl;
            x = x->lChild;
        }
        x = s.top();
        s.pop();
        // cout << "pop: " << x->data << endl;
        visit(x->data);
        x = x->rChild;
    }
}

template <typename T, typename VST>
void travIn_I2(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> s;
    while (true) {
        if (x != nullptr) {
            s.push(x);
            x = x->lChild;
        } else {
            if (s.empty() == true) {
                break;
            }
            x = s.top();
            s.pop();
            visit(x->data);
            x = x->rChild;
        }
    }
}

template <typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST& visit) {
    bool backTrackLastTime = false;
    while (x != nullptr) {
    }
}

template <typename T> template <typename VST>
void BinNode<T>::travLevel(VST& visit) {
    queue<BinNodePosi(T)> q;
    BinNodePosi(T) front;
    q.push(this);
    while (!q.empty()) {
        front = q.front();
        q.pop();
        visit(front->data);
        if (HasLChild((*front)) == true) {
            q.push(front->lChild);
        }
        if (HasRChild((*front)) == true) {
            q.push(front->rChild);
        }
    }
    cout << endl;
}
template <typename T> template <typename VST>
void BinNode<T>::travPre(VST& visit) {
    //travPre_R(this, visit);
    //travPre_I1(this, visit);
    travPre_I2(this, visit);
    cout << endl;
}
template <typename T> template <typename VST>
void BinNode<T>::travIn(VST& visit) {
    //travIn_R(this, visit);
    //travIn_I1(this, visit);
    travIn_I2(this, visit);
    cout << endl;
}
template <typename T> template <typename VST>
void BinNode<T>::travPost(VST& visit) {
    travPost_R(this, visit);
    cout << endl;
}

#endif