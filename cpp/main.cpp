//
//  main.cpp
//  NANDFast
//
//  Created by Gabe Montague on 11/22/17.
//  Copyright © 2017 Gabe Montague. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cassert>
#include <vector>
#include <array>

#include "split.h"

using namespace std;

const int INPUTS = 2048;
const int OUTPUTS = 2048;

typedef array<string, 3> Triple;
typedef array<bool, OUTPUTS> OutputT;
typedef array<bool, INPUTS> InputT;

void binaryFromStr(bool* target, const string s) {
  int i = 0;
  for (const auto & c : s) {
    target[i] = c == '1';
    i++;
  }
}

std::string strFromBinary(const bool* source, int len) {
  string result;
  for (int i = 0; i < len; i++) {
    result += source[i] ? '1' : '0';
  }
  return result;
}

bool nand(const bool a, const bool b) {
  return !(a & b);
}

struct Program {
public:
  bool loadFromFile(const string filename) {
    m_triples = Program::readFileTriples(filename);
    return true;
  }
  
  OutputT execute(const InputT x) {
    OutputT result;
    
    string line;
    map<string, bool> mappings;
    
    for (int i = 0; i < INPUTS; i++) {
      string name = "x_" + to_string(i);
      mappings[name] = x[i];
    }
    
    for (const Triple & triple : m_triples) {
      const auto aIt = mappings.find(triple[1]);
      const auto bIt = mappings.find(triple[2]);
      const bool a = aIt == mappings.end() ? 0 : aIt->second;
      const bool b = bIt == mappings.end() ? 0 : bIt->second;
      const bool c = nand(a, b);
      mappings[triple[0]] = c;
    }
    
    for (int i = 0; i < OUTPUTS; i++) {
      string name = "y_" + to_string(i);
      const auto yIt = mappings.find(name);
      const bool y = yIt == mappings.end() ? 0 : yIt->second;
      result[i] = y;
    }
    
    return result;
  }
  
  
private:
  vector<Triple> m_triples;
  
  static vector<Triple> readFileTriples(const string filename) {
    ifstream nandFile(filename);
    
    vector<Triple> p;
    string line;
    while (getline(nandFile, line)) {
      if (line.size() <= 2) {
        continue;
      }
      line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
      auto tokens = split(line, ',');
      assert(tokens.size() == 3);
      Triple t;
      for (int i = 0; i < 3; i++) {
        t[i] = tokens[i];
      }
      p.push_back(t);
    }
    
    return p;
  }
};

int main(int argc, const char * argv[]) {
  
  const string nandFilename = argv[1];
  //const string nandFilename = "/Users/gabemontague/Desktop/Grading/NAND/nand-pl/autograder/simp.nnd";
  const string keyFilename = argv[2];
  //const string keyFilename = "/Users/gabemontague/Desktop/Grading/NAND/nand-pl/autograder/simp.key";
  
  Program p;
  p.loadFromFile(nandFilename);
  
  // Do all simulation
  ifstream keyFile(keyFilename);
  string line;
  int failures = 0;
  int trials = 0;
  while (getline(keyFile, line)) {
    if (line.size() <= 2) {
      continue;
    }
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    const auto io = split(line, ',');
    assert(io.size() == 2);
    const string inputStr = io[0];
    const string desiredOutputStr = io[1];
    
    trials++;
    InputT input;
    OutputT desiredOutput;
    binaryFromStr(&input[0], inputStr);
    binaryFromStr(&desiredOutput[0], desiredOutputStr);
    OutputT actualOutput = p.execute(input);
    
    for (int i = 0; i < OUTPUTS; i++) {
      if (actualOutput[i] != desiredOutput[i]) {
        cout << "FAILED. Input:" << endl;
        cout << inputStr << endl;
        cout << "Expected output:" << endl;
        cout << strFromBinary(&desiredOutput[0], OUTPUTS) << endl;
        cout << "Actual output:" << endl;
        cout << strFromBinary(&actualOutput[0], OUTPUTS) << endl;
        failures++;
        break;
      }
    }
  }
  
  cout << "\nResults:" << endl;
  cout << (trials - failures) << "/" << trials << endl;
}
