#include "C_Button.h"
#include <thread>			//Para hilos (multiproceso)

void C_Button::Create(Win_Frame* pFrame, std::string Text, int x, int y, int ancho, int alto) {
	// Crear y contener
	C_Objeto::Create(pFrame, Text, x, y, ancho, alto);
	C_Objeto::Contener(*this);
	//Detalles del objeto
	Tipo = "BUTTON";
	//Estilo = BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_FLAT;
	Estilo = BS_PUSHBUTTON | BS_NOTIFY | WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_FLAT;
}


//*********************************************
//*** ASIGNACION DE EVENTO					***
//*********************************************
void C_Button::Assign_Event_Click(void(*Function)()) {
	Funcion_Click = Function;
	Uso_Dinamico = false;
}
void C_Button::Assign_Event_Press(void(*Function)()) {
	Funcion_Press = Function;
	Uso_Dinamico = false;
}
void C_Button::Assign_Event_Click_ID(void(*Function)(int ID)) {
	Funcion_Click_ID = Function;
	Uso_Dinamico = true;
}
void C_Button::Assign_Event_Press_ID(void(*Function)(int ID)) {
	Funcion_Press_ID = Function;
	Uso_Dinamico = true;
}
//*********************************************
//*** EVENTO CLICK (El loop debe llamarlo)	***
//*** No se activa solo						***
//*********************************************
void C_Button::Event_Click() {
	if (!Uso_Dinamico) {
		std::thread Th_Click([this] {Funcion_Click(); });
		Th_Click.detach();
	} else {
		std::thread Th_Click_ID([this] {Funcion_Click_ID(ID); });
		Th_Click_ID.detach();
	}
}

void C_Button::Event_Press() {
	if (!Uso_Dinamico) {
		std::thread Th_Press([this] {Funcion_Press(); });
		Th_Press.detach();
	} else {
		std::thread Th_Press_ID([this] {Funcion_Press_ID(ID); });
		Th_Press_ID.detach();
	}
}

