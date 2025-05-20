// clang-format off
/// tem_list.h: provides a template for implementing a doubly-linked list.
///
/// Macros:
///     DECLARE_LIST(List, T, STORAGE, value_gen): declare a list.
///         value_gen: define the value generator.
///         - GENERATOR_PLAIN_VALUE: define a plain value generator.
///         - GENERATOR_CLASS_VALUE: define a class value generator.
///         - GENERATOR_CUSTOM_VALUE: define a custom value generator.
///     DEFINE_LIST(List, T, STORAGE): define a list.
///
///     Here STORAGE is either `FUNC_STATIC` or `FUNC_EXTERN`
///
/// List Methods:
///     List.init(): initialize the list.
///     List.drop(): drop the list.
///     List.clone_from(const List *other): clone the list from another list.
///     List.clone() const -> List: clone the list.
///     List.front() -> T*: get the front element of the list.
///     List.back() -> T*: get the back element of the list.
///     List.push_front(T value): push a value to the front of the list.
///     List.push_back(T value): push a value to the back of the list.
///     List.pop_front() -> T: pop a value from the front of the list.
///     List.pop_back() -> T: pop a value from the back of the list.
///     List.remove_front(): remove the front element of the list.
///     List.remove_back(): remove the back element of the list.
///     List.remove(ListNode *it) -> ListNode *: remove a node from the list, and return the next node.
///     List.insert_after(ListNode *it, T value): insert a value after a node.
///     List.swap(List *other): swap the list with another list.
///     List.empty() -> bool: check if the list is empty.
///     List.clear(): clear the list.
///
// clang-format on
#pragma once

#include "debug.h"
#include "tem_memory_primitive.h"
#include "utils.h"

#undef DECLARE_LIST
#define DECLARE_LIST(List, T, STORAGE, value_gen)                              \
    DECLARE_LIST_INNER(List, CONCATENATE(List, Node), typeof(T), STORAGE);     \
    value_gen(List, T);

#undef DEFINE_LIST
#define DEFINE_LIST(List, T, STORAGE)                                          \
    DEFINE_LIST_INNER(List, CONCATENATE(List, Node), typeof(T), STORAGE);

#undef DECLARE_LIST_INNER
#define DECLARE_LIST_INNER(List, ListNode, T, STORAGE)                         \
                                                                               \
    typedef struct ListNode {                                                  \
        T data;                                                                \
        struct ListNode *prev;                                                 \
        struct ListNode *next;                                                 \
    } ListNode;                                                                \
                                                                               \
    typedef struct List {                                                      \
        struct ListNode *head;                                                 \
        struct ListNode *tail;                                                 \
        usize size;                                                            \
    } List;                                                                    \
                                                                               \
    /* NOTE: Methods that are required to defined outside the template */      \
                                                                               \
    /* List::drop_value(T *value) */                                           \
    FUNC_STATIC void NSMTD(List, drop_value, /, T * value);                    \
                                                                               \
    /* List::clone_value(const T *other) -> T */                               \
    FUNC_STATIC T NSMTD(List, clone_value, /, const T *other);                 \
                                                                               \
    /* NOTE: Methods to implement in .c */                                     \
                                                                               \
    /* List.drop() */                                                          \
    STORAGE void MTD(List, drop, /);                                           \
                                                                               \
    /* List.clone_from(const List *other) */                                   \
    STORAGE void MTD(List, clone_from, /, const List *other);                  \
                                                                               \
    /* List.front() -> T* */                                                   \
    STORAGE T *MTD(List, front, /);                                            \
                                                                               \
    /* List.back() -> T*/                                                      \
    STORAGE T *MTD(List, back, /);                                             \
                                                                               \
    /* List.push_front(T value) */                                             \
    STORAGE void MTD(List, push_front, /, T value);                            \
                                                                               \
    /* List.push_back(T value) */                                              \
    STORAGE void MTD(List, push_back, /, T value);                             \
                                                                               \
    /* List.pop_front() -> T */                                                \
    STORAGE T MTD(List, pop_front, /);                                         \
                                                                               \
    /* List.pop_back() -> T */                                                 \
    STORAGE T MTD(List, pop_back, /);                                          \
                                                                               \
    /* List.remove(ListNode *it) -> ListNode */                                \
    STORAGE ListNode *MTD(List, remove, /, ListNode * it);                     \
                                                                               \
    /* List.insert_after(ListNode *it, T value) */                             \
    STORAGE void MTD(List, insert_after, /, ListNode * it, T value);           \
                                                                               \
    /* NOTE: static methods that are not required to implement in .c */        \
                                                                               \
    /* List.init() */                                                          \
    FUNC_STATIC void MTD(List, init, /) {                                      \
        self->head = NULL;                                                     \
        self->tail = NULL;                                                     \
        self->size = 0;                                                        \
    }                                                                          \
                                                                               \
    /* List.clone() const -> List */                                           \
    FUNC_STATIC DEFAULT_DERIVE_CLONE(List, /);                                 \
                                                                               \
    /* List.swap(List *other) */                                               \
    FUNC_STATIC void MTD(List, swap, /, List * other) {                        \
        ListNode *MPROT(temp) = self->head;                                    \
        self->head = other->head;                                              \
        other->head = MPROT(temp);                                             \
        MPROT(temp) = self->tail;                                              \
        self->tail = other->tail;                                              \
        other->tail = MPROT(temp);                                             \
        usize MPROT(temp_size) = self->size;                                   \
        self->size = other->size;                                              \
        other->size = MPROT(temp_size);                                        \
    }                                                                          \
                                                                               \
    /* List.remove_front() */                                                  \
    FUNC_STATIC void MTD(List, remove_front, /) {                              \
        T MPROT(value) = CALL(List, *self, pop_front, /);                      \
        NSCALL(List, drop_value, /, &MPROT(value));                            \
    }                                                                          \
                                                                               \
    /* List.remove_back() */                                                   \
    FUNC_STATIC void MTD(List, remove_back, /) {                               \
        T MPROT(value) = CALL(List, *self, pop_back, /);                       \
        NSCALL(List, drop_value, /, &MPROT(value));                            \
    }                                                                          \
                                                                               \
    /* List.empty() -> bool */                                                 \
    FUNC_STATIC bool MTD(List, empty, /) { return self->size == 0; }           \
                                                                               \
    /* List.clear() */                                                         \
    FUNC_STATIC void MTD(List, clear, /) { DROPOBJ(List, *self); }

