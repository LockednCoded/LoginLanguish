#include "fields.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

Fields::Fields()
{
	d.SetObject();
}

std::string Fields::updateFieldState(std::string args)
{
	// Do some work
	rapidjson::Document di;
	di.Parse(args.c_str());
	const std::string fieldName = di[0].GetString();
	const std::string fieldValue = di[1].GetString();

	rapidjson::Value key(fieldName.c_str(), d.GetAllocator());
	rapidjson::Value value(fieldValue.c_str(), d.GetAllocator());
	rapidjson::Value error("", d.GetAllocator());

	// add {"value": value, "error": error} to d, or update it if it already exists
	if (d.HasMember(key)) {
		d[key]["value"] = value;
		d[key]["error"] = "";
	}
	else {
		rapidjson::Value obj(rapidjson::kObjectType);
		obj.AddMember("value", value, d.GetAllocator());
		obj.AddMember("error", "", d.GetAllocator());
		d.AddMember(key, obj, d.GetAllocator());
	}

	return "true";
}

std::string Fields::getFieldStates()
{

	std::cout << "Getting field states" << std::endl;

	std::cout << getJSONString() << std::endl;
	return getJSONString();
}
std::string Fields::getJSONString()
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);
	return buffer.GetString();
}