#include "message.h"

class MessageDecoder
{
public:
    static const Message * decode(const void * data, size_t size)
    {
        if (size != Message::size()) {
            return nullptr;
        }
        const auto * msg = reinterpret_cast<const Message *>(data);
        if (!msg->verify()) {
            msg->print();
            return nullptr;
        }
        return msg;
    }
};

