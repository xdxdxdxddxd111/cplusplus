#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    int target = 3;
    auto found = find(vec.begin(), vec.end(), target);
    if (found != vec.end()) {
        cout << "найдено" << endl;
    } else {
        cout << "не найдено" << endl;
    }

    auto minIt = min_element(vec.begin(), vec.end());
    auto maxIt = max_element(vec.begin(), vec.end());
    cout << "минимум: " << *minIt << ", максимум: " << *maxIt << endl;

    int X = 2;
    int countX = count(vec.begin(), vec.end(), X);
    cout << "число " << X << " встречается " << countX << " раз(а)" << endl;

    reverse(vec.begin(), vec.end());
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    sort(vec.begin(), vec.end()); // по возрастанию
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; }); // по убыванию
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    int removeX = 3;
    vec.erase(remove(vec.begin(), vec.end(), removeX), vec.end());
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    vec.erase(remove_if(vec.begin(), vec.end(), [](int x) { return x > 10; }), vec.end());
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> squares;
    transform(vec.begin(), vec.end(), back_inserter(squares), [](int x) { return x * x; });
    for (int num : squares) {
        cout << num << " ";
    }
    cout << endl;

    map<int, int> freq;
    for (int num : vec) {
        freq[num]++;
    }

    int mostFrequent = 0, maxCount = 0;
    for (const auto& pair : freq) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequent = pair.first;
        }
    }
    cout << "самое частое число: " << mostFrequent << endl;

    int key = 5;
    if (freq.find(key) != freq.end()) {
        cout << "ключ найден" << endl;
    } else {
        cout << "ключ не найден" << endl;
    }

    string text = "apple banana apple orange banana";
    set<string> uniqueWords;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        uniqueWords.insert(word);
    }
    for (const string& w : uniqueWords) {
        cout << w << " ";
    }
    cout << endl;

    map<string, int> wordCount;
    stringstream ss2(text);
    while (ss2 >> word) {
        wordCount[word]++;
    }
    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }

    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    cout << "верхний элемент: " << st.top() << endl;
    st.pop();
    cout << "новый верхний: " << st.top() << endl;

    queue<string> tasks;
    tasks.push("задача 1");
    tasks.push("задача 2");
    tasks.push("задача 3");
    while (!tasks.empty()) {
        cout << "выполняется: " << tasks.front() << endl;
        tasks.pop();
    }

    priority_queue<int> pq;
    pq.push(5);
    pq.push(1);
    pq.push(9);
    pq.push(3);
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    vector<int> nums = {10, 5, 8, 20, 3, 15, 12};
    partial_sort(nums.begin(), nums.begin() + 3, nums.end(), greater<int>());
    cout << "топ‑3: ";
    for (int i = 0; i < 3; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;

    vector<int> numbers = {-5, 3, -1, 7, -2, 9, 0};
    numbers.erase(remove_if(numbers.begin(), numbers.end(), [](int x) { return x < 0; }), numbers.end());
    sort(numbers.begin(), numbers.end());
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
```
