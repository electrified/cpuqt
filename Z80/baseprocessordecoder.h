#ifndef BASEPROCESSORDECODER
#define BASEPROCESSORDECODER

#include "Z80/BaseProcessor.h"

class BaseProcessorDecoder : public BaseProcessor {
public:
    void decode();
};

#endif // BASEPROCESSORDECODER
