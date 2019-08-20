#include<bits/stdc++.h>
using namespace std;

/** @brief Structure to define the node of binary search tree. */

struct node
{
	/** Value inside node */
	int data;
	/** Color of node(for Red-Black Tree) */
	int color;
	/** Right child of node */
	node * right = NULL;
	/** Left child of node */
	node * left = NULL;
	/** Parent of node(for Red-Black Tree) */
	node * parent = NULL;
	
	/** Function to check for leaf node. */
	int isleaf()
	{
		if(right==NULL && left==NULL) return 1;
		else return 0;
	}
	
	/** Function to get height of node(for AVL Tree). */
	int height()
	{
		if(this==NULL) return 0;
		if(isleaf()) return 1;
		else return max(left->height(),right->height()) + 1;
	}
	
	/** Function to get balance of node(for AVL Tree). */
	int balance()
	{
		if(this==NULL) return 0;
		else return left->height()-right->height();
	}
};

/** Function to perform right rotation on any node(for AVL Tree).
* @param root Pointer to root to be right-rotated
*/
void rightrotate(node *& root)
{
	node * temp = root;
	node * sl = temp->left;
	node * b = sl->right;
	sl->right = temp;
	temp->left = b;
	root = sl;
}

/** Function to perform left rotation on any node(for AVL Tree).
* @param root Pointer to root to be left-rotated
*/
void leftrotate(node *& root)
{
	node * temp = root;
	node * sl = temp->right;
	node * b = sl->left;
	sl->left = temp;
	temp->right = b;
	root = sl;
}

/** @brief Structure to define Binary Search Tree data structure. */
struct BST
{
	node * root = NULL;
	
	/** Function to insert node in BST.
	* @param root Pointer to root node of tree
	* @param x Value to be inserted in tree
	*/
	void insert(node *& root,int x)
	{
		if(root==NULL)
		{
			node * newnode = new node;
			newnode->data = x;
			root = newnode;
		}
		else
		{
			if(x>root->data) insert(root->right,x);
			else if(x<root->data) insert(root->left,x);
			else return;
		}
	}
};

/** @brief Structure to define AVL Tree data structure. */
struct AVL
{
	node * root = NULL;
	
	/** Function to insert node in AVL Tree.
	* @param root Pointer to root node of tree
	* @param x Value to be inserted in tree
	*/
	void insert(node *& root,int x)
	{
		if(root==NULL)
		{
			node * newnode = new node;
			newnode->data = x;
			root = newnode;
		}
		else
		{
			if(x>root->data) insert(root->right,x);
			else if(x<root->data) insert(root->left,x);
			else return;
		}
		int bal = root->balance();
		if(bal>1 && x<(root->left->data))
		{
			rightrotate(root);
		}
		else if(bal<-1 && x>(root->right->data))
		{
			leftrotate(root);
		}
		else if(bal>1 && x>(root->left->data))
		{
			leftrotate(root->left);
			rightrotate(root);
		}
		else if(bal<-1 && x<(root->right->data))
		{
			rightrotate(root->right);
			leftrotate(root);
		}
	}
};

struct RBT
{
	/** Null/terminal node for Red-Black Tree */
	node * TNULL;
	/** Root node of Red-Black Tree */
	node * root = NULL;
	
	RBT()
	{
		TNULL = new node;
		TNULL->color = 0;
		TNULL->data = -11;
		root = TNULL;
	}
	
	/** Function to insert node in RBT.
	* @param x Value to be inserted in tree
	*/
	void insert(int x)
	{
		node * newnode = new node;
		newnode->data = x;
		newnode->left = TNULL;
		newnode->right = TNULL;
		newnode->color = 1;
		node * y = NULL;
		node * z = this->root;
		while (z != TNULL)
		{
			y = z;
			if(newnode->data < z->data)
			{
				z = z->left;
			}
			else if(newnode->data > z->data)
			{
				z = z->right;
			}
			else return;
		}
		newnode->parent = y;
		if(y == NULL)
		{
			root = newnode;
		}
		else if(newnode->data < y->data)
		{
			y->left = newnode;
		}
		else
		{
			y->right = newnode;
		}
		if(newnode->parent == NULL)
		{
			newnode->color = 0;
			return;
		}
		if(newnode->parent->parent == NULL)
		{
			return;
		}
		fixInsert(newnode);
	}
	
