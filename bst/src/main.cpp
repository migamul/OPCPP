#include <iostream>

#include "bin_stablo.h"

using namespace std;

void visit(int &data)
{
    cout << data << " ";
}

int main()
{
    // Vlastiti testovi
    //throw "Not implemented.";

    BinarySTree<int> t;

    ///test empty
    cout << t.empty() << endl;

    ///test insert
    t.insert(1);
    t.insert(2);
    t.insert(5);
    t.insert(12);
    t.insert(21);
    t.insert(3);

    cout << t.empty() << endl;

    ///test size
    cout << t.size() << endl;

    ///test isInTree
    cout << t.isInTree(4) << " " << t.isInTree(3) << endl;

    ///test clear
    //t.clear();
    //cout << t.size();

    ///test preorder
    t.preOrder(visit);
    cout << endl;

    ///test postorder
    t.postOrder(visit);
    cout << endl;

    ///test inorder
    t.inOrder(visit);
    cout << endl;

    ///test remove
    t.remove(21);
    cout << t.size() << endl;
    cout << t.isInTree(21) << endl;
    t.preOrder(visit);
    cout << endl;
    t.postOrder(visit);
    cout << endl;
    t.inOrder(visit);
    cout << endl;

    t.remove(&t.root);

    return 0;
}
