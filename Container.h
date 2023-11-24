//
// Created by dinozood on 23.11.23.
//

#ifndef DUMMY_ALLOCATOR_CONTAINER_H
#define DUMMY_ALLOCATOR_CONTAINER_H

#include <iostream>
#include <memory>


template<typename unit_type, typename A = std::allocator<unit_type>>
class forward_list {
public:
    struct node {
        unit_type data;
        node *next;
    };

    forward_list(A allocator = A());

    ~forward_list();

    void add(const unit_type &data);

    template<typename U, typename B>
    friend std::ostream &operator<<(std::ostream &stream, const forward_list<U, B> &list);

    class Iterator {
    public:
        Iterator(forward_list *list) : parent(list), ptr(list->head) {}

        void operator++() {
            if (ptr != nullptr)
                ptr = ptr->next;
        }

        typename forward_list::node &operator*() {
            return *ptr;
        }

        typename forward_list::node *operator->() {
            return ptr;
        }

        bool IsEnd() const {
            return ptr == nullptr;
        }

    private:
        forward_list *parent;
        typename forward_list::node *ptr;
    };

    friend class Iterator;

    void destroy(node *p_node);


private:

    node *head;
    node *tail;

    using allocator_traits = std::allocator_traits<A>;
    using rebind_allocation = typename allocator_traits::template rebind_alloc<node>;

    A alloc_resource;
    rebind_allocation alloc_node;
};

template<typename T, typename A>
forward_list<T, A>::forward_list(A allocator)
        : head(nullptr), tail(nullptr), alloc_resource(allocator) {}

template<typename T, typename A>
forward_list<T, A>::~forward_list() {
    auto ptr = head;
    while (ptr != nullptr) {
        auto next = ptr->next;
        destroy(ptr);
        ptr = next;
    }
}

template<typename T, typename A>
void forward_list<T, A>::destroy(node *p_node) {
    alloc_node.deallocate(p_node, 1);
}

template<typename T, typename A>
void forward_list<T, A>::add(const T &data) {
    node *p_node = alloc_node.allocate(1);
    p_node = new(p_node) node{data, nullptr};
    if (tail != nullptr)
        tail->next = p_node;
    tail = p_node;
    if (head == nullptr)
        head = p_node;
}

template<typename T, typename A>
std::ostream &operator<<(std::ostream &stream, const forward_list<T, A> &list) {
    for (typename forward_list<T, A>::node *ptr = list.head; ptr != nullptr; ptr = ptr->next)
        stream << ptr->data << std::endl;

    return stream;
}


#endif //DUMMY_ALLOCATOR_CONTAINER_H
