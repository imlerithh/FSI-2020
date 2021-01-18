#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>
#include "IT.h"
#include "LT.h"

namespace Gen
{
	struct Gen
	{
		LT::LexTable lexT;
		IT::IdTable idT;
		std::ofstream out;

		Gen(LT::LexTable lexT, IT::IdTable IdT);

		void Head();
		void Constants();
		void Data();
		void Code();
	};
}
