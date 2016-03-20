#include <iostream>
#include <stdio.h>
using namespace std;

class mf {
public:

    void run() {
        C();
        F();
        O();
        P();
    }

private:

    void C () {

    }

    void F () {

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
            }
            else if op == 'R' {
                // R

            }
            else if op == 'L' {
                // L

            }
            else if op == 'F' {
                // F

            }
            else if op == 'B' {
                // B

            }
            else if op == 'u' {
                // u

            }
            else if op == 'd' {
                // d

            }
            else if op == 'r' {
                // r

            }
            else if op == 'l' {
                // l

            }
            else if op == 'f' {
                // f

            }
            else if op == 'b' {
                // b

            }
            else if op == 'x' {
                // x

            }
            else if op == 'y' {
                // y

            }
            else if op == 'z' {
                // z
            }
        }
        else {
            if op == 'U' {
                // U'
            }
            else if op == 'D' {
                // D'
            }
            else if op == 'R' {
                // R'
            }
            else if op == 'L' {
                // L'
            }
            else if op == 'F' {
                // F'
            }
            else if op == 'B' {
                // B'
            }
            else if op == 'u' {
                // u'
            }
            else if op == 'd' {
                // d'
            }
            else if op == 'r' {
                // r'
            }
            else if op == 'l' {
                // l'
            }
            else if op == 'f' {
                // f'
            }
            else if op == 'b' {
                // b'
            }
            else if op == 'x' {
                // x'
            }
            else if op == 'y' {
                // y'
            }
            else if op == 'z' {
                // z'
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