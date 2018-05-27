# 二叉查找树C语言实现  
* 二叉查找树是一种特殊的树，它的左子树的所有值均小于它本身，它的右子树的值均大于它本身，从而达到高效查找的目的。具体实现如下。  
* 基本思路，从节点开始查找，如果待插入数据大于它，则向右继续查找，否则向左进行查找，直到查到一个为空的节点，就是节点不存在，则在该位置加入一个新节点存储该数据。这个过程类似于快排，但是二叉查找树的要求是无相同元素。  
* 二叉树的查找就是根据二叉树左子树的节点均小于该节点，右子树的值均大于该节点，一路向下查找。  
* 二叉树的删除比较难处理，要考虑父元素的指向，分两种情况讨论，分别是左右都不空和左右至少有一个空，左右都不空的时候，右边的最小节点均大于该节点的左子树值，而小于右子树所有值，除了它本身，那么把它的值放到这个待删除节点，再把它删除，就相当于删除了这个节点。而左右有一个空只需要让他的父元素指向它的下一个元素，如果没有，则赋值为NULL，再删除该节点即可。这里删除提供了两种写法，第一种写法的参数和第二种有少许不同，请注意一下。
```
#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

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

pNode find(pNode root, int value) { //查找该节点，并返回指向该节点的指针
  while (root != NULL) {
    if(root->data == value) {
      return root;
    } else if ( root->data < value ) {
      root = root->right;
    } else {
      root = root->left;
    }
  }

  return root;
}

pNode find_min(pNode root) {
  while(root->left != NULL) root = root->left;
  return root;
}

// bool delete_note(pNode * roots, int value) { //非递归写法
//   pNode root = *roots;
//   pNode father=root;
//   while (root != NULL) {//查找待删除节点并保存父节点
//     if(root->data == value) {
//       break;
//     } else if ( root->data < value ) {
//       father = root;
//       root = root->right;
//     } else {
//       father = root;
//       root = root->left;
//     }
//   }
//   if (root == NULL) return false;//没有找到该节点
//
//   if( root->left && root->right ) {
//    //该节点左右子树均非空，则把右子树的最小值赋给该节点并且删除右子树最小节点，达到删除该节点目的,理论依据为二叉树性质，可自行理解
//     pNode temp = find_min(root->right);
//     root->data = temp->data;
//     root = root->right;
//     if( root == temp ) {
//       root->right = NULL;
//     } else {
//       while( root->left != temp ) root = root->left;
//     }
//     free(temp);
//     return true;
//   }
//   if( root == father ) {//这种情况删除根节点
//     *roots = root->left!=NULL?root->left:root->right;
//     free(root);
//     return true;
//   }
//   //下面是普通操作，情况为只有左子树或者只有右子树
//   if( root->left ) {
//     (father->left == root)?(father->left = root->left):(father->right = root->left);
//     free(root);
//   } else if( root->right ) {
//     (father->left == root)?(father->left = root->right):(father->right = root->right);
//     free(root);
//   } else {
//     (father->left == root)?(father->left = NULL):(father->right = NULL);
//     free(root);
//   }
//
//   return true;
// }

pNode delete_note(pNode root, int value) { //递归写法
  pNode temp = NULL;
  if( root == NULL ) return NULL;
  if( root->data > value ) {
    root->left = delete_note( root->left, value ); //与上面循环的思想一样，如果下一个点被删除，那么他就指向下一个应该在此位置的点;
  } else if ( root->data < value ) {
    root->right = delete_note( root->right, value );
  } else if( root->left && root->right ) {
    temp = find_min( root->right );
    root->data = temp->data;
    root->right = delete_note( root->right, temp->data ); // 如果右节点为叶子，那么要使它的right等于NULL;
  } else {
    temp = root;
    if( root->left == NULL ) {
      root = root->right; //可能左右均为NULL此时赋值为NULL就可以了,这里和上面的配合，使返回的root返回它的父节点应该指向的位置
    } else if( root->right == NULL ) {
      root = root->left;
    }
    free( temp );
  }

  return root;
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
  printf("\n");
  root = delete_note(root, -4);
  inorder_traversal(root);
  printf("\n");
  root = delete_note(root, -100);
  inorder_traversal(root);
  printf("\n");

  return 0;
}
```