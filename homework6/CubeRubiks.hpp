//
// Created by Vio on 04.06.2021.
//

#ifndef PROGA6LAB_CUBERUBIKS_HPP
#define PROGA6LAB_CUBERUBIKS_HPP

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class CubeRubiks {
private:
    char cube_color[6][3][3]{};
    vector<string> output;
public:
    explicit CubeRubiks( char cube[6][3][3]) {
        for (int k = 0; k < 6; k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cube_color[k][i][j] = cube[k][i][j];
                }
            }
        }
    }

    void right_turn(int num) {
        char upper_left = cube_color[num][0][0];
        cube_color[num][0][0] = cube_color[num][2][0];
        cube_color[num][2][0] = cube_color[num][2][2];
        cube_color[num][2][2] = cube_color[num][0][2];
        cube_color[num][0][2] = upper_left;

        char upper_middle = cube_color[num][0][1];
        cube_color[num][0][1] = cube_color[num][1][0];
        cube_color[num][1][0] = cube_color[num][2][1];
        cube_color[num][2][1] = cube_color[num][1][2];
        cube_color[num][1][2] = upper_middle;
        char first_upper_rib;
        char middle_upper_rib;
        char last_upper_rib;
        if (num == 0) {
            first_upper_rib = cube_color[1][2][0];
            middle_upper_rib = cube_color[1][2][1];
            last_upper_rib = cube_color[1][2][2];
            for (int i = 0; i < 3; i++) {
                cube_color[1][2][i] = cube_color[4][2][i];
                cube_color[4][2][i] = cube_color[3][2][i];
                cube_color[3][2][i] = cube_color[2][2][i];
            }
            cube_color[2][2][0] = first_upper_rib;
            cube_color[2][2][1] = middle_upper_rib;
            cube_color[2][2][2] = last_upper_rib;
        } else if (num == 1) {
            first_upper_rib = cube_color[5][2][0];
            middle_upper_rib = cube_color[5][2][1];
            last_upper_rib = cube_color[5][2][2];
            for (int i = 0; i < 3; i++) {
                cube_color[5][2][i] = cube_color[4][2 - i][2];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[4][i][2] = cube_color[0][0][i];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[0][0][i] = cube_color[2][2 - i][0];
            }
            cube_color[2][0][0] = first_upper_rib;
            cube_color[2][1][0] = middle_upper_rib;
            cube_color[2][2][0] = last_upper_rib;
        } else if (num == 2) {
            first_upper_rib = cube_color[5][2][2];
            middle_upper_rib = cube_color[5][1][2];
            last_upper_rib = cube_color[5][0][2];
            for (int i = 0; i < 3; i++) {
                cube_color[5][i][2] = cube_color[1][i][2];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[1][i][2] = cube_color[0][i][2];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[0][i][2] = cube_color[3][2 - i][0];
            }
            cube_color[3][0][0] = first_upper_rib;
            cube_color[3][1][0] = middle_upper_rib;
            cube_color[3][2][0] = last_upper_rib;
        } else if (num == 3) {
            first_upper_rib = cube_color[5][0][2];
            middle_upper_rib = cube_color[5][0][1];
            last_upper_rib = cube_color[5][0][0];
            for (int i = 0; i < 3; i++) {
                cube_color[5][0][2 - i] = cube_color[2][2 - i][2];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[2][i][2] = cube_color[0][2][2 - i];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[0][2][i] = cube_color[4][i][0];
            }
            cube_color[4][0][0] = first_upper_rib;
            cube_color[4][1][0] = middle_upper_rib;
            cube_color[4][2][0] = last_upper_rib;
        } else if (num == 4) {
            first_upper_rib = cube_color[5][0][0];
            middle_upper_rib = cube_color[5][1][0];
            last_upper_rib = cube_color[5][2][0];
            for (int i = 0; i < 3; i++) {
                cube_color[5][i][0] = cube_color[3][2 - i][2];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[3][i][2] = cube_color[0][2 - i][0];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[0][i][0] = cube_color[1][i][0];
            }
            cube_color[1][0][0] = first_upper_rib;
            cube_color[1][1][0] = middle_upper_rib;
            cube_color[1][2][0] = last_upper_rib;
        } else if (num == 5) {
            first_upper_rib = cube_color[3][0][2];
            middle_upper_rib = cube_color[3][0][1];
            last_upper_rib = cube_color[3][0][0];
            for (int i = 0; i < 3; i++) {
                cube_color[3][0][i] = cube_color[4][0][i];
                cube_color[4][0][i] = cube_color[1][0][i];
                cube_color[1][0][i] = cube_color[2][0][i];
            }
            cube_color[2][0][2] = first_upper_rib;
            cube_color[2][0][1] = middle_upper_rib;
            cube_color[2][0][0] = last_upper_rib;
        } else
            cout << "mistake";
        if (num == 0) {
            string action_now = "WhiteR ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "WhiteL ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 1) {
            string action_now = "BlueR ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "BlueL ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 2) {
            string action_now = "OrangeR ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "OrangeL ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 3) {
            string action_now = "GreenR ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "GreenL ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 4) {
            string action_now = "RedR ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "RedL ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 5) {
            string action_now = "YellowR ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "YellowL ") {
                output.pop_back();
                output.pop_back();
            }
        }
        if (output.size() >= 4 && output[output.size() - 1] == output[output.size() - 2] &&
            output[output.size() - 3] == output[output.size() - 4] &&
            output[output.size() - 2] == output[output.size() - 3]) {
            output.pop_back();
            output.pop_back();
            output.pop_back();
            output.pop_back();
        }
    }

    void left_turn(int num) {
        char upper_left = cube_color[num][0][0];
        cube_color[num][0][0] = cube_color[num][0][2];
        cube_color[num][0][2] = cube_color[num][2][2];
        cube_color[num][2][2] = cube_color[num][2][0];
        cube_color[num][2][0] = upper_left;

        char upper_middle = cube_color[num][0][1];
        cube_color[num][0][1] = cube_color[num][1][2];
        cube_color[num][1][2] = cube_color[num][2][1];
        cube_color[num][2][1] = cube_color[num][1][0];
        cube_color[num][1][0] = upper_middle;
        char first_upper_rib;
        char middle_upper_rib;
        char last_upper_rib;
        if (num == 0) {
            first_upper_rib = cube_color[1][2][0];
            middle_upper_rib = cube_color[1][2][1];
            last_upper_rib = cube_color[1][2][2];
            for (int i = 0; i < 3; i++) {
                cube_color[1][2][i] = cube_color[2][2][i];
                cube_color[2][2][i] = cube_color[3][2][i];
                cube_color[3][2][i] = cube_color[4][2][i];
            }
            cube_color[4][2][0] = first_upper_rib;
            cube_color[4][2][1] = middle_upper_rib;
            cube_color[4][2][2] = last_upper_rib;
        } else if (num == 1) {
            first_upper_rib = cube_color[5][2][0];
            middle_upper_rib = cube_color[5][2][1];
            last_upper_rib = cube_color[5][2][2];
            for (int i = 0; i < 3; i++) {
                cube_color[5][2][i] = cube_color[2][i][0];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[2][i][0] = cube_color[0][0][2 - i];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[0][0][i] = cube_color[4][i][2];
            }
            cube_color[4][2][2] = first_upper_rib;
            cube_color[4][1][2] = middle_upper_rib;
            cube_color[4][0][2] = last_upper_rib;
        } else if (num == 2) {
            first_upper_rib = cube_color[5][2][2];
            middle_upper_rib = cube_color[5][1][2];
            last_upper_rib = cube_color[5][0][2];
            for (int i = 0; i < 3; i++) {
                cube_color[5][i][2] = cube_color[3][2 - i][0];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[3][i][0] = cube_color[0][2 - i][2];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[0][i][2] = cube_color[1][i][2];
            }
            cube_color[1][2][2] = first_upper_rib;
            cube_color[1][1][2] = middle_upper_rib;
            cube_color[1][0][2] = last_upper_rib;
        } else if (num == 3) {
            first_upper_rib = cube_color[5][0][2];
            middle_upper_rib = cube_color[5][0][1];
            last_upper_rib = cube_color[5][0][0];
            for (int i = 0; i < 3; i++) {
                cube_color[5][0][2 - i] = cube_color[4][i][0];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[4][i][0] = cube_color[0][2][i];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[0][2][i] = cube_color[2][2 - i][2];
            }
            cube_color[2][2][2] = first_upper_rib;
            cube_color[2][1][2] = middle_upper_rib;
            cube_color[2][0][2] = last_upper_rib;
        } else if (num == 4) {
            first_upper_rib = cube_color[5][0][0];
            middle_upper_rib = cube_color[5][1][0];
            last_upper_rib = cube_color[5][2][0];
            for (int i = 0; i < 3; i++) {
                cube_color[5][i][0] = cube_color[1][i][0];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[1][i][0] = cube_color[0][i][0];
            }
            for (int i = 0; i < 3; i++) {
                cube_color[0][i][0] = cube_color[3][2 - i][2];
            }
            cube_color[3][2][2] = first_upper_rib;
            cube_color[3][1][2] = middle_upper_rib;
            cube_color[3][0][2] = last_upper_rib;
        } else if (num == 5) {
            first_upper_rib = cube_color[3][0][2];
            middle_upper_rib = cube_color[3][0][1];
            last_upper_rib = cube_color[3][0][0];
            for (int i = 0; i < 3; i++) {
                cube_color[3][0][i] = cube_color[2][0][i];
                cube_color[2][0][i] = cube_color[1][0][i];
                cube_color[1][0][i] = cube_color[4][0][i];
            }
            cube_color[4][0][2] = first_upper_rib;
            cube_color[4][0][1] = middle_upper_rib;
            cube_color[4][0][0] = last_upper_rib;
        } else
            cout << "mistake";
        if (num == 0) {
            string action_now = "WhiteL ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "WhiteR ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 1) {
            string action_now = "BlueL ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "BlueR ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 2) {
            string action_now = "OrangeL ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "OrangeR ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 3) {
            string action_now = "GreenL ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "GreenR ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 4) {
            string action_now = "RedL ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "RedR ") {
                output.pop_back();
                output.pop_back();
            }
        } else if (num == 5) {
            string action_now = "YellowL ";
            output.push_back(action_now);
            if (output.size() > 1 && output[size(output) - 2] == "YellowR ") {
                output.pop_back();
                output.pop_back();
            }
        }
        if (output.size() >= 4 && output[output.size() - 1] == output[output.size() - 2] &&
            output[output.size() - 3] == output[output.size() - 4] &&
            output[output.size() - 2] == output[output.size() - 3]) {
            output.pop_back();
            output.pop_back();
            output.pop_back();
            output.pop_back();
        }
    }

    void turn_180(int num) {
        right_turn(num);
        right_turn(num);
    }

    void check_output() {
        for (int k = 0; k < 6; k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << cube_color[k][i][j] << ' ';
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    void first_step() {
        int petal = 0;
        int moves_count = 0;
        while (petal != 4) {
            if (moves_count > 50) {
                cout << "mistake flowers";
            }
            if ((cube_color[5][0][1] == 'W') && (cube_color[5][1][0] == 'W') && (cube_color[5][2][1] == 'W') &&
                (cube_color[5][1][2] == 'W')) {
                petal = 4;
                break;
            } else if (cube_color[1][1][0] == 'W') {
                while (cube_color[5][1][0] == 'W') {
                    left_turn(5);
                }
                left_turn(4);
            } else if (cube_color[1][1][2] == 'W') {
                while (cube_color[5][1][2] == 'W') {
                    left_turn(5);
                }
                right_turn(2);
            } else if (cube_color[2][1][0] == 'W') {
                while (cube_color[5][2][1] == 'W') {
                    left_turn(5);
                }
                left_turn(1);
            } else if (cube_color[2][1][2] == 'W') {
                while (cube_color[5][0][1] == 'W') {
                    left_turn(5);
                }
                right_turn(3);
            } else if (cube_color[3][1][0] == 'W') {
                while (cube_color[5][1][2] == 'W') {
                    left_turn(5);
                }
                left_turn(2);
            } else if (cube_color[3][1][2] == 'W') {
                while (cube_color[5][1][0] == 'W') {
                    left_turn(5);
                }
                right_turn(4);
            } else if (cube_color[4][1][0] == 'W') {
                while (cube_color[5][0][1] == 'W') {
                    left_turn(5);
                }
                left_turn(3);
            } else if (cube_color[4][1][2] == 'W') {
                while (cube_color[5][2][1] == 'W') {
                    left_turn(5);
                }
                right_turn(1);
            } else if (cube_color[0][1][0] == 'W') {
                while (cube_color[5][1][0] == 'W') {
                    left_turn(5);
                }
                turn_180(4);
            } else if (cube_color[0][0][1] == 'W') {
                while (cube_color[5][2][1] == 'W') {
                    left_turn(5);
                }
                turn_180(1);
            } else if (cube_color[0][1][2] == 'W') {
                while (cube_color[5][1][2] == 'W') {
                    left_turn(5);
                }
                turn_180(2);
            } else if (cube_color[0][2][1] == 'W') {
                while (cube_color[5][0][1] == 'W') {
                    left_turn(5);
                }
                turn_180(3);
            } else {
                for (int j = 1; j <= 4; j++) {
                    if ((cube_color[j][0][1] == 'W') || (cube_color[j][2][1] == 'W')) {
                        if (j == 1) {
                            while (cube_color[5][2][1] == 'W') {
                                left_turn(5);
                            }
                        } else if (j == 2) {
                            while (cube_color[5][1][2] == 'W') {
                                left_turn(5);
                            }
                        } else if (j == 3) {
                            while (cube_color[5][0][1] == 'W') {
                                left_turn(5);
                            }
                        } else if (j == 4) {
                            while (cube_color[5][1][0] == 'W') {
                                left_turn(5);
                            }
                        }
                        right_turn(j);
                        break;
                    }
                }
            }
        }
        string action_now = " flower ready\n";
        output.push_back(action_now);
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
        }
        output.clear();
    }

    void cross() {
        int petal = 0;
        while (petal != 4) {
            if (cube_color[1][0][1] == 'B' && cube_color[5][2][1] == 'W') {
                turn_180(1);
                petal++;

            } else if (cube_color[1][0][1] == 'R' && cube_color[5][2][1] == 'W') {
                right_turn(5);
                turn_180(4);
                petal++;

            } else if (cube_color[1][0][1] == 'O' && cube_color[5][2][1] == 'W') {
                left_turn(5);
                turn_180(2);
                petal++;

            } else if (cube_color[1][0][1] == 'G' && cube_color[5][2][1] == 'W') {
                turn_180(5);
                turn_180(3);
                petal++;

            } else if (cube_color[2][0][1] == 'O' && cube_color[5][1][2] == 'W') {
                turn_180(2);
                petal++;

            } else if (cube_color[2][0][1] == 'B' && cube_color[5][1][2] == 'W') {
                right_turn(5);
                turn_180(1);
                petal++;

            } else if (cube_color[2][0][1] == 'G' && cube_color[5][1][2] == 'W') {
                left_turn(5);
                turn_180(3);
                petal++;

            } else if (cube_color[2][0][1] == 'R' && cube_color[5][1][2] == 'W') {
                turn_180(5);
                turn_180(4);
                petal++;

            } else if (cube_color[3][0][1] == 'G' && cube_color[5][0][1] == 'W') {
                turn_180(3);
                petal++;

            } else if (cube_color[3][0][1] == 'R' && cube_color[5][0][1] == 'W') {
                left_turn(5);
                turn_180(4);
                petal++;

            } else if (cube_color[3][0][1] == 'B' && cube_color[5][0][1] == 'W') {
                turn_180(5);
                turn_180(1);
                petal++;

            } else if (cube_color[3][0][1] == 'O' && cube_color[5][0][1] == 'W') {
                right_turn(5);
                turn_180(2);
                petal++;

            } else if (cube_color[4][0][1] == 'R' && cube_color[5][1][0] == 'W') {
                turn_180(4);
                petal++;

            } else if (cube_color[4][0][1] == 'O' && cube_color[5][1][0] == 'W') {
                turn_180(5);
                turn_180(2);
                petal++;

            } else if (cube_color[4][0][1] == 'B' && cube_color[5][1][0] == 'W') {
                left_turn(5);
                turn_180(1);
                petal++;

            } else if (cube_color[4][0][1] == 'G' && cube_color[5][1][0] == 'W') {
                right_turn(5);
                turn_180(3);
                petal++;

            }
        }
        string action_now = " cross ready\n";
        output.push_back(action_now);
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
        }
        output.clear();

    }

    void first_layer() {
        int flag_finish = 0;
        while (flag_finish != 4) {
            if ((cube_color[1][2][1] == 'B') && (cube_color[1][0][2] == 'W') && (cube_color[2][0][0] == 'O') &&
                (cube_color[2][2][1] == 'O') && (cube_color[5][2][2] == 'B')) {
                flag_finish = 0;
                left_turn(1);
                left_turn(5);
                right_turn(1);
            } else if ((cube_color[4][2][1] == 'R') && (cube_color[4][0][2] == 'W') && (cube_color[1][0][0] == 'B') &&
                       (cube_color[1][2][1] == 'B') && (cube_color[5][2][0] == 'R')) {
                flag_finish = 0;
                left_turn(4);
                left_turn(5);
                right_turn(4);
            } else if ((cube_color[2][2][1] == 'O') && (cube_color[2][0][2] == 'W') && (cube_color[3][0][0] == 'G') &&
                       (cube_color[3][2][1] == 'G') && (cube_color[5][0][2] == 'O')) {
                flag_finish = 0;
                left_turn(2);
                left_turn(5);
                right_turn(2);
            } else if ((cube_color[3][2][1] == 'G') && (cube_color[3][0][2] == 'W') && (cube_color[4][0][0] == 'R') &&
                       (cube_color[4][2][1] == 'R') && (cube_color[5][0][0] == 'G')) {
                flag_finish = 0;
                left_turn(3);
                left_turn(5);
                right_turn(3);
            } else if ((cube_color[1][2][1] == 'B') && (cube_color[1][0][2] == 'B') && (cube_color[2][0][0] == 'W') &&
                       (cube_color[2][2][1] == 'O') && (cube_color[5][2][2] == 'O')) {
                flag_finish = 0;
                right_turn(2);
                right_turn(5);
                left_turn(2);
            } else if ((cube_color[4][2][1] == 'R') && (cube_color[4][0][2] == 'R') && (cube_color[1][0][0] == 'W') &&
                       (cube_color[1][2][1] == 'B') && (cube_color[5][2][0] == 'B')) {
                flag_finish = 0;
                right_turn(1);
                right_turn(5);
                left_turn(1);
            } else if ((cube_color[2][2][1] == 'O') && (cube_color[2][0][2] == 'O') && (cube_color[3][0][0] == 'W') &&
                       (cube_color[3][2][1] == 'G') && (cube_color[5][0][2] == 'G')) {
                flag_finish = 0;
                right_turn(3);
                right_turn(5);
                left_turn(3);
            } else if ((cube_color[3][2][1] == 'G') && (cube_color[3][0][2] == 'G') && (cube_color[4][0][0] == 'W') &&
                       (cube_color[4][2][1] == 'R') && (cube_color[5][0][0] == 'R')) {
                flag_finish = 0;
                right_turn(4);
                right_turn(5);
                left_turn(4);
            } else if ((cube_color[1][2][1] == 'B') && (cube_color[1][0][2] == 'O') && (cube_color[2][0][0] == 'B') &&
                       (cube_color[2][2][1] == 'O') && (cube_color[5][2][2] == 'W')) {
                flag_finish = 0;
                right_turn(2);
                left_turn(5);
                left_turn(2);
                turn_180(5);
                right_turn(2);
                right_turn(5);
                left_turn(2);
            } else if ((cube_color[4][2][1] == 'R') && (cube_color[4][0][2] == 'B') && (cube_color[1][0][0] == 'R') &&
                       (cube_color[1][2][1] == 'B') && (cube_color[5][2][0] == 'W')) {
                flag_finish = 0;
                right_turn(1);
                left_turn(5);
                left_turn(1);
                turn_180(5);
                right_turn(1);
                right_turn(5);
                left_turn(1);
            } else if ((cube_color[2][2][1] == 'O') && (cube_color[2][0][2] == 'G') && (cube_color[3][0][0] == 'O') &&
                       (cube_color[3][2][1] == 'G') && (cube_color[5][0][2] == 'W')) {
                flag_finish = 0;
                right_turn(3);
                left_turn(5);
                left_turn(3);
                turn_180(5);
                right_turn(3);
                right_turn(5);
                left_turn(3);
            } else if ((cube_color[3][2][1] == 'G') && (cube_color[3][0][2] == 'R') && (cube_color[4][0][0] == 'G') &&
                       (cube_color[4][2][1] == 'R') && (cube_color[5][0][0] == 'W')) {
                flag_finish = 0;
                right_turn(4);
                left_turn(5);
                left_turn(4);
                turn_180(5);
                right_turn(4);
                right_turn(5);
                left_turn(4);
            } else if (((cube_color[1][2][1] == 'B') && (cube_color[2][2][1] == 'O')) &&
                       ((cube_color[1][2][2] == 'W') || (cube_color[2][2][0] == 'W'))) {
                flag_finish = 0;
                left_turn(1);
                left_turn(5);
                right_turn(1);
            } else if (((cube_color[4][2][1] == 'R') && (cube_color[1][2][1] == 'B')) &&
                       ((cube_color[4][2][2] == 'W') || (cube_color[1][2][0] == 'W'))) {
                flag_finish = 0;
                left_turn(4);
                left_turn(5);
                right_turn(4);
            } else if (((cube_color[2][2][1] == 'O') && (cube_color[3][2][1] == 'G')) &&
                       ((cube_color[2][2][2] == 'W') || (cube_color[3][2][0] == 'W'))) {
                flag_finish = 0;
                left_turn(2);
                left_turn(5);
                right_turn(2);
            } else if (((cube_color[3][2][1] == 'G') && (cube_color[4][2][1] == 'R')) &&
                       ((cube_color[3][2][2] == 'W') || (cube_color[4][2][0] == 'W'))) {
                flag_finish = 0;
                left_turn(3);
                left_turn(5);
                right_turn(3);
            } else if (((cube_color[4][2][1] == 'R') && (cube_color[0][0][0] == 'W') && (cube_color[1][2][1] == 'B')) &&
                       ((cube_color[4][2][2] != 'R') || (cube_color[1][2][0] != 'B'))) {
                flag_finish = 0;
                right_turn(1);
                left_turn(5);
                left_turn(1);
            } else if (((cube_color[1][2][1] == 'B') && (cube_color[2][2][1] == 'O') && (cube_color[0][0][2] == 'W')) &&
                       ((cube_color[1][2][2] != 'B') || (cube_color[2][2][0] != 'O'))) {
                flag_finish = 0;
                right_turn(2);
                left_turn(5);
                left_turn(2);
            } else if (((cube_color[2][2][1] == 'O') && (cube_color[3][2][1] == 'G') && (cube_color[0][2][2] == 'W')) &&
                       ((cube_color[2][2][2] != 'O') || (cube_color[3][2][0] != 'G'))) {
                flag_finish = 0;
                right_turn(3);
                left_turn(5);
                left_turn(3);
            } else if (((cube_color[3][2][1] == 'G') && (cube_color[4][2][1] == 'R') && (cube_color[0][2][0] == 'W')) &&
                       ((cube_color[3][2][2] != 'G') || (cube_color[4][2][0] != 'R'))) {
                flag_finish = 0;
                right_turn(4);
                left_turn(5);
                left_turn(4);
            } else {
                flag_finish++;
                right_turn(5);
            }
        }
        string action_now = " first layer ready\n";
        output.push_back(action_now);
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
        }
        output.clear();

    }

    void middle_layer() {
        int flag_finish = 0;
        int flag_iteration;
        while (flag_finish != 4) {
            flag_iteration = 0;
            for (int i = 1; i <= 4; i++) {
                if ((cube_color[i][0][1] == cube_color[i][1][1]) && (((i == 1) && (cube_color[5][2][1] == 'O')) ||
                                                                     ((i == 2) && (cube_color[5][1][2] == 'G')) ||
                                                                     ((i == 3) && (cube_color[5][0][1] == 'R')) ||
                                                                     ((i == 4) && (cube_color[5][1][0] == 'B')))) {
                    if (i != 4) {
                        flag_finish = 0;
                        right_turn(5);
                        right_turn(i + 1);
                        right_turn(5);
                        left_turn(i + 1);
                        left_turn(5);
                        left_turn(i);
                        left_turn(5);
                        right_turn(i);
                        right_turn(5);
                    } else {
                        flag_finish = 0;
                        right_turn(5);
                        right_turn(1);
                        right_turn(5);
                        left_turn(1);
                        left_turn(5);
                        left_turn(i);
                        left_turn(5);
                        right_turn(i);
                        right_turn(5);
                    }
                    flag_iteration = 1;
                    flag_finish = 0;
                    break;
                }
            }
            if (flag_iteration == 0) {
                for (int i = 1; i <= 4; i++) {
                    if ((cube_color[i][0][1] == cube_color[i][1][1]) && (((i == 1) && (cube_color[5][2][1] == 'R')) ||
                                                                         ((i == 2) && (cube_color[5][1][2] == 'B')) ||
                                                                         ((i == 3) && (cube_color[5][0][1] == 'O')) ||
                                                                         ((i == 4) && (cube_color[5][1][0] == 'G')))) {
                        if (i != 1) {

                            left_turn(5);
                            left_turn(i - 1);
                            left_turn(5);
                            right_turn(i - 1);
                            right_turn(5);
                            right_turn(i);
                            right_turn(5);
                            left_turn(i);
                            left_turn(5);
                        } else {

                            left_turn(5);
                            left_turn(4);
                            left_turn(5);
                            right_turn(4);
                            right_turn(5);
                            right_turn(i);
                            right_turn(5);
                            left_turn(i);
                            left_turn(5);
                        }
                        flag_iteration = 1;
                        flag_finish = 0;
                        break;
                    }
                }
            }
            if (flag_iteration == 0) {
                flag_finish++;
                left_turn(5);
            }
            if ((flag_iteration == 0) && (flag_finish == 4) &&
                ((cube_color[1][1][0] != 'B') || (cube_color[4][1][2] != 'R'))) {
                flag_finish = 0;
                right_turn(1);
                right_turn(5);
                left_turn(1);
                left_turn(5);
                left_turn(4);
                left_turn(5);
                right_turn(4);
                right_turn(5);
            } else if ((flag_iteration == 0) && (flag_finish == 4) &&
                       ((cube_color[2][1][0] != 'O') || (cube_color[1][1][2] != 'B'))) {
                flag_finish = 0;
                right_turn(2);
                right_turn(5);
                left_turn(2);
                left_turn(5);
                left_turn(1);
                left_turn(5);
                right_turn(1);
                right_turn(5);
            } else if ((flag_iteration == 0) && (flag_finish == 4) &&
                       ((cube_color[3][1][0] != 'G') || (cube_color[2][1][2] != 'O'))) {
                flag_finish = 0;
                right_turn(3);
                right_turn(5);
                left_turn(3);
                left_turn(5);
                left_turn(2);
                left_turn(5);
                right_turn(2);
                right_turn(5);
            } else if ((flag_iteration == 0) && (flag_finish == 4) &&
                       ((cube_color[4][1][0] != 'R') || (cube_color[3][1][2] != 'G'))) {
                flag_finish = 0;
                right_turn(4);
                right_turn(5);
                left_turn(4);
                left_turn(5);
                left_turn(3);
                left_turn(5);
                right_turn(3);
                right_turn(5);
            }

        }
        string action_now = " middle layer ready\n";
        output.push_back(action_now);
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
        }
        output.clear();
    }

    void yellow() {
        if (cube_color[1][0][1] == 'Y' && cube_color[2][0][1] == 'Y' && cube_color[5][0][1] == 'Y' &&
            cube_color[5][1][0] == 'Y') {
            right_turn(1);
            right_turn(5);
            right_turn(2);
            left_turn(5);
            left_turn(2);
            left_turn(1);
        } else if (cube_color[1][0][1] == 'Y' && cube_color[4][0][1] == 'Y' && cube_color[5][0][1] == 'Y' &&
                   cube_color[5][1][2] == 'Y') {
            right_turn(4);
            right_turn(5);
            right_turn(1);
            left_turn(5);
            left_turn(1);
            left_turn(4);
        } else if (cube_color[2][0][1] == 'Y' && cube_color[3][0][1] == 'Y' && cube_color[5][2][1] == 'Y' &&
                   cube_color[5][1][0] == 'Y') {
            right_turn(2);
            right_turn(5);
            right_turn(3);
            left_turn(5);
            left_turn(3);
            left_turn(2);
        } else if (cube_color[3][0][1] == 'Y' && cube_color[4][0][1] == 'Y' && cube_color[5][1][2] == 'Y' &&
                   cube_color[5][2][1] == 'Y') {
            right_turn(3);
            right_turn(5);
            right_turn(4);
            left_turn(5);
            left_turn(4);
            left_turn(3);
        } else if (cube_color[1][0][1] == 'Y' && cube_color[3][0][1] == 'Y' && cube_color[5][1][0] == 'Y' &&
                   cube_color[5][1][2] == 'Y') {
            right_turn(1);
            right_turn(2);
            right_turn(5);
            left_turn(2);
            left_turn(5);
            left_turn(1);
        } else if (cube_color[2][0][1] == 'Y' && cube_color[4][0][1] == 'Y' && cube_color[5][0][1] == 'Y' &&
                   cube_color[5][2][1] == 'Y') {
            right_turn(2);
            right_turn(3);
            right_turn(5);
            left_turn(3);
            left_turn(5);
            left_turn(2);
        } else if (cube_color[1][0][1] == 'Y' && cube_color[2][0][1] == 'Y' && cube_color[3][0][1] == 'Y' &&
                   cube_color[4][1][0] == 'Y') {
            right_turn(1);
            right_turn(5);
            right_turn(2);
            left_turn(5);
            left_turn(2);
            left_turn(1);
            right_turn(2);
            right_turn(3);
            right_turn(5);
            left_turn(3);
            left_turn(5);
            left_turn(2);
        }
        if (cube_color[5][0][1] != 'Y' || cube_color[5][1][0] != 'Y' || cube_color[5][1][2] != 'Y' ||
            cube_color[5][2][1] != 'Y') {
            cout << "MISTAKE";
        }
        string action_now = " yellow cross ready\n";
        output.push_back(action_now);
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
        }
        output.clear();

    }

    void good_yellow_cross() {
        if (cube_color[2][0][1] == 'B') {
            right_turn(5);
            left_turn(4);
            turn_180(5);
            right_turn(4);
            right_turn(5);
            left_turn(4);
            right_turn(5);
            right_turn(4);
        } else if (cube_color[4][0][1] == 'B') {
            right_turn(5);
            left_turn(3);
            turn_180(5);
            right_turn(3);
            right_turn(5);
            left_turn(3);
            right_turn(5);
            right_turn(3);
        } else if (cube_color[3][0][1] == 'B') {
            right_turn(5);
            left_turn(2);
            turn_180(5);
            right_turn(2);
            right_turn(5);
            left_turn(2);
            right_turn(5);
            right_turn(2);
            right_turn(5);
            left_turn(3);
            turn_180(5);
            right_turn(3);
            right_turn(5);
            left_turn(3);
            right_turn(5);
            right_turn(3);
            right_turn(5);
            left_turn(2);
            turn_180(5);
            right_turn(2);
            right_turn(5);
            left_turn(2);
            right_turn(5);
            right_turn(2);
        }
        if (cube_color[3][0][1] == 'O') {
            right_turn(5);
            left_turn(1);
            turn_180(5);
            right_turn(1);
            right_turn(5);
            left_turn(1);
            right_turn(5);
            right_turn(1);
        } else if (cube_color[4][0][1] == 'O') {
            right_turn(5);
            left_turn(3);
            turn_180(5);
            right_turn(3);
            right_turn(5);
            left_turn(3);
            right_turn(5);
            right_turn(3);
            right_turn(5);
            left_turn(4);
            turn_180(5);
            right_turn(4);
            right_turn(5);
            left_turn(4);
            right_turn(5);
            right_turn(4);
            right_turn(5);
            left_turn(3);
            turn_180(5);
            right_turn(3);
            right_turn(5);
            left_turn(3);
            right_turn(5);
            right_turn(3);
        }
        if (cube_color[4][0][1] == 'G') {
            right_turn(5);
            left_turn(2);
            turn_180(5);
            right_turn(2);
            right_turn(5);
            left_turn(2);
            right_turn(5);
            right_turn(2);
        }
        string action_now = " yellow cross ready\n";
        output.push_back(action_now);
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
        }
        output.clear();
    }

    void six_step() {
        while (true) {
            if ((cube_color[1][0][0] == 'B' && cube_color[5][2][0] == 'Y' && cube_color[4][0][2] == 'O') ||
                (cube_color[1][0][0] == 'B' && cube_color[5][2][0] == 'O' && cube_color[4][0][2] == 'Y') ||
                (cube_color[1][0][0] == 'O' && cube_color[5][2][0] == 'Y' && cube_color[4][0][2] == 'B') ||
                (cube_color[1][0][0] == 'O' && cube_color[5][2][0] == 'B' && cube_color[4][0][2] == 'Y') ||
                (cube_color[1][0][0] == 'Y' && cube_color[5][2][0] == 'O' && cube_color[4][0][2] == 'B') ||
                (cube_color[1][0][0] == 'Y' && cube_color[5][2][0] == 'B' && cube_color[4][0][2] == 'O')) {
                left_turn(1);
                left_turn(4);
                right_turn(1);
                left_turn(2);
                left_turn(1);
                right_turn(4);
                right_turn(1);
                right_turn(2);
            } else if ((cube_color[3][0][0] == 'B' && cube_color[5][0][2] == 'Y' && cube_color[2][0][2] == 'O') ||
                       (cube_color[3][0][0] == 'B' && cube_color[5][0][2] == 'O' && cube_color[2][0][2] == 'Y') ||
                       (cube_color[3][0][0] == 'O' && cube_color[5][0][2] == 'Y' && cube_color[2][0][2] == 'B') ||
                       (cube_color[3][0][0] == 'O' && cube_color[5][0][2] == 'B' && cube_color[2][0][2] == 'Y') ||
                       (cube_color[3][0][0] == 'Y' && cube_color[5][0][2] == 'O' && cube_color[2][0][2] == 'B') ||
                       (cube_color[3][0][0] == 'Y' && cube_color[5][0][2] == 'B' && cube_color[2][0][2] == 'O')) {
                left_turn(2);
                left_turn(1);
                left_turn(4);
                right_turn(1);
                right_turn(2);
                left_turn(1);
                right_turn(4);
                right_turn(1);
            } else if ((cube_color[4][0][0] == 'B' && cube_color[3][0][2] == 'Y' && cube_color[5][0][0] == 'O') ||
                       (cube_color[4][0][0] == 'B' && cube_color[3][0][2] == 'O' && cube_color[5][0][0] == 'Y') ||
                       (cube_color[4][0][0] == 'O' && cube_color[3][0][2] == 'Y' && cube_color[5][0][0] == 'B') ||
                       (cube_color[4][0][0] == 'O' && cube_color[3][0][2] == 'B' && cube_color[5][0][0] == 'Y') ||
                       (cube_color[4][0][0] == 'Y' && cube_color[3][0][2] == 'O' && cube_color[5][0][0] == 'B') ||
                       (cube_color[4][0][0] == 'Y' && cube_color[3][0][2] == 'B' && cube_color[5][0][0] == 'O')) {
                left_turn(1);
                left_turn(4);
                left_turn(3);
                right_turn(4);
                right_turn(1);
                left_turn(4);
                right_turn(3);
                right_turn(4);
            } else break;
        }
        while (true) {
            if ((cube_color[1][0][0] == 'G' && cube_color[5][2][0] == 'Y' && cube_color[4][0][2] == 'O') ||
                (cube_color[1][0][0] == 'G' && cube_color[5][2][0] == 'O' && cube_color[4][0][2] == 'Y') ||
                (cube_color[1][0][0] == 'O' && cube_color[5][2][0] == 'Y' && cube_color[4][0][2] == 'G') ||
                (cube_color[1][0][0] == 'O' && cube_color[5][2][0] == 'G' && cube_color[4][0][2] == 'Y') ||
                (cube_color[1][0][0] == 'Y' && cube_color[5][2][0] == 'O' && cube_color[4][0][2] == 'G') ||
                (cube_color[1][0][0] == 'Y' && cube_color[5][2][0] == 'G' && cube_color[4][0][2] == 'O')) {
                left_turn(3);
                left_turn(2);
                right_turn(3);
                left_turn(4);
                left_turn(3);
                right_turn(2);
                right_turn(3);
                right_turn(4);
            } else if ((cube_color[4][0][0] == 'G' && cube_color[3][0][2] == 'Y' && cube_color[5][0][0] == 'O') ||
                       (cube_color[4][0][0] == 'G' && cube_color[3][0][2] == 'O' && cube_color[5][0][0] == 'Y') ||
                       (cube_color[4][0][0] == 'O' && cube_color[3][0][2] == 'Y' && cube_color[5][0][0] == 'G') ||
                       (cube_color[4][0][0] == 'O' && cube_color[3][0][2] == 'G' && cube_color[5][0][0] == 'Y') ||
                       (cube_color[4][0][0] == 'Y' && cube_color[3][0][2] == 'O' && cube_color[5][0][0] == 'G') ||
                       (cube_color[4][0][0] == 'Y' && cube_color[3][0][2] == 'G' && cube_color[5][0][0] == 'O')) {
                left_turn(4);
                left_turn(3);
                left_turn(2);
                right_turn(3);
                right_turn(4);
                left_turn(3);
                right_turn(2);
                right_turn(3);
            } else break;
        }
        string action_now = " six step ready\n";
        output.push_back(action_now);
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
        }
        output.clear();
    }

    void seven_step() {
        while (true) {

            if (cube_color[2][0][0] == 'Y') {
                left_turn(1);
                right_turn(2);
                right_turn(1);
                left_turn(2);
                left_turn(1);
                right_turn(2);
                right_turn(1);
                left_turn(2);
            } else if (cube_color[1][0][2] == 'Y') {
                right_turn(2);
                left_turn(1);
                left_turn(2);
                right_turn(1);
                right_turn(2);
                left_turn(1);
                left_turn(2);
                right_turn(1);

            }
            if (cube_color[5][2][2] == 'Y' && cube_color[1][0][2] == 'B' && cube_color[2][0][0] == 'O' &&
                cube_color[5][0][2] == 'Y' && cube_color[2][0][2] == 'O' && cube_color[3][0][0] == 'G' &&
                cube_color[5][0][0] == 'Y' && cube_color[3][0][2] == 'G' && cube_color[4][0][0] == 'R' &&
                cube_color[5][2][0] == 'Y' && cube_color[4][0][2] == 'R' && cube_color[1][0][0] == 'B') {
                break;
            }
            right_turn(5);

        }
        string action_now = " seven step ready\n";
        output.push_back(action_now);
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
        }
        output.clear();
    }
};

#endif //PROGA6LAB_CUBERUBIKS_HPP
