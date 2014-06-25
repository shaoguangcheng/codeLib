#include "../src/sys/directory.h"

#include "../src/sys/_io_.h"

using namespace std;

void testGetFiles(const string &path)
{
	vector<string> fileNames;

	csg::getFiles(path,fileNames);

	for(int i=0;i< fileNames.size();i++){
		cout << fileNames[i] << endl;
		PRINT fileNames[i];
	}
}

void testdir()
{
    const char* path= "/home/";
    cout << csg::isDir(path) << endl;
}
int main(int argc,char* argv[])
{
	string path = string(argv[1]);
	testGetFiles(path);

//    testdir();

	return 0;
}
