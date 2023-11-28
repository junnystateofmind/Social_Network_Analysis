#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <sstream>

using namespace std;

class Node {
private:
    vector<shared_ptr<Node>> following;
    vector<shared_ptr<Node>> follower;
    int id;
    float influence;
    float temp_influence;

public:
    Node(int id) : id(id), influence(1.0), temp_influence(0.0) {}

    void add_following(shared_ptr<Node> node) {
        following.push_back(node);
    }

    void add_follower(shared_ptr<Node> node) {
        follower.push_back(node);
    }
    vector<shared_ptr<Node>> get_following() {
        return following;
    }

    vector<shared_ptr<Node>> get_follower() {
        return follower;
    }

    int get_id() {
        return id;
    }

    float get_influence() {
        return influence;
    }

    void ready_influence() {
        // 영향력을 1.0 증가시킨다.
        this->influence += 1.0;
    }

    void flow_influence(float flow) { // 영향력을 흘려준다.
        this->temp_influence += flow;
    }

    void reload_influence() { // 영향력을 갱신한다.
        this->influence += this->temp_influence;
        this->temp_influence = 0.0;
    }

    void flow_influence_to_following() {
        if (this->get_influence() >= 0.0) { // 영향력이 0.0 이상이면
            for (auto& node : following) {
                node->flow_influence(this->get_influence() / (following.size())); // 가진 영향력의 절반을 나눠준다.
            }
        }
        this->influence -= this->get_influence() / 2; // 나눠준 영향력만큼 영향력을 빼준다.
    }
};

class Network {
private:
    unordered_map<int, shared_ptr<Node>> nodes_map;
    vector<shared_ptr<Node>> nodes;

public:
    Network() {}

    void add_node(int id) {
        if (nodes_map.find(id) == nodes_map.end()) {
            auto new_node = make_shared<Node>(id);
            nodes_map[id] = new_node;
            nodes.push_back(new_node);
        }
    }

    void add_following(int id1, int id2) {
        add_node(id1); // id1 노드가 없으면 생성
        add_node(id2); // id2 노드가 없으면 생성

        shared_ptr<Node> node1 = nodes_map[id1];
        shared_ptr<Node> node2 = nodes_map[id2];

        if (node1 && node2) {
            node1->add_following(node2);
        }
    }

    void add_follower(int id1, int id2){
        // implement later
    }

    void flow_influence() {
        for (auto node : nodes) {
            node->ready_influence();
        }
        for (auto node : nodes) {
            node->flow_influence_to_following();
        }
        for (auto node : nodes) {
            node->reload_influence(); // 영향력을 갱신한다.
        }
    }

    vector<float> get_influence() {
        vector<float> influence;
        for (auto node : nodes) {
            influence.push_back(node->get_influence());
        }
        return influence;
    }

    vector<shared_ptr<Node>> get_nodes() {
        return nodes;
    }

    void print() {
        for (auto node : nodes) {
            cout << node->get_id() << " : ";
            for (auto following : node->get_following()) {
                cout << following->get_id() << " ";
            }
            cout << endl;
        }
    }
};

Network make_network(string file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "File cannot be opened: " << file_name << endl;
        exit(1);
    }
    string line;
    getline(file, line); // 헤더 읽기
    Network network;
    while (getline(file, line)) {
        stringstream ss(line);
        string from, to;
        if (!getline(ss, from, ',') || from.empty()) {
            cerr << "Invalid or missing 'from' node in line: " << line << endl;
            continue; // 현재 줄 건너뛰기
        }
        if (!getline(ss, to) || to.empty()) {
            cerr << "Invalid or missing 'to' node in line: " << line << endl;
            continue; // 현재 줄 건너뛰기
        }

        try {
            int from_id = stoi(from);
            int to_id = stoi(to);
            network.add_following(from_id, to_id);
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            continue;
        } catch (const std::out_of_range& e) {
            cerr << "Out of range: " << e.what() << endl;
            continue;
        }
    }
    return network;
}

void write_marked_csv(string file_name, vector<float> influence) {
    ofstream out_file(file_name);
    if (!out_file) {
        cerr << "File cannot be opened: tweeter_marked.csv" << endl;
        exit(1);
    }

    // 헤더 추가
    out_file << "Id, Influence" << endl;

    string line;
    for(int i = 0; i < influence.size(); i++) {
        // influence는 소수점 절사
        out_file << i+1 << ", " << (int)influence[i] << endl;
    }
    out_file.close();
}


int main() {
    Network network = make_network("tweeter.csv");
    // network.print();
    for (int i = 0; i < 50; i++) {
        network.flow_influence();
    }
    vector<float> influence = network.get_influence();
    // for (size_t i = 0; i < influence.size(); i++) {
    //     cout << i << " : " << influence[i] << endl;
    // }
    
    // influnece 총 합 출력
    float sum = 0.0;
    for (size_t i = 0; i < influence.size(); i++) {
        sum += influence[i];
    }
    cout << "sum : " << sum << endl;

    // influnece 를 csv 파일로 저장
    ofstream file("influence.csv");
    if (!file) {
        cerr << "File cannot be opened: influence.csv" << endl;
        exit(1);
    }
    file << "id,influence" << endl;
    for (size_t i = 0; i < influence.size(); i++) {
        file << i << "," << influence[i] << endl;
    }

    // gephi 를 이용하여 그래프 그리기위해 상위 100개 노드 marking해서 새로운 tweeter_marked.csv 파일 생성
    write_marked_csv("node_influence.csv", influence);
    return 0;
}
