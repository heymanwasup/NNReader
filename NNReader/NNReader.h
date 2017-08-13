#ifndef __NNReader_h__
#define __NNReader_h__

#include "lwtnn/LightweightGraph.h"
#include "lwtnn/parse_json.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>

using namespace std;
using namespace lwt;

typedef std::map<std::string, std::map<std::string, double> > input_t;

class NNReader{
  //function members
  public:
    void BookModel(std::string path2json);
    double Evaluate (input_t input);
    double Evaluate ();
    void AddVariable(std::string name, float & variable);

  private:
    input_t TransformInput();

  //data members
  private:
    std::map<std::string, float *> m_variables;
    LightweightGraph * m_graph;
};

#endif
