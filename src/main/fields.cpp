/*!
	@file fields.cpp
	@brief field state manager
	@author Jeb Nicholson
	@copyright 2023 Locked & Coded
*/

#include "fields.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

/*!
	@brief constructor for Fields
*/
Fields::Fields()
{
	d.SetObject();
}

/*!
	@brief updates field states
	@param args JSON string to update field states with
	@return "true" as a string to indicate update was successful
*/
std::string Fields::updateFieldState(std::string args)
{
	// do some work
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

/*!
	@brief obtains and prints field states
	@return field states as a JSON string
*/
std::string Fields::getFieldStates()
{
	std::cout << "Getting field states" << std::endl;
	std::string jsonStr = getJSONString();
	std::cout << jsonStr << std::endl;
	return jsonStr;
}

/*!
	@brief converts a RapidJSON document into a string
	@return string representation of JSON
*/
std::string Fields::getJSONString()
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);
	return buffer.GetString();
}