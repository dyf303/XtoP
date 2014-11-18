#include "../ext/pugixml.hpp"


bool LoadFromXML(char *fileName);

bool CreateSaveDoc();

bool addPngNode(const char *name, int w, int h, int x, int y);

bool addMataData();

bool SaveToplist();