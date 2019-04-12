#include "help_library.h"

bool CustomCompare:: operator() (const TreeNode* first_node, const TreeNode* second_node)
{
    return first_node->frequency > second_node->frequency;
}


/*int get_index_of(vector<TreeNode*> myvector, char a) {

    vector<TreeNode*>::iterator ptr;

    for (ptr = myvector.begin(); ptr < myvector.end(); ptr++)
        if((*ptr)->letter == a)
           return distance(myvector.begin(), ptr);

    return -1;
}*/


pr_queue create_queue(const string &text) {

	unordered_map<char, TreeNode*> umap;

    //vector<TreeNode*> vec;

    for(unsigned int i=0;i<text.size();i++) {

        /*int index = get_index_of(vec, text[i]);

        if(index == -1) {      // first time
            TreeNode *temp_node = new TreeNode();
            temp_node->frequency = 1;
            temp_node->letter = text[i];
            vec.push_back(temp_node);
        }
        else	//not first time
            vec[index]->frequency++;*/
			
		char current_char = text[i];
		
		if(umap.count(current_char)>0)
			umap[current_char]->frequency++;
		else {
            TreeNode *temp_node = new TreeNode();
            temp_node->frequency = 1;
            temp_node->letter = current_char;
            umap[current_char] = temp_node;
		}

    }

    pr_queue pq;

    //for(unsigned int i=0;i<vec.size();i++)
    //    pq.push(vec[i]);
    for (auto x : umap)
		pq.push(x.second);

	//encode_help_string += x.second + '\n' + x.first + '\n';


    return pq;
}


string read_file(const string& file_name) {

    string text;
    ifstream input_stream(file_name, ios::in | ios::binary);

	if(!input_stream)
		return "";

    do {
        int c= input_stream.get();
        if (c==EOF) break;
        text += (char)c;
    } while (!input_stream.fail());

    return text;
}

void save_text_to_file(const string& text, const string& file_name) {

    ofstream OutFile;
    OutFile.open(file_name, ios::out | ios::binary);

    OutFile << text;
    OutFile.close();
}

string int_to_byte(unsigned int num) {

    string final_string = "00000000";

    for(int i=7;i>=0;i--) {
        final_string[i] = (num%2) + '0';
        num = num >> 1;
    }

    return final_string;
}

void delete_tree_nodes(TreeNode *root) {

    //delete
    if(root->left!=nullptr)
        delete_tree_nodes(root->left);

    //right
    if(root->right!=nullptr)
        delete_tree_nodes(root->right);

    //root visit
    root = nullptr;
    delete root;
}
