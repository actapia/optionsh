#include <assert.h>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "twomap.h"

using namespace std;

void test_1() {
  twomap<string,int> m2;
  // Assignment
  m2["albert"] = 72;
  m2["andrew"] = 95;
  m2["stephen"] = m2["albert"];
  m2["arthur"] = 4;
  // Arithmetic (main)
  m2["andrew"] = m2["andrew"] % 5;
  assert(m2["andrew"] == 0);
  m2["andrew"] = m2["andrew"] + m2["arthur"];
  assert(m2["andrew"] == 4);
  m2["andrew"] = 0;
  m2["andrew"] = m2["andrew"] + 5;
  assert(m2["andrew"] == 5);
  m2["andrew"] = m2["andrew"] + m2["stephen"];
  assert(m2["andrew"] == 77);
  m2["andrew"] = 5;
  m2["andrew"] = m2["andrew"] - 2;
  assert(m2["andrew"] == 3);
  m2["andrew"] = m2["andrew"] - m2["arthur"];
  assert(m2["andrew"] == -1);
  m2["andrew"] = 3;
  m2["andrew"] = m2["andrew"]/2;
  assert(m2["andrew"] == 1);
  m2["andrew"] = 36;
  m2["andrew"] = m2["andrew"]/m2["arthur"];
  assert(m2["andrew"] == 9);
  m2["andrew"] = 36;
  // Comparison
  assert(m2["andrew"] == 36);
  assert(m2["andrew"] == m2["andrew"]);
  assert(m2["andrew"] != 10);
  assert(m2["andrew"] != m2["stephen"]);  
  assert(m2["andrew"] < 37);
  assert(m2["andrew"] < m2["stephen"]);
  assert(m2["andrew"] > 35);
  assert(m2["andrew"] > m2["arthur"]);
  assert(m2["andrew"] <= 36);
  assert(m2["andrew"] <= 37);
  assert(m2["andrew"] <= m2["andrew"]);
  assert(m2["andrew"] <= m2["albert"]);
  assert(m2["andrew"] >= 36);
  assert(m2["andrew"] >= 35);
  assert(m2["andrew"] >= m2["andrew"]);
  assert(m2["andrew"] >= m2["arthur"]);
  // Arithmetic (increment, decrement);
  assert(m2["andrew"]++ == 36);
  assert(m2["andrew"] == 37);
  assert(m2.find(37)->second == "andrew");
  assert(m2["andrew"]-- == 37);
  assert(m2["andrew"] == 36);
  assert(m2.find(36)->second == "andrew");
  assert(++m2["andrew"] == 37);
  assert(m2["andrew"] == 37);
  assert(m2.find(37)->second == "andrew");
  assert(--m2["andrew"] == 36);
  assert(m2["andrew"] == 36);
  assert(m2.find(36)->second == "andrew");
  // Compound
  m2["andrew"]+=10;
  assert(m2["andrew"] == 46);
  m2["andrew"]+=m2["arthur"];
  assert(m2["andrew"] == 50);
  m2["andrew"]-=4;
  assert(m2["andrew"] == 46);
  m2["andrew"]-=m2["albert"];
  assert(m2["andrew"] == -26);
  m2["andrew"]*=2;
  assert(m2["andrew"] == -52);
  m2["andrew"]*=m2["arthur"];
  assert(m2["andrew"] == -208);
  m2["andrew"]/=8;
  assert(m2["andrew"] == -26);
  m2["andrew"]/=m2["arthur"];
  assert(m2["andrew"] == -6);
  m2["andrew"]%=4;
  assert(m2["andrew"] == -2);
  m2["andrew"] = 90;
  m2["andrew"]%=m2["stephen"];
  assert(m2["andrew"] == 18);
  // Bitwise
  assert(~m2["stephen"] == ~72);
  assert((m2["stephen"] & 30) == (72 & 30));
  assert((m2["stephen"] & m2["arthur"]) == (72 & 4));
  assert((m2["stephen"] | 33) == (72 | 33));
  assert((m2["stephen"] | m2["arthur"]) == (72 | 4));
  assert((m2["stephen"] ^ 36) == (72 ^ 36));
  assert((m2["stephen"] ^ m2["arthur"]) == (72 ^ 4));
  assert((m2["stephen"] << 3) == (72 << 3));
  assert((m2["stephen"] << m2["arthur"]) == (72 << 4));
  assert((m2["stephen"] >> 3) == (72 >> 3));
  assert((m2["stephen"] >> m2["arthur"]) == (72 >> 4));
  // Compound bitwise
  m2["andrew"]&=9;
  assert(m2["andrew"] == (18 & 9));
  m2["andrew"] = 92;
  m2["andrew"]&=m2["arthur"];
  assert(m2["andrew"] == (92 & 4));
  m2["andrew"] = 33;
  m2["andrew"]|=13;
  assert(m2["andrew"] == (33 | 13));
  m2["andrew"]=5;
  m2["andrew"]|=m2["stephen"];
  assert(m2["andrew"] == (5 | m2["stephen"]));
  m2["andrew"]^=55;
  assert(m2["andrew"] == (77 ^ 55));
  m2["andrew"] = 9;
  m2["andrew"] ^= m2["arthur"];
  assert(m2["andrew"] == (9 ^ 4));
  m2["andrew"] <<= 1;
  assert(m2["andrew"] == (13 << 1));
  m2["andrew"] <<=m2["arthur"];
  assert(m2["andrew"] == (26 << 4));
  m2["andrew"] >>= 1;
  assert(m2["andrew"] == (416 >> 1));
  m2["andrew"] >>= m2["arthur"];
  assert(m2["andrew"] == 13);
  // Yoda
  m2["albert"] = 72;
  m2["andrew"] = 95;
  m2["stephen"] = m2["albert"];
  m2["arthur"] = 4;
  // Yoda arithmetic (main)
  m2["andrew"] = 99 % m2["andrew"];
  assert(m2["andrew"] == 4);
  m2["andrew"] = 40 + m2["andrew"];
  assert(m2["andrew"] == 44);
  m2["andrew"] = 50 - m2["andrew"];
  assert(m2["andrew"] == 6);
  m2["andrew"] = 30/m2["andrew"];
  assert(m2["andrew"] == 5);
  // Yoda comparison
  assert(5 == m2["andrew"]);
  assert(20 != m2["andrew"]);
  assert(4 < m2["andrew"]);
  assert(6 > m2["andrew"]);
  assert(4 <= m2["andrew"]);
  assert(5 <= m2["andrew"]);
  assert(6 >= m2["andrew"]);
  assert(5 >= m2["andrew"]);
  // etc.
  int k = 0;
  k+=m2["andrew"];
  assert(k == 5);
  k-=m2["stephen"];
  assert(k == -67);
  k*=m2["arthur"];
  assert(k == -268);
  k/=m2["albert"];
  assert(k == -3);
  k = 50;
  k%=m2["arthur"];
  assert(k == 2);
  k = 37;
  k&=m2["albert"];
  assert(k == (72 & 37));
  k = 32;
  k|=m2["andrew"];
  assert(k == (5 | 32));
  k = 35;
  k^=m2["stephen"];
  assert(k == (35 ^ 72));
  k = 4;
  k<<=m2["arthur"];
  assert(k == (4 << 4));
  k = 90;
  k>>=m2["arthur"];
  assert(k == (90 >> 4));
  cout << "Forward: " << endl << endl;
  for (auto iter = m2.S_begin(); iter != m2.S_end(); ++iter) {
    cout << iter->first << ", " << iter->second << endl;
  }
  cout << endl << "Inverse: " << endl << endl;
  for (auto iter = m2.T_begin(); iter != m2.T_end(); ++iter) {
    cout << iter->first << ", " << iter->second << endl;
  }
}

