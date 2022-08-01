#include <iostream>
#include <QtWidgets>
#include "src_editor/editor.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Editor editor;
    editor.show();
    return app.exec();
}
