/*!
 @file compatibility_utils.cpp
 @brief platform compatibility
 @author Jeb Nicholson
 @copyright 2023 Locked & Coded
*/

#include "compatibility_utils.h"

std::string getResourcesPath()
{
#ifdef __APPLE__
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
	char path[PATH_MAX];
	if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, static_cast<UInt8 *>(static_cast<void *>(path)), PATH_MAX))
	{
		return "";
	}
	CFRelease(resourcesURL);

	return path;
#endif
#ifdef _WIN32
	//----------------------------
	char path[MAX_PATH];
	GetModuleFileName(NULL, path, (sizeof(path)));
	// strip exe name
	std::size_t pos = std::string(path).find_last_of("\\/");
	return std::string(path).substr(0, pos);
#endif
}

char getSeparator()
{
	#ifdef _WIN32
		return '\\';
	#endif
	return '/';
}