#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/Types.hpp"
#include "../dto/Todo.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class TodoController : public oatpp::web::server::api::ApiController {
private:
	OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);
	List<Object<TodoDto>> todos = List<Object<TodoDto>>::createShared();

	void checkAuth(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject> authObject) {
		if (authObject->userId == "maksim" && authObject->password == "12345") {
			return;
		}
		else {
			throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401, "Not auth!", {});
		}
	}
public:
	TodoController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		: oatpp::web::server::api::ApiController(objectMapper)
	{
		setDefaultAuthorizationHandler(std::make_shared<oatpp::web::server::handler::BasicAuthorizationHandler>("auth-handler"));
	}
	ENDPOINT_INFO(todosAll) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->addSecurityRequirement("Authorisation required");
	}
	ENDPOINT("GET", "/todo/all", todosAll, 
		AUTHORIZATION(std::shared_ptr < oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)){
		checkAuth(authObject);
		return ResponseFactory::createResponse(Status::CODE_200, todos, objectMapper);
	}
	
	ENDPOINT("GET", "/todo/about", todosAbout) {
		std::string header = "<h1 style=\"color:blue; background: gray\">Todo Controller</h1>";
		std::string list = "<ul><li>create todos</li><li>update todos</li></ul>";

		return ResponseFactory::createResponse(Status::CODE_200, header + list);
	}

	ENDPOINT_INFO(todosOne) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->addSecurityRequirement("Authorisation required");
	}
	ENDPOINT("GET", "/todo/{id}", todosOne, PATH(Int16, id), 
		AUTHORIZATION(std::shared_ptr < oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		if (id >= todos->size()) {
			return ResponseFactory::createResponse(Status::CODE_404, "Заметка не найдена!");
		}
		return ResponseFactory::createResponse(Status::CODE_200, todos[id], objectMapper);
	}

	ENDPOINT_INFO(todosAdd) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->addSecurityRequirement("Authorisation required");
	}
	ENDPOINT("POST", "/todo", todosAdd, BODY_DTO(Object<TodoDto>, todoDto),
		AUTHORIZATION(std::shared_ptr < oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		todos->push_back(todoDto);
		return ResponseFactory::createResponse(Status::CODE_201, todoDto, objectMapper);
	}

	ENDPOINT_INFO(todosUpdate) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->pathParams["id"].description = "Descrription of ID";
		info->addSecurityRequirement("Authorisation required");
	}
	ENDPOINT("PUT", "/todo/{id}", todosUpdate, BODY_DTO(Object<TodoDto>, todoDto), PATH(Int16, id),
		AUTHORIZATION(std::shared_ptr < oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		if (id >= todos->size()) {
			return ResponseFactory::createResponse(Status::CODE_404, "Заметка не найдена!");
		}
		todos[id] = todoDto;

		return ResponseFactory::createResponse(Status::CODE_200, todoDto, objectMapper);
	}

	ENDPOINT_INFO(todosDelete) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->addSecurityRequirement("Authorisation required");
	}
	ENDPOINT("DELETE", "/todo/{id}", todosDelete, PATH(Int16, id), 
		AUTHORIZATION(std::shared_ptr < oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		if (id >= todos->size()) {
			return ResponseFactory::createResponse(Status::CODE_404, "Заметка не найдена!");
		}
		todos->remove(todos[id]);
		return ResponseFactory::createResponse(Status::CODE_204, "");
	}

};

#include OATPP_CODEGEN_END(ApiController)
