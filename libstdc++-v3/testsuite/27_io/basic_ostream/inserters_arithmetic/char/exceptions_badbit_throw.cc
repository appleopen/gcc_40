// 2003-03-08  Jerry Quinn  <jlquinn@optonline.net>

// Copyright (C) 2003, 2004 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

#include <locale>
#include <sstream>
#include <testsuite_hooks.h>
#include <testsuite_io.h>

// libstdc++/9561
template<typename T>
void test_badbit()
{
  using namespace std;
  bool test __attribute__((unused)) = true;

  locale loc(locale::classic(), new __gnu_test::fail_num_put);
  ostringstream stream("jaylib - champion sound");
  stream.imbue(loc);

  stream.exceptions(ios_base::badbit);
  VERIFY( stream.rdstate() == ios_base::goodbit );

  try 
    {
      T i = T();
      stream << i;
      VERIFY( false );
    }
  catch (const __gnu_test::facet_error&) 
    {
      // stream should set badbit and rethrow facet_error.
      VERIFY( stream.bad() );
      VERIFY( (stream.rdstate() & ios_base::failbit) == 0 );
      VERIFY( !stream.eof() );
    }
  catch (...) 
    {
      VERIFY(false);
    }
}


int main()
{
  test_badbit<bool>();
  test_badbit<short>();
  test_badbit<unsigned short>();
  test_badbit<int>();
  test_badbit<unsigned int>();
  test_badbit<long>();
  test_badbit<unsigned long>();

  test_badbit<float>();
  test_badbit<double>();

  return 0;
}
