#include "functions.h"

void startPage(string* &directoriesArray, string* &filesArray,
               int &numberOfDirectories, int &numberOfFiles){

directoriesArray = new string[1];
filesArray = new string[1];
struct passwd *user = NULL;
string previousDirectory;
string temp;

uid_t user_id = getuid();
user = getpwuid(user_id);

string direct;

direct = user->pw_dir;

directoryBrowsing(direct, directoriesArray, filesArray, numberOfDirectories, numberOfFiles);
previousDirectory = direct;

}

void mainActions(){
//    directoriesArray = new string[1];
//     filesArray = new string[1];


////            printf("Choose a directory to open\n"
////                   "Enter -1 to exit\n");
//            cout << "Choice a directory to open" << endl << "Enter -1 to exit" << endl;
//            fflush(stdin);
//            rewind(stdin);
//            //cin >> choice;
//           int choice = 3;

//            //scanf("%d", &choice);
//            if (choice == -1) {

//            }
//            depth++;

//            //save previous directory to back to the previous folder


//            temp = directoriesArray[choice];
//           // strncpy(temp, directoriesArray[choice], PATH_MAX);
//            previousDirectory = directoriesArray[choice];
//           // strncpy(previousDirectory, directoriesArray[choice], PATH_MAX);

//            //delete directoriesArray;

//            //delete filesArray;

//            directoriesArray = new string[1];
//            filesArray = new string[1];
////            directoriesArray = (char **) calloc(1, sizeof(char *));
////            directoriesArray[0] = (char *) calloc(PATH_MAX, sizeof(char));
////            filesArray = (char **) calloc(1, sizeof(char *));
////            filesArray[0] = (char *) calloc(PATH_MAX, sizeof(char));

//            numberOfFiles = 0;
//            numberOfDirectories = 0;

//            directoryBrowsing(temp, directoriesArray, filesArray, numberOfDirectories, numberOfFiles);




//        //go to previous folder
//        int i = 0;
//        for (i = previousDirectory.size(); previousDirectory[i] != '/'; i--){
//            previousDirectory[i] = '\0';
//        }
//        previousDirectory[i] = '\0';


//        //delete directoriesArray;


//        //delete filesArray;

//        directoriesArray = new string[1];
//         filesArray = new string[1];
////        directoriesArray = (char **) calloc(1, sizeof(char *));
////        directoriesArray[0] = (char *) calloc(PATH_MAX, sizeof(char));
////        filesArray = (char **) calloc(1, sizeof(char *));
////        filesArray[0] = (char *) calloc(PATH_MAX, sizeof(char));

//        numberOfFiles = 0;
//        numberOfDirectories = 0;

//        directoryBrowsing(previousDirectory, directoriesArray, filesArray, numberOfDirectories, numberOfFiles);

//        //return EXIT_SUCCESS;
}


void displayPermission (int st_mode )
{
    static const char xtbl[10] = "rwxrwxrwx";
    char     amode[10];
    int      i, j;

    for ( i = 0, j = ( 1 << 8 ); i < 9; i++, j >>= 1 )
        amode[i] = ( st_mode&j ) ? xtbl[i]: '-';
    if ( st_mode & S_ISUID )   amode[2]= 's';
    if ( st_mode & S_ISGID )   amode[5]= 's';
    if ( st_mode & S_ISVTX )   amode[8]= 't';
    amode[9]='\0';
    cout << amode;
    //printf ( "%s ",amode );
}

unsigned directoryBrowsing(string introducedDir, string* &directoriesArray, string* &filesArray,
                           int &numberOfDirectories, int &numberOfFiles){
    int accessParameters;
    DIR *dir = NULL;
    string* temp;
    struct dirent *entry = NULL;
    //char pathName[PATH_MAX + 1];
    string pathName;
    mode_t status;
    dir = opendir(introducedDir.c_str());
    if( dir == NULL ) {
        cout << "Error opening " << introducedDir << ":" <<strerror(errno);
        //printf( "Error opening %s: %s", introducedDir, strerror(errno));
        return 0;
    }
    entry = readdir(dir);
    while(entry != NULL) {
        struct stat entryInfo;
        if((strncmp(entry->d_name, ".", PATH_MAX) == 0) || (strncmp(entry->d_name, "..", PATH_MAX) == 0)) {
            entry = readdir(dir);
            continue;
        }
        pathName = introducedDir;
        pathName += "/";
        pathName += entry->d_name;
//        (void)strncpy(pathName, introducedDir, PATH_MAX);
//        (void)strncat(pathName, "/", PATH_MAX);
//        (void)strncat(pathName, entry->d_name, PATH_MAX);
        if(lstat(pathName.c_str(), &entryInfo) == 0) {
            if(S_ISDIR(entryInfo.st_mode)) {
                directoriesArray[numberOfDirectories] = pathName;
                numberOfDirectories++;
                temp = new string[numberOfDirectories + 1];
                for (int i = 0; i < numberOfDirectories; i++) {
                    temp[i] = directoriesArray[i];

                }
                directoriesArray = temp;
                //delete temp;
//                directoriesArray[numberOfDirectories] = strcpy(directoriesArray[numberOfDirectories], pathName);
//                numberOfDirectories++;
//                directoriesArray = (char**)realloc(directoriesArray, (numberOfDirectories + 1)*sizeof(char*));
//                directoriesArray[numberOfDirectories] = (char*)calloc(PATH_MAX, sizeof(char));
//                displayPermission(entryInfo.st_mode);
                 displayPermission(entryInfo.st_mode);
                cout <<"\t" <<pathName << "\t\t\t\n";
                    // printf("\t-d %s\t\t\t\n", pathName);
            }
            else if(S_ISREG(entryInfo.st_mode)) {
                  filesArray[numberOfFiles] = pathName;
                  numberOfFiles++;
                  temp = new string[numberOfFiles + 1];
                  for (int i = 0; i < numberOfFiles; i++) {
                      temp[i] = filesArray[i];
                  }
                  filesArray = temp;
                 // delete temp;
                  displayPermission(entryInfo.st_mode);
                   cout <<"\t" <<pathName << "\t\t\t\n";
//                filesArray[numberOfFiles] = strcpy(filesArray[numberOfFiles], pathName);
//                numberOfFiles++;
//                filesArray = (char**)realloc(filesArray, (numberOfFiles + 1)*sizeof(char*));
//                filesArray[numberOfFiles] = (char*)calloc(PATH_MAX, sizeof(char));
//                displayPermission(entryInfo.st_mode);
//                printf("\t-f %s \n", pathName);
            }
            else if(S_ISLNK(entryInfo.st_mode)) {
                //string targetName;
                char targetName[PATH_MAX + 1];
                if(readlink(pathName.c_str(), targetName, PATH_MAX) != -1) {
                    filesArray[numberOfFiles] = pathName;
                    numberOfFiles++;
                    temp = new string[numberOfFiles + 1];
                    for (int i = 0; i < numberOfFiles; i++) {
                        temp[i] = filesArray[i];
                    }
                    filesArray = temp;
                    //delete temp;
                     cout <<"\t ->" <<pathName << "\t" << targetName << "\n";
                    //displayPermission(entryInfo.st_mode);
                   // printf("\t-l %s -> %s\n", pathName, targetName);
                }
                else {
                    printf("\t%s -> (invalid symbolic link!)\n", pathName);
                }
            }
        }
        else {
            printf("Error statting %s: %s\n", pathName, strerror(errno));
        }
        entry = readdir(dir);
    }
    (void)closedir(dir);
    return 0;
}
