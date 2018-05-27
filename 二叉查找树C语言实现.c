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
