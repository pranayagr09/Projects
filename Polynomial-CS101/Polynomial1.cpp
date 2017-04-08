//Shraddheya Shendre (150050018)
#include "Polynomial.h"

Polynomial::Polynomial() {    
	n=100;
	for (int i=0;i<=100;i++) arrayF[i] = 0;
}

Polynomial::Polynomial(const Polynomial &p) {
	n = p.n;
	for (int i=0; i<=n; i++) {
		arrayF[i] = p.arrayF[i];
	}
}

void Polynomial::print() const { /* DONE 
	code has become lengthy as initially I was not printing
	the coefficient and/or index if it is equal to '1' (makes no sense).
	But after watching testcases on BodhiTree, modified it by explicitly
	writing a '1' before 'x' and a '1' after '^'*/    
	if (n==0 and arrayF[0]==0) cout << "0";
	bool foundNeg=false;
	for (int h=1;h<=n;h++) {
		if (arrayF[h]<0) foundNeg = true;
		if (arrayF[h]>0) break;
	} 
	if (arrayF[0]==0 and foundNeg) {cout << "-";}
	for (int i=0;i<=n;i++) {
		if(i<n){
			if (arrayF[i+1]>0) {
				if (arrayF[i]==-1 and i==0) cout << "-1 + ";
				if (arrayF[i]==-1 and i==1) cout << "1x^1 + ";
				if (arrayF[i]==1 and i==0) cout << "1 + ";
		        if (arrayF[i]==1 and i==1) cout << "1x^1 + ";
		        if (arrayF[i]==1 and i!=0 and i!=1) cout << "1x^" << i << " + ";
		        if (arrayF[i]==-1 and i!=0 and i!=1) cout << "1x^" << i << " + ";
		        if (i==0 and arrayF[i]!=1 and arrayF[i]!=-1 and arrayF[i]!=0 and i!=n) cout << arrayF[i] << " + ";
		        if (i==1 and arrayF[i]!=1 and arrayF[i]!=-1 and arrayF[i]!=0 and i!=n) cout << abs(arrayF[i]) << "x^1 + ";
		        //if (i==1 and arrayF[i]!=1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x";
		        if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and	arrayF[i]!=-1 and i!=n) cout << abs(arrayF[i]) << "x^" << i << " + ";
		        //if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and i==n) cout << arrayF[i] << "x^(" << i << ") + ";   
		}
		    else if (arrayF[i+1]<0) {
			    if (arrayF[i]==1 and i==0) cout << "1 - ";
			    if (arrayF[i]==1 and i==1) cout << "1x^1 - ";
				if (arrayF[i]==-1 and i==0) cout << "-1 - ";
		        if (arrayF[i]==-1 and i==1) cout << "1x^1 - ";
		        if (arrayF[i]==1 and i!=0 and i!=1) cout << "1x^" << i << " - ";
		        if (arrayF[i]==-1 and i!=0 and i!=1) cout << "1x^" << i << " - ";
		        if (i==0 and arrayF[i]!=-1 and arrayF[i]!=1 and arrayF[i]!=0 and i!=n) cout << arrayF[i] << " - ";
		        if (i==1 and arrayF[i]!=-1 and arrayF[i]!=1 and arrayF[i]!=0 and i!=n) cout << abs(arrayF[i]) << "x^1 - ";
		        //if (i==1 and arrayF[i]!=-1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x";
		        if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and arrayF[i]!=1 and i!=n) cout << abs(arrayF[i]) << "x^" << i << " - ";
		        //if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and i==n) cout << arrayF[i] << "x^(" << i << ") - ";   
		    }
		    if (arrayF[i+1]==0) {
				for (int y = i+2;y<=n;y++) {
					if (arrayF[y]>0) {
						if (arrayF[i]==-1 and i==0) cout << "-1 + ";
				        if (arrayF[i]==-1 and i==1) cout << "1x^1 + ";
				        if (arrayF[i]==1 and i==0) cout << "1 + ";
		                if (arrayF[i]==1 and i==1) cout << "1x^1 + ";
		                if (arrayF[i]==1 and i!=0 and i!=1) cout << "1x^" << i << " + ";
		                if (arrayF[i]==-1 and i!=0 and i!=1) cout << "1x^" << i << " + ";
		                if (i==0 and arrayF[i]!=1 and arrayF[i]!=-1 and arrayF[i]!=0 and i!=n) cout << arrayF[i] << " + ";
		                if (i==1 and arrayF[i]!=1 and arrayF[i]!=-1 and arrayF[i]!=0 and i!=n) cout << abs(arrayF[i]) << "x^1 + ";
		              //if (i==1 and arrayF[i]!=1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x";
		                if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and	arrayF[i]!=-1 and i!=n) cout << abs(arrayF[i]) << "x^" << i << " + ";
		              //if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and i==n) cout << arrayF[i] << "x^(" << i << ") + ";
		                break;
				    }
					else if (arrayF[y]<0) {
						//if (arrayF[i]==0 and i!=0) cout << " -$ ";
						if (arrayF[i]==1 and i==0) cout << "1 - ";
			            if (arrayF[i]==1 and i==1) cout << "1x^1 - ";
				        if (arrayF[i]==-1 and i==0) cout << "-1 - ";
		                if (arrayF[i]==-1 and i==1) cout << "1x^1 - ";
		                if (arrayF[i]==1 and i!=0 and i!=1) cout << "1x^" << i << " - ";
		                if (arrayF[i]==-1 and i!=0 and i!=1) cout << "1x^" << i << " - ";
		                if (i==0 and arrayF[i]!=-1 and arrayF[i]!=1 and arrayF[i]!=0 and i!=n) cout << arrayF[i] << " - ";
		                if (i==1 and arrayF[i]!=-1 and arrayF[i]!=1 and arrayF[i]!=0 and i!=n) cout << abs(arrayF[i]) << "x^1 - ";
		              //if (i==1 and arrayF[i]!=-1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x";
		                if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and arrayF[i]!=1 and i!=n) cout << abs(arrayF[i]) << "x^" << i << " - ";
		              //if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and i==n) cout << arrayF[i] << "x^(" << i << ") - ";
		                break;
			        }
					//else if (arrayF[y]==0) {}
				}
			}
		}
	    else if (i==n) {
			if (arrayF[i]>0) {
				if (i==0 and i==n) cout << arrayF[i];
				if (i==1 and arrayF[i]!=1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x^1";
				if (i==1 and arrayF[i]==1 and arrayF[i]!=0 and i==n) cout << "1x^1";
			    if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and i==n) cout << arrayF[i] << "x^" << i << "";
			    if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]==1 and i==n) cout << "1x^" << i << "";
			}
			else if (arrayF[i]<0) {
				if (i==0 and i==n) cout << arrayF[i];
			    if (i==1 and arrayF[i]!=-1 and arrayF[i]!=0 and i==n) cout << abs(arrayF[i]) << "x^1";
			    if (i==1 and arrayF[i]==-1 and arrayF[i]!=0 and i==n) cout << "1x^1";
			    if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and i==n) cout << abs(arrayF[i]) << "x^" << i << "";
			    if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]==-1 and i==n) cout << "1x^" << i << "";
			}
		}
	}
	cout << endl;
}

