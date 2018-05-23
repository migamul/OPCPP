#ifndef BIN_STABLO_IMPL_H_INCLUDED
#define BIN_STABLO_IMPL_H_INCLUDED

#include <iostream>
#include "bin_stablo.h"

///// Implementacija metoda iz Node klase //////////////////////

template <typename T>
Node<T>::Node()
{
   left = nullptr;
   right = nullptr;
   return ;
}

template <typename T>
Node<T>::Node(T const &t)
{
    left = nullptr;
    right = nullptr;
    data = t;
    return ;
}

//// Implementacija metoda iz BinaryTree klase //////////////////

// Konstruktor---------------------------------------------------------------
template <typename T>
BinarySTree<T>::BinarySTree ()
{
    root = nullptr;
    return ;
}

// Empty--------------------------------------------------------------------
template <typename T>
bool BinarySTree<T>::empty() const
{
    if (root == nullptr)
        return true;
    return false;
}

// Size--------------------------------------------------------------------
template <typename T>
int BinarySTree<T>::size()
{
    return sizeRek(root);
}

template <typename T>
int BinarySTree<T>::sizeRek(Node<T> *node) //pomocna rekurzivna fja
{
     if(node == nullptr)
         return 0;
     else
        return sizeRek(node->right) + 1 + sizeRek(node->left);
}

// Clear-------------------------------------------------------------------
template <typename T>
void BinarySTree<T>::clear()
{
    if(root == nullptr)
        return ;
     clearRek(root);
     root = nullptr;
}

template <typename T>
void BinarySTree<T>::clearRek(Node<T> *node) //pomocna rekurzivna fja
{
    if(node == nullptr)
        return ;
        if(node->left != nullptr)
            clearRek(node->left);
        if(node->right != nullptr)
            clearRek(node->right);
        delete node;
}

// isInTree-----------------------------------------------------------------
template <typename T>
bool BinarySTree<T>::isInTree(T const & t)
{
    Node<T> *temp = new Node<T>;
    temp = find(root, t);
    if(temp == nullptr && temp->data != t)
        return false;
    else if(temp->data == t)
        return true;
    else
        return false;
    //return isInTreeRek(root,t);
}

/*template <typename T>
bool BinarySTree<T>::isInTreeRek(Node<T> *node, T const & t) //pomocna rekurzivna fja
{
    if(node == nullptr)
        return false;
    if(node->data == t)
        return true;
    if(node->data > t)
        return isInTreeRek(node->left, t);
    return isInTreeRek(node->right, t);
}*/

// Remove(element)------------------------------------------------------------
//trebat ce mi pomocne funkcije
// pronalazi max vrijednosti data
template<typename T>
T BinarySTree<T>::max(Node<T> *node)
{
    while(node->right)
        node = node->right;
    //std::cout << "max " << node->data << std::endl;
    return node->data;
}

//pronalazi cvor sa zadanom vrijednoscu data
template<typename T>
Node<T>* BinarySTree<T>::find(Node<T> *node, T const &t)
{
    if(node->data > t)
        return find(node->left,t);
    else if(node->data < t)
        return find(node->right, t);
    else if(node == nullptr)
        return nullptr;
    return node;
}

//pronalazi roditelja cvora node koji ima vrijednost data=t
template<class T>
Node<T>* BinarySTree<T>::parent(Node<T> *node, T const &t)
{
    if(node->left != nullptr && node->right != nullptr)
       if((node->left)->data == t || (node->right)->data == t)
           return node;

    if(node->left != nullptr)
        if((node->left)->data == t)
            return node;
    if(node->right != nullptr)
        if((node->right)->data == t)
            return node;
    if(node->data > t)
        return parent(node->left, t);
    if (node->data < t)
        return parent(node->right, t);
    return nullptr;
}

template <typename T>
ErrorCode BinarySTree<T>::remove(T const & t)
{
    if(isInTree(t) == 0)
        return notfound;

    Node<T> *temp, *pr;
    temp = find(root, t);

    if(temp->left == nullptr && temp->right == nullptr)
    {
        pr = parent(root,t);

        if(pr == 0)
            delete root;
        if(pr->left == temp)
        {
            pr->left = nullptr;
            delete temp;
            return success;
        }
        if(pr->right == temp)
        {
            pr->right = nullptr;
            delete temp;
            return success;
        }
    }

    if(temp->left == nullptr)
    {
        pr = parent(root, t);

        if(pr->left == temp)
        {
            pr->left = temp->right;
            delete temp;
            return success;
        }
        if(pr->right == temp)
        {
            pr->right = temp->right;
            delete temp;
            return success;
        }
    }

    if(temp->right == nullptr)
    {
        pr = parent(root, t);

        if(pr->left == temp)
        {
            pr->left = temp->left;
            delete temp;
            return success;
        }
        if(pr->right == temp)
        {
            pr->right = temp->left;
            delete temp;
            return success;
        }
    }

    T zamjena = max(temp->left);
    Node<T> *zamj = find(root, zamjena);
    Node<T> *prOdZamj = parent(root, zamj->data);

    if(zamj == prOdZamj->left)
        prOdZamj->left = nullptr;
    else if (zamj == prOdZamj->right)
        prOdZamj->right = nullptr;

    temp->data = zamj->data;
    if(zamj->left != nullptr)
    {
        prOdZamj->right = zamj->left;
    }
    delete zamj;
    return success;
}

// Insert (rekurzivno)-------------------------------------------------------
template <typename T>
ErrorCode BinarySTree<T>::insert(Node<T> * &root, T const & t)
{
    if(root == nullptr)
        {
            Node<T> *temp = new Node<T>(t);
            root = temp;
            return success;
        }

        if(root->data < t)
        {
            if(root->right == nullptr)
            {
                Node<T> *temp = new Node<T>(t);
                root->right = temp;
                return success;
            }
            insert(root->right, t);
        }
        if(root->data > t)
        {
            if(root->left == nullptr)
            {
                Node<T> *temp = new Node<T>(t);
                root->left = temp;
                return success;
            }
            insert(root->left, t);
        }
        return duplicate;
}

// Remove (root)----------------------------------------------------------------
template <typename T>
ErrorCode BinarySTree<T>::remove(Node<T> * &root)
{
    if(root == nullptr)
        return notfound;

    auto da = root->data;
        return remove(da);
}


// preOrder(rekurzija) -----------------------------------------------------------
template <typename T>
template <typename Funct>
void BinarySTree<T>::preOrder(Node<T> *root, Funct visit)
{
    if(root == nullptr)
        return ;
    if(root != nullptr)
    {
        visit(root->data);
        preOrder(root->left, visit);
        preOrder(root->right, visit);
    }
}

// postOrder(rekurzija)---------------------------------------------------
template <typename T>
template <typename Funct>
void BinarySTree<T>::postOrder(Node<T> *root, Funct visit)
{
    if(root == nullptr)
        return ;
    if(root != nullptr)
    {
        postOrder(root->left, visit);
        postOrder(root->right, visit);
        visit(root->data);
    }
}

// inOrder(rekurzija) ----------------------------------------------------
template <typename T>
template <typename Funct>
void BinarySTree<T>::inOrder(Node<T> *root, Funct visit)
{
    if(root == nullptr)
        return ;
    if(root != nullptr)
    {
        inOrder(root->left, visit);
        visit(root->data);
        inOrder(root->right, visit);
    }
}


//-----------------------------------------------------------------
/*template <typename T>
template <typename Funct>
void BinarySTree<T>::preOrder(Node<T> * root, Funct visit)
{
     throw "Not implemented.";   
}*/

#endif // BIN_STABLO_IMPL_H_INCLUDED
