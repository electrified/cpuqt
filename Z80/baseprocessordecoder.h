#ifndef BASEPROCESSORDECODER
#define BASEPROCESSORDECODER

#include "Z80/BaseProcessor.h"

class BaseProcessorDecoder : public BaseProcessor {
public:
//    using BaseProcessor::BaseProcessor;
    BaseProcessorDecoder(Memory& memory, IO& io) : BaseProcessor::BaseProcessor(memory, io){
    }


    void decode();
};

#endif // BASEPROCESSORDECODER
