#include "../include/fixed_position_constraint.h"

#include <cmath>

FixedPositionConstraint::FixedPositionConstraint() : Constraint(2) {
    /* void */
}

FixedPositionConstraint::~FixedPositionConstraint() {
    /* void */
}

void FixedPositionConstraint::calculate(
        Output *output,
        int body_i,
        OdeSolver::System *system)
{
    output->n = 2;

    const double q1 = system->Position_X[body_i];
    const double q2 = system->Position_Y[body_i];
    const double q3 = system->Angles[body_i];

    const double cos_q3 = std::cos(q3);
    const double sin_q3 = std::sin(q3);

    const double bodyX = q1 + cos_q3 * m_bodyX;
    const double bodyY = q2 + sin_q3 * m_bodyY;

    const double dbodyX_dq1 = 1.0;
    const double dbodyX_dq2 = 0.0;
    const double dbodyX_dq3 = -sin_q3 * m_bodyX;

    const double dbodyY_dq1 = 0.0;
    const double dbodyY_dq2 = 1.0;
    const double dbodyY_dq3 = cos_q3 * m_bodyY;

    const double d2bodyX_dq1_2 = 0.0;
    const double d2bodyX_dq2_2 = 0.0;
    const double d2bodyX_dq3_2 = -cos_q3 * m_bodyX;

    const double d2bodyY_dq1_2 = 0.0;
    const double d2bodyY_dq2_2 = 0.0;
    const double d2bodyY_dq3_2 = -sin_q3 * m_bodyY;

    const double C1 = bodyX - m_fixedPositionX;
    const double C2 = bodyY - m_fixedPositionY;

    output->dC_dq[0][0] = dbodyX_dq1;
    output->dC_dq[0][1] = dbodyX_dq2;
    output->dC_dq[0][2] = dbodyX_dq3;

    output->dC_dq[1][0] = dbodyY_dq1;
    output->dC_dq[1][1] = dbodyY_dq2;
    output->dC_dq[1][2] = dbodyY_dq3;

    output->d2C_dq2[0][0] = d2bodyX_dq1_2;
    output->d2C_dq2[0][1] = d2bodyX_dq2_2;
    output->d2C_dq2[0][2] = d2bodyX_dq3_2;

    output->d2C_dq2[1][0] = d2bodyY_dq1_2;
    output->d2C_dq2[1][1] = d2bodyY_dq2_2;
    output->d2C_dq2[1][2] = d2bodyY_dq3_2;

    output->ks[0] = 5000.0 * C1;
    output->ks[1] = 5000.0 * C2;

    output->kd[0] = output->kd[1] = 20.0;
}
