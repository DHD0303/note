# 二叉查找树C语言实现  
* 二叉查找树是一种特殊的树，它的左子树的所有值均小于它本身，它的右子树的值均大于它本身，从而达到高效查找的目的。具体实现如下。  
* 基本思路，从节点开始查找，如果待插入数据大于它，则向右继续查找，否则向左进行查找，直到查到一个为空的节点，就是节点不存在，则在该位置加入一个新节点存储该数据。这个过程类似于快排，但是二叉查找树的要求是无相同元素。具体代码如下：  
```
#include<stdio.h>
#include<malloc.h>

typedef struct Node{
  int data;
  struct Node * left;
  struct Node * right;
}Node, * pNode;

int insert_search_tree(pNode * root, int data) { //返回值0成功，1为分配内存失败，2为元素已存在
  if(*root == NULL){ //如果该树为空则新建根节点
    *root = (pNode)malloc(sizeof(Node));
    if(*root == NULL) return 1;
    (*root)->left = (*root)->right = NULL;
    (*root)->data = data;
    return 0;
  }
  pNode temp = *root;

  while(1) {
    if( data > temp->data ) { //如果待插入数据比当前节点大则放到该节点右边
      if(temp->right == NULL) {
        temp->right = (pNode)malloc(sizeof(Node));
        temp = temp->right;
        temp->left = temp->right = NULL;
        temp->data = data;
        return 0;
      } else {
        temp = temp->right;
      }
    } else if( data < temp->data ) {//如果待插入数据比当前节点小则放到该节点左边
      if(temp->left == NULL) {
        temp->left = (pNode)malloc(sizeof(Node));
        temp = temp->left;
        temp->left = temp->right = NULL;
        temp->data = data;
        return 0;
      } else {
        temp = temp->left;
      }
    } else { //如果待插入数据与当前节点一样则返回插入失败
      return 2;
    }
  }

}

void inorder_traversal(pNode root) { //中序遍历
  if( root == NULL) return;
  inorder_traversal(root->left);
  printf("%d ", root->data);
  inorder_traversal(root->right);

  return;
}

int main(void) {
  int i, a[13] = {-100, 4, 6, -10, 9, 46, -4, 3, 6, 5, 8, 44, 20};
  pNode root = NULL;
  for(i=0; i<13; i++) {
    insert_search_tree(&root, a[i]); //依次插入每个数据
  }
  inorder_traversal(root);

  return 0;
}

```  
* 查找，删除节点后面再写