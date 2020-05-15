#include <iostream>   
#include<string>
#include<algorithm>
#include <sstream>
#include <cstring>
#include <climits> 
#include <fstream>
#include <cstdlib>
using namespace std;


struct Node
{
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color; 		//black 0 red 1
};

class RedBlackTree
{
private:
  	Node *root;
  	Node *TNULL;
  	
  	void initializenode(Node *node, Node *parent)   //ªì©l€Æ 
  	{
   		node->data = 0;
    	node->parent = parent;
    	node->left = NULL;
    	node->right = NULL;
    	node->color = 0;
  	}
  
	void inorderoutput(Node *node)   
	{
    	
		if (node!=TNULL)
    	{
    		string s;
    		
    		inorderoutput(node->left);
    		
			cout<<"key: "<<node->data<<" parent: ";
			s=(node->color)?"red":"black";
			if(node->parent==0)
				cout<<"  color: "<<s<<endl;
			else
				cout<<node->parent->data<<" color: "<<s<<endl;
    		
			inorderoutput(node->right);
      		
    	}
	}
  
  	Node* search(Node *now, int key)
  	{
    	while (now!=TNULL && key!=now->data) {                                    
	    	if (key < now->data)                    
            	now = now->left;   
        	else
            	now=now->right;  
        }
    
    return now;
	}
	
  	void rbTransplant(Node *u, Node *v)
  	{
    	if (u->parent==NULL)
    	{
      		root = v;
    	}
    	else if (u == u->parent->left)
    	    u->parent->left = v;
    	else
    	    u->parent->right = v;
    	
		if(v!=NULL)
		   v->parent = u->parent;
  	}	
  
  	void BSTdelete(Node *node, int key)
  	{
    	Node *z = search(node,key);
    	Node *x, *y;
    	
    	y=z;
    	int y_original_color = y->color;
    	if(z->left == TNULL)
    	{
     	 x=z->right;
     	 rbTransplant(z,z->right);
    	}
    	else if(z->right == TNULL)
    	{
      		x = z->left;
     		rbTransplant(z, z->left);
   	 	}
    	else				//z has two child
    	{
     		y=minimum(z->right);		//y ¬° zªºsuccessor
			y_original_color=y->color;
      		x = y->right;
      		if(y->parent!=z)
     		{
        		rbTransplant(y,y->right);   //y left ¥²¬°NULL 
        		y->right = z->right;
        		y->right->parent = y;
      		}
      		else
        		x->parent = y;
      			
      		rbTransplant(z,y);
      		y->left = z->left;
      		y->left->parent=y;
      		y->color = z->color;
    	}
    
    
    	delete z;
    	if (y_original_color==0)
    		deletefixup(x);
     	
    	
  	}
  

  
  	void deletefixup(Node *x)
  	{
  		
    	Node *w;
    	while (x!= root && x->color==0)
    	{
      		if (x == x->parent->left)
      		{
        		w=x->parent->right;   //w=uncle
        		if (w->color == 1)	  //case 1
        		{
          		w->color = 0;
          		x->parent->color = 1;
          		leftRotate(x->parent);
          		w= x->parent->right;
        		}
        		if(w->left->color==0 && w->right->color == 0) //case 2
        		{
          			w->color = 1;
          			x=x->parent;
        		}
        		else  //case 3
        		{
        			if(w->right->color==0){
	          	    	w->left->color = 0;
	            		w->color = 1;
	            		rightRotate(w);
	            		w= x->parent->right;
	            	}
          		}
          		w->color = x->parent->color; //case4
          		x->parent->color = 0;
          		w->right->color = 0;
          		leftRotate(x->parent);
          		x = root;
        	}
      		else
      		{
        		w= x->parent->left;
        		if(w->color==1)
        		{
          			w->color = 0;
          			x->parent->color = 1;
          			rightRotate(x->parent);
          			w = x->parent->left;
          			
        		}
        		
        		if (w->right->color == 0 && w->left->color == 0)
        		{	
					w->color = 1;
          			x = x->parent;
          			
        		}
        		else 
        		{
            		if(w->left->color == 0){
						w->right->color = 0;
	            		w->color = 1;
	            		leftRotate(w);
	            		w = x->parent->left;
	            	}
            		
          		}
          		
          		w->color = x->parent->color;
				x->parent->color = 0;
          		w->left->color = 0;
          		rightRotate(x->parent);
          		x = root;
          		
        	}
      	}
    	x->color = 0;
  	}
  
