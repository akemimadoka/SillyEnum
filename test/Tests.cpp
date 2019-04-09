#include <catch2/catch.hpp>

#include <EnumInfo.h>

#include <iterator>
#include <string_view>

#define ENUM_FOO_DEFINITION                                                                        \
	BEGIN_ENUM(Foo, int)                                                                             \
		ENUM(a)                                                                                        \
		ENUM(b, 10)                                                                                    \
	END_ENUM(Foo)

#define DEFINING_ENUM ENUM_FOO_DEFINITION
#include <MakeEnum.h>

#define ENUM_BAR_DEFINITION                                                                        \
	BEGIN_ENUM(Bar, long long)                                                                       \
		ENUM(a, 1000)                                                                                  \
		ENUM(b)                                                                                        \
		ENUM(c, 100000)                                                                                \
	END_ENUM(Bar)

#define DEFINING_ENUM ENUM_BAR_DEFINITION
#include <MakeEnum.h>

TEST_CASE("SillyEnum", "[EnumGeneration]")
{
	SECTION("Enum test")
	{
		using namespace std::literals::string_view_literals;

		REQUIRE(static_cast<int>(Foo::a) == 0);
		REQUIRE(static_cast<int>(Foo::b) == 10);

		REQUIRE(SillyEnum::EnumTraits<Foo>::Name == "Foo"sv);
		REQUIRE(std::size(SillyEnum::EnumTraits<Foo>::Enumerators) == 2);
		REQUIRE(SillyEnum::EnumTraits<Foo>::EnumeratorTraits<Foo::a>::Name == "a"sv);
		REQUIRE(SillyEnum::EnumTraits<Foo>::EnumeratorTraits<
		            SillyEnum::EnumTraits<Foo>::Enumerators[1]>::Name == "b"sv);

		Foo foundEnumerator;
		REQUIRE(SillyEnum::FindEnumerator<Foo>("a"sv, foundEnumerator));
		REQUIRE(foundEnumerator == Foo::a);
	}
}
