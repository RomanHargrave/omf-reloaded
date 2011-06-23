#ifndef GLOBAL_OPTIONS_H
#define GLOBAL_OPTIONS_H

class global_options
{
    public:
        global_options();
        virtual ~global_options();
        static global_options * getSingletonPtr();
        int framerate;
        int speed;
        short server_port;
    protected:
    private:
};

#endif // GLOBAL_OPTIONS_H
