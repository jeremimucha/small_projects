#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include <memory>
#include <iterator>
#include <utility>
#include <initializer_list>

template<typename> class node;
template<typename> class List_iterator;
template<typename> class List_const_iterator;


/* List */
/* ------------------------------------------------------------------------- */
template< typename T,
          typename Allocator = std::allocator<node<T>> >
class List
{
    typedef node<T>                Node;
public:
    using value_type             = T;
    using allocator_type         = Allocator;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = T*;
    using const_pointer          = const T*;
    using iterator               = List_iterator<T>;
    using const_iterator         = List_const_iterator<T>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

/* constructors */
    explicit List( const Allocator& al = Allocator() )
        : alloc(al), head(), tail()
        {
            head.next = &tail;
            tail.prev = &head;
        }
    explicit List( size_type count, const Allocator& al = Allocator() );
    // List( size_type count,
    //             const T& value,
    //             const Allocator& al = Allocator() );
    // template<typename InputIter>
    // List( InputIter first, InputIter last,
    //             const Allocator& al = Allocator() );
    List( std::initializer_list<T> init,
                const Allocator& al = Allocator() );
    ~List() noexcept;

/*  copy control */
    List( const List& other );
    List( List&& other ) noexcept;
    List& operator=( const List& other );
    List& operator=( List&& other );
    List& operator=( std::initializer_list<T> init );

/* element access */
    reference front() noexcept
        { return head.next->value; }
    const_reference front() const noexcept
        { return head.next->value; }
    reference back() noexcept
        { return tail.prev->value; }
    const_reference back() const noexcept
        { return tail.prev->value; }

/* capacity */
    bool empty() noexcept
        { return head.next == tail.next == nullptr; }
    size_type size() noexcept;

/* iterators */
    iterator begin() noexcept
        { return iterator(head.next); }
    iterator end() noexcept
        { return iterator(&tail); }
    const_iterator begin() const noexcept
        { return const_iterator(head.next); }
    const_iterator end() const noexcept
        { return const_iterator(&tail); }
    const_iterator cbegin() const noexcept
        { return const_iterator(head.next); }
    const_iterator cend() const noexcept
        { return const_iterator(&tail); }

/* modifiers */
    void clear() noexcept
        { free(); head.next = tail.prev = nullptr; }
    
    iterator insert(iterator pos, const T& value );
    iterator insert(iterator pos, T&& value);
    iterator insert(iterator pos, size_type count, const T& value);
    template<typename InputIterator>
    iterator insert(iterator pos, InputIterator first, InputIterator last);
    iterator insert(iterator pos, std::initializer_list<T> init);

protected:
    template<typename... Args>
    Node* create_node(Node* p, Node* n, Args&&... args);
    std::pair<Node*,Node*> alloc_n( size_type n, const T& val=T() );
    template<typename Iter>
    std::pair<Node*,Node*> alloc_range(Iter begin, Iter end);
    void free() noexcept;

private:
    Allocator alloc;
    Node head;
    Node tail;
};
/* ------------------------------------------------------------------------- */



/* node */
/* ------------------------------------------------------------------------- */
template<typename T>
class node
{
friend class List<T>;
friend class List_iterator<T>;
friend class List_const_iterator<T>;
public:
    node() { }
    explicit node(const T& val, node* p=nullptr, node* n=nullptr) noexcept
        : prev(p), next(n), value(val)
        { }
    template<typename... Args>
    node(node* p=nullptr, node* n=nullptr, Args&&... args)
        : prev(p), next(n), value(std::forward<Args>(args)...)
        { }
private:
    node* prev;
    node* next;
    T value;
};
/* ------------------------------------------------------------------------- */


/* List_iterator */
/* ------------------------------------------------------------------------- */
template<typename T>
class List_iterator 
/*     : public std::iterator<
                std::bidirectional_iterator_tag // iterator_category
                ,T                               // value_type
                ,std::ptrdiff_t                  // difference_type
                ,T*                              // pointer
                ,T&                              // reference
                >  */           
{
    friend class List<T>;
public:
    typedef List_iterator<T>                    self;
    typedef node<T>                             Node;
    typedef std::bidirectional_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef List_const_iterator<T>              const_iterator;          
    /* constructors */
    List_iterator()
        : current()
        { }
    explicit List_iterator(Node* n)
        : current(n)
        { }
    
    reference operator*() const noexcept
        { return current->value; }
    pointer operator->() const noexcept
        { return &(current->value); }

    self& operator++() noexcept
        {
            current = current->next;
            return *this;
        } 
    self& operator++(int) noexcept
        {
            self temp(*this);
            current = current->next;
            return temp;
        }
    self& operator--() noexcept
        {
            current = current->prev;
            return *this;
        }
    self operator--(int) noexcept
        {
            self temp(*this);
            current = current->prev;
            return temp;
        }
    
    operator const_iterator()
        { return const_iterator(current); }

    bool operator==(const self& other) const
        { return current == other.current; }
    bool operator!=(const self& other) const
        { return current != other.current; }

private:
    Node* current;
};
/* ------------------------------------------------------------------------- */


