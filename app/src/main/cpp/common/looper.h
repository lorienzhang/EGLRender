#include <pthread.h>
#include <semaphore.h>

struct loopermessage;
typedef struct loopermessage loopermessage;

struct loopermessage {
    int what;
    int arg1;
    int arg2;
    void *obj;
    loopermessage *next;
    bool quit;
};

class looper {
    public:
        looper();
        looper& operator=(const looper& ) = delete;
        looper(looper&) = delete;
        virtual ~looper();

        void post(int what, void *data, bool flush = false);
        void post(int what, int arg1, int arg2, bool flush = false);
        void quit();

        virtual void handle(loopermessage *msg);

    private:
        void addmsg(loopermessage *msg, bool flush);
        static void* trampoline(void* p);
        void loop();
        loopermessage *head;
        pthread_t worker;
        sem_t headwriteprotect;
        sem_t headdataavailable;
        bool running;
};
