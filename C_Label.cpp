#include "C_Label.h"


void C_Label::Create(Win_Frame* pFrame, std::string Text, int x, int y, int ancho, int alto, W_Align Align){
	// Crear y contener
	C_Objeto::Create(pFrame, Text, x, y, ancho, alto);
	C_Objeto::Contener(*this);
	// Valores propios
	this->Align = Align;
	// Detalles del objeto
	Tipo = "STATIC";
	// Estilo
	switch (Align){
	case W_Align::A_IZQ:
		Estilo = WS_CHILD | WS_VISIBLE;
		break;
	case W_Align::A_DER:
		Estilo = WS_CHILD | WS_VISIBLE | SS_RIGHT;
		break;
	case W_Align::A_CENT:
		Estilo = WS_CHILD | WS_VISIBLE | SS_CENTER;
		break;
	}
}

void C_Label::Set_TextColor(COLORREF Color) {
	C_Objeto::TextColor = Color;
}

void C_Label::Set_BackColor(COLORREF Color){
	C_Objeto::BackColor = Color;
}

void C_Label::Set_Text(string Text) {
	LimpiarLabel = true;
	C_Objeto::Set_Text(this->Texto);
	
	C_Objeto::Set_Text(Text);
}
