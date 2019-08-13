struct Frac{
    int num, den;
    Frac(){
        num = 0; den = 1;
    }
    Frac(int a, int b): num(a), den(b){}
    Frac(int a):num(a), den(1){}

    void normalize(){
        if(num == 0){
            den = 1;
        }
        if(den < 0){
            den = -den;
            num = -num;
        }
    }

    Frac fix(int a, int b){
        if(!a) return Frac(0,1);
        if(!b) return Frac(oo,1);
        int foo = gcd(abs(a),abs(b));
        Frac ret = Frac(a/foo, b/foo);
        ret.normalize();
        return ret;
    }

    Frac operator + (const Frac& other){
        int num2 = num*other.den + den*other.num, den2 = den*other.den;
        return fix(num2,den2);       
    }

    Frac operator - (const Frac& other){
        int num2 = num*other.den - den*other.num, den2 = den*other.den;
        return fix(num2,den2);
    }

    Frac operator * (int c){
        int num2 = num*c, den2 = den;
        return fix(num2,den2);
    }

    Frac operator * (const Frac& other){
        int num2 = num*other.num, den2 = den*other.den;
        return fix(num2,den2);
    }

    Frac operator / (int c){
        int num2 = num, den2 = den * c;
        return fix(num2,den2);
    }

    Frac operator / (const Frac& other){
        int num2 = num*other.den, den2 = den*other.num;
        return fix(num2,den2);
    }

    bool operator < (const Frac& other) const{
        if(num * other.den < other.num*den) return true;
        return false;
    }
    
    bool operator == (const Frac& other) const{
        if(num == other.num && den == other.den) return true;
        return false;
    }
};
