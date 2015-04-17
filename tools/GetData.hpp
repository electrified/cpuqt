#pragma once
// class FinalNode;

class GetData : public FinalNode
{
public:
   uint8_t level;

public:
   void write(std::ofstream* writer) override;
   GetData(uint8_t level);
};
