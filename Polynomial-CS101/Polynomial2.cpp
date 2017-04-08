//Pranay Agrawal (150050026)
#include "Polynomial.h"

void Polynomial::read() {    // DONE
	int nTerms;
	int tp;
	int exp[101];
	cin >> nTerms;
	for (int i=0;i<nTerms;i++) {
		cin >> tp;
		cin >> arrayF[tp];
		exp[i] = tp;
	}
	int maxsofar=exp[0];
	for (int j=1; j< nTerms; j++) {
		if (exp[j]>maxsofar) maxsofar = exp[j];
	}
	n = maxsofar;
}

Polynomial Polynomial::integral() const {        // DONE
	Polynomial result;
	if (n==0) {
		result.n = 1;
		result.arrayF[0] = 0;
		result.arrayF[1] = arrayF[0];
	}
	else if (n>0) {
		result.n = n + 1;
		for (int i=1; i<=result.n+1; i++) {
			result.arrayF[i] = arrayF[i-1]/(i);
			result.arrayF[0] = 0;
		}
	}
	return result;
}

double Polynomial::root() const {            // DONE
    double epsilon = 1.0E-15;
    double epsilon1=1.0E-3;
    double xi = -10000;
    Polynomial q=derivative();
	while(abs(valueAt(xi))>epsilon&&xi<1000) {
        xi = xi-(valueAt(xi)/q.valueAt(xi));
    }
 //to improve precision
    if(xi>0){
        int xf=xi;
        if((xi-xf)<epsilon1) xi=xf;
        else if((xf+1-xi)<epsilon1) xi=xf+1;
    }
    if(xi<0) {
        int xf=xi-1;
        if((xi-xf)<epsilon1) xi=xf;
        else if((xf+1-xi)<epsilon1) xi=xf+1;
    }
    return xi;
}

void Polynomial::roots() const {
	           
	double epsilon = 1.0E-15;
	double xi = -10000; // here,assumed that lowest polynomial root is greater than -10000
	double xd=0;
	int n1 = n;
    if(n>1){
        Polynomial q[n-1];
        double epsilon1=1.0E-3;
        double epsilon2=1.0E-8;
        q[0]=derivative();
        for(int i=0;i<n-2;i++){
            q[i+1]=q[i].derivative();
        }
        while(n1>=1&&xi<1000) {
            while(abs(valueAt(xi))>epsilon) {
                xi = xi-(valueAt(xi)/q[0].valueAt(xi));
            }
            //to improve precision
             if(xi>0){
                int xf=xi;
                if((xi-xf)<epsilon1) xi=xf;
                else if((xf+1-xi)<epsilon1) xi=xf+1;
            }
            if(xi<0) {
                int xf=xi-1;
                if((xi-xf)<epsilon1) xi=xf;
                else if((xf+1-xi)<epsilon1) xi=xf+1;
            }
            cout<<xi<<" ";  
            int j=0;
            while (abs(q[j].valueAt(xi))<epsilon2&&j<=n-2) {
                    cout<<xi<<" "; 
                    n1=n1-1;
                    j=j+1;
                    if(j==n-1) break;
            }
            
            if(n1>1){

                xd = xi + 0.2; // assumed roots have difference > 0.2;
                if(q[0].valueAt(xi)!=0){
                    while((q[0].valueAt(xi)*q[0].valueAt(xd))>0&&xd<1000) {
                        xd=xd+0.1;

                    }
                }
                else if(q[0].valueAt(xi)==0){
                    xi=xi+0.1;
                    while((q[0].valueAt(xi)*q[0].valueAt(xd))>0&&xd<1000) {
                        xd=xd+0.1;

                    }
                }
            }
            
            xi=xd+0.3;
            n1--;
            
        }
    }
    if(n==1) {cout<<-arrayF[0]/arrayF[1];}
    cout << endl;
}
 