	/** Function to fix the violations/conflicts in RBT due to BST insertion.
	* @param k Pointer to node in RBT
	*/
	void fixInsert(node * k)
	{
		node * u;
		while(k->parent->color == 1)
		{
			if(k->parent == k->parent->parent->right)
			{
				u = k->parent->parent->left;
				if(u->color == 1)
				{
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else
				{
					if(k == k->parent->left)
					{
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else
			{
				u = k->parent->parent->right;

				if(u->color == 1)
				{
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				}
				else
				{
					if(k == k->parent->right)
					{
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if(k == root)
			{
				break;
			}
		}
		root->color = 0;
	}
	
	/** Function to rotate left on any node.
	* @param x Pointer to node to be left-rotated
	*/
	void leftRotate(node * x)
	{
		node * y = x->right;
		x->right = y->left;
		if(y->left != TNULL)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if(x->parent == NULL)
		{
			this->root = y;
		}
		else if(x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	
	/** Function to rotate right on any node.
	* @param x Pointer to node to be right-rotated
	*/
	void rightRotate(node * x)
	{
		node * y = x->left;
		x->left = y->right;
		if(y->right != TNULL)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL)
		{
			this->root = y;
		}
		else if(x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
};

/** Function to display the tree in inorder form.
* @param root Pointer to root node of tree
* @param option Option for either BST/AVL (0) or RBT (1)
*/
void display(node * root,int option = 0)
{
	if(option==0)
	{
		if(root==NULL) return;
		else
		{
			display(root->left);
			cout<<root->data<<" ";
			display(root->right);
		}
	}
	else
	{
		if(root->data== -11) return;
		else
		{
			display(root->left,1);
			cout<<root->data<<" ";
			display(root->right,1);
		}
	}
}

/** Function to display all paths in tree.
* @param x Value at leaf node
* @param temp Pointer to temporary node(used in recursion)
* @param option Option for either BST/AVL (0) or RBT (1)
*/
void displayallpaths(int x,node * temp,int option = 0)
{
	node * p = temp;
	cout<<temp->data;
	while(p->data!=x)
	{
		if(x<p->data)
		{
			p = p->left;
			cout<<"->"<<p->data;
		}
		else if(x>p->data)
		{
			p = p->right;
			cout<<"->"<<p->data;
		}
	}
	cout<<endl;
	if(option == 0)
	{
		if(temp->isleaf()) return;
	}
	else
	{
		if(temp->left->data==-11 && temp->right->data==-11) return;
	}
	if(x<temp->data) temp = temp->left;
	else if(x>temp->data) temp = temp->right;
	displayallpaths(x,temp,option);
}

/** Function to get leaf node of tree and print path to it.
* @param temp Pointer to temporary node(used in recursion)
* @param root Pointer to root node of tree
* @param option Option for either BST/AVL (0) or RBT (1)
*/
void getleaf(node * temp,node * root,int option = 0)
{
	if(option == 0)
	{
		if(temp==NULL) return;
	}
	else
	{
		if(temp->data==-11) return;
	}
	if(option == 0)
	{
		if(temp->isleaf()) displayallpaths(temp->data,root,option);
		else
		{
			getleaf(temp->left,root,option);
			getleaf(temp->right,root,option);
		}
	}
	else
	{
		if(temp->left->data==-11 && temp->right->data==-11) displayallpaths(temp->data,root,option);
		else
		{
			getleaf(temp->left,root,option);
			getleaf(temp->right,root,option);
		}
	}
}

/** Function to obtain AVL Tree from Binary Search Tree inorder traversal.
* @param root Pointer to root node of Binary Search Tree
* @param a Pointer to AVL Tree
*/
void bsttoavl(node * root,AVL *& a)
{
	if(root==NULL) return;
	else
	{
		bsttoavl(root->left,a);
		a->insert(a->root,root->data);
		bsttoavl(root->right,a);
	}
}

/** Function to display tree in level-indentation form.
* @param root Pointer to root node of tree
* @param option Option for either BST/AVL (0) or RBT (1)
* @param lvl Level of node to help in indentation
*/
void displaylevel(node * root,int option = 0,int lvl = 0)
{
	if(option==0)
	{
		if(root==NULL) return;
		else
		{
			for(int i=0;i<lvl;i++) cout<<"\t";
			int bal = root->balance();
			if(bal<0) bal = (-1)*bal;
			cout<<root->data<<" ";
			cout<<"["<<bal<<"] ";
			cout<<endl;
			displaylevel(root->left,option,lvl+1);
			displaylevel(root->right,option,lvl+1);
		}
	}
	else
	{
		if(root->data==-11) return;
		else
		{
			for(int i=0;i<lvl;i++) cout<<"\t";
			int bal = root->balance();
			if(bal<0) bal = (-1)*bal;
			cout<<root->data<<" ";
			cout<<"["<<bal<<"] ";
			if(root->color == 1) cout<<"[RED]";
			else cout<<"[BLACK]";
			cout<<endl;
			displaylevel(root->left,option,lvl+1);
			displaylevel(root->right,option,lvl+1);
		}
	}
}

int main()
{
	clock_t start,end;
	start = clock();
	BST * b = new BST;
	AVL * a = new AVL;
	RBT * r = new RBT;
	int choice = 1;
	while(choice)
	{
		cout<<"Select your choice :-"<<endl;
		cout<<"1. Insert node in BST/RBT."<<endl;
		cout<<"2. Create AVL from inorder traversal of BST."<<endl;
		cout<<"3. Print inorder traversal of BST/AVL/RBT."<<endl;
		cout<<"4. Display all paths in BST/AVL/RBT."<<endl;
		cout<<"5. Print BST/AVL/RBT in level-wise indentation."<<endl;
		cout<<"6. Exit."<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1: cout<<"Enter value"<<endl;
					int x;
					cin>>x;
					b->insert(b->root,x);
					r->insert(x);
					break;
			case 2: bsttoavl(b->root,a);
					break;
			case 3: cout<<"BST: -"<<endl;
					display(b->root);
					cout<<endl;
					cout<<"AVL: -"<<endl;
					display(a->root);
					cout<<endl;
					cout<<"RBT: -"<<endl;
					display(r->root,1);
					cout<<endl;
					break;
			case 4: cout<<"BST: -"<<endl;
					getleaf(b->root,b->root);
					cout<<"AVL: -"<<endl;
					getleaf(a->root,a->root);
					cout<<"RBT: -"<<endl;
					getleaf(r->root,r->root,1);
					break;
			case 5: cout<<"BST: -"<<endl;
					displaylevel(b->root);
					cout<<endl<<endl;
					cout<<"AVL: -"<<endl;
					displaylevel(a->root);
					cout<<endl<<endl;
					cout<<"RBT: -"<<endl;
					displaylevel(r->root,1);
					cout<<endl<<endl;
					break;
			case 6: choice = 0;
					break;
			default:cout<<"Wrong choice! Enter again."<<endl;
		}
	}
	end = clock();
    cout<<"Total CPU time is: "<<float(end-start)/CLOCKS_PER_SEC<<" seconds.";
    return 0;
	return 0;
}
