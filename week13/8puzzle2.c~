#include <stdio.h>
#include <string.h>
typedef struct state {
	char pos;
	 char board[10];
	 //board[3][3];
} state;

state open[40320],closed[40320];
	int front_o = 0;// tro toi vi tri dau list open
	int rear_o = 0;
	int front_c = 0;// tro toi dau list closed
	int rear_c = 0;
	
void print_state(state s) {
	int i;
	for (i = 0;i< 9;i++)
		if ((i+1) % 3 != 0) printf("%c ",s.board[i]);
		else printf("%c \n",s.board[i]);

}
int path[40320]; // Dung de luu vet duong di

//Tao trang thai moi tu trang thai hien tai
state create_state(state cur,int move) {
	state new = cur;
	char tmp;
	if (move == 0) {//chuyen len
			tmp = cur.board[cur.pos - 3];
			new.board[cur.pos -3] = '0';
			new.board[cur.pos] = tmp;
			new.pos = cur.pos - 3;
		}

	if (move == 1) {//chuyen xuong
			tmp = cur.board[cur.pos + 3];
			new.board[cur.pos + 3] = '0';
			new.board[cur.pos] = tmp;
			new.pos = cur.pos + 3;
		}

	if (move == 2) {//chuyen sang trai
			tmp = cur.board[cur.pos - 1];
			new.board[cur.pos - 1] = '0';
			new.board[cur.pos] = tmp;
			new.pos = cur.pos - 1;
		}

	if (move == 3) {//chuyen sang phai
			tmp = cur.board[cur.pos + 1];
			new.board[cur.pos + 1] = '0';
			new.board[cur.pos] = tmp;
			new.pos = cur.pos + 1;
		}
	return new;
}

int da_co_trong_open(state x) {
	int result = 0;
	int i;
	for (i = front_o;i < rear_o;i++ )
		if (strcmp(open[i].board,x.board) == 0) return 1;
	return result;
}

int da_co_trong_closed(state x) {
	int result = 0;
	int i;
	for (i = 0;i < rear_c;i++ )
		if (strcmp(closed[i].board,x.board) == 0) return 1;
	return result;
}

void ket_qua(int node_id) {
	int i;
	for (i = node_id; i > -1; i = path[i]) 
		{
			print_state(open[i]);
			
			printf("\n");
		}
}

int main() {
	state next_s,start,goal; 
	strcpy(start.board,"123456780");
	start.pos = 8;
	//strcpy(goal.board,"012345678");
	strcpy(goal.board,"013425786");
	open[rear_o++] = start;
	state cur_s;
	int i_da_co_open;
	int i_da_co_closed;
	
	int node_count = 0;
	path[node_count++] = -1;
	while ((rear_o - front_o) != 0) {
		cur_s = open[front_o++]; // Lay ra node dau danh sach
		
		if (strcmp(goal.board,cur_s.board) == 0) {
			printf("da tim thay ket qua. Khong gian search hien tai:%d\n",node_count );
			ket_qua(front_o - 1);
			break;
		}
		else {
			closed[rear_c++] = cur_s;
			
			if (cur_s.pos > 2) next_s = create_state(cur_s,0); // Vi tri 0,1,2 khong the di chuyen len	
			i_da_co_open = da_co_trong_open(next_s); // Kiem tra state moi da co trong danh sach open chua
			i_da_co_closed = da_co_trong_closed(next_s); // Kiem tra state moi da co trong danh sach closed chua
			if 	(i_da_co_open == 0 && i_da_co_closed == 0) { // Neu chua co thi them vao danh sach open
				open[rear_o++] = next_s; //
				path[node_count++] = front_o - 1; // Ghi lai vi tri state cha cua state hien tai
			}
			if (cur_s.pos < 6) next_s = create_state(cur_s,1);	// Vi tri 6,7,8 khong the di xuong
			i_da_co_open = da_co_trong_open(next_s);
			i_da_co_closed = da_co_trong_closed(next_s);
			if 	(i_da_co_open == 0 && i_da_co_closed == 0) {
				open[rear_o++] = next_s;
				path[node_count++] = front_o - 1;// Ghi lai vi tri state cha cua state hien tai
			}
		
			if (cur_s.pos % 3 != 0) next_s = create_state(cur_s,2);	//Vi tri 0,3,6 khong the sang trai
			i_da_co_open = da_co_trong_open(next_s);
			i_da_co_closed = da_co_trong_closed(next_s);
			if 	(i_da_co_open == 0 && i_da_co_closed == 0) {
				open[rear_o++] = next_s;
				path[node_count++] = front_o - 1;// Ghi lai vi tri state cha cua state hien tai
			}
		
			if ((cur_s.pos + 1) % 3 != 0) next_s = create_state(cur_s,3); // Vi tri 2,5,8 khong the dich sang phai	
			i_da_co_open = da_co_trong_open(next_s);
			i_da_co_closed = da_co_trong_closed(next_s);
			if 	(i_da_co_open == 0 && i_da_co_closed == 0) {
				open[rear_o++] = next_s;
				path[node_count++] = front_o - 1;// Ghi lai vi tri state cha cua state hien tai
			}
			
		}
	}

	//print_state(cur_s);
	return 0;
}