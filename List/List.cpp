#include<iostream>
#include"List.h"
using namespace std;

template<class P>
CustomNode<P>::CustomNode()
{

}

template<class P>
CustomNode<P>::CustomNode(P data)
{
	setData(data);

}

template<class P>
CustomNode<P>::~CustomNode()
{
	_pre = nullptr;
	_next = nullptr;
}

template<class T>
CustomList<T>::CustomList()
{
	_head = new CustomNode<T>();
	//_head->_pre = _head;
	// _head->_next =
}

template<class T>
CustomList<T>::~CustomList()
{

}

template<class T>
CustomNode<T>* CustomList<T>::push(T num)
{
	// auto newNode = make_shared<CustomNode<T>>(num);
	auto newNode = new CustomNode<T>(num);
	auto lastNode = _head;
	while (lastNode->_next != nullptr) {
		lastNode = lastNode->_next;
	}
	lastNode->_next = newNode;
	newNode->_pre = lastNode;
	return newNode;

}

// 将num插到node后
template<class T>
CustomNode<T>* CustomList<T>::insert(CustomNode<T>* node, T num)
{
	auto newNode = new CustomNode<T>(num);
	auto tempNode = node->_next;
	node->_next = newNode;
	newNode->_pre = node;
	if (tempNode) {
		newNode->_next = tempNode;
		tempNode->_pre = newNode;
	}
	return newNode;
}

template<class T>
bool CustomList<T>::find(T num)
{
	auto pNode = _head->_next;
	if (!pNode) return false;
	while (num != pNode->getData()) {
		pNode = pNode->_next;
		if (!pNode)
			return false;
	}
	return true;
}

template<class T>
void CustomList<T>::remove(CustomNode<T>* node)
{
	if (node->_next) {
		node->_pre->_next = node->_next;
		node->_next->_pre = node->_pre;
	}
	else {
		node->_pre->_next = nullptr;
	}
	delete node;
}

template<class T>
void CustomList<T>::popAll()
{
	while (_head->_next) {
		auto pNode = _head->_next;
		_head->_next = pNode->_next;
		cout << pNode->getData() << " ";
		delete pNode;
	}
	cout << endl;
}

int main(){
	// 将类模板实例化
	auto list1 = new CustomList<int>();
	auto node1 = list1->push(1);
	auto node2 = list1->push(2);
	auto node3 = list1->insert(node2, 3);
	auto ret = list1->find(2);
	list1->remove(node2);
	list1->popAll();
	return 0;
}
