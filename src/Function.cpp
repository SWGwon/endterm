#include <iostream>

#include "Function.hxx"

double x[100] = {};
double A1[100] = {};
double A2[100] = {};

namespace Function
{
    void Help()
    {
        std::cout<<"Usage: ./endterm [OPTION]"<<std::endl;
        std::cout<<"  --help, -h                   : show this help message and exit"<<std::endl;
        std::cout<<"  --inputfile, -i [file]       : input files"<<std::endl;
    }

    bool Parsing(int argc, char * argv[])
    {
        int option_index = 0;
        int option = 0;
        struct option options[] = 
        {
            {"help", 0, 0, 'h'},
            {"input", 1, 0, 'i'},
            {"output", 1, 0, 'o'},
            {0,0,0,0}
        };
        if(argc == 1)
        {
            Function::Help();
            return false;
        }
        while((option = getopt_long(argc, argv, "hi:o:", options, &option_index))!=EOF)
        {
            switch(option)
            {
                case 'h' :
                    {
                        Function::Help();
                        return false;
                    }
                case 'i' :
                    {
                        Option::name_input_file = (std::string)optarg;
                        break;
                    }
                case 'o' :
                    {
                        Option::name_output_file = (std::string)optarg;
                        break;
                    }
            }
        }
        return true;
    }

    void MakeOutputGraph(double* x, double* y, int inHistogramNumber)
    {
        std::unique_ptr<TGraph> gr = std::make_unique<TGraph> (100,x,y);
        std::unique_ptr<TCanvas> can = std::make_unique<TCanvas> ();
        gr->SetTitle(Form("A vs M_{pumpkin}, histogram h%d", inHistogramNumber));
        gr->GetXaxis()->SetTitle("pumpkin mass");
        gr->GetYaxis()->SetTitle("A (number of total counts)");
        gr->Draw();
        can->SaveAs(Form("output/graph_%d.pdf", inHistogramNumber));
    }
    void FittingLoop(TH1F* inHistogram, double* inArray, int inHistogramNumber)
    {
        gSystem->Exec(Form("mkdir output/h%d", inHistogramNumber));

        for (int i = 0; i < 100; i++)
        {
            x[i] = i;
            double m = i;
            double sigma = std::pow(m,0.5);

            std::unique_ptr<TF1> fittingFunction = std::make_unique<TF1> ("fittingFunction",Form("[0] + [1]*exp(-0.5*((x-%f)/%f)**2)",m,sigma),0,100);
            fittingFunction->SetParLimits(0,0,100);
            fittingFunction->SetParLimits(1,0,100);
            inHistogram->Fit("fittingFunction","","",0,100);

            inArray[i] = fittingFunction->Integral(0,100) - fittingFunction->GetParameter(0)*100;

            std::unique_ptr<TCanvas> can = std::make_unique<TCanvas> ();
            inHistogram->Draw();
            can->SaveAs(Form("output/h%d/Mass_%d.pdf", inHistogramNumber,i));
        }
    }
}

namespace Option
{
    std::string name_input_file = "";
    std::string name_output_file = "output.root";
}
