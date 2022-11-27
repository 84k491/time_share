#include "message.h"

class ISender
{
public:
    virtual ~ISender() = default;
    virtual int send(const Message & msg) = 0; // TODO pass ptr and size here
    virtual bool is_ready() const = 0; // TODO just move it here, no need to override it
};
