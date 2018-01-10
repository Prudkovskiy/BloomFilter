#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

class BitSet {
private:
	char* bitarray;
public:
	BitSet() { }
	BitSet(int size) {
		bitarray = new char[size] { 0x00 };
	}

	char* operator [](int n) { return &bitarray[n]; }

	~BitSet() {
		delete[] bitarray;
	}

	BitSet& operator=(BitSet&& tmp)
	{
		bitarray = tmp.bitarray;
		tmp.bitarray = nullptr;
		return *this;
	}
};

class BloomFilter {
private:
	unsigned int M;
	vector<int> primes;
	int m_size;
	int m_numHashes;
	int idxLast;
	BitSet bitarray;

public:
	BloomFilter(int N, double P) {
		M = pow(2, 31) - 1;
		m_size = floor(-N * log2(P) / log(2) + 0.5);
		m_numHashes = floor(-log2(P) + 0.5);
		cout << m_size << " " << m_numHashes << endl;

		if (m_size % 8 == 0) {
			int size = m_size / 8;
			bitarray = BitSet(size);
			idxLast = m_size / 8 - 1;
		}
		else {
			int size = m_size / 8 + 1;
			bitarray = BitSet(size);
			idxLast = m_size / 8;
		}
	}

	void add(unsigned long long int data) {
		for (int i = 0; i < m_numHashes; i++) {
			int prime;
			if (primes.size() >= (i + 1))
				prime = primes[i];
			else
				prime = simple(i + 1);
			int hesh = ((data % M)*(i + 1) % M + prime % M) % M % m_size;

			int idx = hesh / 8;
			int n = hesh % 8;
			
			if (!(*bitarray[idx] & 1 << n))
				*bitarray[idx] ^= (1 << n);
		}
	}

	void show() {
		std::ios::sync_with_stdio(false);
		for (int i = 0; i < idxLast; ++i) {
			for (int idx = 0; idx < 8; ++idx)
				if (*bitarray[i] & 1 << idx) {
					cout << 1;
				}
				else
					cout << 0;
		}
		char LastByte = *bitarray[idxLast];
		int num = m_size % 8;
		if (num == 0) num = 8;
		for (int i = 0; i < num; ++i)
			if (LastByte & 1 << i)
				cout << 1;
			else
				cout << 0;
		cout << endl;
	}

	void possiblyContains(unsigned long long int data) {
		std::ios::sync_with_stdio(false);
		int i;
		for (i = 0; i < m_numHashes; i++) {
			int prime;
			if (primes.size() >= (i + 1))
				prime = primes[i];
			else
				prime = simple(i + 1);
			int hesh = ((data % M)*(i + 1) % M + prime % M) % M % m_size;
			int idx = hesh / 8;
			int n = hesh % 8;
			
			if (!(*bitarray[idx] & 1 << n)) {
				cout << 0 << endl;
				break;
			}
		}
		if (i == m_numHashes)
			cout << 1 << endl;
	}

	int simple(int i) {
		int simpleCount = 0;
		int num = 1;
		int divider;
		while (simpleCount != i) {
			num++;
			divider = 0;
			for (int j = 1; j <= num; j++)
				if (num%j == 0)
					divider++;
			if (divider == 2)
				simpleCount++;
		}
		primes.push_back(num);
		return num;
	}
};


void printing(BloomFilter *bloom, string data, istringstream* ss) {
	std::ios::sync_with_stdio(false);

	(*ss).clear();
	(*ss).str(data);

	string command;
	*ss >> command;

	string key;
	*ss >> key;

	if (command == "add")
		(*bloom).add(stoull(key));

	else if (command == "search")
		(*bloom).possiblyContains(stoull(key));

	else if (command == "print")
		(*bloom).show();

	else if (command != "")
		cout << "error" << endl;

}

int main() {
	std::ios::sync_with_stdio(false);
	string vvod, N = "0", P = "0";
	getline(cin, vvod);
	istringstream ss(vvod);
	while (cin) {
		string set;
		ss >> set;
		ss >> N;
		ss >> P;
		if (set == "set" && N != "" && P != "" && stoi(N) > 0 && stod(P) < 0.6185 && stod(P) > 0)
			break;
		else if (set != "")
			cout << "error" << endl;

		getline(cin, vvod);
		ss.clear();
		ss.str(vvod);
	}
	if (stoi(N) <= 0 || stod(P) <= 0 || stod(P) >= 0.6185)
		return 0;

	BloomFilter a(stoi(N), stod(P));

	getline(cin, vvod);
	while (cin) {
		printing(&a, vvod, &ss);
		getline(cin, vvod);
	}

	return 0;
}
