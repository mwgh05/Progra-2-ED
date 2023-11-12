#include <iostream>
#include "Estructuras.h"
#define SPACE 10

using namespace std;

class TreeNode {
  public:
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent; // Nuevo puntero al nodo padre

    TreeNode() {
      value = 0;
      left = NULL;
      right = NULL;
      parent = NULL; // Inicializar el puntero al padre
    }
    
    TreeNode(int v) {
      value = v;
      left = NULL;
      right = NULL;
      parent = NULL;
    }
};

class BST {
  public:
    TreeNode *root;

  BST() {
    root = NULL;
  }

  bool isTreeEmpty() {
    return root == NULL;
  }

  void insertNode(TreeNode *new_node) {
    if (root == NULL) {
      root = new_node;
      cout << "Value Inserted as root node!" << endl;
    } else {
      TreeNode *temp = root;
      while (temp != NULL) {
        if (new_node->value == temp->value) {
          cout << "Value Already exists, Insert another value!" << endl;
          return;
        } else if ((new_node->value < temp->value) && (temp->left == NULL)) {
          temp->left = new_node;
          new_node->parent = temp; // Asignar el puntero al padre
          cout << "Value Inserted to the left!" << endl;
          break;
        } else if (new_node->value < temp->value) {
          temp = temp->left;
        } else if ((new_node->value > temp->value) && (temp->right == NULL)) {
          temp->right = new_node;
          new_node->parent = temp; // Asignar el puntero al padre
          cout << "Value Inserted to the right!" << endl;
          break;
        } else {
          temp = temp->right;
        }
      }
    }
  }

  TreeNode *insertRecursive(TreeNode *r, TreeNode *new_node) {
    if (r == NULL) {
      r = new_node;
      cout << "Insertion successful" << endl;
      return r;
    }

    if (new_node->value < r->value) {
      r->left = insertRecursive(r->left, new_node);
      new_node->parent = r; // Asignar el puntero al padre
    } else if (new_node->value > r->value) {
      r->right = insertRecursive(r->right, new_node);
      new_node->parent = r; // Asignar el puntero al padre
    } else {
      cout << "No duplicate values allowed!" << endl;
      return r;
    }
    return r;
  }

  void print2D(TreeNode * r, int space) {
    if (r == NULL) // Base case  1
      return;
    space += SPACE; // Increase distance between levels   2
    print2D(r -> right, space); // Process right child first 3 
    cout << endl;
    for (int i = SPACE; i < space; i++) // 5 
      cout << " "; // 5.1  
    cout << r -> value << "\n"; // 6
    print2D(r -> left, space); // Process left child  7
  }

  void printPreorder(TreeNode * r) //(current node, Left, Right) 
  {
    if (r == NULL)
      return;
    /* first print data of node */
    cout << r -> value << " ";
    /* then recur on left sutree */
    printPreorder(r -> left);
    /* now recur on right subtree */
    printPreorder(r -> right);
  }

  void printInorder(TreeNode * r) //  (Left, current node, Right)
  {
    if (r == NULL)
      return;
    /* first recur on left child */
    printInorder(r -> left);
    /* then print the data of node */
    cout << r -> value << " ";
    /* now recur on right child */
    printInorder(r -> right);
  }

  void printPostorder(TreeNode * r) //(Left, Right, Root)
  {
    if (r == NULL)
      return;
    // first recur on left subtree 
    printPostorder(r -> left);
    // then recur on right subtree 
    printPostorder(r -> right);
    // now deal with the node 
    cout << r -> value << " ";
  }

  TreeNode * iterativeSearch(int v) {
    if (root == NULL) {
      return root;
    } else {
      TreeNode * temp = root;
      while (temp != NULL) {
        if (v == temp -> value) {
          return temp;
        } else if (v < temp -> value) {
          temp = temp -> left;
        } else {
          temp = temp -> right;
        }
      }
      return NULL;
    }
  }

  TreeNode * recursiveSearch(TreeNode * r, int val) {
    if (r == NULL || r -> value == val)
      return r;

    else if (val < r -> value)
      return recursiveSearch(r -> left, val);

    else
      return recursiveSearch(r -> right, val);
  }

  int height(TreeNode * r) {
    if (r == NULL)
      return -1;
    else {
      /* compute the height of each subtree */
      int lheight = height(r -> left);
      int rheight = height(r -> right);

      /* use the larger one */
      if (lheight > rheight)
        return (lheight + 1);
      else return (rheight + 1);
    }
  }

  /* Print nodes at a given level */
  void printGivenLevel(TreeNode * r, int level) {
    if (r == NULL)
      return;
    else if (level == 0)
      cout << r -> value << " ";
    else // level > 0  
    {
      printGivenLevel(r -> left, level - 1);
      printGivenLevel(r -> right, level - 1);
    }
  }
  void printLevelOrderBFS(TreeNode * r) {
    int h = height(r);
    for (int i = 0; i <= h; i++)
      printGivenLevel(r, i);
  }

  TreeNode * minValueNode(TreeNode * node) {
    TreeNode * current = node;
    /* loop down to find the leftmost leaf */
    while (current -> left != NULL) {
      current = current -> left;
    }
    return current;
  }

