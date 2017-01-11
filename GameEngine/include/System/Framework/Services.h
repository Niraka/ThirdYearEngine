/**
The names of the services.

If a new service is added, its name must be added to this file aswell.

@author Nathan */

#ifndef SERVICES_H
#define SERVICES_H

enum Services
{
	FILE_SYSTEM_WATCHER,       	// System: For receiving and forwarding events occurring within the filesystem
	LOGGER,						// System: For logging information to the console and filesystem
	MODULE_WATCHER,				// System: For detecting and resolving errors within modules
	RESOURCE_CLEANER,			// System: For cleaning unused resources out of the resource module
	RESOURCE_USAGE_TRACKER,		// System: For tracking the usage of a resource within the resource module
};

#endif