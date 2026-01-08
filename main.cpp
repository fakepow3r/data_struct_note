#include "Tree.h"
#include <iostream>
#include <vector>
int main() {
    Tree tree;
    tree.build();
    vector<vector<ElemType>> result;
    tree.BFS(result); // 调用层序遍历
    // 输出结果
    cout << "层序遍历结果：" << endl;
    for (auto& level : result) {
        for (int val : level) {
            cout << val << " ";
        }
        cout<<endl;
    }
    cout << "=================" << endl;
    tree.non_recursive_preorder();
    tree.non_recur_posorder();
    bool isbst=tree.isBST();
    cout << "树是否为BST：" << (tree.isBST() ? "是" : "否") << endl;
    bool iscbt = tree.isCBT();
    cout << "树是否为CBT： " << (iscbt ? "是" : "否") << endl;
    bool isb=tree.isBBT();
    cout << "树是否为BBT： " << (isb ? "是" : "否") << endl;
    bool isbst_rec = tree.isBST_rec();
    cout << "树是否为BST：" << (isbst_rec ? "是" : "否") << endl;
    bool isf = tree.isF();
    cout<< "树是否为F：" << (isf ? "是" : "否") << endl;
    return 0;
}