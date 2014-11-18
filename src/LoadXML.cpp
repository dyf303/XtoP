#include "LoadXML.h"

#include "../src/pugicast.h"
#include <iostream>
#include <string>

std::string xmlName;
std::string pngName;

pugi::xml_document saveDoc;
pugi::xml_node  dictRoot;
pugi::xml_node  dictFrame;

bool LoadFromXML(char *fileName)
{
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(fileName);
	if (!result)
	{
		std::cout << "Failed to load " <<fileName<<","<< result.description() << std::endl;
		return false;
	}

	xmlName = fileName;

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

		addPngNode(frameName.c_str(), w, h, x, y);
	}
	addMataData();
	return true;
}

bool CreateSaveDoc()
{
	pugi::xml_node decl = saveDoc.prepend_child(pugi::node_declaration);
	decl.append_attribute("version") = "1.0";
	decl.append_attribute("encoding") = "UTF-8";

	pugi::xml_node doctype = saveDoc.append_child(pugi::node_doctype);

	pugi::xml_node plist = saveDoc.append_child("plist");
	plist.append_attribute("version") = "1.0";

	dictRoot = plist.append_child("dict");

	pugi::xml_node keyRoot = dictRoot.append_child("key");
	keyRoot.text() = "frames";

	dictFrame = dictRoot.append_child("dict");

	return true;
}

bool addPngNode(const char *name, int w, int h, int x, int y)
{
	char  buffer[100] = {0};

	pugi::xml_node pngName = dictFrame.append_child("key");
	pngName.text() = name;

	pugi::xml_node dict = dictFrame.append_child("dict");

	pugi::xml_node frame = dict.append_child("key");
	frame.text() = "frame";

	pugi::xml_node string1 = dict.append_child("string");
	sprintf_s(buffer, "{{%d,%d},{%d,%d}}", x, y, w, h);
	string1.text() = buffer;

	pugi::xml_node offset = dict.append_child("key");
	offset.text() = "offset";

	pugi::xml_node string2 = dict.append_child("string");
	sprintf_s(buffer, "{%d,%d}", 0, 0);
	string2.text() = buffer;

	pugi::xml_node rotated = dict.append_child("key");
	rotated.text() = "rotated";

	pugi::xml_node bRotated = dict.append_child(pugi::node_element);
	bRotated.set_name("false");

	pugi::xml_node sourceColorRect = dict.append_child("key");
	sourceColorRect.text() = "sourceColorRect";

	pugi::xml_node string3 = dict.append_child("string");
	sprintf_s(buffer, "{{%d,%d},{%d,%d}}",0,0, w, h);
	string3.text() = buffer;

	pugi::xml_node sourceSize = dict.append_child("key");
	sourceSize.text() = "sourceSize";

	pugi::xml_node string4 = dict.append_child("string");
	sprintf_s(buffer, "{%d,%d}", w, h);
	string4.text() = buffer;

	return true;
}

bool addMataData()
{
	pugi::xml_node metadata = dictRoot.append_child("key");
	metadata.text() = "metadata";

	pugi::xml_node dict = dictRoot.append_child("dict");

	pugi::xml_node format = dict.append_child("key");
	format.text() = "format";

	pugi::xml_node integer = dict.append_child("integer");
	integer.text() = "2";

	pugi::xml_node realTextureFileName = dict.append_child("key");
	realTextureFileName.text() = "realTextureFileName";

	pugi::xml_node string1 = dict.append_child("string");
	string1.text() = pngName.c_str();

	pugi::xml_node size = dict.append_child("key");
	size.text() = "size";

	pugi::xml_node string2 = dict.append_child("string");
	string2.text() = "{1080,142}";

	pugi::xml_node smartupdate = dict.append_child("key");
	smartupdate.text() = "smartupdate";

	pugi::xml_node string3 = dict.append_child("string");
	string3.text() = "$TexturePacker:SmartUpdate:62179c0e5073a06e984ad79313a522b1:5e1dde739c2d39d82324ef3cf1750918:d1a3550a662b1ecb610c18fd661492b9$";

	pugi::xml_node textureFileName = dict.append_child("key");
	textureFileName.text() = "textureFileName";

	pugi::xml_node string4 = dict.append_child("string");
	string4.text() = pngName.c_str();

	return true;
}

bool SaveToplist()
{
	std::basic_string <char>::size_type pos;
	pos = xmlName.find(".");
	xmlName.replace(pos,4, ".plist");
	saveDoc.save_file(xmlName.c_str(), "    ", pugi::format_indent);
	return true;
}