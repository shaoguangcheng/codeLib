#include "directory.h"

bool csg::isDir(const char* dir)
{
    if(dir == NULL)
        return false;

    struct stat statBuf;
    lstat(dir,&statBuf);
    int ret = S_ISDIR(statBuf.st_mode);
    if(ret == 1) return true;

    return false;
}

int csg::pwd(string& path)
{
    char buffer[1024];
    if(getcwd(buffer,sizeof(buffer)) == NULL){
        cout << "directory name is too long\n";
        return -1;
    }

    path = string(buffer);
    return 0;
}

int csg::currentDirectoryName(string& directoryName)
{
    string path;

    csg::pwd(path);
    basic_string<char>::size_type pos = path.find_last_of("/");

    directoryName.resize(path.size()-pos);
    copy(path.begin()+pos+1,path.end(),directoryName.begin());

    return 0;
}

void csg::cd(const string& path)
{
    chdir(path.c_str());
}

int getFiles(const string& path,vector<string>& fileName)
{
    DIR    *dir;
    struct dirent *entry;
    struct stat   stateBuf;

    if((dir = opendir(path.c_str())) == NULL){
        cout << "can not open the directory\n";
        return -1;
    }

    csg::cd(path);

    while((entry = readdir(dir)) != NULL){
        lstat(entry->d_name,&stateBuf);
        if(S_ISDIR(stateBuf.st_mode)){
            if(strcmp(".",entry->d_name) == 0||
                    strcmp("..",entry->d_name) == 0||
                    entry->d_name[0] == '.')         //ignore the hidden folder
                continue;

            getFiles(string(entry->d_name),fileName);
        }

        lstat(entry->d_name,&stateBuf);
        if(entry->d_name[0] != '.'&&!S_ISDIR(stateBuf.st_mode)){
            string p="";
            csg::pwd(p);
            fileName.push_back(p+'/'+string(entry->d_name));
        }
    }

    csg::cd("..");
    closedir(dir);

    return 0;
}
