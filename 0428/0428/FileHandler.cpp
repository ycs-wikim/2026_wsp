#include "FileHandler.h"

#include <iostream>


BOOL FileHandler::real_file_open(
	WCHAR* path,
	DWORD dAccess,
	DWORD sMode,
	DWORD fAttribte
	)
{
	m_handle = CreateFile(path,
		dAccess,
		sMode,
		NULL,
		CREATE_ALWAYS,
		fAttribte,
		NULL
	);

	/// 파일 생성 점검
	if (FALSE == m_handle.isSetHandle())
	{
		printf("%s : %d error\n", __FUNCTION__, GetLastError());
		return FALSE;
	}

	return TRUE;
}


void FileHandler::CloseFile()
{
	m_handle.closeHandle();
}

BOOL FileHandler::FileOpenNormal(WCHAR* path)
{
	return real_file_open(path, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		FILE_ATTRIBUTE_NORMAL);
}
/*
BOOL FileHandler::FileOpenReadOnly(WCHAR* path)
{
	real_file_open(path, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		FILE_ATTRIBUTE_NORMAL);
}


BOOL FileHandler::FileOpenWriteOnly(WCHAR* path)
{
	real_file_open(path, GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_ATTRIBUTE_NORMAL);
}
*/
