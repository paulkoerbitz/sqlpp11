/*
 * Copyright (c) 2013, Roland Bock
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "TabSample.h"
#include "MockDb.h"
#include "is_regular.h"
#include <sqlpp11/select.h>
#include <sqlpp11/functions.h>
#include <sqlpp11/connection.h>

#include <iostream>

DbMock db = {};

int main()
{
	TabSample t;
	TabFoo f; 

	// Test a table
	{
		using T = decltype(t);
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test an alias of table
	{
		using T = decltype(t.as(sqlpp::alias::a));
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test an integral column of an alias of table
	{
		using T = decltype(t.as(sqlpp::alias::a).alpha);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}


	// Test an integral table column
	{
		using T = decltype(t.alpha);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a floating point table column
	{
		using T = decltype(f.omega);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a an alias of a numeric table column
	{
		using T = decltype(t.alpha.as(sqlpp::alias::a));
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a select of a single column without a from
	{
		using T = decltype(select(t.alpha)); // Hint: The current rule is pretty crude (a from is required), but certainly better than nothing
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a select of a single numeric table column
	{
		using T = decltype(select(t.alpha).from(t));
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a select of an alias of a single numeric table column
	{
		using T = decltype(select(t.alpha.as(sqlpp::alias::a)).from(t));
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test an alias of a select of a single numeric table column
	{
		using T = decltype(select(t.alpha).from(t).as(sqlpp::alias::b));
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "red to not be boolean");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test the column of an alias of a select of an alias of a single numeric table column
	{
		using T = decltype(select(t.alpha.as(sqlpp::alias::a)).from(t).as(sqlpp::alias::b));
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test the column of an alias of a select of a single numeric table column
	{
		using T = decltype(select(t.alpha).from(t).as(sqlpp::alias::b).alpha);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test an alias of a select of an alias of a single numeric table column
	{
		using T = decltype(select(t.alpha.as(sqlpp::alias::a)).from(t).as(sqlpp::alias::b).a);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test that select(all_of(tab)) is expanded in select
	{
		auto a = select(all_of(t));
		auto b = select(t.alpha, t.beta, t.gamma);
		//auto c = select(t);
		static_assert(std::is_same<decltype(a), decltype(b)>::value, "all_of(t) has to be expanded by select()");
		//static_assert(std::is_same<decltype(b), decltype(c)>::value, "t has to be expanded by select()");
	}

	// Test that select(all_of(tab)) is expanded in multi_column
	{
		auto a = multi_column(sqlpp::alias::a, all_of(t));
		auto b = multi_column(sqlpp::alias::a, t.alpha, t.beta, t.gamma);
		static_assert(std::is_same<decltype(a), decltype(b)>::value, "all_of(t) has to be expanded by multi_column");
	}

	// Test that select(tab) is expanded in multi_column
	{
		auto a = multi_column(sqlpp::alias::a, all_of(t));
		auto b = multi_column(sqlpp::alias::a, t.alpha, t.beta, t.gamma);
		static_assert(std::is_same<decltype(a), decltype(b)>::value, "t has to be expanded by multi_column");
	}

	// Test that a multicolumn is not a value
	{
		auto m = multi_column(sqlpp::alias::a, t.alpha, t.beta);
		auto a = select(m).from(t).as(sqlpp::alias::b).a;
		static_assert(not sqlpp::is_value_t<decltype(a)>::value, "a multi_column is not a value");
	}

	// Test that result sets with identical name/value combinations have identical types
	{
		auto a = select(t.alpha);
		auto b = select(f.epsilon.as(t.alpha));
		using A = typename decltype(a)::_result_row_t;
		using B = typename decltype(b)::_result_row_t;
		static_assert(std::is_same<
				decltype(t.alpha)::_value_type::_base_value_type, 
				decltype(f.epsilon)::_value_type::_base_value_type>::value, "Two bigint columns must have identical base_value_type");
		static_assert(std::is_same<A, B>::value, "select with identical columns(name/value_type) need to have identical result_types");
		static_assert(sqlpp::is_regular<A>::value, "type requirement");
		static_assert(sqlpp::is_regular<B>::value, "type requirement");
	}

	{
		auto s = dynamic_select(db, all_of(t)).dynamic_from().dynamic_where().dynamic_limit().dynamic_offset();
		s = s.add_from(t);
		s = s.add_where(t.alpha > 7 and t.alpha == any(select(t.alpha).from(t).where(t.alpha < 3)));
		s = s.set_limit(30);
		s = s.set_limit(3);
		std::cerr << "------------------------\n";
		s.serialize(std::cerr, db);
		std::cerr << "------------------------\n";
		using T = decltype(s);
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test that select can be called with zero columns if it is used with dynamic columns.
	{
		auto s = dynamic_select(db).dynamic_columns().add_column(t.alpha);
		s.serialize(std::cerr, db); std::cerr << "\n";
	}

	// Test that verbatim_table compiles
	{
		auto s = select(t.alpha).from(sqlpp::verbatim_table("my_unknown_table"));
		s.serialize(std::cerr, db); std::cerr << "\n";
	}


	static_assert(sqlpp::is_select_flag_t<decltype(sqlpp::all)>::value, "sqlpp::all has to be a select_flag");
  using T = sqlpp::detail::wrap_operand<int>::type;
	static_assert(sqlpp::is_regular<T>::value, "type requirement");
	static_assert(T::_is_expression, "T has to be an expression");
	static_assert(std::is_same<typename T::_value_type::_is_numeric, std::true_type>::value, "T has to be a numeric");
	static_assert(sqlpp::is_numeric_t<T>::value, "T has to be a numeric");
	static_assert(sqlpp::is_numeric_t<decltype(t.alpha)>::value, "TabSample.alpha has to be a numeric");
	((t.alpha + 7) + 4).asc();
	static_assert(sqlpp::is_boolean_t<decltype(t.gamma == t.gamma)>::value, "Comparison expression have to be boolean");
	auto x = (t.gamma == true) and (t.alpha == 7);
	auto y = t.gamma and true and t.gamma;
	!t.gamma;
	t.beta < "kaesekuchen";
	(t.beta + "hallenhalma").serialize(std::cerr, db);
	concat(t.beta, "hallenhalma").serialize(std::cerr, db);
	static_assert(sqlpp::must_not_insert_t<decltype(t.alpha)>::value, "alpha must not be inserted");
	t.alpha.serialize(std::cerr, db);
	std::cerr << "\n" << sizeof(TabSample) << std::endl;
	static_assert(std::is_same<typename decltype(t.alpha)::_value_type::_is_named_expression, std::true_type>::value, "alpha should be a named expression");
	static_assert(sqlpp::is_named_expression_t<decltype(t.alpha)>::value, "alpha should be a named expression");
	static_assert(sqlpp::is_named_expression_t<decltype(t.alpha.as(sqlpp::alias::a))>::value, "an alias of alpha should be a named expression");
	static_assert(sqlpp::is_alias_t<decltype(t.alpha.as(sqlpp::alias::a))>::value, "an alias of alpha should be an alias");
	auto z = select(t.alpha) == 7;
	auto l = t.as(sqlpp::alias::left);
	auto r = select(t.gamma.as(sqlpp::alias::a)).from(t).where(t.gamma == true).as(sqlpp::alias::right);
	static_assert(sqlpp::is_boolean_t<decltype(select(t.gamma).from(t))>::value, "select(bool) has to be a bool");
	select(sqlpp::distinct, sqlpp::straight_join, l.alpha, l.beta, select(r.a).from(r))
		.from(l, r)
		.where(t.beta == "hello world" and select(t.gamma).from(t))// .as(sqlpp::alias::right))
		.group_by(l.gamma, r.a)
		.having(r.a != true)
		.order_by(l.beta.asc())
		.limit(17)
		.offset(3)
		.as(sqlpp::alias::a)
		.serialize(std::cerr, db);

	return 0;
}
