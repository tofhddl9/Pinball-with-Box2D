#include "Flipper.h"

Flipper::Flipper(b2World *world, const b2Vec2 pivot_pos, const b2Vec2 head_pos, const float head_angle, bool is_left)
{
	isKeyDown_ = false;
	isLeft_ = is_left;
	halfWH_ = b2Vec2(2.0f, 0.1f);

	CreatePivot(world, pivot_pos);
	CreateHead(world, head_pos, head_angle);
	CreateJoint(world, is_left);
}

// for windmill
Flipper::Flipper(b2World* world, const b2Vec2 pos, const b2Vec2 LWH)
{
	isKeyDown_ = false;
	halfWH_ = LWH;

	CreatePivot(world, pos);
	CreateHead(world, pos, LWH);
	CreateJoint(world);
}

void Flipper::Render()
{
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.5f);
	glTranslatef(head_->GetPosition().x, head_->GetPosition().y, 0.0f);
	glRotatef(head_->GetAngle() * 180 / b2_pi, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex2f(-halfWH_.x, -halfWH_.y);
		glVertex2f(-halfWH_.x, halfWH_.y);
		glVertex2f(halfWH_.x, -halfWH_.y);
		glVertex2f(halfWH_.x, halfWH_.y);
	}
	glEnd();
	glPopMatrix();
}
void Flipper::SetIsKeyDown(bool isKeyDown)
{
	isKeyDown_ = isKeyDown;
}

bool Flipper::IsKeyDown()
{
	return isKeyDown_;
}

void Flipper::Flip()
{
	float speed;
	speed = isLeft_ ? 20.0f : -20.0f;
	joint_->SetMotorSpeed(speed);
}

void Flipper::Unflip()
{
	float speed;
	speed = isLeft_ ? -10.0f : 10.0f;
	joint_->SetMotorSpeed(speed);
}

void Flipper::CreatePivot(b2World* world, const b2Vec2 pivot_pos)
{
	b2BodyDef pivot_bd;
	pivot_bd.type = b2_staticBody;
	pivot_bd.position.Set(pivot_pos.x, pivot_pos.y);
	pivot_ = world->CreateBody(&pivot_bd);

	b2CircleShape circle;
	circle.m_radius = 0.1f;
	pivot_->CreateFixture(&circle, 0.0f);
}

void Flipper::CreateHead(b2World* world, const b2Vec2 head_pos, const float head_angle)
{
	b2BodyDef head_bd;
	head_bd.type = b2_dynamicBody;
	head_bd.position = head_pos;
	head_bd.angle = head_angle;
	head_ = world->CreateBody(&head_bd);

	b2PolygonShape box;
	box.SetAsBox(2.0f, 0.1f);
	head_->CreateFixture(&box, 10.0f);

	int objectType = FLIPPER;
	head_->SetUserData((void*)objectType);
}

void Flipper::CreateHead(b2World* world, const b2Vec2 head_pos, const b2Vec2 LWH)
{
	b2BodyDef head_bd;
	head_bd.type = b2_dynamicBody;
	head_bd.position = head_pos;
	head_ = world->CreateBody(&head_bd);

	b2PolygonShape box;
	box.SetAsBox(LWH.x, LWH.y);
	head_->CreateFixture(&box, 1000.0f);

	int objectType = FLIPPER;
	head_->SetUserData((void*)objectType);
}

void Flipper::CreateJoint(b2World* world, const bool is_left)
{
	b2RevoluteJointDef jd;
	jd.Initialize(pivot_, head_, pivot_->GetWorldCenter());
	jd.collideConnected = false;
	jd.enableLimit = true;
	jd.maxMotorTorque = 5000.0f;
	jd.motorSpeed = 10.0f;
	jd.enableMotor = true;

	if (is_left) {
		jd.localAnchorA.Set(0, 0);
		jd.localAnchorB.Set(-halfWH_.x, 0);
		jd.lowerAngle = 1.0f * b2_pi / 180.0f;
		jd.upperAngle = 45.0f * b2_pi / 180.0f;
	}
	else {
		jd.localAnchorA.Set(0, 0);
		jd.localAnchorB.Set(halfWH_.x, 0);
		jd.lowerAngle = -45.0f * b2_pi / 180.0f;
		jd.upperAngle = -1.0f * b2_pi / 180.0f;
	}
	joint_ = (b2RevoluteJoint*)world->CreateJoint(&jd);
}

void Flipper::CreateJoint(b2World* world)
{
	b2RevoluteJointDef jd;
	jd.Initialize(pivot_, head_, pivot_->GetWorldCenter());
	jd.collideConnected = false;
	jd.maxMotorTorque = 10000.0f;
	jd.motorSpeed = -20.0f;
	jd.enableMotor = true;
	joint_ = (b2RevoluteJoint*)world->CreateJoint(&jd);
}
