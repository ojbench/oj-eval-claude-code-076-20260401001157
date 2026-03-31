#include <iostream>
#include <string>
#include "MyList.h"

using namespace std;

int main() {
    int n;
    cin >> n;

    MyList<int> lists[105];  // Support multiple lists

    for (int i = 0; i < n; i++) {
        string operation;
        int list_id;
        cin >> operation >> list_id;

        if (operation == "push_back") {
            int value;
            cin >> value;
            lists[list_id].push_back(value);
        } else if (operation == "pop_back") {
            lists[list_id].pop_back();
        } else if (operation == "push_front") {
            int value;
            cin >> value;
            lists[list_id].push_front(value);
        } else if (operation == "pop_front") {
            lists[list_id].pop_front();
        } else if (operation == "front") {
            cout << lists[list_id].front() << endl;
        } else if (operation == "back") {
            cout << lists[list_id].back() << endl;
        } else if (operation == "insert") {
            int index, value;
            cin >> index >> value;
            lists[list_id].insert(index, value);
        } else if (operation == "erase") {
            int index;
            cin >> index;
            lists[list_id].erase(index);
        } else if (operation == "size") {
            cout << lists[list_id].size() << endl;
        } else if (operation == "empty") {
            cout << (lists[list_id].empty() ? 1 : 0) << endl;
        } else if (operation == "clear") {
            lists[list_id].clear();
        } else if (operation == "link") {
            int other_list_id;
            cin >> other_list_id;
            lists[list_id].link(lists[other_list_id]);
        } else if (operation == "cut") {
            int index;
            cin >> index;
            lists[100] = lists[list_id].cut(index);  // Temporary storage
        } else if (operation == "print") {
            MyList<int> temp = lists[list_id];
            while (!temp.empty()) {
                cout << temp.front();
                temp.pop_front();
                if (!temp.empty()) cout << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
