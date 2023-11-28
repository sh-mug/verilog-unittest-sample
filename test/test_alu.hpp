#include "Valu.h"

class ValuForTest : public Valu {
   public:
    ValuForTest() : Valu() {}
    ~ValuForTest() {}

    void exec(const int &_inst, const int &_a, const int &_b);
};
