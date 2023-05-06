#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "AppComponent.hpp"
#include "dto/ResultDto.hpp"
#include "dto/HelloDto.hpp"
#include "controller/MathController.hpp"
#include "controller/TodoController.hpp"
#include "oatpp-swagger/Controller.hpp"

class HelloHandler : public oatpp::web::server::HttpRequestHandler {
public:
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        auto list = HelloDto::createShared();

        auto element1 = ElementDto::createShared();
        list->elements = {};
        element1->id = 1;
        element1->name = "Misha";

        auto element2 = ElementDto::createShared();
        element2->id = 2;
        element2->name = "Katya";

        list->elements->push_back(element1);
        list->elements->push_back(element2);

        return ResponseFactory::createResponse(Status::CODE_200, list, objectMapper);
    }
};

class SumHandler : public oatpp::web::server::HttpRequestHandler {
public:
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        auto aPtr = request->getQueryParameter("a").get();
        auto bPtr = request->getQueryParameter("b").get();

        if (aPtr == nullptr || bPtr == nullptr) {
            return ResponseFactory::createResponse(Status::CODE_400, "Не все параметры указаны!");
        }

        float a = atof(aPtr->c_str());
        float b = atof(bPtr->c_str());
        
        auto dto = ResultDto::createShared();
        dto->value = a + b;
        dto->message = "Success!";
        dto->arguments = ArgumentsDto::createShared();
        dto->arguments->a = a;
        dto->arguments->b = b;

        auto response = ResponseFactory::createResponse(Status::CODE_200, dto, objectMapper);

        return response;
        
    }
};


void runServer() {
    AppComponent components;

    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter);
    oatpp::web::server::api::Endpoints docEndpoints;
    docEndpoints.append(httpRouter->addController(std::make_shared<MathController>())->getEndpoints());
    docEndpoints.append(httpRouter->addController(std::make_shared<TodoController>())->getEndpoints());
    httpRouter->addController(oatpp::swagger::Controller::createShared(docEndpoints));
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider);

    oatpp::network::Server server(serverConnectionProvider, serverConnectionHandler);

    OATPP_LOGI("App", "Сервер запущен!");

    server.run();
}



int main() {
    setlocale(LC_CTYPE, "Rus");
    oatpp::base::Environment::init();
    runServer();
    return 0;
}