void test_2() {
  twomap<string,bool> m;
  m["lexington"] = false;
  m["louisville"] = true;
  m["danville"] = true;
  m["nicholasville"] = false;
  assert(!m["lexington"]);
  assert(!(m["lexington"] && false));
  assert(!(m["lexington"] && m["nicholasville"]));
  assert(!(m["lexington"] && true));
  assert(!(m["lexington"] && m["louisville"]));
  assert(m["louisville"] && true);
  assert(m["louisville"] && m["danville"]);
  assert(!(m["lexington"] || m["nicholasville"]));
  assert(!(m["lexington"] || false));
  assert(m["lexington"] || m["louisville"]);
  assert(m["lexington"] || true);
  assert(m["louisville"] || true);
  assert(m["louisville"] || m["danville"]);
  cout << "Forward: " << endl << endl;
  for (auto iter = m.S_begin(); iter != m.S_end(); ++iter) {
    cout << iter->first << ", " << iter->second << endl;
  }
  cout << endl << "Inverse: " << endl << endl;
  for (auto iter = m.T_begin(); iter != m.T_end(); ++iter) {
    cout << iter->first << ", " << iter->second << endl;
  }
}

void test_3() {
  // Constructor (2)
  vector<pair<int,string>> vec = {make_pair<int,string>(1,"one"),
				  make_pair<int,string>(2,"two"),
				  make_pair<int,string>(3,"three"),
				  make_pair<int,string>(4,"four"),
				  make_pair<int,string>(5,"five"),
				  make_pair<int,string>(6,"six"),
				  make_pair<int,string>(7,"seven")};
  twomap<int,string> m1(vec.begin(),vec.end());
  for (auto it = m1.S_begin(); it != m1.S_end(); ++it) {
    assert(it->second == vec[it->first-1].second);
  }
  for (auto it = m1.T_begin(); it != m1.T_end(); ++it) {
    assert(it->first == vec[it->second-1].second);
  }
  // Constructor (3)
  twomap<int,string> m2(m1);
  for (auto it = m2.S_begin(); it != m2.S_end(); ++it) {
    assert(it->second == vec[it->first-1].second);
  }
  for (auto it = m2.T_begin(); it != m2.T_end(); ++it) {
    assert(it->first == vec[it->second-1].second);
  }
  // Constructor (4)
  twomap<int,string> m3(twomap<int,string>(vec.begin(),vec.end()));
  for (auto it = m3.S_begin(); it != m3.S_end(); ++it) {
    assert(it->second == vec[it->first-1].second);
  }
  for (auto it = m3.T_begin(); it != m3.T_end(); ++it) {
    assert(it->first == vec[it->second-1].second);
  }
  // Constructor (5)
  twomap<int,string> m4({make_pair<int,string>(1,"one"),
			make_pair<int,string>(2,"two"),
			make_pair<int,string>(3,"three"),
			make_pair<int,string>(4,"four"),
			make_pair<int,string>(5,"five"),
			make_pair<int,string>(6,"six"),
			make_pair<int,string>(7,"seven")});
  for (auto it = m4.S_begin(); it != m4.S_end(); ++it) {
    assert(it->second == vec[it->first-1].second);
  }
  for (auto it = m4.T_begin(); it != m4.T_end(); ++it) {
    assert(it->first == vec[it->second-1].second);
  }
  twomap<int,string> m5({make_pair<string,int>("one",1),
			 make_pair<string,int>("two",2),
			 make_pair<string,int>("three",3),
			 make_pair<string,int>("four",4),
			 make_pair<string,int>("five",5),
			 make_pair<string,int>("six",6),
			 make_pair<string,int>("seven",7)});
  for (auto it = m5.S_begin(); it != m5.S_end(); ++it) {
    assert(it->second == vec[it->first-1].second);
  }
  for (auto it = m5.T_begin(); it != m5.T_end(); ++it) {
    assert(it->first == vec[it->second-1].second);
  }
  // = (1)
  twomap<int,string> m6 = m1;
  for (auto it = m6.S_begin(); it != m6.S_end(); ++it) {
    assert(it->second == vec[it->first-1].second);
  }
  for (auto it = m6.T_begin(); it != m6.T_end(); ++it) {
    assert(it->first == vec[it->second-1].second);
  }
  // = (2)
  twomap<int,string> m7 = twomap<int,string>(vec.begin(),vec.end());
  for (auto it = m7.S_begin(); it != m7.S_end(); ++it) {
    assert(it->second == vec[it->first-1].second);
  }
  for (auto it = m7.T_begin(); it != m7.T_end(); ++it) {
    assert(it->first == vec[it->second-1].second);
  }
  // = (3)
  // twomap<int,string> m8 = {make_pair<int,string>(1,"one"),
  // 			   make_pair<int,string>(2,"two"),
  // 			   make_pair<int,string>(3,"three"),
  // 			   make_pair<int,string>(4,"four"),
  // 			   make_pair<int,string>(5,"five"),
  // 			   make_pair<int,string>(6,"six"),
  // 			   make_pair<int,string>(7,"seven")};
  // for (auto it = m8.S_begin(); it != m8.S_end(); ++it) {
  //   assert(it->second == vec[it->first-1].second);
  // }
  // for (auto it = m8.T_begin(); it != m8.T_end(); ++it) {
  //   assert(it->first == vec[it->second-1].second);
  // }
  // Capacity
  twomap<int,string> m9;
  assert(m9.empty());
  m9[0] = "zero";
  assert(!m9.empty());
  m9[1] = "one";
  assert(m9.size() == 2);
  cout << m9.max_size() << endl;
  // Clear
  m9.clear();
  assert(m9.empty());
  assert(m9.size() == 0);
  // Insert
  twomap<int,string> m10;
  auto pair  = std::make_pair<int,string>(12,"twelve");
  auto insert_res = m10.insert(pair);
  assert(insert_res.second);
  assert(insert_res.first.first->first == pair.first);
  assert(insert_res.first.first->second == pair.second);
  assert(insert_res.first.second->first == pair.second);
  assert(insert_res.first.second->second == pair.first);
  assert(m10.find(pair.first)->second == pair.second);
  assert(m10.find(pair.second)->second == pair.first);
  auto insert_bad = m10.insert(std::make_pair<int,string>(12,"dozen"));
  assert(!insert_bad.second);
  assert(insert_bad.first.first->first == pair.first);
  assert(insert_bad.first.first->second == pair.second);
  assert(insert_bad.first.second->first == pair.second);
  assert(insert_bad.first.second->second == pair.first);
  assert(m10.find(pair.first)->second == pair.second);
  assert(m10.find(pair.second)->second == pair.first);
  twomap<int,string> m11;
  auto pair_2 = std::make_pair<string,int>("eleven",11);
  auto insert_res_2 = m11.insert(pair_2);
  assert(insert_res_2.second);
  assert(insert_res_2.first.first->first == pair_2.second);
  assert(insert_res_2.first.first->second == pair_2.first);
  assert(insert_res_2.first.second->first == pair_2.first);
  assert(insert_res_2.first.second->second == pair_2.second);
  assert(m11.find(pair_2.second)->first == pair_2.second);
  assert(m11.find(pair_2.first)->first == pair_2.first);
  auto insert_bad_2 = m11.insert(std::make_pair<string,int>("ten",11));
  assert(!insert_bad_2.second);
  assert(insert_bad_2.first.first->first == pair_2.second);
  assert(insert_bad_2.first.first->second == pair_2.first);
  assert(insert_bad_2.first.second->first == pair_2.first);
  assert(insert_bad_2.first.second->second == pair_2.second);
  assert(m11.find(pair_2.second)->first == pair_2.second);
  assert(m11.find(pair_2.first)->first == pair_2.first);
  // Emplace
  twomap<int,string> m12;
  auto emplace_res = m12.emplace(13,"thirteen");
  assert(emplace_res.second);
  assert(emplace_res.first.first->first == 13);
  assert(emplace_res.first.first->second == "thirteen");
  assert(emplace_res.first.second->first == "thirteen");
  assert(emplace_res.first.second->second == 13);
  assert(m12.find(13)->second == "thirteen");
  assert(m12.find("thirteen")->second == 13);
  auto emplace_bad = m12.emplace(13,"fourteen");
  assert(!emplace_bad.second);
  assert(emplace_bad.first.first->first == 13);
  assert(emplace_bad.first.first->second == "thirteen");
  assert(emplace_bad.first.second->first == "thirteen");
  assert(emplace_bad.first.second->second == 13);
  assert(m12.find(13)->second == "thirteen");
  assert(m12.find("thirteen")->second == 13);
  twomap<int,string> m13;
  auto emplace_res_2 = m13.emplace("fourteen",14);
  assert(emplace_res_2.second);
  assert(emplace_res_2.first.first->first == 14);
  assert(emplace_res_2.first.first->second == "fourteen");
  assert(emplace_res_2.first.second->first == "fourteen");
  assert(emplace_res_2.first.second->second == 14);
  assert(m13.find(14)->second == "fourteen");
  assert(m13.find("fourteen")->second == 14);
  auto emplace_bad_2 = m13.emplace("fifteen",14);
  assert(!emplace_bad_2.second);
  assert(emplace_bad_2.first.first->first == 14);
  assert(emplace_bad_2.first.first->second == "fourteen");
  assert(emplace_bad_2.first.second->first == "fourteen");
  assert(emplace_bad_2.first.second->second == 14);
  assert(m13.find(14)->second == "fourteen");
  assert(m13.find("fourteen")->second == 14);
  // Erase (1)
  twomap<int,string> m14;
  m14.emplace(14,"fourteen");
  m14.emplace(114,"fourteen");
  m14.erase(m14.find(14));
  assert(m14.find(14) == m14.S_end());
  assert(m14.find("fourteen") != m14.T_end());
  assert(m14.find(114) != m14.S_end());
  m14.emplace(14,"fourteen");
  m14.erase(m14.find("fourteen"));
  assert(m14.find("fourteen") != m14.T_end());
  // Erase (2)
  twomap<int,string> m15;
  m15.emplace(15,"fifteen");
  m15.emplace(115,"fifteen");
  m15.emplace(136,"foo");
  auto S_b = m15.S_begin();
  auto S_next = m15.S_begin();
  ++S_next;
  ++S_next;  
  m15.erase(S_b,S_next);
  assert(m15.find(S_next->first) != m15.S_end());
  assert(m15.find(S_next->second) != m15.T_end());
  assert(!m15.empty());
  twomap<int,string> m16;
  m16.emplace(15,"fifteen");
  m16.emplace(115,"fifteen");
  m16.emplace(136,"foo");
  auto T_b = m16.T_begin();
  auto T_next = m16.T_begin();
  ++T_next;
  ++T_next;
  m16.erase(T_b,T_next);
  assert(m16.find(T_next->first) != m16.T_end());
  assert(m16.find(T_next->second) != m16.S_end());
  assert(!m16.empty());
  // Erase (3)
  twomap<int,string> m17;
  m17.emplace(15,"fifteen");
  m17.emplace(115,"fifteen");
  m17.emplace(136,"foo");
  assert(m17.erase(115) == 1);
  assert(m17.erase(115) == 0);
  assert(m17.find(115) == m17.S_end());
  assert(!m17.empty());
  twomap<int,string> m18;
  m18.emplace(15,"fifteen");
  m18.emplace(115,"fifteen");
  m18.emplace(136,"foo");
  assert(m18.erase("fifteen") == 2);
  assert(m18.erase("fifteen") == 0);
  assert(m18.find("fifteen") == m18.T_end());
  assert(!m18.empty());
  // Swap
  vector<std::pair<int,string>> vec_2 = {make_pair<int,string>(8,"eight"),
					 make_pair<int,string>(9,"nine"),
					 make_pair<int,string>(10,"ten"),
					 make_pair<int,string>(11,"eleven"),
					 make_pair<int,string>(12,"twelve"),
					 make_pair<int,string>(13,"thirteen"),
					 make_pair<int,string>(14,"fourteen")};
  twomap<int,string> m19(vec.begin(),vec.end());
  twomap<int,string> m20(vec_2.begin(),vec_2.end());
  m19.swap(m20);
  for (auto it = m20.S_begin(); it != m20.S_end(); ++it) {
    assert(it->second == vec[it->first-1].second);
  }
  for (auto it = m20.T_begin(); it != m20.T_end(); ++it) {
    assert(it->first == vec[it->second-1].second);
  }
  for (auto it = m19.S_begin(); it != m19.S_end(); ++it) {
    assert(it->second == vec_2[it->first-8].second);
  }
  for (auto it = m19.T_begin(); it != m19.T_end(); ++it) {
    assert(it->first == vec_2[it->second-8].second);
  }
  // At (1)
  twomap<int,string> m21;
  try {
    m21.at(5);
    assert(false);
  }
  catch (const std::out_of_range& e) {
  }
  m21[5] = "five";
  m21.at(5) = "six";
  assert(m21[5] == "six");
  assert(m21.at(5) == "six");
  assert(m21.find("six") != m21.T_end());
  // []
  twomap<int,string> m22;
  m22[21] = "twenty-one";
  assert(m22[21] == "twenty-one");
  assert(m22.find("twenty-one") != m22.T_end());
  // count
  twomap<int,string> m23;
  m23.emplace(0,"zero");
  m23.emplace(-1,"negative one");
  m23.emplace(-3,"negative three");
  assert(m23.count(0) == 1);
  assert(m23.count(-2) == 0);
  twomap<int,string> m24;
  m24.emplace(0,"dog");
  m24.emplace(1,"dog");
  m24.emplace(2,"cat");
  m24.emplace(3,"rabbit");
  assert(m24.count("dog") == 2);
  assert(m24.count("cat") == 1);
  assert(m24.count("mouse") == 0);
  // equal_range
  twomap<int,string> m25;
  m25.emplace(0,"dog");
  m25.emplace(1,"dog");
  m25.emplace(2,"cat");
  m25.emplace(3,"rabbit");
  m25.emplace(4,"dog");
  auto S_range = m25.equal_range(2);
  auto S_next_2 = S_range.first;
  ++S_next_2;
  assert(S_next_2 == S_range.second);
  assert(S_range.first->first == 2);
  assert(S_range.first->second == "cat");
  auto T_range = m25.equal_range("dog");
  assert(std::distance(T_range.first,T_range.second) == 3);
  unordered_set<int> T_values;
  for (auto it = T_range.first; it != T_range.second; ++it) {
    T_values.insert(it->second);
  }
  assert(T_values.contains(0));
  assert(T_values.contains(1));
  assert(T_values.contains(4));
  twomap<int,string> m26;
  m26.emplace(0,"dog");
  m26.emplace(1,"dog");
  m26.emplace(2,"cat");
  m26.emplace(3,"rabbit");
  m26.emplace(4,"dog");
  assert(m26 == m25);
  assert(m25 == m26);
  twomap<int,string> m27;
  m27.emplace(0,"dog");
  m27.emplace(1,"dog");
  m27.emplace(2,"cat");
  m27.emplace(3,"rabbit");
  assert(m27 != m26);
  assert(m26 != m27);
}

