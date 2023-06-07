#include <iostream>
#include <cassert>

#include <memory>
#include <utility>
#include <optional>


using DType = int;

struct Node {
    DType value;
    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> next;
    explicit Node(DType val) : value(val), prev(nullptr), next(nullptr) {
    }
};

/*
 * head and tail are dummy nodes that contain no data.
 * 
 * The list internal structure is as follows:
 * 
 * head <-> data_node_1 <-> data_node_2 <-> ... <-> data_node_n <-> tail
 */
class DoublyLinkedList {
public:
    DoublyLinkedList() {
        head_ = std::make_shared<Node>(0);
        tail_ = std::make_shared<Node>(0);
        head_->next = tail_;
        tail_->prev = head_;
    }

    void pushBack(DType value) {
        auto new_node = std::make_shared<Node>(value);
        linkBetween(tail_->prev, new_node, tail_);
    }
    void pushFront(DType value) {
        auto new_node = std::make_shared<Node>(value);
        linkBetween(head_, new_node, head_->next);
    }

    std::optional<DType> popBack() {
        if (tail_->prev == head_) {
            return std::nullopt; // Empty list
        }
        auto back = tail_->prev;
        tail_->prev = back->prev;
        back->prev->next = tail_;
        return back->value;
    }
    std::optional<DType> popFront() {
        if (head_->next == tail_) {
            return std::nullopt; // Empty list
        }
        auto front = head_->next;
        head_->next = front->next;
        front->next->prev = head_;
        return front->value;
    }

private:
    // lhs_node <-> rhs_node   ==>   lhs_node <-> new_node <-> rhs_node
    void linkBetween(
        std::shared_ptr<Node> lhs_node,
        std::shared_ptr<Node> new_node,
        std::shared_ptr<Node> rhs_node
    ) {
        assert(lhs_node->next == rhs_node);
        assert(rhs_node->prev == lhs_node);

        lhs_node->next = new_node;
        new_node->prev = lhs_node;

        rhs_node->prev = new_node;
        new_node->next = rhs_node;
    }

private:
    std::shared_ptr<Node> head_;
    std::shared_ptr<Node> tail_;
};


int main() {
    DoublyLinkedList list;
    for (auto value : {4, 5, 6}) {
        list.pushBack(value);
    }
    for (auto value : {3, 2, 1}) {
        list.pushFront(value);
    }
    assert(list.popFront() == 1);
    assert(list.popFront() == 2);
    assert(list.popBack() == 6);
    assert(list.popBack() == 5);
    std::cout << *list.popFront() << std::endl;
}