void Polynomial::printss() const { /* DONE  (same as print except the last endl)
	code has become lengthy as initially I was not printing
	the coefficient and/or index if it is equal to '1' (makes no sense).
	But after watching testcases on BodhiTree, modified it by explicitly
	writing a '1' before 'x' and a '1' after '^'*/    
	if (n==0 and arrayF[0]==0) cout << "0";
	bool foundNeg=false;
	for (int h=1;h<=n;h++) {
		if (arrayF[h]<0) foundNeg = true;
		if (arrayF[h]>0) break;
	} 
	if (arrayF[0]==0 and foundNeg) {cout << "-";}
	for (int i=0;i<=n;i++) {
		if(i<n){
			if (arrayF[i+1]>0) {
				if (arrayF[i]==-1 and i==0) cout << "-1 + ";
				if (arrayF[i]==-1 and i==1) cout << "1x^1 + ";
				if (arrayF[i]==1 and i==0) cout << "1 + ";
		        if (arrayF[i]==1 and i==1) cout << "1x^1 + ";
		        if (arrayF[i]==1 and i!=0 and i!=1) cout << "1x^" << i << " + ";
		        if (arrayF[i]==-1 and i!=0 and i!=1) cout << "1x^" << i << " + ";
		        if (i==0 and arrayF[i]!=1 and arrayF[i]!=-1 and arrayF[i]!=0 and i!=n) cout << arrayF[i] << " + ";
		        if (i==1 and arrayF[i]!=1 and arrayF[i]!=-1 and arrayF[i]!=0 and i!=n) cout << abs(arrayF[i]) << "x^1 + ";
		        //if (i==1 and arrayF[i]!=1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x";
		        if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and	arrayF[i]!=-1 and i!=n) cout << abs(arrayF[i]) << "x^" << i << " + ";
		        //if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and i==n) cout << arrayF[i] << "x^(" << i << ") + ";   
		}
		    else if (arrayF[i+1]<0) {
			    if (arrayF[i]==1 and i==0) cout << "1 - ";
			    if (arrayF[i]==1 and i==1) cout << "1x^1 - ";
				if (arrayF[i]==-1 and i==0) cout << "-1 - ";
		        if (arrayF[i]==-1 and i==1) cout << "1x^1 - ";
		        if (arrayF[i]==1 and i!=0 and i!=1) cout << "1x^" << i << " - ";
		        if (arrayF[i]==-1 and i!=0 and i!=1) cout << "1x^" << i << " - ";
		        if (i==0 and arrayF[i]!=-1 and arrayF[i]!=1 and arrayF[i]!=0 and i!=n) cout << arrayF[i] << " - ";
		        if (i==1 and arrayF[i]!=-1 and arrayF[i]!=1 and arrayF[i]!=0 and i!=n) cout << abs(arrayF[i]) << "x^1 - ";
		        //if (i==1 and arrayF[i]!=-1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x";
		        if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and arrayF[i]!=1 and i!=n) cout << abs(arrayF[i]) << "x^" << i << " - ";
		        //if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and i==n) cout << arrayF[i] << "x^(" << i << ") - ";   
		    }
		    if (arrayF[i+1]==0) {
				for (int y = i+2;y<=n;y++) {
					if (arrayF[y]>0) {
						if (arrayF[i]==-1 and i==0) cout << "-1 + ";
				        if (arrayF[i]==-1 and i==1) cout << "1x^1 + ";
				        if (arrayF[i]==1 and i==0) cout << "1 + ";
		                if (arrayF[i]==1 and i==1) cout << "1x^1 + ";
		                if (arrayF[i]==1 and i!=0 and i!=1) cout << "1x^" << i << " + ";
		                if (arrayF[i]==-1 and i!=0 and i!=1) cout << "1x^" << i << " + ";
		                if (i==0 and arrayF[i]!=1 and arrayF[i]!=-1 and arrayF[i]!=0 and i!=n) cout << arrayF[i] << " + ";
		                if (i==1 and arrayF[i]!=1 and arrayF[i]!=-1 and arrayF[i]!=0 and i!=n) cout << abs(arrayF[i]) << "x^1 + ";
		              //if (i==1 and arrayF[i]!=1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x";
		                if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and	arrayF[i]!=-1 and i!=n) cout << abs(arrayF[i]) << "x^" << i << " + ";
		              //if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and i==n) cout << arrayF[i] << "x^(" << i << ") + ";
		                break;
				    }
					else if (arrayF[y]<0) {
						//if (arrayF[i]==0 and i!=0) cout << " -$ ";
						if (arrayF[i]==1 and i==0) cout << "1 - ";
			            if (arrayF[i]==1 and i==1) cout << "1x^1 - ";
				        if (arrayF[i]==-1 and i==0) cout << "-1 - ";
		                if (arrayF[i]==-1 and i==1) cout << "1x^1 - ";
		                if (arrayF[i]==1 and i!=0 and i!=1) cout << "1x^" << i << " - ";
		                if (arrayF[i]==-1 and i!=0 and i!=1) cout << "1x^" << i << " - ";
		                if (i==0 and arrayF[i]!=-1 and arrayF[i]!=1 and arrayF[i]!=0 and i!=n) cout << arrayF[i] << " - ";
		                if (i==1 and arrayF[i]!=-1 and arrayF[i]!=1 and arrayF[i]!=0 and i!=n) cout << abs(arrayF[i]) << "x^1 - ";
		              //if (i==1 and arrayF[i]!=-1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x";
		                if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and arrayF[i]!=1 and i!=n) cout << abs(arrayF[i]) << "x^" << i << " - ";
		              //if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and i==n) cout << arrayF[i] << "x^(" << i << ") - ";
		                break;
			        }
					//else if (arrayF[y]==0) {}
				}
			}
		}
	    else if (i==n) {
			if (arrayF[i]>0) {
				if (i==0 and i==n) cout << arrayF[i];
				if (i==1 and arrayF[i]!=1 and arrayF[i]!=0 and i==n) cout << arrayF[i] << "x^1";
				if (i==1 and arrayF[i]==1 and arrayF[i]!=0 and i==n) cout << "1x^1";
			    if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=1 and i==n) cout << arrayF[i] << "x^" << i << "";
			    if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]==1 and i==n) cout << "1x^" << i << "";
			}
			else if (arrayF[i]<0) {
				if (i==0 and i==n) cout << arrayF[i];
			    if (i==1 and arrayF[i]!=-1 and arrayF[i]!=0 and i==n) cout << abs(arrayF[i]) << "x^1";
			    if (i==1 and arrayF[i]==-1 and arrayF[i]!=0 and i==n) cout << "1x^1";
			    if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]!=-1 and i==n) cout << abs(arrayF[i]) << "x^" << i << "";
			    if (i!=0 and i!=1 and arrayF[i]!=0 and arrayF[i]==-1 and i==n) cout << "1x^" << i << "";
			}
		}
	}
}

