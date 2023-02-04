#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlApplicationEngine>


class Engine : public QQmlApplicationEngine
{
public:
    static Engine* getInstance()
    {
        static Engine instance;
        return &instance;
    }
    ~Engine()
    {
        //手动销毁单例
    }

private:
    Engine() {}
    Engine(const Engine &) = delete;
    Engine& operator=(const Engine &) = delete;
};

#endif // ENGINE_H
