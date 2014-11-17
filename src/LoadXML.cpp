#include "LoadXML.h"

#include "../src/pugicast.h"
#include <iostream>

std::string xmlName;
std::string pngName;

bool LoadFromXML()
{
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("common1.xml");
	if (!result)
	{
		std::cout << "[Error - Vocations::loadFromXml] Failed to load vocations.xml: " << result.description() << std::endl;
		return false;
	}

	pugi::xml_node node = doc.child("sequence");
	pugi::xml_attribute attr;

	if (!(attr = node.attribute("name")))
	{
		std::cout << "Miss sequence" << std::endl;
		return false;
	}
	xmlName = attr.as_string();
	std::cout << "xmlName: " << xmlName.c_str() << std::endl;

	pugi::xml_node imgNode = node.first_child();
	if (!(attr = imgNode.attribute("savedname")))
	{
		std::cout << "Miss img" << std::endl;
		return false;
	}
	pngName = attr.as_string();
	std::cout << "pngName: " << pngName.c_str() << std::endl;

	pugi::xml_node frameNode = imgNode.next_sibling();
	for (pugi::xml_node childnode = frameNode.first_child(); childnode; childnode = childnode.next_sibling())
	{
		pugi::xml_attribute attrFrame;

		attrFrame = childnode.attribute("name");
		std::string frameName = attrFrame.as_string();

		attrFrame = childnode.attribute("w");
		int w = pugi::cast<int>(attrFrame.value());

		attrFrame = childnode.attribute("h");
		int h = pugi::cast<int>(attrFrame.value());

		attrFrame = childnode.attribute("x");
		int x = pugi::cast<int>(attrFrame.value());

		attrFrame = childnode.attribute("y");
		int y = pugi::cast<int>(attrFrame.value());

		std::cout << "name=" << '"' << frameName.c_str()<<'"';
		std::cout << " w=" << '"' << w << '"';
		std::cout << " h=" << '"' << h << '"';
		std::cout << " x=" << '"' << x << '"';
		std::cout << " y=" << '"' << y << '"';
		std::cout << std::endl;
	}

	return true;
}

bool SaveToplist()
{
	pugi::xml_document doc;

	pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
	decl.append_attribute("version") = "1.0";
	decl.append_attribute("encoding") = "UTF-8";
	

	pugi::xml_node doctype = doc.append_child(pugi::node_doctype);

	pugi::xml_node plist = doc.append_child("plist");
	plist.append_attribute("version") = "1.0";

	pugi::xml_node dict1 = plist.append_child("dict");

	pugi::xml_node key1 = dict1.append_child("key");
	key1.text() = "frames";

	pugi::xml_node dict2 = dict1.append_child("dict");

	pugi::xml_node key2 = dict2.append_child("key");
	key2.text() = "button_collection_001_1.png";

	pugi::xml_node dict3 = dict2.append_child("dict");

	pugi::xml_node key30 = dict3.append_child("key");
	key30.text() = "frame";

	pugi::xml_node string = dict3.append_child("string");
	string.text() = "{{228,223},{19,19}}";


	doc.save_file("common1.plist", "\n");
	return true;
}