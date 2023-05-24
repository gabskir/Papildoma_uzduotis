#pragma once
#include "mylib.h"

string GautiFailoPasirinkima();
bool ArAtsidaro (const string& failoPasirinkimas);
bool TikrinameArUrl (const string& zodis);
string sutvaromeZodi(const string& zodis);
void pridedameISarasa(const string& zodis, map<string, vector<int>>& sarasas, int eilutesNumeris);
void failoSkaitymas(const string& failoPasirinkimas,  map<string, vector<int>>& sarasas, vector<string>& urls);
void rasymas (map<string, vector<int>>& sarasas,vector<string> urls);