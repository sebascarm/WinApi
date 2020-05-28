#pragma once
#include "C_Objeto.h"

// Dependencias			
// Agregar en WinApi	
// Agregar en General	
// Agregar en Contenedor
// Agregar en C_Objeto	

class C_Shape:public Win_Shape, public C_Objeto {
public:
	void Create(Win_Frame* pFrame, S_Style Style, int x, int y, int ancho, int alto);
	// Propiedades	
	string	Get_Text() { return C_Objeto::Get_Text(); }
	int		Get_Pos_X() { return C_Objeto::Get_Pos_X(); }
	int		Get_Pos_Y() { return C_Objeto::Get_Pos_Y(); }
	S_Style S_Estilo;
	// Metodos		
	void	Set_Text(string Text) { C_Objeto::Set_Text(Text); }
	void	Set_Pos(int x, int y, int ancho, int alto) { C_Objeto::Set_Pos(x, y, ancho, alto); }
	void	Set_Enable() { C_Objeto::Set_Enable(); }
	void	Set_Disable() { C_Objeto::Set_Disable(); }

	// Evento		(Llamado automatico al dibujar)
	void	Draw_Shape();
};

