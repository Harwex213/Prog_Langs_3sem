extern "C"
{
	int getmin(int* pointer, int length)
	{
		int min = *pointer;
		for (int i = 1; i < length; i++)
			if (min > pointer[i])
				min = pointer[i];

		return min;
	}


	int getmax(int* pointer, int length)
	{
		int max = *pointer;
		for (int i = 1; i < length; i++)
			if (max < pointer[i])
				max = pointer[i];

		return max;
	}
}