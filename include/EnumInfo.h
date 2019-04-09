#pragma once

#include <iterator>
#include <type_traits>

namespace SillyEnum
{
	template <typename Enum>
	struct EnumTraits;

	namespace Detail
	{
		template <typename Enum>
		struct EnumeratorTraitsContainer;

		template <typename Enum, std::size_t... I>
		constexpr bool FindEnumeratorImpl(std::string_view const& name, Enum& result,
		                                  std::index_sequence<I...>) noexcept
		{
			return (... || [&] {
				if (EnumTraits<Enum>::template EnumeratorTraits<EnumTraits<Enum>::Enumerators[I]>::Name == name)
				{
					result = EnumTraits<Enum>::Enumerators[I];
					return true;
				}
				return false;
			}());
		}
	} // namespace Detail

	template <typename Enum>
	constexpr bool FindEnumerator(std::string_view const& name, Enum& result) noexcept
	{
		return Detail::FindEnumeratorImpl<Enum>(
		    name, result, std::make_index_sequence<std::size(EnumTraits<Enum>::Enumerators)>{});
	}
} // namespace SillyEnum
