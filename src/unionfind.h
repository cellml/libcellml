/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <unordered_map>

template<typename T>
class UnionFind
{
public:
    T find(const T &x)
    {
        auto it = parent.find(x);
        if (it == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }

        if (it->second != x) {
            it->second = find(it->second); // Path compression
        }
        return it->second;
    }

    void unite(const T &a, const T &b)
    {
        T rootA = find(a);
        T rootB = find(b);

        if (rootA == rootB)
            return;

        // Union by rank
        if (rank[rootA] < rank[rootB]) {
            parent[rootA] = rootB;
        } else if (rank[rootA] > rank[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rank[rootA]++;
        }
    }

    bool connected(const T &a, const T &b)
    {
        return find(a) == find(b);
    }

private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;
};
