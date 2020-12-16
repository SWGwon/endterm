#ifndef FUNCTION_H
#define FUNCTION_H

#include <memory>
#include <getopt.h>
#include <unistd.h>

#include "TSystem.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TGraph.h"

/**
 * @brief functions
 * @date 2020-12-16
 */
namespace Function
{
    void Help();

    bool Parsing(int argc, char * argv[]);

    void MakeOutputGraph(double* x, double* y, int inHistogramNumber);

    void FittingLoop(TH1F* inHistogram, double* inArray, int inHistogramNumber);
}

namespace Option
{
    extern std::string name_input_file;
    extern std::string name_output_file;
}

extern double x[100];
extern double A1[100];
extern double A2[100];


#endif
