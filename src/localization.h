#ifndef localization_h
#define localization_h

#define en_US 0

#ifndef LOCALE
#warning "No locale selected, falling back to en_US"
#define LOCALE en_US
#endif

#if LOCALE == en_US
#define NO_INPUT_FILE_MSG "No input file."
#define ERR_MSG "error:"
#define WRN_MSG "warning:"
#define BITWISE_NOT_ALLOWED "Bitwise operations are not allowed."
#define UNEXPECTED_CHAR "Unexpected character."
#undef LOCALE
#endif

#endif