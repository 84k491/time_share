#include "message.h"

class ISender
{
public:
    virtual ~ISender() = default;
    virtual int send(const Message & msg) = 0;
    virtual bool is_ready() const = 0;
};
