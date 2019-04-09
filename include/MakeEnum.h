#define SILLY_ENUM_STRINGIFY_IMPL(a) #a
#define SILLY_ENUM_STRINGIFY(a) SILLY_ENUM_STRINGIFY_IMPL(a)

#ifdef DEFINING_ENUM

// 创造实际定义

#	define BEGIN_ENUM(name, ...)                                                                    \
		enum class name __VA_OPT__( : __VA_ARGS__)                                                     \
		{
#	define ENUM(name, ...) name __VA_OPT__(= __VA_ARGS__),
#	define END_ENUM(name)                                                                           \
		}                                                                                              \
		;

DEFINING_ENUM

#	undef BEGIN_ENUM
#	undef ENUM
#	undef END_ENUM

// 定义枚举子信息

#	define BEGIN_ENUM(name, ...)                                                                    \
		template <>                                                                                    \
		struct SillyEnum::Detail::EnumeratorTraitsContainer<name>                                      \
		{                                                                                              \
			using EnumType = name;                                                                       \
			template <EnumType Enumerator>                                                               \
			struct EnumeratorTraits;
#	define ENUM(name, ...)                                                                          \
		template <>                                                                                    \
		struct EnumeratorTraits<EnumType::name>                                                        \
		{                                                                                              \
			static constexpr const char Name[] = SILLY_ENUM_STRINGIFY(name);                             \
		};
#	define END_ENUM(name)                                                                           \
		}                                                                                              \
		;

DEFINING_ENUM

#	undef BEGIN_ENUM
#	undef ENUM
#	undef END_ENUM

// 定义枚举信息

#	define BEGIN_ENUM(name, ...)                                                                    \
		template <>                                                                                    \
		struct SillyEnum::EnumTraits<name> : ::SillyEnum::Detail::EnumeratorTraitsContainer<name>      \
		{                                                                                              \
			using EnumType = name;                                                                       \
			static constexpr const char Name[] = SILLY_ENUM_STRINGIFY(name);                             \
			static constexpr name Enumerators[] = {
#	define ENUM(name, ...) EnumType::name,
#	define END_ENUM(name)                                                                           \
		}                                                                                              \
		;                                                                                              \
		}                                                                                              \
		;

DEFINING_ENUM

#	undef DEFINING_ENUM

#endif

#undef SILLY_ENUM_STRINGIFY_IMPL
#undef SILLY_ENUM_STRINGIFY

#undef BEGIN_ENUM
#undef ENUM
#undef END_ENUM