/*void Polynomial::plot(double xL,double xR) const {   (commented out due to obvious reasons)
    initCanvas("plot",800,800);
    Turtle t1;
    double x=t1.getX();
    double y=t1.getY();
    Line l1 (x,y+300,x,y-300);
    Line l2 (x-300,y,x+300,y);
    Line arrowx1(x+290,y-10,x+300,y);
    Line arrowx2(x+290,y+10,x+300,y);
    Line arrowy1(x-10,y-290,x,y-300);
    Line arrowy2(x+10,y-290,x,y-300);
    Text t(x-10,y+10,"O");
    Text tx(x+300,y+20,"X");
    Text ty(x+20,y-300,"Y");
    double x1=max(abs(xL),abs(xR));
    double scaleX=280/x1;
    double maxvalueAt=abs(valueAt(xL));
    for(double xM=xL;xM<=xR;xM=xM+0.1){
        maxvalueAt=max(abs(valueAt(xM)),maxvalueAt);
    }
    double scaleY=280/maxvalueAt;
    Text xL1((x+xL*scaleX),y+10,xL);
    Text xR1(x+xR*scaleX,y+10,xR);
    t1.penUp();
    t1.moveTo(x+xL*scaleX,y-valueAt(xL)*scaleY);
    t1.penDown();
    double xM=xL;
    double xM1=xM+0.1;
    double s1=0,s2=0,s3=0;
    while(xM<=xR){
        s1=(xM1-xM)*scaleX;
        s2=(valueAt(xM1)-valueAt(xM))*scaleY;
        s3=s2/s1;
        t1.left(atan(s3)*180/3.14);
        t1.forward(sqrt(pow(s1,2)+pow(s2,2)));

        t1.right(atan(s3)*180/3.14);
        xM=xM1;
        xM1=xM1+0.1;
    }
    t1.hide();
    wait(200);
}*/

void Polynomial::rootsARRAY() {  // DONE
	rootsv = new double [100];
	for (int l=0; l<100; l++) rootsv[l] = 2000;           
	double epsilon = 1.0E-15;
	double xi = -10000; // here,assumed that lowest polynomial root is greater than -10000
	double xd=0;
	int n1 = n;
	int a=0;
    if(n>1){
        Polynomial q[n-1];
        double epsilon1=1.0E-3;
        double epsilon2=1.0E-8;
        q[0]=derivative();
        for(int i=0;i<n-2;i++){
            q[i+1]=q[i].derivative();
        }
        while(n1>=1&&xi<1000) {
            while(abs(valueAt(xi))>epsilon) {
                xi = xi-(valueAt(xi)/q[0].valueAt(xi));
            }
            //to improve precision
             if(xi>0){
                int xf=xi;
                if((xi-xf)<epsilon1) xi=xf;
                else if((xf+1-xi)<epsilon1) xi=xf+1;
            }
            if(xi<0) {
                int xf=xi-1;
                if((xi-xf)<epsilon1) xi=xf;
                else if((xf+1-xi)<epsilon1) xi=xf+1;
            }
            rootsv[a] = xi;a++;  
            int j=0;
            while (abs(q[j].valueAt(xi))<epsilon2&&j<=n-2) {
                    rootsv[a] = xi; 
                    n1=n1-1;
                    j=j+1;
                    a++;
                    if(j==n-1) break;
            }
            if(n1>1){
                xd = xi + 0.2; // assumed roots have difference > 0.2;
                if(q[0].valueAt(xi)!=0){
                    while((q[0].valueAt(xi)*q[0].valueAt(xd))>0&&xd<1000) {
                        xd=xd+0.1;
                    }
                }
                else if(q[0].valueAt(xi)==0){
                    xi=xi+0.1;
                    while((q[0].valueAt(xi)*q[0].valueAt(xd))>0&&xd<1000) {
                        xd=xd+0.1;
                    }
                }
            }
            xi=xd+0.3;
            n1--;
        }
    }
    if(n==1) {rootsv[0] = -arrayF[0]/arrayF[1];}
    rootsL = 0;
    for (int h=0; h<100; h++) {
		if (rootsv[h] == 2000) break;
		else rootsL++;
	}
}

bool Polynomial::comparison(const Polynomial p){
	bool flag1=false, flag2=false;
	for (int ff=0; ff<=n; ff++) {
		if(arrayF[ff]==p.arrayF[ff]) {flag2 = true;continue;}
		else {flag2 = false;break;}
	}
	if (n == p.n and flag2) flag1 = true;
	return flag1;
}

Polynomial Polynomial :: GCD(Polynomial p){
    Polynomial m;Polynomial a;
    m.n=n;
    for(int i=0;i<=n;i++){
        m.arrayF[i]=arrayF[i];
    }

    Polynomial q=p;
    Polynomial alpha=m%q;
    a.n=alpha.n;
    while(alpha.comparison(a)==false){
        Polynomial nextm,nextq;
        nextm=q;
		nextq=m%q;
		m=nextm;
		q=nextq;
		alpha=m%q;
		a.n=alpha.n;
    }
    return q;
}

Polynomial Polynomial :: LCM(Polynomial q){
    Polynomial m;
    m.n=n;
    for(int i=0;i<=n;i++){
        m.arrayF[i]=arrayF[i];
    }
    Polynomial a=m*q;
    Polynomial b=m.GCD(q);
    Polynomial c=a/b;
    return c;

}
