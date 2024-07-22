// Segment Tree for range query with single point update.
#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    vector<int> tree;
    vector<int> array;
    int n;

private:
    void buildTree(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = array[start];
            return;
        }
        int mid = (start + end) / 2;
        buildTree(2 * node, start, mid);
        buildTree(2 * node + 1, mid + 1, end);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
    void updateTree(int node, int start, int end, int index, int value)
    {
        if (start == end)
        {
            array[index] = value;
            tree[node] = value;
            return;
        }
        int mid = (start + end) / 2;
        if (index <= mid)
            updateTree(2 * node, start, mid, index, value);
        else
            updateTree(2 * node + 1, mid + 1, end, index, value);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
    int queryTree(int node, int start, int end, int left, int right)
    {
        if (left > end || right < start)
            return INT_MIN;
        if (left <= start && end <= right)
            return tree[node];
        int mid = (start + end) / 2;
        int leftMax = queryTree(2 * node, start, mid, left, right);
        int rightMax = queryTree(2 * node + 1, mid + 1, end, left, right);
        return max(leftMax, rightMax);
    }

public:
    SegmentTree(vector<int> &arr) : array(arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        buildTree(1, 0, n - 1);
    }

    void update(int index, int value)
    {
        updateTree(1, 0, n - 1, index, value);
    }

    int query(int left, int right)
    {
        return queryTree(1, 0, n - 1, left, right);
    }
};

int main()
{
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(arr);

    cout << "Max in range [1, 3]: " << segTree.query(1, 3) << endl;

    segTree.update(2, 6);
    cout << "Max in range [1, 3] after update: " << segTree.query(1, 3) << endl;

    return 0;
}

// Example Question Codeforces Edu section range sum with point updates

#include <bits/stdc++.h>
using namespace std;
#define ll long long

class SegmentTree
{
    vector<ll> tree;
    vector<ll> array;
    int n;

private:
    void buildTree(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = array[start];
            return;
        }
        int mid = (start + end) / 2;
        buildTree(2 * node, start, mid);
        buildTree(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void updateTree(int node, int start, int end, int index, ll value)
    {
        if (start == end)
        {
            array[index] = value;
            tree[node] = value;
            return;
        }
        int mid = (start + end) / 2;
        if (index <= mid)
            updateTree(2 * node, start, mid, index, value);
        else
            updateTree(2 * node + 1, mid + 1, end, index, value);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    ll queryTree(int node, int start, int end, int left, int right)
    {
        if (left > end || right < start)
            return 0;
        if (left <= start && end <= right)
            return tree[node];
        int mid = (start + end) / 2;
        ll leftSum = queryTree(2 * node, start, mid, left, right);
        ll rightSum = queryTree(2 * node + 1, mid + 1, end, left, right);
        return leftSum + rightSum;
    }

public:
    SegmentTree(vector<ll> &arr) : array(arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        buildTree(1, 0, n - 1);
    }

    void update(int index, ll value)
    {
        updateTree(1, 0, n - 1, index, value);
    }

    ll query(int left, int right)
    {
        return queryTree(1, 0, n - 1, left, right);
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    SegmentTree segTree(arr);

    for (int i = 0; i < m; i++)
    {
        int a;
        cin >> a;
        if (a == 1)
        {
            int b;
            ll c;
            cin >> b >> c;
            segTree.update(b, c);
        }
        else
        {
            int b, c;
            cin >> b >> c;
            cout << segTree.query(b, c - 1) << "\n";
        }
    }
    return 0;
}
