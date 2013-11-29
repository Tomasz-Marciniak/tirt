#ifndef EXPONENTIAL_H_
#define EXPONENTIAL_H_

#include "Source.h"

namespace traffic_generators {

class Exponential: public traffic_generators::Source {

public:
    Exponential();
    virtual ~Exponential();
};

} /* namespace traffic_generators */
#endif /* Exponential_H_ */
