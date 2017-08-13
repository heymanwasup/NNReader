#include "NNReader/NNReader.h"

void NNReader::BookModel(std::string path2json){
  std::ifstream input(path2json.c_str());
  LightweightGraph * graph = new LightweightGraph(parse_json_graph(input), "activation_2_0");
  m_graph = graph;
}

double NNReader::Evaluate (input_t input){
  auto out = m_graph -> compute(input); 
  return out["out_0"];
}

void NNReader::AddVariable(std::string name,float & variable){
  m_variables[name] = & variable;
}

input_t NNReader::TransformInput(){
  std::map<std::string,double> out;
  for(auto item : m_variables){
    out[item.first] = double(*(item.second));
  }
  input_t out_;
  out_["node_0"] = out;
  return out_;
}

double NNReader::Evaluate(){
  return Evaluate(TransformInput());
}

