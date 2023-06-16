#pragma once

#include <vector>
#include "Stone.h"

/*

 o = small stone
 0 = large stone
| | = bridge

      o
  0       0
o          |o|
0          |0|
o          |o|
  0       0
      o

---------------------
INDEXES OF BRIDGE
---------------------
      o           o
  o       o   o       o
o          |0|          o
o          |1|          o
o          |2|          o
  o       o   o       o
      o           o

 */

class Bridge {
    std::vector<Stone> chain;
public:
    Bridge(Stone s0, Stone s1, Stone s2);
    [[nodiscard]] std::vector<Stone> getChain() const;
    void setChain(std::vector<Stone> chain);
};


