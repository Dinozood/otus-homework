//
// Created by dinozood on 31.10.23.
//

#ifndef IP_FILTER_CUSTOM_ALLOCATOR_H
#define IP_FILTER_CUSTOM_ALLOCATOR_H

/*
 * Construct is for construing something in allocated memory
 * Allocate is for allocating memory for some object which is going to be memory where ojbect will be constructed
 *
 * */

#include <cstddef>
#include <memory>
#include <iostream>
#include <vector>
#include <functional>

constexpr std::size_t _default_allocation_size = 10;
#define base
#ifdef base
template<typename Unit, std::size_t _default_size = _default_allocation_size>
class base_allocator {
private:
    std::size_t default_size = (_default_size * sizeof(Unit));
    std::size_t pos = 0;
    std::shared_ptr<void> memory_pool;

    static void deleter(void *ptr) {
        (void)ptr;
//        ::operator delete(ptr); // as far  our allocator should delete memory...
    };

public:
    using value_type = Unit;

    base_allocator() {
        memory_pool = std::shared_ptr<void>(::operator new(default_size), deleter);
    };

    template<class U>
    base_allocator(const base_allocator<U> &_other) {
        base_allocator<U, _other.default_size>();
    }

    virtual Unit *allocate(std::size_t __size, const void * = static_cast<const void *>(nullptr)) {
        if ((__size * sizeof(Unit)) + pos > default_size)
            throw std::bad_alloc();
        auto now_pos = pos;
        pos += (__size * sizeof(Unit));
        return reinterpret_cast<Unit *>(
                static_cast<uint8_t *>(memory_pool.get()) + now_pos);
    }

    void deallocate(Unit *p, std::size_t) {
        this->destroy(p);
//        In real scenario here should be some memory_management
    }

    void destroy(Unit *p) {
        p->~Unit();
    }

    ~base_allocator() noexcept {
//        ::operator delete(memory_pool.get());
//        memory_pool = nullptr;
    }

    template<class U>
    struct rebind {
        typedef base_allocator<U, _default_size> other;
    };

    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap = std::false_type;
};

template<class unit_type, class U>
constexpr bool operator==(const base_allocator<unit_type> &a1, const base_allocator<U> &a2) noexcept {
    (void )a1; (void)a2;
    return false;
}

template<class unit_type, class U>
constexpr bool operator!=(const base_allocator<unit_type> &a1, const base_allocator<U> &a2) noexcept {
    (void )a1; (void)a2;
    return true;
}

/*
 * ------------------------------------------------------------------------------------------------
 * */
#endif

#define expand
#ifdef expand

template<typename Unit, std::size_t _default_size = _default_allocation_size>
class expanding_allocator {
private:
    struct memory_pool {
        std::shared_ptr<void> pool;
        std::size_t size;
        std::size_t local_pos = 0;
        std::size_t used = 0;

        static void deleter(void* ptr) {
//            ::operator delete(ptr);
            (void )ptr;
//            ptr = nullptr;
        }

        explicit memory_pool(std::size_t pool_size) {
            pool = std::shared_ptr<void>(::operator new(pool_size), deleter);
            size = pool_size;
        }

        void expanded(std::size_t _size) {
            this->local_pos += _size;
            this->used += _size;
        }

        ~memory_pool() = default;
    };

    std::size_t default_size = (_default_size * sizeof(Unit));
    std::vector<memory_pool> memory_pools;

public:
    using value_type = Unit;

    expanding_allocator() {
        memory_pools.emplace_back(memory_pool(default_size));
    };

    template<class U>
    explicit expanding_allocator(const expanding_allocator<U> &_other) {
        expanding_allocator<U, _other.default_size>();
    }

    Unit *allocate_new_pool(std::size_t _size) {
        default_size > _size ? default_size *= 2 : default_size = _size * 2;
        memory_pools.emplace_back(memory_pool(default_size));
        memory_pools.back().expanded(_size * sizeof(Unit));
        return static_cast<Unit *>(this->memory_pools.back().pool.get());
    }

    Unit *allocate(std::size_t _size, const void * = static_cast<const void *>(nullptr)) {
        auto last_pool = this->memory_pools.back();
//        if ((_size * sizeof(Unit)) + last_pool.local_pos > last_pool.size)
//            return allocate_new_pool(_size);
        auto now_pos = last_pool.local_pos;
        last_pool.expanded(_size * sizeof(Unit));
        return reinterpret_cast<Unit *>(static_cast<uint8_t *>(memory_pools.back().pool.get()) + now_pos);
    }

    std::size_t find_memory_pool(void* p){
        (void)p;
        /*for(std::size_t i = 0; i < memory_pools.size(); ++i) {
            if (p > memory_pools[i].pool.get() and
            p < ((uint8_t*)(memory_pools[i].pool.get()) + memory_pools[i].size))
                return i;
        }*/
//        throw std::logic_error("Pointer not in allocator memory pools");
        return 0;
    }

    void deallocate(Unit *p, std::size_t) {
        (void)p;
        /*
        auto index = find_memory_pool(p);
        p->~Unit();
        memory_pools[index].used -= sizeof(Unit);
        if(memory_pools[index].used == 0) {
            memory_pools.erase(memory_pools.begin() + index);
        }
        memory_pools.shrink_to_fit();
        */
    }

    ~expanding_allocator() noexcept {
//        ::delete (memory_pool);
//        memory_pool = nullptr;
    }

    template<class U>
    struct rebind {
        typedef expanding_allocator<U, _default_size> other;
    };

    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap = std::false_type;
};

template<class unit_type, class U>
constexpr bool operator==(const expanding_allocator<unit_type> &a1, const expanding_allocator<U> &a2) noexcept {
    (void )a1; (void)a2;
    return false;
}

template<class unit_type, class U>
constexpr bool operator!=(const expanding_allocator<unit_type> &a1, const expanding_allocator<U> &a2) noexcept {
    (void )a1; (void)a2;
    return true;
}

#endif

#endif //IP_FILTER_CUSTOM_ALLOCATOR_H
