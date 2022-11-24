#include <fstream>
#include <iostream>
#include <string>

#include "animation_builder/animation_builder.hpp"
#include "views/svg_view/svg_view.hpp"
#include "views/text_view/text_view.hpp"

using namespace std;

enum OutputType {Text, SVG};

void usage_msg(char* prog_name);

int main(int argc, char* argv[]) {
  OutputType output_type;

  string infile_path;
  ifstream infile;

  string outfile_path;
  ofstream outfile;
  ostream* out = &cout;

  Animation* anim;
  views::View* view;

  string err_msg;

  if (argc == 1 || (argc == 2 && strcmp(argv[1], "-h") == 0) || !(argc == 5 || argc == 7)) {
    usage_msg(argv[0]);
    exit(1);
  }

  int curr_arg = 1;
  if (strcmp(argv[curr_arg++], "-v") != 0) {
    usage_msg(argv[0]);
    exit(1);
  }

  string type_text = argv[curr_arg++];
  to_lower(type_text);
  if (type_text.compare("text") == 0) output_type = Text;
  else if (type_text.compare("svg") == 0) output_type = SVG;
  else {
    usage_msg(argv[0]);
    exit(1);
  }

  if (strcmp(argv[curr_arg++], "-i") != 0) {
    usage_msg(argv[0]);
    exit(1);
  }

  infile_path = argv[curr_arg++];
  infile.open(infile_path, ifstream::in);

  anim = animation_builder::build(&infile, &err_msg);

  if (anim == 0) {
    cout << err_msg << endl;
    return 1;
  }

#ifdef DEBUG
  cout << "Loaded file with 0 errors." << endl;
#endif

  if (argc > 5) {
    if (argc != 7 || strcmp(argv[curr_arg++], "-o") != 0) {
      usage_msg(argv[0]);
      exit(1);
    }

    outfile_path = argv[curr_arg++];
    outfile.open(outfile_path, ofstream::out);
    out = &outfile;
  }


  switch (output_type) {
    case Text:
      view = new views::TextView(*out);
      break;
    case SVG:
      view = new views::SVGView(*out, 100);
      break;
  }

  view->play(anim);

  return 0;
}

void usage_msg(char* prog_name) {
  cout << "usage: " << prog_name << " -v <VIEW> -i <INFILE> [-o <OUTFILE>]" << endl;
  cout << '\t' << "VIEW\ttext, svg" << endl;
}