#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class rational
{
    int n, d;
public:
    rational() : n(1), d(1) {};
    ~rational() {};

    void getData(int a, int b)
    {
        n = a;
        d = b;
    }

    int GCD(int n1, int remainder)
    {
        if (remainder == 0)
            return(n1);
        else { return(GCD(remainder, n1 % remainder)); }
    }

    void reduce(int& n, int& d)
    {
        int rdc = 0;
        if (d > n)
            rdc = GCD(d, n);
        else if (d < n)
            rdc = GCD(n, d);
        else
            rdc = GCD(n, d);
        n /= rdc;
        d /= rdc;
        cout << n << "/" << d << endl;
    }
    void prnt(rational temp) {
        reduce(temp.n, temp.d);
    }

};

struct Tree
{
    int count, level;
    string keya;
    string keyb;
    double key;
    Tree* right;
    Tree* left;
    Tree* parent;
    Tree* root;
}*root;



class AATree
{
public:
    AATree()
    {
        root = NULL;
    }


    int lookup(string& keya, string& keyb)
    {
        Tree* temp = new Tree;
        temp->keya = keya;
        temp->keyb = keyb;
        temp->key = stod(keya) / stod(keyb);
        temp->level = 1;
        temp->count = 0;
        temp->left = NULL;
        temp->right = NULL;
        temp->parent = NULL;
        temp = insert(root, temp);
        return temp->count;
    }


    void skew(Tree* temp)
    {
        Tree* ptr = temp->left;
        if (temp->parent->left == temp)
            temp->parent->left = ptr;
        else
            temp->parent->right = ptr;
        ptr->parent = temp->parent;
        temp->parent = ptr;
        temp->left = ptr->right;
        if (temp->left != NULL)
            temp->left->parent = temp;
        ptr->right = temp;
        temp->level = (temp->left ? temp->left->level + 1 : 1);
    }

 
    bool split(Tree* temp)
    {
        Tree* ptr = temp->right;
        if (ptr && ptr->right && (ptr->right->level == temp->level))
        {
            if (temp->parent->left == temp)
                temp->parent->left = ptr;
            else
                temp->parent->right = ptr;
            ptr->parent = temp->parent;
            temp->parent = ptr;
            temp->right = ptr->left;
            if (temp->right != NULL)
                temp->right->parent = temp;
            ptr->left = temp;
            ptr->level = temp->level + 1;
            return true;
        }
        return false;
    }


    void rebalance(Tree* temp)
    {
        temp->left = NULL;
        temp->right = NULL;
        temp->level = 1;
        for (temp = temp->parent; temp != root; temp = temp->parent)
        {
            if (temp->level != (temp->left ? temp->left->level + 1 : 1))
            {
                skew(temp);
                if (temp->right == NULL)
                    temp = temp->parent;
                else if (temp->level != temp->right->level)
                    temp = temp->parent;
            }
            if (temp->parent != root)
            {
                if (split(temp->parent) == false)
                    break;
            }
        }
    }

  
    Tree* insert(Tree* temp, Tree* ins)
    {
        if (root == NULL)
        {
            ins->count = 1;
            ins->parent = NULL;
            ins->left = NULL;
            ins->right = NULL;
            root = ins;
            return root;
        }
        if (ins->key < temp->key)                                      
        {
            if (temp->left)
                return insert(temp->left, ins);
            temp->left = ins;
            ins->parent = temp;
            ins->count = 1;
            rebalance(ins);
            return ins;
        }
        if (ins->key > temp->key)                                       
        {
            if (temp->right)
                return insert(temp->right, ins);
            temp->right = ins;
            ins->parent = temp;
            ins->count = 1;
            rebalance(ins);
            return ins;
        }
        temp->count++;
        delete ins;
        return temp;
    }

    
    void print(Tree* temp)
    {
        if (!temp)
            return;
        print(temp->left);
        rational c1;
        c1.getData(stod(temp->keya), stod(temp->keyb));

        cout << "Value: "; c1.prnt(c1); cout  << "  Count:" << temp->count;       
        cout << "  Level: " << temp->level << endl;
        print(temp->right);
    }

   
    int countnode(Tree* temp)
    {
        if (!temp)
            return 0;
        int count = 1;
        count = count + countnode(temp->left);
        count = count + countnode(temp->right);
        return count;
    }
};


int main()
{
 
    AATree aa;
    int ch;
    string x;
    string y;
    ifstream f("AATreeElement.txt");
    if (f.is_open())
    {
        while (getline(f, x, '/') && getline(f, y, ' '))
        {
            aa.lookup(x, y);
        }
        f.close();
    }
    while (1)
    {
        cout << "\nAA Tree: " << endl;
        cout << "1.Show Tree" << endl;
        cout << "2.Total Tree Nodes" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Elemets of AA Tree" << endl;
           aa.print(root);
            break;
        case 2:
            cout << "Number of nodes" << endl;
            cout << aa.countnode(root) << endl;
            break;
        case 3:
            cout << "Exiting" << endl;
            exit(1);
            break;
        default:
            exit(1);
        }
    }
    return 0;
}
