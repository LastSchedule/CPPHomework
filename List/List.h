#pragma once
template<class T>
class CustomList;


template<class P>
class CustomNode {
public:
	CustomNode();
	CustomNode(P);
	~CustomNode();
	const CustomNode& operator = (const CustomNode& node);
	CustomNode* _pre = nullptr;
	CustomNode* _next = nullptr;
	void setData(P data) { this->_data = data; }
	P getData() { return this->_data; }
	friend class CustomList<P>;

private:
	P _data;
};

template<class T>
class CustomList {
public:
	CustomList();
	~CustomList();
	CustomNode<T>* push(T);
	CustomNode<T>* insert(CustomNode<T>*,T);
	bool find(T);
	void remove(CustomNode<T>*);
	void popAll();
private:
	CustomNode<T>* _head;
};

