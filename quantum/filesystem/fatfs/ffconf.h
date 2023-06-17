/*---------------------------------------------------------------------------/
/  Configurations of FatFs Module
/---------------------------------------------------------------------------*/

#define FFCONF_DEF	80286	/* Revision ID */

/*---------------------------------------------------------------------------/
/ Function Configurations
/---------------------------------------------------------------------------*/

#define FF_FS_READONLY	0

#define FF_FS_MINIMIZE	0

#define FF_USE_FIND		0

#define FF_USE_MKFS		0

#define FF_USE_FASTSEEK	0

#define FF_USE_EXPAND	0

#define FF_USE_CHMOD	0

#define FF_USE_LABEL	0

#define FF_USE_FORWARD	0

#define FF_USE_STRFUNC	0
#define FF_PRINT_LLI	1
#define FF_PRINT_FLOAT	1
#define FF_STRF_ENCODE	3
/* FF_USE_STRFUNC switches string functions, f_gets(), f_putc(), f_puts() and
/  f_printf().
/
/   0: Disable. FF_PRINT_LLI, FF_PRINT_FLOAT and FF_STRF_ENCODE have no effect.
/   1: Enable without LF-CRLF conversion.
/   2: Enable with LF-CRLF conversion.
/
/  FF_PRINT_LLI = 1 makes f_printf() support long long argument and FF_PRINT_FLOAT = 1/2
/  makes f_printf() support floating point argument. These features want C99 or later.
/  When FF_LFN_UNICODE >= 1 with LFN enabled, string functions convert the character
/  encoding in it. FF_STRF_ENCODE selects assumption of character encoding ON THE FILE
/  to be read/written via those functions.
/
/   0: ANSI/OEM in current CP
/   1: Unicode in UTF-16LE
/   2: Unicode in UTF-16BE
/   3: Unicode in UTF-8
*/

/*---------------------------------------------------------------------------/
/ Locale and Namespace Configurations
/---------------------------------------------------------------------------*/

#define FF_CODE_PAGE	850
/* This option specifies the OEM code page to be used on the target system.
/  Incorrect code page setting can cause a file open failure.
/
/   437 - U.S.
/   720 - Arabic
/   737 - Greek
/   771 - KBL
/   775 - Baltic
/   850 - Latin 1
/   852 - Latin 2
/   855 - Cyrillic
/   857 - Turkish
/   860 - Portuguese
/   861 - Icelandic
/   862 - Hebrew
/   863 - Canadian French
/   864 - Arabic
/   865 - Nordic
/   866 - Russian
/   869 - Greek 2
/   932 - Japanese (DBCS)
/   936 - Simplified Chinese (DBCS)
/   949 - Korean (DBCS)
/   950 - Traditional Chinese (DBCS)
/     0 - Include all code pages above and configured by f_setcp()
*/

#define FF_USE_LFN		0

#define FF_FS_RPATH		0
/* This option configures support for relative path.
/
/   0: Disable relative path and remove related functions.
/   1: Enable relative path. f_chdir() and f_chdrive() are available.
/   2: f_getcwd() function is available in addition to 1.
*/

/*---------------------------------------------------------------------------/
/ Drive/Volume Configurations
/---------------------------------------------------------------------------*/

#define FF_VOLUMES		1

#define FF_STR_VOLUME_ID	0
#define FF_VOLUME_STRS		"SD"

#define FF_MULTI_PARTITION	0

#define FF_MIN_SS		512
#define FF_MAX_SS		512

#define FF_LBA64		0

#define FF_USE_TRIM		0

/*---------------------------------------------------------------------------/
/ System Configurations
/---------------------------------------------------------------------------*/

#define FF_FS_TINY		1
/* This option switches tiny buffer configuration. (0:Normal or 1:Tiny)
/  At the tiny configuration, size of file object (FIL) is shrinked FF_MAX_SS bytes.
/  Instead of private sector buffer eliminated from the file object, common sector
/  buffer in the filesystem object (FATFS) is used for the file data transfer. */

#define FF_FS_EXFAT		0

#define FF_FS_NORTC		1
#define FF_NORTC_MON	6
#define FF_NORTC_MDAY	17
#define FF_NORTC_YEAR	2023

#define FF_FS_NOFSINFO	0

#define FF_FS_LOCK		0

#define FF_FS_REENTRANT	0
