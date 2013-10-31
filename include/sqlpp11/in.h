/*
 * Copyright (c) 2013, Roland Bock
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SQLPP_IN_H
#define SQLPP_IN_H

#include <sstream>
#include <sqlpp11/type_traits.h>
#include <sqlpp11/detail/set.h>

namespace sqlpp
{
	namespace detail
	{
		template<bool not_inverted, typename Operand, typename... Args>
		struct in_t: public Operand::_value_type::template operators<in_t<not_inverted, Operand, Args...>>
		{
			static constexpr bool inverted = not not_inverted;
			static_assert(sizeof...(Args) > 0, "in() requires at least one argument");

			struct _value_type: public Operand::_value_type::_base_value_type
			{
				using _is_named_expression = std::true_type;
			};

			struct _name_t
			{
				static constexpr const char* _get_name() { return inverted ? "NOT IN" : "IN"; }
				template<typename T>
					struct _member_t
					{
						T in;
					};
			};

			in_t(const Operand& operand, const Args&... args):
				_operand(operand),
				_args(args...)
			{}

			in_t(Operand&& operand, Args&&... args):
				_operand(std::move(operand)),
				_args(std::move(args...))
			{}

			in_t(const in_t&) = default;
			in_t(in_t&&) = default;
			in_t& operator=(const in_t&) = default;
			in_t& operator=(in_t&&) = default;
			~in_t() = default;

			template<typename Db>
				void serialize(std::ostream& os, Db& db) const
				{
					_operand.serialize(os, db);
					os << (inverted ? " NOT IN(" : " IN(");
					detail::serialize_tuple(os, db, _args, ',');
					os << ")";
				}

		private:
			Operand _operand;
			std::tuple<Args...> _args;
		};
	}
}

#endif