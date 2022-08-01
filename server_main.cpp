#include <iostream>
#include "server/ctrlhilos.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Uso: ./dune_server servicename" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        CtrlHilos ctrlHilos(argv[1]);
        ctrlHilos.run();
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch(...) {
        std::cerr << "Error Desconocido en main." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