struct employee {
  string name;
  int id;
};

struct employee_search {
  using is_transparent = void;
  bool operator()(employee const& l, string const& name) const {
    return l.name < name;
  }
  bool operator()(string const& name, employee const& r) const {
    return name < r.name;
  }
  bool operator()(employee const& l, employee const& r) const {
    return l.name < r.name;
  }

};

struct ex_struct {
  int a;
  string b;
};

struct ex_search {
  using is_transparent = void;
  bool operator()(ex_struct const& l, ex_struct const& r) const {
    return l.a < r.a;
  }
  bool operator()(ex_struct const& l, int const& r) const {
    return l.a < r;
  }
  bool operator()(int const& l, ex_struct const& r) const {
    return l < r.a;
  }
};

bool operator==(const employee& lhs, const employee& rhs) {
  return ((lhs.name == rhs.name) && (lhs.id == rhs.id));
}

void test_4() {
  // Transparency testing.
  // S_find
  twomap<employee,int,employee_search> mappy;
  employee dale = {"dale",0};
  employee daniel = {"daniel",1};
  employee david = {"david",2};
  mappy[dale] = 50;
  mappy[daniel] = 100;
  mappy[david] = 30;
  assert(mappy.S_find("dale")->first.name == dale.name);
  assert(mappy.S_find("dale")->first.id == dale.id);
  assert(mappy.S_find("dale")->second == 50);
  // T_find
  twomap<employee,ex_struct,employee_search,ex_search> m2;
  m2[dale] = ex_struct {50,"salad"};
  m2[daniel] = ex_struct {2,"chips"};
  m2[david] = ex_struct {50,"fries"};
  unordered_set<string> fifty_names = {"dale","david"};
  unordered_set<string> fifty_snacks = {"salad", "fries"};
  auto find_result = m2.T_find(50);
  assert(find_result->first.a == 50);
  assert(fifty_snacks.contains(find_result->first.b));
  assert(fifty_names.contains(find_result->second.name));
  // S_count
  assert(mappy.S_count("dale") == 1);
  assert(mappy.S_count("darryl") == 0);
  // T_count
  assert(m2.T_count(50) == 2);
  assert(m2.T_count(2) == 1);
  assert(m2.T_count(0) == 0);
  // S_contains
  assert(mappy.S_contains("dale"));
  assert(mappy.S_contains("daniel"));
  assert(mappy.S_contains("david"));
  assert(!mappy.S_contains("darryl"));
  // T_contains
  assert(m2.T_contains(50));
  assert(m2.T_contains(2));
  assert(!m2.T_contains(3));
  // S_equal_range
  auto S_range = m2.S_equal_range("daniel");
  auto S_next = S_range.first;
  ++S_next;
  assert(S_next == S_range.second);
  assert(S_range.first->first == daniel);
  assert(S_range.first->second.a == 2);
  assert(S_range.first->second.b == "chips");
  // T_equal_range
  auto T_range = m2.T_equal_range(50);
  set<employee,employee_search> T_values;
  set<ex_struct,ex_search> S_values;
  for (auto it = T_range.first; it != T_range.second; ++it) {
    T_values.insert(it->second);
    S_values.insert(it->first);
  }
  assert(T_values.contains(dale));
  assert(T_values.contains(david));
  assert(S_values.contains(ex_struct {50,"salad"}));
  assert(S_values.contains(ex_struct {50,"fries"}));
  assert(!T_values.contains(daniel));
  assert(!S_values.contains(ex_struct {2,"chips"}));
}

int main() {
  test_1();
  cout << endl << endl;
  test_2();
  cout << endl << endl;
  test_3();
  cout << endl << endl;
  test_4();
}
