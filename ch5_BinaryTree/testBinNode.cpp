#include "BinNode.h"
#include <iostream>

using namespace std;

int main()
{
    BinNode<char> node1('A', nullptr);

    cout << "data: " << node1.data << endl;
    cout << "parent: " << node1.parent << endl;
    cout << "lChild: " << node1.lChild << endl;
    cout << "rChild: " << node1.rChild << endl;

    node1.insertAsLC('B');
    node1.insertAsRC('C');

    cout << endl;

    cout << "data: " << node1.data << endl;
    cout << "parent: " << node1.parent << endl;
    cout << "lChild: " << node1.lChild << endl;
    cout << "rChild: " << node1.rChild << endl;

    cout << endl;

    cout << "data: " << node1.data << endl;
    cout << "parent: " << node1.parent << endl;
    cout << "lChild: " << node1.lChild << endl;
    cout << "lChild data: " << node1.lChild->data << endl;
    cout << "lChild parent: " << node1.lChild->parent->data << endl;
    cout << "rChild: " << node1.rChild << endl;
    cout << "rChild data: " << node1.rChild->data << endl;
    cout << "rChild parent: " << node1.rChild->parent->data << endl;

    (node1.lChild)->insertAsLC('D');
    (node1.lChild)->insertAsRC('E');
    (node1.rChild)->insertAsLC('F');
    (node1.rChild)->insertAsRC('G');

    printVST<char> visit;

    node1.travPre(visit);
    node1.travIn(visit);
    node1.travPost(visit);
    node1.travLevel(visit);

    system("pause");
    return 0;
}