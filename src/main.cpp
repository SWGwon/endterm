#include <iostream>
#include <memory>

#include "TFile.h"

#include "Function.hxx"

int main(int argc, char* argv[])
{
    Function::Parsing(argc, argv);

    std::unique_ptr<TFile> inputFile = std::make_unique<TFile> (Option::name_input_file.c_str());

    TH1F * h1 = (TH1F*)inputFile->Get("h1");
    TH1F * h2 = (TH1F*)inputFile->Get("h2");

    gSystem->Exec("mkdir output");

    Function::FittingLoop(h1, A1, 1);
    Function::MakeOutputGraph(x, A1, 1);
    Function::FittingLoop(h2, A2, 2);
    Function::MakeOutputGraph(x, A2, 2);

    return 0;
}
