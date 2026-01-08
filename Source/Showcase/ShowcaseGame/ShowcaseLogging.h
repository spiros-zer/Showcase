// Spyridon Zervos

#pragma once

#define _SHOWCASE_FUNCTION_NAME_ *(FString(__FUNCTION__))

#define _SHOWCASE_LOG_IMPL_(Object, Category, Verbosity, Format, ...) \
{ \
	UE_LOG( \
		Category, \
		Verbosity, \
		TEXT("%s - %s"), \
		_SHOWCASE_FUNCTION_NAME_, \
		*FString::Printf(Format, ##__VA_ARGS__)); \
}

#define _SHOWCASE_LOG_STATIC_IMPL_(Category, Verbosity, Format, ...) \
{ \
	UE_LOG( \
		Category, \
		Verbosity, \
		TEXT("%s - %s"), \
		_SHOWCASE_FUNCTION_NAME_, \
		*FString::Printf(Format, ##__VA_ARGS__)); \
}

#define SHOWCASE_LOG(Category, Format, ...) \
do { \
	_SHOWCASE_LOG_IMPL_(this, Category, Log, Format, ##__VA_ARGS__) \
} while (0)

#define SHOWCASE_LOG_STATIC(Category, Format, ...) \
do { \
	_SHOWCASE_LOG_STATIC_IMPL_(Category, Log, Format, ##__VA_ARGS__) \
} while (0)

#define SHOWCASE_ERROR(Category, Format, ...) \
do { \
	_SHOWCASE_LOG_IMPL_(this, Category,  Error, Format, ##__VA_ARGS__) \
} while (0)

#define SHOWCASE_ERROR_STATIC(Category, Format, ...) \
do { \
	_SHOWCASE_LOG_STATIC_IMPL_(Category,  Error, Format, ##__VA_ARGS__) \
} while (0)

#define SHOWCASE_VERBOSE(Category, Format, ...) \
do { \
	_SHOWCASE_LOG_IMPL_(this, Category, Verbose, Format, ##__VA_ARGS__) \
} while (0)

#define SHOWCASE_VERBOSE_STATIC(Category, Format, ...) \
do { \
	_SHOWCASE_LOG_STATIC_IMPL_(Category, Verbose, Format, ##__VA_ARGS__) \
} while (0)

#define SHOWCASE_FATAL(Category, Format, ...) \
do { \
	_SHOWCASE_LOG_IMPL_(this, Category, Fatal, Format, ##__VA_ARGS__) \
} while (0)

#define SHOWCASE_FATAL_STATIC(Category, Format, ...) \
do { \
	_SHOWCASE_LOG_STATIC_IMPL_(Category, Fatal, Format, ##__VA_ARGS__) \
} while (0)
