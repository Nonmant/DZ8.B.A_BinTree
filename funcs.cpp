//https://contest.yandex.ru/contest/29403/problems/A/

#include "funcs.h"
#include <bits/stdc++.h>

struct BinThreeNode{
    BinThreeNode * left, *right;
    int value;
    explicit BinThreeNode(int value):
            value(value),
            left(nullptr),right(nullptr){};
    void print(std::ostream & output, int depth) const{
        if(left!= nullptr)
            left->print(output, depth+1);
        std::fill_n(std::ostream_iterator<char>(output),
                depth, '.');
        output<<value<<'\n';
        if(right!= nullptr)
            right->print(output, depth+1);
    }

    //! @return true if added, false if already exists
    bool add(int newVal){
        if(newVal == value)
            return false;
        if(newVal<value){
            if(left == nullptr){
                left = new BinThreeNode(newVal);
                return true;
            }
            return left->add(newVal);
        } else {
            if(right == nullptr){
                right = new BinThreeNode(newVal);
                return true;
            }
            return right->add(newVal);
        }
    }

    [[nodiscard]]
    bool search(int val) const{
        if(val == value)
            return true;
        if(val < value){
            if(left == nullptr)
                return false;
            return left->search(val);
        } else {
            if(right == nullptr)
                return false;
            return right->search(val);
        }
    }
};

struct BinThree{
    BinThreeNode * root;
    std::ostream & output;
public:
    explicit BinThree(std::ostream & output):
            output(output), root(nullptr){}
    void print(){
        if(root != nullptr)
            return root->print(output,0);
    }
    void add(int value){
        bool res;
        if(root == nullptr){
            root = new BinThreeNode(value);
            res = true;
        } else {
            res = root->add(value);
        }

        output<<(res ? "DONE" : "ALREADY")<<std::endl;
    }
    void search(int value){
        bool res;
        if(root == nullptr){
            res = false;
        } else {
            res = root->search(value);
        }

        output<<(res ? "YES" : "NO")<<std::endl;
    }
};

void parseFile(std::istream & input, std::ostream & output){
    BinThree three(output);

    std::string request;
    int val;
    while (input >> request){
        if(request == "ADD"){
            input >> val;
            three.add(val);
        } else if (request == "SEARCH"){
            input >> val;
            three.search(val);
        } else {
            three.print();
        }
    }
}