double Polynomial::valueAt (double x) const {    // DONE
	double sum = 0; 
	double term = 1; 
	for(int i = 0; i < n+1; i++) {  
	   for(int j = 0; j < i; j++) { 
	   term = term * x; 
	   } 
	term = term * arrayF[i]; 
	sum = sum + term; 
	term = 1; 
	} 
	return sum;
}

Polynomial Polynomial::operator + (Polynomial adder) const {    // DONE
	Polynomial result;
	if (adder.n > n) {
		result.n = adder.n;
		for (int i=0; i<=n; i++) result.arrayF[i] = adder.arrayF[i] + arrayF[i];
		for (int j=n+1; j <= result.n; j++) result.arrayF[j] = adder.arrayF[j];
	}
	else if (adder.n < n) {
		result.n = n;
		for (int k=0; k<=adder.n; k++) result.arrayF[k] = adder.arrayF[k] + arrayF[k];
		for (int l=adder.n + 1;l<=result.n;l++) result.arrayF[l] = arrayF[l];
	}
	else if (adder.n == n) {
		result.n = n;
		for (int m=0; m<=n; m++) result.arrayF[m] = adder.arrayF[m] + arrayF[m];
		for (int z=n;z>0;z--) {
			if (result.arrayF[z]==0) result.n = z-1;
			else break;
		}
	}
	return result;
}

