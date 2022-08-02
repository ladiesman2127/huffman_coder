#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <queue>
#define DEBUG

struct node
{
	std::string code;
	int frequency;
	char name;
	node* left;
	node* right;
	node(const int frequency, char name = ' ', node left = nullptr, node* right = nullptr)
	{
		this->frequency = frequency;
		this->name = name;
		this->left = left;
		this->right = right;
	}
};
node* tree = nullptr;
std::map<char, std::string> dictionary;

void search(node* cur_node, std::string code)
{
	node* prev = cur_node;
	if (cur_node == tree)
		code = "";
	if (cur_node->left == nullptr && cur_node->right == nullptr)
	{
		dictionary[cur_node->name] = code;
		if (prev->left == cur_node)
			prev->left = nullptr;
		else
			prev->right = nullptr;
		return;
	}
	if (cur_node->left != nullptr)
	{
		search(cur_node->left, code + "0");
	}
	if (cur_node->right != nullptr)
	{
		search(cur_node->right, code + "1");
	}
}

std::string huffman_code(std::string s)
{
	if(s.size() == 1)
	{
		std::cout << "1" << " " << "1\n";
		std::cout << s << ": " << "0" << '\n';
		return "0";
	}

	std::vector<node> nodes;
	for (int i = 0; i < s.size(); i++)
	{
		bool found = false;
		for (int j = 0; j < nodes.size(); j++)
		{
			if (nodes[j].name == s[i])
			{
				nodes[j].frequency++;
				found = true;
				break;
			}
		}
		if (!found)
		{
			nodes.emplace_back(1, s[i]);
		}
	}
	if(nodes.size() == 1)
	{
		std::string result;
		int i = 0;
		while(i < s.size())
		{
			result += "0";
			i++;
		}
		std::cout << "1" << " " << result.size() << "\n";
		std::cout << s[0] << ": " << "0\n";
		return result;
	}

	std::deque<node*> pq;
	for (auto& node : nodes)
	{
		pq.push_back(&node);
	}
	
	while (!pq.empty())
	{
		std::sort(pq.begin(), pq.end(), [](const node* a, const node* b) { return a->frequency < b->frequency; });
		node* el1 = pq.front();
		pq.pop_front();
		node* el2 = pq.front();
		pq.pop_front();
		if (pq.empty())
		{
			tree = new node(el1->frequency + el2->frequency, ' ', el1, el2);
			break;
		}
		pq.push_front(new node(el1->frequency + el2->frequency, ' ', el1, el2));
	}

	node* cur_node = tree;
	

	search(tree, "");

	std::string result;

	for(const auto& ch : s)
	{
		result += dictionary[ch];
	}
	std::cout << dictionary.size() << ' ' << result.size() << '\n';

	search(cur_node, result);

	for(const auto& ch : dictionary)
	{
		std::cout << ch.first << ": " << ch.second << '\n';

	}

	return result; // TODO
}




int main()
{
	std::string s = "a"; 
	std::cin >> s; // UNCOMMENT
	std::cout << huffman_code(s);
	return 0;
}*
