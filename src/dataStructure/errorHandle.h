#ifndef ERRORHANDLE_H
#define ERRORHANDLE_H

enum errorType{overFlow=0,
              underFlow,
              rangeError};

void errorMsg(errorType error)
{
    switch(error){
        case overFlow:
        try{
           throw std::overflow_error("memory overflow\n");
        } catch(std::overflow_error err){
            std::cerr << "*********error*************"<<std::endl;
            std::cerr << "error info:"<< err.what()
                      << "file      :"<< __FILE__ << std::endl
                      << "line      :"<< __LINE__ << std::endl
                      << "data " << __DATE__ << " at " << __TIME__<<std::endl;
        }
        break;
    }
}

class errorHandle
{
public:
    errorHandle(errorType error);
private:
    void processOverFlow();

};

errorHandle::errorHandle(errorType error)
{
    errorMsg(error);
}

#endif // ERRORHANDLE_H
