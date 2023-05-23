#include "mylib.h"

string GautiFailoPasirinkima() {

    cout << "\nGalimi failai:" << endl;
    string dirPath = "./";
    for (const auto& i : fs::directory_iterator(dirPath)) {
        if (i.is_regular_file() && i.path().extension() == ".txt") {
            cout << i.path().filename() << endl;
        }
    }
    string failoPasirinkimas;
    cout << "\nIveskite failo, kuri norite nuskaityti, pavadinima: "<< endl;
    cin >> failoPasirinkimas; 

    if (failoPasirinkimas.size() < 4 || failoPasirinkimas.substr(failoPasirinkimas.size() - 4) != ".txt")
        failoPasirinkimas += ".txt";

    return failoPasirinkimas.empty() ? "text.txt" : failoPasirinkimas;
}

bool ArAtsidaro (const string& failoPasirinkimas) {
    ifstream in(failoPasirinkimas);
    return in.good();
}

bool TikrinameArUrl (const string& zodis) {
    regex urlRegex("(https?://|www\\.)[\\w-]+(\\.[\\w-]+)+([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?");
    return regex_match(zodis, urlRegex);
}

string sutvaromeZodi(const string& zodis) {
    regex negrazusZodisRegex("[^\\w]+");
    string grazusZodis = regex_replace(zodis, negrazusZodisRegex, "");
    transform(grazusZodis.begin(), grazusZodis.end(), grazusZodis.begin(), ::tolower);
    return grazusZodis;
}

void pridedameISarasa(const string& zodis, map<string, vector<int>>& sarasas, int eilutesNumeris) {
    if (zodis.empty()) 
        return;

    auto it = sarasas.find(zodis);

    if (it == sarasas.end()) {
        vector<int> eiluciuNr;
        eiluciuNr.push_back(eilutesNumeris);
        sarasas[zodis] = eiluciuNr;
    }
    else {
        vector<int>& eiluciuNr = it->second;
        if (eilutesNumeris != eiluciuNr.back()) {
            eiluciuNr.push_back(eilutesNumeris);
        }
    }
}

void failoSkaitymas(const string& failoPasirinkimas,  map<string, vector<int>>& sarasas, vector<string>& urls) {

    ifstream failas;
    failas.open(failoPasirinkimas);
    stringstream tekstas;
    tekstas << failas.rdbuf();
    failas.close();

    string eilute;
    int eilutesNumeris = 0;
    while(getline(tekstas, eilute)) {
        eilutesNumeris++;
        string zodis;
        istringstream in(eilute);
        while( in >> zodis) {
            bool arYraSkaicius = false; 
            for (char c : zodis) {
                if (isdigit(c)) {
                    arYraSkaicius = true;
                    break;
                }
            }
            if(TikrinameArUrl(zodis)) {
                urls.push_back(zodis);
            }
            else if (!arYraSkaicius) {
                zodis = sutvaromeZodi(zodis);
                pridedameISarasa(zodis, sarasas,eilutesNumeris);
            }
        }
    }
}

void rasymas ( map<string, vector<int>>& sarasas,vector<string> urls) {
    ofstream out("rezultatai.txt");

    if (!out.good()) {
        cout << "Failo nepavyko sukurti." << endl;
        return;
    }

    out << "URLS (" << urls.size() << ")" << endl;
    for (const auto& url : urls)
        out << url << endl;

    out << endl;

    out << "ZODZIU SARASAS" << endl;

   if (!sarasas.empty()) {
        out << left << setw(30) << "ZODIS" << setw(10) << "KIEKIS" << "EILUCIU NR." << endl;

        for (const auto& i : sarasas) {
            if (i.second.size() > 1){
                out << left << setw(30) << i.first << setw(10) << i.second.size();

                for (int j : i.second) {
                    out << setw(4) << j;
                }

            out << endl;
            }
        }
    }

    out.close();
}
  

