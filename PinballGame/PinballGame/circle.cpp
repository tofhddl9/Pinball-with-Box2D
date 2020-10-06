#include "circle.h"

void Circle::RenderCircle()
{
    glPushMatrix();
    glTranslatef(body_->GetPosition().x, body_->GetPosition().y, 0.0f);

    float theta;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        theta = b2_pi * i / 180;
        glVertex2f(radius_ * cos(theta), radius_ * sin(theta));
    }
    glEnd();
    glPopMatrix();
}