#include <iostream>
#include "CubeRubiks.hpp"

int main() {
    char cube[6][3][3] = {{{'G', 'W', 'B'}, {'O', 'W', 'G'}, {'Y', 'W', 'R'}},
                          {{'G', 'W', 'B'}, {'Y', 'B', 'B'}, {'Y', 'G', 'W'}},
                          {{'O', 'R', 'R'}, {'O', 'O', 'Y'}, {'R', 'Y', 'W'}},
                          {{'Y', 'G', 'W'}, {'B', 'G', 'G'}, {'G', 'B', 'B'}},
                          {{'O', 'B', 'W'}, {'O', 'R', 'R'}, {'R', 'Y', 'O'}},
                          {{'B', 'R', 'G'}, {'R', 'Y', 'W'}, {'O', 'O', 'Y'}}};
    CubeRubiks cubik(cube);
    cubik.first_step();
    cubik.check_output();
    cubik.cross();
    cubik.check_output();
    cubik.first_layer();
    cubik.check_output();
    cubik.middle_layer();
    cubik.check_output();
    cubik.yellow();
    cubik.check_output();
    cubik.good_yellow_cross();
    cubik.check_output();
    cubik.six_step();
    cubik.check_output();
    cubik.seven_step();
    cubik.check_output();

    return 0;
}
