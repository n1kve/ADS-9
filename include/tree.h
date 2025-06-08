// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>

class PMTree {
 public:
    struct Node {
        char val;
        std::vector<std::shared_ptr<Node>> kids;
        explicit Node(char v) : val(v) {}
    };
    explicit PMTree(const std::vector<char>& elmnts);
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPerm1(int num) const;
    std::vector<char> getPerm2(int num) const;

 private:
    std::shared_ptr<Node> root;
    size_t total_perms;
    void build(std::shared_ptr<Node> node, const std::vector<char>& rest);
    void collect(std::shared_ptr<Node> node, std::vector<char>& crrnt,
                 std::vector<std::vector<char>>& rslt) const;
    bool findTraversal(std::shared_ptr<Node> node, std::vector<char>& crrnt,
                       int& cnt, int target_num, std::vector<char>& res) const;
    bool findNavigation(std::shared_ptr<Node> node, std::vector<char>& crrnt,
                        int& remaining, std::vector<char>& res) const;
    int fact(int n) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
