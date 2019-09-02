#include <dlfcn.h>
#include <stdio.h>

int main()
{
    void *handle;
    void (*runLib)(void);
    char func[32];

    printf("Enter lib: ");
    scanf("%s", func);
    
    handle = dlopen("libN.so", RTLD_LAZY);

    *(void **)(&runLib) = dlsym(handle, func);
    runLib();

    return 0;
}