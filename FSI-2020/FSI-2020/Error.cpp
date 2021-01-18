#include "stdafx.h"
#include "Error.h"

//��� 114
namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[SYS] ������������ ��� ������"),
		ERROR_ENTRY(1, "[SYS] ��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[SYS] �������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "[SYS] ��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "[SYS] ������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "[SYS] ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "[SYS] ������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113, "[LEX] �������� ������ ��������������"),
		ERROR_ENTRY(114, "[LEX] �������������� ��� ��������������"),
		ERROR_ENTRY(115, "[LEX] ���� ��������� �� ������� ��� ��������� ������� ������. ��������, �� ������ �������� '}'"),
		ERROR_ENTRY(116, "[LEX] ���� ��������� ������� ��� ������� ������. ��������, �� �������� ������ '}'"),
		ERROR_ENTRY(117, "[LEX] �������� ���������� ������ ��������"),
		ERROR_ENTRY(118, "[LEX] ������� �� ����� ���� ������"),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190), ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY(400, "[SEM] ��������� ������� ��������� ���������������"),
		ERROR_ENTRY(401, "[SEM] ��� ����� �����"),
		ERROR_ENTRY(402, "[SEM] pelagus(main) ������ ���� ������ ����"),
		ERROR_ENTRY(403, "[SEM] ��������������� ��������������"),
		ERROR_ENTRY(404, "[SEM] ������ ������������� ����"),
		ERROR_ENTRY(405, "[SEM] �������� ����������� ���������� �������"),
		ERROR_ENTRY(406, "[SEM] ������ � �������� ��������� ��� �����"),
		ERROR_ENTRY(407, "[SEM] �������� ��� ��������� � ������� quadrum"),
		ERROR_ENTRY(408, "[SEM] �������� ��� ��������� � ������� transformatio"),
		ERROR_ENTRY(409, "[SEM] �������� ���� ���������� � ���������� �������"),
		ERROR_ENTRY(410, "[SEM] ����� ������� �� ����"),
		ERROR_ENTRY(411, "[SEM] ������� ������������ �� ���������������� ����"),
		ERROR_ENTRY(412, "[SEM] ��������� ������������� �������� ����� ���� ������ ������������� ���������� ��� �������"),
		ERROR_ENTRY(413, "[SEM] ��� �������������� �� ����� ��������� � �����"),
		ERROR_ENTRY_NODEF(414), ERROR_ENTRY_NODEF(415),
		ERROR_ENTRY_NODEF(416), ERROR_ENTRY_NODEF(417), ERROR_ENTRY_NODEF(418), ERROR_ENTRY_NODEF(419), ERROR_ENTRY_NODEF10(420), ERROR_ENTRY_NODEF10(430), ERROR_ENTRY_NODEF10(440),ERROR_ENTRY_NODEF10(450),ERROR_ENTRY_NODEF10(460), ERROR_ENTRY_NODEF10(470), ERROR_ENTRY_NODEF10(480), ERROR_ENTRY_NODEF10(490),
		ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[SYN] �������� ��������� ���������"),
		ERROR_ENTRY(601, "[SYN] ��������� ��������"),
		ERROR_ENTRY(602, "[SYN] ������ � ���������"),
		ERROR_ENTRY(603, "[SYN] ������ � ���������� ���������"),
		ERROR_ENTRY(604, "[SYN] ������ � ���������� �������"),
		ERROR_ENTRY(605, "[SYN] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(606, "[SYN] �������������� ������"),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY) {
			return errors[0];
		}
		return errors[id];
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY) {
			return errors[0];
		}
		ERROR err = errors[id];
		err.inext.line = line;
		err.inext.col = col;
		return err;
	}
};