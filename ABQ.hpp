#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
    size_t front_;
    size_t back_;

public:
    // Constructors + Big 5
    ABQ() : capacity_(1), curr_size_(0), array_(new T[capacity_]), front_(0), back_(0) {}

    explicit ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity_]), front_(0), back_(0) {}

    ABQ(const ABQ& other) : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[other.capacity_]), front_(other.front_), back_(other.back_) {
        for (int i = 0; i < other.curr_size_; i++) {
            this->array_[i] = other.array_[i];
        }
    }

    ABQ& operator=(const ABQ& rhs) {
        if (this = &rhs) return *this;

        delete[] array_;

        this->array_ = new T[rhs.capacity_];
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->front_ = rhs.front_;
        this->back_ = rhs.back_;

        for (int i = 0; i < rhs.curr_size_; i++) {
            this->array_[i] = rhs.array_[i];
        }

        return *this;
    }

    ABQ(ABQ&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_), front_(other.front_), back_(other.back_) {
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this = &rhs) return *this;

        delete[] array_;
        
        this->array_ = rhs.array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->front_ = rhs.front_;
        this->back_ = rhs.back_;

        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.front_ = 0;
        rhs.back_ = 0;

        return *this;
    }

    ~ABQ() noexcept override {
        delete[] array_;
        capacity_ = 0;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ >= capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* newArray = new T[capacity_];

            for (int i = 0; i < curr_size_; i++) {
                array_[i] = newArray[i];
            }

            delete[] array_;
            array_ = newArray;
        }

        array_[back_] = data;
        back_ = (back_ + 1) % capacity_;
        ++curr_size_;
    }

    // Access
    T peek() const override {
        return array_[front_];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) throw std::out_of_range("Empty");
        T temp = array_[front_];
        front_ = (front_ + 1) % capacity_;
        return temp;
    }
};
