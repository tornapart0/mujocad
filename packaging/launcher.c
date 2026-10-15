/* Native macOS bootstrap. CAD and training logic remain Sensible Lang. */
#include <mach-o/dyld.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv) {
 char executable[PATH_MAX], resolved[PATH_MAX], resources[PATH_MAX], python[PATH_MAX], pythonhome[PATH_MAX], packages[PATH_MAX], script[PATH_MAX], searchpath[PATH_MAX*2];
 uint32_t size=sizeof(executable);
 if (_NSGetExecutablePath(executable,&size) || !realpath(executable,resolved)) return 1;
 char *tail=strrchr(resolved,'/'); if(!tail)return 1; *tail=0;
 snprintf(resources,sizeof(resources),"%s/../Resources",resolved);
 snprintf(pythonhome,sizeof(pythonhome),"%s/python",resources);
 snprintf(python,sizeof(python),"%s/bin/python3.11",pythonhome);
 snprintf(packages,sizeof(packages),"%s/site-packages",resources);
 snprintf(script,sizeof(script),"%s/start.py",resources);
 snprintf(searchpath,sizeof(searchpath),"%s/bin:/usr/bin:/bin:/usr/sbin:/sbin",pythonhome);
 setenv("PYTHONHOME",pythonhome,1); setenv("PYTHONPATH",packages,1);
 setenv("PYTHONNOUSERSITE","1",1); setenv("PATH",searchpath,1);
 setenv("OPENBLAS_NUM_THREADS","1",1); setenv("VECLIB_MAXIMUM_THREADS","1",1);
 char **args=calloc(argc+2,sizeof(char*)); if(!args)return 1;
 args[0]=python;args[1]=script;for(int i=1;i<argc;i++)args[i+1]=argv[i];
 execv(python,args);perror("Unable to launch bundled MuJoCoCAD Python");return 1;
}
