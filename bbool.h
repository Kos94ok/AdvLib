
#define FALSE		0
#define TRUE		1
#define TOGGLE		2
#define toggle		2

class bbool
{
public:
	char val;
	bbool() { val = FALSE; }
	bbool(bool val) { 
		if (!val) { this->val = FALSE; }
		else if (val) { this->val = TRUE; }
	}
	bbool(int val) {
		this->val = (char)val;
	}

	void apply(bool* t) {
		if (val == FALSE) { *t = false; }
		if (val == TRUE) { *t = true; }
		if (val == TOGGLE) { *t = !*t; }
	}
};