Polynomial Polynomial::operator - (Polynomial subtract) const {   // DONE
	Polynomial result;
	if (subtract.n > n) {
		result.n = subtract.n;
		for (int i=0; i<=n; i++) result.arrayF[i] = -subtract.arrayF[i] + arrayF[i];
		for (int j=n+1; j <= result.n; j++) result.arrayF[j] = -subtract.arrayF[j];
	}
	else if (subtract.n < n) {
		result.n = n;
		for (int k=0; k<=subtract.n; k++) result.arrayF[k] = -subtract.arrayF[k] + arrayF[k];
		for (int l=subtract.n + 1;l<=result.n;l++) result.arrayF[l] = arrayF[l];
	}
	else if (subtract.n == n) {
		result.n = n;
		for (int m=0; m<=n; m++) result.arrayF[m] = -subtract.arrayF[m] + arrayF[m];
		for (int z=n;z>0;z--) {
			if (result.arrayF[z]==0) result.n = z-1;
			else break;
		}
	}
	return result;
}

Polynomial Polynomial::operator * (Polynomial multiply) const {    //          DONE
	Polynomial result;
	result.n = multiply.n + n;
	for (int j = 0; j<=n; j++) for (int k = 0; k<=multiply.n; k++)
	result.arrayF[j+k] += arrayF[j] * multiply.arrayF[k];
	return result;
}

