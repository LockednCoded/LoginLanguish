#include "compatibility_utils.h"

std::string getResourcesPath()
{
#ifdef __APPLE__
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
	char path[PATH_MAX];
	if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
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