/* List_const_iterator */
/* ------------------------------------------------------------------------- */
template<typename T>
class List_const_iterator
/*     : public std::iterator<
                std::bidirectional_iterator_tag  // iterator_category
                ,T                               // value_type
                ,std::ptrdiff_t                  // difference_type
                ,const T*                        // pointer
                ,const T&                        // reference
                > */
{
    friend class List<T>;
public:
    typedef List_const_iterator<T>              self;
    typedef const node<T>                       Node;
    typedef List_iterator<T>                    iterator;
    typedef std::bidirectional_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef const T*                            pointer;
    typedef const T&                            reference;
    
    /* constructors */
    List_const_iterator()
        : current()
        { }
    explicit List_const_iterator(const Node* n)
        : current(n)
        { }
    
    /* access */
    reference operator*() const
        { return current->value; }
    pointer operator->() const
        { return &(current->value); }

    self& operator++() noexcept
        {
            current = current->next;
            return *this;
        }
    self operator++(int) noexcept
        {
            self temp(*this);
            current = current->next;
            return temp;
        }
    self& operator--() noexcept
        {
            current = current->prev;
            return *this;
        }
    self operator--(int) noexcept
        {
            self temp(*this);
            current = current->prev;
            return temp;
        }

    bool operator==(const self& other) const noexcept
        { return current == other.current; }
    bool operator!=(const self& other) const noexcept
        { return current != other.current; }

private:
    Node* current;
};
/* ------------------------------------------------------------------------- */


/* List implementation */
/* ------------------------------------------------------------------------- */

/* helper functions */
/* ------------------------------------------------------------------------- */
template<typename T, typename Allocator>
    template<typename... Args>
inline typename List<T,Allocator>::Node*
List<T,Allocator>::create_node(Node* p, Node* n, Args&&... args)
{
    Node* data = alloc.allocate(1);
    alloc.construct(data, p, n, std::forward<Args>(args)...);
    return data;
}

template<typename T, typename Allocator>
inline std::pair<node<T>*,node<T>*>
List<T,Allocator>::alloc_n( size_type n, const T& val )
{
    Node* data = alloc.allocate(1);
    alloc.construct(data, val);
    Node* pred = data;
    for(size_type i=1; i<n; ++i){
        Node* succ = alloc.allocate(1);
        alloc.construct(succ, val, pred);
        pred->next = succ;
        pred = succ;
    }
    data->prev = &head;
    pred->next =  &tail;
    return std::make_pair(data, pred);
}

template<typename T, typename Allocator>
    template<typename Iter>
inline std::pair<node<T>*,node<T>*>
List<T,Allocator>::alloc_range(Iter begin, Iter end)
{
    Node* data = alloc.allocate(1);
    alloc.construct(data, *begin);
    Node* pred = data;
    while(++begin != end){
        Node* succ = alloc.allocate(1);
        alloc.construct(succ, *begin, succ);
        pred->next = succ;
        pred = succ;
    }
    data->prev = &head;
    pred->next = &tail;
    return std::make_pair(data, pred);
}

template<typename T, typename Allocator>
inline void List<T,Allocator>::free() noexcept
{
    Node* next = head.next;
    Node* temp;
    while(next != &tail){
        temp = next->next;
        alloc.destroy(next);
        alloc.deallocate(next, 1);
        next = temp;
    }
}
/* ------------------------------------------------------------------------- */


/* constructors */
/* ------------------------------------------------------------------------- */
template<typename T, typename Allocator>
inline List<T,Allocator>::List( size_type count, const Allocator& al )
    : alloc(al)
{
    std::pair<Node*,Node*> data = alloc_n(count);
    head.next = data.first;
    tail.prev = data.second;
}

template<typename T, typename Allocator>
inline List<T,Allocator>::List( std::initializer_list<T> init
                              , const Allocator& al )
    : alloc(al)
{
    std::pair<Node*,Node*> data = alloc_range(init.begin(), init.end());
    head.next = data.first;
    tail.prev = data.second;
}

