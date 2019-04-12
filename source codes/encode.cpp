#include <iostream>
#include <unordered_map>    //hashtable
#include "help_library.h"

using namespace std;



//hashtable with char key and string content
unordered_map<char, string> umap;
string current_encoding;


TreeNode* create_huffman_tree(pr_queue pq) {

    while(pq.size() > 1) {
        TreeNode *n1 = pq.top();
        pq.pop();
        TreeNode *n2 = pq.top();
        pq.pop();

        TreeNode *temp_node = new TreeNode();
        temp_node->left = n1;
        temp_node->right = n2;
        temp_node->frequency = n1->frequency + n2->frequency;

        pq.push(temp_node);
    }

    return pq.top();
}

//fill hash_table with <char, string> pairs --- post-order traversal
void get_encoding_pairs(TreeNode *root) {

    //left
    if(root->left!=nullptr) {
        current_encoding.push_back('0');
        get_encoding_pairs(root->left);
    }

    //right
    if(root->right!=nullptr) {
        current_encoding.push_back('1');
        get_encoding_pairs(root->right);
    }

    // visit root if it's a leaf
    if(root->left==nullptr && root->right==nullptr)
        umap[root->letter] = current_encoding;

    current_encoding.pop_back();
}

//final encode (bits->bytes=chars)
string encode_bits(const string &bits) {

    string final_string;

    unsigned int sum = 0;   // unsigned to support extended ascii
    for(unsigned int i=0;i<bits.size();i++) {
        sum = sum << 1;
        sum += (bits[i]  - '0');

        if((i+1)%8==0) {
            final_string += (unsigned char)sum;
            sum = 0;
        }
    }

    return final_string;
}

//prefix is the number of useful last bits and suffix 0s which are added to complete the final byte if necessary
string add_prefix_and_suffix(string bits) {

    int added_bits = bits.size()%8;
    bits = int_to_byte(added_bits) + bits;

    while(bits.size()%8 != 0)
        bits += '0';

    return bits;
}

string original_text_to_bits(const string& text) {
    string bits;

    for(unsigned int i=0;i<text.size();i++)
        bits += umap[text[i]];

    return bits;
}

string get_encode_help() {

    string encode_help_string;
    for (auto x : umap)
        encode_help_string += x.second + '\n' + x.first + '\n';

    return encode_help_string;
}


int main(int argc, char **argv) {

    if(argc < 4)
        return -1;

    string original_text = read_file(argv[1]);
    if(original_text == "")
        return -1;

    pr_queue pq = create_queue(original_text);
    TreeNode *root = create_huffman_tree(pq);
    get_encoding_pairs(root);

    //deallocate the tree space
    delete_tree_nodes(root);
    root = nullptr;

    string bits = original_text_to_bits(original_text);
	//cout << bits << endl;
    string normalized_bits = add_prefix_and_suffix(bits);
	//cout << normalized_bits << endl;

    string encoded_string = encode_bits(normalized_bits);
    save_text_to_file(encoded_string, argv[2]);

    string encode_help_string = get_encode_help();
    save_text_to_file(encode_help_string, argv[3]);

    return 0;
}
