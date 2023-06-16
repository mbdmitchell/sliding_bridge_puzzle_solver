#pragma once

#include <vector>
#include "Stone.h"

/*

 o = small stone
 0 = large stone

      o
  0       0
o          |o|
0          |0|
o          |o|
  0       0
      o

---------------------
INDEXES OF LOOPS
---------------------
      7           7
  6       8   8       6
5          |o|          5
4   upper  |0|  lower   4
3          |o|          3
  2       0   0       2
      1           1

 */

class Loop {
public:
    enum ID {UPPER, LOWER};
    Loop(ID id, Stone s0, Stone s1, Stone s2, Stone s3, Stone s4, Stone s5, Stone s6, Stone s7, Stone s8);
    std::vector<Stone> getChain() const;
    void setChain(const std::vector<Stone>& chain);
private:
    ID id;
    std::vector<Stone> chain;
};


