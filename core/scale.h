#ifndef S
#define S
#include <vector>

using namespace std;

struct Scale{
public:
	Scale();

	vector<Note> noteScale;
	void transport(int);
	int whereIs(Note);
};

#endif // S
