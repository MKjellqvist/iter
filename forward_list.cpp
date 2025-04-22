//
// Created by martin on 2024-12-06.
//
#include "forward_list.h"


forward_list::node::~node() {
    // Avoiding recursion
    // A -> B -> C -> nullptr
    // A = this;
    // 1 - disconnects B, delete B
    // 2 - disconnects C(disconnected)
    // 3 - deletes nullptr
    auto next_to_delete = this->next;
    while(next_to_delete){
        auto saved_list = next_to_delete->next;
        next_to_delete->next = nullptr;
        delete next_to_delete;
        next_to_delete = saved_list;
    }
}

forward_list::forward_iterator::forward_iterator(forward_list::node_pointer node) {
    current = node;
}

bool forward_list::forward_iterator::operator!=(forward_list::forward_iterator rhs) {
    return current != rhs.current;
}

forward_list::forward_iterator &forward_list::forward_iterator::operator++() {
    if (!current) return *this;
    current = current->next;
    return *this;
}

forward_list::value_type &forward_list::forward_iterator::operator*() {
    return current->data;
}

forward_list::forward_iterator forward_list::forward_iterator::operator++(int) {
    auto now = *this;
    ++(*this);
    return now;
}


#ifdef NOT_IN_THIS_COURSE
forward_list &forward_list::operator=(forward_list rhs) {
    swap(*this, rhs);
    return *this;
}
#else

forward_list &forward_list::operator=(const forward_list &rhs) {
    auto old_list_cleaner = forward_list(rhs);
    swap(*this, old_list_cleaner);
    return *this;
}

#endif

void swap(forward_list &lhs, forward_list &rhs) noexcept {
    std::swap(lhs.head_sentinel, rhs.head_sentinel);
    std::swap(lhs.head, rhs.head);
    std::swap(lhs.tail, rhs.tail);
}

forward_list::node_pointer make_node(forward_list::node_pointer &connect_to) {
    return forward_list::node::make_after(connect_to);
}

forward_list::forward_list(forward_list::const_pointer first, forward_list::const_pointer last) : forward_list() {
    while (first != last) {
        push_back(*first++);
    }
}

forward_list::forward_list(const forward_list &rhs) : forward_list() {
    for (auto value: rhs) {
        push_back(value);
    }
}

forward_list::iterator forward_list::begin() {
    return forward_list::iterator(head);
}

forward_list::iterator forward_list::end() {
    return forward_list::iterator(tail);
}

forward_list::const_iterator forward_list::begin() const {
    return forward_list::const_iterator(head);
}

forward_list::const_iterator forward_list::end() const {
    return forward_list::const_iterator(tail);
}

forward_list::forward_list() : head_sentinel(), head(&head_sentinel), tail(&head_sentinel) {

}

forward_list::iterator forward_list::push_back(forward_list::value_type value) {
    tail->data = value;
    auto old_tail = tail;
    tail = make_node(tail);
    return old_tail;
}

#ifdef NOT_IN_THIS_COURSE
forward_list::forward_list(forward_list && xval) noexcept {
    swap(*this, xval);
}
#endif

/**
 * Removes an element from the list. The size of the list is reduced by one.
 *
 * @param element An iterator to a valid element in the list.
 * @return An iterator to the next value in the list. This is actually the same object as the element parameter.
 */
forward_list::iterator forward_list::remove(forward_list::iterator element) {
    // Actually deletes the next element and transfer the contents of the delete node here.
    // 1 - This might be the sentinel object
    // 2 - We can't influence the previous nodes next pointer.
    auto to_delete = element.current->next;
    element.current->data = std::move(element.current->next->data);
    element.current->next = element.current->next->next;
    to_delete->next = nullptr;
    delete to_delete;
    return element;
}
forward_list::iterator forward_list::pop_front(){
    return remove(iterator(&head_sentinel));
}
forward_list::forward_list(size_t size, forward_list::value_type value) : forward_list() {
    while (size--) {
        push_back(value);
    }
}
