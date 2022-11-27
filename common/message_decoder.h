#include "message.h"

class MessageDecoder
{
public:
    static const Message * decode(const void * data, size_t size)
    {
        if (size != Message::size()) {
            std::cout << "Received size = " << size << std::endl;
            return nullptr;
        }
        const auto * msg = reinterpret_cast<const Message *>(data);
        if (!msg->verify()) {
            msg->print();
            std::cout << "message not verified" << std::endl;
            return nullptr;
        }
        return msg;
    }
};

