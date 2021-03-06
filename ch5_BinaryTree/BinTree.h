#ifndef _BINTREE_H
#define _BINTREE_H
#include "BinNode.h"

template <typename T> class BinTree {
protected:
    int _size;
    BinNodePosi(T) _root;
    virtual int updateHeight(BinNodePosi(T));
    void updateHeightAbove(BinNodePosi(T));

public:
    BinTree() : _size(0), _root(nullptr) { }
    ~BinTree() {
        if (_size > 0) {
            remove(_root);
        }
    }
    int remove(BinNodePosi(T) x);
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodePosi(T) root() const { return _root; }
    BinNodePosi(T) insertAsRoot(const T& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, const T& e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, const T& e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& T);
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& T);
    BinTree<T>* secede(BinNodePosi(T) x);
    template <typename VST>
    void travLevel(VST& visit) {
        if (_root) {
            _root->travLevel(visit);
        }
    }
    template <typename VST>
    void travPre(VST& visit) {
        if (_root) {
            _root->travPre(visit);
        }
    }
    template <typename VST>
    void travIn(VST& visit) {
        if (_root) {
            _root->travIn(visit);
        }
    }
    template <typename VST>
    void travPostVST& visit) {
        if (_root) {
            _root->travPost(visit);
        }
    }
};

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {

}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(const T& e) {

}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, const T& e) {

}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, const T& e) {

}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& T) {

}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& T) {

}
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {

}
#endif