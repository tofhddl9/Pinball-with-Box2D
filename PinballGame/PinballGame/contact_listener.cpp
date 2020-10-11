#include "contact_listener.h"

ContactListener::ContactListener(SoundManager* soundManager) : score_(0), soundManager_(soundManager) {}

ContactListener::~ContactListener()
{
    delete soundManager_;
}

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    body_ptr bodyA = fa->GetBody();
    body_ptr bodyB = fb->GetBody();

    int contactInfo = (int)bodyA->GetUserData() | (int)bodyB->GetUserData();

    // make bodyB Ball
    if (((int)bodyA->GetUserData() & BALL)) {
        std::swap(bodyA, bodyB);
        std::swap(fa, fb);
    }
    if (IsContactWithBall(contactInfo)) {
        int contactObjectWithBall = ContactObjectWithBall(contactInfo);
        soundManager_->PlaySFX(contactObjectWithBall);

        b2WorldManifold wm;
        contact->GetWorldManifold(&wm);

        switch (contactObjectWithBall) {
        case WATER: {
            if ((int)bodyB->GetUserData() & FLOATING) {
                waterAndBall.insert({ fa, fb });
                break;
            }
            else {
                bodyB->SetUserData((void*)(BALL | DIVING));
                break;
            }
        }

        }
    }
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    body_ptr bodyA = fa->GetBody();
    body_ptr bodyB = fb->GetBody();

    int contactInfo = (int)bodyA->GetUserData() + (int)bodyB->GetUserData();

    // make bodyB Ball
    if ((int)bodyA->GetUserData() == BALL) {
        std::swap(bodyA, bodyB);
    }

    if (IsContactWithBall(contactInfo)) {
        b2WorldManifold wm;
        contact->GetWorldManifold(&wm);
        int contactObjectWithBall = ContactObjectWithBall(contactInfo);

        switch (contactObjectWithBall) {
        case WINDMILL:
            break;
        case BUMPER_SMALL: {}
        case BUMPER_LARGE: {
            b2Vec2 reflection = GetReflection(bodyB->GetLinearVelocity(), wm.normal);
            bodyB->ApplyLinearImpulse(BUMPER_ELASTICITY * reflection, bodyB->GetPosition(), true);
            break;
        }
        case REBOUNDER: {
            b2Vec2 rebound = GetRebound(bodyB->GetLinearVelocity(), wm.normal);
            bodyB->ApplyLinearImpulse(REBOUNDER_ELASTICITY * rebound, bodyB->GetPosition(), true);
            break;
        }
        case WORMHOLE: {
            break;
        }

        }
    }
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

void ContactListener::EndContact(b2Contact* contact)
{
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    body_ptr bodyA = fa->GetBody();
    body_ptr bodyB = fb->GetBody();

    int contactInfo = (int)bodyA->GetUserData() + (int)bodyB->GetUserData();

    // make bodyB Ball
    if ((int)bodyA->GetUserData() == BALL) {
        std::swap(bodyA, bodyB);
    }
    
    if (IsContactWithBall(contactInfo)) {
        b2WorldManifold wm;
        contact->GetWorldManifold(&wm);
        int contactObjectWithBall = ContactObjectWithBall(contactInfo);

        if (contactObjectWithBall < WINDMILL) return;

        Scoring(contactObjectWithBall);
        switch (contactObjectWithBall) {
        case WINDMILL: {
            break;
        }
        case BUMPER_SMALL or BUMPER_LARGE: {
            break;
        }
        case REBOUNDER: {
            break;
        }
        case WORMHOLE: {
            bodyB->SetUserData((void*)(BALL | TRAVELING));
            break;
        }
        case WATER: {
            waterAndBall.erase({ fa, fb });
            break;
        }

        }
    }
}

int ContactListener::GetScore()
{
    return score_;
}

void ContactListener::FloatBall()
{
    if (waterAndBall.size() > 0) {
        auto it = waterAndBall.begin();
        auto end = waterAndBall.end();

        while (it != end) {
            b2Fixture* water = it->first;
            b2Fixture* ball = it->second;

            float density = water->GetDensity();
            
            std::vector<b2Vec2> intersectionPoints;

            if (FindIntersectionOfWaterAndBall(water, ball, intersectionPoints)) {
                float area = 0;
                b2Vec2 centroid = ComputeCentroid(intersectionPoints, area);

                ApplyBuoyancy(water, ball, area, b2Vec2(0.0f, -9.8f), centroid);
            }

            it++;
        }
    }
}

