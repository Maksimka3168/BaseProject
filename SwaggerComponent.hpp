#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

class SwagerComponent {
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocementInfo)([] {
		oatpp::swagger::DocumentInfo::Builder builder;
		builder.setTitle("Todo Application");
		builder.setDescription("Me first C++ Nackend application");
		builder.setVersion("0.0.1");
		builder.setContactName("Emil and Maksim");
		builder.setContactEmail("proga@mail.ru");
		return builder.build();
		}());

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
		return oatpp::swagger::Resources::loadResources("Dependencies\\oatp-swagger\\include\\oatpp-1.3.0\\bin\\oatpp-swagger\\res");
		}());
};
