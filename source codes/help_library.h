#ifndef HELP_LIBRARY_H_INCLUDED
#define HELP_LIBRARY_H_INCLUDED

#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>    //hashtable

using namespace std;

class TreeNode {
  public:
    TreeNode *right=nullptr, *left=nullptr;
    unsigned int frequency = 0;
    char letter = ' ';
};

struct CustomCompare {
    bool operator()(const TreeNode*, const TreeNode*);
};

int get_index_of(vector<TreeNode*>, char);

typedef priority_queue<TreeNode*, vector<TreeNode*>, CustomCompare> pr_queue;

pr_queue create_queue(const string&);

string read_file(const string&);

void save_text_to_file(const string&, const string&);

//used for the first byte in order to know the useful bits of the final byte
string int_to_byte(unsigned int);

void delete_tree_nodes(TreeNode*);


#endif // DATA_STRUCTURES_H_INCLUDED
