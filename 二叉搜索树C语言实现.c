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
