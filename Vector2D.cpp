#include "Vector2D.h"


Vector2D::Vector2D(float x, float y){
	m_x = x;
	m_y = y;	
}

Vector2D::Vector2D(void){
	m_x = 0;
	m_y = 0;		
}

float Vector2D::getX(){
	return m_x;
}

float Vector2D::getY(){
	return m_y;
}

void Vector2D::setX(float x){
	m_x = x;
}

void Vector2D::setY(float y){
	m_y = y;	
}

float Vector2D::length(){
	return sqrt(pow(m_y,2) + pow (m_x,2));
}

void Vector2D::normaliza(){
	float modulo = length();
	m_x = m_x/modulo;
	m_y = m_y/modulo;
}

