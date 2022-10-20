#ifndef ANIM_BUILDER_CXXTEST_HPP
#define ANIM_BUILDER_CXXTEST_HPP

#include <cxxtest/TestSuite.h>
#include <fstream>
#include <iostream>
#include <string>

#include "../animation_builder/animation_builder.hpp"

// Mock setup and exec
#define setup() std::ifstream infile; std::string err_msg = ""; Animation* anim = 0;
#define build(FILE) infile.open(FILE); anim = animation_builder::build(&infile, &err_msg);

#define no_error() TS_ASSERT_DIFFERS(anim, nullptr); TS_ASSERT(err_msg == "");
#define build_success(FILE) build(FILE); no_error();

#define error() TS_ASSERT_EQUALS(anim, nullptr); TS_ASSERT(err_msg != "");
#define build_error(FILE, ERROR) build(FILE); error(); TS_ASSERT(err_msg == ERROR);

class AnimationBuilderTestSuite : public CxxTest::TestSuite
{
public:

  void test_build_empty_file() {
    setup();
    build_error("empty.txt", "Usage error: canvas size must be specified\n\tmake sure you include the following command in your animation file\n\tcanvas WIDTH HEIGHT");
  }

  void test_build_no_file() {
    setup();
    build_error("", "System error: file not open");
  }

  void test_invalid_command() {
    setup();

    const char * file_name = "invalid_command.tmp.txt";
    std::ofstream file(file_name);

    // Misspelled command
    file << "convas 255 255\n";
    file.close();
    
    build_error(file_name, "System error: invalid command\n\tcanvas WIDTH HEIGHT\n\tshape NAME TYPE\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");

    std::remove(file_name);
  }

  void test_canvas_usage_errors() {
    // canvas WIDTH HEIGHT
    setup();

    const char * file_name = "canvas_usage_errors.tmp.txt";
    std::ofstream file(file_name);

    // Not enough arguments
    file << "canvas 255\n";
    file.close();
    build_error(file_name, "Usage error: both canvas WIDTH and HEIGHT must be greater than 0\n\tcanvas 255\n\tcanvas WIDTH HEIGHT");


    // Invalid arguments
    file.open(file_name);
    file << "canvas 255 0\n";
    file.close();
    build_error(file_name, "Usage error: both canvas WIDTH and HEIGHT must be greater than 0\n\tcanvas 255 0\n\tcanvas WIDTH HEIGHT");
    
    file.open(file_name);
    file << "canvas -1 255\n";
    file.close();
    build_error(file_name, "Usage error: both canvas WIDTH and HEIGHT must be greater than 0\n\tcanvas -1 255\n\tcanvas WIDTH HEIGHT");
    

    // Repeat command
    file.open(file_name);
    file << "canvas 100 200\n" << "canvas 300 400\n";
    file.close();
    build_error(file_name, "Usage error: specified more than one canvas\n\tcanvas 300 400\n\tcanvas WIDTH HEIGHT");


    // Too many arguments
    file.open(file_name);
    file << "canvas 100 255 20\n";
    file.close();
    build_error(file_name, "Usage error: too many arguments specified\n\tcanvas 100 255 20\n\tcanvas WIDTH HEIGHT");

    std::remove(file_name);
  }

  void test_shape_usage_errors() {
    // shape NAME TYPE
    setup();

    const char * file_name = "shape_usage_errors.tmp.txt";
    std::ofstream file(file_name);

    // Not enough arguments
    file << "shape \n";
    file.close();
    build_error(file_name, "Usage error: shape NAME and TYPE must be specified\n\tshape \n\tshape NAME TYPE");


    // Invalid arguments
    file.open(file_name);
    file << "shape C1 circle\n";
    file.close();
    build_error(file_name, "Usage error: unsupported or unrecognized shape type 'circle'\n\tshape C1 circle\n\tshape NAME TYPE");


    // Duplicate shape name
    file.open(file_name);
    file << "shape S1 rectangle\n";
    file << "shape S1 ellipse\n";
    file.close();
    build_error(file_name, "Usage error: already specified a shape of the same NAME 'S1'\n\tshape S1 ellipse\n\tshape NAME TYPE");


    // Too many arguments
    file.open(file_name);
    file << "shape rect0 rectangle ellipse\n";
    file.close();
    build_error(file_name, "Usage error: too many arguments specified\n\tshape rect0 rectangle ellipse\n\tshape NAME TYPE");

    std::remove(file_name);
  }

  void test_keyframe_usage_errors() {
    // keyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE
    setup();

    const char * file_name = "keyframe_usage_errors.tmp.txt";
    std::ofstream file(file_name);
    // Not enough arguments
    file << "shape rect rectangle\n";
    file << "keyframe \n";
    file.close();
    build_error(file_name, "Usage error: SHAPE_NAME must be specified\n\tkeyframe \n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");

    // Use of undeclared shape
    file.open(file_name);
    file << "keyframe rect 0 0 0 0 0 0 0 0\n";
    file.close();
    build_error(file_name, "Usage error: use of undeclared shape 'rect'\n\tkeyframe rect 0 0 0 0 0 0 0 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");

    // Invalid arguments
    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect -3 0 0 0 0 0 0 0\n";
    file.close();
    build_error(file_name, "Usage error: TICK must be at least 0\n\tkeyframe rect -3 0 0 0 0 0 0 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");


    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 -10 0 0 0 0\n";
    file.close();
    build_error(file_name, "Usage error: WIDTH and HEIGHT must be at least 0\n\tkeyframe rect 0 0 0 -10 0 0 0 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");
    
    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 0 -49 0 0 0\n";
    file.close();
    build_error(file_name, "Usage error: WIDTH and HEIGHT must be at least 0\n\tkeyframe rect 0 0 0 0 -49 0 0 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");


    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 0 0 -34 0 0\n";
    file.close();
    build_error(file_name, "Usage error: RED, GREEN, and BLUE must all be between 0 and 255 (inclusive)\n\tkeyframe rect 0 0 0 0 0 -34 0 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");
    
    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 0 0 256 0 0\n";
    file.close();
    build_error(file_name, "Usage error: RED, GREEN, and BLUE must all be between 0 and 255 (inclusive)\n\tkeyframe rect 0 0 0 0 0 256 0 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");
    
    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 0 0 0 -256 0\n";
    file.close();
    build_error(file_name, "Usage error: RED, GREEN, and BLUE must all be between 0 and 255 (inclusive)\n\tkeyframe rect 0 0 0 0 0 0 -256 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");
    
    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 0 0 0 1000 0\n";
    file.close();
    build_error(file_name, "Usage error: RED, GREEN, and BLUE must all be between 0 and 255 (inclusive)\n\tkeyframe rect 0 0 0 0 0 0 1000 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");

    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 0 0 0 0 -9999\n";
    file.close();
    build_error(file_name, "Usage error: RED, GREEN, and BLUE must all be between 0 and 255 (inclusive)\n\tkeyframe rect 0 0 0 0 0 0 0 -9999\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");
    
    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 0 0 0 0 8888\n";
    file.close();
    build_error(file_name, "Usage error: RED, GREEN, and BLUE must all be between 0 and 255 (inclusive)\n\tkeyframe rect 0 0 0 0 0 0 0 8888\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");


    // Too many arguments
    file.open(file_name);
    file << "shape rect rectangle\n";
    file << "keyframe rect 0 0 0 0 0 0 0 0 0\n";
    file.close();
    build_error(file_name, "Usage error: too many arguments specified\n\tkeyframe rect 0 0 0 0 0 0 0 0 0\n\tkeyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE");

    std::remove(file_name);
  }

};

#endif
