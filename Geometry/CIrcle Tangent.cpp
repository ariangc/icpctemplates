//Asumo que las circunferencias son diferentes
//Centro p y radio r1, centro q y radio r2 
//Al menos un radio tiene que ser mayor que 0
//maneja el caso en que un circulo es punto 
vector< Line > ComputeTgtInt(PT p, double r1, PT q, double r2){
	vector< Line > out;
	out.clear(); 
	if(equal(p, q)) return out;
	if(r1 > r2){
		swap(r1, r2);
		swap(p, q);
	}
	
	double distcent = sqrt(dist2(p, q)); 
	if(distcent + r1 - EPS < r2){
		return out;
	}

	vector< PT > ccinter =  CircleCircleInter(p, q, r1, r2);	
	Line lin; 
	if(sz(ccinter) == 2) return out;
	else{
		if(sz(ccinter) == 1){
			PT tmp = ccinter[0];
			lin.fst = tmp;
			lin.snd = tmp + RotateCCW90(p - tmp); 
			out.pb(lin);
		}
		else{
			PT O1; 
			O1 = (p * r2 + q * r1) / (r1 + r2); 
			double distc = sqrt(dist2(q, O1));
			double Alfa = asin(r2 / distc);
			PT tmp1 = (p - O1) * cos(Alfa);
			PT tmp2 = (q - O1) * cos(Alfa); 
			lin.fst = O1 + RotateCCW(tmp1, Alfa);
			lin.snd = O1 + RotateCCW(tmp2, Alfa);
			out.pb(lin);
			lin.fst = O1 + RotateCCW(tmp1, 2 * PI - Alfa);
			lin.snd = O1 + RotateCCW(tmp2, 2 * PI - Alfa);
			out.pb(lin);			
		}	
		return out;	
	}
}

//Asumo que las circunferencias son diferentes
//Centro p y radio r1, centro q y radio r2 
//Siempre devuelve 0 o 2 tangentes
//En el caso de que solo haya 1, devuelve 2 rectas que son 
//las mismas salvo por EPS 
vector< Line > ComputeTgtExt(PT p, double r1, PT q, double r2){
	vector< Line > out;
	out.clear(); 
	if(equal(p, q)) return out;
	if(r1 > r2){
		swap(r1, r2);
		swap(p, q);
	}
	
	double distcent = sqrt(dist2(p, q)); 
	if(distcent + r1 + EPS < r2){
		return out;
	}
	
	Line lin;
	PT tmp1, tmp2;
	if(abs(r1 - r2) < EPS){
		tmp1 = q - p;
		tmp1 = tmp1 * (r1 / distcent);
		tmp2 = p - q;
		tmp2 = tmp2 * (r2 / distcent);
		lin.fst = p + RotateCCW90(tmp1);
		lin.snd = q + RotateCW90(tmp2);
		out.pb(lin);
		lin.fst = p + RotateCW90(tmp1);
		lin.snd = q + RotateCCW90(tmp2); 
		out.pb(lin);	
	}
	else{
		double sinalfa = (r2 - r1) / distcent;
		sinalfa = max(sinalfa, 0.0); 
		double Alfa = asin(sinalfa);
		PT O1;
		O1 = p + (p - q) * r1 / (r2 - r1);
		tmp1 = (p - O1) * cos(Alfa);
		tmp2 = (q - O1) * cos(Alfa);
		lin.fst = O1 + RotateCCW(tmp1, Alfa);
		lin.snd = O1 + RotateCCW(tmp2, Alfa);	
		out.pb(lin);
		lin.fst = O1 + RotateCCW(tmp1, 2 * PI - Alfa);
		lin.snd = O1 + RotateCCW(tmp2, 2 * PI - Alfa);
		out.pb(lin);	
	}
	return out;
}
