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

#ifndef SQLPP_SELECT_FWD_H
#define SQLPP_SELECT_FWD_H

#include <sqlpp11/noop_fwd.h>
#include <type_traits>

namespace sqlpp
{
	// select flags
	struct all_t;
	struct distinct_t;
	struct straight_join_t;

	template<typename FlagTuple> struct select_flag_list_t;
	template<typename Database, typename NamedExprTuple> struct select_expression_list_t;

	template<typename Database, typename... TableOrJoin>	struct from_t;

	template<typename Database, typename... Expr>	struct where_t;

	template<typename Database, typename... Expr> struct group_by_t;

	template<typename Database, typename... Expr> struct having_t;

	template<typename Database, typename... Expr> struct order_by_t;

	struct limit_t;

	struct offset_t;

	template<
		typename Db,
		typename Flags = noop,
		typename ExpressionList = noop,
		typename From = noop,
		typename Where = noop,
		typename GroupBy = noop,
		typename Having = noop,
		typename OrderBy = noop,
		typename Limit = noop,
		typename Offset = noop
			>
		struct select_t;
}
#endif
