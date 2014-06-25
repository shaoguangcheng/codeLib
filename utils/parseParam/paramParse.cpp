#include "../../src/clpp/parser.hpp"

#include <string>
#include <iostream>

using namespace std;

class param
{
public:
    void getPath(const string &path_){
        path = path_;
    }

    void getFileName(const string &fileName_){
        fileName = fileName_;
    }

    void getNumber(int number_=100){
        number = number_;
    }

    void print(){
        cout << "===============parameters list==================" << endl;
        cout << "path          :            " << this->path << endl;
        cout << "fileName      :            " << this->fileName <<endl;
        cout << "number        :            " << this->number <<endl;
        cout << "=================================================" <<endl;
    }

    void help(){
        cout << "[usage:] parseParam [-p=][--path=]path [-f=]fileName [-n=][number=100]"<<endl;
        exit(0);
    }

private:
    string path;
    string fileName;
    int number;
};

int main(int argc,char* argv[])
{
    bool isOk = 1;
    clpp::command_line_parameters_parser parser;
    param pa;

    try{
        parser.add_parameter("-h","--help",&pa,&param::help);
        parser.add_parameter("-p","--path",&pa,&param::getPath)
//                .necessary()
                .check_semantic(clpp::path)
                .order(1);
        parser.add_parameter("-f","--fileName",&pa,&param::getFileName)
//                .necessary()
                .order(2);
        parser.add_parameter("-n","--number",&pa,&param::getNumber)
                .default_value(100)
               .order(3);

        parser.parse(argc,argv);
    } catch(const std::exception &exc){
        cerr << exc.what() <<endl;
        isOk = 0;
    }

    if(isOk)
        pa.print();

    return 0;
}
