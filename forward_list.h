//
// Created by martin on 2024-12-04.
//

#ifndef ITER_FORWARD_LIST_H
#define ITER_FORWARD_LIST_H

#include <algorithm>

//#define NOT_IN_THIS_COURSE

class forward_list {
    class forward_iterator;
public:
    using value_type = int;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    /**
     * Implements the requirements of [LegacyForwardIterator][https://en.cppreference.com/w/cpp/named_req/ForwardIterator]
     */
    using iterator = forward_iterator;
    using const_iterator = const iterator;

    forward_list();
    explicit forward_list(size_t size, value_type value = value_type());
    forward_list(const_pointer first, const_pointer last);
    forward_list(const forward_list & );
#ifdef NOT_IN_THIS_COURSE
    forward_list(forward_list &&) noexcept;
#endif
#ifndef NOT_IN_THIS_COURSE
    forward_list& operator=(const forward_list& );
#else
    forward_list& operator=(forward_list );
#endif
/**
 * Iterators
 */
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

/**
 * Modifiers
 */
    iterator push_back(value_type);
    iterator remove(iterator element);
    iterator pop_front();

private:
    struct node;
    using node_pointer = node*;

    struct node{
        value_type data;
        node_pointer next;
        node() = default;
        ~node();
        static node_pointer make_after(node_pointer& ptr){
            auto new_node = new node();
            return ptr->next = new_node;
        }
    };
    // This is only the end sentinel for an empty list.
    // => The end is unique, even for empty lists.
    node head_sentinel;
    node_pointer head;
    node_pointer tail;

    class forward_iterator{
        friend forward_list;
    public:
        // from InputIterator
        forward_iterator() = default;

        forward_iterator& operator++();
        bool operator !=(forward_iterator );
        value_type& operator*();

        // from ForwardIterator
        forward_iterator operator++(int);
    private:
        forward_iterator(node_pointer node);
        node_pointer current;
    };

    friend forward_list::node_pointer make_node(node_pointer& );
    friend void swap(forward_list& lhs, forward_list& rhs) noexcept;
};


#endif //ITER_FORWARD_LIST_H
