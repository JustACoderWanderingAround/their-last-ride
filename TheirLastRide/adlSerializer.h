#pragma once
#include "json.hpp"
#include "Node.h"
using json = nlohmann::json;

template<typename T>
struct adl_serializer {
	static void to_json(json& j, const T& value) {
		to_json(j, value);
	}
	static void from_json(const json& j, T& value) {
		from_json(j, value);
	}
};