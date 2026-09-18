#define WIN32_LEAN_AND_MEAN

#ifdef THALRIN_EXPORTS
#define THALRIN_API __declspec(dllexport)
#else
#define THALRIN_API __declspec(dllimport)
#endif