#include <iostream>
#include <sstream>  //getline for string
#include "help_library.h"

using namespace std;


// construct the tree using the help file
TreeNode* file_to_tree(const string& my_string) {
    TreeNode *root = new TreeNode();
    TreeNode *curr = root;

    istringstream f(my_string);
    string encoding;
    string char_line;
    char character;

    while (std::getline(f, encoding) && std::getline(f, char_line)) {
        //new line case
        if(char_line=="")
        {
            std::getline(f, char_line);    // to jump
            char_line = "\n";
        }

        character = char_line[0];
        for(unsigned int i=0;i<encoding.size();i++) {
            if(encoding[i] == '0') {  // left child
                if(curr->left==nullptr) { // create child
                    TreeNode *left_node = new TreeNode();
                    curr->left = left_node;
                }
                //go left
                curr = curr->left;
            }
            else if(encoding[i] == '1') {  // right child
                if(curr->right==nullptr) { // create child
                    TreeNode *right_node = new TreeNode();
                    curr->right = right_node;
                }
                //go right
                curr = curr->right;
            }

            curr->letter = character;
        }
        curr = root;
    }

    return root;
}

string decode_bits(const string& bits, TreeNode *root) {

    string text = "";
    TreeNode *curr = root;

    for(unsigned int i=0;i<bits.size();i++) {
        if(bits[i] == '0' && curr->left!=nullptr)	// left child
            curr = curr->left;
        else if(bits[i] == '1' && curr->right!=nullptr)	// right child
            curr = curr->right;
		
        if(curr->left==nullptr && curr->right==nullptr) {  // leaf
            text.push_back(curr->letter);
            curr = root;
        }
    }

    return text;
}

string encoded_text_to_bits(const string& str) {

    string bits = "";

    for(unsigned int i=0;i<str.size();i++) {
        unsigned int x = str[i];
        bits += int_to_byte(x);
    }
    return bits;
}

int byte_to_int(const string& byte) {

    int sum = 0;
    for(unsigned int i=0;i<8;i++) {
        sum = sum << 1;
        sum += (byte[i]  - '0');
    }

    return sum;
}

//prefix is the number of useful last bits and suffix 0s which are added to complete the final byte if necessary
string remove_prefix_and_suffix(string bits) {

    string prefix_byte = bits.substr(0,8);
    int suffix_used = byte_to_int(prefix_byte);

    while(suffix_used%8!=0) {
        bits.pop_back();
        suffix_used++;
    }

    return bits.substr(8);
}


int main(int argc, char **argv) {
    if(argc < 4)
        return -1;

    string encoded_text = read_file(argv[1]);
    if(encoded_text == "")
        return -1;

    string bits = encoded_text_to_bits(encoded_text);
    string normalized_bits = remove_prefix_and_suffix(bits);

    string help_text = read_file(argv[2]);
    if(help_text == "")
        return -1;

    TreeNode *root = file_to_tree(help_text);

    //find the original encoded text using the huffman tree
    string original_text = decode_bits(normalized_bits, root);

    //save original text
    save_text_to_file(original_text, argv[3]);

    //deallocate the tree space
    delete_tree_nodes(root);
    root = nullptr;

    return 0;
}