/* destructor */
template<typename T, typename Allocator>
inline List<T,Allocator>::~List() noexcept
{
    free();
    head.next = tail.prev = nullptr;
}
/* ------------------------------------------------------------------------- */

/* copy control */
/* ------------------------------------------------------------------------- */
template<typename T, typename Allocator>
inline List<T,Allocator>::List( const List& other )
    : alloc(other.alloc)
{
    std::pair<Node*,Node*> data = alloc_range(other.cbegin(), other.cend());
    head.next = data.first;
    tail.prev = data.second;
}

template<typename T, typename Allocator>
inline List<T,Allocator>::List( List&& other ) noexcept
    : alloc(std::move(other.alloc))
{
    head.next = other.head.next;
    other.head.next->prev = &head;
    tail.prev = other.tail.prev;
    other.tail.prev->next = &tail;

    other.head.next = other.tail.prev = nullptr;
}

template<typename T, typename Allocator>
inline List<T,Allocator>&
List<T,Allocator>::operator=( const List& other )
{
    if( this == &other )
        return *this;

    free();
    std::pair<Node*,Node*> data = alloc_range(other.cbegin(), other.cend());
    alloc = other.alloc;
    head.next = data.first;
    tail.prev = data.second;
    return *this;
}

template<typename T, typename Allocator>
inline List<T,Allocator>&
List<T,Allocator>::operator=( List&& other )
{
    if( this == &other )
        return *this;

    free();
    alloc = std::move(other.alloc);
    head.next = other.head.next;
    other.head.next->prev = &head;
    tail.prev = other.tail.prev;
    other.tail.prev->next = &tail;
    other.head.next = other.tail.prev = nullptr;
    return *this;
}

template<typename T, typename Allocator>
inline List<T,Allocator>&
List<T,Allocator>::operator=( std::initializer_list<T> init )
{
    free();
    std::pair<Node*,Node*> data = alloc_range(init.begin(), init.end());
    head.next = data.first;
    tail.prev = data.second;
    return *this;
}
/* ------------------------------------------------------------------------- */

/* capacity */
/* ------------------------------------------------------------------------- */
template<typename T, typename Allocator>
inline typename List<T,Allocator>::size_type List<T,Allocator>::size() noexcept
{
    size_type s{0};
    Node* pnode = head.next;
    while(pnode != &tail){
        ++s;
        pnode = pnode->next;
    }
    return s;
}
/* ------------------------------------------------------------------------- */


/* modifiers */
/* ------------------------------------------------------------------------- */
template<typename T, typename Allocator>
inline typename List<T,Allocator>::iterator
List<T,Allocator>::insert(iterator pos, const T& value )
{
    Node* target = create_node(pos.current->prev, pos.current, value);
    pos.current->prev->next = target;
    pos.current->prev = target;
    return iterator(target);
}
template<typename T, typename Allocator>
inline typename List<T,Allocator>::iterator
List<T,Allocator>::insert(iterator pos, T&& value)
{
    Node* target = create_node(pos.current->prev, pos.current, std::move(value));
    pos.current->prev->next = target;
    pos.current->prev = target;
    return iterator(target);
}
template<typename T, typename Allocator>
inline typename List<T,Allocator>::iterator
List<T,Allocator>::insert(iterator pos, size_type count, const T& value)
{
    std::pair<Node*,Node*> data = alloc_n(count, value);
    data.first->prev = pos.current->prev;
    pos.current->prev->next = data.first;
    pos.current->prev = data.second;
    data.second->next = pos.current;
    return iterator(data.second);
}
template<typename T, typename Allocator>
    template<typename InputIterator>
inline typename List<T,Allocator>::iterator
List<T,Allocator>::insert(iterator pos, InputIterator first, InputIterator last)
{
    std::pair<Node*,Node*> data = alloc_range(first, last);
    data.first->prev = pos.current->prev;
    pos.current->prev->next = data.first;
    pos.current->prev = data.second;
    data.second->next = pos.current;
    return iterator(data.second);
}
template<typename T, typename Allocator>
inline typename List<T,Allocator>::iterator
List<T,Allocator>::insert(iterator pos, std::initializer_list<T> init)
{
    std::pair<Node*,Node*> data = alloc_range(init.begin(), init.end());
    data.first->prev = pos.current->prev;
    pos.current->prev->next = data.first;
    pos.current->prev = data.second;
    data.second->next = pos.current;
    return iterator(data.second);
}
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */


#endif /* List_HPP_ */
