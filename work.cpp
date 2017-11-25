#include <iostream>
#include <stdio.h>
using namespace std;

struct Corner {
    int s1, s2, s3;
    Corner() {}
    Corner(int _s1, int _s2, int _s3) {
        s1 = _s1; s2 = _s2; s3 = _s3;
    }
};

struct Edge {
    int s1, s2;
    Edge() {}
    Edge(int _s1, int _s2) {
        s1 = _s1; s2 = _s2;
    } 
};

class mf {
public:

    void run() {
        C();
        F();
        O();
        P();
    }

private:

    Corner corner(int p) {
        // 1 上前左
        // 2 上后左
        // 3 上后右
        // 4 上前右
        // 5 下前左
        // 6 下后左
        // 7 下后右
        // 8 下前右
        int s1[8] = {0, 0, 0, 0, 1, 1, 1, 1};
        int s2[8] = {2, 3, 3, 2, 2, 3, 3, 2};
        int s3[8] = {4, 4, 5, 5, 4, 4, 5, 5};
        return Corner(s1[p-1], s2[p-1], s3[p-1]);
    }

    bool isCornerSame(Corner c, int s1, int s2, int s3) {
        if (face[c.s1] == s1 && face[c.s2] == s2 && face[c.s3] == s3)
            return true;
        else if (face[c.s1] == s1 && face[c.s2] == s3 && face[c.s3] == s2)
            return true;
        else if (face[c.s1] == s2 && face[c.s2] == s1 && face[c.s3] == s3)
            return true;
        else if (face[c.s1] == s2 && face[c.s2] == s3 && face[c.s3] == s1)
            return true;
        else if (face[c.s1] == s3 && face[c.s2] == s1 && face[c.s3] == s2)
            return true;
        else if (face[c.s1] == s3 && face[c.s2] == s2 && face[c.s3] == s1)
            return true;
        return false;
    }

