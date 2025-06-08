// Copyright 2022 NNTU-CS
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elmnts) {
    if (elmnts.empty()) {
        root = nullptr;
        total_perms = 0;
        return;
    }
    root = std::make_shared<Node>('\0');
    build(root, elmnts);
    total_perms = fact(elmnts.size());
}

void PMTree::build(std::shared_ptr<Node> node, const std::vector<char>& rest) {
    if (rest.empty()) return;
    for (char v : rest) {
        auto kid = std::make_shared<Node>(v);
        node->kids.push_back(kid);
        std::vector<char> new_rest;
        for (char r : rest) {
            if (r != v) new_rest.push_back(r);
        }
        build(kid, new_rest);
    }
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> rslt;
    if (!root) return rslt;
    std::vector<char> crrnt;
    for (const auto& kid : root->kids) {
        collect(kid, crrnt, rslt);
    }
    return rslt;
}

void PMTree::collect(std::shared_ptr<Node> node, std::vector<char>& crrnt,
                     std::vector<std::vector<char>>& rslt) const {
    crrnt.push_back(node->val);
    if (node->kids.empty()) {
        rslt.push_back(crrnt);
    } else {
        for (const auto& kid : node->kids) {
            collect(kid, crrnt, rslt);
        }
    }
    crrnt.pop_back();
}

std::vector<char> PMTree::getPerm1(int num) const {
    if (num < 1 || num > total_perms) return {};
    std::vector<char> res;
    std::vector<char> crrnt;
    int cnt = 0;
    for (const auto& kid : root->kids) {
        if (findTraversal(kid, crrnt, cnt, num, res)) break;
    }
    return res;
}

bool PMTree::findTraversal(std::shared_ptr<Node> node, std::vector<char>& crrnt,
                    int& cnt, int target_num, std::vector<char>& res) const {
    crrnt.push_back(node->val);
    if (node->kids.empty()) {
        cnt++;
        if (cnt == target_num) {
            res = crrnt;
            crrnt.pop_back();
            return true;
        }
    } else {
        for (const auto& kid : node->kids) {
            if (findTraversal(kid, crrnt, cnt, target_num, res)) {
                crrnt.pop_back();
                return true;
            }
        }
    }
    crrnt.pop_back();
    return false;
}

std::vector<char> PMTree::getPerm2(int num) const {
    if (num < 1 || num > total_perms) return {};
    std::vector<char> res;
    int remaining = num - 1;
    std::shared_ptr<Node> node = root;
    while (!node->kids.empty()) {
        int f = fact(node->kids.size() - 1);
        int idx = remaining/f;
        if (idx >= node->kids.size()) return {};
        auto& kid = node->kids[idx];
        res.push_back(kid->val);
        remaining = remaining % f;
        node = kid;
    }
    return res;
}

int PMTree::fact(int n) const {
    if (n <= 1) return 1;
    return n * fact(n - 1);
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPerm1(num);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPerm2(num);
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}
