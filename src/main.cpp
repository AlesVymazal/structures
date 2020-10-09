
#include<iostream>

struct Node{
	Node(int data)
	{
		this->data = data;
	}

	int data;
	Node *left = nullptr;
	Node *right = nullptr;
};

class BTS{
public:
	void insert(int data)
	{
		
		if(!root)
		{
			root = new Node(data);
			tree = new Node(data);
		}
		if(root)
		{
			Node* current = root;
			while(true)
			{
				if(current->data > data)
				{
					if(!current->left)
					{
						tree->left = new Node(data);
						break;
					}
					else
					{
						current = tree->left;
					}
				}
				else
				{
					if(!current->right)
					{
						tree->right = new Node(data);
						break;
					}
					else
					{
						current = tree->right;
					}
				}	
			}
		}
	}
	void delete1(int data)
	{

	}
private:
	Node *root = nullptr;
	Node *tree = nullptr;
};
 
int main(int argc, char *argv[]){
   BTS A;
   A.insert(5);
   A.insert(8);
   A.insert(2);
   A.insert(7);
   return 0;
}

