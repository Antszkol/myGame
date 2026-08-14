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

class game{
    public: 
        game(){};

    private:
        //battle* battlePtr;     // pointer - battle can be null
        setting settings; // reference - settings must exist
};  

/* 
void game::createBattle(){
    
}
*/

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    mainWidget window;
    window.show();

    return app.exec();
}