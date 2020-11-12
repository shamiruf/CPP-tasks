#include "trie.hpp"

#include <cassert>

#include <queue>
#include <iostream>
#include <stack>


trie::trie() {
    m_root = new trie_node;
    m_size = 0;
}

trie::trie(const std::vector<std::string>& strings) {
    m_root = new trie_node;
    m_size = 0;
    for (const auto & string : strings) {
        insert(string);
    }
}

trie &trie::operator=(const trie &rhs) {
    if (this->m_root == rhs.m_root)
        return *this;
    return *this;
}

trie::trie(const trie &rhs) {
    std::cout<<'h';
}

trie::trie(trie &&rhs) {
    m_root = rhs.m_root;
    rhs.m_root = nullptr;
}

trie &trie::operator=(trie &&rhs) {
    std::vector<trie_node *> nodes;
    std::stack<trie_node *> stack;
    // add the first elem
    stack.push(m_root);

    while (!stack.empty()) {
        // get the first elem of array and delete it
        trie_node* curr = stack.top(); stack.pop();

//        if (!curr) continue;
        for (trie_node* child : curr->children) {
            if (child){
                // add next node to array
                stack.push(child);
            }
        }

        nodes.push_back(curr);
    }
    for (auto node : nodes) {
        //free the memory
        delete node;
    }

    m_root = rhs.m_root;
    rhs.m_root = nullptr;

    m_size = rhs.m_size;
    rhs.m_size = 0;
    return *this;
}

trie::~trie() {
    if (this->m_root != nullptr) {
        std::queue <trie_node* > trie;
        trie.push(m_root);

        while (!trie.empty()) {
            //check the children of root
            trie_node* parent_node = trie.front(); trie.pop();
            for (auto &child : parent_node->children) {
                if(child != nullptr){
                    //add children to queue to work with them later
                    trie.push(child);
                }
                else{
                    break;
                }
            }
            //delete parent because we get all his children
            delete parent_node;
        }
    }
    else {
        this->m_root = nullptr;
        this->m_size = 0;
    }
}

size_t new_length(const std::string& str) {
    size_t len = str.length();
    if (str.empty()) {
        len = len + 1;
    }
    return len;
}

bool trie::insert(const std::string& str) {

    if (contains(str)) {
        return false;
    }

    trie_node* curr = this->m_root;

    if (curr == nullptr) {
        return false;
    }

    size_t len = new_length(str);

    for (size_t i = 0; i < len; i++) {
        char  c = str[i];
        for (auto& child : curr->children) {
            if (child != nullptr) {
                if (child->payload == c) {
                    curr = child;
                    break;
                }
            }
            else if (child == nullptr) {
                auto* new_node = new trie_node;
                new_node->payload = c;
                new_node->parent = curr;
                child = new_node;
                curr = child;
                break;
            }
        }
    }

    m_size++;
    curr->is_terminal = true;

    return contains(str);
}


bool trie::contains(const std::string& str) const {
    // if trie is empty return false
    if (this->m_root == nullptr) {
        return false;
    }
    size_t len = new_length(str);

    trie_node* curr = this->m_root;

    for (size_t i = 0; i < len; i++) {
        char  c = str[i];
        for (auto* child : curr->children) {
            if (child == nullptr) {
                return false;
            }
            else {
                if (child->payload == c) {
                    curr = child;
                    break;
                }
            }
        }
    }
    return curr->is_terminal;
}

bool trie::empty() const {
    return m_size == 0;
}

bool trie::erase(const std::string& str) {
    if (this->m_root == nullptr)
        return false;

    if (!contains(str)) {
        return false;
    }

    size_t len = new_length(str);

    auto* curr = this->m_root;

    for (size_t i = 0; i < len; i++) {
        char  c = str[i];
        for (auto& child : curr->children) {
            if (child != nullptr) {
                if (child->payload == c) {
                    curr = child;
                    break;
                }

            }
        }
    }

    if (curr->is_terminal) {
        int i = 0;
        if ((bool) curr->children[i]) {
            curr->is_terminal = false;
        }
        else {
            delete(curr);
        }

        m_size--;
        if (m_size == 0) {
            trie_node* fff = this->m_root;
            for (auto& child : fff->children) {
                child = nullptr;
            }
        }
        return true;
    }
    return false;
}

size_t trie::size() const {
    return m_size;
}


trie::const_iterator::const_iterator(const trie_node *node) {
    this->current_node = node;
}

trie::const_iterator trie::begin() const {
    trie_node* curr = this->m_root;

    while(curr != nullptr) {
        if (curr->children[0] != nullptr) {
            curr = curr->children[0];
            if (curr->is_terminal) {
                break;
            }
        }
        if(curr->is_terminal) {
            break;
        }
    }

    return curr;
}

trie::const_iterator trie::end() const {
    return nullptr;
}

void trie::swap(trie& rhs) {

}

bool trie::operator==(const trie& rhs) const {
    return false;
}

bool trie::operator<(const trie& rhs) const {
    return false;
}

trie trie::operator&(trie const& rhs) const {
    auto trie_1 = trie();
    return trie_1;
}

trie trie::operator|(trie const& rhs) const {
    auto trie_1 = trie();
    return trie_1;
}

std::vector<std::string> trie::get_prefixes(const std::string &str) const {
    return std::vector<std::string>();
}

std::vector<std::string> trie::search_by_prefix(const std::string &prefix) const {
    return std::vector<std::string>();
}

const trie_node* next_node(const trie_node* curr, const char pld) {
    const char ch = '\0';
    for (const auto &child : curr->children) {
        if (child && child->payload > pld) {
            if(!child->is_terminal) {
                return next_node(child, ch);
            } else {
                return child;
            }
        } else {
            continue;
        }
    }

    if (!curr->parent) {
        return nullptr;
    } else {
        return next_node(curr->parent, curr->payload);
    }
}

trie::const_iterator &trie::const_iterator::operator++() {
    const char ch = '\0';
    this->current_node = next_node(this->current_node, ch);
    return *this;
}


trie::const_iterator trie::const_iterator::operator++(int z) {
    int i = 0;
    auto bar = z + 1;
    const char ch = '\0';

    while(i < bar) {
        this->current_node = next_node(this->current_node, ch);
        ++i;
    }

    return *this;
}


trie::const_iterator::reference trie::const_iterator::operator*() const {
    // change code for another bad same
    auto curr = this->current_node;
    std::string str = "";
    bool n = true;
    if(curr->payload) {
        while (n) {
            str = curr->payload + str;
            curr = curr->parent;
            if (!curr->payload) {
                n = false;
            }
        }
    }

    return str;
}

bool trie::const_iterator::operator==(const trie::const_iterator &rhs) const {
    return this->current_node == rhs.current_node;
}

bool trie::const_iterator::operator!=(const trie::const_iterator &rhs) const {
    return this->current_node != rhs.current_node;
}

bool operator!=(const trie& lhs, const trie& rhs) {
    return false;
}

bool operator<=(const trie& lhs, const trie& rhs) {
    return false;
}

bool operator>(const trie& lhs, const trie& rhs) {
    return false;
}

bool operator>=(const trie& lhs, const trie& rhs) {
    return false;
}

void swap(trie& lhs, trie& rhs) {

}

std::ostream& operator<<(std::ostream& out, trie const& trie) {
    return out;
}