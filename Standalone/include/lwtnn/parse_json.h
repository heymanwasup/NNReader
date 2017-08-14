// WARNING: this code was copied automatically from
// https://github.com/lwtnn/lwtnn.git (rev v2.2)
// Please don't edit it! To get the latest version, run
// > ./-bash
// from RNNReader/share

#ifndef PARSE_JSON_HH
#define PARSE_JSON_HH

#include "lightweight_network_config.h"

namespace lwt {
  // build feed forward variant
  JSONConfig parse_json(std::istream& json);
  // build graph variant
  GraphConfig parse_json_graph(std::istream& json);
}


#endif
