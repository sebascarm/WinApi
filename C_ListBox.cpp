#include "C_ListBox.h"

void C_ListBox::Create(Win_Frame* pFrame, int x, int y, int ancho, int alto, bool Sort) {
	// Crear y contener
	C_Objeto::Create(pFrame, "", x, y, ancho, alto);
	C_Objeto::Contener(*this);
	// Detalles del objeto
	Tipo = "LISTBOX";
	// Estilo
	if (Sort) {
		Estilo = WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY;
	} else {
		Estilo = WS_CHILD | WS_VISIBLE | LBS_NOTIFY;
	}
}

int C_ListBox::Get_Row() {
	return (int)SendMessage(hWnd, LB_GETCURSEL, 0, 0);
}
void C_ListBox::Set_Row(int Row) {
	SendMessage(hWnd, LB_SETCURSEL, (WPARAM)Row, 0);
}


string C_ListBox::Get_Text() {
	//string text;
	char* text;
	int length;
	int row = this->Get_Row();
	
	length = (int)SendMessage(hWnd, LB_GETTEXTLEN, (WPARAM)row, 0);
	text = new char[length + 1];
	SendMessage(hWnd, LB_GETTEXT, (WPARAM)row, (LPARAM)text);
	//SendMessage(hWnd, LB_GETTEXT, row, (LPARAM)text);
	return text;
}

void C_ListBox::Add_Line(string Texto) {
	SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)Texto.c_str());
}

void C_ListBox::Clear() {
	SendMessage(hWnd, LB_RESETCONTENT, 0, 0);
}

//*********************************************
//*** ASIGNACION DE EVENTO					***
//*********************************************
void C_ListBox::Assign_Event_ChangeCell(void(*Function)()) {
	Function_ChangeCell = Function;
}
void C_ListBox::Assign_Event_DobleClick(void(*Function)()) {
	Function_DobleClick = Function;
}


//*********************************************
//*** EVENTO	 (El loop debe llamarlo)	***
//*** No se activa solo						***
//*********************************************
void C_ListBox::Event_ChangeCell() {
	Function_ChangeCell();
}
void C_ListBox::Event_DobleClick() {
	Function_DobleClick();
}




//std::thread Th_ChangeCell([this, row, text] {Function_ChangeCell(row, text);});
//Th_ChangeCell.detach();