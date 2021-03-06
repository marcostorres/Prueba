#include "igvFuenteLuz.h"

// Metodos constructores 

igvFuenteLuz::igvFuenteLuz() {
}

igvFuenteLuz::igvFuenteLuz(const unsigned int _idLuz,
													 const igvPunto3D  & _posicion,
													 const igvColor & cAmb, const igvColor & cDif, const igvColor & cEsp,
													 const double a0, const double a1, const double a2) {

  idLuz = _idLuz;
														 
	posicion = _posicion;
														 
	colorAmbiente = cAmb;
	colorDifuso = cDif;
	colorEspecular = cEsp;

	aten_a0 = a0;
	aten_a1 = a1;
	aten_a2 = a2;

	// valores por defecto cuando la luz no es un foco
	direccion_foco = igvPunto3D(0,0,0);
	angulo_foco = 180; // de esta manera la luz se convierte en puntual	
	exponente_foco = 0;

	encendida = true;
}

igvFuenteLuz::igvFuenteLuz(const unsigned int _idLuz,
			                     const igvPunto3D & _posicion, 
			                     const igvColor& cAmb, const igvColor& cDif, const igvColor& cEsp,
								           const double a0, const double a1, const double a2,
													 const igvPunto3D& dir_foco, const double ang_foco, const double exp_foco) {

  idLuz = _idLuz;
														 
	posicion = _posicion;
														 
	colorAmbiente = cAmb;
	colorDifuso = cDif;
	colorEspecular = cEsp;

	aten_a0 = a0;
	aten_a1 = a1;
	aten_a2 = a2;

	direccion_foco = dir_foco;
	angulo_foco = ang_foco;
	exponente_foco = exp_foco;

	encendida = true;
}

// Metodos publicos ----------------------------------------

igvPunto3D& igvFuenteLuz::getPosicion(void) {
	return posicion;
}

void igvFuenteLuz::setPosicion(igvPunto3D pos) {
	posicion = pos;
}


void igvFuenteLuz::set(const igvColor & cAmb, const igvColor & cDif, const igvColor & cEsp) {
	colorAmbiente = cAmb;
	colorDifuso = cDif;
	colorEspecular = cEsp;
}

void igvFuenteLuz::setAmbiental(const igvColor & cAmb) {
	colorAmbiente = cAmb;
}

void igvFuenteLuz::setDifuso(const igvColor & cDif) {
	colorDifuso = cDif;
}

void igvFuenteLuz::setEspecular(const igvColor & cEsp) {
	colorEspecular = cEsp;
}

igvColor & igvFuenteLuz::getAmbiental(void) {
	return colorAmbiente;
}

igvColor & igvFuenteLuz::getDifuso(void) {
	return colorDifuso;
}

igvColor & igvFuenteLuz::getEspecular(void) {
	return colorEspecular;
}

void igvFuenteLuz::setAtenuacion(double a0, double a1, double a2) {
	aten_a0 = a0;
	aten_a1 = a1;
	aten_a2 = a2;
}

void igvFuenteLuz::getAtenuacion(double & a0, double & a1, double & a2) {
	a0 = aten_a0;
	a1 = aten_a1;
	a2 = aten_a2;
}

void igvFuenteLuz::encender(void) {
  encendida = true;
}

void igvFuenteLuz::apagar(void) {
  encendida = false;
}

unsigned int igvFuenteLuz::esta_encendida(void) {
  return encendida;
}

void igvFuenteLuz::aplicar(void) {

    
    GLfloat posiciones[] = {posicion.c[0],posicion.c[1],posicion.c[2],1};
    GLfloat ambiental[] = {colorAmbiente[0],colorAmbiente[1],colorAmbiente[2]};
    GLfloat difuso[] = {colorDifuso[0],colorDifuso[1],colorDifuso[2]};
    GLfloat especular[] = {colorEspecular[0],colorEspecular[1],colorEspecular[2]};
    GLfloat dir_Foco[] = {direccion_foco[0],direccion_foco[1],direccion_foco[2]};

// APARTADO A
// si la luz está encendida
	if(esta_encendida()){
//	activar la luz
		glEnable(idLuz);
//	establecer la posición de la luz
		glLightfv(idLuz,GL_POSITION,posiciones);
//	establecer los colores ambiental, difuso y especular
		glLightfv(idLuz,GL_AMBIENT,ambiental);
		glLightfv(idLuz,GL_DIFFUSE,difuso);
		glLightfv(idLuz,GL_SPECULAR,especular);
//	establecer la atenuación radial
		glLightf(idLuz,GL_CONSTANT_ATTENUATION,aten_a0);
		glLightf(idLuz,GL_LINEAR_ATTENUATION,aten_a1);
		glLightf(idLuz,GL_QUADRATIC_ATTENUATION,aten_a2);
//	establecer la atenuación angular y la dirección del foco
		glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir_Foco);
		glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,angulo_foco);
		glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,exponente_foco);
	}else{
// si la luz está apagada
//	desactivar la luz
		apagar();
		glDisable(idLuz);
	}

	

}

