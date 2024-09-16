#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Robot {
private:
    int x, y;
    int time;
    bool canPassWall;
    int speed;

public:
    Robot() : x(0), y(0), time(0), canPassWall(false), speed(1) {}

    void setPosition(int startX, int startY) {
        x = startX;
        y = startY;
    }

    void move(char direction, vector<vector<char>>& map) {
        int newX = x, newY = y;
        switch (direction) {
            case 'U': newY--; break;
            case 'D': newY++; break;
            case 'L': newX--; break;
            case 'R': newX++; break;
        }

        if (newX >= 0 && newX < map[0].size() && newY >= 0 && newY < map.size()) {
            if (map[newY][newX] != 'x' || canPassWall) {
                x = newX;
                y = newY;
                time += 2 / speed;
                processCell(map[y][x]);
            } else {
                cout << "Robot nabrak, silahkan diperbaiki" << endl;
            }
        }
    }

    void processCell(char cell) {
        switch (cell) {
            case 'M':
                cout << "Bertemu dengan mekanik, siap membasmi rintangan" << endl;
                canPassWall = true;
                break;
            case 'E':
                cout << "Bertemu dengan electrical, kecepatan roda naik menjadi 200%" << endl;
                speed = 2;
                break;
            case 'P':
                cout << "Hi Programmer" << endl;
                break;
            case 'O':
                cout << "Bertemu dengan official, diajak ngonten bareng" << endl;
                time *= 2;
                break;
            case 'F':
                cout << "Robot berhasil mencapai tujuan" << endl;
                break;
        }
    }

    bool isAtGoal(const vector<vector<char>>& map) const {
        return map[y][x] == 'F';
    }

    int getTime() const { return time; }
};

int main() {
    int M, N;
    cin >> M >> N;

    vector<vector<char>> map(M, vector<char>(N));
    Robot robot;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'S') {
                robot.setPosition(j, i);
            }
        }
    }

    int P;
    cin >> P;

    cin.ignore(); // ingore newline character

    string movements;
    // cin >> movements;
    // menggunakan get line 
    getline(cin, movements);

    // Debugging: Menampilkan string movements sebelum dihapus spasinya
    cout << "Input string sebelum dihapus spasi: '" << movements << "'" << endl;

    // Menghapus semua spasi dari string movements
    movements.erase(remove(movements.begin(), movements.end(), ' '), movements.end());

    // Debugging: Menampilkan string movements setelah dihapus spasinya
    cout << "Input string setelah dihapus spasi: '" << movements << "'" << endl;

    for (char move : movements) {
        robot.move(move, map);
        if (robot.isAtGoal(map)) break;
    }

    if (!robot.isAtGoal(map)) {
        cout << "Robot gagal dalam mencapai tujuan :(" << endl;
    }

    cout << "Robot telah berjalan selama " << robot.getTime() << " menit" << endl;

    return 0;
}