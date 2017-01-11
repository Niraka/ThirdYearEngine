/**
A structure for storing a collection of values relating to a particular resource types
usage within the resource module.

@author Nathan */

#ifndef RESOURCE_TYPE_STATS_H
#define RESOURCE_TYPE_STATS_H

struct ResourceTypeStats
{
	unsigned int uiTotalCreated;
	unsigned int uiTotalDeleted;
	unsigned int uiTotalAccess;
};

#endif