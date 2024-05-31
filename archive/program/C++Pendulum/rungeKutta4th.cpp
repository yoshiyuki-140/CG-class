/*------------------------------------------------------------
 4����Runge-Kutta�@
 ���� dfunc	: �������������L�q����Ă���֐���
	  dim	: �A�������������̎�����
	  x[]	: ��ԕϐ�
	�@t		: ���ݎ����i�����ł͂Ȃ��Ɨ��ϐ��̏ꍇ������j
	�@dt	: t�̂����ݕ�
--------------------------------------------------------------*/
void rungeKutta4th( void (*dfunc)(double *, double *, double ), int dim, double x[], double t, double dt)
{
	double k1[dim], k2[dim], k3[dim], k4[dim], f[dim];
	double tmpX[dim], tmpT;
	int i;

	dfunc(f, x, t);

	for (i = 0; i < dim ; i++){
		k1[i]   = f[i]*dt;          /* k1 = f(x, t)*dt */
		tmpX[i] = x[i] + k1[i]*0.5; /* tmpX = x + k1/2 */
	}
	tmpT = t + dt*0.5;
	dfunc(f, tmpX, tmpT);

	for (i = 0; i < dim; i++){
		k2[i]   = f[i]*dt;          /* k2 = f(x + k1/2, t + dt/2)*dt */
		tmpX[i] = x[i] + k2[i]*0.5; /* tmpX = x + k2/2 */
	}
	dfunc(f, tmpX, tmpT);

	for (i = 0; i < dim ; i++){
		k3[i]   = f[i]*dt;      	/* k3 = f(x + k2/2, t + dt/2)*dt */
		tmpX[i] = x[i] + k3[i]; 	/* tmpX = x + k3 */
	}
	tmpT = t + dt;
	dfunc(f, tmpX, tmpT);

	for (i = 0; i < dim ; i++){
		k4[i] = f[i]*dt;		/* k4 = f(x + k3, t + dt)*dt */
		/* x = x + (k1 + 2*k2 + 2*k3 + k4)/6 */
		x[i] += (k1[i] + 2.0*(k2[i] + k3[i]) + k4[i])/6.0;
	}
}