bool ContactListener::FindIntersectionOfWaterAndBall(b2Fixture* water, b2Fixture* ball, std::vector<b2Vec2>& vertices)
{
    b2PolygonShape* shapeOfWater = (b2PolygonShape*)water->GetShape();
    b2PolygonShape* shapeOfBall = (b2PolygonShape*)ball->GetShape();

    for (int i = 0; i < shapeOfBall->m_count; ++i) {
        vertices.push_back(ball->GetBody()->
            GetWorldPoint(shapeOfBall->m_vertices[i]));
    }

    std::vector<b2Vec2> clipPolygon;
    for (int i = 0; i < shapeOfWater->m_count; ++i) {
        clipPolygon.push_back(water->GetBody()->
            GetWorldPoint(shapeOfWater->m_vertices[i]));
    }
    
    b2Vec2 cp1 = clipPolygon[clipPolygon.size() - 1];
    for (auto cp2 : clipPolygon) {
        if (vertices.empty())
            return false;

        std::vector<b2Vec2> inputList = vertices;
        vertices.clear();
        b2Vec2 s = inputList[inputList.size() - 1];
        for (auto e : inputList) {
            if (IsInside(cp1, cp2, e)) {
                if (!IsInside(cp1, cp2, s)) {
                    vertices.push_back(GetIntersection(cp1, cp2, s, e));
                }
                vertices.push_back(e);
            }
            else if (IsInside(cp1, cp2, s)) {
                vertices.push_back(GetIntersection(cp1, cp2, s, e));
            }
            s = e;
        }
        cp1 = cp2;
    }
    return !vertices.empty();
}

bool ContactListener::IsContactWithBall(int contactInfo)
{
    return (contactInfo & BALL) > 0;
}

int ContactListener::ContactObjectWithBall(int contactInfo)
{
    contactInfo &= (~BALL);
    contactInfo &= (~TRAVELING);
    contactInfo &= (~DIVING);
    contactInfo &= (~FLOATING);
    return contactInfo;
}

float32 ContactListener::InnerProduct(b2Vec2 va, b2Vec2 vb)
{
    return va.x * vb.x + va.y * vb.y;
}

b2Vec2 ContactListener::GetRebound(b2Vec2 velocity, b2Vec2 normal)
{
    b2Vec2 reflection = GetReflection(velocity, normal);
    float32 reflectionLength = reflection.Length();
    reflection.Normalize();

    b2Vec2 rebound = reflection + REBOUNDER_CORRECTION;
    return reflectionLength * rebound;
}

b2Vec2 ContactListener::GetReflection(b2Vec2 velocity, b2Vec2 normal)
{
    return velocity + 2 * InnerProduct(-velocity, normal) * normal;
}

void ContactListener::Scoring(int objectType)
{
    switch (objectType) {
    case WINDMILL: {
        score_ += SCORE_WINDMILL;
        break;
    }
    case BUMPER_SMALL: {
        score_ += SCORE_BUMPER_SMALL;
        break;
    }
    case BUMPER_LARGE: {
        score_ += SCORE_BUMPER_LARGE;
        break;
    }
    case REBOUNDER: {
        score_ += SCORE_REBOUNDER;
        break;
    }
    case WORMHOLE: {
        score_ += SCORE_WORMHOLE;
        break;
    }
    case STAR_SMALL: {
        score_ += SCORE_STAR_SMALL;
        break;
    }
    case STAR_LARGE: {
        score_ += SCORE_STAR_LARGE;
        break;
    }
    }
}

bool ContactListener::IsInside(
    const b2Vec2 cp1, const b2Vec2 cp2, const b2Vec2 p)
{
    return (cp2.x - cp1.x)*(p.y - cp1.y) > (cp2.y - cp1.y)*(p.x - cp1.x);
}

b2Vec2 ContactListener::GetIntersection(
    const b2Vec2 cp1, const b2Vec2 cp2, const b2Vec2 s, const b2Vec2 e)
{
    b2Vec2 dc(cp1.x - cp2.x, cp1.y - cp2.y);
    b2Vec2 dp(s.x - e.x, s.y - e.y);
    float n1 = b2Cross(cp1, cp2);
    float n2 = b2Cross(s, e);
    float n3 = 1.0f / b2Cross(dc, dp);
    return b2Vec2((n1 * dp.x - n2 * dc.x) * n3, (n1 * dp.y - n2 * dc.y) * n3);
}

b2Vec2 ContactListener::ComputeCentroid(std::vector<b2Vec2> vs, float& area)
{
    int count = (int)vs.size();
    b2Assert(count >= 3);

    b2Vec2 c(0.0f, 0.0f);
    area = 0.0f;

    b2Vec2 pRef(0.0f, 0.0f);
    const float inv3 = 1.0f / 3.0f;

    for (int i = 0; i < count; ++i) {
        b2Vec2 p1 = pRef;
        b2Vec2 p2 = vs[i];
        b2Vec2 p3 = i + 1 < count ? vs[i+1] : vs[0];

        b2Vec2 e1 = p2 - p1;
        b2Vec2 e2 = p3 - p1;

        float d = b2Cross(e1, e2);
        float triangleArea = 0.5f * d;
        area += triangleArea;

        c += triangleArea * inv3 * (p1 + p2 + p3);
    }
    if (area > b2_epsilon)
        c *= 1.0f / area;
    else
        area = 0;
    return c;
}

void ContactListener::ApplyBuoyancy(b2Fixture* water, b2Fixture* ball,
    const float area, const b2Vec2 gravity, const b2Vec2 centroid)
{
    float displacedMass = water->GetDensity() * area;
    b2Vec2 buoyancyForce = displacedMass * -1 * gravity;
    ball->GetBody()->ApplyForce(buoyancyForce, centroid, true);
}
