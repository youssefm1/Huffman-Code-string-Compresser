#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H


#include <iostream>
#include <map>
#include <iterator>
#include <stack>
#include <vector>
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
using namespace std;


class HuffmanTree : public HuffmanTreeBase{
    public:
    HuffmanTree();
    string compress(const string inputStr);
    string serializeTree();
    string decompress(const string inputCode, const string serializedTree);

    private:
    HuffmanNode *rootNode;

    void postOrderCompress(string code, map<char, string>* codes, HuffmanNode* node);
    void postOrderSerializeTree(string *code, HuffmanNode* node);
};



#endif /* HUFFMANTREE_H */