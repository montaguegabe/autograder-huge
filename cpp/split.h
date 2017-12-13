//
//  split.h
//  NANDFast
//
//  Created by Gabe Montague on 11/22/17.
//  Copyright © 2017 Gabe Montague. All rights reserved.
//

#ifndef split_h
#define split_h

template<typename Out>
void split(const std::string &s, char delim, Out result) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

#endif /* split_h */
