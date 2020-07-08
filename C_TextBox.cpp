#include "C_TextBox.h"
#include <thread>			//Para hilos (multiproceso)

void C_TextBox::Create(Win_Frame* pFrame, std::string Text, int x, int y, int ancho, int alto) {
	// Crear y contener
	C_Objeto::Create(pFrame, Text, x, y, ancho, alto);
	C_Objeto::Contener(*this);
	// Valores propios
	Tipo = "EDIT";
	Estilo = WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | WS_BORDER | BS_FLAT;

}

//*********************************************
//*** ASIGNACION DE EVENTO					***
//*********************************************
void C_TextBox::Assign_Event_Text_Change_ID(void(*Function)(int ID)){
	Funcion_Text_Change_ID = Function;
}

//*********************************************
//*** EVENTO TEXT CHANGE(El loop debe llamar)**
//*** No se activa solo						***
//*********************************************
void C_TextBox::Event_Text_Change() {
	std::thread Th_Text_C([this] {Funcion_Text_Change_ID(ID); });
	Th_Text_C.detach();
}