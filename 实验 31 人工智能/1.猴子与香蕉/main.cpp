#include <iostream>
using namespace std;

char monkey[3] = { 'a','2','m'};   // 在 a, 在 1 楼
char box[3] = { 'a','1','x'};
char banana[3] = { 'b','3','B'};

bool climbUp(char mk[3]) {
    cout << "Monkey tried climbing up,";
    if (mk[0] == box[0] && mk[1] == box[1]) {
        cout << "it did climb up.\n";
        mk[1]++;
        return 1;
    }
    return 0;
}

bool climbOff(char mk[3]) {
    cout << "Monkey tried climbing down,";
    if (mk[0] == box[0] && mk[1] == box[1] + 1) {
        cout << "it did climb down.\n";
        mk[1]--;
        return 1;
    }
    return 0;
}

void grab(char mk[3], char obj[3]) { // 猴子拿起物品
    cout << "Monkey tried grabbing " << (obj[3] == 'm' ? "monkey" : (obj[3] == 'x' ? "box" : "banana")) << ",";
    if (mk[0] == obj[0] && mk[1] == obj[1])
    {
        cout << "it did grab "<< (obj[3] == 'm' ? "monkey" : (obj[3] == 'x' ? "box" : "banana"))<<".\n";
        obj[0] = 'm'; // 物品在猴子手上
    }
}

void drop(char mk[3], char obj[3]) {
    cout << "Monkey tried dropping "<< (obj[3] == 'm' ? "monkey" : (obj[3] == 'x' ? "box" : "banana")) << ", ";;
    if (obj[0] == 'm')
    {
        cout << "it did drop " << (obj[3] == 'm' ? "monkey" : (obj[3] == 'x' ? "box" : "banana")) << ".\n";
        obj[0] = mk[0]; // 物品在猴子的脚下放下
    }
}

string approach(char mk[3], char obj[3]) { // 尝试接近物品
    cout << "Monkey approching "<< (obj[3] == 'm' ? "monkey" : (obj[3] == 'x' ? "box" : (obj[3] == 'G' ? "ground" : "banana")))<<", ";
    if (mk[1] > obj[1]) // y 轴接近, 高于物品
        climbOff(mk);
    if (mk[0] != obj[0]) // x 轴接近
    {
        if (mk[1] == '1')
            mk[0] = obj[0];
        else
        {
            cout << "monkey can't move x-axis on second floor. Monkey is tring to get to first floor.\n";
            char ground[3] = { mk[1],'0','G'};
            approach(mk, ground);
            return "closer";
        }
    }
    if (mk[1] < obj[1]) { // y 轴接近, 低于物品
        if (!climbUp(mk))
        {
            cout << (obj[3] == 'm' ? "monkey" : (obj[3] == 'x' ? "box" : "banana"))<<" is too high.\n";
            return "too high";
        }
    }
    cout << "Monkey got closer to " << (obj[3] == 'm' ? "monkey" : (obj[3] == 'x' ? "box" : "banana")) << ".\n";
    return "closer";
}

int main() {
    string monkeyThought; // 猴子思考
    int tried = 0;
    do {
        monkeyThought = approach(monkey, banana);
        if (monkeyThought == "too high") { // 香蕉太高，垫
            approach(monkey, box);
            grab(monkey, box);
            approach(monkey, banana);
            drop(monkey, box);
        } else if (monkeyThought == "closer") 
            grab(monkey, banana);
        if (tried++ == 20)
        {
            cout << "\nMonkey tried it best and fail getting banana.";
            return 0;
        }
    } while (banana[0] != 'm'); // 循环直到香蕉在猴子手上
    cout << "Monkey got banana.";
}