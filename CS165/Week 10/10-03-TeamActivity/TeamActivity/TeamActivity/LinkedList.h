#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>
#include <exception>
#include <algorithm>

template<typename T>
struct Node
{
	Node(T t) :data(t), next(nullptr) {};
	T data;
	std::shared_ptr<Node> next;
};

template<typename T>
class LinkedList
{
public:
	LinkedList() : head(nullptr), size(0) {};
	LinkedList(LinkedList const & other) :head(clone(other.head)) {};
	LinkedList(LinkedList&&) = default;
	LinkedList& operator=(LinkedList const & other) { head = head(clone(other.head)); };
	size_t getSize() const { return size; };
	std::shared_ptr<Node<T>> getHead() { return head; }
	void insert(T t);
	void deleteNode(T t);
	std::shared_ptr<Node<T>> findNode(T t);
	template<typename F>
	void forEach(F& f)
	{
		for (auto cur = head; cur != nullptr; cur = cur->next)
		{
			f(cur->data);
		}
	}
private:
	void insertAfter(T const & value, std::shared_ptr<Node<T>> location);
	void deleteNext(std::shared_ptr<Node<T>> previous);
	std::shared_ptr<Node<T>> find(T const & target, std::shared_ptr<Node<T>> list);


	std::shared_ptr<Node<T>> head;
	size_t size;

	std::shared_ptr<Node<T>> clone(std::shared_ptr<Node<T>> list)
	{
		if (!list) return nullptr;
		auto node = std::make_shared<Node<T>>(list->data);
		node->next = clone(list->next);
		return node;
	}

};

template<typename T>
void LinkedList<T>::insert(T t)
{
	if (!head)
	{
		head = std::make_shared<Node<T>>(t);
		++size;
	}
	else
	{
		auto node = head;

		for (size_t i = 0; i < getSize(); ++i)
		{
			if (!node->next)
			{
				insertAfter(t, node);
				break;
			}
			if (node->next->data >= t)
			{
				insertAfter(t, node);
				break;
			}
			node = node->next;
		}
	}
}

template<typename T>
void LinkedList<T>::insertAfter(T const & value, std::shared_ptr<Node<T>> location)
{
	if (!location) return;
	auto node = std::make_shared<Node<T>>(value);
	node->next = location->next;
	location->next = node;
	++size;
}

template<typename T>
void LinkedList<T>::deleteNode(T t)
{

	if (!head)
	{
		std::cout << "No list exists. " << std::endl;
	}
	else
	{
		auto node = head;

		for (size_t i = 0; i < getSize(); ++i)
		{
			if (!node->next)
			{
				std::cout << "No node with selected value " << t << " exists. " << std::endl;
				break;
			}
			if (node->next->data == t)
			{
				deleteNext(node);
				std::cout << "Node of value " << t << " has been deleted. " << std::endl;
				break;
			}
			node = node->next;
		}
	}
}

template<typename T>
void LinkedList<T>::deleteNext(std::shared_ptr<Node<T>> previous)
{
	if (!previous) return;
	if (!previous->next) return;
	previous->next = previous->next->next;
	--size;
}

template<typename T>
std::shared_ptr<Node<T>> LinkedList<T>::findNode(T t)
{
	return find(t, head);
}


template<typename T>
std::shared_ptr<Node<T>> LinkedList<T>::find(T const & target, std::shared_ptr<Node<T>> list)
{
	if (!list) return list;
	if (list->data == target) return list;
	return find(target, list->next);
}

#endif
