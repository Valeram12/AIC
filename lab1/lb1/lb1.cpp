#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>

using namespace std;


typedef long long int long_int;
const int max_int = 1000000001; 

 
inline int myHash(long_int a_prime, long_int b_prime, int p_prime, int table_size, int key)
{
    return (((a_prime * key + b_prime) % p_prime) % table_size);
}


class h1
{
    vector<int> cells;
    int size; 
    long_int hash_a;
    long_int hash_b;
    int prime;

public:
    h1() {}
    void Build()
    {
        prime = 17;
        hash_a = std::rand() % prime;
        hash_b = 1 + std::rand() % (prime - 1);
    }

   
    void Construct(list<int>& input)
    {
        if (input.empty())
        {
            size = 0;
            return;
        }

        size = input.size() * input.size();
        bool flag = true;

      
        while (flag)
        {
            cells.assign(size, max_int);
            Build();
            list<int>::iterator e1 = input.begin();
            while (e1 != input.end() && flag)
            {
                int hashKey = myHash(hash_a, hash_b, prime, size, *e1);
                if (hashKey < 0)
                    hashKey = -hashKey;

                
                if (cells[hashKey] != max_int)
                {
                    flag = false;
                    break;
                }
                cells[hashKey] = *e1;
                ++e1;
            }

            if (!flag)
                flag = true;
            else
                flag = false;
        }
    }

    bool Contains(int e1)
    {
        if (size == 0)
            return false;
        int hashKey = myHash(hash_a, hash_b, prime, size, e1);
        if (hashKey < 0)
            hashKey = -hashKey;
        if (cells[hashKey] == e1)
            return true;
        return false;
    }
};


class h2
{
    int tSize;
    long_int hashFA;
    long_int hashFB;
    int primeN;
    vector<list<int> > _elementsInCells;
    vector<h1> _buckets;

public:
    h2()
    {
        primeN = 100013; 
        hashFA = std::rand() % primeN;
        hashFB = 1 + std::rand() % (primeN - 1);
    }

    void TSize(int size)
    {
        tSize = size;
        _buckets.resize(size);
    }

    void Build(const vector<int>& numbers)
    {
        tSize = numbers.size();
        _buckets.resize(numbers.size());
        _elementsInCells.resize(numbers.size());
        for (int i = 0; i < numbers.size(); ++i)
        {
            int hashKey = myHash(hashFA, hashFB, primeN, tSize, numbers[i]);
            if (hashKey < 0)
                hashKey = -hashKey;
            _elementsInCells[hashKey].push_back(numbers[i]);
        }
        for (int i = 0; i < numbers.size(); ++i)
        {
            _buckets[i].Construct(_elementsInCells[i]);
        }
    }

    bool Contains(int number)
    {
        int hashKey = myHash(hashFA, hashFB, primeN, tSize, number);
        if (hashKey < 0)
            hashKey = -hashKey;
        return _buckets[hashKey].Contains(number);
    }

};

int main()
{
    int n;
    cout << "Enter number of Elements: ";
    cin>> n;

    h2 H;
    vector<int> FirstV;
    H.TSize(n);
    

    for (int i = 0; i < n; ++i)
    {
        int e;
        cin>>e;

        FirstV.push_back(e);
    }

    H.Build(FirstV);
    int n1;
    cout << "Enter number of element for search";
    cin>>n1;
    for (int i = 0; i < n1; ++i)
    {
        int e1;
        cout << "Enter element for search";
        cin>>e1;
        if (H.Contains(e1))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }


    return 0;
}