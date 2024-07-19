#ifndef localization_h
#define localization_h

#ifndef LOCALE
#warning "No locale selected, falling back to en_US"
#define LOCALE en_US
#endif

#if LOCALE == en_US
#define NO_INPUT_FILE_MSG "No input file"
#define ERR_MSG "error:"
#define WRN_MSG "warning:"
#define BITWISE_NOT_ALLOWED_MSG "Bitwise operations are not allowed"
#define UNEXPECTED_CHAR_MSG "Unexpected character"
#define FILE_NOT_FOUND_MSG "File not found"
#undef LOCALE
#endif

#endif