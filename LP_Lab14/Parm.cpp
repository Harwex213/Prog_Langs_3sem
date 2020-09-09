#include <wchar.h>
#include "Parm.h"
#include "Error.h"

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM sample;			//возвращаемая структура 
		wchar_t* temp_in = NULL;		//временный указатель
		wchar_t* temp_out = NULL;
		wchar_t* temp_log = NULL;

		bool chek_in = false;	//bool переменные для проверки аргументов
		bool chek_out = false;
		bool chek_log = false;

		if (argc > 1)
		{
			for (int i = 1; i < argc; i++)
			{
				if (wcslen(argv[i]) <= PARM_MAX_SIZE)
				{
					if (!chek_in && (temp_in = wcsstr(argv[i], PARM_IN)))
						chek_in = true;

					if (!chek_out && (temp_out = wcsstr(argv[i], PARM_OUT)))
						chek_out = true;

					if (!chek_log && (temp_log = wcsstr(argv[i], PARM_LOG)))
						chek_log = true;
				}
				else
					throw ERROR_THROW(104);
			}

			if (chek_in)
				wcscpy_s(sample.in, (temp_in + wcslen(PARM_IN)));
			else
				throw ERROR_THROW(100);

			if (chek_out)
				wcscpy_s(sample.out, (temp_out + wcslen(PARM_OUT)));
			else
			{
				wcscpy_s(sample.out, sample.in);
				wcscat_s(sample.out, PARM_OUT_DEFAULT_EXT);
			}

			if (chek_log)
				wcscpy_s(sample.log, (temp_log + wcslen(PARM_LOG)));
			else
			{
				wcscpy_s(sample.log, sample.in);
				wcscat_s(sample.log, PARM_LOG_DEFAULT_EXT);
			}

		}
		else
			throw ERROR_THROW(100);

		return sample;
	}
}