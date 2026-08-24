#include <string>
#include <iostream>
#include <fstream>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <nlohmann/json.hpp>

#include "mainWidget.hpp"
#include "settings.hpp"

using namespace std;
using json = nlohmann::json;

class Game{
    public:
        Game(){};

    private:
        //Battle* battlePtr_;     // pointer - battle can be null
        Setting settings_; // reference - settings must exist
};

/*
void Game::createBattle(){

}
*/

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    MainWidget window;
    window.show();

    return app.exec();
}