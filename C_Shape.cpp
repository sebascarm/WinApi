#include "C_Shape.h"


void C_Shape::Create(Win_Frame* pFrame, S_Style Style, int x, int y, int ancho, int alto) {
	// Crear y contener
	C_Objeto::Create(pFrame, "", x, y, ancho, alto);
	C_Objeto::Contener(*this);
	S_Estilo = Style;   // Line, Rect, Circle
    this->Redibujar = true;
}

void C_Shape::Set_Color(COLORREF Color){
    this->Color = Color;
    if (this->Iniciado) {
        // Forzamos el redibujado al no ser el arranque
        this->Redibujar = true;
        RedrawWindow(*hWnd_Padre, 0, 0, RDW_INVALIDATE);
    }
}

void C_Shape::Set_BackColor(COLORREF Color){
    this->BackColor = Color;
    if (this->Iniciado) {
        // Forzamos el redibujado al no ser el arranque
        this->Redibujar = true;
        const RECT rect = { x,y,x+ancho,y+alto };
        //InvalidateRect(hWnd, &rect, TRUE);
        RedrawWindow(*hWnd_Padre, &rect, 0, RDW_INVALIDATE);
    }
}

void C_Shape::Set_FreePoints(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5){
    this->Poligono[0] = { x+x1,y+y1 };
    this->Poligono[1] = { x+x2,y+y2 };
    this->Poligono[2] = { x+x3,y+y3 };
    this->Poligono[3] = { x+x4,y+y4 };
    this->Poligono[4] = { x+x5,y+y5 };
    
}

//*********************************************
//*** (El loop debe llamarlo)	            ***
//*** No se activa solo						***
//*********************************************
void C_Shape::Draw_Shape(HDC hdc) {
    HGDIOBJ hPen = CreatePen(PS_SOLID, 1, this->Color);
    HGDIOBJ hBrush = CreateSolidBrush(this->BackColor);
   HGDIOBJ holdPen = SelectObject(hdc, hPen);
    HGDIOBJ holdBrush = SelectObject(hdc, hBrush);
    switch (S_Estilo) {
    case S_Style::S_LINE:
        MoveToEx(hdc, x, y, NULL);
        LineTo(hdc, x+ancho, y + alto);
        break;
    case S_Style::S_RECTANGLE:
        Rectangle(hdc, x, y, x + ancho, y + alto);
        break;
    case S_Style::S_CIRCLE:
        Ellipse(hdc, x, y, x + ancho, y + alto);
        break;
    case S_Style::S_FREE:
        Polygon(hdc, this->Poligono, 5);
        break;
    }
    DeleteObject(hPen);
    DeleteObject(hBrush); 
    DeleteObject(holdPen);
    DeleteObject(holdBrush);
    this->Redibujar = false; 
    this->Iniciado = true;
}