Polynomial Polynomial::operator / (Polynomial divisor) const {   //         DONE
	Polynomial q, temp, zero;
	zero.n = 0;
	zero.arrayF[0] = 0; 
	temp.n = n;
	for (int z=0; z<=n; z++) temp.arrayF[z] = arrayF[z];
	int i, dd;
	double *d;
	if (temp.n<divisor.n) return zero;
	else {
		q.n = temp.n - divisor.n;
	    d = new double [temp.n+1];
	    while (temp.n>=divisor.n) {
			for (i=0; i<temp.n+1; i++) {                 
				d[i] = 0;
			}
			for (i=0; i<divisor.n+1; i++) {          
				d[i+temp.n-divisor.n] = divisor.arrayF[i];
			}
			dd = temp.n;
			q.arrayF[temp.n-divisor.n] = temp.arrayF[temp.n]/d[dd];
			for (i=0; i<q.n+1; i++) {
				d[i] = d[i] * q.arrayF[temp.n-divisor.n];
			}
			for (i=0; i<temp.n+1; i++) {
				temp.arrayF[i] = temp.arrayF[i] - d[i];
			}
			temp.n--;
	}
}
	return q;
}

Polynomial Polynomial::operator % (Polynomial divisor) const {    // DONE
	Polynomial zero;
	zero.n = 0;
	Polynomial q, r, temp; 
	temp.n = n;
	for (int z=0; z<=n; z++) temp.arrayF[z] = arrayF[z];
	int i, dd;
	double *d;
	q.n = temp.n - divisor.n;
	r.n = temp.n - divisor.n;
	d = new double [temp.n+1];
	if (temp.comparison(divisor*(temp/divisor))) return zero;
	while (temp.n>=divisor.n) {
			for (i=0; i<temp.n+1; i++) {
				d[i] = 0;
			}
			for (i=0; i<divisor.n+1; i++) {
				d[i+temp.n-divisor.n] = divisor.arrayF[i];
			}
			dd = temp.n;
			q.arrayF[temp.n-divisor.n] = temp.arrayF[temp.n]/d[dd];
			for (i=0; i<q.n+1; i++) {
				d[i] = d[i] * q.arrayF[temp.n-divisor.n];
			}
			for (i=0; i<temp.n+1; i++) {
				temp.arrayF[i] = temp.arrayF[i] - d[i];
			}
			temp.n--;
	}
	for (int m=0; m<temp.n+1; m++) {
		r.arrayF[m] = temp.arrayF[m];
	}
	r.n = temp.n;
	if (r.n!=0) {
		while (1){
		if (r.arrayF[r.n]==0) {r.n--;continue;}
		else break;
	    }
	}
	if (!(divisor.n==0 and divisor.arrayF[0]==1)) return r;
	else return zero;
}

void Polynomial::divide(Polynomial q, Polynomial &s, Polynomial &r) const {    //DONE
	Polynomial temp;
	temp.n = n;
	for (int i=0; i<n+1; i++) temp.arrayF[i] = arrayF[i];
	s = temp/q;
	r = temp%q;
	return;
}

Polynomial Polynomial::power (int p) const {         //DONE
	Polynomial result, temp;
	temp.n = n;
	for (int i=0; i<n+1; i++) temp.arrayF[i] = arrayF[i];
	result = temp;
	for (int j=1; j<p; j++) result = result * temp;
	return result;
}

Polynomial Polynomial::derivative() const {        // DONE
	Polynomial result;
	if (n==0) {
		result.n = 0;
		result.arrayF[0] = 0;
	}
	else if (n>0) {
		result.n = n - 1;
		for (int i=0;i<=result.n;i++) {
			result.arrayF[i] = (i+1) * arrayF[i+1];
		}
	}
	return result;
}

void Polynomial::factorise() {       // DONE
	Polynomial p1, temp;
	//rootsL = 0;
	temp.n = n;
	for (int d=0; d<=n; d++) temp.arrayF[d] = arrayF[d];
	rootsARRAY();
	temp.rootsARRAY();
	p1.n = 0;
	p1.arrayF[0] = 1;
	for (int f = 0; f<rootsL; f++) {
	    cout << "(";
		Polynomial p2;
		p2.n = 1;
		p2.arrayF[1] = 1;
		p2.arrayF[0] = - rootsv[f];
		p1 = p1 * p2;
		p2.printss();
		cout << ")" ;
	}
	
	bool flag1=false, flag2=false;
	for (int ff=0; ff<=temp.n; ff++) {
		if(temp.arrayF[ff]==p1.arrayF[ff]) {flag2 = true;continue;}
		else {flag2 = false;break;}
	}
	if (temp.n == p1.n and flag2) flag1 = true;
	if (!(flag1)) {
		Polynomial pi = temp / p1;
	    cout << "(";
	    pi.printss();
	    cout << ")";
	}
	cout << endl;
	return;
}