  TreeNode * deleteNode(TreeNode * r, int v) {
    // base case 
    if (r == NULL) {
      return NULL;
    }
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    else if (v < r -> value) {
      r -> left = deleteNode(r -> left, v);
    }
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (v > r -> value) {
      r -> right = deleteNode(r -> right, v);
    }
    // if key is same as root's key, then This is the node to be deleted 
    else {
      // node with only one child or no child 
      if (r -> left == NULL) {
        TreeNode * temp = r -> right;
        delete r;
        return temp;
      } else if (r -> right == NULL) {
        TreeNode * temp = r -> left;
        delete r;
        return temp;
      } else {
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        TreeNode * temp = minValueNode(r -> right);
        // Copy the inorder successor's content to this node 
        r -> value = temp -> value;
        // Delete the inorder successor 
        r -> right = deleteNode(r -> right, temp -> value);
        //deleteNode(r->right, temp->value); 
      }
    }
    return r;
  }

};

int ObtenerValor_Aux(TreeNode * r);
int ObtenerValor(TreeNode * r);

void incertarhumanoslista(int cantidad, ListaHumanos listadehumanos, BST arbolmundo){
  NodoHumano * humano = new NodoHumano(gen);
  int nuevosnodos = abs(cantidad / 100);
  while(cantidad != 0){
    listadehumanos.insertarNodo(humano);
    cantidad--;
  }
  TreeNode * new_node = new TreeNode();
  int val = 1;
  while(nuevosnodos > 0){
    new_node->value = ObtenerValor(arbolmundo.root);
	  arbolmundo.root= arbolmundo.insertRecursive(arbolmundo.root,new_node);
    nuevosnodos--;
  }
}

int ObtenerValor(TreeNode * r){
  if (r == NULL) {
      return 50000;
    }
  else if (r -> left == NULL) {
    return 25000;
  }
  else if (r -> right == NULL) {
    return 75000;
  }
  else{
    return ObtenerValor_Aux(r);
  }
}

int ObtenerValor_Aux(TreeNode * r){
  if (r->left == NULL || r->right == NULL){
    //250 < 500 entonces |parent-hijo/2|
    if(r->value < r->parent->value){
      return abs((r->parent->value - r->value) / 2);
    }
    //750 > 500 entonces |hijo-parent/2|
    else if(r->value > r->parent->value){
      return abs((r->value - r->parent->value) / 2);
    }
  }
  else{
    ObtenerValor_Aux(r->left);
    ObtenerValor_Aux(r->right);
  }
}

int main() {
  BST obj;
  ListaHumanos objHuman;

  int option, val, gen = 0;

  do {
    cout << "What operation do you want to perform? " <<
      " Select Option number. Enter 0 to exit." << endl;
    cout << "1. Incertar humanos" << endl;
    cout << "2. Search Node" << endl;
    cout << "3. Delete Node" << endl;
    cout << "4. Print/Traversal BST values" << endl;
    cout << "5. Height of Tree" << endl;
    cout << "6. Clear Screen" << endl;
    cout << "0. Exit Program" << endl;

    cin >> option;
    //Node n1;
    TreeNode * new_node = new TreeNode();

    switch (option) {
    case 0:
      break;
    case 1:
      	cout <<"INSERT"<<endl;
	      cout <<"Cantida de humanos a incertar: ";
	      cin >> val;
        incertarhumanoslista(val, objHuman, obj);

	      //new_node->value = val;
	      //obj.root= obj.insertRecursive(obj.root,new_node);

	      cout<<endl;
    		break;
      
    case 2:
      cout << "SEARCH" << endl;
      cout << "Enter VALUE of TREE NODE to SEARCH in BST: ";
      cin >> val;
      //new_node = obj.iterativeSearch(val);
      new_node = obj.recursiveSearch(obj.root, val);
      if (new_node != NULL) {
        cout << "Value found" << endl;
      } else {
        cout << "Value NOT found" << endl;
      }
      break;
    case 3:
      cout << "DELETE" << endl;
      cout << "Enter VALUE of TREE NODE to DELETE in BST: ";
      cin >> val;
      new_node = obj.iterativeSearch(val);
      if (new_node != NULL) {
        obj.deleteNode(obj.root, val);
        cout << "Value Deleted" << endl;
      } else {
        cout << "Value NOT found" << endl;
      }
      break;
    case 4:
      cout << "PRINT 2D: " << endl;
      obj.print2D(obj.root, 5);
      cout << endl;
      cout << "Print Level Order BFS: \n";
      obj.printLevelOrderBFS(obj.root);
      cout << endl;
      //	      cout <<"PRE-ORDER: ";
      //	      obj.printPreorder(obj.root);
      //	      cout<<endl;
      //	      cout <<"IN-ORDER: ";
      //	      obj.printInorder(obj.root);
      //	      cout<<endl;
      //	      cout <<"POST-ORDER: ";
      //	      obj.printPostorder(obj.root);
      break;
    case 5:
      cout << "TREE HEIGHT" << endl;
      cout << "Height : " << obj.height(obj.root) << endl;
      break;
    case 6:
      system("cls");
      break;
    default:
      cout << "Enter Proper Option number " << endl;
    }

  } while (option != 0);

  return 0;
}