#undef DEFINE_LIST_INNER
#define DEFINE_LIST_INNER(List, ListNode, T, STORAGE)                          \
    /* List.drop() */                                                          \
    STORAGE void MTD(List, drop, /) {                                          \
        while (self->head) {                                                   \
            ListNode *MPROT(now) = self->head;                                 \
            self->head = self->head->next;                                     \
            NSCALL(List, drop_value, /, &MPROT(now)->data);                    \
            free(MPROT(now));                                                  \
        }                                                                      \
        self->head = NULL;                                                     \
        self->tail = NULL;                                                     \
        self->size = 0;                                                        \
    }                                                                          \
                                                                               \
    /* List.clone_from(const List *other) */                                   \
    STORAGE void MTD(List, clone_from, /, const List *MPROT(other)) {          \
        DROPOBJ(List, *self);                                                  \
        if (!MPROT(other)->head) {                                             \
            return;                                                            \
        }                                                                      \
        ListNode *MPROT(p) = NULL;                                             \
        ListNode *MPROT(now) = NULL;                                           \
        ListNode *MPROT(it) = MPROT(other)->head;                              \
        while (MPROT(it)) {                                                    \
            MPROT(p) = MPROT(now);                                             \
            MPROT(now) = CREOBJRAWHEAP(ListNode);                              \
            MPROT(now)->data = NSCALL(List, clone_value, /, &MPROT(it)->data); \
            if (MPROT(p)) {                                                    \
                MPROT(p)->next = MPROT(now);                                   \
            } else {                                                           \
                self->head = MPROT(now);                                       \
            }                                                                  \
            MPROT(now)->prev = MPROT(p);                                       \
            MPROT(it) = MPROT(it)->next;                                       \
        }                                                                      \
        self->tail = MPROT(now);                                               \
        self->size = MPROT(other)->size;                                       \
    }                                                                          \
                                                                               \
    /* List.front() -> T* */                                                   \
    STORAGE T *MTD(List, front, /) {                                           \
        ASSERT(self->head);                                                    \
        return &self->head->data;                                              \
    }                                                                          \
                                                                               \
    /* List.back() -> T*/                                                      \
    STORAGE T *MTD(List, back, /) {                                            \
        ASSERT(self->tail);                                                    \
        return &self->tail->data;                                              \
    }                                                                          \
                                                                               \
    /* List.push_front(T value) */                                             \
    STORAGE void MTD(List, push_front, /, T MPROT(value)) {                    \
        ListNode *MPROT(now) = CREOBJRAWHEAP(ListNode);                        \
        MPROT(now)->data = MPROT(value);                                       \
        MPROT(now)->next = self->head;                                         \
        MPROT(now)->prev = NULL;                                               \
        if (self->head) {                                                      \
            self->head->prev = MPROT(now);                                     \
        }                                                                      \
        self->head = MPROT(now);                                               \
        if (!self->tail) {                                                     \
            self->tail = MPROT(now);                                           \
        }                                                                      \
        self->size++;                                                          \
    }                                                                          \
                                                                               \
    /* List.push_back(T value) */                                              \
    STORAGE void MTD(List, push_back, /, T MPROT(value)) {                     \
        ListNode *MPROT(now) = CREOBJRAWHEAP(ListNode);                        \
        MPROT(now)->data = MPROT(value);                                       \
        MPROT(now)->prev = self->tail;                                         \
        MPROT(now)->next = NULL;                                               \
        if (self->tail) {                                                      \
            self->tail->next = MPROT(now);                                     \
        }                                                                      \
        self->tail = MPROT(now);                                               \
        if (!self->head) {                                                     \
            self->head = MPROT(now);                                           \
        }                                                                      \
        self->size++;                                                          \
    }                                                                          \
                                                                               \
    /* List.pop_front() -> T */                                                \
    STORAGE T MTD(List, pop_front, /) {                                        \
        ASSERT(self->head);                                                    \
        ListNode *MPROT(now) = self->head;                                     \
        T MPROT(value) = MPROT(now)->data;                                     \
        self->head = MPROT(now)->next;                                         \
        if (self->head) {                                                      \
            self->head->prev = NULL;                                           \
        } else {                                                               \
            self->tail = NULL;                                                 \
        }                                                                      \
        free(MPROT(now));                                                      \
        self->size--;                                                          \
        return MPROT(value);                                                   \
    }                                                                          \
                                                                               \
    /* List.pop_back() -> T */                                                 \
    STORAGE T MTD(List, pop_back, /) {                                         \
        ASSERT(self->tail);                                                    \
        ListNode *MPROT(now) = self->tail;                                     \
        T MPROT(value) = MPROT(now)->data;                                     \
        self->tail = MPROT(now)->prev;                                         \
        if (self->tail) {                                                      \
            self->tail->next = NULL;                                           \
        } else {                                                               \
            self->head = NULL;                                                 \
        }                                                                      \
        free(MPROT(now));                                                      \
        self->size--;                                                          \
        return MPROT(value);                                                   \
    }                                                                          \
    /* List.remove(ListNode *it) -> ListNode */                                \
    STORAGE ListNode *MTD(List, remove, /, ListNode * MPROT(it)) {             \
        if (MPROT(it)->prev) {                                                 \
            MPROT(it)->prev->next = MPROT(it)->next;                           \
        } else {                                                               \
            self->head = MPROT(it)->next;                                      \
        }                                                                      \
        if (MPROT(it)->next) {                                                 \
            MPROT(it)->next->prev = MPROT(it)->prev;                           \
        } else {                                                               \
            self->tail = MPROT(it)->prev;                                      \
        }                                                                      \
        ListNode *MPROT(ret) = MPROT(it)->next;                                \
        NSCALL(List, drop_value, /, &MPROT(it)->data);                         \
        self->size--;                                                          \
        free(MPROT(it));                                                       \
        return MPROT(ret);                                                     \
    }                                                                          \
    /* List.insert_after(ListNode *it, T value) */                             \
    STORAGE void MTD(List, insert_after, /, ListNode * it, T value) {          \
        if (!it) {                                                             \
            CALL(List, *self, push_front, /, value);                           \
        }                                                                      \
        ListNode *MPROT(now) = CREOBJRAWHEAP(ListNode);                        \
        MPROT(now)->data = value;                                              \
        MPROT(now)->next = it->next;                                           \
        MPROT(now)->prev = it;                                                 \
        if (it->next) {                                                        \
            it->next->prev = MPROT(now);                                       \
        } else {                                                               \
            self->tail = MPROT(now);                                           \
        }                                                                      \
        it->next = MPROT(now);                                                 \
        self->size++;                                                          \
    }
