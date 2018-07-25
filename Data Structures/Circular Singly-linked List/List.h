#include <iostream>
#include <optional>

#ifndef _List_H_
#define _List_H_
//-------------------------------------------------------------------------------------------------
template <typename Type>
class List
{
private:
	struct Node
	{
		Type element = {};
		Node* next = nullptr;
	};
	size_t count;
	Node* head;
public:
	List();
	List(const List & lst);
	List(List && lst);
	List & operator = (const List & lst);
	List & operator = (List && lst);
	~List();

	template <typename Type>
	friend std::ostream & operator << (std::ostream & os, const List & lst);

	void push_front(const Type & tp);
	void push_back(const Type & tp);
	void push_pos(const Type & tp, const size_t & pos);

	void pop_front();
	void pop_back();
	void pop_pos(const size_t & pos);
	
	bool empty() const;
	const std::optional<Type> & front() const;
	const std::optional<Type> & back() const;

	void show() const;
};
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::List() : count(0), head(nullptr)
{

}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::List(const List & lst) : count(lst.count), head(nullptr)
{
	for (const Node* n_ptr = lst.head; n_ptr->next != lst.head; n_ptr = n_ptr->next)
	{
		Node* n_ptr_new = new Node;
		n_ptr_new->element = n_ptr->element;
		if (head == nullptr)
		{
			head = n_ptr_new;
			head->next = head;
		}
		else
		{
			Node* n_ptr_tmp = head;
			while (n_ptr_tmp->next != head)
			{
				n_ptr_tmp = n_ptr_tmp->next;
			}
			n_ptr_new->next = head;
			n_ptr_tmp->next = n_ptr_new;
		}
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::List(List && lst) : count(lst.count), head(lst.head)
{
	lst.count = 0;
	lst.head = nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type> & List<Type>::operator = (const List & lst)
{
	if (this == &lst)
	{
		return *this;
	}
	
	List tmp(lst);
	std::swap(count, tmp.count);
	std::swap(head, tmp.head);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type> & List<Type>::operator = (List && lst)
{
	if (this == &lst)
	{
		return *this;
	}

	std::swap(count, lst.count);
	std::swap(head, lst.head);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::~List()
{
	while (head)
	{
		Node* n_ptr = head;
		head = head->next;
		delete n_ptr;
	}
	count = 0;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::push_front(const Type & tp)
{
	Node* n_ptr_new = new Node;
	n_ptr_new->element = tp;
	if (head == nullptr)
	{
		head = n_ptr_new;
		head->next = head;
		n_ptr_new = nullptr;
	}
	else
	{
		Node* n_ptr_tmp = head;
		while (n_ptr_tmp->next != head)
		{
			n_ptr_tmp = n_ptr_tmp->next;
		}
		n_ptr_new->next = head;
		head = n_ptr_new;
		n_ptr_tmp->next = head;
	}
	++count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::push_back(const Type & tp)
{
	Node* n_ptr_new = new Node;
	n_ptr_new->element = tp;
	if (head == nullptr)
	{
		head = n_ptr_new;
		head->next = head;
		n_ptr_new = nullptr;
	}
	else
	{
		Node* n_ptr_tmp = head;
		while (n_ptr_tmp->next != head)
		{
			n_ptr_tmp = n_ptr_tmp->next;
		}
		n_ptr_new->next = head;
		n_ptr_tmp->next = n_ptr_new;
	}
	++count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::push_pos(const Type & tp, const size_t & pos)
{
	if (empty() || pos == 0)
	{
		push_front(tp);
		return;
	}

	if (pos == count)
	{
		push_back(tp);
		return;
	}

	if (pos < count && pos > 0)
	{
		Node* n_ptr_new = new Node;
		Node* n_ptr_prev = nullptr;
		Node* n_ptr_cur = head;
		n_ptr_new->element = tp;
	
		for (size_t i = 0; i < pos; ++i)
		{
			n_ptr_prev = n_ptr_cur;
			n_ptr_cur = n_ptr_cur->next;
		}
		n_ptr_prev->next = n_ptr_new;
		n_ptr_new->next = n_ptr_cur;
		++count;
	}
	else
	{
		throw std::out_of_range("Invalid position");
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::pop_front()
{
	if (empty())
	{
		throw std::out_of_range("Can't pop from empty list");
	}
	
	if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}

	Node* n_ptr = head;
	head = head->next;
	--count;
	delete n_ptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::pop_back()
{
	if (empty())
	{
		throw std::out_of_range("Can't pop from empty list");
	}

	if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}

	Node* n_ptr = head;
	while (n_ptr->next != tail)
	{
		n_ptr = n_ptr->next;
	}
	--count;
	delete tail;

	tail = n_ptr;
	tail->next = nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::pop_pos(const size_t & pos)
{
	if (empty())
	{
		throw std::out_of_range("Can't pop from empty list");
	}

	if (pos == 0)
	{
		pop_front();
		return;
	}
	else
	if (pos == --count)
	{
		pop_back();
		return;
	}

	if (pos < count && pos > 0)
	{
		Node* n_ptr_prev = nullptr;
		Node* n_ptr_cur = head;

		for (size_t i = 0; i < pos; ++i)
		{
			n_ptr_prev = n_ptr_cur;
			n_ptr_cur = n_ptr_cur->next;
		}
		n_ptr_prev->next = n_ptr_cur->next;
		--count;
		delete n_ptr_cur;
	}
	else
	{
		throw std::out_of_range("Invalid position");
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
bool List<Type>::empty() const
{
	return head == nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const std::optional<Type> & List<Type>::front() const
{
	if (empty())
	{
		return std::nullopt;
	}
	return head->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const std::optional<Type> & List<Type>::back() const
{
	if (empty())
	{
		return std::nullopt;
	}
	return tail->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
std::ostream & operator << (std::ostream & os, const List<Type> & lst)
{
	lst.show();
	return os;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::show() const
{
	if (empty())
	{
		std::cerr << "Stack is empty!" << std::endl;
	}
	else
	{
		Node* n_ptr = nullptr;
		for (n_ptr = head; n_ptr->next != head; n_ptr = n_ptr->next)
		{
			std::cout << n_ptr->element << std::endl;
		}
		std::cout << n_ptr->element << std::endl;
	}
}
//-------------------------------------------------------------------------------------------------
#endif // _List_H_