struct Table {
	int mult;
	float div;
};

//Prottypes
void set_mult_values(struct Table**, int row, int col);
void set_div_values(struct Table**, int row, int col);
void delete_table(struct Table**, int row, int col);

