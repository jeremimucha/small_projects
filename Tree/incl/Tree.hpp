#ifndef TREE_HPP_
#define TREE_HPP_


#include <memory>
#include <iterator>
#include <utility>
#include <initializer_list>


template<typename> class Tree_node;
template<typename> class Tree_iterator;
template<typename> class Tree_const_iterator;


/* Tree */
/* ------------------------------------------------------------------------- */
template< typename T
        , typename Compare = std::less<T>
        , typename Allocator = std::allocator<T>
        >
class Tree
{
    typedef Tree_node<T>                            Node;
    
public:
    typedef T                                       value_type;
    typedef Allocator                               allocator_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;
    typedef T*                                      pointer;
    typedef const T*                                const_pointer;
    typedef Tree_iterator<T>                        iterator;
    typedef Tree_const_iterator<T>                  const_iterator;
    typedef std::reverse_iterator<iterator>         reverse_iterator;
    typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

/* constructors */
    explicit Tree( const Allocator& al = Allocator() )
        : alloc(al), root() { }
    explicit Tree( size_type count, const Allocator& al = Allocator() );

private:
    Allocator alloc;
    Compare cmp;
    Node root;
};
/* ------------------------------------------------------------------------- */

/* Tree_node */
/* ------------------------------------------------------------------------- */
template<typename T>
class Tree_node
{
    friend class Tree<T>;
    friend class Tree_iterator<T>;
    friend class Tree_const_iterator<T>;

    typedef Tree_node<T>    self;

public:
    Tree_node() { }
    explicit Tree_node( const T& val,
                        self* parent_=nullptr,
                        self* left_=nullptr, self* right_=nullptr ) noexcept
        : parent(parent_)
        , left(left_)
        , right(right_)
        , data(val)
        { }
    template<typename... Args>
    explicit Tree_node( self* parent_=nullptr,
                        self* left_=nullptr, self* right_=nullptr,
                        Args&&... args) noexcept
        : parent(parent_)
        , left(left_)
        , right(right_)
        , data(std::forward<Args>(args)...)
        { }
private:
    self* parent;
    self* left;
    self* right;
    T     data;
};
/* ------------------------------------------------------------------------- */


/* Tree_iterator */
/* ------------------------------------------------------------------------- */
template<typename T>
class Tree_iterator
{
    friend class Tree<T>;
    typedef Tree_iterator<T>                    self;
public:
    typedef Tree_node<T>                        Node;
    typedef std::bidirectional_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef Tree_const_iterator<T>              const_iterator;

    /* constructors */
    Tree_iterator()
        : p_node() { }
    explicit Tree_iterator( Node* node )
        : p_node( node )
        { }

    reference operator*() const noexcept
        { return p_node->data; }
    pointer operator->() const noexcept
        { return &(p_node->data); }

    self& operator++() noexcept
        {
        }
    self operator++(int) noexcept
        {
        }
    self& operator--() noexcept
        {
        }
    self operator--(int) noexcept
        {
        }

    bool operator==( const self& other ) const noexcept
        { return p_node == other.p_node; }
    bool operator!=( const self& other ) const noexcept
        { return p_node != other.p_node; }

private:
    Node* p_node;
};
/* ------------------------------------------------------------------------- */


/* Tree_const_iterator */
/* ------------------------------------------------------------------------- */
template<typename T>
class Tree_const_iterator
{
    friend class Tree<T>;
    typedef Tree_const_iterator<T>              self;
public:
    typedef const Tree_node<T>                  Node;
    typedef std::bidirectional_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef const T*                            pointer;
    typedef const T&                            reference;
    typedef Tree_iterator<T>                    iterator;

    /* constructors */
    Tree_const_iterator() = default;
    Tree_const_iterator( Node* node )
        : p_node(node)
        { }
    
    reference operator*() noexcept
        { return p_node->data; }
    pointer operator->() noexcept
        { return &(p_node->data); }

    self& operator++() noexcept
        {
        }
    self operator++(int) noexcept
        {
        }
    self& operator--() noexcept
        {
        }
    self operator--(int) noexcept
        {
        }

    bool operator==( const self& other ) const noexcept
        { return p_node == other.p_node; }
    bool operator!=( const self& other ) const noexcept
        { return p_node != other._pnode; }

private:
    Node* p_node;
};
/* ------------------------------------------------------------------------- */
#endif /* TREE_HPP_ */
