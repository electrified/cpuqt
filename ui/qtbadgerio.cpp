#include "qtbadgerio.h"

QtBadgerIO::QtBadgerIO() {}

QtBadgerIO::~QtBadgerIO() {}

void QtBadgerIO::outputCharacter(std::uint8_t value) { emit consoleTextOutput(value); }