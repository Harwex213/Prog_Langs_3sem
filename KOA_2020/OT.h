#pragma once

namespace OT
{
	struct Entry
	{
		
	};

	struct OperationTable
	{
		int maxsize;
		int current_size;
		Entry* table;
	};
}