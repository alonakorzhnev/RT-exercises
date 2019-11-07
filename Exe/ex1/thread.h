#include <pthread.h>
#include <stdexcept>
using namespace std;

class ThreadException
{
    public:
        ThreadException() : runtime_error("Generic error") {}
};

void* secret_function(void* data);

class Thread
{
    public:
        virtual void run() = 0;
        void start() {
            int return_value = ptheread_create(&pid, NULL, secret_function, this);
            if(return_value != 0)
            {
                throw new ThreadException();
            }
        }

        void join() {
            int return_value = pthread_join(pid, NULL);
            if(return_value != 0)
            {
                throw new ThreadException();
            }
        }

        Thread() { }
        virtual ~Thread() {}

    protected:
        pthread_t pid;
};

void* secret_function(void* data)
{
    Thread* t = (Thread*)data;
    data->run();
}