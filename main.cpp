#include <fstream>
#include <iostream>
#include <string>

#include "animation_builder/animation_builder.hpp"
#include "views/svg_view/svg_view.hpp"
#include "views/text_view/text_view.hpp"

using namespace std;

void usage_msg(char* prog_name);

int main(int argc, char* argv[]) {
  string file_path;
  ifstream infile;

  Animation* anim;
  views::View* view;

  string err_msg;

  if (argc == 1 || argc == 2 && argv[1] == "-h") {
    usage_msg(argv[0]);
    exit(1);
  }

  int curr_arg = 1;
  while (argv[curr_arg]) {
    
  }

  infile.open(file_path, ifstream::in);

  anim = animation_builder::build(&infile, &err_msg);

  if (anim == 0) {
    cout << err_msg << endl;
    return 1;
  }

#ifdef DEBUG
  cout << "Loaded file with 0 errors." << endl;
#endif

  // views::View* view = new views::TextView(cout);
  view = new views::SVGView(cout, 100);

  view->play(anim);

  return 0;
}

void usage_msg(char* prog_name) {
  cout << "usage: " << prog_name << " -v <VIEW> -i <INFILE> [-o <OUTFILE>]" << endl;
  cout << '\t' << "VIEW\ttext, svg" << endl;
}