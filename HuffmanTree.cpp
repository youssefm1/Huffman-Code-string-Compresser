#include "HuffmanTree.hpp"


HuffmanTree::HuffmanTree(){}

string HuffmanTree::compress(const string inputStr){
    map<char, int> freq;

    for(int a=0; a<inputStr.size(); a++){
        if(freq.find(inputStr[a]) != freq.end()){
            freq[inputStr[a]]++;
        } else{
            freq[inputStr[a]] = 1;
        }
    }

    HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue;

    map<char, int>::iterator freqItr = freq.begin();

    while(freqItr != freq.end()){
        priorityQueue.insert(new HuffmanNode(freqItr->first, freqItr->second));
        freqItr++;
    }

    while(priorityQueue.size() > 1){
        HuffmanNode* left = priorityQueue.min();
        priorityQueue.removeMin();
        
        HuffmanNode* right = priorityQueue.min();
        priorityQueue.removeMin();

        int rootFrequency = left->getFrequency() + right->getFrequency();
        HuffmanNode* root = new HuffmanNode('\0', rootFrequency, nullptr, left, right);

        left->parent = root;
        right->parent = root;

        priorityQueue.insert(root);
    }

    rootNode = priorityQueue.min();
    priorityQueue.removeMin();

    freqItr = freq.begin();

    map<char, string> codes;

    string code = "";

    postOrderCompress(code, &codes, rootNode);

    string finalCode = "";

    for(int a=0; a<inputStr.size(); a++){
        finalCode += codes[inputStr[a]];
    }

    return finalCode;
}

void HuffmanTree::postOrderCompress(string code, map<char, string>* codes, HuffmanNode* node){
    if(node->right != nullptr){
        postOrderCompress(code + "1", codes, node->right);
    }

    if(node->left != nullptr){
        postOrderCompress(code + "0", codes, node->left);
    }

    if(node->isLeaf()){
        codes[0][node->getCharacter()] = code;
    }
}

string HuffmanTree::serializeTree() {
    string code;
    HuffmanNode *temp = rootNode;
    postOrderSerializeTree(&code, temp);

    return code;
}

void HuffmanTree::postOrderSerializeTree(string* code, HuffmanNode* node){
    if(node == nullptr){
        return;
    }

    postOrderSerializeTree(code, node->left);

    postOrderSerializeTree(code, node->right);

    if(node->isLeaf()){
        string c(1, node->getCharacter());
        *(code) += "L";
        *(code) = *(code) + c;
    }
    if(node->isBranch()){
        *(code) += "B";
    }
}

string HuffmanTree::decompress(const string inputCode, const string serializedTree){
    stack<HuffmanNode*> s;
    
    vector<char> alpha;

    for(int a=0; a<serializedTree.size(); a++){
        if(serializedTree[a] == 'L'){
            a++;
            HuffmanNode* node = new HuffmanNode(serializedTree[a], 0);
            alpha.push_back(serializedTree[a]);
            s.push(node);
        }else if(serializedTree[a] == 'B'){
            HuffmanNode* left = s.top();
            s.pop();

            HuffmanNode* right = s.top();
            s.pop();

            HuffmanNode* branch = new HuffmanNode('\0', 0, nullptr, left, right);
            left->parent = branch;
            right->parent = branch;

            s.push(branch);
        }
    }
    
    HuffmanNode* root = s.top();
    s.pop();

    string code;
    map<char, string> codes;

    postOrderCompress(code, &codes, root);

    for(int a=0; a<alpha.size(); a++){
        code = codes[alpha[a]];
        for(int b=0; b<code.size(); b++){
            if(code[b] == '1'){
                code[b] = '0';
            }else{
                code[b] = '1';
            }
        }
        codes[alpha[a]] = code;
    }

    code = "\0";

    map<char, string>::iterator itr = codes.begin();
    string converted;

    for(int a=0; a<inputCode.size(); a++){
        code += inputCode[a];
        while(itr != codes.end()){
            if(code == itr->second){
                converted += itr->first;
                code = "\0";
                break;
            }
            itr++;
        }
        itr = codes.begin();
    }

    return converted;
}