    Edge edge(int p) {
        // 1 上前
        // 2 上左
        // 3 上后
        // 4 上右
        // 5 下前
        // 6 下左
        // 7 下后
        // 8 下右
        // 9 前左
        // 10 后左
        // 11 后右
        // 12 前右
        int s1[12] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 3, 3, 2};
        int s2[12] = {2, 4, 3, 5, 2, 4, 3, 5, 4, 4, 5, 5};
        return Edge(s1[p-1], s2[p-1]);
    }

    bool isEdgeSame(Edge e, int s1, int s2) {
        if (face[e.s1] == s1 && face[e.s2] == s2)
            return true;
        else if (face[e.s1] == s2 && face[e.s2] == s1)
            return true;
        return false;
    }

    void resetPlace() {
        //把白色中心方块转到下面
        if (face[0][4] == 1) {
            change('x', true);
            change('x', true);
        }
        else if (face[2][4] == 1) {
            change('x', false);
        }
        else if (face[3][4] == 1) {
            change('x', true);
        }
        else if (face[4][4] == 1) {
            change('z', false);
        }
        else if (face[5][4] == 1) {
            change('z', true);
        }

        //把蓝色中心方块转到前面
        if (face[3][4] == 2) {
            change('y', true);
            change('y', true);
        }
        else if (face[4][4] == 2) {
            change('y', false);
        }
        else if (face[5][4] == 2) {
            change('y', true);
        }
    }

    void adjust_C(int b, int f) {
        //块在底层，面朝底
        if (face[1][3] == b && face[4][7] == f) {
            changeCommand("L2U'F2");
        }
        else if (face[1][7] == b && face[3][7] == f) {
            changeCommand("B2U2F2");
        }
        else if (face[1][5] == b && face[5][7] == f) {
            changeCommand("R2UF2");
        }

        //块在底层，面不朝底
        if (face[1][1] == f && face[2][7] == b) {
            changeCommand("F'DR'D'");
        }
        else if (face[1][3] == f && face[4][7] == b) {
            changeCommand("L'F'");
        }
        else if (face[1][7] == f && face[3][7] == b) {
            changeCommand("BDRD'");
        }
        else if (face[1][5] == f && face[5][7] == b) {
            changeCommand("RF");
        }


        //块在顶层，面朝顶
        if (face[0][7] == b && face[2][1] == f) {
            changeCommand("F2");
        }
        else if (face[0][3] == b && face[4][1] == f) {
            changeCommand("U'F2");
        }
        else if (face[0][1] == b && face[3][1] == f) {
            changeCommand("U2F2");
        }
        else if (face[0][5] == b && face[5][1] == f) {
            changeCommand("UF2");
        }

        //块在顶层，面不朝顶
        if (face[0][7] == f && face[2][1] == b) {
            changeCommand("U'R'F");
        }
        else if (face[0][3] == f && face[4][1] == b) {
            changeCommand("LF'");
        }
        else if (face[0][1] == f && face[3][1] == b) {
            changeCommand("UR'F");
        }
        else if (face[0][5] == f && face[5][1] == b) {
            changeCommand("R'F");
        }

        //块在中间层
        if (face[2][3] == b && face[4][5] == f) {
            changeCommand("D'LD'");
        }
        else if (face[2][3] == f && face[4][5] == b) {
            changeCommand("F'");
        }

        else if (face[4][3] == b && face[3][5] == f) {
            changeCommand("D2BD2");
        }
        else if (face[4][3] == f && face[3][5] == b) {
            changeCommand("D'L2D");
        }

        else if (face[5][5] == b && face[3][3] == f) {
            changeCommand("D2B'D2");
        }
        else if (face[5][5] == f && face[3][3] == b) {
            changeCommand("DR2D'");
        }

        else if (face[2][5] == b && face[5][3] == f) {
            changeCommand("DR'D'");
        }
        else if (face[2][5] == f && face[5][3] == b) {
            changeCommand("F");
        }
    }

    void C () {
        resetPlace();
        adjust_C(1, 2);
        change('y', true);
        adjust_C(1, 5);
        change('y', true);
        adjust_C(1, 3);
        change('y', true);
        adjust_C(1, 4);
        change('y', true);
    }

    void adjust_F_corner(int d, int f, int r) {
        if (isCornerSame(1, d, f, r)) {
            changeCommand("U'");
        }
        else if (isCornerSame(2, d, f, r)) {
            changeCommand("U2");
        }
        else if (isCornerSame(3, d, f, r)) {
            changeCommand("U");
        }
        else if (isCornerSame(5, d, f, r)) {
            changeCommand("L'U'L");
        }
        else if (isCornerSame(6, d, f, r)) {
            changeCommand("LU2L'");
        }
        else if (isCornerSame(7, d, f, r)) {
            changeCommand("BUB'");
        }
    }

    void adjust_F_edge(int f, int r) {
        if (isEdgeSame(1, f, r)) {
            changeCommand("RU'R'");
        }
        else if (isEdgeSame(2, f, r)) {
            changeCommand("RU2R'");
        }
        else if (isEdgeSame(3, f, r)) {
            changeCommand("RUR'");
        }
        else if (isEdgeSame(4, f, r)) {
            changeCommand("R'FRF'");
        }
        else if (isEdgeSame(9, f, r)) {
            changeCommand("L'RU2LR'");
        }
        else if (isEdgeSame(10, f, r)) {
            changeCommand("LRU2L'R'");
        }
        else if (isEdgeSame(11, f, r)) {
            changeCommand("BF'UFB'");
        }
    }

    void adjust_F(int d, int f, int r) {
        adjust_F_edge(f, r);
        adjust_F_corner(d, f, r);

        if (isCornerSame(4, d, f, r)) {
            if (face[0][8] == d) {
                if (face[2][5] == f) {
                    changeCommand("RUR'U'RUR'U'RUR'");
                }
                else {
                    changeCommand("RU'R'F'U2F");
                }
            }
            else if (face[2][2] == d) {
                if (face[2][5] == f) {
                    changeCommand("U'RU'R'U2RU'R'");
                }
                else {
                    changeCommand("U'RUR'UF'U'F");
                }
            }
            else if (face[5][0] == d) {
                if (face[2][5] == f) {
                    changeCommand("UF'UFU2F'UF");
                }
                else {
                    changeCommand("UF'U'FU'RUR'");
                }
            }
        }
        else if (isCornerSame(8, d, f, r)) {
            if (face[2][8] == d) {
                if (face[2][5] == f) {
                    changeCommand("RUR'U'RU2R'U'RUR'");
                }
                else {
                    changeCommand("RU'RUBUB'R2");
                }
            }
            else if (face[2][2] == d) {
                if (face[2][5] == f) {
                    changeCommand("F'U'FUF'U2F'U'F'U'F");
                }
                else {
                    changeCommand("R2BUB'U'R'UR'");
                }
            }
            else if (face[1][2] == d) {
                if (face[2][5] == r) {
                    changeCommand("RU2R'U'RU2R'U2F'U'F");
                }
            }
        }
    }

    void F () {
        resetPlace();
        adjust_F(1, 2, 5);
        change('y', true);
        adjust_F(1, 5, 3);
        change('y', true);
        adjust_F(1, 3, 4);
        change('y', true);
        adjust_F(1, 4, 2);
        change('y', true);
    }

    void O () {

    }

    void P () {

    }

    void changeCommand(string &command) {
        int size = command.size();
        int i;
        for (int i = 0; i < size; i++) {
            if (i < size - 1 && command[i+1] == '\'') {
                change(command[i], true);
                i += 1;
            }
            else if (i < size - 1 && command[i+1] == '2') {
                change(command[i], false)
                change(command[i], false);
                i += 1;
            }
            else {
                change(command[i], false);
            }
        }
    }

    void changeLoop(int &p1, int &p2, int &p3, int &p4) {
        int temp = p1;
        p1 = p4;
        p4 = p3;
        p3 = p2;
        p2 = temp;
    }

    void change(char op, bool rev) {
        if rev == false {
            if op == 'U' {
                // U
                changeLoop(face[2][0], face[4][0], face[3][0], face[5][0]);
                changeLoop(face[2][1], face[4][1], face[3][1], face[5][1]);
                changeLoop(face[2][2], face[4][2], face[3][2], face[5][2]);
                changeLoop(face[0][0], face[0][2], face[0][8], face[0][6]);
                changeLoop(face[0][1], face[0][5], face[0][7], face[0][3]);
            }
            else if op == 'D' {
                // D
                changeLoop(face[2][6], face[5][6], face[3][6], face[4][6]);
                changeLoop(face[2][7], face[5][7], face[3][7], face[4][7]);
                changeLoop(face[2][8], face[5][8], face[3][8], face[4][8]);
                changeLoop(face[1][0], face[1][2], face[1][8], face[1][6]);
                changeLoop(face[1][1], face[1][5], face[1][7], face[1][3]);
            }
            else if op == 'R' {
                // R
                changeLoop(face[2][2], face[0][2], face[3][6], face[1][2]);
                changeLoop(face[2][5], face[0][5], face[3][3], face[1][5]);
                changeLoop(face[2][8], face[0][8], face[3][0], face[1][8]);
                changeLoop(face[5][0], face[5][2], face[5][8], face[5][6]);
                changeLoop(face[5][1], face[5][5], face[5][7], face[5][3]);
            }
            else if op == 'L' {
                // L
                changeLoop(face[2][0], face[1][0], face[3][8], face[0][0]);
                changeLoop(face[2][3], face[1][3], face[3][5], face[0][3]);
                changeLoop(face[2][6], face[1][6], face[3][2], face[0][6]);
                changeLoop(face[4][0], face[4][2], face[4][8], face[4][6]);
                changeLoop(face[4][1], face[4][5], face[4][7], face[4][3]);
            }
            else if op == 'F' {
                // F
                changeLoop(face[4][2], face[0][8], face[5][6], face[1][0]);
                changeLoop(face[4][5], face[0][7], face[5][3], face[1][1]);
                changeLoop(face[4][8], face[0][6], face[5][0], face[1][2]);
                changeLoop(face[2][0], face[2][2], face[2][8], face[2][6]);
                changeLoop(face[2][1], face[2][5], face[2][7], face[2][3]);
            }
            else if op == 'B' {
                // B
                changeLoop(face[0][0], face[4][6], face[1][8], face[5][2]);
                changeLoop(face[0][1], face[4][3], face[1][7], face[5][5]);
                changeLoop(face[0][2], face[4][0], face[1][6], face[5][8]);
                changeLoop(face[3][0], face[3][2], face[3][8], face[3][6]);
                changeLoop(face[3][1], face[3][5], face[3][7], face[3][3]);
            }
            else if op == 'u' {
                // u
                changeLoop(face[2][0], face[4][0], face[3][0], face[5][0]);
                changeLoop(face[2][1], face[4][1], face[3][1], face[5][1]);
                changeLoop(face[2][2], face[4][2], face[3][2], face[5][2]);
                changeLoop(face[0][0], face[0][2], face[0][8], face[0][6]);
                changeLoop(face[0][1], face[0][5], face[0][7], face[0][3]);

                changeLoop(face[2][3], face[4][3], face[3][3], face[5][3]);
                changeLoop(face[2][4], face[4][4], face[3][4], face[5][4]);
                changeLoop(face[2][5], face[4][5], face[3][5], face[5][5]);
            }
            else if op == 'd' {
                // d
                changeLoop(face[2][6], face[5][6], face[3][6], face[4][6]);
                changeLoop(face[2][7], face[5][7], face[3][7], face[4][7]);
                changeLoop(face[2][8], face[5][8], face[3][8], face[4][8]);
                changeLoop(face[1][0], face[1][2], face[1][8], face[1][6]);
                changeLoop(face[1][1], face[1][5], face[1][7], face[1][3]);

                changeLoop(face[2][3], face[5][3], face[3][3], face[4][3]);
                changeLoop(face[2][4], face[5][4], face[3][4], face[4][4]);
                changeLoop(face[2][5], face[5][5], face[3][5], face[4][5]);
            }
            else if op == 'r' {
                // r
                changeLoop(face[2][2], face[0][2], face[3][6], face[1][2]);
                changeLoop(face[2][5], face[0][5], face[3][3], face[1][5]);
                changeLoop(face[2][8], face[0][8], face[3][0], face[1][8]);
                changeLoop(face[5][0], face[5][2], face[5][8], face[5][6]);
                changeLoop(face[5][1], face[5][5], face[5][7], face[5][3]);

                changeLoop(face[2][1], face[0][1], face[3][7], face[1][1]);
                changeLoop(face[2][4], face[0][4], face[3][4], face[1][4]);
                changeLoop(face[2][7], face[0][7], face[3][1], face[1][7]);
            }
            else if op == 'l' {
                // l
                changeLoop(face[2][0], face[1][0], face[3][8], face[0][0]);
                changeLoop(face[2][3], face[1][3], face[3][5], face[0][3]);
                changeLoop(face[2][6], face[1][6], face[3][2], face[0][6]);
                changeLoop(face[4][0], face[4][2], face[4][8], face[4][6]);
                changeLoop(face[4][1], face[4][5], face[4][7], face[4][3]);

                changeLoop(face[2][1], face[1][1], face[3][7], face[0][1]);
                changeLoop(face[2][4], face[1][4], face[3][4], face[0][4]);
                changeLoop(face[2][7], face[1][7], face[3][1], face[0][7]);
            }
            else if op == 'f' {
                // f
                changeLoop(face[4][2], face[0][8], face[5][6], face[1][0]);
                changeLoop(face[4][5], face[0][7], face[5][3], face[1][1]);
                changeLoop(face[4][8], face[0][6], face[5][0], face[1][2]);
                changeLoop(face[2][0], face[2][2], face[2][8], face[2][6]);
                changeLoop(face[2][1], face[2][5], face[2][7], face[2][3]);

                changeLoop(face[0][3], face[5][1], face[1][5], face[4][7]);
                changeLoop(face[0][4], face[5][4], face[1][4], face[4][4]);
                changeLoop(face[0][5], face[5][7], face[1][3], face[4][1]);
            }
            else if op == 'b' {
                // b
                changeLoop(face[0][0], face[4][6], face[1][8], face[5][2]);
                changeLoop(face[0][1], face[4][3], face[1][7], face[5][5]);
                changeLoop(face[0][2], face[4][0], face[1][6], face[5][8]);
                changeLoop(face[3][0], face[3][2], face[3][8], face[3][6]);
                changeLoop(face[3][1], face[3][5], face[3][7], face[3][3]);

                changeLoop(face[0][3], face[4][7], face[1][5], face[5][1]);
                changeLoop(face[0][4], face[4][4], face[1][4], face[5][4]);
                changeLoop(face[0][5], face[4][1], face[1][3], face[5][7]);
            }
            else if op == 'x' {
                // x = r + L'
                changeLoop(face[2][2], face[0][2], face[3][6], face[1][2]);
                changeLoop(face[2][5], face[0][5], face[3][3], face[1][5]);
                changeLoop(face[2][8], face[0][8], face[3][0], face[1][8]);
                changeLoop(face[5][0], face[5][2], face[5][8], face[5][6]);
                changeLoop(face[5][1], face[5][5], face[5][7], face[5][3]);

                changeLoop(face[2][1], face[0][1], face[3][7], face[1][1]);
                changeLoop(face[2][4], face[0][4], face[3][4], face[1][4]);
                changeLoop(face[2][7], face[0][7], face[3][1], face[1][7]);

                changeLoop(face[2][0], face[0][0], face[3][8], face[1][0]);
                changeLoop(face[2][3], face[0][3], face[3][5], face[1][3]);
                changeLoop(face[2][6], face[0][6], face[3][2], face[1][6]);
                changeLoop(face[4][0], face[4][6], face[4][8], face[4][2]);
                changeLoop(face[4][1], face[4][3], face[4][7], face[4][5]);
            }
            else if op == 'y' {
                // y = u + D'
                changeLoop(face[2][0], face[4][0], face[3][0], face[5][0]);
                changeLoop(face[2][1], face[4][1], face[3][1], face[5][1]);
                changeLoop(face[2][2], face[4][2], face[3][2], face[5][2]);
                changeLoop(face[0][0], face[0][2], face[0][8], face[0][6]);
                changeLoop(face[0][1], face[0][5], face[0][7], face[0][3]);

                changeLoop(face[2][3], face[4][3], face[3][3], face[5][3]);
                changeLoop(face[2][4], face[4][4], face[3][4], face[5][4]);
                changeLoop(face[2][5], face[4][5], face[3][5], face[5][5]);

                changeLoop(face[2][6], face[4][6], face[3][6], face[5][6]);
                changeLoop(face[2][7], face[4][7], face[3][7], face[5][7]);
                changeLoop(face[2][8], face[4][8], face[3][8], face[5][8]);
                changeLoop(face[1][0], face[1][6], face[1][8], face[1][2]);
                changeLoop(face[1][1], face[1][3], face[1][7], face[1][5]);
            }
            else if op == 'z' {
                // z = f + B'
                changeLoop(face[4][2], face[0][8], face[5][6], face[1][0]);
                changeLoop(face[4][5], face[0][7], face[5][3], face[1][1]);
                changeLoop(face[4][8], face[0][6], face[5][0], face[1][2]);
                changeLoop(face[2][0], face[2][2], face[2][8], face[2][6]);
                changeLoop(face[2][1], face[2][5], face[2][7], face[2][3]);

                changeLoop(face[0][3], face[5][1], face[1][5], face[4][7]);
                changeLoop(face[0][4], face[5][4], face[1][4], face[4][4]);
                changeLoop(face[0][5], face[5][7], face[1][3], face[4][1]);

                changeLoop(face[0][0], face[5][2], face[1][8], face[4][6]);
                changeLoop(face[0][1], face[5][5], face[1][7], face[4][3]);
                changeLoop(face[0][2], face[5][8], face[1][6], face[4][0]);
                changeLoop(face[3][0], face[3][6], face[3][8], face[3][2]);
                changeLoop(face[3][1], face[3][3], face[3][7], face[3][5]);
            }
        }
        else {
            if op == 'U' {
                // U'
                changeLoop(face[2][0], face[5][0], face[3][0], face[4][0]);
                changeLoop(face[2][1], face[5][1], face[3][1], face[4][1]);
                changeLoop(face[2][2], face[5][2], face[3][2], face[4][2]);
                changeLoop(face[0][0], face[0][6], face[0][8], face[0][2]);
                changeLoop(face[0][1], face[0][3], face[0][7], face[0][5]);
            }
            else if op == 'D' {
                // D'
                changeLoop(face[2][6], face[4][6], face[3][6], face[5][6]);
                changeLoop(face[2][7], face[4][7], face[3][7], face[5][7]);
                changeLoop(face[2][8], face[4][8], face[3][8], face[5][8]);
                changeLoop(face[1][0], face[1][6], face[1][8], face[1][2]);
                changeLoop(face[1][1], face[1][3], face[1][7], face[1][5]);
            }
            else if op == 'R' {
                // R'
                changeLoop(face[2][2], face[1][2], face[3][6], face[0][2]);
                changeLoop(face[2][5], face[1][5], face[3][3], face[0][5]);
                changeLoop(face[2][8], face[1][8], face[3][0], face[0][8]);
                changeLoop(face[5][0], face[5][6], face[5][8], face[5][2]);
                changeLoop(face[5][1], face[5][3], face[5][7], face[5][5]);
            }
            else if op == 'L' {
                // L'
                changeLoop(face[2][0], face[0][0], face[3][8], face[1][0]);
                changeLoop(face[2][3], face[0][3], face[3][5], face[1][3]);
                changeLoop(face[2][6], face[0][6], face[3][2], face[1][6]);
                changeLoop(face[4][0], face[4][6], face[4][8], face[4][2]);
                changeLoop(face[4][1], face[4][3], face[4][7], face[4][5]);
            }
            else if op == 'F' {
                // F'
                changeLoop(face[4][2], face[1][0], face[5][6], face[0][8]);
                changeLoop(face[4][5], face[1][1], face[5][3], face[0][7]);
                changeLoop(face[4][8], face[1][2], face[5][0], face[0][6]);
                changeLoop(face[2][0], face[2][6], face[2][8], face[2][2]);
                changeLoop(face[2][1], face[2][3], face[2][7], face[2][5]);
            }
            else if op == 'B' {
                // B'
                changeLoop(face[0][0], face[5][2], face[1][8], face[4][6]);
                changeLoop(face[0][1], face[5][5], face[1][7], face[4][3]);
                changeLoop(face[0][2], face[5][8], face[1][6], face[4][0]);
                changeLoop(face[3][0], face[3][6], face[3][8], face[3][2]);
                changeLoop(face[3][1], face[3][3], face[3][7], face[3][5]);
            }
            else if op == 'u' {
                // u'
                changeLoop(face[2][0], face[5][0], face[3][0], face[4][0]);
                changeLoop(face[2][1], face[5][1], face[3][1], face[4][1]);
                changeLoop(face[2][2], face[5][2], face[3][2], face[4][2]);
                changeLoop(face[0][0], face[0][6], face[0][8], face[0][2]);
                changeLoop(face[0][1], face[0][3], face[0][7], face[0][5]);

                changeLoop(face[2][3], face[5][3], face[3][3], face[4][3]);
                changeLoop(face[2][4], face[5][4], face[3][4], face[4][4]);
                changeLoop(face[2][5], face[5][5], face[3][5], face[4][5]);
            }
            else if op == 'd' {
                // d'
                changeLoop(face[2][6], face[4][6], face[3][6], face[5][6]);
                changeLoop(face[2][7], face[4][7], face[3][7], face[5][7]);
                changeLoop(face[2][8], face[4][8], face[3][8], face[5][8]);
                changeLoop(face[1][0], face[1][6], face[1][8], face[1][2]);
                changeLoop(face[1][1], face[1][3], face[1][7], face[1][5]);

                changeLoop(face[2][3], face[4][3], face[3][3], face[5][3]);
                changeLoop(face[2][4], face[4][4], face[3][4], face[5][4]);
                changeLoop(face[2][5], face[4][5], face[3][5], face[5][5]);
            }
            else if op == 'r' {
                // r'
                changeLoop(face[2][2], face[1][2], face[3][6], face[0][2]);
                changeLoop(face[2][5], face[1][5], face[3][3], face[0][5]);
                changeLoop(face[2][8], face[1][8], face[3][0], face[0][8]);
                changeLoop(face[5][0], face[5][6], face[5][8], face[5][2]);
                changeLoop(face[5][1], face[5][3], face[5][7], face[5][5]);

                changeLoop(face[2][1], face[1][1], face[3][7], face[0][1]);
                changeLoop(face[2][4], face[1][4], face[3][4], face[0][4]);
                changeLoop(face[2][7], face[1][7], face[3][1], face[0][7]);
            }
            else if op == 'l' {
                // l'
                changeLoop(face[2][0], face[0][0], face[3][8], face[1][0]);
                changeLoop(face[2][3], face[0][3], face[3][5], face[1][3]);
                changeLoop(face[2][6], face[0][6], face[3][2], face[1][6]);
                changeLoop(face[4][0], face[4][6], face[4][8], face[4][2]);
                changeLoop(face[4][1], face[4][3], face[4][7], face[4][5]);

                changeLoop(face[2][1], face[0][1], face[3][7], face[1][1]);
                changeLoop(face[2][4], face[0][4], face[3][4], face[1][4]);
                changeLoop(face[2][7], face[0][7], face[3][1], face[1][7]);
            }
            else if op == 'f' {
                // f'
                changeLoop(face[4][2], face[1][0], face[5][6], face[0][8]);
                changeLoop(face[4][5], face[1][1], face[5][3], face[0][7]);
                changeLoop(face[4][8], face[1][2], face[5][0], face[0][6]);
                changeLoop(face[2][0], face[2][6], face[2][8], face[2][2]);
                changeLoop(face[2][1], face[2][3], face[2][7], face[2][5]);

                changeLoop(face[0][3], face[4][7], face[1][5], face[5][1]);
                changeLoop(face[0][4], face[4][4], face[1][4], face[5][4]);
                changeLoop(face[0][5], face[4][1], face[1][3], face[5][7]);
            }
            else if op == 'b' {
                // b'
                changeLoop(face[0][0], face[5][2], face[1][8], face[4][6]);
                changeLoop(face[0][1], face[5][5], face[1][7], face[4][3]);
                changeLoop(face[0][2], face[5][8], face[1][6], face[4][0]);
                changeLoop(face[3][0], face[3][6], face[3][8], face[3][2]);
                changeLoop(face[3][1], face[3][3], face[3][7], face[3][5]);

                changeLoop(face[0][3], face[5][1], face[1][5], face[4][7]);
                changeLoop(face[0][4], face[5][4], face[1][4], face[4][4]);
                changeLoop(face[0][5], face[5][7], face[1][3], face[4][1]);
            }
            else if op == 'x' {
                // x' = l + R'
                changeLoop(face[2][0], face[1][0], face[3][8], face[0][0]);
                changeLoop(face[2][3], face[1][3], face[3][5], face[0][3]);
                changeLoop(face[2][6], face[1][6], face[3][2], face[0][6]);
                changeLoop(face[4][0], face[4][2], face[4][8], face[4][6]);
                changeLoop(face[4][1], face[4][5], face[4][7], face[4][3]);

                changeLoop(face[2][1], face[1][1], face[3][7], face[0][1]);
                changeLoop(face[2][4], face[1][4], face[3][4], face[0][4]);
                changeLoop(face[2][7], face[1][7], face[3][1], face[0][7]);

                changeLoop(face[2][2], face[1][2], face[3][6], face[0][2]);
                changeLoop(face[2][5], face[1][5], face[3][3], face[0][5]);
                changeLoop(face[2][8], face[1][8], face[3][0], face[0][8]);
                changeLoop(face[5][0], face[5][6], face[5][8], face[5][2]);
                changeLoop(face[5][1], face[5][3], face[5][7], face[5][5]);
            }
            else if op == 'y' {
                // y' = d + U'
                changeLoop(face[2][6], face[5][6], face[3][6], face[4][6]);
                changeLoop(face[2][7], face[5][7], face[3][7], face[4][7]);
                changeLoop(face[2][8], face[5][8], face[3][8], face[4][8]);
                changeLoop(face[1][0], face[1][2], face[1][8], face[1][6]);
                changeLoop(face[1][1], face[1][5], face[1][7], face[1][3]);

                changeLoop(face[2][3], face[5][3], face[3][3], face[4][3]);
                changeLoop(face[2][4], face[5][4], face[3][4], face[4][4]);
                changeLoop(face[2][5], face[5][5], face[3][5], face[4][5]);

                changeLoop(face[2][0], face[5][0], face[3][0], face[4][0]);
                changeLoop(face[2][1], face[5][1], face[3][1], face[4][1]);
                changeLoop(face[2][2], face[5][2], face[3][2], face[4][2]);
                changeLoop(face[0][0], face[0][6], face[0][8], face[0][2]);
                changeLoop(face[0][1], face[0][3], face[0][7], face[0][5]);
            }
            else if op == 'z' {
                // z' = b + F'
                changeLoop(face[0][0], face[4][6], face[1][8], face[5][2]);
                changeLoop(face[0][1], face[4][3], face[1][7], face[5][5]);
                changeLoop(face[0][2], face[4][0], face[1][6], face[5][8]);
                changeLoop(face[3][0], face[3][2], face[3][8], face[3][6]);
                changeLoop(face[3][1], face[3][5], face[3][7], face[3][3]);

                changeLoop(face[0][3], face[4][7], face[1][5], face[5][1]);
                changeLoop(face[0][4], face[4][4], face[1][4], face[5][4]);
                changeLoop(face[0][5], face[4][1], face[1][3], face[5][7]);

                changeLoop(face[4][2], face[1][0], face[5][6], face[0][8]);
                changeLoop(face[4][5], face[1][1], face[5][3], face[0][7]);
                changeLoop(face[4][8], face[1][2], face[5][0], face[0][6]);
                changeLoop(face[2][0], face[2][6], face[2][8], face[2][2]);
                changeLoop(face[2][1], face[2][3], face[2][7], face[2][5]);
            }
        }
    }

        // 0   Up   Yellow
        // 1   Down   White
        // 2   Front   Blue
        // 3   Back   Green
        // 4   Left   Orange
        // 5   Right   Red
        /*

                    +---+---+---+
                    | 0 | 1 | 2 |
                    +---+---+---+
                    | 3 | U | 5 |
                    +---+---+---+
                    | 6 | 7 | 8 |
        +---+---+---+---+---+---+---+---+---+---+---+---+
        | 0 | 1 | 2 | 0 | 1 | 2 | 0 | 1 | 2 | 0 | 1 | 2 |
        +---+---+---+---+---+---+---+---+---+---+---+---+
        | 3 | L | 5 | 3 | F | 5 | 3 | R | 5 | 3 | B | 5 |
        +---+---+---+---+---+---+---+---+---+---+---+---+
        | 6 | 7 | 8 | 6 | 7 | 8 | 6 | 7 | 8 | 6 | 7 | 8 |
        +---+---+---+---+---+---+---+---+---+---+---+---+
                    | 0 | 1 | 2 |
                    +---+---+---+
                    | 3 | D | 5 |
                    +---+---+---+
                    | 6 | 7 | 8 |
                    +---+---+---+



        */
    int face[6][9];
};