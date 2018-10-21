#pragma once
using namespace std;
#include <iostream>
template <class K,class V>
struct AVLNode
{
	AVLNode<K,V>*  _left;
	AVLNode<K,V>* _right;
	AVLNode<K,V>* _parent;
	int _bf;
	K _key;
	V _value;
	AVLNode(const K& key,const V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_bf(0)
		,_key(key)
		,_value(value)
	{}



};
template <class K,class V>
class AVLTree
{
	typedef AVLNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
	if(_root == NULL)
	{
	_root = new Node(key,value);
	}
	else
	{
	Node* cur = _root;
	Node* parent  = NULL;
	Node* _insert_node = new Node(key,value);
	Node* modify_parent = NULL;
	while(1)
	{
		if(key > cur->_key)
		{
		parent = cur;
		cur = cur->_right;
		if(cur == NULL)
		{
		_insert_node->_parent = parent;
		parent->_right = _insert_node;
		parent->_bf++;
		while(parent != _root && parent->_bf !=0 )//˵����߸߶�����,���Ƚڵ�ҲҪ�ı�
		{
			if(parent == parent->_parent->_left)   //�˴���Ҫע�⣬ֻҪ��������һ��ƽ������ʧ�⣬��ôֹͣ���ϸ���ƽ�����ӣ���ʼ��ת����
			{
				parent->_parent->_bf--;
				if(parent->_parent->_bf == -2)
					break;
			}
			else
				{
					parent->_parent->_bf++;
					if(parent->_parent->_bf == 2)
						break;
				}
			parent = parent->_parent;
		}
		break;
		}		
		}
		else if(key < cur->_key)
		{
		parent = cur;
		cur = cur->_left;
		if(cur == NULL)
		{ 
		_insert_node->_parent = parent;
		parent->_left = _insert_node;
		parent->_bf--;
		while(parent != _root && parent->_bf !=0 )//˵����߸߶�����
		{
			if(parent == parent->_parent->_left)  			
			{
				parent->_parent->_bf--;
				if(parent->_parent->_bf == -2)
					break;
			}
			else
				{
					parent->_parent->_bf++;
					if(parent->_parent->_bf == 2)
						break;
				}
			parent = parent->_parent;
		}
		break;
		}		
		}
		else
		return false;
	}
	parent = _insert_node->_parent;
	//�ҵ���Ҫ�����λ
	//��ɲ��룬�����ѵ��ںô���ƽ�����ӣ���ʼ���ƽ�⣬һֱ��鵽���ڵ�
	while(1)
    {
	if(parent->_bf == 0)     //  ����Ҫ��ƽ
			return true;
	if(parent->_bf == 1 || parent->_bf == -1)  
	{
	//������Ҫ����  ��ʼ����ͨ�����ƽ������  ������
		if(parent == _root)
		{
			return true;
		}
		if(parent->_bf == 1 && parent->_parent->_bf == 2 )   //����  (ע����ڵ�)
		{
			RotateL(parent->_parent);
			return true;
		}
		else if(parent->_bf == -1 && parent->_parent->_bf == -2 )  //�ҵ���  (ע����ڵ�)
		{
			RotateR(parent->_parent);
			return true;
		}
		else if(parent->_parent->_right == parent && parent->_bf == -1 && parent->_parent->_bf == 2)
		{
			int flag = 0;
			
			if(parent->_left->_bf == 1)
			{
				flag = 1;
			}
			if(parent->_left->_bf == -1)
			{
				flag = -1;
			}
			RotateR(parent);
			RotateL(parent->_parent->_parent);
			if(flag == 1)
			{
				parent->_parent->_left->_bf = -1;
			}
			if(flag == -1)
			{
				parent->_bf = 1;
			}
			return true;
		}
		else if(parent->_parent->_left == parent && parent->_bf == 1 && parent->_parent->_bf == -2)
		{
			int flag = 0;
			if(parent->_right->_bf == -1)
			{
			flag = -1;
			}
			if(parent->_right->_bf == 1)
			{
			flag = 1;
			}
		
			RotateL(parent);
			RotateR(parent->_parent->_parent);   //��ͼ�Ϳ���֪��
			if(flag == -1)
			{
				parent->_parent->_right->_bf = 1;
			}
			if(flag == 1)
			{
				parent->_bf = -1;
			}
		
			return true;
		}
		
	}
	parent = parent->_parent;
	}
	}
	}
	void RotateL(Node* root)
	{
		Node* subR = root->_right;
		Node* subRL = subR->_left;
		Node*  root_parent = root->_parent;
		subR->_parent = root_parent;
		if(root_parent)
		{
			if(root == root_parent->_right)
			root_parent->_right = subR;
			else
				root_parent->_left = subR;
		}
		else
		{
		_root = subR;
		}
		subR->_left = root;
		root->_parent = subR;
		root->_right = subRL;
		if(subRL)
			subRL->_parent = root;
		root->_bf = 0;
		subR->_bf = 0;
	}
	void RotateR(Node* root)
	{
		Node* subL = root->_left;
		Node* subLR = subL->_right;
		Node*  root_parent = root->_parent;
		subL->_parent = root_parent;
		if(root_parent)
		{
			if(root == root_parent->_right)
			root_parent->_right = subL;
			else
				root_parent->_left = subL;
		}
		else
		{
		_root = subL;
		}
		subL->_right = root;
		root->_parent = subL;
		root->_left = subLR;
		if(subLR)
			subLR->_parent = root;
		root->_bf = 0;
		subL->_bf = 0;
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	void _InOrder(Node*  root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	int height (Node* root)
	{
	if(root == NULL)
		return 0;
	int leftHeight = height(root->_left);
	int rightHeight = height(root->_right);
	return (leftHeight>rightHeight? leftHeight:rightHeight)+1;
	}

	bool IsBalance()
	{
		int height = 0;
		return _IsBalanceOP(_root,height);
	}
	bool _IsBalance(Node*  root)
	{
		if(root == NULL)
			return true;
		int leftHeight = height(root->_left);	
		int rightHeight = height(root->_right);

		return abs(rightHeight-leftHeight)<2 && (_IsBalance(root->_left)) && (_IsBalance(root->_right));
			
	}
	bool _IsBalanceOP(Node* root,int& height)
	{
		if(root == NULL)
		{
			height = 0;
			return true;
		}
		int leftHeight = 0;
		int rightHeight = 0;
		if(_IsBalanceOP(root->_left,leftHeight) == false)
			return false;

		if(_IsBalanceOP(root->_right,rightHeight) == false)
			return false;
		if(rightHeight - leftHeight != root->_bf)
		{
			cout<<"ƽ�������쳣"<<endl;
			cout<<"�쳣�ڵ�ƽ������:"<<root->_bf;
			cout<<endl;
		}

		height = (leftHeight>rightHeight? leftHeight:rightHeight)+1;
		return abs(rightHeight-leftHeight)<2;
	}
private:
	Node* _root;
};
void test()
{
	int a[] = {16,3,7,11,9,26,18,14,15};
	double b[] = {4,2,6,1,3,5,15,0.5,1.5,1.7};
	AVLTree<double,int> t;
	for(size_t i = 0;i < 10;i++)
	t.Insert(b[i],0);
	t.InOrder();
	cout<<endl;
	cout<<t.IsBalance()<<endl;
	system("pause");

}
