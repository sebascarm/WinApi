#include "C_Shape.h"

bool C_Shape::Dibujo_Pendiente = false;

void C_Shape::Create(Win_Frame* pFrame, S_Style Style, int x, int y, int ancho, int alto) {
    // Crear y contener
    C_Objeto::Create(pFrame, "", x, y, ancho, alto);
    C_Objeto::Contener(*this);
    S_Estilo = Style;   // Line, Rect, Circle
    this->Redibujar = true;
}

void C_Shape::Set_Pos(int x, int y, int ancho, int alto) {
    C_Objeto::Set_Pos(x, y, ancho, alto);
    Redibujado();
}

void C_Shape::Set_Color(COLORREF Color){
    if (this->Color != Color) {
        this->Color = Color;
        Redibujado();
    }
}

void C_Shape::Set_BackColor(COLORREF Color){
    if (this->BackColor != Color) {
        this->BackColor = Color;
        Redibujado();
    }
}

void C_Shape::Set_Border_Size(int Size) {
    if (this->Grosor != Size) {
        this->Grosor = Size;
        Redibujado();
    }
}

// Funcion interna para llamar al redibujado
void C_Shape::Redibujado(){
    
    if (this->Iniciado) {
        int loops = 0;
        while ((this->Dibujo_Pendiente) & (loops < 100)) {
            Sleep(2); // Esperamos 1 ms hasta que se liberen los dibujos pendientes
            ++loops;
        };
        this->Dibujo_Pendiente = true;
        // Forzamos el redibujado al no ser el arranque
        this->Redibujar = true;
        // ampliar zona de redibujado
        int ancho_ad;
        int alto_ad;
        int x_ad;
        int y_ad;
        if (ancho > 0) {
            ancho_ad = ancho + 2;
            x_ad = x - 2;
        } else {
            ancho_ad = ancho - 2;
            x_ad = x + 2;
        } 
        if (alto > 0) {
            alto_ad = alto + 2;
            y_ad = y - 2;
        } else {
            alto_ad = alto - 2;
            y_ad = y + 2;
        }
        const RECT rect = { x_ad, y_ad ,x + ancho_ad,y + alto_ad }; //son posiciones absolutas
        //InvalidateRect(hWnd, &rect, TRUE);
        RedrawWindow(*hWnd_Padre, &rect, 0, RDW_INVALIDATE);
        Sleep(2); // Esperamos 1 ms hasta que se liberen los dibujos pendientes
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
    HGDIOBJ hPen = CreatePen(PS_SOLID, this->Grosor, this->Color);
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
    this->Dibujo_Pendiente = false;
}


