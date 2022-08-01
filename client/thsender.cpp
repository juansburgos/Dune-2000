#include "thsender.h"

ThSender::ThSender(ClientProtocol &cProtocol, ClientQueue &queue, Partida &partida, bool& lostConn) : queue(std::move(queue)),
                                                                                      cProtocol(std::move(cProtocol)),
                                                                                      partida(std::move(partida)),
                                                                                      lostConnection(std::move(lostConn)) {
}

void ThSender::run() {
    while (!partida.isGameEnded()) {
      try {
        std::shared_ptr<CMsg> cMsg = queue.pop();
        cMsg->send(cProtocol);
      } catch (const std::exception &e) {
          lostConnection = true;
          std::cout << "Cierre de conexión" << std::endl;
          break;
      }
    }
}
