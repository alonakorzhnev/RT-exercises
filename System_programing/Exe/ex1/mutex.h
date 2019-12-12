#include <pthread.h>
#include <stdexcept>
using namespace std;

class MutexException
{
    public:
        MutexException() : runtime_error("Generic error") {}
};

class Mutex
{
    public:
        Mutex() {
            int return_value;
            return_value = pthread_mutex_init(&mutex, NULL);
            if(return_value != 0)
            {
                throw 
            }
        }

    private:
        pthread_mutex_t mutex; 
};