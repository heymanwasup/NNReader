#include "NNReader/lwtnn/Exceptions.h"
#include <string>

namespace lwt {

  // ______________________________________________________________________
  // excpetions
  LightweightNNException::LightweightNNException(std::string problem):
    std::logic_error(problem)
  {}
  NNConfigurationException::NNConfigurationException(std::string problem):
    LightweightNNException(problem)
  {}
  NNEvaluationException::NNEvaluationException(std::string problem):
    LightweightNNException(problem)
  {}
}
