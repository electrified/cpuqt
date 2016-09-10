#define CATCH_CONFIG_RUNNER

#include "spdlog/spdlog.h"
#include "../Z80/utils.h"
#include <iostream>

// TODO: this doesn't work :(
// https://github.com/philsquared/Catch/blob/master/docs/tostring.md
namespace Catch {
    std::string toString( std::uint8_t const& value ) {
      std::cout << "hallo";  
      return utils::int_to_hex( value );
    }
}

#include "catch.hpp"

int main( int argc, char* const argv[] )
{
  auto console = spdlog::stdout_logger_mt("console");
  console->set_level(spdlog::level::debug);

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return result;
}
