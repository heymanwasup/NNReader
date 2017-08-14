// WARNING: this code was copied automatically from
// https://github.com/lwtnn/lwtnn.git (rev v2.2)
// Please don't edit it! To get the latest version, run
// > ./-bash
// from RNNReader/share

#ifndef INPUT_PREPROCESSOR_HH
#define INPUT_PREPROCESSOR_HH

#include "lightweight_network_config.h"
#include "Exceptions.h"

#include <Eigen/Dense>
#include <map>
#include <vector>

namespace lwt {

  using Eigen::VectorXd;
  using Eigen::MatrixXd;

  // use a normal map externally, since these are more common in user
  // code.  TODO: is it worth changing to unordered_map?
  typedef std::map<std::string, double> ValueMap;
  typedef std::vector<std::pair<std::string, double> > ValueVector;
  typedef std::map<std::string, std::vector<double> > VectorMap;

  // ______________________________________________________________________
  // input preprocessor (handles normalization and packing into Eigen)

  class InputPreprocessor
  {
  public:
    InputPreprocessor(const std::vector<Input>& inputs);
    VectorXd operator()(const ValueMap&) const;
  private:
    // input transformations
    VectorXd m_offsets;
    VectorXd m_scales;
    std::vector<std::string> m_names;
  };

  class InputVectorPreprocessor
  {
  public:
    InputVectorPreprocessor(const std::vector<Input>& inputs);
    MatrixXd operator()(const VectorMap&) const;
  private:
    // input transformations
    VectorXd m_offsets;
    VectorXd m_scales;
    std::vector<std::string> m_names;
  };
}

#endif
