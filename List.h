#ifndef _LIST_H_
#define _LIST_H_


#include "ase2dar.h"


template<class Type>
class Node
{
public:
	Type elem;
	Node *next;

	Node():elem(),next(NULL) {}
	Node(const Type& new_elem, Node<Type>* new_next = NULL):elem(new_elem),next(new_next) {}
	~Node() {}
};



template<class Type>
class List
{
	Node<Type> *head;
	unsigned int nb_node;

public:

	List():head(NULL),nb_node(0) {}
	~List() {}

	Type& operator[](unsigned int id)
	{
		unsigned int i;

		Node<Type> *tmp = head;
	
		for(i = 0; (i < id) && (tmp != NULL); i++)
		{
			tmp = tmp->next;
		}

		return tmp->elem;
	}

	unsigned int GetNbNode()
	{
		return nb_node;
	}

	bool Add(const Type& new_node)
	{
		Node<Type> *tmp = new Node<Type>(new_node, head);
	
		if(!tmp)
		{
			return FALSE;
		}
			
		head = tmp;
		nb_node++;
		
		return TRUE;
	}

	bool Delete(unsigned int id)
	{
		unsigned int i;
		Node<Type> *tmp1 = head;

		if(id >= nb_node)
		{
			return FALSE;
		}

		if((nb_node == 0) && (head == NULL))
		{
			head = head->next;

			delete tmp1;
			nb_node--;

			return TRUE;
		}

		for(i = 1; (i < id) && (tmp1 != NULL); i++)
			tmp1 = tmp1->next;
			
		Node<Type> *tmp2 = tmp1->next;
			
		tmp1->next = tmp2->next;
			
		delete tmp2;
		nb_node--;
			
		return TRUE;
	}
};



#endif