  	void BSTinsert(int key)
  	{
    	Node *node = new Node;
    	node->parent = NULL;
    	node->data = key;
    	
    	Node *y = NULL;
    	Node *x = this->root;
    	while (x!=TNULL)
    	{
      		y=x;
      		if(node->data<x->data)
      			x = x->left;
      		else
      		    x = x->right;
      	}
    
    	node->parent = y;
    	if(y ==NULL)
    		root = node;
    	else if (node->data<y->data)
    		y->left = node;
    	else
    		y->right = node;
    	
	node->left = TNULL;
    	node->right = TNULL;
    	node->color = 1;
		
		if(node->parent == NULL)
    	{
      		node->color = 0;
      		return;
    	}
    	if (node->parent->parent == nullptr)
    		return;
    	insertFix(node);
  	}
  	
  	
  	void insertFix(Node *z)
  	{
   		Node *y;
    	while (z->parent->color == 1)
    	{
      		if (z->parent == z->parent->parent->right)
      		{
        	y = z->parent->parent->left;
        		if(y->color == 1)
        		{
	          		z->parent->color = 0;
					y->color = 0;
	          		z->parent->parent->color = 1;
	          		z = z->parent->parent;
        		}
        		else
        		{
	          		if (z == z->parent->left)
	          		{
	            		z = z->parent;
	            		rightRotate(z);
	          		}
	          		z->parent->color = 0;
	          		z->parent->parent->color = 1;
	          		leftRotate(z->parent->parent);
        		}
      		}
      		else
      		{
        		y = z->parent->parent->right;
		        if (y->color == 1)
		        {
		        	z->parent->parent->color = 1;
		          	y->color = 0;
		          	z->parent->color = 0;
		          	z = z->parent->parent;
		        }
		        else
		        {
		        	if (z == z->parent->right)
		          	{
		            	z = z->parent;
		            	leftRotate(z);
		          	}
		          	z->parent->color = 0;
		          	z->parent->parent->color = 1;
		          	rightRotate(z->parent->parent);
		        }
      		}
      		if (z == root)
        		break;
      
    	}
    	root->color = 0;
  	}
  
public:
  	RedBlackTree()
  	
	{
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  	}
  
  	Node* searchTree(int k)
  	{
    	return search(this->root, k);
  	}
  	Node* minimum(Node *node)
  	{
    	while (node->left != TNULL)
    	    node = node->left;
    	return node;
  	}

  	void leftRotate(Node *x)
  	{
    	Node *y = x->right;
    	x->right = y->left;
    	if (y->left != TNULL)
    	    y->left->parent = x;
    	y->parent = x->parent;
    	if (x->parent == nullptr)
    		this->root = y;
    	else if (x == x->parent->left)
    	  	x->parent->left = y;
    	else
    	    x->parent->right = y;
        y->left = x;
    	x->parent = y;
  	}
  	void rightRotate(Node *x)
  	{
    	Node *y = x->left;
    	x->left = y->right;
    	if (y->right != TNULL)
    	    y->right->parent = x;
        y->parent = x->parent;
    	if (x->parent == nullptr)
    	    this->root = y;
        else if (x == x->parent->right)
    	    x->parent->right = y;
        else
    	    x->parent->left = y;
        y->right = x;
    	x->parent = y;
  	}
  
  	void Delete(int data)
  	{
    	BSTdelete(this->root, data);
  	}
  	
  	void insert(int data)
  	{
    	BSTinsert(data);
  	}
			
  	void inorder(){
		inorderoutput(this->root);
  	}
};

int main()
{
	fstream fin;	
	fin.open("input.txt",ios::in);
	
	
	int time;
	fin>>time;
	RedBlackTree bst;
	while(time--){
		
		int select,insert_num;
		
		string insert,enter;
		fin>>select;
		getline(fin,enter); //¥h±ŒŠhŸlªºenter
		getline(fin,insert);
		//cout<<"select="<<select<<"insert="<<insert<<"enter="<<enter<<endl;
		insert_num=count(insert.begin(), insert.end(), ' ');
		insert_num+=1;
				
		int insert_table[insert_num];
		int current=0;
		
		for(int i=0;i<insert_num;i++){
			int pos=insert.find_first_of(" ",current);
			insert_table[i]=atoi(insert.substr(current, pos-current).c_str());
			current=pos+1;
			
		}
		
		if(select == 1){
			cout<<"Insert: ";
			for(int i=0;i<insert_num;i++){
				cout<<insert_table[i];
				if(i<insert_num-1)
					cout<<", ";
				bst.insert(insert_table[i]);
			}
			cout<<endl;
			bst.inorder();
		}
		
		else if(select==2){
			cout<<"Delete: ";
			for(int i=0;i<insert_num;i++){
				cout<<insert_table[i];
				if(i<insert_num-1)
					cout<<", ";
				bst.Delete(insert_table[i]);
			}
			cout<<endl;
			bst.inorder();
		}
	}

}