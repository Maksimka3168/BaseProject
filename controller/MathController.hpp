#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class MathController : public oatpp::web::server::api::ApiController {
private:
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

    ResultDto::Wrapper createDto(Float32 a, Float32 b, Float32 result) {
        ResultDto::Wrapper dto = ResultDto::createShared();
        dto->value = a + b;
        dto->message = "Success!";
        dto->arguments = ArgumentsDto::createShared();
        dto->arguments->a = a;
        dto->arguments->b = b;

        return dto;
    };
public:
	MathController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		: oatpp::web::server::api::ApiController(objectMapper)
	{ }


    ENDPOINT_INFO(sum) {
        info->tags = std::list<oatpp::String>{ "Math" };
        info->summary = "Sum of two numbers";
        info->description = "Complete description of sum";
        std::string header = "<b>Title</b>";
        std::string block1 = "<div>div</div>";
        info->description = header + block1; 

        info->queryParams["a"].description = "First param of sum";
    }
	ENDPOINT("GET", "/math/sum", sum, QUERY(Float32, a, "a"), QUERY(Float32, b, "b")) {
        return ResponseFactory::createResponse(Status::CODE_200, createDto(a, b, a + b), objectMapper);
	}
    ENDPOINT_INFO(substract) {
        info->tags = std::list<oatpp::String>{ "Math" };
        info->summary = "Substract of two numbers";
    }
    ENDPOINT("GET", "/math/substract", substract, QUERY(Float32, a, "a"), QUERY(Float32, b, "b")) {
        return ResponseFactory::createResponse(Status::CODE_200, createDto(a, b, a - b), objectMapper);
    }
    ENDPOINT_INFO(multiply) {
        info->tags = std::list<oatpp::String>{ "Math" };
        info->summary = "Multiply of two numbers";
    }
    ENDPOINT("GET", "/math/multiply", multiply, QUERY(Float32, a, "a"), QUERY(Float32, b, "b")) {
        return ResponseFactory::createResponse(Status::CODE_200, createDto(a, b, a * b), objectMapper);
    }
    ENDPOINT_INFO(divide) {
        info->tags = std::list<oatpp::String>{ "Math" };
        info->summary = "Divide of two numbers";
    }
    ENDPOINT("GET", "/math/divide", divide, QUERY(Float32, a, "a"), QUERY(Float32, b, "b")) {
        return ResponseFactory::createResponse(Status::CODE_200, createDto(a, b, a / b), objectMapper);
    }

};

#include OATPP_CODEGEN_END(ApiController)