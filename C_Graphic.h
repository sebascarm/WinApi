#pragma once
//######################################################//
// Graphic v1.0											//
//######################################################//
// ULTIMA MODIFICACION DOCUMENTADA                      //
// 30/06/2020                                           //
// Creacion                                             //
//######################################################//

#pragma once
#include "C_Objeto.h"

class C_Graphic :public Win_Graphic, public C_Objeto {
protected:
	HBITMAP			hBitmap;
	BITMAP			bitmap;
	HDC				hdcMem;
	HGDIOBJ			oldBitmap;
	string			Imagen;				//archivo bmp

public:
	bool	Redibujar = false; // utilizado para enviar redibujado

	void Create(Win_Frame* pFrame, string Imagen_bmp, int x, int y, int ancho, int alto);
	// Propiedades	
	int		Get_Pos_X() { return C_Objeto::Get_Pos_X(); }
	int		Get_Pos_Y() { return C_Objeto::Get_Pos_Y(); }
	// Metodos		
	void	Set_Enable() { C_Objeto::Set_Enable(); }
	void	Set_Disable() { C_Objeto::Set_Disable(); }
	// Metodos propios 
	
	// Evento		(Llamado automatico al dibujar)
	void	Draw_Shape(HDC hdc);

};

