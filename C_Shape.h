//######################################################//
// Shape v1.6											//
//######################################################//
// ULTIMA MODIFICACION DOCUMENTADA                      //
// 26/06/2020                                           //
// Ampliacion de region de dibujo						//
// Manejo del reintento de redibujado con sleep			//
// Cambiar el grosor del borde					 		//
// Posiblidad de cambiar la posicion del grafico 		//
// Correccion en el redibujado							//
// Cambio de color										//
// Fix Varios graficos									//
// Creacion                                             //
//######################################################//

#pragma once
#include "C_Objeto.h"

// Dependencias			
// Agregar en WinApi	
// Agregar en General	
// Agregar en Contenedor
// Agregar en C_Objeto	

class C_Shape:public Win_Shape, public C_Objeto {
protected:
	bool	 Iniciado = false;
	COLORREF Color =  RGB(0, 0, 0) ;
	COLORREF BackColor = RGB(255,0,0);
	POINT	 Poligono[5] = { 0,0,0,0,0,0,0,0,0,0 };	// Para poligonos
	int		 Grosor = 1;
	void	 Redibujado();
	
public:
	static bool Dibujo_Pendiente;

	void Create(Win_Frame* pFrame, S_Style Style, int x, int y, int ancho, int alto);
	// Propiedades	
	string	Get_Text() { return C_Objeto::Get_Text(); }
	int		Get_Pos_X() { return C_Objeto::Get_Pos_X(); }
	int		Get_Pos_Y() { return C_Objeto::Get_Pos_Y(); }
	S_Style S_Estilo = S_Style::S_LINE;
	bool	Redibujar = false; // utilizado para enviar redibujado
	// Metodos		
	void	Set_Text(string Text) { C_Objeto::Set_Text(Text); }
	void	Set_Pos(int x, int y, int ancho, int alto); // parcialmente modificado
	void	Set_Enable() { C_Objeto::Set_Enable(); }
	void	Set_Disable() { C_Objeto::Set_Disable(); }
	// Metodos propios 
	void	Set_Color(COLORREF Color);
	void	Set_Border_Size(int Size);
	void	Set_BackColor(COLORREF Color);
	void	Set_FreePoints(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5);
	// Evento		(Llamado automatico al dibujar)
	void	Draw_Shape(HDC hdc);

};

